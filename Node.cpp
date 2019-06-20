#include "Node.h"
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include<string>
#include<sstream>
  //null constructors
  Node::Node(){
    float t_event= INT_MAX;
    this->parent=nullptr;
    this->rchild=nullptr;
    this->lchild=nullptr;
    }
  //simple constructor
  Node::Node(float birth, float death){
    //set all pointers to null
    this->parent=nullptr;
    this->rchild=nullptr;
    this->lchild=nullptr;
    //set rates
    this->birth_rate = birth;
    this->death_rate = death;
    }
  //constructor inheriting rates from parent
  Node::Node(Node * ancestor){
    //inherit rates from parent
    this->birth_rate = ancestor->birth_rate;
    this->death_rate = ancestor->death_rate;
    //set parent
    this->parent=ancestor;
    //set child pointers to null
    this->rchild=nullptr;
    this->lchild=nullptr;
  }
  //methods
  bool Node::hasChild(){
    bool flag = 0;
    if(this->lchild != nullptr | this->rchild!=nullptr){
      flag=1;
    }
    return(flag);
  }
  //setter for event time
  void Node::set_event_time(float tau){
    this->t_event = tau;
  }
  //getter for total rate
  float Node::get_rate(){
    return(this->birth_rate + this->death_rate);
  }
  //setter for total rate
  float Node::get_event_time(){
    return(this->t_event);
  }
  std::string Node::print_addr(){
    std::stringstream ss;
    ss << (void const *)this;
    return(ss.str());
  }

  void Node::set_left_child(Node * n){
    this->lchild = n;
  }
  void Node::set_right_child(Node *n){
    this->rchild = n;
  }
  void Node::set_parent(Node*n){
    this->parent = n;
  }
  Node * Node::get_left_child(){
    return(this->lchild);
  }
  Node * Node::get_right_child(){
    return(this->rchild);
  }
  Node * Node::get_parent(){
    return(this->parent);
  }
  float Node::get_brlen(){
    return(brlen);
  }
  void Node::set_brlen(float len){
    this->brlen = len;
  };
