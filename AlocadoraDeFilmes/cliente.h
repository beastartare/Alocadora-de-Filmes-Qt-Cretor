#ifndef CLIENTE_H
#define CLIENTE_H

#include <QDialog>
#include <QSqlQuery>
#include <QtSql>
#include <vector>
#include <QSqlDatabase>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include "aluguel.h"
#include "perfil.h"
#include <utility>

using namespace std;

namespace Ui {
class Cliente;
}

class Cliente : public QDialog
{
    Q_OBJECT

public:
    explicit Cliente(QWidget *parent = nullptr);
    ~Cliente();
    void on_button_itemDoubleClicked(QString titulo);
    QString m_username;
    static Cliente *instance()
    {
        static Cliente instance;
        return &instance;
    };

private slots:
    void on_pushButton_clicked();

private:
    Ui::Cliente *ui;
};

#endif // CLIENTE_H
