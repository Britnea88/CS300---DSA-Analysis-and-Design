//============================================================================
// Name        : ABCU Advisor
// Author      : Brittany Elderts-Ajala
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <fstream>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Course {
    string courseID; // unique identifier
    string title;
    string preReq1;
    string preReq2;
    Course() {
        preReq2 = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseID);
    Course Search(string courseID);
};


/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    if (root != nullptr) {
        if (root->left != nullptr) {
            delete root->left;
        }
        if (root->right != nullptr) {
            delete root->right;
        }
    }
    delete root;
    root = nullptr;
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    this->preOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equal to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(course);
    }
    // else
    else {
        // add Node root and course
        this->addNode(root, course);
    }

}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseID) {
    // remove node root courseID
    this->removeNode(root, courseID);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseID) {
    //set current node equal to root
    Node* current = root;

    while (current != nullptr) {
        // If current node matches, return it
        if (current->course.courseID.compare(courseID) == 0) {
            return current->course;
        }
        // If courseID is smaller, traverse left subtree
        if (courseID.compare(current->course.courseID) < 0) {
            current = current->left;
        }
        // traverse right subtree
        else {
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
 * @param Course course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {

    // If node > course, add to left subtree
    if (node->course.courseID.compare(course.courseID) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        // If left node exists, keep traversing down left subtree
        else {
            this->addNode(node->left, course);
        }
    }
    // If node < course, add to right subtree
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        // If right node exists, keep traversing down right subtree
        else {
            this->addNode(node->right, course);
        }
    }
}
// Searches through the tree in order
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseID << ": "
            << node->course.title << " | "
            << node->course.preReq1 << " | "
            << node->course.preReq2 << endl;
        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output courseID, title, and prerequisites
        cout << node->course.courseID << " | " << node->course.title << " | " << node->course.preReq1 << " | " << node->course.preReq2 << endl;
    }
}

void BinarySearchTree::preOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output bidID, title, amount, fund
        cout << node->course.courseID << " | " << node->course.title << " | " << node->course.preReq1 << " | " << node->course.preReq2 << endl;
        //preOrder left
        preOrder(node->left);
        //preOrder right
        preOrder(node->right);
    }
}
Node* BinarySearchTree::removeNode(Node* node, string courseID) {

    if (node == nullptr) {
        return node;
    }

    if (courseID.compare(node->course.courseID) < 0) {
        node->left = removeNode(node->left, courseID);
    }
    else if (courseID.compare(node->course.courseID) > 0) {
        node->right = removeNode(node->right, courseID);
    }
    else {
        // no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // one child, left
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        // one child, right
        else if (node->left == nullptr && node->right != nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // two children
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->course = temp->course;
            node->right = removeNode(node->right, temp->course.courseID);
        }
    }
    return node;

}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseID << ": " << course.title << " | " << course.preReq1 << " | "
        << course.preReq2 << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadDataStructure(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        //cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of 
            Course course;
            course.courseID = file[i][1];
            course.title = file[i][0];
            course.preReq1 = file[i][8];
            course.preReq2 = strToDouble(file[i][4], '$');

            // push this course to the end
            bst->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "courseID";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "ABCU_Input.csv";
        bidKey = "courseID";
    }

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    cout << "\n\t\tABCU Course Advisor Program\n\n";
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Complete the method call to load the data structure
            loadDataStructure(csvPath, bst);
            break;

        case 2:
            // Print all courses
            bst->InOrder();
            break;

        case 3:
            // Search and print specific course
            cout << "Please enter course ID number. ";
            cin >> bidKey;

            course = bst->Search(bidKey);

            if (!course.courseID.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course ID " << bidKey << " not found." << endl;
            }

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
