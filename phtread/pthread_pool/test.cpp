#include "thread_pool.h"
#include <cstdio>
#include <iostream>
#include <unistd.h>

using namespace std;

class CMyTask:public CTask{
    public:
       //:wq
       //cMyTask() = default;
        int Run(){
            printf("%s\n",(char*)m_ptrData);
            int x = rand() % 4 +1;
            sleep(x);
            return 0;
        }

        ~CMyTask(){}
};

int main(){

    CMyTask taskObj;
    char szTmp[] = "hello!.";
    taskObj.setData((void*)szTmp);
    CThreadPool threadpool(5);//创建线程池大小为5；

    for(int i = 0 ;i < 10 ;i++){
        threadpool.AddTask(&taskObj);
    }

    while(1){
        printf("there are still %d tasks need to handle\n",threadpool.getTaskSize());

        //任务没有任务；
        if(threadpool.getTaskSize() == 0 ){
            //清除线程池；
            if( threadpool.StopAll() == -1){
                printf("Thread pool clear,exit.\n");
                exit(0);
            }
        }
        sleep(2);
        printf("2 seconds later .....\n");
    }
    return 0;
}
