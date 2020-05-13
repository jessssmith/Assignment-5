#include <iostream>

using namespace std;

//contains fields that both student and faculy have
class Person {
public:
  int m_id;
  string m_name;
  string m_level;

  Person();
  Person(int id, string name, string level);
  ~Person();
  //Person(istream& i);

  int getID();
  string getName();
  string getLevel();

  void setID();
  void setName();
  void setLevel();

  friend istream& operator >> (istream& i, Person& p);
  friend ostream& operator << (ostream&, Person& p);
  friend bool operator < (Person &p1, Person &p2);
  friend bool operator > (Person &p1, Person &p2);
};

Person::Person() {
  m_id = 0;
  m_name = "N/A";
  m_level = "unkown";
}

Person::Person(int id, string name, string level) {
  m_id = id;
  m_name = name;
  m_level = level;
}

Person::~Person() {
  //figure this out
}


//istream
/*Person::Person(istream& i) { //might have to change order..
  i >> m_id;
  getline(i, m_name);
  getline(i, m_level);
} */

//gets id (can be student or faculty)
int Person::getID() {
  return m_id;
}

//gets name of student of faculty
string Person::getName() {
  return m_name;
}

//gets level of student or faculty
string Person::getLevel() {
  return m_level;
}

//sets id
void Person::setID() {
  cout << "Enter ID #: ";
  cin >> m_id;
}

/*istream& operator >> (istream& i, Person& p) {
  i >> p.m_id;
  i >> p.m_name;
  i >> p.m_level;
  return i;
} */

ostream& operator << (ostream& o, Person p) {
  o << p.m_id << endl;
  o << p.m_name << endl;
  o << p.m_level << endl;
  return o;
}

bool operator > (Person &p1, Person &p2) {
  if(p1.m_id > p2.m_id)
    return true;
  else
    return false;
}

bool operator < (Person &p1, Person &p2) {
  if(p1.m_id < p2.m_id)
    return true;
  else
    return false;
}
