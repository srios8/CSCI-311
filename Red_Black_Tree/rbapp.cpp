#include "rbapp.h"
#include <iostream>
#include <sstream>
using std::cin;
using std::cout;

int main() {
    RBapp app;
    app.mainLoop();
    return 1;
}

RBapp::RBapp(){

}
//will take the input and process it and run functions
void RBapp::processCommand() {
     //int i=0;
//while (i!=100 ){
   std::string line;
   while (getline(std::cin, line)){
   std::istringstream input(line);
   std::string command;
   input >> command;
   //while (std::cin>>command){
   line = line.substr(line.find_first_of(" \t")+1);
   if(command == "insert") {
      processInsert(line);
   } else if(command == "print") {
      processPrint();
   } else if(command == "find") {
      processFind(line);
   } else if(command == "delete") {
      processDelete(line);
   } else if(command == "quit") {
       processQuit();
   } else {
      done = true;
   }
}
}

//@param string& line will be spliced and passed into
//the insert function as two strings
void RBapp::processInsert(string& line) {
   int pos = line.find(' ');
   string key = line.substr(0, pos);
   line = line.substr(line.find_first_of(" \t")+1);
   myRBT.rbInsert(key, line);
}
//@param string& line will be spliced and passed into
//the delete function as two strings
void RBapp::processDelete(string& line){
    int pos = line.find(' ');
    string key = line.substr(0, pos);
    line = line.substr(line.find_first_of(" \t")+1);
    myRBT.rbDelete(key, line);
}
//print out the entire contents of the tree
void RBapp::processPrint(){
    myRBT.rbPrintTree();
}
//will prompt the main loop that will start the program
void RBapp::mainLoop(){
    processCommand();
}
//will print out all of the same keys that occur in the tree.
void RBapp::processFind(string& line){
     vector<const string*>::iterator it;
     vector<const string*> search;
     search = myRBT.rbFind(line);
     for(it=search.begin(); it!=search.end();it++) {
         std::cout<<line<<" "<<*(*it)<<std::endl;
     }
}
//will exit the program
void RBapp::processQuit(){
    exit(0);
}
