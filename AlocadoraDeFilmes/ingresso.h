#ifndef INGRESSO_H
#define INGRESSO_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSql>
#include <sstream>
#include "cliente.h"


using namespace std;

namespace Ui {
class Ingresso;
}

class Ingresso : public QDialog
{
    Q_OBJECT

public:
    explicit Ingresso(QWidget *parent = nullptr);
    ~Ingresso();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Ingresso *ui;
};

class Ing
{
protected:
    float m_valor;
    QString m_filme;
    QString m_data;
    int m_cadeira;
public:
    Ing(int cadeira, QString filme, QString data, float valor=20):m_cadeira(cadeira), m_filme(filme), m_data(data), m_valor(valor){};
    virtual QString ToString()=0;
    ~Ing(){};
};

class IngressoPadrao : public Ing
{
public:
    IngressoPadrao(int cadeira, QString filme, QString data):Ing(cadeira,filme,data){};
    QString ToString();

};
class IngressoVip: public Ing
{
private:
    QString m_beneficio;
public:
    IngressoVip(int cadeira, QString filme, QString data):Ing(cadeira,filme,data,40),m_beneficio("Vale pipoca 'M' e refri 600ml"){};
    QString ToString();
};

#endif // INGRESSO_H
