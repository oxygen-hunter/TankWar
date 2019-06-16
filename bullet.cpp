#include "Bullet.h"
#include "QDebug"


Bullet::Bullet()
{

}


Bullet::Bullet(int x,int y,int verdict)
{
    this->x = x;
    this->y = y;
    this->dir = verdict;
    speed = 25;
    isAlive = true;
}


void Bullet::run()
{
    count = 3;
    while(isAlive)
    {
        Bullet::msleep(100);

        switch(dir)
        {
        case 0:
            y -= speed;
            break;
        case 1:
            y += speed;
            break;
        case 2:
            x -= speed;
            break;
        case 3:
            x += speed;
            break;
        }
        if(x<0||x>880||y<0||y>590)
        {
            isAlive = false;
        }
    }
}


Bullet::~Bullet()
{
}
