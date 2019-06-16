#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include"Tank.h"
#include "QThread"
#include "QVector"
#include "Bullet.h"
#include "qdebug.h"
#include "PlayerTank.h"

class EnemyTank: public Tank, public QThread
{
public:
    EnemyTank();
    EnemyTank(int x, int y, int dir);
    void run();
public:
    Bullet *en_bullet;
    QVector<Bullet *> en_bullet_vector;
};

#endif // ENEMYTANK_H
