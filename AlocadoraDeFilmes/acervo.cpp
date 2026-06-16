#include "acervo.h"
#include "ui_acervo.h"

Acervo::Acervo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Acervo)
{
    ui->setupUi(this);

    size_t i;

    QVector<QString> filmes;

    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);
    QSqlQuery q(db);

    if(query.exec("SELECT * FROM cadastrar_filmes"))
    {
        while(query.next())
        {
            filmes.push_back(query.value(0).toString());
        }
    }

    std::sort(filmes.begin(), filmes.end());

    auto last = std::unique(filmes.begin(), filmes.end());
    filmes.erase(last, filmes.end());

    for(i=0;i<filmes.size();i++)
    {
        ui->listWidget->addItem(filmes.at(i));
    }

}

Acervo::~Acervo()
{
    delete ui;
}

void Acervo::on_pushButton_clicked()
{
    QString titulo = ui->lineEdit->text();

    QVector<QString> filmes;
    size_t i;

    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);

    ui->listWidget->clear();

    if(query.exec("SELECT * FROM cadastrar_filmes WHERE filme='"+titulo+"'"))
    {
        while(query.next())
        {
            filmes.push_back(query.value(0).toString());
        }
    }

    std::sort(filmes.begin(), filmes.end());

    auto last = std::unique(filmes.begin(), filmes.end());
    filmes.erase(last, filmes.end());

    for(i=0;i<filmes.size();i++)
    {
        ui->listWidget->addItem(filmes.at(i));
    }
}

void Acervo::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Global::instance()->m_titulo = item->text();

    this->close();
    Filme janela;
    janela.setModal(true);
    janela.exec();
}



