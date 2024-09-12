//
// Created by zhuli on 24-9-12.
//
#include "MomoFSM.h"
#include<iostream>

using namespace momo;
using namespace std;

class A:public MomoState{
    void entry(MomoFSM &fsm) override{
        cout<<"A_entry"<<endl;
    }
    void exit(MomoFSM &fsm) override{
        cout<<"A_exit"<<endl;
    }
};
class B:public MomoState{
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
    fsm.AddState(new A,AState,Relation{.single = test,.stateName = BState},
                 Relation{.single = aa,.stateName = AState});
    fsm.AddState(new B,BState,Relation{.single = test,.stateName = AState},
                 Relation{.single = bb,.stateName = AState},
                 Relation{.single = cc,.stateName = BState});
    fsm.setStartState(AState);
    fsm.sendSingle(test);
    fsm.sendSingle(cc);
    fsm.sendSingle(aa);
    fsm.sendSingle(test);
    return 1;
}
