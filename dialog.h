#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
    void on_pushButton_clicked();
    void on_L_Reco_clicked();
    void on_EXIT_clicked();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
