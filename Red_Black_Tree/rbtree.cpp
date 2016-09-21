// rbtree->cpp
/*
Written by Sean McDonald
Created 4/24/2016
Last Updated 4/26/2016
Skeleteon functions were written by Dr. Judith Challinger
References cplusplus.com for exit function, stack overflow for return
on void function
I used http://www.cs.yorku.ca/~aaw/Sotirios/RedBlackTreeAlgorithm.html
for pesudo code on successor and predecessor

*/
#include <iostream>
#include <iomanip>
#include "rbtree.h"
#include <list>

using std::cout;
using std::setw;
using std::endl;

//constructor for the Tree
RBTree::RBTree() {
    nil=new Node();
    root=nil;
}

//destructor for tree will start with the root and delete fixup
//until there is nothing left to delete
RBTree::~RBTree(){
    while(root->right != nil || root->left != nil) {
      if(root->right != nil) {
         rbDelete(root->right);
      }
      if(root->left != nil) {
         rbDelete(root->left);
      }
   }
   delete root;
   delete nil;



    /*
    while(root!=nil){
        rbDelete(root);
    }
    */
}

//Node constructor taht will null out pointers and sets color to be black
RBTree::Node::Node()
    : parent(nullptr),left(nullptr),right(nullptr),color('B')
{}

//destructor for Node delete the values being stored
RBTree::Node::~Node(){
    delete key;
    delete value;
}

//Node overload constructor
//@param const string& key1 will be the key of the new node
//@param const string& value1 will be the value of the new node
//@param Node* will be if the node is nil or not.
RBTree::Node::Node(const string& key1, const string& value1, Node* nily) {
    parent=left=right=nily;
    key=new string(key1);
    value=new string(value1);
}

//@param Node* z the newly constructed node that
//will be inserted into the tree
void RBTree::rbInsert(Node* z){
    Node* x=root;
    Node* y=nil;
    //while x is not at a leaf
    while (x!=nil){
        y=x;
        //if x is greater it will move down the tree
        if(*(z->key) < *(x->key)){
            x=x->left;
        }
        else {
            x=x->right;
        }
    }
    z->parent=y;
    if(y==nil){
        root=z;
    }
    //compare the key of the nodes, it y is larger z will be the child
    //of y
    else if(*(z->key) < *(y->key)) {
        y->left=z;
    }
    else if (*(z->key) == *(y->key) && *(z->value) < *(y->value)){
        y->left=z;
    }
    else if (*(z->key) == *(y->key) && *(z->value) > *(y->value)){
        y->right=z;
    }
    else {
        y->right=z;
    }
        z->left=nil;
        z->right=nil;
        z->color='R';
        //after you insert you need to make sure that the tree is still
        //balanced and the colors have been maintainted
        rbInsertFixup(z);
}
//@param const string& key the key to put into the node
//@param const string& value the value to be put into the node
void RBTree::rbInsert(const string& key, const string& value){
    //takes the contents of the soon to be new node and
    Node* z = new Node(key,value,nil);
    //after the node has been made call the insert function
    rbInsert(z);
}

//@param const string& key holds the node's key
//@param const string& value holds the node's key

void RBTree::rbDelete(const string& key, const string& value) {
    std::list<Node*> get_outta_mah_house;
    Node* matrix=rbTreeSearch(root,key);
    if(matrix!=nil){
        Node* node=matrix;
        while(node!=nil &&*(node->key)==key){
            get_outta_mah_house.push_back(node);
            node=rbTreeSuccessor(node);
        }
        node=rbTreePredecessor(matrix);
        while((node!=nil)&&*(node->key)==key){
            get_outta_mah_house.push_back(node);
            node=rbTreePredecessor(node);
        }
    }
          for(std::list<Node*>::iterator it = get_outta_mah_house.begin();
          it != get_outta_mah_house.end(); ++it) {
        if(*((*it)->value) == value) {
            rbDelete(*it);
         }
      }
      get_outta_mah_house.clear();
}

//print the tree
void RBTree::rbPrintTree(){
reverseInOrderPrint(root,0);
}
//the function that will be called by rbPrintTree to print the tree
void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}
//@param Node smallest current node
//@return Node*
//left child of the current node passed in
RBTree::Node* RBTree::rbTreeMinimum(Node* x){
    if(x==nil){
        return x;
    }
    while (x->left!=nil) {
        x=x->left;
    }
    return x;
}

//@param Node largest current node
//@return Node*
//right child of the current node passed in
RBTree::Node* RBTree::rbTreeMaximum(Node* x) {
    while (x->right!=nil) {
        x=x->right;
    }
    return x;
}
//@param Node* the node passed in that
//@return the node that is the right most left node of the tree
RBTree::Node* RBTree::rbTreeSuccessor(Node* x){
if(x->right!=nil){
    return rbTreeMinimum(x->right);
}
    Node* y=x->parent;
  while ((y !=nil && x==y->right)){
         x=y;
         y=y->parent;
}
return y;
}

//@param Node* the node passed in that
//@return the node that is the left most right node of the tree
RBTree::Node* RBTree::rbTreePredecessor(Node* x){
Node* y;
if(x->left!=nil){
    return rbTreeMaximum(x->left);
}
y =x->parent;
while(y!=nil && x==y->left){
    x=y;
    y=y->parent;
}
return y;
}

//@param Node* x the node that will traverse the tree
//@param const string& key the key that will be compared with the node key
//@return Node* the same node if the value isn't found otherwise will return
//a different node
RBTree::Node* RBTree::rbTreeSearch(Node* x, const string& key){
    while(x!=nil){
        if(*(x->key)==key) {
            return x;
        }
        else if(key< *(x->key)) {
            x=x->left;
        }
        else {
            x=x->right;
        }
    }
    return x;
}

//@param x, if children of the tree are unbalanced it will reorder the tree
//to restore  balance on each side of the tree
void RBTree::leftRotate(Node* x){
Node* y=x->right;
x->right=y->left;
if(y->left!=nil) {
    y->left->parent=x;
}
y->parent=x->parent;
if(x->parent==nil){
    root=y;
}
else if(x==x->parent->left){
        x->parent->left=y;
    } else {
    x->parent->right=y;
    }

y->left=x;
x->parent=y;
}

//@param Node* x
//will rotate from the left to the right side of the tree
void RBTree::rightRotate(Node* x){
Node* y=x->left;
x->left=y->right;
if(y->right!=nil) {
    y->right->parent=x;
}
y->parent=x->parent;
if(x->parent==nil){
    root=y;
}
else if(x==x->parent->right){
        x->parent->right=y;
    } else {
    x->parent->left=y;
    }
y->right=x;
x->parent=y;
}

//@param Node* will be called after an insert and maintain the colors and
//shape of  the tree
void RBTree::rbInsertFixup(Node* z){
Node* y;
while(z->parent->color=='R'){
    if (z->parent==z->parent->parent->left) {
        y=z->parent->parent->right;
        if (y->color=='R') {
            z->parent->color='B';
            y->color='B';
            z->parent->parent->color='R';
            z=z->parent->parent;
        }
        else
        {
            if (z==z->parent->right){
            z=z->parent;
            leftRotate(z);
            }
        z->parent->color='B';
        z->parent->parent->color='R';
        //was z
        rightRotate(z->parent->parent);
        }
    }
    else {
    y=z->parent->parent->left;
    if (y->color=='R') {
        z->parent->color='B';
        y->color='B';
        z->parent->parent->color='R';
        z=z->parent->parent;
    }
        else {
            if (z==z->parent->left){
                z=z->parent;
                rightRotate(z);
            }
            z->parent->color='B';
            z->parent->parent->color='R';
            leftRotate(z->parent->parent);
    }
}
}
root->color='B';
}

//@param Node *will maintain the colors of the nodes after a deletion
void RBTree::rbDeleteFixup(Node* x) {
        Node* w;
while (x!=root && x->color=='B') {
    if (x==x->parent->left) {
        w=x->parent->right;
        if (w->color=='R') {
            w->color='B';
            x->parent->color='R';
            leftRotate(x->parent);
            w=x->parent->right;
        }
        if (w->left->color=='B' && w->right->color=='B'){
            w->color='R';
            x=x->parent;
        }
        else {
             if (w->right->color=='B') {
            w->left->color='B';
            w->color='R';
            rightRotate(w);
            w=x->parent->right;
        }
        w->color=x->parent->color;
        x->parent->color='B';
        w->right->color='B';
        leftRotate(x->parent);
        x=root;
    }
      }
    else {
        w=x->parent->left;
        if (w->color=='R') {
            w->color='B';
            x->parent->color='R';
            rightRotate(x->parent);
            w=x->parent->left;
        }
        if ((w->right->color=='B') && (w->left->color=='B')){
            w->color='R';
            x=x->parent;
        }
        else {
                if(w->left->color=='B') {
            w->right->color='B';
            w->color='R';
            leftRotate(w);
            w=x->parent->left;
        }
        w->color=x->parent->color;
        x->parent->color='B';
        w->left->color='B';
        rightRotate(x->parent);
        x=root;
    }
    }
}
x->color='B';
}
//Node* u  v will be moved according to u
//Node* v will be the uncle of u
void RBTree::rbTransplant(Node* u, Node* v){
    if(u->parent==nil) {
        root=v;
    }
    else if(u==u->parent->left){
        u->parent->left=v;
    }
    else {
        u->parent->right=v;
    }
      v->parent=u->parent;
}

//@param takes a node pointer z that will be deleted
void RBTree::rbDelete(Node* z){
     Node* x;
     Node* y;
    y=z;
    char y_original=y->color;
    if (z->left==nil) {
        x=z->right;
        rbTransplant(z,z->right);
    }
    else if (z->right==nil) {
        x=z->left;
        rbTransplant(z,z->left);
    }
    else {
        y= rbTreeMaximum(z->left);
        y_original=y->color;
        x=y->left;
        if (y->parent==z) {
            x->parent=y;
        }
        else {
            rbTransplant(y,y->left);
            y->left=z->left;
            y->left->parent=y;
        }
        rbTransplant(z,y);
        y->right=z->right;
        y->right->parent=y;
        y->color=z->color;
    }
    if (y_original=='B') {
        rbDeleteFixup(x);
    }
}

//@param const string& key will match with the key to see
//if the current node it is at is the one(s) we are looking for
//@return vector of const string will return the node onto the vector
vector<const string*> RBTree::rbFind(const string& key) {
    vector<const string*>hope;
    Node* node;
    node=rbTreeSearch(root,key);
    if(node!=nil && key==*(node->key)) {
        hope.push_back(node->value);
        Node* snode;
        Node* aftersnode=node;
        snode=rbTreeSuccessor(aftersnode);
        while(snode!=nil && *(snode->key)==key) {
            hope.push_back(snode->value);
            aftersnode=snode;
            snode=rbTreeSuccessor(snode);
        }
        Node* pnode;
        Node*afterpnode=node;
        pnode=rbTreePredecessor(afterpnode);
        while(pnode!=nil && *(pnode->key)==key) {
            hope.push_back(pnode->value);
            afterpnode=pnode;
            pnode=rbTreePredecessor(pnode);
        }
    }
    return hope;
}
