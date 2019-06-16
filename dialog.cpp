#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "dialog_1.h"
#include "QPainter"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    MainWindow *m = new MainWindow();
    m->setWindowOpacity(0.90);
    m->show();  // 显示新的gaming窗口
}


void Dialog::on_L_Reco_clicked()
{
    Dialog_1 *d =new Dialog_1();
    d->show();

}


void Dialog::on_EXIT_clicked()
{
    this->close();
}
