#include "party.h"
/*
Written by Sean McDonald
the implementation of part.h with constructors. 
*/

   Party::Party(){
      this->reservationName=nullptr;
      this->numDiners=0;
      this->timeRequired=0;
   }
   //constructor
   Party::Party(const string& reservationName, int numDiners, int timeRequired){
      std::string* temp= new string(reservationName);
      this->reservationName=temp; 
      this->numDiners=numDiners;
      this->timeRequired=timeRequired;
   }
   //deconstructor
   Party::~Party(){}
   
   
