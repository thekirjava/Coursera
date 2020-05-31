#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person {
public:
    Person(string type, string name) : type(type), Name(name) {}

    virtual void Walk(string destination) const {
        cout << type << ": " << Name << " walks to: " << destination << endl;
    };

    string GetType() const {
        return type;
    }

    string GetName() const {
        return Name;
    }

protected:
    const string type;
    string Name;
};

class Student : public Person {
public:

    Student(string name, string favouriteSong) : Person("Student", name), FavouriteSong(favouriteSong) {}

    void Learn() const {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(string destination) const override {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

private:
    string FavouriteSong;
};


class Teacher : public Person {
public:

    Teacher(string name, string subject) : Person("Teacher", name), Subject(subject) {}

    void Teach() const {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }


private:
    string Subject;
};


class Policeman : public Person {
public:
    Policeman(string name) : Person("Policeman", name) {}

    void Check(const Person &p) const {
        cout << "Policeman: " << Name << " checks " << p.GetType() << ". " << p.GetType() << "'s name is: "
             << p.GetName() << endl;
    }


};


void VisitPlaces(Person &person, vector<string> places) {
    for (auto p : places) {
        person.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
