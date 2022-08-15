#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <time.h>

// #include "CSVparser.hpp"

using namespace std;

struct Course
{
    string courseId; // unique identifier
    string title;
    string preReq1;
    string preReq2;
    vector<string> preReqs;
};

// Internal structure for tree node
struct Node
{
    Course course;
    Node *left;
    Node *right;

    // default constructor
    Node()
    {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course t_course)
    {
        left = nullptr;
        right = nullptr;
        course = t_course;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree
{

private:
    Node *root;

    void addNode(Node *node, Course course);
    void inOrder(Node *node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    // void Remove(string courseId);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree()
{
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder()
{
    //  call inOrder function and pass root
    this->inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course)
{

    if (root == nullptr)
    {
        root = new Node(course);
    }
    else
    // add Node root and course
    {
        this->addNode(root, course);
    }
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId)
{
    // set current node equal to root

    Node *current = root;

    // keep looping downwards until bottom reached or matching courseId found
    // if match found, return current course
    while (current != nullptr)
    {
        // If current node matches, return it
        if (current->course.courseId.compare(courseId) == 0)
        {
            return current->course;
        }
        // If course is smaller, traverse left subtree
        if (courseId.compare(current->course.courseId) < 0)
        {
            current = current->left;
        }
        // else larger so traverse right
        else
        {
            current = current->right;
        }
    }

    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node *node, Course course)
{
    // if node is larger then add to left
    if (node->course.courseId.compare(course.courseId) > 0)
    {
        // if no left node
        // this node becomes left
        if (node->left == nullptr)
        {
            node->left = new Node(course);
        }
        // else recurse down the left node
        else
        {
            this->addNode(node->left, course);
        }
    }
    else
    {
        // if no right node
        // this node becomes right
        if (node->right == nullptr)
        {
            node->right = new Node(course);
        }
        // else recurse down the right node
        else
        {
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node *node)
{
    // if node is not equal to null ptr
    // inOrder node left
    // output courseID, title
    // inOrder right

    if (node != nullptr)
    {

        inOrder(node->left); // Traverse left side first

        cout << node->course.courseId << ", " << node->course.title << endl;

        inOrder(node->right); // Traverse right side after each level's been checked
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayCourse(Course &course)
{
    cout << course.courseId << ", " << course.title << endl;

    if (!(course.preReq2 == " "))
    {

        cout << "Prerequisites: " << course.preReq1 << ", " << course.preReq2;
    }
    else
    {
        cout << "Prerequisities: " << course.preReq1;
    }
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadCourses(string csvPath, BinarySearchTree *bst)
{
    Course course;

    cout << "Loading CSV file " << csvPath << endl;

    ifstream file;
    string line;

    try
    {
        file.open(csvPath);
        if (file.is_open())
        {
            while (file.good())
            {
                cout << line << endl;

                while (getline(file, line))
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

                    course.courseId = courseID;
                    course.title = title;
                    course.preReq1 = preReq1;
                    course.preReq2 = preReq2;

                    course.preReqs.push_back(preReq1);
                    course.preReqs.push_back(preReq2);

                    bst->Insert(course);
                    ss.clear();
                }
            }
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
}

int main(int argc, char *argv[])
{

    // process command line arguments
    string csvPath, courseKey;
    Course course;

    switch (argc)
    {
    case 2:
        csvPath = argv[1];
        // courseKey = course.courseId;
        break;
    case 3:
        csvPath = argv[1];
        // courseKey = course.courseId;
        break;
    default:
        csvPath = "ABCU_Advising_Program_Input.csv";
        // courseId = ;
    }

    // Define a binary search tree to hold all bids
    BinarySearchTree *bst;
    bst = new BinarySearchTree();

    int choice = 0;
    while (choice != 9)
    {
        if (!(choice <= 3) && (choice > 0))
        {
            cout << endl;
            cout << choice << " is not a valid option.";
            cout << endl;
        }

        cout << endl;
        cout << "==============================" << endl;
        cout << "Welcome to the course planner." << endl;
        cout << "==============================" << endl;
        cout << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {

        case 1:
            loadCourses(csvPath, bst);
            break;

        case 2:

            if (bst == NULL)
            {
                cout << "Data not loaded.";
            }
            else
                cout << "Here is a sample schedule:\n"
                     << endl;
            bst->InOrder(); // Print bids in order of courseId
            break;

        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseKey;

            transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);

            course = bst->Search(courseKey);

            if (!course.courseId.empty())
            {
                displayCourse(course);
            }
            else
            {
                cout << "Course " << courseKey << " not found." << endl;
            }
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}