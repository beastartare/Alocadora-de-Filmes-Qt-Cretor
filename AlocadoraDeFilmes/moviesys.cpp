#include "moviesys.h"
#include "ui_moviesys.h"

MovieSys::MovieSys(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MovieSys)
{
    ui->setupUi(this);
}

MovieSys::~MovieSys()
{
    delete ui;
}

void MovieSys::on_pushButton_clicked()
{
    Cadastro janela;
    janela.setModal(true);
    janela.exec();
}


void MovieSys::on_pushButton_2_clicked()
{
    Acervo janela;
    janela.setModal(true);
    janela.exec();

}


