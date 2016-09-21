#include "restaurant.h"
#include <iostream>
/*
written by Sean McDonald
in this file you manipulate between the linked lists and seat parties while the restaurant is open. the restaurant closes when there is no more waiting parties and there are no occupied tables
*/
  //is a void function that will get all the file input 
   void Restaurant::getInput() {
      std::string type;
      std::string table_num;
      int table_size;
      std::string server_name;
      
      int party_size;
      string reseration_name;
      int time_needed;
      while(std::cin >>type && type!="end" ){
      if(type=="table") {
         std::cin>>table_num;
         std::cin>>table_size;
         std::cin>>server_name;
         Table* temp = new Table(table_num,table_size,server_name);
         available.append(temp);  
      }
      else if(type=="party"){
         std::cin>>party_size;
         std::cin>>reseration_name;
         std::cin>>time_needed;
         Party* temp = new Party(reseration_name,party_size,time_needed);
         waiting.append(temp);
      }
      }
   }
      //will used the saved input and sort the parties into tables when 
      //available and with let them leave when they are done.
      void Restaurant::serveParties(){
         Table* available_table=available.first();
         Table* occupied_table= occupied.first();
         Party* waiting_diners= waiting.first();
         bool workplease=false;
         bool flag= false;
         
         
         //when the function still has diners waiting or people sitting
         while (flag==false){
         if(occupied.empty() && waiting.empty()) {
         flag=true;
         }        
         available_table=available.first();
         occupied_table=occupied.first();
         waiting_diners=waiting.first();
             while(occupied_table!=nullptr){
                 if (occupied_table->getTimer()!=0){
                       occupied_table->decrementTimer();     
                    }
                 if(occupied_table->getTimer()==0){
                 std::cout<<*(occupied_table->getParty()->getReservationName());
                 std::cout<<" finished at "<<*(occupied_table->getTableID());
                 std::cout<<"\n";
                  occupied_table->clearTable();
                  available.append(occupied_table);
                  occupied_table=occupied.remove();
                  workplease=true;
                  }
                  occupied_table=occupied.next();
                  
                  if(workplease==true && occupied_table==nullptr ){
                 available_table=available.first();
                 break; 
                 }
                 else if (occupied_table==nullptr){
                    occupied_table=occupied.first();
                    break;
                 }
                 if(occupied.empty() && waiting.empty()){
                    flag=true;
                 }
                 if(occupied.empty()==true) {
                 break;
                 }

                }
                //while there are still available tables
            while(available_table!=nullptr&&waiting_diners!=nullptr)
            {
             if(available_table->getNumSeats()>=waiting_diners->getNumDiners()){         
                  std::cout<<*(waiting_diners->getReservationName());
                  std::cout<<" seated at ";
                  std::cout<<*(available_table->getTableID())<<"\n";
                  available_table->seatParty(waiting_diners);
      servers[*available_table->getServerName()]+=waiting_diners->getNumDiners();
                  occupied.append(available_table);
                  waiting_diners=waiting.remove();
                  available_table=available.remove();
                 
                  waiting_diners=waiting.first();
                  available_table=available.first();
              }
              else 
              {
                 available_table=available.next();
              }
               if(available_table==nullptr&&waiting_diners!=nullptr){
                 available_table=available.first();
                 waiting_diners=waiting.next();
              }
              //checks to see if the restaurant can be closed
             // if (occupied.empty() &&waiting.empty() ){
               // flag=true;
               // break;
              // }       
//map<string,int>::iterator iter;
//for (iter=servers.begin();iter<servers.end();iter++){
//std::cout<<*(iter).first<< *(iter).second;
//}
  }     
  }
  for ( std::map<string,int>::iterator a=servers.begin();a!=servers.end();a++)
  {
     std::cout<<a->first <<" served "<< a->second<< "\n";
  }
  }
   int main(){

      Restaurant myDiner;
      myDiner.getInput();
      myDiner.serveParties();
      return 0;
   }
