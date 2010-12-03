#include "configure.h"
#include "ui_configure.h"
<<<<<<< HEAD

///CONSTRUCTOR:displays the values in settings to config menu
Configure::Configure(QWidget *parent) :
=======
#include "gitcommand.h"
Configure::Configure(QWidget *parent, GitCommand *gitCommand) :
>>>>>>> hef/master
    QDialog(parent),
    ui(new Ui::Configure),
    gitCommand(gitCommand)
{
    ui->setupUi(this);
    ui->gitPathLineEdit->setText(settings.value("gitPath").toString());
<<<<<<< HEAD
    ui->authorNameLineEdit->setText(settings.value("authorName").toString());
    ui->defaultRepoLineEdit->setText(settings.value("defaultRepo").toString());
    ui->authorEmailLineEdit->setText(settings.value("authorEmail").toString());
}
=======
    QStringList name = gitCommand->run(QStringList() << "config" << "user.name");
    if(name.size() > 0)
        ui->nameLineEdit->setText(name[0]);
    QStringList email = gitCommand->run(QStringList() << "config" << "user.email");
    if(email.size() > 0)
        ui->emailLineEdit->setText(email[0]);
>>>>>>> hef/master

}
Configure::~Configure()
{
    delete ui;
}
void Configure::accept()
{
    settings.setValue("gitPath",ui->gitPathLineEdit->text());
<<<<<<< HEAD
    settings.setValue("authorName",ui->authorNameLineEdit->text());
    settings.setValue("authorEmail",ui->authorEmailLineEdit->text());
    settings.setValue("defaultRepo",ui->defaultRepoLineEdit->text());
=======
    gitCommand->run(QStringList() << "config" << "user.name" << ui->nameLineEdit->text());
    gitCommand->run(QStringList() << "config" << "user.email" << ui->emailLineEdit->text());
>>>>>>> hef/master
    this->hide();
}
void Configure::reject()
{
    ui->gitPathLineEdit->setText(settings.value("gitPath").toString());
<<<<<<< HEAD
    ui->authorNameLineEdit->setText(settings.value("authorName").toString());
    ui->authorEmailLineEdit->setText(settings.value("authorEmail").toString());
    ui->defaultRepoLineEdit->setText(settings.value("defaultRepo").toString());
=======
    QStringList name = gitCommand->run(QStringList() << "config" << "user.name");
    if(name.size() > 0)
        ui->nameLineEdit->setText(name[0]);
    QStringList email = gitCommand->run(QStringList() << "config" << "user.email");
    if(email.size() > 0)
        ui->emailLineEdit->setText(email[0]);
>>>>>>> hef/master
    this->hide();
}
