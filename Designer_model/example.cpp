#include "stdfx.h"
#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <mutex>
#include <vector>
using namespace std;



namespace funtemplate{
    class test{
        public:
            test(){}
            int run(int argc,char** argv);
        private:
        protected:
    };
    template <typename T>
    const T& Max(const T& a,const T& b){
        return a > b ? a : b;
    }
    int test::run(int argc,char** argv){
        int i = 30;
        int j = 20;
        cout << "max(30,20):" << Max(i,j) << endl;

        double f1 = 13.5;
        double f2 = 20.7;
        cout << "max(13.5,20.7)" << Max(f1,f2) << endl;

        string s1 = "hello";
        string s2 = "arvinn";
        cout << "max(s1,s2)" << Max(s1,s2) << endl;
        return 0;
    }
}
namespace Mutex{
    DWORD WINAPI Fun1Proc(LPVOID param);
    DWORD WINAPI Fun2Proc(LPVOID param);
    int idx = 0;
    int ticks = 100;
    HANDLE hMutex;

    
    class test{
        public:
            test(){}
            int run(int argc,char** argv);
        private:
        protected:
    };
    int test::run(int argc,char** argv){
        HANDLE hThread1 = CreateThread(NULL,0,Fun1Proc,NULL,0,NULL);
        HANDLE hThread2 = CreateThread(NULL,0,Fun2Proc,NULL,0,NULL);
        CloseHandle(hThread1);
        CloseHandle(hThread2);
        hMutex = CreateMutex(NULL,TRUE,"ticks");
        if(hMutex){
            if(ERROR_ALREADY_EXISTS==GetLastError()){
                cout << "only one instance can run" << endl;
                return 0;
            }
        }
        WaitForSingleObject(hMutex,INFINITE);
     
        ReleaseMutex(hMutex);
        ReleaseMutex(hMutex);
        Sleep(4000);
    }
    DWORD WINAPI Fun1Proc(LPVOID param){
        while(1){
            // WaitForSingleObject(hMutex,INFINITE);
            if(ticks>0){
                Sleep(1);
                cout << "Thread1 sell ticket:" << ticks-- << endl;
            }else{
                break;
            }
            ReleaseMutex(hMutex);
        }
        WaitForSingleObject(hMutex,INFINITE);
        cout << "thread1 is end running" << endl;
        return 0;
    }
    DWORD WINAPI Fun2Proc(LPVOID param){
        while(1){
            WaitForSingleObject(hMutex,INFINITE);
            if(ticks>0){
                Sleep(1);
                cout << "Thread2 sell ticket:" << ticks-- << endl;
            }else{
                break;
            }
            ReleaseMutex(hMutex);
        }
        WaitForSingleObject(hMutex,INFINITE);
        cout << "thread2 is end running" << endl;
        return 0;
    }
}

namespace Auto_ptr{
    class Base1{
        public:
            Base1(){}
            bool dd;
            int m_itest;
            virtual void func(){
                cout << __FUNCTION__ << endl;
            }
            ~Base1(){
                cout << "ptr:" << this << endl;
                cout << __FUNCTION__ << endl;
            }
            void showPtr(){
                cout << "ptr:" << this << endl;                
            }
        private:    
        protected:
    };
    class test{
        public:
            test(){}
            void run();
        private:
        protected:
    };
    void test::run(){
        shared_ptr<Base1> shptr = make_shared<Base1>();
        cout << shptr.use_count() << endl;

        weak_ptr<Base1> wptr(shptr);
        cout << wptr.use_count() << endl;

        // if(!wptr.expired()){
        //     shared_ptr<Base1> shptr2 = wptr.lock();
            
        // }


        
       
        
    }
}

namespace tmp{
    // template <class T>
    // // class MyArray{clear
    // //     public:
    // //         MyArray(){}
            
    // //     private:
    // //         T* pAddr;
    // //         int mSize;
    // //     protected:
    // // };

    // template T
    class Base1{
        public:
            Base1(){}
             template<typename T>
            virtual T fun()=0;
        private:
        protected:
    };
    class Base2:public Base1{
        public:
            Base2(){}
            virtual template<typename T>
            T fun(){

            }
        private:
        protected:
    };
    vector <int> fun(vector <int> a){
        for(int i=0;i<a.size();i++){
            cout << "a[" << i << "]" << a[i] << endl;
        }
        return a;
    }
    void run(){
        vector <int> a ;
        a.push_back(2);
        a.push_back(5);
        a.push_back(6);
        vector <int> b = fun(a);
        // fun(b);

    }
}
int main(int argc,char* argv[]){
    // tmp::test t;
    // t.run();
    tmp::run();
    return 0;
}


    #include <iostream>  
    #include <vector>  
    using namespace std;  
      
    template<class Item>  
    class Iterator  
    {  
    public:  
        virtual void first()=0;  
        virtual void next()=0;  
        virtual Item* currentItem()=0;  
        virtual bool isDone()=0;  
        virtual ~Iterator(){}  
    };  
      
    template<class Item>  
    class ConcreteAggregate;  
      
    template<class Item>  
    class ConcreteIterator : public Iterator <Item>  
    {  
        ConcreteAggregate<Item> * aggr;  
        int cur;  
    public:  
        ConcreteIterator(ConcreteAggregate<Item>*a):aggr(a),cur(0){}  
        virtual void first()  
        {  
            cur=0;  
        }  
        virtual void next()  
        {  
            if(cur<aggr->getLen())  
                cur++;  
        }  
        virtual Item* currentItem()  
        {  
            if(cur<aggr->getLen())  
                return &(*aggr)[cur];  
            else  
                return NULL;  
        }  
        virtual bool isDone()  
        {  
            return (cur>=aggr->getLen());  
        }  
    };  
      
    template<class Item>  
    class Aggregate  
    {  
    public:  
        virtual Iterator<Item>* createIterator()=0;  
        virtual ~Aggregate(){}  
    };  
      
    template<class Item>  
    class ConcreteAggregate:public Aggregate<Item>  
    {  
        vector<Item >data;  
    public:  
        ConcreteAggregate()  
        {  
            data.push_back(1);  
            data.push_back(2);  
            data.push_back(3);  
        }  
        virtual Iterator<Item>* createIterator()  
        {  
            return new ConcreteIterator<Item>(this);  
        }  
        Item& operator[](int index)  
        {  
            return data[index];  
        }  
        int getLen()  
        {  
            return data.size();  
        }  
    };  
      
    int main()  
    {  
        Aggregate<int> * aggr =new ConcreteAggregate<int>();  
        Iterator<int> *it=aggr->createIterator();  
      
        for(it->first();!it->isDone();it->next())  
        {  
            cout<<*(it->currentItem())<<endl;  
        }  
        delete it;  
        delete aggr;  
        return 0;  
    }  