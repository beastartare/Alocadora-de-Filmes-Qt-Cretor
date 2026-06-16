#include "cliente.h"
#include "ui_cliente.h"

Cliente::Cliente(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Cliente)
{
    ui->setupUi(this);

    QVector<pair<QString,QString>>filmes;
    size_t i;
    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);


    if(query.exec("SELECT * FROM cadastrar_filmes"))
    {
        while(query.next())
        {
            filmes.push_back(make_pair(query.value(0).toString(),query.value(2).toString()));
        }
    }

    std::sort(filmes.begin(), filmes.end());

    auto last = std::unique(filmes.begin(), filmes.end());
    filmes.erase(last, filmes.end());

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout();
    scrollWidget->setLayout(scrollLayout);


    ui->scrollArea->setWidget(scrollWidget);

    for(i=0;i<filmes.size();i++)
    {
        QPushButton *button = new QPushButton();
        QPixmap pixmap(filmes.at(i).second);
        pixmap = pixmap.scaled(138, 204, Qt::KeepAspectRatio);  // Redimensiona o poster
        scrollLayout->addWidget(button);
        button->setIcon(pixmap);
        button->setIconSize(pixmap.size());
        button->setText(filmes.at(i).first);
        QString titulo = button->text();
        connect(button, &QPushButton::clicked, [this,titulo]()
                {on_button_itemDoubleClicked(titulo);});
    }
}

void Cliente::on_button_itemDoubleClicked(QString titulo)
{
    Global::instance()->m_titulo = titulo;
    Aluguel janela;
    janela.setModal(true);
    janela.exec();
}
Cliente::~Cliente()
{
    delete ui;
}

void Cliente::on_pushButton_clicked()
{
    if(ui->comboBox->currentText()=="Perfil")
    {
        Perfil janela;
        janela.setModal(true);
        janela.exec();
    }
}

