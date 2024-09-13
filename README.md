# MomoFSM
一个简单的有限状态机，实现简单，上手简单，移植也很简单，可方便的在各平台运行（包括嵌入式平台，都用有限状态机了，裸机实现一个内存管理也很合理对吧），C++17及以上。

设计思路是，状态的转换只与发生的事件有关，至于当前状态的任务，就取决于使用者的思路了（把FSM嵌入到线程指示线程工作，或者干脆在entry之后执行操作）

## 文件导入
所有用到的文件只有一个头文件和一个源文件，所以导入项目可以简单粗暴，下载，然后像其他文件正常编入项目。
MomoFSM在设计开始就尽量避免使用STL和其他库文件，目前只导入了cstring和cassert，在保证C++17及以上版本时应当是不存在其他编译问题的。

## 使用
### 步骤一、继承MomoState状态
实现void entry(MomoFSM &fsm);和void exit(MomoFSM &fsm)函数, 例如:
```C++
class A:public MomoState{
    void entry(MomoFSM &fsm) override{
        cout<<"A_entry"<<endl;
    }
    void exit(MomoFSM &fsm) override{
        cout<<"A_exit"<<endl;
    }
};
```
需要伴随状态定义其他变量的时候，继承MomoFSM类，定义在新的类中，在MomoState中使用变量将引用转换成你定义的类就好啦。
### 步骤二、定义枚举
定义枚举的目的主要是方便管理，名称随意，需要有两个枚举类型（信号，状态）
```C++
enum State{AState,BState};
enum Single{test,aa,bb,cc,abaaba};
```
### 步骤三、添加状态
实例化一个MomoFSM（或者继承该类的对象），调用AddState函数就好啦
```C++
MomoFSM fsm;
fsm.AddState(new A,AState,Relation{.event = test,.stateName = BState}
    ,Relation{.event = aa,.stateName = AState});
```
1. 将MomoState交给fsm托管，不需要手动移除内存，如果有自己属性需要申请内存，请写好析构函数。
2. Relation{.event = aa,.stateName = AState}定义的是转换关系，可以同时定义多个，示例中只用了两个。
这里用到了C++17和11的一些特性，需要更低版本的支持就自行修改吧，也不难。
### 步骤四、运行
设置初始状态，然后在合适的时候发送事件就可以啦
```C++
fsm.setStartState(AState);
fsm.sendEvent(test);
```
初始状态是不会运行entry函数的。
## 多线程中不同状态切换任务
fsm定义在线程类里，实现MomoState中的task函数，在循环中始终运行fsm.curState->task(fsm);