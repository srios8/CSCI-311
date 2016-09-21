#include "table.h"
/*
 Sean McDonald
 the implementation of table.h it has a constructor and destructor
*/
Table::Table(){
   this->tableID=nullptr;
   this->numSeats=0;
   this->serverName=nullptr;
}
   //constructor
   Table::Table(const string& tableID, int numSeats, const string& serverName){
      std::string* temp= new string(tableID); 
      std::string* servertemp= new string(serverName);
      this->tableID=temp;
      this->numSeats=numSeats;
      this->serverName=servertemp;
   }
   //@param takes a party pointer and will set the time required and make a new party
   void Table::seatParty(const Party* newParty){
      party= newParty;
      setTimer(party->getTimeRequired());
   }
   //deconstructor
   Table::~Table(){
      delete tableID;
     // delete numSeats;
      delete serverName;
   }




   
