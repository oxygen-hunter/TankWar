#include "main_window.h"
#include "ui_main_window.h"

Main_Window::Main_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Main_Window)
{
    ui->setupUi(this);
}

Main_Window::~Main_Window()
{
    delete ui;
}
