#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

// structure to hold course info
struct Course
{

    string courseID;
    string title;
    string preReq1;
    string preReq2;
    vector<string> courses;
    int preReqCount;
};

vector<string> loadCourses(string filePath, vector<string> courses)
{
    Course course;

    cout << "Loading .txt File...";

    ifstream myFile;

    myFile.open(filePath);
    string line;

    if (!myFile.good())
    {

        cout << "File " << filePath << " is not good." << endl;
    }
    else
    {
        while (getline(myFile, line, ','))
        {
            courses.push_back(line);
        }
    }
    return courses;
}

void printAll(vector<string> courses)
{
    for (string course : courses)
    {
        cout << course;
    }
}

int main()
{
    Course course;
    string txtPath = "testdatadv1.txt";
    vector<string> courses;

    loadCourses(txtPath, courses);

    return 0;
}