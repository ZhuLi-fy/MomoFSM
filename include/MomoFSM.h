//
// Created by zhuli on 24-9-12.
//

#ifndef MOMOFSM_MOMOFSM_H
#define MOMOFSM_MOMOFSM_H
#include <cassert>
#include <cstring>

namespace momo {
    static int increment = 10;
    enum State{OK,ERROR_NOTFINDSINGLE,ERROR_NOTFINDSTATE,ERROR_MALLOC,ERROR_EXISTSTATE};
    typedef struct {int single;int stateName;}Relation;

    class MomoState;
    class MomoFSM {
    protected:
        MomoState* curState = nullptr;
        MomoState** stateList = nullptr;
        int* stateNameMap = nullptr;
        int usedSize = 0;
        int size = 0;
    public:
        [[nodiscard]] int currentState() const{if(curState) return 0;}

        template<typename ... Args>
        State AddState(MomoState* state,int name,Args ... args){
            if(usedSize>=size){
                for (int i = 0; i < usedSize; ++i) {
                    if(stateNameMap[i]==name)
                        return ERROR_EXISTSTATE;
                }

                auto temp = new MomoState*[size+increment];
                assert(temp != nullptr);
                memcpy(temp,stateList,size);
                delete[] stateList;
                stateList = temp;

                int* temp1 = new int[size+increment];
                assert(temp1 != nullptr);
                memcpy(temp1,stateNameMap,size);
                delete[] stateNameMap;
                stateNameMap = temp1;
                size+=increment;
            }

            ((state->AddRelation(args))|...);
            stateNameMap[usedSize] = name;
            stateList[usedSize] = state;
            usedSize++;

            return OK;
        }
        State setStartState(int state);
        State sendSingle(int single);
        ~MomoFSM();
    };

    class MomoState{
    protected:
        int StateName;
        int *singleList = nullptr;
        int *stateList = nullptr;
        int usedSize = 0;
        int size = 0;
    public:
        virtual void entry(MomoFSM& fsm){};
        virtual void exit(MomoFSM& fsm){};
        int getStateName(){return StateName;}
        State AddRelation(Relation relation);
        int* findSingleReturnState(int single);
        ~MomoState();
    };
}

#endif //MOMOFSM_MOMOFSM_H
