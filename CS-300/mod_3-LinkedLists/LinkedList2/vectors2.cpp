#include <iostream>
#include <fstream>
#include <algorithm>
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
    int preReqCount;
};

void NumPreReqs(vector<string> &courses, Course course)
{
    for (int i = 0; i <= courses.size() - 1; i++)
    {
        cout << courses.at(i) << endl;
    }
}

void displayCourse(vector<string> &courses)
{
    for (string course : courses)
    {
        cout << course << endl;
    }
}

void loadCourses(string txtPath, vector<string> &courses)
{
    Course course;
    course.preReqCount = 0;

    ifstream myFile;

    myFile.open(txtPath);
    string line;

    if (!myFile.good())
    {
        cout << "Unable to load " << txtPath << "file." << endl;
    }
    else
        cout << "Loading " << txtPath << "file...\n"
             << endl;
    while (getline(myFile, line))
    {
        stringstream ss(line);
        string courseID;
        string title;
        string preReq1;
        string preReq2;
        string count;

        getline(ss, courseID, ',');
        getline(ss, title, ',');
        getline(ss, preReq1, ',');
        getline(ss, preReq2, ',');

        course.courseID = courseID;
        course.title = title;
        course.preReq1 = preReq1;
        course.preReq2 = preReq2;

        if ((course.preReq1 != "") && (course.preReq2 != ""))
        {
            course.preReqCount++;
        }
        if (course.preReq1 != "")
        {
            course.preReqCount++;
        }
        courses.push_back(course.courseID + ", " + course.title + ", " + course.preReq1 + ", " + course.preReq2);
    }
    cout << course.preReqCount << endl;

    myFile.close();

    return;
}

int main()
{
    vector<string> courses;
    Course course;

    string txtPath = "testdatadv1.txt";

    loadCourses(txtPath, courses);
    // displayCourse(courses);
    NumPreReqs(courses, course);

    return 0;
}