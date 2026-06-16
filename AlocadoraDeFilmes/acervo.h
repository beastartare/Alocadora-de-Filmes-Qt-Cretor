#ifndef ACERVO_H
#define ACERVO_H

#include <QDialog>
#include <QSqlQuery>
#include <QtSql>
#include <QListWidgetItem>
#include <vector>
#include "filme.h"

namespace Ui {
class Acervo;

}

class Acervo : public QDialog
{
    Q_OBJECT

public:
    explicit Acervo(QWidget *parent = nullptr);
    ~Acervo();

private slots:

    void on_pushButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);


private:

    Ui::Acervo *ui;
};

class Global{

public:

    QString last_item, m_data, m_titulo;

    static Global* instance()
    {
        static Global instance;
        return &instance;
    }

private:
    // Construtor privado para evitar criação de instâncias externas
    Global() {}
    Global(const Global&) = delete;
    Global& operator=(const Global&) = delete;
};

#endif // ACERVO_H
