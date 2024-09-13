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
    typedef struct {int event;int stateName;}Relation;

    class MomoFSM;
    class MomoState{
    protected:
        int StateName;
        int *singleList = nullptr;
        int *stateList = nullptr;
        int usedSize = 0;
        int size = 0;
    public:
        /// 进入状态
        /// \param fsm
        virtual void entry(MomoFSM& fsm){};
        /// 退出状态
        /// \param fsm
        virtual void exit(MomoFSM& fsm){};
        /// 方便拓展预留的运行函数
        /// \param fsm
        virtual void task(MomoFSM& fsm){};

        int getStateName() const{return StateName;}
        /// 添加转换关系
        /// \param relation
        /// \return
        State AddRelation(Relation relation);
        int* findSingleReturnState(int event);
        ~MomoState();
    };

    class MomoFSM {
    protected:
        MomoState* curState = nullptr;
        MomoState** stateList = nullptr;
        int* stateNameMap = nullptr;
        int usedSize = 0;
        int size = 0;
    public:
        /// 返回当前状态
        /// \return
        int currentState();

        /// 为状态机添加状态
        /// \tparam Args
        /// \param state 状态对象
        /// \param name 状态名称
        /// \param args 可变数量的转换关系，请使用Relation结构体
        /// \return
        template<typename ... Args>
        State AddState(MomoState* state,int name,Args ... args){
            for (int i = 0; i < usedSize; ++i) {
                if(stateNameMap[i]==name)
                    return ERROR_EXISTSTATE;
            }
            if(usedSize>=size){
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
        /// 设置开始状态
        /// \param state
        /// \return
        State setStartState(int state);
        /// 发送事件
        /// \param event
        /// \return
        State sendEvent(int event);
        ~MomoFSM();
    };

}

#endif //MOMOFSM_MOMOFSM_H
