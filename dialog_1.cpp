#include "dialog_1.h"
#include "ui_dialog_1.h"


Dialog_1::Dialog_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_1)
{
    ui->setupUi(this);
}


Dialog_1::~Dialog_1()
{
    delete ui;
}
