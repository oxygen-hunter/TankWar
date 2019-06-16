#include "EnemyTank.h"
#include "ctime"
#include "QTextCodec"


EnemyTank::EnemyTank()
{

}


EnemyTank::EnemyTank(int x, int y, int dir)
{

    this->x = x;
    this->y =y;
    this->dir =dir;
    isAlive = true;
    speed = 5;

}


void EnemyTank::run()
{
    int movnum=10;
    while(isAlive)
    {
        srand(clock());
        EnemyTank::msleep(65);         // 睡眠
        dir = qrand()%4;               // 随机产生敌方坦克的方向
        switch(dir)
        {
        case 0:
            for(int i=0;i<movnum;i++)
            {
                if(dir==0)
                {
                    EnemyTank::msleep(70);
                    if(y>5&&dir==0)
                    {
                        y -= speed;
                    }
                    else{
                        dir=1;
                        break;
                    }
                }

            }
            break;
        case 1:
            for(int i=0;i<movnum;i++)
            {
                if(dir==1)
                {
                    EnemyTank::msleep(70);
                    if(y<550)
                    {
                        y += speed;
                    }
                    else {
                        dir=0;
                        break;
                    }
                }
            }
            break;
        case 2:
            for(int i=0;i<movnum;i++)
            {
                if(dir==2)
                {
                    EnemyTank::msleep(70);
                    if(x>10)
                    {
                        x -= speed;
                    }
                    else
                    {
                        dir=3;
                        break;
                    }
                }
            }
            break;
        case 3:
            for(int i=0;i<movnum;i++)
            {
                if(dir==3)
                {
                    EnemyTank::msleep(70);
                    if(x<840)
                    {
                        x +=  speed;
                    }
                    else{
                        dir=2;
                        break;
                    }
                }
            }
            break;
        }
    }
}
