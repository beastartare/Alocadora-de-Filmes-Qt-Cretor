#ifndef FILME_H
#define FILME_H

#include <QDialog>
#include <QSqlQuery>
#include <QtSql>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "acervo.h"
#include "cliente.h"

namespace Ui {
class Filme;
}

class Filme : public QDialog
{
    Q_OBJECT

public:
    explicit Filme(QWidget *parent = nullptr);
    ~Filme();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Filme *ui;
};

#endif // FILME_H
