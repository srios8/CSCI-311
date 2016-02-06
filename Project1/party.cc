#include "party.h"
   Party::Party(){
      this->reservationName=nullptr;
      this->numDiners=0;
      this->timeRequired=0;
   }

   Party::Party(const string& reservationName, int numDiners, int timeRequired){
      std::string* temp= new string(reservationName);
      this->reservationName=temp; 
      this->numDiners=numDiners;
      this->timeRequired=timeRequired;
   }
   
   Party::~Party(){}
   
   