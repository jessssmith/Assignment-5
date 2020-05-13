#include <iostream>
#include "Person.h"

using namespace std;

class Student : public Person {
public:
  string m_major;
  double m_gpa;
  int m_advisor;

  Student();
  Student(string major, double gpa, int advisor);
  Student(string major, double gpa, int advisor, int id, string name, string level);
  ~Student();
  //Student(istream& i);

  string getMajor();
  double getgpa();
  int getAdvisor();
  void printSorF();
  void setAdvisor(int adv);

  //serialize
  ostream& serialize(ostream& o);
};

Student::Student() : Person() {
  m_major = "working";
  m_gpa = 1.0;
  m_advisor = 1;
}

Student::Student(string major, double gpa, int advisor) : Person() {
  m_major = major;
  m_gpa = gpa;
  m_advisor = advisor;
}

Student::Student(string major, double gpa, int advisor, int id, string name, string level) : Person(id, name, level) {
  m_major = major;
  m_gpa = gpa;
  m_advisor = advisor;
}


Student::~Student() {
  //figure this out
}

//istream
/*Student::Student(istream& i) : Person(i) {
  getline(i, m_major);
  getline(i, m_major);
  i >> m_gpa;
  i >> m_advisor;
  string empty;
  getline(i, empty);
  getline(i, empty);
} */

//gets major
string Student::getMajor() {
  return m_major;
}

//gets gpa
double Student::getgpa() {
  return m_gpa;
}

//gets advisor id
int Student::getAdvisor() {
  return  m_advisor;
}

//print student
void Student::printSorF() {
  cout << "\nName: " << getName() << endl;
  cout << "Level: " << getLevel() << endl;
  cout << "GPA: " << getgpa() << endl;
  cout << "Major: " << getMajor() << endl;
  cout << "ID: " << getID() << endl;
  cout  << "Advisor: " << getAdvisor() << endl;
}

ostream& Student::serialize(ostream& o) {
  o << getName() << endl;
  o << getLevel() << endl;
  o << m_major << endl;
  o << getID() << endl;
  o << m_gpa << endl;
  o << m_advisor << endl;
  o << endl;

  return o;
}

void Student::setAdvisor(int adv) {
  m_advisor = adv;
}
