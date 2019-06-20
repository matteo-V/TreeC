#include "Node.h"
#include "Tree.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <string>

using namespace std;

Tree::Tree(void){
  this->root = new Node();
  rv = RandomVariable();
  this->activeNodes.insert(this->root);
}

Tree::Tree(float b, float d){
  rv = RandomVariable();
  treenodes.push_back(new Node);
  treenodes.push_back(new Node(b,d));
  //init tree structure
  root = treenodes[0];
  root->set_left_child(treenodes[1]);
  treenodes[1]->set_parent(root);
  //insert active lineage into set
  this->addActiveNode(treenodes[1]);
}

double Tree::getTotalRate(){
    double rtot = 0;
    for(Node* nde: this->activeNodes){ rtot += nde->get_rate();}
    return(rtot);
}


Tree::Tree(float b, float d, float duration){
  this->duration = duration;
  rv = RandomVariable();
  treenodes.push_back(new Node);
  treenodes.push_back(new Node(b,d));
  //init tree structure
  root = treenodes[0];
  root->set_left_child(treenodes[1]);
  treenodes[1]->set_parent(root);
  //insert active lineage into set
  this->addActiveNode(treenodes[1]);
  double t = 0;
  //while not extinct and there are active nodes
  // forward simulation for tree structure
  while(t < this->duration & activeNodes.size() > 0){
    /* EVENT TIME */
    //generate next event time
    double rtot = this->getTotalRate();
    //udate t
    t += rv.exponential(rtot);
    //std::cout << "Rate totals: "<< rtot << ", time: " << t << std::endl;
    //if time is still less than duration
    if(t < this->duration){
      //choose random node for event
      Node * eventNode = this->chooseRandomNode();
      //set time := t
      eventNode->set_event_time(t);
      //choose random number for event selection
      double u = rv.uniform(0,1);
      /* TODO: MAKE THIS CALL SELECT NEXT EVENT */
      if(u < b/(b+d)){ //SPECIATION
        //add two new tree nodes speciating from eventNode
        // this adds the node as the parent
        Node* new_left = new Node(eventNode);
        Node* new_right = new Node(eventNode);
        // add to tree
        treenodes.push_back(new_left);
        treenodes.push_back(new_right);
        //set new nodes as children of event node
        eventNode->set_left_child(new_left);
        eventNode->set_right_child(new_right);
        //add children to active nodes
        this->addActiveNode(new_left);
        this->addActiveNode(new_right);
        //remove parent from active nodes
        this->removeActiveNode(eventNode);
      }
      else{ //EXTINCTION
        this->removeActiveNode(eventNode); //selected node goes extinct
      };
    }

  }
  //set numTaxa to total of surviving lineages
  numTaxa = this->numActive();
  //set active nodes event time to duration
  for(Node* n: this->activeNodes){n->set_event_time(this->duration);}
  //calculate br lengths on tree
  calculateBranchLengths(this->root);

}

Tree::~Tree(void){
  deleteTree(this->root);
}

void Tree::deleteTree(Node* ptr){
  if(ptr == NULL){
    return;
  } else {
    deleteTree(ptr->get_right_child());
    deleteTree(ptr->get_left_child());
    delete(ptr);

  }
  //std::cout << "Deleted node" << std::endl;
}

void Tree::printTreeNodes(){
  for(Node* node: this->treenodes)
    std::cout << node->get_event_time() << std::endl;
  return;
}

void Tree::removeActiveNode(Node *n){
  std::set<Node *>::iterator it = this->activeNodes.find(n);
  //debug, std::cout << "Removed " << *it << std::endl;
  this->activeNodes.erase(it);
}

void Tree::calculateBranchLengths(Node* p){
  if(p != nullptr){
    calculateBranchLengths(p->get_left_child());
    calculateBranchLengths(p->get_right_child());
    if(p->get_parent() != nullptr){
    p->set_brlen(p->get_event_time() - p->get_parent()->get_event_time()); }

  }
  else {
    return;
  }
}

std::string Tree::printNewickTree(){
  std::stringstream ss; //initialize string stream
  //call recursive function starting with crown group, pass ss to build newick as reference
  this->writeTree(this->root->get_left_child(), ss);
  //since we passed by ref, ss has been modified by writeTree
  return(ss.str());
}

void Tree::writeTree(Node * p, std::stringstream &ss){
  if(p != NULL){
    if(!p->hasChild()){ //if no children print name and brlen
      ss << p << ":" << std::setprecision(3) << p->get_brlen();
    }
    else{ // recursively write tree
      ss << "(";
      writeTree(p->get_left_child(), ss);
      ss << ",";
      writeTree(p->get_right_child(), ss);
      // if parent is null, no brlen
      if(p->get_parent() == NULL){
        ss << ")";
      }
      else{ //write brlen
        ss << "):" << std::setprecision(3) << p->get_brlen();
      }
    }
  }
}

bool Tree::hasActive(void){
  return(!(this->activeNodes.empty()));
}

void Tree::printActiveNodes(void){
  for(Node* n:this->activeNodes ){
    std::cout << n->print_addr() <<std::endl;
  }
}

int Tree::numActive(void){
  return(this->activeNodes.size());
}

void Tree::addActiveNode(Node * toAdd){
  this->activeNodes.insert(toAdd);
}

Node* Tree::chooseRandomNode(void){
  std::default_random_engine gen;
  std::uniform_real_distribution<double> unif(0.0,1.0);
  int which = unif(gen) * this->activeNodes.size();
  int i = 0;
  for(Node* nde : this->activeNodes){
    if (which == i){ return nde; }
    i++;
}

return NULL;

}
