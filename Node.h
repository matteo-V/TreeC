#include<stdlib.h>
#include<string>
#include<sstream>

#ifndef NODE_H
#define NODE_H

class Node{
public:
  //data members
  float t_event;
  float birth_rate;
  float death_rate;
  //float shift_rate
  //float type
  float brlen;
protected:
  Node* parent;
  Node* lchild;
  Node* rchild;
//methods
public:
  //constructors
  Node();
  Node(float birth, float death);
  Node(Node * ancestor);

  //getters
  Node * get_left_child();
  Node * get_right_child();
  Node * get_parent();
  float get_event_time();
  float get_rate();
  float get_brlen(); 
  //setters
  void set_left_child(Node *);
  void set_right_child(Node *);
  void set_parent(Node*);
  void set_brlen(float len);
  void set_event_time(float tau);
  //boolean tests
  bool hasChild();
  //print method
  std::string print_addr();

}; // end class definition

#endif
