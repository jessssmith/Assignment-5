//#include<iostream>
#include "GenDoublyLinked.h"
//#include "Person.h"

class Faculty : public Person {
public:
  string m_department;
  GenDoublyLinked<int> *m_advisees;
  //list of all faculty memners ids

  Faculty();
  Faculty(string department);
  Faculty(int id, string name, string level, string department);
  //Faculty(istream& i);

  string getDepartment();
  void setDepartment(string department);
  GenDoublyLinked<int>* getAdvisees();

  void addAdvisee(int id);
  void removeAdvisee(int id);
  void printSorF();

  //serialize
  ostream& serialize(ostream& o);
};

Faculty::Faculty() : Person() {
  m_department = "department1";
  m_advisees = new GenDoublyLinked<int>();
}

Faculty::Faculty(string department) : Person() {
  m_department = department;
  m_advisees = new GenDoublyLinked<int>();
}

Faculty::Faculty(int id, string name, string level, string department) : Person(id, name, level) {
  m_department = department;
  m_advisees = new GenDoublyLinked<int>();
}

//istream
/*Faculty::Faculty(istream& i) : Person(i) {
  getline(i, m_department);

  //get the linked list
  m_advisees = new GenDoublyLinked<int>();
  int size; //of the list
  i >> size;
  int id;
  for(int j = 0; j < size; ++j) {
    i >> id;
    m_advisees->insertBack(id);
  }


} */

//gets the department
string Faculty::getDepartment() {
  return m_department;
}

//set department
void Faculty::setDepartment(string department) {
  m_department = department;
}

//add students id to list
void Faculty::addAdvisee(int id) {
  m_advisees->insertBack(id);
}

//remove students id from list
void Faculty::removeAdvisee(int id) {
  m_advisees->remove(id);
}

ostream& Faculty::serialize(ostream& o) {
  o << getName() << endl;
  o << getLevel() << endl;
  o << m_department << endl;
  o << getID() << endl;
 int size = m_advisees->getSize();
 o << size << endl;
 //loop through list
 for(int i = 0; i < size; ++i)
   o << m_advisees->removeFront() << endl;
 o << endl;
  return o;
}

//print faculty
void Faculty::printSorF() {
  cout << "\n\nName: " << getName() << endl;
  cout << "Level: " << getLevel() << endl;
  cout << "ID: " << getID() << endl;
  cout << "Department: " << getDepartment() << endl;
  cout << "Advisee's: " << endl;
  m_advisees->printList();
}

GenDoublyLinked<int>* Faculty::getAdvisees() {
  return m_advisees;
}
