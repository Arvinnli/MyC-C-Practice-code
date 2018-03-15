#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include "../stdfx.h"


using namespace std;
//chinese : GBK
int arg_count;
char** arg_arr;

namespace music_8bit{
    /*返回数字简谱中数字t所对应的频率*/
    int notation_frequency(int t)
    {
        switch (t)
        {
        /*中音部分:1,2,3,4,5,6,7*/
        case 1:
            return 523;
        case 2:
            return 587;
        case 3:
            return 659;
        case 4:
            return 698;
        case 5:
            return 784;
        case 6:
            return 880;
        case 7:
            return 988;
        /*低音部分:-1,-2,-3,-4,-5,-6,-7*/
        case -1:
            return 262;
        case -2:
            return 294;
        case -3:
            return 330;
        case -4:
            return 349;
        case -5:
            return 392;
        case -6:
            return 440;
        case -7:
            return 494;
        /*高音部分:11,12,13,14,15,16,17*/
        case 11:
            return 1047;
        case 12:
            return 1175;
        case 13:
            return 1319;
        case 14:
            return 1397;
        case 15:
            return 1568;
        case 16:
            return 1760;
        case 17:
            return 1976;
        /*安静:0,不合法数值*/
        default:
            return 0;
        }
    }

    /*演奏《小星星》*/
    void play_xiaoxingxing(void)
    {
        int i;
        int _xiaoxingxing[48] = {1, 1, 5, 5, 6, 6, 5, 0,
                                4, 4, 3, 3, 2, 2, 1, 0,
                                5, 5, 4, 4, 3, 3, 2, 0,
                                5, 5, 4, 4, 3, 3, 2, 0,
                                1, 1, 5, 5, 6, 6, 5, 0,
                                4, 4, 3, 3, 2, 2, 1, 0}; //小星星乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《小星星》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 47; i++)
        {
            if (_xiaoxingxing[i] == 0)
                printf("\n");
            else
                printf("%d", _xiaoxingxing[i]);
            Beep(notation_frequency(_xiaoxingxing[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }

    /*演奏《茉莉花》*/
    void play_molihua(void)
    {
        int i, t;
        int _molihua[72] = {3, 3, 5, 6, 11, 11, 6, 5, 0,
                            5, 6, 5, 0,
                            3, 3, 5, 6, 11, 11, 6, 5, 0,
                            5, 6, 5, 0,
                            5, 5, 5, 3, 5, 6, 0,
                            6, 6, 5, 0,
                            3, 2, 3, 5, 0,
                            3, 2, 1, 0,
                            1, 2, 1, 0,
                            3, 2, 1, 2, 0,
                            3, 5, 6, 11, 6, 5, 0,
                            5, 2, 3, 5, 3, 2, 1, 2, 1, 0}; //茉莉花乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《茉莉花》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 71; i++)
        {
            t = _molihua[i];
            if (t < 0)
                t = -t;
            t = t % 10;
            if (t == 0)
                printf("\n");
            else
                printf("%d", t);
            Beep(notation_frequency(_molihua[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }

    /*演奏《找朋友》*/
    void play_zhaopengyou(void)
    {
        int i, t;
        int _zhaopengyou[32] = {
            5,
            6,
            5,
            6,
            5,
            6,
            5,
            0,
            5,
            11,
            7,
            6,
            5,
            5,
            3,
            0,
            5,
            5,
            3,
            3,
            5,
            5,
            3,
            0,
            2,
            4,
            3,
            2,
            1,
            2,
            1,
            0,
        }; //找朋友乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《找朋友》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 31; i++)
        {
            t = _zhaopengyou[i];
            if (t < 0)
                t = -t;
            t = t % 10;
            if (t == 0)
                printf("\n");
            else
                printf("%d", t);
            Beep(notation_frequency(_zhaopengyou[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }

    /*演奏《上学歌》*/
    void play_shangxuege(void)
    {
        int i, t;
        int _shangxuege[30] = {1, 2, 3, 1, 5, 0,
                            6, 6, 11, 6, 5, 0,
                            6, 6, 11, 0,
                            5, 6, 3, 0,
                            6, 5, 3, 5, 3, 1, 2, 3, 1, 0}; //找朋友乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《上学歌》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 29; i++)
        {
            t = _shangxuege[i];
            if (t < 0)
                t = -t;
            t = t % 10;
            if (t == 0)
                printf("\n");
            else
                printf("%d", t);
            Beep(notation_frequency(_shangxuege[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }

    /*演奏《一分钱》*/
    void play_yifenqian(void)
    {
        int i, t;
        int _yifenqian[52] = {5, 11, 6, 11, 5, 0,
                            3, 5, 2, 3, 5, 0,
                            3, 5, 6, 11, 5, 6, 5, 3, 5, 1, 0,
                            3, 2, 0,
                            3, 2, 1, 2, 3, 0,
                            6, 5, 3, 5, 6, 0,
                            5, 11, 11, 6, 5, 6, 3, 0,
                            5, 2, 3, 2, 1, 0}; //找朋友乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《一分钱》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 51; i++)
        {
            t = _yifenqian[i];
            if (t < 0)
                t = -t;
            t = t % 10;
            if (t == 0)
                printf("\n");
            else
                printf("%d", t);
            Beep(notation_frequency(_yifenqian[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }

    /*演奏《征服》*/
    void play_zhengfu(void)
    {
        int i, t;
        int _zhengfu[33] = {
            5,
            11,
            7,
            5,
            5,
            6,
            5,
            0,
            5,
            11,
            7,
            5,
            6,
            3,
            6,
            0,
            6,
            6,
            6,
            5,
            3,
            3,
            4,
            0,
            4,
            4,
            4,
            5,
            6,
            3,
            2,
            2,
            0,
        }; //征服乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《征服》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 32; i++)
        {
            t = _zhengfu[i];
            if (t < 0)
                t = -t;
            t = t % 10;
            if (t == 0)
                printf("\n");
            else
                printf("%d", t);
            Beep(notation_frequency(_zhengfu[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }

    /*演奏《沧海一声笑》*/
    void play_canghaiyishengxiao(void)
    {
        int i, t;
        int _canghaiyishengxiao[31] = {12, 12, 1, 6, 5, 4, 0,
                                    6, 5, 4, 2, 1, 0,
                                    1, 2, 1, 2, 4, 4, 5, 6, 11, 0,
                                    12, 12, 11, 6, 5, 4, 5, 0}; //沧海一声笑乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《沧海一声笑》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 30; i++)
        {
            t = _canghaiyishengxiao[i];
            if (t < 0)
                t = -t;
            t = t % 10;
            if (t == 0)
                printf("\n");
            else
                printf("%d", t);
            Beep(notation_frequency(_canghaiyishengxiao[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }
    /*演奏《童话》*/
    void play_tonghua(void)
    {
        int i, t;
        int _tonghua[46] = {
            5,
            4,
            3,
            0,
            3,
            4,
            3,
            0,
            3,
            4,
            3,
            4,
            3,
            2,
            1,
            0,
            1,
            3,
            5,
            6,
            0,
            6,
            6,
            5,
            2,
            2,
            4,
            3,
            0,
            1,
            3,
            5,
            6,
            0,
            6,
            6,
            7,
            6,
            5,
            4,
            3,
            4,
            3,
            2,
            1,
            0,
        }; //童话乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《童话》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 45; i++)
        {
            t = _tonghua[i];
            if (t < 0)
                t = -t;
            t = t % 10;
            if (t == 0)
                printf("\n");
            else
                printf("%d", t);
            Beep(notation_frequency(_tonghua[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }
    /*演奏《同桌的你》*/
    void play_tongzhuodeni(void)
    {
        int i, t;
        int _tongzhuodeni[71] = {
            5,
            5,
            5,
            5,
            3,
            4,
            5,
            7,
            0,
            6,
            6,
            6,
            6,
            4,
            6,
            5,
            0,
            5,
            5,
            5,
            5,
            7,
            6,
            5,
            4,
            0,
            4,
            4,
            4,
            4,
            3,
            2,
            1,
            0,
            11,
            11,
            11,
            11,
            5,
            6,
            11,
            11,
            11,
            11,
            0,
            12,
            12,
            12,
            12,
            11,
            7,
            6,
            0,
            7,
            7,
            7,
            7,
            7,
            11,
            12,
            0,
            5,
            0,
            7,
            7,
            11,
            12,
            11,
            7,
            11,
            0,
        }; //同桌的你乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《同桌的你》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 70; i++)
        {
            t = _tongzhuodeni[i];
            if (t < 0)
                t = -t;
            t = t % 10;
            if (t == 0)
                printf("\n");
            else
                printf("%d", t);
            Beep(notation_frequency(_tongzhuodeni[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }
    /*演奏《小熊和洋娃娃》*/
    void play_xiaoxiongheyangwawa(void)
    {
        int i, t;
        int _xiaoxiongheyangwawa[77] = {
            1,
            0,
            2,
            3,
            4,
            5,
            5,
            5,
            4,
            3,
            4,
            4,
            4,
            3,
            2,
            1,
            3,
            5,
            1,
            0,
            2,
            3,
            4,
            5,
            5,
            5,
            4,
            3,
            4,
            4,
            4,
            3,
            2,
            1,
            3,
            1,
            6,
            0,
            6,
            6,
            5,
            4,
            5,
            5,
            5,
            4,
            3,
            4,
            4,
            4,
            3,
            2,
            1,
            3,
            5,
            6,
            0,
            6,
            6,
            5,
            4,
            5,
            5,
            5,
            4,
            3,
            4,
            0,
            4,
            4,
            3,
            2,
            1,
            0,
            3,
            1,
            0,
        }; //小熊和洋娃娃乐谱
        int notation_frequency(int t);
        printf("请欣赏乐曲《小熊和洋娃娃》……\n");
        Beep(0, 1000); //暂停一秒钟
        for (i = 0; i <= 76; i++)
        {
            t = _xiaoxiongheyangwawa[i];
            if (t < 0)
                t = -t;
            t = t % 10;
            if (t == 0)
                printf("\n");
            else
                printf("%d", t);
            Beep(notation_frequency(_xiaoxiongheyangwawa[i]), 1000);
        }
        printf("演奏完毕！谢谢欣赏！\n");
    }
    void run(){
        int choice;
        while(1){
            printf("请选择需要演奏的曲目：\n");
            printf("【1】《小星星》\n");
            printf("【2】《茉莉花》\n");
            printf("【3】《找朋友》\n");
            printf("【4】《上学歌》\n");
            printf("【5】《一分钱》\n");
            printf("【6】《征服》\n");
            printf("【7】《沧海一声笑》\n");
            printf("【8】《童话》\n");
            printf("【9】《同桌的你》\n");
            printf("【10】《小熊和洋娃娃》\n");
            printf("【0】退出程序\n");
            printf("\n");
            printf("请选择：");scanf("%d",&choice);
            switch(choice)
            {
                    case 1: play_xiaoxingxing(); break;
                    case 2: play_molihua();break;
                    case 3: play_zhaopengyou();break;
                    case 4: play_shangxuege();break;
                    case 5: play_yifenqian();break;
                    case 6: play_zhengfu();break;
                    case 7: play_canghaiyishengxiao();break;
                    case 8: play_tonghua();break;
                    case 9: play_tongzhuodeni();break;
                    case 10: play_xiaoxiongheyangwawa();break;
                    case 0: break;
                    default: printf("输入有误！请正确输入！\n");
            }
            Beep(0,1000);//暂停一秒钟
            printf("\n");
            if(choice==0)
            {
                    printf("\n谢谢使用，再见！");
                    Beep(0,1000);//暂停一秒钟
                    break;
            }
        }
    }
}
namespace character_weapon{
    struct WeaponBehavior{
        public:
            virtual void useWeapon(){}
        private:
        protected:
    };  
    struct Character{
        public:
            Character(){
                this->_wb = NULL;
            }
            virtual void fight(){
                if(this->_wb!=NULL){
                    this->_wb->useWeapon();
                }
            }
            WeaponBehavior* getWeaponBehavior(){
                return this->_wb;
            }
            void setWeaponBehavior(WeaponBehavior* w){
                this->_wb = w;
            }
        private:
            WeaponBehavior* _wb;
        protected:
    };

    struct SwordBehavior:public WeaponBehavior{
        public:
            virtual void useWeapon(){
                cout << "use the sword" << endl;
            }
        private:
        protected:
    };
    struct KnifeBehavior:public WeaponBehavior{
        public:
            virtual void useWeapon(){
                cout << "use the Knife" <<  endl;
            }
        private:
        protected:
    };  
    struct BowAndArrowBehavior:public WeaponBehavior{
        public:
            virtual void useWeapon(){
                cout << "use the BowAndArrow" <<  endl;
            }
        private:
        protected:
    };
    struct AxeBehavior:public WeaponBehavior{
        public:
            virtual void useWeapon(){
                cout << "use the Axe" <<  endl;
            }
        private:
        protected:
    };
    struct HammerBehavior:public WeaponBehavior{
        public:
            virtual void useWeapon(){
                cout << "use the hammer" <<  endl;
            }
        private:
        protected:
    };
    struct King:public Character{
        public:
            King(){
                try{
                    this->_weapon = new AxeBehavior;
                }catch(const bad_alloc& e){
                    cerr<<e.what()<<endl; 
                }
                Character::setWeaponBehavior(this->_weapon);
            }
            ~King(){
                if(this->_weapon!=NULL){
                    delete this->_weapon;
                }
            }
        private:
            WeaponBehavior* _weapon;
        protected:
    };
    struct Knight:public Character{
        public:
            Knight(){
                try{
                    this->_weapon = new SwordBehavior;
                }catch(const bad_alloc& e){
                    cerr<<e.what()<<endl; 
                }
                Character::setWeaponBehavior(this->_weapon);
            }
            ~Knight(){
                if(this->_weapon!=NULL)
                    delete this->_weapon;           
            }
        private:
            WeaponBehavior* _weapon;
        protected:
    };
    struct Queen:public Character{
        public:
            Queen(){
                try{
                    this->_weapon = new KnifeBehavior;
                }catch(const bad_alloc& e){
                    cerr<<e.what()<<endl; 
                }
                Character::setWeaponBehavior(this->_weapon);
            }
            ~Queen(){
                if(this->_weapon!=NULL)
                    delete this->_weapon;
            }
        private:
            WeaponBehavior* _weapon;
        protected:
    };
    struct Troll:public Character{
        public:
            Troll(){
                try{
                    this->_weapon = new BowAndArrowBehavior;
                }catch(const bad_alloc& e){
                    cerr<<e.what()<<endl; 
                }
                Character::setWeaponBehavior(this->_weapon);
            }
            ~Troll(){
                if(this->_weapon!=NULL)
                    delete this->_weapon;
            }
        private:
            WeaponBehavior* _weapon;
        protected:
    };
    struct Paladin:public Character{
        public:
            Paladin(){
                try{
                    this->_weapon = new HammerBehavior;
                }catch(const bad_alloc& e){
                    cerr<<e.what()<<endl; 
                }
                Character::setWeaponBehavior(this->_weapon);
            }
            ~Paladin(){
                if(this->_weapon!=NULL)
                    delete this->_weapon;
            }
        private:
            WeaponBehavior* _weapon;
        protected:
    };  
}
namespace StrategyParttern{//GBK    “策略模式”
    struct FlyBehavior{
        public:
            virtual void fly(){}
        private:
        protected:
    };
    struct QuackBehavior{
        public:
            virtual void quack(){}
        private:
        protected:
    };

    struct FlyRocketPowered:public FlyBehavior{
        public:
            FlyRocketPowered(){
                SCI_TRACE_LOW();
            }
            ~FlyRocketPowered(){
                SCI_TRACE_LOW();            
            }   
            virtual void fly(){
                cout << "Flying with a rocket" << endl;
            }
        private:
        protected:
    };



    struct FlyWithWings :public FlyBehavior{
        public:
            virtual void fly(){
                cout << "flying" << endl;
            }
        private:
    };

    struct FlyNoWay :public FlyBehavior{
        public:
            virtual void fly(){
                cout << "can not fly" << endl;
            }
        private:
        protected:
    };

    struct Quack:public QuackBehavior{
        public:
            virtual void quack(){
                cout << "quack" <<endl;
            }
        private:
    };

    struct MuteQuack:public QuackBehavior{
        public:
            virtual void quack(){
                cout << "squeak" <<endl;
            }
        private:
    };

    struct Duck:public FlyBehavior,public QuackBehavior{
        public:
            Duck(){
                SCI_TRACE_LOW();
                this->fly_behavior = NULL;
                this->quack_behavior = NULL;
            }
            
            virtual void display(){}
            virtual void performFly(){
                if(this->fly_behavior!=NULL)
                    fly_behavior->fly();
            }
            virtual void performQuack(){
                if(this->quack_behavior!=NULL)
                    quack_behavior->quack();
            }
            virtual void swim(){
                cout << " all ducks float, even decoys!" << endl;
            }
            void setFlyBehavior(FlyBehavior& fly){
                this->fly_behavior = &fly;
            }
            void setQuackBehavior(QuackBehavior& quack){
                this->quack_behavior = &quack;
            }
            FlyBehavior* getFlyBehavior(){
                return this->fly_behavior;
            }
            QuackBehavior* getQuackBehavior(){
                return this->quack_behavior;
            }
            
        private: 
            FlyBehavior* fly_behavior;
            QuackBehavior* quack_behavior;
        protected:
    };

    struct MallardDuck:public Duck{
        public:
            MallardDuck(){
                FlyWithWings fb ;
                Quack qb;
                Duck::setFlyBehavior(fb);
                Duck::setQuackBehavior(qb);    
            }
            virtual void display(){
                cout << " is a real mallard duck" << endl;
            }
        private:
    };

    struct ModelDuck:public Duck{
        public:
            ModelDuck(){
                
                
                try{
                    this->_fnw = new FlyNoWay();
                    this->_qak = new Quack();
                }catch(const bad_alloc& e){
                    cerr<<e.what()<<endl; 
                }

                Duck::setFlyBehavior(*(this->_fnw));
                Duck::setQuackBehavior(*(this->_qak));
            }
            virtual void display(){
                cout << "Is model duck0" <<endl;
            }
            ~ModelDuck(){
                SCI_TRACE_LOW();
                if(this->_fnw!=NULL)
                    delete this->_fnw;
                SCI_TRACE_LOW();
                if(this->_qak!=NULL)
                    delete this->_qak;
                
            }
        private:
            FlyNoWay* _fnw;
            Quack* _qak;
        protected:
    };

    struct DuckTest{
        void run(){
            Duck dd;
            ModelDuck md;
            FlyRocketPowered frp;
            Duck& dm = md;
            dm.performFly();
            dm.setFlyBehavior(frp);
            dm.performFly();
        }  
    };
}
namespace ObserverParttern{//GBK    “观察者模式”
    class Observer{
        public:
            virtual void update(float temperature,float humidity,float pressure)=0;
        private:
        protected:
    };
    class Subject{
        public:
            virtual void registerObserver(Observer* o)=0;
            virtual void removeObserver(Observer* o)=0;
            virtual void notifyObserver()=0;

            // virtual void setChanged(bool changed)=0;
            // virtual bool hasChanged()=0;
        private:
        protected:
    };//page 52  
    class DisplayElement{
        public:
            // DisplayElement(){}
            virtual void display()=0;
        private:
        protected:
    };
    class ArrayListBehavior{
        public:
            virtual int add(void* obj) = 0;
            virtual int remove(int idx) = 0;
            virtual int get(int idx,void** obj) = 0; 
            virtual int set(int idx,void* obj) = 0;
            virtual int show() = 0;
            virtual int getIdx(void* obj) = 0;
            virtual int getSize()=0;
        private:
        protected:
    };
    class ArrayListInt{
        public:
            ArrayListInt(){
                this->_lenth = 0;
            }
            int add(int data){
                if(this->_lenth==1024)
                    return -1;
                this->_buf[this->_lenth] = data;
                this->_lenth++;
                return 0;
            }
            void remove(int idx){
                int i,flag = 0;
                // this->_buf[idx] = 0;
                for(i=idx;i<this->_lenth;i++){
                    this->_buf[idx] = this->_buf[idx+1];
                    flag = 1;
                }
                if(flag)
                    this->_lenth--;
            }
            int get(int idx){
                return this->_buf[idx];
            }
            void set(int idx,int data){
                this->_buf[idx] = data;
            }
            void show(){
                int i ;
                for(i=0;i<this->_lenth;i++){
                    cout << "buf[" << i << "] : " << this->_buf[i] << endl;
                }
            }
        private:
            int _lenth;
            int _buf[1024];
        protected:
    };
    class ArraylistObserver:public ArrayListBehavior{
        public:
            ArraylistObserver(){}
            virtual int add(void* obj) {
                if(this->size==1024)
                    return -1;
                this->buf[this->size] = (Observer*)obj;
                this->size++;
                return 0;
            }
            virtual int remove(int idx) {
                if(idx<0||idx>1023){
                    return -1;
                }
                int i ;
                for(i=idx;i<this->size;i++){
                    this->buf[i] = this->buf[i+1];
                }
                this->size--;
                return 0;
            }
            virtual int get(int idx,void** obj) {
                if(idx<0||idx>1023){
                    return -1;
                }
                Observer** p = (Observer**)obj;
                *p = this->buf[idx];
                return 0;
            } 
            virtual int getIdx(void* obj) {
                int i ;
                for(i = 0;i<this->size;i++){
                    if(this->buf[i] == (Observer*)obj)
                        return i;
                }
                return -1;
            }
            virtual int set(int idx,void* obj) {
                if(idx<0||idx>this->size){
                    return -1;
                }
                this->buf[idx] = (Observer*)obj;
            }
            virtual int getSize(){
                return this->size;
            }
            virtual int show() {

                return 0;
            }


        private:
            Observer* buf[1024];
            int size;
        protected:
    };
    class CurrentConditionsDisplay:public Observer,public DisplayElement{
        public:
            CurrentConditionsDisplay(Subject* weatherData){
                this->weatherData = weatherData;
                weatherData->registerObserver(this);
            }
            virtual void update(float temperature,float humidity,float pressure){
                this->temperature = temperature;
                this->humidity = humidity;
                display();
            }
            void display(){
                cout << "Current coditions: ";
                cout << temperature << "F degrees and ";
                cout << humidity << "% humidity"<<endl;
            }
            
        private:
            float temperature;
            float humidity;
            Subject* weatherData;
        protected:
    };
    class ForecastDisplay:public Observer,public DisplayElement{
        public:
            ForecastDisplay(Subject* weatherData){
                this->weatherData = weatherData;
                weatherData->registerObserver(this);               
            }
            virtual void update(float temperature,float humidity,float pressure){
                this->pressure = pressure;
                display();
            }
            void display(){
                cout << "ForecastDisplay coditions: ";
                cout << pressure << "Pa  "<<endl;
            }
        private:
            Subject* weatherData;
            float pressure;
        protected:
    };
    class WeatherData:public Subject{
        public:
            WeatherData(){
                this->observers = new ArraylistObserver();
            }
            ~WeatherData(){
                if(this->observers!=NULL)
                    delete this->observers;
            }
            virtual void registerObserver(Observer* o){
                this->observers->add(o);
            }
            virtual void removeObserver(Observer* o){
                int i = observers->getIdx(o);
                if(i!=-1)
                    this->observers->remove(i);
            }
            virtual void notifyObserver(){
                for(int i=0;i<observers->getSize();i++){
                    Observer* observer = NULL;
                    this->observers->get(i,(void**)&observer);
                    observer->update(temperature,humidity,pressure);
                }
            }
            void measurementsChanged(){
                notifyObserver();
            }
            void setMeasurements(float temperature,float humidity,float pressure){
                this->temperature = temperature;
                this->humidity = humidity;
                this->pressure = pressure;
                measurementsChanged();              
            }

        private:
            ArraylistObserver* observers;
            float temperature;
            float humidity;
            float pressure;
        protected:
    };
    struct test{
        void run(){
            WeatherData weatherData;
            CurrentConditionsDisplay ccd = CurrentConditionsDisplay(&weatherData);
            ForecastDisplay fd = ForecastDisplay(&weatherData);

            weatherData.setMeasurements(80,65,60.4);
            weatherData.setMeasurements(82,70,29.2);
            weatherData.setMeasurements(70,90,29.2);
        }
    };
}
namespace DecoratorParttern{//Gbk   “装饰者模式”
    class Beverage{
        public:
            string _description;
            Beverage():_description("Unknow Beverage"){}
            virtual string getDescription(){
                return this->_description;
            }
            virtual double cost() = 0;
        private:         
        protected:
    };
    class CondimentDecorator:public Beverage{
        public:
            CondimentDecorator(){}
            virtual string getDescription()=0;
        private:
        protected:
    };
    class Espresso:public Beverage{
        public:
            Espresso(){
                _description = "Espresso";
            }
            virtual double cost(){
                return 1.99;
            }
        private:
        protected:
    };
    class HouseBlend:public Beverage{
        public:
            HouseBlend(){
                _description = "House Blend Coffee";
            }
            virtual string getDescription(){
                return this->_description;
            }
            virtual double cost(){
                return 0.89;
            }
        private:
        protected:
    };
    class DarkRoast:public Beverage{
        public:
            DarkRoast(){
                _description = "DarkRoast";
            }
            virtual double cost(){
                return 0.99;
            }
        private:
        protected:
    };
    class Mocha:public CondimentDecorator{
        public:
            Beverage* _beverage;
            Mocha(Beverage* beverage):_beverage(beverage){}

            virtual string getDescription(){
                return _beverage->getDescription() + ", Mocha";
            }
            virtual double cost(){
                return 0.20 + _beverage->cost();
            }
            
        private:
        protected:
    };    
    class Soy:public CondimentDecorator{
        public:
            Beverage* _beverage;
            Soy(Beverage* beverage):_beverage(beverage){}
            virtual string getDescription(){
                return _beverage->getDescription() + " ,Soy";
            }
            virtual double cost(){
                return 0.15 + _beverage->cost();
            }
            
        private:
        protected:
    };
    class Whip:public CondimentDecorator{
        public:
            Beverage* _beverage;
            Whip(Beverage* beverage):_beverage(beverage){}
            virtual string getDescription(){
                return _beverage->getDescription() + " ,Whip";
            }
            virtual double cost(){
                return 0.10 + _beverage->cost();
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
    void run(){test t;t.run();}void test::run(){
        
        Beverage* beverage = new Espresso();
        cout << beverage->getDescription() ;
        cout << " $" << beverage->cost() << endl;
        delete beverage;


        DarkRoast dr;
        Mocha mocha(&dr);
        SCI_TRACE_LOW("%s",mocha.getDescription().c_str());
        Mocha mocha1(&mocha);
        SCI_TRACE_LOW("%s",mocha1.getDescription().c_str());
        Mocha mocha2(&mocha1);
        SCI_TRACE_LOW("%s",mocha2.getDescription().c_str());
        
        cout << mocha2.getDescription() << " $";
        cout << mocha2.cost() << endl;
        
        HouseBlend hb;
        SCI_TRACE_LOW("%s $%.02f",hb.getDescription().c_str(),hb.cost());
        Soy soy(&hb);
        SCI_TRACE_LOW("%s $%.02f",soy.getDescription().c_str(),soy.cost());
        Mocha soy1(&soy);
        SCI_TRACE_LOW("%s $%.02f",soy1.getDescription().c_str(),soy1.cost());
        Whip soy2(&soy1);
        SCI_TRACE_LOW("%s $%.02f",soy2.getDescription().c_str(),soy2.cost());
        
        cout << soy2.getDescription() << " $";
        cout << soy2.cost() << endl;
    }
}
namespace PizzaFactory{     //GBK   "工厂模式"
    namespace SimplePizzaFactory{
        class Pizza{
            public:
                Pizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class CheesePizza:public Pizza{
            public:
                CheesePizza(){}
                
            private:
            protected:
        };
        class PepperoniPizza:public Pizza{
            public:
                PepperoniPizza(){}
                
            private:
            protected:
        };      
        class ClamPizza:public Pizza{
            public:
                ClamPizza(){}
                
            private:
            protected:
        };  
        class VeggiePizza:public Pizza{
            public:
                VeggiePizza(){}
                
            private:
            protected:
        };
        class SimplePizzaFactory{
            public:
                Pizza* _pizza;
                SimplePizzaFactory():_pizza(NULL){}
                Pizza* createPizza(string type){
                    if(type=="cheese"){
                        _pizza = new CheesePizza();
                    }else if(type=="pepperoni"){
                        _pizza = new PepperoniPizza();                    
                    }else if(type=="clam"){
                        _pizza = new ClamPizza();
                    }else if(type=="veggie"){
                        _pizza = new VeggiePizza();
                    }
                    return _pizza;
                }       
            private:
            protected:
        };
        class PizzaStore{
            public:
                SimplePizzaFactory* _factory;
                PizzaStore(SimplePizzaFactory* factory):_factory(factory){}
                Pizza* orderPizza(string type){
                    Pizza* pizza;
                    pizza = _factory->createPizza(type);

                    pizza->prepare();
                    pizza->bake();
                    pizza->cut();
                    pizza->box();
                    return pizza;
                }
            private:
            protected:
        };
    };
    namespace SimplePizzaFactory1{
        class Pizza{
            public:
                Pizza(){}
                virtual void prepare()=0;
                virtual void bake()=0;
                virtual void cut()=0;
                virtual void box()=0;
            private:
            protected:
        };
        class CheesePizza:public Pizza{
            public:
                CheesePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class PepperoniPizza:public Pizza{
            public:
                PepperoniPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };      
        class ClamPizza:public Pizza{
            public:
                ClamPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}            
            private:
            protected:
        };  
        class VeggiePizza:public Pizza{
            public:
                VeggiePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}            
            private:
            protected:
        };
        class SimplePizzaFactory{
            public:
                Pizza* _pizza;
                SimplePizzaFactory():_pizza(NULL){}
                Pizza* createPizza(string type){
                    if(type=="cheese"){
                        _pizza = new CheesePizza();
                    }else if(type=="pepperoni"){
                        _pizza = new PepperoniPizza();                    
                    }else if(type=="clam"){
                        _pizza = new ClamPizza();
                    }else if(type=="veggie"){
                        _pizza = new VeggiePizza();
                    }
                    return _pizza;
                }       
            private:
            protected:
        };
        class PizzaStore{
            public:
                PizzaStore(){}
                Pizza* orderPizza(string type){
                    Pizza* pizza;
                    pizza = createPizza(type);

                    pizza->prepare();
                    pizza->bake();
                    pizza->cut();
                    pizza->box();

                    return pizza;
                }
                
                virtual Pizza* createPizza(string type)=0;
            private:
            protected:
        };

        class NYStyleCheesePizza:public CheesePizza{
            public:
                NYStyleCheesePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class NYStylePepperoniPizza:public PepperoniPizza{
            public:
                NYStylePepperoniPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class NYStyleClamPizza:public ClamPizza{
            public:
                NYStyleClamPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class NYStyleVeggiePizza:public VeggiePizza{
            public:
                NYStyleVeggiePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };

        class ChicagoStyleCheesePizza:public CheesePizza{
            public:
                ChicagoStyleCheesePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class ChicagoStylePepperoniPizza:public PepperoniPizza{
            public:
                ChicagoStylePepperoniPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };  
        class ChicagoStyleClamPizza:public ClamPizza{
            public:
                ChicagoStyleClamPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class ChicagoStyleVeggiePizza:public VeggiePizza{
            public:
                ChicagoStyleVeggiePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };


        class NYStylePizzaStore:public PizzaStore{
            public:
                NYStylePizzaStore(){}
                virtual Pizza* createPizza(string type){
                    Pizza* pizza;
                    if(type == "cheese"){
                        pizza = new NYStyleCheesePizza();
                    }else if(type == "pepperoni"){
                        pizza = new NYStylePepperoniPizza();
                    }else if(type == "clam"){
                        pizza = new NYStyleClamPizza();
                    }else if(type == "veggie"){
                        pizza = new NYStyleVeggiePizza();
                    }
                }
            private:
            protected:
        };
        class ChicagoStylePizzaStore:public PizzaStore{
            public:
                ChicagoStylePizzaStore(){}
                virtual Pizza* createPizza(string type){
                    Pizza* pizza;
                    if(type == "cheese"){
                        pizza = new ChicagoStyleCheesePizza();
                    }else if(type == "pepperoni"){
                        pizza = new ChicagoStylePepperoniPizza();
                    }else if(type == "clam"){
                        pizza = new ChicagoStyleClamPizza();
                    }else if(type == "veggie"){
                        pizza = new ChicagoStyleVeggiePizza();
                    }
                    return pizza;
                }
            private:
            protected:
        };
    };
    namespace SimplePizzaFactory2{
        class Pizza{
            public:
                Pizza(){}
                virtual void prepare()=0;
                virtual void bake()=0;
                virtual void cut()=0;
                virtual void box()=0;
            private:
            protected:
        };
        class CheesePizza:public Pizza{
            public:
                CheesePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class PepperoniPizza:public Pizza{
            public:
                PepperoniPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };      
        class ClamPizza:public Pizza{
            public:
                ClamPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}            
            private:
            protected:
        };  
        class VeggiePizza:public Pizza{
            public:
                VeggiePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}            
            private:
            protected:
        };
        class SimplePizzaFactory{
            public:
                Pizza* _pizza;
                SimplePizzaFactory():_pizza(NULL){}
                Pizza* createPizza(string type){
                    if(type=="cheese"){
                        _pizza = new CheesePizza();
                    }else if(type=="pepperoni"){
                        _pizza = new PepperoniPizza();                    
                    }else if(type=="clam"){
                        _pizza = new ClamPizza();
                    }else if(type=="veggie"){
                        _pizza = new VeggiePizza();
                    }
                    return _pizza;
                }       
            private:
            protected:
        };
        class PizzaStore{
            public:
                PizzaStore(){}
                Pizza* orderPizza(string type){
                    Pizza* pizza;
                    pizza = createPizza(type);

                    pizza->prepare();
                    pizza->bake();
                    pizza->cut();
                    pizza->box();

                    return pizza;
                }
                    
            private:
            protected:
                virtual Pizza* createPizza(string type)=0;
        };

        class NYStyleCheesePizza:public CheesePizza{
            public:
                NYStyleCheesePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class NYStylePepperoniPizza:public PepperoniPizza{
            public:
                NYStylePepperoniPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class NYStyleClamPizza:public ClamPizza{
            public:
                NYStyleClamPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class NYStyleVeggiePizza:public VeggiePizza{
            public:
                NYStyleVeggiePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };

        class ChicagoStyleCheesePizza:public CheesePizza{
            public:
                ChicagoStyleCheesePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class ChicagoStylePepperoniPizza:public PepperoniPizza{
            public:
                ChicagoStylePepperoniPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };  
        class ChicagoStyleClamPizza:public ClamPizza{
            public:
                ChicagoStyleClamPizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };
        class ChicagoStyleVeggiePizza:public VeggiePizza{
            public:
                ChicagoStyleVeggiePizza(){}
                virtual void prepare(){}
                virtual void bake(){}
                virtual void cut(){}
                virtual void box(){}
            private:
            protected:
        };


        class NYStylePizzaStore:public PizzaStore{
            public:
                NYStylePizzaStore(){}
                virtual Pizza* createPizza(string type){
                    Pizza* pizza;
                    if(type == "cheese"){
                        pizza = new NYStyleCheesePizza();
                    }else if(type == "pepperoni"){
                        pizza = new NYStylePepperoniPizza();
                    }else if(type == "clam"){
                        pizza = new NYStyleClamPizza();
                    }else if(type == "veggie"){
                        pizza = new NYStyleVeggiePizza();
                    }
                }
            private:
            protected:
        };
        class ChicagoStylePizzaStore:public PizzaStore{
            public:
                ChicagoStylePizzaStore(){}
                virtual Pizza* createPizza(string type){
                    Pizza* pizza;
                    if(type == "cheese"){
                        pizza = new ChicagoStyleCheesePizza();
                    }else if(type == "pepperoni"){
                        pizza = new ChicagoStylePepperoniPizza();
                    }else if(type == "clam"){
                        pizza = new ChicagoStyleClamPizza();
                    }else if(type == "veggie"){
                        pizza = new ChicagoStyleVeggiePizza();
                    }
                    return pizza;
                }
            private:
            protected:
        };
    
    };
    namespace SimplePizzaFactory3{


        class Topping
        {
        public:
            Topping() : _size(0) {}
            virtual int add(string obj)
            {
                _buf[_size] = obj;
                _size++;
                return _size;
            }
            virtual int remove(int idx) {}
            virtual int get(int idx, void **obj) {}
            virtual int set(int idx, void *obj) {}
            virtual int show()
            {
                for (int i = 0; i < _size; i++)
                {
                    cout << i << ":" << _buf[i];
                }
            }
            virtual int getIdx(void *obj) {}
            virtual int getSize()
            {
                return _size;
            }
            virtual string get(int idx)
            {
                return _buf[idx];
            }

        private:
            string _buf[128];
            int _size;

        protected:
        };
        class Pizza
        {
        public:
            string _name;
            string _dough;
            string _sauce;
            Topping _topping;
            Pizza() : _name("Pizza"), _dough(""), _sauce("") {}
            void prepare()
            {
                cout << "Prepareing " << _name << endl;
                cout << "Tossing dough..." << endl;
                cout << "Adding sauce..." << endl;
                cout << "Adding toppings: " << endl;
                for (int i = 0; i < _topping.getSize(); i++)
                {
                    cout << "   " << _topping.get(i) << endl;
                }
            }
            virtual void bake()
            {
                cout << "Bake for 25 minutes at 350" << endl;
            }
            virtual void cut()
            {
                cout << "Cutting the pizza into diagonal slices" << endl;
            }
            virtual void box()
            {
                cout << "Place pizza in official Pizzastore box" << endl;
            }
            virtual string getName()
            {
                return _name;
            }

        private:
        protected:
        };

        class PizzaStore
        {
        public:
            Pizza *_pizza;
            PizzaStore() : _pizza(NULL) {}
            Pizza *orderPizza(string type)
            {
                Pizza *pizza;
                pizza = createPizza(type);
                // // _pizza = pizza;
                pizza->prepare();

                pizza->bake();
                pizza->cut();
                pizza->box();

                return pizza;
            }
            virtual Pizza *createPizza(string type) = 0;

        private:
        protected:
        };

        class NYStyleCheesePizza : public Pizza
        {
        public:
            NYStyleCheesePizza()
            {
                _name = "NY Style Sauce and Cheese Pizza";
                _dough = "Thin Crust Dough";
                _sauce = "Marinara Sauce";

                _topping.add("Grated Reggiano Cheese");
            }

        private:
        protected:
        };
        class NYStylePepperoniPizza : public Pizza
        {
        public:
            NYStylePepperoniPizza() {}
            virtual void prepare() {}
            virtual void bake() {}
            virtual void cut() {}
            virtual void box() {}

        private:
        protected:
        };
        class NYStyleClamPizza : public Pizza
        {
        public:
            NYStyleClamPizza() {}
            virtual void prepare() {}
            virtual void bake() {}
            virtual void cut() {}
            virtual void box() {}

        private:
        protected:
        };
        class NYStyleVeggiePizza : public Pizza
        {
        public:
            NYStyleVeggiePizza() {}
            virtual void prepare() {}
            virtual void bake() {}
            virtual void cut() {}
            virtual void box() {}

        private:
        protected:
        };

        class ChicagoStyleCheesePizza : public Pizza
        {
        public:
            ChicagoStyleCheesePizza()
            {
                _name = "Chicago Style Deep Dish Cheese Pizza";
                _dough = "Extra Thick Crust Dough";
                _sauce = "Plum Tomato Sauce";

                _topping.add("Shredded Mozzarella Cheese");
            }
            // virtual void bake(){}
            virtual void cut()
            {
                cout << "Cutting the pizza into square slices" << endl;
            }
            // virtual void box(){}
        private:
        protected:
        };
        class ChicagoStylePepperoniPizza : public Pizza
        {
        public:
            ChicagoStylePepperoniPizza() {}
            virtual void prepare() {}
            virtual void bake() {}
            virtual void cut() {}
            virtual void box() {}

        private:
        protected:
        };
        class ChicagoStyleClamPizza : public Pizza
        {
        public:
            ChicagoStyleClamPizza() {}
            virtual void prepare() {}
            virtual void bake() {}
            virtual void cut() {}
            virtual void box() {}

        private:
        protected:
        };
        class ChicagoStyleVeggiePizza : public Pizza
        {
        public:
            ChicagoStyleVeggiePizza() {}
            virtual void prepare() {}
            virtual void bake() {}
            virtual void cut() {}
            virtual void box() {}

        private:
        protected:
        };

        class NYStylePizzaStore : public PizzaStore
        {
        public:
            NYStylePizzaStore() {}
            virtual Pizza *createPizza(string type)
            {
                Pizza *pizza;
                if (type == "cheese")
                {
                    pizza = new NYStyleCheesePizza();
                }
                else if (type == "pepperoni")
                {
                    pizza = new NYStylePepperoniPizza();
                }
                else if (type == "clam")
                {
                    pizza = new NYStyleClamPizza();
                }
                else if (type == "veggie")
                {
                    pizza = new NYStyleVeggiePizza();
                }
                return pizza;
            }

        private:
        protected:
        };
        class ChicagoStylePizzaStore : public PizzaStore
        {
        public:
            ChicagoStylePizzaStore() {}
            virtual Pizza *createPizza(string type)
            {
                Pizza *pizza;
                if (type == "cheese")
                {
                    pizza = new ChicagoStyleCheesePizza();
                }
                else if (type == "pepperoni")
                {
                    pizza = new ChicagoStylePepperoniPizza();
                }
                else if (type == "clam")
                {
                    pizza = new ChicagoStyleClamPizza();
                }
                else if (type == "veggie")
                {
                    pizza = new ChicagoStyleVeggiePizza();
                }
                return pizza;
            }

        private:
        protected:
        };

        class Dough
        {
        public:
            Dough() {}

        private:
        protected:
        };
        class Sauce
        {
        public:
            Sauce() {}

        private:
        protected:
        };
        class Cheese
        {
        public:
            Cheese() {}

        private:
        protected:
        };
        class Veggies
        {
        public:
            Veggies() {}

        private:
        protected:
        };
        class Pepperoni
        {
        public:
            Pepperoni() {}

        private:
        protected:
        };
        class Clams
        {
        public:
            Clams() {}

        private:
        protected:
        };

        class PizzaIngredientFactory
        {
        public:
            PizzaIngredientFactory() {}
            virtual Dough *createDough() = 0;
            virtual Sauce *createSauce() = 0;
            virtual Cheese *createCheese() = 0;
            virtual Veggies *createVeggies() = 0;
            virtual Pepperoni *createPerioni() = 0;
            virtual Clams *createClam() = 0;

        private:
        protected:
        };
        class NYPizzaIngredientFactory : public PizzaIngredientFactory
        {
        public:
            NYPizzaIngredientFactory() {}
            virtual Dough *createDough()
            {
            }
            virtual Sauce *createSauce() {}
            virtual Cheese *createCheese() {}
            virtual Veggies *createVeggies() {}
            virtual Pepperoni *createPerioni() {}
            virtual Clams *createClam() {}

        private:
        protected:
        };

        // class AbstractFactory{
        //     public:
        //         AbstractFactory(){}
        //         virtual ProductA* CreateProductA()=0;
        //         virtual ProductB* CreateProductB()=0;
        //     private:
        //     protected:
        // };

        class test
        {
        public:
            void run0();
            void run();

        private:
        };
        void run(){test t;t.run();}void test::run()
        {
        }
        void test::run0()
        {
            PizzaStore *newyorkStore = new NYStylePizzaStore();

            PizzaStore *chicagoStore = new ChicagoStylePizzaStore();

            Pizza *pizza = newyorkStore->orderPizza("cheese");

            cout << "Ethan ordered a " << pizza->getName() << endl
                << endl;

            Pizza *pizza1 = chicagoStore->orderPizza("cheese");
            cout << "Joel orderde a " << pizza1->getName() << endl;

            delete newyorkStore;
            delete chicagoStore;
            delete pizza;
            delete pizza1;
        } //page 153
    };
}
namespace SimpleCarFactory{//Gbk
    //抽象产品
    class Car{
        public:
            Car(){}
            virtual void Drive()=0;
        private:
        protected:
    };
    //具体产品
    class Benz:public Car{
        public:
            Benz(){}
            virtual void Drive(){
                cout << "Drive the Benz" << endl;
            }
        private:
        protected:
    };
    //具体产品
    class Bmw:public Car{
        public:
            Bmw(){}
            virtual void Drive(){
                cout << "Drive the BMW" << endl;
            }
            
        private:
        protected:
    };
    //简单工厂
    class CarFactory{
        public:
            CarFactory(){}
            static Car* createCar(string type){
                Car* car = NULL;
                if(type=="Benz"){
                    car = new Benz();
                }else if(type=="Bmw"){
                    car = new Bmw();
                }
                return car;
            }
        private:
        protected:
    };

    //客户

    class test{
        public:
            test(){}
            void run();
        private:
        protected:
    };
    void run(){test t;t.run();}void test::run(){
        Car* cars = CarFactory::createCar("Benz");
        cars->Drive();

        Car* cars1 = CarFactory::createCar("Bmw");
        cars1->Drive();

        delete cars;
        delete cars1;
    }
}
namespace FactoryMethod{
    //factoryMethod
    //chinese codec::GBK
    //抽象产品
    class Car{
        public:
            Car(){}
            virtual void Drive()=0;
        private:
        protected:
    };

    //具体产品
    class Benz:public Car{
        public:
            Benz(){}
            virtual void Drive(){
                cout << "Drive the Benz" << endl;
            }
        private:
        protected:
    };
    //具体产品
    class Bmw:public Car{
        public:
            Bmw(){}
            virtual void Drive(){
                cout << "Drive the BMW" << endl;
            }
            
        private:
        protected:
    };

    //抽象工厂
    class CarFactory{
        public:
            CarFactory(){}
            virtual Car* createCar()=0;
        private:
        protected:
    };
    //具体工厂
    class BenzFactory:public CarFactory{
        public:
            BenzFactory(){}
            virtual Car* createCar(){
                Car* car = new Benz();
                return car;
            }
        private:
        protected:
    };
    //具体工厂
    class BmwFactory:public CarFactory{
        public:
            BmwFactory(){}
            virtual Car* createCar(){
                Car* car = new Bmw();
                return car;
            }      
        private:
        protected:
    };

    //客户

    class test{
        public:
            test(){}
            void run();
        private:
        protected:
    };
    void run(){test t;t.run();}void test::run(){
        CarFactory* carfactory = new BenzFactory();
        CarFactory* carfactory1 = new BmwFactory();
        Car* c = carfactory->createCar();
        c->Drive();
        Car* c1 = carfactory1->createCar();
        c1->Drive();
        delete carfactory;
        delete c;
        delete carfactory1;
        delete c1;
    }
}
namespace AbstractFactory{
    //抽象产品
    class BenzCar{
        public:
            BenzCar(){}
            virtual void Drive()=0;
        private:
        protected:
    };
    //具体产品
    class BenzSportCar:public BenzCar{
        public:
            BenzSportCar(){}
            virtual void Drive(){
                cout << "Driver Benzsportcar" << endl;
            }
        private:
        protected:
    };  
    //具体产品
    class BenzBusinessCar:public BenzCar{
        public:
            BenzBusinessCar(){}
            virtual void Drive(){
                cout << "Driving the BenzBusinessCar" << endl;
            }
        private:
        protected:
    };
    //抽象产品
    class BmwCar{
        public:
            BmwCar(){}
            virtual void Drive()=0;
        private:
        protected:
    };
    //具体产品
    class BmwSportCar:public BmwCar{
        public:
            BmwSportCar(){}
            virtual void Drive(){
                cout << "Driving the BmwSportCar" << endl;
            }
        private:
        protected:
    };
    //具体产品
    class BmwBusinessCar:public BmwCar{
        public:
            BmwBusinessCar(){}
            virtual void Drive(){
                cout << "Driving the BmwBusinessCar" << endl;
            }
        private:
        protected:
    };  
    //抽象工厂
    class CarFactory{
        public:
            CarFactory(){}
            virtual BenzCar* createBenzCar()=0;
            virtual BmwCar* createBmwCar()=0;
        private:
        protected:
    };
    //具体工厂
    class SportCarFactory:public CarFactory{
        public:
            SportCarFactory(){}
            virtual BenzCar* createBenzCar(){
                BenzCar* benzCar = new BenzSportCar();
                return benzCar;
            }
            virtual BmwCar* createBmwCar(){
                BmwCar* bmwCar = new BmwSportCar();
                return bmwCar;
            }
        private:
        protected:
    };
    //具体工厂
    class BusinessCarFactory:public CarFactory{
        public:
            BusinessCarFactory(){}
            virtual BenzCar* createBenzCar(){
                BenzCar* benzCar = new BenzBusinessCar();
                return benzCar;
            }
            virtual BmwCar* createBmwCar(){
                BmwCar* bmwCar = new BmwBusinessCar();
                return bmwCar;
            }
        private:
        protected:
    };


    //client
    class test{
        public:
            test(){}
            void run();
        private:
        protected:
    };
    void run(){test t;t.run();}void test::run(){
        CarFactory* cf = new SportCarFactory();
        BenzCar* bc = cf->createBenzCar();
        bc->Drive();
        delete cf;
        delete bc;
    }
}
namespace Singleton{//              单件模式

    namespace ChocolateBoiler_{
        class ChocolateBoiler{
            public:
                static ChocolateBoiler* uniqueInstance;
                static ChocolateBoiler* getInstance();
                static void destroyInstance();
                void fill();
                void drain();
                void boil();
                bool isEmpty();
                bool isBoiled();
                static ChocolateBoiler* getData();
                // static ()
                int getA(){
                    return a;
                }
                void setA(int dat){
                    a = dat;
                }
            
            private:    
                ChocolateBoiler();
                
                bool empty;
                bool boiled;
                int a;
            protected:
        };
        #if 1
        ChocolateBoiler* ChocolateBoiler::uniqueInstance = NULL;
        #else 
        ChocolateBoiler* ChocolateBoiler::uniqueInstance = new ChocolateBoiler();  
        //codec GBK :: 急切创建实例  进程开始就已创建实例 ；
        #endif
        ChocolateBoiler* ChocolateBoiler::getInstance(){
            # if 0
            if(uniqueInstance==NULL){
                uniqueInstance = new ChocolateBoiler();
                // assert(ChocolateBoiler::uniqueInstance);
            }
            return uniqueInstance;
            #else
            static ChocolateBoiler _s_Instance;
            uniqueInstance = &_s_Instance;
            return uniqueInstance;
            #endif
        }
        ChocolateBoiler* ChocolateBoiler::getData(){
            return uniqueInstance;
        }
        void ChocolateBoiler::destroyInstance(){
            delete uniqueInstance;
            uniqueInstance = NULL;
        }   
        ChocolateBoiler::ChocolateBoiler(){
            this->empty = true;
            this->boiled = false;
            // cout << "p:" << uniqueInstance << endl;
        }
        void ChocolateBoiler::fill(){
            if(isEmpty()){
                this->empty = false;
                this->boiled = false;
            }
        }
        void ChocolateBoiler::drain(){
            if(!isEmpty()&&isBoiled()){
                this->empty = true;
            }
        }
        void ChocolateBoiler::boil(){
            if(!isEmpty()&&!isBoiled()){
                this->boiled = true;
            }
        }
        bool ChocolateBoiler::isEmpty(){
            return this->empty;
        }
        bool ChocolateBoiler::isBoiled(){
            return this->boiled;
        }
    }
    template <class T>
    class Csingleton{
        public:
            static T* getInstance();
            ~Csingleton(){
                if(m_pInstance!=NULL)
                    delete m_pInstance;
                if(hMutex!=0){
                    CloseHandle(hMutex);
                    hMutex = 0;
                }
                cout << __FUNCTION__ << endl;
            }
        private:
            static T* m_pInstance;
            static HANDLE hMutex;
        protected:
            Csingleton();//gbk 防止构造多个实例
            Csingleton& operator =(const Csingleton&){}//防止赋值构造多个实例
            Csingleton(const Csingleton&){}//防止拷贝构造多个实例 
                       
    };
    template <class T> T* Csingleton<T>::m_pInstance = NULL;
    template <class T> HANDLE Csingleton<T>::hMutex = CreateMutex(NULL,TRUE,"Csingleton::m_pInstance");
    template <class T> T* Csingleton<T>::getInstance(){      
        if(!m_pInstance){
            WaitForSingleObject(hMutex,INFINITE);
            if(!m_pInstance){
                m_pInstance = new T;
            }            
            ReleaseMutex(hMutex);
        }     
        return m_pInstance;
    }
    class Cmylog{
        friend class Csingleton<Cmylog>;
        public:
            
            void log(string str){
                cout << "log msg:" << str << endl;
            }
            ~Cmylog(){
                cout << __FUNCTION__ << endl;
                //
            }

        private:
            Cmylog(){};
            void t(){
                cout << __FUNCTION__ << endl;
            }
        protected:
    };
    class test{
        public:
            test(){}
            void run();
        private:
        protected:
    };
    void run(){test t;t.run();}void test::run(){
        // ChocolateBoiler* cb = ChocolateBoiler::getInstance();
        // ChocolateBoiler::destroyInstance();
        // A* a = A::getinstance();
        Cmylog* pLog = Csingleton<Cmylog>::getInstance();
        pLog->log("hello arvinn");
        // pLog->test();

        delete pLog ;

        // delete (Csingleton*)
        system("pause");
        
    }   
}
namespace OrderParttern{ // 命令模式

    class RoastCook{
        public:
            RoastCook(){}
            void MakeMutton(){
                cout << __FUNCTION__ << endl;
            }
            void MakeChickenWing(){
                cout << __FUNCTION__ << endl;
            }
        private:
        protected:
    };
    class Command{
        public:
            Command(RoastCook* recv){
                this->receiver = recv;
            }
            virtual void execute()=0;
        private:
        protected:
            RoastCook* receiver;            
    };
    class MakeMuttonCmd:public Command{
        public:
            MakeMuttonCmd(RoastCook* recv):Command(recv){}
            virtual void execute(){
                receiver->MakeMutton();
            }            
        private:
        protected:
    };
    class MakeChickenWingCmd:public Command{
        public:
            MakeChickenWingCmd(RoastCook* recv):Command(recv){}
            virtual void execute(){
                receiver->MakeChickenWing();
            }
        private:
        protected:
    };

    class Waiter{
        public:
            Waiter(){}
            void SetCmd(Command* cmd);
            void Notify();
            
        private:
            vector<Command*> m_cmdlst;
        protected:
    };
    void Waiter::SetCmd(Command* cmd){
        m_cmdlst.push_back(cmd);
        cout << "Add order" <<endl;
    }
    void Waiter::Notify(){
        vector<Command*>::iterator it;
        for(it = m_cmdlst.begin();it!=m_cmdlst.end();++it){
            (*it)->execute();
        }
    }

    class test{
        public:
            test(){}
            void run();
        private:
        protected:
    };
    void run(){test t;t.run();}void test::run(){
        RoastCook* cook = new RoastCook();
        Command* cmd1 = new MakeMuttonCmd(cook);
        Command* cmd2 = new MakeChickenWingCmd(cook);
        Waiter* girl = new Waiter();

        //点菜
        girl->SetCmd(cmd1);
        girl->SetCmd(cmd2);

        //服务员通知
        girl->Notify();
    }
}
namespace AdapterParttern{ // 适配器模式

    class Duck{
        public:
            Duck(){}
            virtual void quack()=0;
            virtual void fly()=0;
        private:
        protected:
    };
    class MallardDuck:public Duck{
        public:
            MallardDuck(){}
            virtual void quack(){
                cout << __FUNCTION__ << endl;
            }
            virtual void fly(){
                cout << "MallardDuck" ;
                cout << __FUNCTION__ << endl;
            }
        private:
        protected:
    };
    class Turkey{
        public:
            Turkey(){}
            virtual void gobble()=0;
            virtual void fly()=0;
        private:
        protected:
    };
    class WildTurkey:public Turkey{
        public:
            WildTurkey(){}
            virtual void gobble(){
                cout << __FUNCTION__ << __LINE__ << endl;
            }
            virtual void fly(){
                cout << __FUNCTION__ << __LINE__ << endl;
            }
        private:
        protected:
    };
    class TurkeyAdapter:public Duck{
        public:
            Turkey* turkey;  
            TurkeyAdapter(Turkey* tk){
                this->turkey = tk;
            }
            virtual void quack(){
                turkey->gobble();
            }
            virtual void fly(){
                for(int i=0; i<5;i++){
                    turkey->fly();
                }
            }
        private:
        protected:
    };
    class DuckAdapter:public Turkey{
        public:
            DuckAdapter(Duck* duck):_duck(duck){}
            virtual void gobble(){
                _duck->quack();
            }
            virtual void fly(){
                cout << "DuckAdapter" << endl;
                _duck->fly();
            }
        private:
            Duck* _duck;
            
        protected:
    };

    //目标接口类   duck
    class Target{ 
        public:
            Target(){}
            virtual ~Target(){}
            virtual void Request(){
                cout << __FUNCTION__ << __LINE__ << endl;
            }
        private:
        protected:
    };
    //需要适配的类  turkey
    class Adaptee{
        public:
            Adaptee(){}
            ~Adaptee(){}
            void SpecificRequest(){
                cout << __FUNCTION__ << __LINE__ << endl;
            }
        private:
        protected:
    };
    //类模式，适配器类,通过PUBLIC继承获得接口继承的效果,
    //                通过private继承得到实现继承的效果
    class Adapter:public Target,private Adaptee{
        public:
            Adapter(){}
            ~Adapter(){}
            virtual void Request(){
                cout << __FUNCTION__ << __LINE__ << endl;
                this->SpecificRequest();
                cout << "@_@" << endl;
            }
        private:
        protected:
    };

    //对象模式,适配器类,继承Target类,采用组合的方式实现Adaptee的复用
    class Adapter1:public Target{
        public:
            Adapter1(Adaptee* adaptee):_adaptee(adaptee){}
            virtual void Request(){
                cout << __FUNCTION__ << __LINE__ << endl;
                this->_adaptee->SpecificRequest();
                cout << "@_@" << endl;
            }
        private:
            Adaptee* _adaptee;
        protected:
    };


    void run(){
        //类模式
        Target* ptarget = new Adapter();
        ptarget->Request();

        Adaptee* ade = new Adaptee();
        Target* ptarget1 = new Adapter1(ade);
        ptarget1->Request();

        delete ptarget;
        delete ade;
        delete ptarget1;

    }
}
namespace facola{//         外观模式
    class Sub_work1{
        public:
            Sub_work1(){}
            void working1(){
                cout << __FUNCTION__ << __LINE__ << endl;
            }
        private:
        protected:
    };
    class Sub_work2{
        public:
            Sub_work2(){}
            void working2(){
                cout << __FUNCTION__ << __LINE__ << endl;
            }

        private:
        protected:
    };
    class Sub_work3{
        public:
            Sub_work3(){}
            void working3(){
                cout << __FUNCTION__ << __LINE__ << endl;
            }
        private:
        protected:
    };

    class Sub_work4{
        public:
            Sub_work4(){}
            void working4(){
                cout << __FUNCTION__ << __LINE__ << endl;
            }
        private:
        protected:
    };

    class Work{//总工作,客户与之打交道
        public:
            Work(){}
            void work1(){
                w1.working1();
                w3.working3();
            }
            void work2(){
                w2.working2();
                w3.working3();
                w4.working4();
            }
        private:
            Sub_work1 w1;
            Sub_work2 w2;
            Sub_work3 w3;
            Sub_work4 w4;
        protected:
    };

    void run(){
        Work w;
        cout << "开始调用总工作1" << endl;
        w.work1();

        cout << "开始调用总工作2" << endl;
        w.work2();

    }
}
namespace facolaParttern{
    class CaffeineBeverage{
        public:
            CaffeineBeverage(){}
            virtual void prepareRecipe()final{
                boilWater();
                brew();
                pourInCup();
                addCondiments();
            }
            virtual void brew(){
                cout << "OBJ.brew();" << endl;
            }
            virtual void addCondiments(){
                cout << "OBJ.addCondiments();" << endl;
            }
            virtual void boilWater(){
                cout << "Boiling water" << endl;
            }
            virtual void pourInCup(){
                cout << "Pouring into cup" << endl;
            }
        private:
        protected:
    };
    class Tea:public CaffeineBeverage{
        public:
            Tea(){}
            virtual void brew(){
                cout << "Steeping the tea" << endl;
            }   
            virtual void addCondiments(){
                cout << "Adding Lemon" << endl; 
            }
            
            
        private:
        protected:
    };
    class Coffee:public CaffeineBeverage{
        public:
            Coffee(){}
            virtual void brew(){
                cout << "Dripping Coffee through filter" << endl;
            }
            virtual void addCondiments(){
                cout << "Adding Sugar and milk" << endl;
            }
        private:
        protected:
    };
    class AbstractClass{
        public:
            AbstractClass(){}
            virtual void templateMethod() final {
                primitiveOperation1();
                primitiveOperation2();
                ConcreteOperation();
                hook();
            }
            virtual void primitiveOperation1(){}
            virtual void primitiveOperation2(){}
            virtual void ConcreteOperation()final{

            }
            void hook(){

            }
        private:
        protected:
    };
    class CaffeineBeverageWithHook{
        public:
            CaffeineBeverageWithHook(){}
            void prepareRecipe(){
                boilWater();
                brew();
                pourInCup();
                if(customerWantsCondiments()){
                    addCondiments();
                }
            }
            virtual void brew(){}
            virtual void addCondiments(){}
            virtual void boilWater(){
                cout << "Boiling water" << endl;
            }
            virtual void pourInCup(){
                cout << "Pouring into cup" << endl;
            }
            virtual bool customerWantsCondiments(){
                return true;
            }
        private:
        protected:
    };
    class CoffeeWithHook:public CaffeineBeverageWithHook{
        public:
            CoffeeWithHook(){}
            virtual void brew(){
                cout << "Dripping Coffee through filter" << endl;
            }
            virtual void addCondiments(){
                cout << "Adding Sugar and Milk" << endl;
            }
            virtual bool customerWantsCondiments(){
                string answer = getUserInput();
                char ch = answer.c_str()[0];
                if(ch == 'y' || ch == 'Y'){
                    return true;
                }else{
                    return false;
                }
            }
            
        private:
            string getUserInput(){
                string answer;
                cout << "Would you like milk and sugar with your coffee (y/n)? " << endl;

                cin >> answer;
                return answer;
            }
        protected:
    };
    class TeaWithHook:public CaffeineBeverageWithHook{
        public:
            TeaWithHook(){}
            virtual void brew(){
                cout << "Steeping the tea" << endl;
            }   
            virtual void addCondiments(){
                cout << "Adding Lemon" << endl; 
            }
            virtual bool customerWantsCondiments(){
                string answer = getUserInput();
                char ch = answer.c_str()[0];
                if(ch == 'y' || ch == 'Y'){
                    return true;
                }else{
                    return false;
                }
            }
            virtual string getUserInput(){
                string answer;
                cout << "Would you like lemon with your tea (y/n)?" << endl;
                cin >> answer;
                return answer;
            }
        private:
        protected:
    };
    void run(){
        TeaWithHook teawithhook;
        CoffeeWithHook coffeewithhook;

        cout << "Making tea..." <<endl;
        teawithhook.prepareRecipe();

        cout << "Making coffee..." << endl;
        coffeewithhook.prepareRecipe();
    }
}
namespace IteratorParttern{// 适配器模式
    template<class Item>
    class Iterator{
        public:
            Iterator(){}
            virtual void first()=0;
            virtual void next()=0;
            virtual Item* curItem()=0;
            virtual bool isDone()=0;
        private:
        protected:
    };
    template<class Item>class ConcreteAggregate;
    template<class Item>
    class ConcreteIterator:public Iterator<Item>{
        ConcreteAggregate<Item>* mAggr;
        int cur;
        public:
            ConcreteIterator(ConcreteAggregate<Item>* aggr){
                mAggr = aggr;
            }
            virtual void first(){
                cur = 0;
            }
            virtual void next(){
                if(cur< mAggr->getLen()){
                    cur++;
                }
            }
            virtual Item* curItem(){
                if(cur < mAggr->getLen()){
                    return &(*mAggr)[cur];
                }else {
                    return NULL;
                }
            }
            virtual bool isDone(){
                return (cur >= mAggr->getLen());
            }
            
        private:
        protected:
    };
    template<class Item>
    class Aggregate{
        public:
            Aggregate(){}
            virtual Iterator<Item>* createIterator()=0;
        private:
        protected:
    };
    template<class Item>
    class ConcreteAggregate:public Aggregate<Item>{
        vector<Item> mData;
        public:
            ConcreteAggregate(){
                mData.push_back(1);
                mData.push_back(2);
                mData.push_back(3);
            }
            virtual Iterator<Item>* createIterator(){
                return new ConcreteIterator<Item>(this);
            }
            Item& operator[](int idx){
                return mData[idx];
            }
            int getLen(){
                return mData.size();
            }
        private:
        protected:
    };

    void run(){
        Aggregate<int>* aggr = new ConcreteAggregate<int>();
        Iterator<int>* it = aggr->createIterator();
        for(it->first();!it->isDone();it->next()){
            cout << *(it->curItem()) << endl;
        }
        delete it;
        delete aggr;
        
    }
}
namespace StateParttern{    // 状态模式
    #define log() cout << __FUNCTION__ << ":" << __LINE__ << endl
    #ifdef __ORG  
    class GumballMachine{
        enum STATE_E{
            SOLD_OUT = 0,
            NO_QUARTER = 1,
            HAS_QUARTER = 2,
            SOLD = 3,
        };
        public:
            GumballMachine(int count){
                mCount = count;
                if(mCount > 0){
                    mState = NO_QUARTER;
                }
            }

            virtual void insertQuarter(){//塞入 25分币
                switch(mState){
                    case SOLD_OUT:{
                        cout << "You can't insert a quarter, the machine is sold out" << endl;
                    }break;
                    case NO_QUARTER:{
                        mState = HAS_QUARTER;
                        cout << "You inserted a quarter" << endl;
                    }break;
                    case HAS_QUARTER:{
                        cout << "You can't insert another quarter" << endl;
                    }break;
                    case SOLD:{
                        cout << "Please wait, we're already giving you a gumball" << endl;
                    }break;
                }
            }
            virtual void ejectQuarter(){//退出 分币
                switch(mState){
                    case SOLD_OUT:{
                        cout << "You can't eject, you haven't inserted aquarter yet" << endl;
                    }break;
                    case NO_QUARTER:{
                        cout << "You haven't inserted a quarter" << endl;
                    }break;
                    case HAS_QUARTER:{
                        cout << "Quarter returned" << endl;
                    }break;
                    case SOLD:{
                        cout << "Sorry, you already turned the crank" << endl;
                    }break;
                }
            }
            virtual void turnCrank(){//扭动 曲柄
                switch(mState){
                    case SOLD:{
                        cout << "Turning twice doesn't get you anoter gumball!" << endl;
                    }break;
                    case NO_QUARTER:{
                        cout << "You turned but there's no quarter" << endl;
                    }break;
                    case SOLD_OUT:{
                        cout << "You truned ,but there are no gumballs" << endl;
                    }break;
                    case HAS_QUARTER:{
                        cout << "You turned..." << endl;
                        mState = SOLD;
                        dispense();
                    }
                }
            }
            virtual void dispense(){ // 发放
                switch(mState){
                    case SOLD_OUT:{
                        cout << "A gumball comes rolling out the slot" << endl;
                        mCount--;
                        if(mCount==0){
                            cout << "Oops, out of gumballs!" << endl;
                            mState = SOLD_OUT;
                        }else{
                            mState = NO_QUARTER;
                        }
                    }break;
                    case NO_QUARTER:{
                        mState = HAS_QUARTER;
                        cout << "You need to pay first" << endl;
                    }break;
                    case HAS_QUARTER:{
                        cout << "No gumball dispensed" << endl;
                    }break;
                    case SOLD:{
                        cout << "Please wait, we're already giving you a gumball" << endl;
                    }break;
                }
            }
            
        private:
            int mState;
            int mCount;
        protected:
    };       
    
    void run(){
        GumballMachine gm(5);
        cout << "gumballMachine" << endl;

        gm.insertQuarter();
        gm.turnCrank();

        log();

        gm.insertQuarter();
        gm.ejectQuarter();
        gm.turnCrank();

        log();

        gm.insertQuarter();
        gm.turnCrank();
        gm.insertQuarter();
        gm.turnCrank();
        gm.ejectQuarter();

        log();

        gm.insertQuarter();
        gm.insertQuarter();
        gm.turnCrank();
        gm.insertQuarter();
        gm.turnCrank();
        gm.insertQuarter();
        gm.turnCrank();

        log();
    }
    #endif
    class State{
        public:
            State(){}
            virtual void insertQuarter()=0;
            virtual void ejectQuarter()=0;
            virtual void turnCrank()=0;
            virtual void dispense()=0;
        private:
        protected:
    };
    class GumballMachine{
        public:
            GumballMachine(int numberOfGumballs);
            ~GumballMachine();
            void insertQuarter();
            void ejectQuarter();
            void turnCrank();
            void setState(State* state);
            void releaseBall();
            State* getSoldOutState();
            State* getNoQuarterState();
            State* getHasQuarterState();
            State* getSoldState();
            State* getWinnerState();
            int getCount();

        private:
            State* mState;
            State* soldOutState;
            State* noQuarterState;
            State* hasQuarterState;
            State* soldState;
            State* winnerState;
            int mCount;
            // int randomWinner;
        protected:
    };
    class NoQuarterState:public State{
        public:
            NoQuarterState(GumballMachine* gm):mGm(gm){}
            virtual void insertQuarter(){
                cout << "You inserted a quarter" << endl;
                mGm->setState(mGm->getHasQuarterState());
            }
            virtual void ejectQuarter(){
                cout << "You haven't inserted a quarter" << endl;
            }
            virtual void turnCrank(){
                cout << "You turned, but there's no quarter" << endl;
            }
            virtual void dispense(){
                cout << "You need to pay first" << endl;
            }
        private:
            GumballMachine* mGm;

        protected:
    };
    class HasQuarterState:public State{
        public:
            HasQuarterState(GumballMachine* gm):mGm(gm){}
            virtual void insertQuarter(){
                cout << "You can't insert another quarter" << endl;
            }
            virtual void ejectQuarter(){
                cout << "Quarter returned" << endl;
                mGm->setState(mGm->getNoQuarterState());
            }
            virtual void turnCrank(){
                cout << "You turned..." << endl;
                // mGm->setState(mGm->getSoldState());
                int rd = rand()%10;
                if(rd==0&&mGm->getCount()>1){
                    mGm->setState(mGm->getWinnerState());
                }else{
                    mGm->setState(mGm->getSoldState());
                }
            }
            virtual void dispense(){
                cout << "No gumball dispensed" << endl;
            }
        private:
            GumballMachine* mGm;
        protected:
    };
    class SoldState:public State{
        public:
            SoldState(GumballMachine* gm){
                this->mGm = gm;
            }
            virtual void insertQuarter(){
                cout << "Please wait, we're already giving you a gumball" << endl;
            }
            virtual void ejectQuarter(){
                cout << "Sorry, you already turned the crank" << endl;
            }
            virtual void turnCrank(){
                cout << "Turning twice doesn't get you another gumball!" << endl;
            }
            virtual void dispense(){
                mGm->releaseBall();
                if(mGm->getCount()>0){
                    mGm->setState(mGm->getNoQuarterState());
                }else{
                    cout << "Oops, out of gumballs!" << endl;
                    mGm->setState(mGm->getSoldOutState());
                }
            }
        private:
            GumballMachine* mGm;
        protected:
    };
    class SoldOutState:public State{
        public:
            SoldOutState(GumballMachine* gm){
                mGm = gm;
            }
            virtual void insertQuarter(){
                cout << "You can't insert a quarter, the machine is sold out" << endl;
            }
            virtual void ejectQuarter(){
                cout << "You can't eject, you haven't inserted aquarter yet" << endl;
            }
            virtual void turnCrank(){
                cout << "You turned, but ther are no gumballs" << endl;
            }
            virtual void dispense(){
                cout << "No gumball dispensed" << endl;
            }
        private:
            GumballMachine* mGm;
        protected:
    };
    class WinnerState:public State{
        public:
            WinnerState(GumballMachine* gm){
                mGm = gm;
            }
            virtual void insertQuarter(){
                log();
            }
            virtual void ejectQuarter(){
                log();
            }
            virtual void turnCrank(){
                log();
            }
            virtual void dispense(){
                cout << "YOU'RE A WINNER! You get two gumballs for your quarter"<< endl;
                mGm->releaseBall();
                if(mGm->getCount()==0){
                    mGm->setState(mGm->getSoldOutState());
                }else{
                    mGm->releaseBall();
                    if(mGm->getCount()>0){
                        mGm->setState(mGm->getNoQuarterState());
                    }else{
                        cout << "Oops, out of gumbalss" << endl;
                        mGm->setState(mGm->getSoldOutState());
                    }                   
                }
            }
            
        private:
            GumballMachine* mGm;
        protected:
    };


    GumballMachine::GumballMachine(int numberOfGumballs){
        soldOutState = new SoldOutState(this);
        noQuarterState = new NoQuarterState(this);
        hasQuarterState = new HasQuarterState(this);
        soldState = new SoldState(this);
        winnerState = new WinnerState(this);
        mCount = numberOfGumballs;
        if(numberOfGumballs>0){
            mState = noQuarterState;
        }
    }
    GumballMachine::~GumballMachine(){
        // delete mState;
        delete soldOutState;
        delete noQuarterState;
        delete hasQuarterState;
        delete soldState;
    }
    void GumballMachine::insertQuarter(){
        mState->insertQuarter();
    }
    void GumballMachine::ejectQuarter(){
        mState->ejectQuarter();
    }
    void GumballMachine::turnCrank(){
        mState->turnCrank();
        mState->dispense();
    }
    void GumballMachine::setState(State* state){
        mState = state;
    }
    void GumballMachine::releaseBall(){
        cout << "A gumball comes rolling out the slot..." << endl;
        if(mCount!=0){
            mCount--;
        }
    }
    State* GumballMachine::getSoldOutState(){
        return this->soldOutState;
    }
    State* GumballMachine::getNoQuarterState(){
        return this->noQuarterState;
    }
    State* GumballMachine::getHasQuarterState(){    
        return this->hasQuarterState;
    }
    State* GumballMachine::getSoldState(){
        return this->soldState;
    }
    State* GumballMachine::getWinnerState(){
        return this->winnerState;
    }
    int GumballMachine::getCount(){
        return mCount;
    }

    void run(){
        GumballMachine gm(5);
        
        log();

        gm.insertQuarter();
        gm.turnCrank();

        log();

        gm.insertQuarter();
        gm.turnCrank();
        gm.insertQuarter();
        gm.turnCrank();
    }
    
}
namespace Player{
    class State{
        public:
            State(){}
            virtual void play()=0;
            virtual void pause()=0;
            virtual void stop()=0;
        private:
        protected:
    };
    class Player{
        public:
            Player();
            ~Player();
            void play();
            void pause();
            void stop();
            void setState(State* state){
                mCurState = state;
            }

            State* getCurState(){
                return mCurState;
            }
            State* getPlayingState(){
                return mPlayingState;
            }
            State* getPauseState(){
                return mPauseState;
            }
            State* getStopState(){
                return mStopState;
            }
        private:
            State* mCurState;
            State* mPlayingState;
            State* mPauseState;
            State* mStopState;
        protected:
    };
    class PlayingState:public State{
        public:
            PlayingState(Player* player){
                mPlayer = player;
            }
            virtual void play(){
                cout << "playing..." << endl;
            }
            virtual void pause(){
                cout << "Paused" << endl;
                mPlayer->setState(mPlayer->getPauseState());
            }
            virtual void stop(){
                cout << "Stoped" << endl;
                mPlayer->setState(mPlayer->getStopState());
            }
            
        private:
            Player* mPlayer;
        protected:
    };
    class PauseState:public State{
        public:
            PauseState(Player* player){
                mPlayer = player;
            }
            virtual void play(){
                cout << "resume" << endl;
                mPlayer->setState(mPlayer->getPlayingState());
            }
            virtual void pause(){
                cout << "Cur state is Paused" << endl;
            }
            virtual void stop(){
                cout << "Stop !!!" << endl;
                mPlayer->setState(mPlayer->getStopState());
            }
        private:
            Player* mPlayer;
        protected:
    };
    class StopState:public State{
        public:
            StopState(Player* player){
                mPlayer = player;
            }
            virtual void play(){
                cout << "Start play" << endl;
                mPlayer->setState(mPlayer->getPlayingState());
            }
            virtual void pause(){
                cout << "Cur state is Stoped" << endl;
            }
            virtual void stop(){
                cout << "Cur state is Stoped" << endl;                
            }
        private:
            Player* mPlayer;
        protected:
    };
    Player::Player(){
        mPlayingState = new PlayingState(this);
        mPauseState = new PauseState(this);
        mStopState = new StopState(this);
        mCurState = mStopState;
    }
    Player::~Player(){
        delete (PlayingState*)mPlayingState;
        delete (PauseState*)mPauseState;
        delete (StopState*)mStopState;
        mPlayingState = NULL;
        mPauseState = NULL;
        mStopState = NULL;
    }
    void Player::play(){
        mCurState->play();
    }
    void Player::pause(){
        mCurState->pause();
    }
    void Player::stop(){
        mCurState->stop();
    }
    void run(){
        Player player;
        player.play();
        player.stop();
        player.pause();
        player.stop();
        player.play();
        player.pause();
        player.play();
        player.stop();
    }
}
namespace PhoxyParttern{//代理模式
    class Ifactory{
        public:
            Ifactory(){}
            virtual void makeProduct()=0;
        private:
        protected:
    };
    class PhoneFactory:public Ifactory{
        public:
            PhoneFactory(){}
            virtual void makeProduct(){
                cout << "Make cell phone" << endl;
            }
        private:
        protected:
    };
    class FoxconnProxy:public Ifactory{
        public:
            FoxconnProxy(Ifactory* factory){
                mReal = factory;
            }
            virtual void makeProduct(){
                mReal->makeProduct();
            }
            
        private:
            Ifactory* mReal;
        protected:
    };
    void run(){

    }
}
namespace tmp{
    class Quackable{
        public:
            Quackable(){}
            virtual void quack()=0;
            operator Quackable*(){// is dangerous
                return this;
            }
        private:
        protected:
    };

    class MallardDuck:public Quackable{
        public:
            MallardDuck(){}
            virtual void quack(){
                cout << "Quack" << endl;
            }
        private:
        protected:
    };
    class RedheadDuck:public Quackable{
        public:
            RedheadDuck(){}
            virtual void quack(){
                cout<< "Quack" << endl;
            }
        private:
        protected:
    };
    class DuckCall:public Quackable{
        public:
            DuckCall(){}
            virtual void quack(){
                cout << "Kwak" << endl;
            }
        private:
        protected:
    };
    class RubberDuck:public Quackable{
        public:
            RubberDuck(){}
            virtual void quack(){
                cout << "Squack" << endl;
            }
        private:
        protected:
    };
    class Goose{
        public:
            Goose(){}
            virtual void honk(){
                cout << "Honk" << endl;
            }
        private:
        protected:
    };
    class GooseAdapter:public Quackable{
        public:
            GooseAdapter(Goose* goose){
                mGoose = goose;
            }
            virtual void quack(){
                mGoose->honk();
            }
        private:
            Goose* mGoose;
        protected:
    };
    class QuackCounter:public Quackable{         
        public:
            QuackCounter(Quackable* duck){
                mDuck = duck;               
            }  
            virtual void quack();
            static int getQuacks();
            Quackable* getDuck(){
                return mDuck;
            }
        private:
            Quackable* mDuck;
            static int numberOfQuacks;
        protected:
    };
    int QuackCounter::numberOfQuacks = 0;
    void QuackCounter::quack(){
        mDuck->quack();
        QuackCounter::numberOfQuacks++;
    }
    int QuackCounter::getQuacks(){
        return QuackCounter::numberOfQuacks;
    }

   
    class AbstractDuckFactory{
        public:
            AbstractDuckFactory(){}
            virtual Quackable* createMallardDuck()=0;
            virtual Quackable* createRedheadDuck()=0;
            virtual Quackable* createDuckCall()=0;
            virtual Quackable* createRubberDuck()=0;
        private: //page 509
        protected:
    };
    class DuckFactory:public AbstractDuckFactory{
        public:
            DuckFactory(){}
            ~DuckFactory(){
                #ifdef __FACTORY_CTRL_DELETE_PRODUCT
                for(int i=0;i<mQuackables.size();i++){
                    Quackable* ptr = mQuackables[i];
                    delete ptr;
                }
                #endif
            }
            virtual Quackable* createMallardDuck(){
                Quackable* quackable = new MallardDuck();
                #ifdef __FACTORY_CTRL_DELETE_PRODUCT                
                mQuackables.push_back(quackable);
                #endif
                return quackable;
            }
            virtual Quackable* createRedheadDuck(){
                Quackable* quackable = new RedheadDuck();
                #ifdef __FACTORY_CTRL_DELETE_PRODUCT                
                mQuackables.push_back(quackable);
                #endif
                return quackable;
            }
            virtual Quackable* createDuckCall(){
                Quackable* quackable = new DuckCall();
                #ifdef __FACTORY_CTRL_DELETE_PRODUCT
                mQuackables.push_back(quackable);
                #endif
                return quackable;
            }
            virtual Quackable* createRubberDuck(){
                Quackable* quackable = new RubberDuck();
                #ifdef __FACTORY_CTRL_DELETE_PRODUCT
                mQuackables.push_back(quackable);
                #endif
                return quackable;
            }
        private:
            #ifdef __FACTORY_CTRL_DELETE_PRODUCT
            vector<Quackable*> mQuackables;
            #endif
        protected:
    };
    class CountingDuckFactory:public AbstractDuckFactory{
        public:
            CountingDuckFactory(){}
            virtual Quackable* createMallardDuck(){
                return new QuackCounter(new MallardDuck());
            }
            virtual Quackable* createRedheadDuck(){
                return new QuackCounter(new RedheadDuck());
            }
            virtual Quackable* createDuckCall(){
                return new QuackCounter(new DuckCall());
            }
            virtual Quackable* createRubberDuck(){
                return new QuackCounter(new RubberDuck());
            }
        private:
            // vector<
        protected:
    };
    class DuckSimulator{
        public:
            DuckSimulator(){}
            void simulate(){
                // MallardDuck md;
                // RedheadDuck rd;
                // DuckCall dc;
                // RubberDuck rd1; 
                // Goose goose;
                // GooseAdapter ga(&goose);

                // simulate(QuackCounter(md));
                // simulate(QuackCounter(rd));
                // simulate(QuackCounter(dc));
                // simulate(QuackCounter(rd1));
                // simulate(ga);

                // cout << "The ducks quacked " ;
                // cout << QuackCounter::getQuacks() << " times" << endl;
                CountingDuckFactory factory;
                simulate(&factory);

            }
            void simulate(Quackable* duck){
                duck->quack();
            }
            void simulate(AbstractDuckFactory* factory){
                Quackable* mallardduck = factory->createMallardDuck();
                Quackable* redheadduck = factory->createRedheadDuck();
                Quackable* duckcall = factory->createDuckCall();
                Quackable* rubberduck = factory->createRubberDuck();
                Goose goose;
                Quackable* gooseduck = new GooseAdapter(&goose);

                cout << "Duck simulator: with abstract factory" << endl;

                simulate(mallardduck);
                simulate(redheadduck);
                simulate(duckcall);
                simulate(rubberduck);
                simulate(gooseduck);
                cout << "The ducks quacked" << QuackCounter::getQuacks() ;
                cout << " times" << endl;
                Quackable* ptr = nullptr;
                ptr = ((QuackCounter*)mallardduck)->getDuck();
                delete ptr;
                ptr = ((QuackCounter*)redheadduck)->getDuck();
                delete ptr;
                ptr = ((QuackCounter*)duckcall)->getDuck();
                delete ptr;
                ptr = ((QuackCounter*)rubberduck)->getDuck();
                delete ptr;
                delete mallardduck;
                delete redheadduck;
                delete duckcall;
                delete rubberduck;
                delete gooseduck;

            }
        private:
        protected:
    };
    void run(){
        DuckSimulator ds;
        ds.simulate();
    }
}


int main(int argc,char** argv){
    arg_count = argc;
    arg_arr = argv;
    tmp::run();
    system("pause");
    return 0;
}














