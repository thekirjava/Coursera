#include <iostream>
#include <map>
#include <tuple>

using namespace std;

/*enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

using TasksInfo = map<TaskStatus, int>;*/

class TeamTasks {
public:
    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return data.at(person);
    }

    void AddNewTask(const string &person) {
        data[person][TaskStatus::NEW]++;
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string &person, int task_count) {
        TasksInfo changed;
        TasksInfo untouched;
        for (auto[key, value]:data[person]) {
            if ((task_count == 0) || (key == TaskStatus::DONE)) {
                untouched[key] = value;
            } else {
                auto nextKey = static_cast<TaskStatus>(static_cast<int>(key) + 1);
                if (task_count >= value) {
                    changed[nextKey] = value;
                    task_count -= value;
                } else {
                    changed[nextKey] = task_count;
                    untouched[key] = value - task_count;
                    task_count = 0;
                }
            }
        }
        data[person].clear();
        for (auto [key, value]:changed) {
            data[person][key] = value;
        }
        for (auto [key, value]:untouched) {
            data[person][key] += value;
        }
        auto ans = tie(changed, untouched);
        get<1>(ans).erase(TaskStatus::DONE);
        return ans;
    }

private:
    map<string, TasksInfo> data;
};

void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}