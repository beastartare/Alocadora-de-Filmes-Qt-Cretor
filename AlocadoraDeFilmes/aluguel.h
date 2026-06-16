#ifndef ALUGUEL_H
#define ALUGUEL_H

#include <QDialog>
#include <QSqlQuery>
#include <QtSql>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "acervo.h"
#include "ingresso.h"

namespace Ui {
class Aluguel;
}

class Aluguel : public QDialog
{
    Q_OBJECT

public:
    explicit Aluguel(QWidget *parent = nullptr);
    ~Aluguel();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Aluguel *ui;
};

#endif // ALUGUEL_H
