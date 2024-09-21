//
// Created by zhuli on 24-9-12.
//
#include "MomoFSM.h"
#include<iostream>

using namespace momo;
using namespace std;

class A:public MomoState{
    using MomoState::MomoState;
    void entry(MomoFSM &fsm) override{
        cout<<"A_entry"<<endl;
    }
    void exit(MomoFSM &fsm) override{
        cout<<"A_exit"<<endl;
    }
};
class B:public MomoState{
    using MomoState::MomoState;
    void entry(MomoFSM &fsm) override{
        cout<<"B_entry"<<endl;
    }
    void exit(MomoFSM &fsm) override{
        cout<<"B_exit"<<endl;
    }
};
enum State{AState,BState};
enum Single{test,aa,bb,cc};

int main(){
    MomoFSM fsm;
    fsm.AddState(new A(AState),Relation{.event = test,.stateName = BState},
                 Relation{.event = aa,.stateName = AState});
    fsm.AddState(new B(BState),Relation{.event = test,.stateName = AState},
                 Relation{.event = bb,.stateName = AState},
                 Relation{.event = cc,.stateName = BState});
    fsm.setStartState(AState);
    fsm.sendEvent(test);
    fsm.sendEvent(cc);
    fsm.sendEvent(aa);
    fsm.sendEvent(test);
    int stateNum = 5;
    string stateName[stateNum];
    stateName[0]="First";
    stateName[1]="Second";
    string eventName[stateNum];
    eventName[0]="test";
    eventName[1]="aa";
    eventName[2]="bb";
    eventName[3]="cc";

    cout<<fsm.FSMTomdStr(stateName,stateNum,eventName,stateNum);
    return 1;
}
