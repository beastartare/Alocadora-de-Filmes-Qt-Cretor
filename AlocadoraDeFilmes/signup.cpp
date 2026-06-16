#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);

}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_clicked()
{
    QString usuario = ui->lineEdit->text();
    QString senha = ui->lineEdit_2->text();

    if (usuario=="" || senha=="") {
        ui->label->setText("*campo obrigatório");
        ui->label_2->setText("*campo obrigatório");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);

    if (!query.exec("INSERT INTO usuario (username, senha) VALUES ('"+usuario+"', '"+senha+"')")) {
        ui->label->setText("o usuário digitado já existe");
        return;
    }

    this->close();

}

