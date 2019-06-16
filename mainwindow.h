#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PlayerTank.h"
#include "Bullet.h"
#include "EnemyTank.h"
#include <time.h>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void collision_attack_player_enemy();      // 我方子弹和敌方坦克的碰撞检测
    void collision_bullet_player_enemy();      // 我方子弹和敌方子弹的碰撞检测
    void collision_tank_enemy_enemy();         // 敌方子弹和敌方子弹的碰撞检测
    void collision_bullet_enemy_player();      // 敌方子弹和我方坦克的碰撞检测
    void create_tank_enenmy();                 // 制造敌方坦克
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void paintEvent(QPaintEvent *event);       // 绘图
    void keyPressEvent(QKeyEvent *);           // 键盘响应
    void keyReleaseEvent(QKeyEvent *);         // 键盘松开
    void mousePressEvent(QMouseEvent *);       // 鼠标响应
    void PaintAll(int x,int y,QString a,int target_x,int target_y,int source_x,int source_y);
public:
    MyTank  myTank;
    Bullet  bullet;
    Bullet  *bul1;
    EnemyTank enemytank;
    QVector<EnemyTank *> vector_enemy;

    QTimer *timer;
    QTimer *timeradd;

    int getx;             // 用于子弹的绘制
    int gety;
    QString str_score;    // 得分控制
    int int_score;
    QString str_life;     // 坦克生命控制
    int enemy_size;       // 敌方坦克数量
    int bullet_size;
private slots:
    void on_EXIT_clicked();
    void on_L_Request_destroyed();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
