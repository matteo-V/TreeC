#include "Node.h"
#include "RandomVariable.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <set>
#include <string>
#ifndef TREE_H
#define TREE_H

class Tree{
  //data members
  public:
    int numTaxa;
    double duration;
  protected:
    Node* root;
    RandomVariable rv;
    std::set<Node *> activeNodes;
    std::vector<Node *> treenodes;
    //std::stringstream ss;

  //methods
  public:
    //constructor
    Tree();
    Tree(float b, float d);
    Tree(float b, float d, float duration);
    //destructor
    ~Tree();
    void deleteTree(Node * ptr);

    //getters checkers and setters for active nodes
    double getTotalRate();
    void addActiveNode(Node * toAdd);
    void removeActiveNode(Node * toRemove);
    Node* chooseRandomNode();
    int numActive();
    bool hasActive();
    void printActiveNodes();


    void printTreeNodes();
    std::string printNewickTree();
    void writeTree(Node *p, std::stringstream&ss);
  protected:
    void calculateBranchLengths(Node* p);
    /* Converting class to an interface */
    //std::string printNewick();
    //float next_event_time();
    //Node* chooseRandomNode();
    //method needs to be overrideen in implementing class
    //virtual get_next_event() = 0;
    //method needs to be overriden in classes implementing this interface
    //virtual runSimulation() = 0;
};

#endif
