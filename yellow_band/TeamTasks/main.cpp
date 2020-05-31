#include <iostream>
#include <map>
#include <string>

using namespace std;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return person_tasks.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person) {
        person_tasks[person][TaskStatus::NEW]++;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string &person, int task_count) {
        TasksInfo upd, not_upd;
        for (const auto &task :person_tasks[person]) {
            if ((task_count != 0) && (task.first != TaskStatus::DONE)) {
                upd[static_cast<TaskStatus>(static_cast<int>(task.first) + 1)] = min(task.second, task_count);
                if (task.second <= task_count) {
                    task_count -= task.second;
                } else {
                    not_upd[static_cast<TaskStatus>(static_cast<int>(task.first))] = task.second - task_count;
                    task_count = 0;
                }
            } else {
                not_upd[static_cast<TaskStatus>(static_cast<int>(task.first))] = task.second;
            }
        }
        person_tasks[person].clear();
        for (const auto &task:upd) {
            person_tasks[person][task.first] += task.second;
        }
        for (const auto &task:not_upd) {
            person_tasks[person][task.first] += task.second;
        }
        not_upd.erase(TaskStatus::DONE);
        return tie(upd, not_upd);
    }

private:
    map<string, TasksInfo> person_tasks;
};
