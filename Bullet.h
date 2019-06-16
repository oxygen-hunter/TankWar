#ifndef BULLET_H
#define BULLET_H

#include "QThread"

class Bullet : public QThread
{
public:
    Bullet();
    Bullet(int x,int y,int dir);
    void run();
    ~Bullet();
public:
    int x;        // 纵坐标
    int y;        // 横坐标
    int count;    // 武器子弹的数量
    int dir;      // 判断子弹的方向
    int speed;    // 子弹的速度
    bool isAlive; // 是否存活，决定是否显示
};

#endif // BULLET_H
