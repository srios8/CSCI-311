#include "table.h"

Table::Table(){
   this->tableID=nullptr;
   this->numSeats=0;
   this->serverName=nullptr;
}
   
   Table::Table(const string& tableID, int numSeats, const string& serverName){
      std::string* temp= new string(tableID); 
      std::string* servertemp= new string(serverName);
      this->tableID=temp;
      this->numSeats=numSeats;
      this->serverName=servertemp;
   }

   
   Table::~Table(){}


   