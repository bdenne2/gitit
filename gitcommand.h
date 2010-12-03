#ifndef GITCOMMAND_H
#define GITCOMMAND_H


#include <QObject>
#include <QStringList>
#include <QString>
#include <QProcess>
/**
* This class is responsible for all interactions with the git command, and therefor the git databases.
*/
class GitCommand : public QObject
{
    Q_OBJECT
public:
    explicit GitCommand(QObject *parent = 0);
    ~GitCommand();
    ///runs git with given args catenated with default args
    void run(QStringList arguments);
    ///gets gits current status on changed files
    void status();
    ///removes ignored files from the git status list
    void lsIgnored();
    ///stages the file
    void add(QString filename);
    ///gets the log from git and emits output
    void log();
    ///sets the repos author to whats in the settings
    void author();

private:
    QStringList* defaultArgs;
    QString repo;
    QProcess* gitRunProcess;
    QProcess* gitStatusProcess;
    QProcess* gitSetAuthorProcess;
    QProcess* gitLSIgnoredProcess;
    QProcess* gitLogProcess;
    QProcess* gitAddProcess;

signals:
    void status(QStringList files);
    void lsIgnored(QStringList files);
    void log(QString log);

public slots:
    void setRepo(QString repo);
    void setAuthor();

private slots:
    void statusOutput(int exitCode, QProcess::ExitStatus exitStatus);
    void lsIgnoredOutput(int exitCode, QProcess::ExitStatus exitStatus);
    void logOutput(int exitCode, QProcess::ExitStatus exitStatus);
    void authorOutput(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // GITCOMMAND_H
