//
// Created by zhuli on 24-9-12.
//

#include "MomoFSM.h"

using namespace momo;

State MomoState::AddRelation(Relation relation) {
    if(usedSize>=size){
        int *temp = new int[size+increment];
        assert(temp != nullptr);
        memcpy(temp,eventList,size);
        delete[] eventList;
        eventList = temp;

        temp = new int[size+increment];
        assert(temp != nullptr);
        memcpy(temp,stateList,size);
        delete[] stateList;
        stateList = temp;
        size+=increment;
    }
    eventList[usedSize] = relation.event;
    stateList[usedSize] = relation.stateName;
    usedSize++;
    return OK;
}

int *MomoState::findEventReturnState(int event) {
    for (int i = 0; i < usedSize; ++i) {
        if(eventList[i]==event)
            return stateList+i;
    }
    return nullptr;
}

MomoState::~MomoState() {
    delete[] eventList;
    delete[] stateList;
    eventList = nullptr;
    stateList = nullptr;
}

using namespace std;
string MomoState::eventToStr(int statesNum, string* events, int eventsNum) {
    string temp;
    for (int i = 0; i < usedSize; ++i) {
        assert(eventList[i] <= eventsNum);
        assert(stateList[i] <= statesNum);
        temp.append(to_string(getStateName())+"-->"+ to_string(stateList[i])+":"+events[i]+'\n');
    }

    return temp;
}


State MomoFSM::setStartState(int state) {
    for (int i = 0; i < usedSize; ++i) {
        if (stateNameMap[i] == state){
            curState = stateList[i];
            startState = stateList[i];
            return OK;
        }
    }
    return ERROR_NOTFINDSTATE;
}

State MomoFSM::sendEvent(int event) {
    int* temp = curState->findEventReturnState(event);
    if(temp == nullptr)
        return ERROR_NOTFINDSINGLE;
    int aimStateName = *temp;
    MomoState* aim;
    for (int i = 0; i < usedSize; ++i) {
        if(stateNameMap[i]==aimStateName)
            aim = stateList[i];
    }
    curState->exit(*this);
    aim->entry(*this);
    curState = aim;
    return OK;
}

MomoFSM::~MomoFSM() {
    for (int i = 0; i < usedSize; ++i) {
        delete stateList[i];
    }
    delete[] stateList;
    delete[] stateNameMap;
    curState = nullptr;
    stateList = nullptr;
    stateNameMap = nullptr;
}

int MomoFSM::currentState() {
    if(curState!= nullptr)
        return curState->getStateName();
    return 0;
}

string MomoFSM::FSMTomdStr(string *states, int statesNum, string *events, int eventNum) {
    string temp = "```mermaid\nstateDiagram-v2\n";
    assert(startState != nullptr);
    assert(stateList != nullptr);
    assert(stateNameMap != nullptr);
    assert(usedSize <= statesNum);
    for (int i = 0; i < usedSize; ++i) {
        temp.append(to_string(i)+":"+states[i]+'\n');
    }

    temp.append("[*]-->"+to_string(startState->getStateName())+'\n');

    for (int i = 0; i < usedSize; ++i) {
        temp.append(stateList[i]->eventToStr(statesNum,events,eventNum));
    }

    temp.append("```");
    return temp;
}
