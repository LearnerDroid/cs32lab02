#ifndef DATAAQ_H
#define DATAAQ_H
#include "demogData.h"
#include "stateDemog.h"

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <memory>

using namespace std;
class dataAQ {
  public:
    dataAQ() {

    }
    void createStateData(std::vector< shared_ptr<demogData> > theData){
      string state = "";
      for( shared_ptr<demogData> county: theData) {
        state = county->getState();
        //if true, key is not found
        if(states.count(state) == 0){
          states.insert(make_pair(state, make_shared<stateDemog>(state)));
        }
        states.at(state)->addCounty(county);
      }
      //now to calculate all the values with the inputted data
      for(map<string, shared_ptr<stateDemog>>::iterator i = states.begin(); i != states.end(); ++i ){
        i->second->calculate();
      }
    }
    //return the name of the state with the largest PROPORTION population under age 5, answer is UT
    string youngestPop() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = states.begin(); i != states.end(); i++ ){
        pop = i->second->getpopUnder5();
        //cout << i->second->getName() << "       " << pop << endl;
        if(pop > largestPop){
          //cout << i->second->getName() << endl;
          largestPop = pop;
          state = i->first;
        }
        /*
        if((i->first).compare("UT") == 0){
          cout << i->second->getName() << " " << (i->second->getpopUnder5() / i->second->getTotalPop()) 
            << " " << i->second->getBAup() << endl;
        }
        */
      }
      return state;
    }
    //return the name of the state with the largest population under age 18
    string teenPop() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = states.begin(); i != states.end(); i++ ){
        pop = i->second->getpopUnder18();
        if(pop > largestPop){
          //cout << i->second->getName() << "       " << pop << endl;
          largestPop = pop;
          state = i->first;
        }
      }
      return state;
    }
    //return the name of the state with the largest population over age 65
    string wisePop() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = states.begin(); i != states.end(); i++ ){
        pop = i->second->getpopOver65();
        //cout << i->second->getName() << "       " << pop << endl;
        if(pop > largestPop){
          //cout << i->second->getName() << endl;
          largestPop = pop;
          state = i->first;
        }
      }
      return state;
    }
    //return the name of the state with the largest population who did not finish high school
    string underServeHS() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = states.begin(); i != states.end(); i++ ){
        pop = 100 - i->second->getHSup();
        //cout << i->second->getName() << "       " << pop << endl;
        if(pop > largestPop){
          //cout << i->second->getName() << "   inside     " << pop << endl;
          largestPop = pop;
          state = i->first;
        }
      }
      return state;
    }
    //return the name of the state with the largest population who completed college, answer is DC
    string collegeGrads() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = states.begin(); i != states.end(); i++ ){
        pop = i->second->getBAup();
        //cout << i->second->getName() << "       " << pop << endl;
        if(pop > largestPop){
          //cout << i->second->getName() << "   inside     " << pop << endl;
          largestPop = pop;
          state = i->first;
          //cout << state << " " << largestPop << endl;
        }
        /*
        if((i->first).compare("DC") == 0){
          cout << i->second->getName() << " " << (i->second->getpopUnder5() / i->second->getTotalPop()) 
            << " " << i->second->getBAup() << endl;
        }
        */
      }
      //cout << "Test Failed: 'Testing state data aggregation query...\nPASSED: youngestPop\nPASSED: bachelors\nPASSED: teenPop\nPASSED: wisePop\nPASSED: underServeHS' != 'Testing state data aggregation query...\n   FAILED: youngestPop\n     Expected: UT Actual: SD\nPASSED: bachelors\n   FAILED: teenPop\n     Expected: UT Actual: SD\n   FAILED: wisePop\n     Expected: FL Actual: SD\n   FAILED: underServeHS\n     Expected: CA Actual:" << endl;
      return state;
    }
    map<string, shared_ptr<stateDemog>> states;
 };
 #endif