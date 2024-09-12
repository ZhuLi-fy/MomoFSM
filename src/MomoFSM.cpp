//
// Created by zhuli on 24-9-12.
//

#include "MomoFSM.h"

using namespace momo;

State MomoState::AddRelation(Relation relation) {
    if(usedSize>=size){
        int *temp = new int[size+increment];
        assert(temp != nullptr);
        memcpy(temp,singleList,size);
        delete[] singleList;
        singleList = temp;

        temp = new int[size+increment];
        assert(temp != nullptr);
        memcpy(temp,stateList,size);
        delete[] stateList;
        stateList = temp;
        size+=increment;
    }
    singleList[usedSize] = relation.single;
    stateList[usedSize] = relation.stateName;
    usedSize++;
    return OK;
}

int *MomoState::findSingleReturnState(int single) {
    for (int i = 0; i < usedSize; ++i) {
        if(singleList[i]==single)
            return stateList+i;
    }
    return nullptr;
}

MomoState::~MomoState() {
    delete[] singleList;
    delete[] stateList;
    singleList = nullptr;
    stateList = nullptr;
}


State MomoFSM::setStartState(int state) {
    for (int i = 0; i < usedSize; ++i) {
        if (stateNameMap[i] == state){
            curState = stateList[i];
            return OK;
        }
    }
    return ERROR_NOTFINDSTATE;
}

State MomoFSM::sendSingle(int single) {
    int* temp = curState->findSingleReturnState(single);
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
