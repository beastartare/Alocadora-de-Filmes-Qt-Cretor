#include "login.h"
#include "./ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);



    QSqlDatabase bancodedados = QSqlDatabase::addDatabase("QSQLITE","bancodedados");
    QString diretorio = QDir::homePath() + "/bandodedados.db";

    bancodedados.setDatabaseName(diretorio);

    bancodedados.open();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{

    QString usuario = ui->lineEdit->text();
    QString senha = ui->lineEdit_2->text();

    Cliente::instance()->m_username = usuario;

    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);

    if (usuario=="" || senha=="") {
        ui->label->setText("*campo obrigatório");
        ui->label_2->setText("*campo obrigatório");
        return;
    }

    if(!query.exec("SELECT * FROM usuario WHERE username= '"+usuario+"' AND senha= '"+senha+"'"))
    {
        if (!query.exec("CREATE TABLE IF NOT EXISTS usuario (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE NOT NULL, senha TEXT NOT NULL, ingresso TEXT)")) {
            qDebug() << "Erro ao criar tabela usuarios:" << query.lastError();
            return;
        }
        qDebug() << "Tabela criada ou já existe.";
        if (!query.exec("INSERT INTO usuario (username, senha) VALUES ('funcionario', '123')")) {
            qDebug() << "Erro ao inserir dados usuarios:" << query.lastError();
            return;
        }
         qDebug() << "Dados usuarios inseridos com sucesso.";
    }

    query.prepare("SELECT * FROM usuario WHERE id= ? AND username= '"+usuario+"' AND senha= '"+senha+"'");
    query.addBindValue(1);

    if(query.exec())
    {
        int cont=0;
        while(query.next())
        {
            cont++;
        }
        if(cont>0)
        {
            this->close();
            MovieSys janela;
            janela.setModal(true);
            janela.exec();
        }
        else
        {
            if(query.exec("SELECT * FROM usuario WHERE username= '"+usuario+"'"))
            {
                cont=0;
                while(query.next())
                {
                    cont++;
                }
                if(cont>0)
                {
                    if(query.exec("SELECT * FROM usuario WHERE senha= '"+senha+"'"))
                    {
                        cont=0;
                        while(query.next())
                        {
                            cont++;
                        }
                        if(cont>0)
                        {
                            this->close();
                            Cliente janela;
                            janela.setModal(true);
                            janela.exec();
                        }
                        else
                        {
                            ui->label->setText("senha incorreta");
                        }
                    }
                }
                else
                {
                    ui->label->setText("O usuário digitado não existe");
                }
            }

        }

    }
   QSqlDatabase::database("bancodedados").close();
}

void Login::on_pushButton_2_clicked()
{
    SignUp janela;
    janela.setModal(true);
    janela.exec();
}

