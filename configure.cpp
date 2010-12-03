#include "configure.h"
#include "ui_configure.h"

Configure::Configure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configure)
{
    ui->setupUi(this);
    ui->gitPathLineEdit->setText(settings.value("gitPath").toString());
    ui->authorNameLineEdit->setText(settings.value("authorName").toString());
    ui->authorEmailLineEdit->setText(settings.value("authorEmail").toString());
}

Configure::~Configure()
{
    delete ui;
}
void Configure::accept()
{
    settings.setValue("gitPath",ui->gitPathLineEdit->text());
    settings.setValue("authorName",ui->authorNameLineEdit->text());
    settings.setValue("authorEmail",ui->authorEmailLineEdit->text());
    this->hide();
}
void Configure::reject()
{
    ui->gitPathLineEdit->setText(settings.value("gitPath").toString());
    ui->authorNameLineEdit->setText(settings.value("authorName").toString());
    ui->authorEmailLineEdit->setText(settings.value("authorEmail").toString());
    this->hide();
}
