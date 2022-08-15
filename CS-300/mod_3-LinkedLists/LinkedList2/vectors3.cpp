#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Course
{
    string courseID;
    string title;
    string preReq1;
    string preReq2;
    unsigned int preReqCount = 0;
    vector<string> prereqs;
    vector<string> courses;
};

class CourseList
{
private:
    struct Node
    {
        Course course;
        Node *next;
        Node *prev;

        Node()
        {
            next = nullptr;
            prev = nullptr;
        }
        Node(Course aCourse)
        {
            next = nullptr;
            prev = nullptr;
            course = aCourse;
        }
    };

public:
    void Print(vector<Course> &courses);
    void PreReqList(vector<Course> &course);
};

vector<Course> courses;

void CourseList::Print(vector<Course> &courses)
{
    for (Course course : courses)
    {
        cout << course.courseID + " " + course.title << " " << course.preReq1 << " " << course.preReq2 << endl;
    }
}

void CourseList::PreReqList(vector<Course> &courses)
{
    for (Course course : courses)
    {
        if ((course.preReq1 != "") && (course.preReq2 == ""))
        {
            course.prereqs.push_back(course.preReq1);
        }
        else
        {
            course.prereqs.push_back(course.preReq1 + ", " + course.preReq2);
        }
        cout << course.preReq1 + " " + course.preReq2 << endl;
    }
}

void loadCourses(string filePath, CourseList *list)
{
    Course course;
    string line;
    fstream myFile;
    myFile.open(filePath);

    if (!myFile.good())
    {
        cout << "Cannot load file " << filePath << "..." << endl;
    }
    else
        while (getline(myFile, line))
        {
            stringstream ss(line);

            string courseID;
            string title;
            string preReq1;
            string preReq2;

            getline(ss, courseID, ',');
            getline(ss, title, ',');
            getline(ss, preReq1, ',');
            getline(ss, preReq2, ',');

            course.courseID = courseID;
            course.title = title;
            course.preReq1 = preReq1;
            course.preReq2 = preReq2;

            courses.push_back(course);
        }
}

int main()
{
    CourseList course;
    Course acourse;

    string txtPath = "testdatadv1.txt";

    loadCourses(txtPath, &course);
    course.Print(courses);
    course.PreReqList(courses);

    return 0;
}
