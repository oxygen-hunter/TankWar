#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "qbitmap.h"
#include "QKeyEvent"
#include "qdebug.h"
#include "QDebug"
#include "QMessageBox"
#include "iterator"
#include "QLabel"
#include "math.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enemy_size =40;
    int_score=0;
    ui->L_Score->setText("     0");
    //ui->L_Request->setText("     1");
    ui->L_Life->setText("   5");
    bullet_size=5;

    for(int ecnt=1;ecnt<6;ecnt++)
    {
        // 初始出生6个敌方坦克
        srand(clock());
        int direct = qrand()%4;
        EnemyTank *entank = new EnemyTank(ecnt*150,ecnt*50,direct);
        MainWindow::vector_enemy.append(entank);
        entank->start();
        // 在创建的敌方坦克中创建其子弹
        bul1 = new Bullet(entank->x+20,entank->y+10,entank->dir);
        entank->en_bullet_vector.append(bul1);
        // 子弹开始运动
        bul1->start();
    }

    // 设置定时器用来不停地更新界面
    timer = new QTimer;

    // 连接处理函数
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));                           // 数据更新
    connect(timer,SIGNAL(timeout()),this,SLOT(collision_tank_enemy_enemy()));       // 敌人子弹-敌人子弹
    connect(timer,SIGNAL(timeout()),this,SLOT(collision_bullet_enemy_player()));    // 敌人子弹-我方子弹
    connect(timer,SIGNAL(timeout()),this,SLOT(collision_attack_player_enemy()));    // 敌人子弹-我方坦克
    connect(timer,SIGNAL(timeout()),this,SLOT(collision_bullet_player_enemy()));    // 我方子弹-敌人坦克
    connect(timer,SIGNAL(timeout()),this,SLOT(mboom(bool)));                        //
    connect(timer,SIGNAL(timeout()),this,SLOT(myshock()));                          //
    connect(timer,SIGNAL(timeout()),this,SLOT(create_tank_enenmy()));               // 制造敌人坦克

    // 每隔80毫秒钟重新绘制一下
    timer->start(80);

    // 绘制坦克大战的地图
    QPixmap pixmap(":/new/prefix1/image/gamemap2.jpg");
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(pixmap));
    setPalette(palette);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    if(myTank.isAlive==true)
    {
        // 绘制我方坦克
        switch(myTank.dir)
        {
        case 0:
        {
            QString qs=":/new/prefix1/image/MyTank_U.png";
            PaintAll(myTank.x,myTank.y,qs,50,50,50,50);
            break;
        }
        case 1:
        {
            QString qs=":/new/prefix1/image/MyTank_D.png";
            PaintAll(myTank.x,myTank.y,qs,50,50,50,50);
            break;
        }
        case 2:
        {
            QString qs=":/new/prefix1/image/MyTank_L.png";
            PaintAll(myTank.x,myTank.y,qs,50,50,50,50);
            break;
        }
        case 3:
        {
            QString qs=":/new/prefix1/image/MyTank_R.png";
            PaintAll(myTank.x,myTank.y,qs,50,50,50,50);
            break;
        }
        }

        // 绘制我方坦克的子弹
        for(int bcnt=0 ; bcnt<myTank.bullet_vector.size() ;bcnt++)
        {
            Bullet *bu = myTank.bullet_vector.at(bcnt);
            if(bu->count!=0&& bu->isAlive==true)
            {
                QString qs=":/new/prefix1/image/Bullet.png";
                PaintAll(bu->x,bu->y,qs,10,10,10,10);
            }
            if( bu->isAlive==false)
            {
                myTank.bullet_vector.remove(bcnt);
            }
        }
    }

    else
    {
        for(int boompic=0;boompic<20;boompic++)
        {
            if(0<=boompic&&boompic<=2)
            {
                QString qss=":/new/prefix1/image/Bomb_1";
                PaintAll(myTank.x,myTank.y,qss,60,60,60,60);
            }
            if(15<=boompic && boompic<=19)
            {
                QString qs=":/new/prefix1/image/Bomb_2";
                PaintAll(myTank.x,myTank.y,qs,60,60,60,60);
            }
        }
    }

    //绘制敌人坦克
    for(int ecnt=0; ecnt<vector_enemy.size();ecnt++)
    {
        EnemyTank *etank=MainWindow::vector_enemy.at(ecnt);
        getx = etank->x;
        gety = etank->y;

        if(etank->isAlive==true)
        {
            switch(etank->dir)
            {
            case 0:
            {
                QString enemy=":/new/prefix1/image/EnemyTank_U.png";
                PaintAll(etank->x,etank->y,enemy,50,50,50,50);
                break;
            }
            case 1:
            {
                QString enemy=":/new/prefix1/image/EnemyTank_D.png";
                PaintAll(etank->x,etank->y,enemy,50,50,50,50);
                break;
            }
            case 2:
            {
                QString enemy=":/new/prefix1/image/EnemyTank_L.png";
                PaintAll(etank->x,etank->y,enemy,50,50,50,50);
                break;
            }
            case 3:
            {
                QString enemy=":/new/prefix1/image/EnemyTank_R.png";
                PaintAll(etank->x,etank->y,enemy,50,50,50,50);
                break;
            }
            }

            for(int bcnt=0;bcnt<etank->en_bullet_vector.size();bcnt++)
            {
                Bullet *bul11 = etank->en_bullet_vector.at(bcnt);
                if(bul11->isAlive==true)
                {
                    QString enemy_bu=":/new/prefix1/image/eBullet.jpg";
                    PaintAll(bul11->x,bul11->y,enemy_bu,10,10,10,10);
                }
                else{
                    etank->en_bullet_vector.remove(bcnt);
                }
                if(etank->isAlive)
                {
                    while(etank->en_bullet_vector.size()<1)  // 控制敌人子弹的数量
                    {
                        switch(etank->dir)
                        {
                        case 0:
                            bul1 = new Bullet(etank->x+20,etank->y-10,etank->dir);
                            etank->en_bullet_vector.append(bul1);
                            break;
                        case 1:
                            bul1 = new Bullet(etank->x+20,etank->y+60,etank->dir);
                            etank->en_bullet_vector.append(bul1);
                            break;
                        case 2:
                            bul1 = new Bullet(etank->x-10,etank->y+20,etank->dir);
                            etank->en_bullet_vector.append(bul1);
                            break;
                        case 3:
                            bul1 = new Bullet(etank->x+60,etank->y+20,etank->dir);
                            etank->en_bullet_vector.append(bul1);
                            break;
                        }
                        bul1->start();
                    }
                }
            }
        }

        else
        {
            for(int boompic = 0; boompic < 20; boompic++)
            {
                if(0 <= boompic && boompic <= 2)
                {
                    QString qss=":/new/prefix1/image/Bomb_1";
                    PaintAll(getx,gety,qss,60,60,60,60);
                }
                if(15 <= boompic && boompic <= 19)
                {
                    QString qs=":/new/prefix1/image/Bomb_2";
                    PaintAll(getx,gety,qs,60,60,60,60);
                }
            }
            MainWindow::vector_enemy.remove(ecnt);
        }
    }
}


void MainWindow::keyPressEvent(QKeyEvent *k)
{
    if(k->key() == Qt::Key_W)     // 判断按键按上
    {
        myTank.up=true;
        myTank.move();
    }
    else if(k->key()==Qt::Key_S ) // 判断按键按下
    {
        myTank.down=true;
        myTank.move();
    }
    else if(k->key()==Qt::Key_A ) // 判断按键按左
    {
        myTank.left=true;
        myTank.move();
    }
    else if (k->key()==Qt::Key_D) // 判断按键按右
    {
        myTank.right=true;
        myTank.move();
    }

    if(k->key()== Qt::Key_J )     // 判断开火
    {
        if(myTank.bullet_vector.size()<bullet_size)
        {
            myTank.fire();
        }
    }
    this->repaint();
}


void MainWindow::keyReleaseEvent(QKeyEvent *k)
{
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(myTank.bullet_vector.size()<bullet_size)
    {
        myTank.fire();
    }
}


void MainWindow::PaintAll(int x,int y,QString a,int target_x,int target_y,int source_x,int source_y )
{
    QRectF target(x,y, target_x, target_y);
    QRectF source(0, 0, source_x, source_y);
    QImage image(a);
    QPainter painter(this);
    painter.drawImage(target, image, source);
}


void MainWindow::collision_attack_player_enemy()
{
    if(myTank.isAlive)
    {
        for(int bcnt=0;bcnt<myTank.bullet_vector.size();bcnt++)
        {
            Bullet *mbu=myTank.bullet_vector.at(bcnt);
            if(mbu->isAlive==true)
            {
                for(int ecnt=0;ecnt<MainWindow::vector_enemy.size();ecnt++)
                {
                    EnemyTank *etank = MainWindow::vector_enemy.at(ecnt);
                    if(etank->isAlive==true)
                    {
                        if(mbu->x>=etank->x && mbu->x<=(etank->x+50)&& mbu->y>=etank->y && mbu->y<=(etank->y+50))
                        {
                            etank->isAlive=false;
                            mbu->isAlive=false;
                            int_score+=500;
                            str_score =" "+ QString::number(int_score,10);
                            ui->L_Score->setText(str_score);
                        }
                    }
                }
            }
        }
    }
}


void MainWindow::collision_bullet_player_enemy()
{
    if(myTank.isAlive)
    {
        for(int mbcnt=0;mbcnt<myTank.bullet_vector.size();mbcnt++)
        {
            Bullet *mbu=myTank.bullet_vector.at(mbcnt);
            if(mbu->isAlive==true)
            {
                for(int ecnt=0;ecnt<MainWindow::vector_enemy.size();ecnt++)
                {
                    EnemyTank *ent = MainWindow::vector_enemy.at(ecnt);
                    if(ent->isAlive==true)
                    {
                        for(int ebcnt=0;ebcnt<ent->en_bullet_vector.size();ebcnt++)
                        {
                            Bullet *enbu=ent->en_bullet_vector.at(ebcnt);

                            if(enbu->isAlive==true)
                            {
                                if((abs(mbu->x-enbu->x)<=15)&&(abs(abs(mbu->y-enbu->y)<=15)))
                                {
                                    mbu->isAlive=false;
                                    enbu->isAlive=false;
                                    int_score+=500;
                                    str_score =" "+ QString::number(int_score,10);
                                    ui->L_Score->setText(str_score);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


void MainWindow::collision_tank_enemy_enemy()
{
    for(int ecnt1=0;ecnt1< MainWindow::vector_enemy.size();ecnt1++)
    {
        EnemyTank *entank1 = MainWindow::vector_enemy.at(ecnt1);
        if(entank1->isAlive==true)
        {
            for(int ecnt2=0;ecnt2<MainWindow::vector_enemy.size();ecnt2++)
            {
                if(ecnt2==ecnt1)
                {
                    continue;
                }
                else
                {
                    EnemyTank *entank2 = MainWindow::vector_enemy.at(ecnt2);
                    if(entank1->isAlive==true)
                    {
                        if(((abs(entank1->x-entank2->x)<=50) && (abs(entank1->y-entank2->y)<=50)) || ((abs(entank2->x-entank1->x)<=50) && (abs(entank2->y-entank1->y)<=50)))
                        {
                            entank1->speed=0;
                            entank2->speed=0;
                            switch(entank2->dir)
                            {
                            case 0:entank2->y+=8;entank2->dir=1;entank2->speed=10;break;
                            case 1:entank2->y-=8;entank2->dir=0;entank2->speed=10;break;
                            case 2:entank2->x+=8;entank2->dir=3;entank2->speed=10;break;
                            case 3:entank2->x-=8;entank2->dir=2;entank2->speed=10;break;
                            }
                            switch(entank1->dir)
                            {
                            case 0:entank1->y+=8;entank1->dir=1; entank1->speed=10;break;
                            case 1:entank1->y-=8;entank1->dir=0; entank1->speed=10;break;
                            case 2:entank1->x+=8;entank1->dir=3; entank1->speed=10;break;
                            case 3:entank1->x-=8;entank1->dir=2; entank1->speed=10;break;
                            }
                        }
                        else
                        {
                            entank1->speed=10;
                            entank2->speed=10;
                        }
                    }
                }
            }
        }
    }
}


void MainWindow::collision_bullet_enemy_player()
{
    if(myTank.isAlive)
    {
        for(int ecnt=0; ecnt<MainWindow::vector_enemy.size(); ecnt++)
        {
            EnemyTank *entank = MainWindow::vector_enemy.at(ecnt);
            if(entank->isAlive==true)
            {
                for(int ebcnt=0;ebcnt<entank->en_bullet_vector.size();ebcnt++)
                {
                    Bullet *enbu = entank->en_bullet_vector.at(ebcnt);
                    if(enbu->isAlive==true)
                    {
                        if(myTank.x<= enbu->x && myTank.x+50>= enbu->x &&myTank.y<= enbu->y+5 &&myTank.y+50>= enbu->y)
                        {
                            enbu->isAlive=false;
                            if(myTank.hp<=1)
                            {
                                ui->L_Life->setText("  0");
                                myTank.isAlive=false;
                                enbu->isAlive=false;
                                QMessageBox::information(this,"Failure","You Lose the game!\n\nSee you next time...");
                                timer->stop();
                                ui->EXIT->setEnabled(true);
                            }
                            else
                            {
                                myTank.hp-=1;
                                str_life =" "+ QString::number(myTank.hp,10);
                                ui->L_Life->setText("   "+str_life);
                            }
                        }
                    }
                }
            }
        }
    }
}


void MainWindow::create_tank_enenmy()
{
    if(vector_enemy.size()!=0)
    {
        if(vector_enemy.size()<4 &&enemy_size>=30)
        {
            // 随机刷新出生点
            srand(clock());
            int xx = qrand()%800;
            int yy = qrand()%500;

            EnemyTank *enta = new EnemyTank(xx,yy,1);
            MainWindow::vector_enemy.append(enta);
            enta->start();

            //在创建的敌方坦克中创建其子弹
            bul1 = new Bullet(enta->x+20,enta->y+10,enta->dir);
            enta->en_bullet_vector.append(bul1);

            bul1->start();
            enemy_size--;
        }
        else if(vector_enemy.size()<7 &&enemy_size<30 &&enemy_size>20)
        {
            // 随机刷新出生点
            srand(clock());
            int xx = qrand()%840;

            EnemyTank *enta = new EnemyTank(xx,0,1);
            MainWindow::vector_enemy.append(enta);
            enta->start();

            //在创建的敌方坦克中创建其子弹
            bul1 = new Bullet(enta->x+20,enta->y+10,enta->dir);
            enta->en_bullet_vector.append(bul1);

            bul1->start();
            enemy_size--;
        }
        else if(vector_enemy.size()<9 && enemy_size<=20&& enemy_size>0)
        {
            // 随机刷新出生点
            srand(clock());
            int xx = qrand()%840;

            EnemyTank *enta = new EnemyTank(xx,0,1);
            MainWindow::vector_enemy.append(enta);
            enta->start();

            //在创建的敌方坦克中创建其子弹
            bul1 = new Bullet(enta->x+20,enta->y+10,enta->dir);
            enta->en_bullet_vector.append(bul1);

            bul1->start();
            enemy_size--;
        }
    }
    else{
        QMessageBox::information(this,"Win","You kill all enemy!\n\nGood job!");
        timer->stop();
        delete ui;
    }
}


void MainWindow::on_EXIT_clicked()
{
    this->close();
}


void MainWindow::on_L_Request_destroyed()
{

}
