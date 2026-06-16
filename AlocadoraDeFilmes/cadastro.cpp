#include "cadastro.h"
#include "ui_cadastro.h"
#include <QCalendarWidget>
#include <QVBoxLayout>

Cadastro::Cadastro(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Cadastro)
{
    ui->setupUi(this);
}

Cadastro::~Cadastro()
{
    delete ui;
}

void Cadastro::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString data = ui->dateTimeEdit->text();
    QString imagem = ui->lineEdit_2->text();
    int i;

    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);

    if(!query.exec("INSERT INTO cadastrar_filmes (filme, data, image) VALUES ('"+name+"', '"+data+"', '"+imagem+"')"))
    {
        if (!query.exec("CREATE TABLE IF NOT EXISTS cadastrar_filmes (filme TEXT NOT NULL, data TEXT NOT NULL, image BLOB NOT NULL)")) {
            qDebug() << "Erro ao criar tabela filmes:" << query.lastError();
            return;
        }
        qDebug() << "Tabela filmes criada ou já existe.";
        if (!query.exec("INSERT INTO cadastrar_filmes (filme, data, image) VALUES ('"+name+"', '"+data+"', '"+imagem+"')")){
            qDebug() << "Erro ao inserir dados filmes:" << query.lastError();
            return;
        }

        qDebug() << "Dados filmes inseridos com sucesso.";
    }
    ui->label_4->setText("Filme cadastrado com sucesso!");
    if(!query.exec("SELECT * FROM cadeiras_disponíveis"))
    {
        if (!query.exec("CREATE TABLE IF NOT EXISTS cadeiras_disponíveis (filme TEXT NOT NULL, data TEXT NOT NULL, cadeira INTEGER NOT NULL )"))
        {
            qDebug() << "Erro ao criar tabela cadeiras:" << query.lastError();
            return;
        }
    }
    for(i=1;i<30;i++)
    {
        query.prepare("INSERT INTO cadeiras_disponíveis (filme, data, cadeira) VALUES ('"+name+"', '"+data+"', :cad)");
        query.bindValue(":cad",i);
        if(!query.exec())
        {
            qDebug() << "Erro ao inserir cadeira dados:" << query.lastError();
            return;
        }
    }

}

