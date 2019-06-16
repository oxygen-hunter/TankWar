#ifndef MYTANK_H
#define MYTANK_H

#include "Tank.h"
#include "Bullet.h"
#include "QKeyEvent"
#include "QVector"
#include "QTimer"
#include "qobject.h"

class MyTank : public QObject, public Tank
{
      Q_OBJECT
public:
    MyTank();
    ~MyTank();
    void fire();
public slots:
    void move();
public:
    Bullet *bullet;
    QVector<Bullet *> bullet_vector;
public:
    QTimer *timer;
    bool up;        // 辅助方向标记上
    bool down;      // 辅助方向标记下
    bool left;      // 辅助方向标记左
    bool right;     // 辅助方向标记右
};

#endif // MYTANK_H
