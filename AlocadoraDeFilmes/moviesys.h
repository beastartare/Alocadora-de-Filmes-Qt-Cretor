#ifndef MOVIESYS_H
#define MOVIESYS_H

#include <QDialog>
#include "cadastro.h"
#include "acervo.h"
#include "aluguel.h"

namespace Ui {
class MovieSys;
}

class MovieSys : public QDialog
{
    Q_OBJECT

public:
    explicit MovieSys(QWidget *parent = nullptr);
    ~MovieSys();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MovieSys *ui;
};

#endif // MOVIESYS_H
