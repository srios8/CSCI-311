#include "restaurant.h"
#include <iostream>

      //std::map<string,int> m_map;
      //m_map["name_1"]=0;
   int main() {
      Restaurant mydiner;
   }
   
   void Restaurant::getInput() {
      std::string type;
      std::string table_num;
      int table_size;
      std::string server_name;
      
      int party_size;
      string reseration_name;
      int time_needed;
      
      std::cin>>type;
      if(type=="table") {
         std::cin>>table_num;
         std::cin>>table_size;
         std::cin>>server_name;
         
         
      }
      else if(type=="party"){
         std::cin>>party_size;
         std::cin>>reseration_name;
         std::cin>>time_needed;
         Party temp = Party(reseration_name,party_size,time_needed);
         waiting.append(&temp);
         
      }
   }
      
      void Restaurant::serveParties(){
         
      }