#include "PlayerTank.h"
#include "QThread"
#include "QDebug"


MyTank::MyTank()
{
    x = 400;
    y = 480.0;
    dir = 0;
    speed = 15;
    hp = 5;
    isAlive = true;
    up = false;
    down = false;
    left = false;
    right = false;

    timer = new QTimer;                   //新建一个定时器来定时刷新图

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));           //这个定时器只是作用与数据的更新
}


MyTank::~MyTank()
{
  delete timer;
}


void MyTank::move()
{
    if(up==true&&down!=true&&left!=true&&right!=true)
    {
        if(x<0||y<10)   // 上移越界
        {
            y = y;
        }
        else
        {
            y -= speed;
        }
        dir=0;
        up=false;
    }
    else if(up!=true&&down==true&&left!=true&&right!=true)
    {
        if(x>850||y>540)   // 下移越界
        {
            y = y;
        }
        else
        {
            y += speed;
        }
        dir=1;
        down=false;
    }
    else if(up!=true&&down!=true&&left==true&&right!=true)
    {
        if(x<10)   // 左移越界
        {
            x = x;
        }
        else
        {
            x -= speed;
        }
        dir=2;
        left=false;
    }
    else if(up!=true&&down!=true&&left!=true&&right==true)
    {
        if(x>840)   // 右移越界
        {
            x = x;
        }
        else
        {
            x += speed;
        }
        dir=3;
        right=false;
    }
}


void MyTank::fire()
{

    if(isAlive == true)
    {
        switch(dir)
        {
        case 0:
            bullet = new Bullet(x+20,y-7,dir);
            bullet_vector.append(bullet);
            break;
        case 1:
            bullet = new Bullet(x+20,y+50,dir);
            bullet_vector.append(bullet);
            break;
        case 2:
            bullet = new Bullet(x-7,y+20,dir);
            bullet_vector.append(bullet);
            break;
        case 3:
            bullet = new Bullet(x+50,y+20,dir);
            bullet_vector.append(bullet);
            break;
        }
        bullet->start();
    }
}
