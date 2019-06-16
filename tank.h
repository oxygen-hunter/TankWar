#ifndef TANK_H
#define TANK_H

class Tank
{
public:
    Tank();
    void fire();
public:
    int x;          // 纵坐标
    int y;          // 横坐标
    int dir;        // 坦克的方向
    int speed;      // 坦克的速度
    int hp;         // 坦克的生命值
    bool isAlive;   // 坦克的是否还活着
};

#endif // TANK_H
