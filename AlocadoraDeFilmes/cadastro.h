#ifndef CADASTRO_H
#define CADASTRO_H

#include <QDialog>
#include <QSqlQuery>
#include <QtSql>

namespace Ui {
class Cadastro;
}

class Cadastro : public QDialog
{
    Q_OBJECT

public:
    explicit Cadastro(QWidget *parent = nullptr);
    ~Cadastro();

private slots:
    void on_pushButton_clicked();


private:
    Ui::Cadastro *ui;
};

#endif // CADASTRO_H
