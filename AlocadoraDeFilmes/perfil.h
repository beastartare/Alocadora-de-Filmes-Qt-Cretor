#ifndef PERFIL_H
#define PERFIL_H

#include <QDialog>
#include <QSql>
#include <QSqlQuery>
#include "login.h"

namespace Ui {
class Perfil;
}

class Perfil : public QDialog
{
    Q_OBJECT

public:
    explicit Perfil(QWidget *parent = nullptr);
    ~Perfil();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Perfil *ui;
};

#endif // PERFIL_H
