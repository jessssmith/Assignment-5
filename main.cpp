#include "Student.h"
#include "Faculty.h"
#include "BST.h"
#include "serBST.h"
#include "GenStack.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
  int numStudents, numFaculty;

  //create student and faculty trees
  serBST<Student*> *masterStudent = new serBST<Student*>();
  serBST<Faculty*> *masterFaculty = new serBST<Faculty*>();

  //Doubly Linked lists for rollback
  GenStack<Student*> *studRollback = new GenStack<Student*>();
  GenStack<Faculty*> *facRollback = new GenStack<Faculty*>();
  GenStack<int> *addOrRemove = new GenStack<int>();

  //check for existance of faculty and student tables
  ifstream studentTable ("studentTable");
  ifstream facultyTable ("facultyTable");
  ofstream masterFacultyOut;
  ofstream masterStudentOut;

  if(studentTable.is_open() && facultyTable.is_open()) {
    string name, level, department, major,blank;
    int stId, adId, adId2, adviseeId, numAdvisees;
    double gpa;
    //read files into master trees
    //read student first
    if(studentTable.is_open()) {
      studentTable >> numStudents;
      getline(studentTable, blank);
      for(int i = 0; i < numStudents; ++i) {
        getline(studentTable, name);
        getline(studentTable, level);
        getline(studentTable, major);
        studentTable >> stId;
        studentTable >> gpa;
        studentTable >> adId;
        Student *s = new Student(major, gpa, adId, stId, name, level);
        masterStudent->insert(s);
        getline(studentTable, blank);
        getline(studentTable, blank);
    }
  }
      //now read faculty
      if(facultyTable.is_open()) {
        facultyTable >> numFaculty;
        getline(facultyTable, blank);
        for(int i = 0; i < numFaculty; ++i) {
          getline(facultyTable, name);
          getline(facultyTable, level);
          getline(facultyTable, department);
          facultyTable >> adId2;
          facultyTable >> numAdvisees;
          Faculty *f = new Faculty(adId2, name, level, department);
          getline(facultyTable,blank);
          for(int j = 0; j < numAdvisees; ++j) {
            facultyTable >>adviseeId;
            f->addAdvisee(adviseeId);
            getline(facultyTable, blank);
          }
          masterFaculty->insert(f);
          getline(facultyTable, blank);
      }
    }
    studentTable.close();
    facultyTable.close();
    cout << "Files have been read from" << endl;
  }
  //if files dont exist
  else {
    cout << "No files found. Starting with new files" << endl;
  }

  while(true) {

    //display menu and take in selection
    int input;
    cout << "\nMENU:" << endl;
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the students id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6. Given a faculty id, print ALL the names and info of his/her advisees" << endl;
    cout << "7. Add a new student" << endl;
    cout << "8. Delete a student given the id" << endl;
    cout << "9. Add a new faculty member" << endl;
    cout << "10. Delete a faculty member given the id" << endl;
    cout << "11. Change a student’s advisor given the student id and the new faculty id" << endl;
    cout << "12. Remove an advisee from a faculty member given the ids" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;

    cin >> input;

      if(input == 1)
      //print all students
        masterStudent->printTree(masterStudent->root);
      else if(input == 2) {
        //print all faculty
        masterFaculty->printTree(masterFaculty->root);
      }
      else if(input == 3) {
        //find and display student
        cin.ignore(); //skips first input without this

        string strId;
        int id;
        cout << "Enter the students id number: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cerr << "ID's should only contain integers. Please start over" << endl;
          continue;
        }
        masterStudent->searchKey(id)->printSorF();
      }
      else if(input == 4) {
        //find and display faculty given id
        cin.ignore();

        string strId;
        int id;
        cout << "Enter the faculty members id number: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cerr << "ID's should only contain integers. Please start over" << endl;
          continue;
        }
        masterFaculty->searchKey(id)->printSorF();
      }
      else if(input == 5) {
        //given student id print their advisor
        cin.ignore();

        string strId;
        int id, advID;
        cout << "Enter the students id number: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cerr << "ID's should only contain integers. Pleaase start over" << endl;
          continue;
        }
        advID = masterStudent->searchKey(id)->getAdvisor();
        cout << "\nAdvisor information: ";
        masterFaculty->searchKey(advID)->printSorF();

      }
      else if(input == 6) {
        //given faculy id print all their students
        cin.ignore();

        string strId;
        int id, size;
        cout << "Enter the faculty members id number: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cerr << "ID's should only contain integers. Please start over" << endl;
          continue;
        }
        size = masterFaculty->searchKey(id)->getAdvisees()->getSize();
        for(int i = 0; i < size; ++i) {
          int stdID;
          stdID = masterFaculty->searchKey(id)->getAdvisees()->removeFront();
          Student *s = masterStudent->searchKey(stdID);
          s->printSorF();
          masterFaculty->searchKey(id)->addAdvisee(s->getID());
        }
      }
      else if(input == 7) {
        //insert new student
        cin.ignore();

        //get variables to create new student from user
        string name, level, major, strId, strGpa, strAdvisor;
        double gpa;
        int advisor, id;

        //name
        cout << "Enter the name of the student: ";
        getline(cin, name);

        //level
        cout << "Enter the level of the student (ex. Freshman): ";
        getline(cin, level);

        //major
        cout << "Enter the students major: ";
        getline(cin, major);

        //id
        cout << "Enter the students ID number: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cerr << "ID's should only contain integers. Please try again" << endl;
          continue;
        }

        //gpa
        cout << "Enter the students GPA: ";
        getline(cin, strGpa);
        try {
          gpa = stoi(strGpa);
        }
        catch(invalid_argument e) {
          cout << "GPA should only contain integers. Please try again" << endl;
          continue;
        }

        //advisor
        cout << "Enter the ID number of the students advisor: ";
        getline(cin, strAdvisor);
        try {
          advisor = stoi(strAdvisor);
        }
        catch(invalid_argument e) {
          cout << "Advisor ID should only contain integers. Please try again" << endl;
          continue;
        }

        //check if advisor actually exists, if they do add the student to the list of advisees
        if(masterFaculty->searchKey(advisor) == NULL) {
          cout << "No advisor with that ID" << endl;
          continue;
        }
        //add students id to faculty members list of student ids
        Faculty *f = masterFaculty->searchKey(advisor);
        f->addAdvisee(id);

        //create new student with user input
        Student *s = new Student( major, gpa, advisor, id, name, level);
        masterStudent->insert(s);

        //add to rollback
        studRollback->push(s);
        cout << studRollback->peek() << endl;
        addOrRemove->push(0);

        numStudents++;

      }
      else if(input == 8) {
        //delete student given ID
        cin.ignore();

        string strId;
        int id;
        cout << "Enter the ID of the student you want to delete: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cout << "ID should only contain integers. Please start over" << endl;
          continue;
        }

        //search for student
        if(masterStudent->searchKey(id) == NULL) {
            cout << "No student with that ID" << endl;
            continue;
        }

        //if the student exists
        Student *s = masterStudent->searchKey(id);
        //remove him from his faculty members list
        Faculty *f = masterFaculty->searchKey(s->getAdvisor());
        f->removeAdvisee(s->getID()); //why is this not deleting from the advisors list??!??!?!?
        masterStudent->deleteNode(s);

        studRollback->push(s);
        addOrRemove->push(1);

        numStudents--;
      }
      else if(input == 9) {
        //insert new faculty member
        cin.ignore(); //skips first input without this

        //get variables to create new student from user
        string name, level, strId, strGpa, department;
        int id;

        //name
        cout << "Enter the name of the faculty member: ";
        getline(cin, name);

        //level
        cout << "Enter the level of the faculty member (ex. Prof): ";
        getline(cin, level);

        //department
        cout << "Enter the faculty members department: ";
        getline(cin, department);

        //id
        cout << "Enter the faculty members ID number: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cerr << "ID should only contain integers. Please start over" << endl;
          continue;
        }

        //create new student with user input
        Faculty *f = new Faculty(id, name, level, department);
        masterFaculty->insert(f);

        facRollback->push(f);
        addOrRemove->push(2);

        numFaculty++;
      }
      else if(input == 10) {
        //delete faculty given id
        cin.ignore();

        string strId;
        int id;
        cout << "Enter the ID of the faculty member you want to delete: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cout << "ID should only contain integers. Please start over" << endl;
          continue;
        }
        //search for student
        if(masterFaculty->searchKey(id) == NULL) {
            cout << "No faculty member with that ID" << endl;
            continue;
        }

        //check if the faculty exists
        Faculty *f = masterFaculty->searchKey(id);
        f->removeAdvisee(id);

        masterFaculty->deleteNode(f);

        facRollback->push(f);
        addOrRemove->push(3);
        numFaculty--;

      }
      else if(input == 11) {
        //change students advisor given both ids
        cin.ignore();

        string strId, strId2;
        int id, id2;
        //get student id
        cout << "Enter the students ID: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cout << "ID should only contain integers. Please start over" << endl;
          continue;
        }

        //check if student exists
        if(masterStudent->searchKey(id) == NULL) {
          cout << "No student with that ID" << endl;
          continue;
        }

        //get faculty id
        cout << "Enter new faculty members ID: ";
        getline(cin, strId2);
        try {
          id2 = stoi(strId2);
        }
        catch(invalid_argument e) {
          cout << "ID should only contain integers. Please start over" << endl;
          continue;
        }

        //check if faculty member exists
        if(masterFaculty->searchKey(id2) == NULL) {
          cout << "No facutly member with that ID" << endl;
          continue;
        }

        //if both Exit
        //change advisor id of student
        Student *s = masterStudent->searchKey(id);
        int old;
        old = s->getAdvisor();
        Faculty *fOld = masterFaculty->searchKey(old);
        fOld->removeAdvisee(id);
        s->setAdvisor(id2);

        //add student to new advisors list
        Faculty *f = masterFaculty->searchKey(id2);
        f->addAdvisee(id);

        //remove student from old faculty list

      }
      else if(input == 12) {
        //remove advisee from faculty given ids
        cin.ignore();

        string strId, strId2;
        int id, id2;

        //get faculty id
        cout << "Enter the faculty members ID: ";
        getline(cin, strId2);
        try {
          id2 = stoi(strId2);
        }
        catch(invalid_argument e) {
          cout << "ID should only contain integers. Please start over" << endl;
          continue;
        }

        //check if faculty member exists
        if(masterFaculty->searchKey(id2) == NULL) {
          cout << "No facutly member with that ID" << endl;
          continue;
        }

        //get student id
        cout << "Enter the students ID: ";
        getline(cin, strId);
        try {
          id = stoi(strId);
        }
        catch(invalid_argument e) {
          cout << "ID should only contain integers. Please start over" << endl;
          continue;
        }

        //check if student exists
        if(masterStudent->searchKey(id) == NULL) {
          cout << "No student with that ID" << endl;
          continue;
        }

        //if both exist
        Faculty *f = masterFaculty->searchKey(id2);
        f->removeAdvisee(id);

      }
      else if(input == 13) {
        //rollback
        int input;
        cout << "How many commands would you like to roll back? (1-5)" << endl;
        cin >> input;
        if(input > 5) {
          cout << "Can only rollback 5 commands" << endl;
          continue;
        }
        cout << addOrRemove->mSize << endl;
        if(input > addOrRemove->mSize) {
          cout << input << " commads have not been made that can be rolled back" << endl;
          continue;
        }
        for(int i = 0; i < input; ++i) {
          int popVal;
          popVal = addOrRemove->pop();
          if(popVal == 0) {
            Student *s = studRollback->pop();
            Faculty *f = masterFaculty->searchKey(s->getAdvisor());
            f->removeAdvisee(s->getID());
            masterStudent->deleteNode(s);
            numStudents--;
          }
          else if(popVal == 1) {
            Student *s = studRollback->pop();
            Faculty *f = masterFaculty->searchKey(s->getAdvisor());
            f->addAdvisee(s->getID());
            masterStudent->insert(s);
            numStudents++;
          }
          else if(popVal == 2) {
            Faculty *f = facRollback->pop();
            masterFaculty->deleteNode(f);
            numFaculty--;
          }
          else {
            Faculty *f = facRollback->pop();
            masterFaculty->insert(f);
            numFaculty++;
          }
        }

      }
      else if(input == 14) {
        //write tress to out Files
        //exit

        masterStudentOut.open("studentTable");
        masterStudentOut << numStudents << endl;
        masterStudent->serTree(masterStudentOut);

        masterFacultyOut.open("facultyTable");
        masterFacultyOut << numFaculty << endl;
        masterFaculty->serTree(masterFacultyOut);

        delete masterStudent;
        delete masterFaculty;
        exit(1);
      }
      else {
        cout << "Enter a valid input: ";
        cin >> input;
      }
  }
}
