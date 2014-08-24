#include "gitcommand.h"
#include <QStringList>
#include <QSettings>
#include <QProcess>

GitCommand::GitCommand(QObject *parent) :
    QObject(parent),
    defaultArgs(new QStringList),
    repo(),
    gitRunProcess(new QProcess),
    gitStatusProcess(new QProcess),
    gitSetAuthorProcess(new QProcess),
    gitLSIgnoredProcess(new QProcess),
    gitLogProcess(new QProcess),
    gitAddProcess(new QProcess),
    gitBranchListProcess(new QProcess)
{
    connect(gitStatusProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(statusOutput(int, QProcess::ExitStatus)));
    connect(gitSetAuthorProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(authorOutput(int, QProcess::ExitStatus)));
    connect(gitLSIgnoredProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(lsIgnoredOutput(int, QProcess::ExitStatus)));
    connect(gitLogProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(logOutput(int, QProcess::ExitStatus)));
}
GitCommand::~GitCommand()
{
    delete defaultArgs;
    delete gitRunProcess;
    delete gitStatusProcess;
    delete gitSetAuthorProcess;
    delete gitLSIgnoredProcess;
    delete gitAddProcess;
    delete gitLogProcess;
    delete gitBranchListProcess;
}
QStringList GitCommand::run(QStringList arguments)
{
    QSettings settings;
    QString proc = settings.value("gitPath").toString();
    QStringList args = *defaultArgs;
    args << arguments;
    gitRunProcess->start(proc, args);
    gitRunProcess->waitForFinished(3000);
    QByteArray result = gitRunProcess->readAll();
    QString resultString(result);
    QStringList resultList = resultString.split('\n',QString::SkipEmptyParts);
    return resultList;
}
void GitCommand::status()
{
    QSettings settings;
    QString proc = settings.value("gitPath").toString();
    QStringList args = *defaultArgs;
    args << "status" << "--porcelain";
    gitStatusProcess->start(proc, args);

}
void GitCommand::statusOutput(int exitCode, QProcess::ExitStatus exitStatus)
{
    QByteArray result = gitStatusProcess->readAll();
    QString resultString(result);

    QStringList fileList = resultString.split('\n',QString::SkipEmptyParts);
    emit status(fileList);

}
void GitCommand::lsIgnored()
{
    QSettings settings;
    QString proc = settings.value("gitPath").toString();
    QStringList args = *defaultArgs;
    args << "ls-files" << "--others" << "--ignored" << "--exclude-standard";
    gitLSIgnoredProcess->start(proc, args);
}
void GitCommand::lsIgnoredOutput(int exitCode, QProcess::ExitStatus exitStatus)
{
    QByteArray result = gitLSIgnoredProcess->readAll();
    QString resultString(result);

    QStringList fileList = resultString.split('\n',QString::SkipEmptyParts);
    emit lsIgnored(fileList);
}
void GitCommand::setAuthor()
{
    author();
}
void GitCommand::author()
{
    QSettings settings;
    QString proc = settings.value("gitPath").toString();
    //QString proc = "C:\\Program Files (x86)\\Mysysgit\\cmd\\git.cmd";
    QStringList args = *defaultArgs;

    QString author = settings.value("authorName").toString(); //doesn't seem to work with Mike
    //QString author = "Mika";

    args << "config" << "user.name" << author;
    //args << "--git-dir" << repo + "/.git" << "--work-tree" << repo << "config" << "user.name" << author;

    gitSetAuthorProcess->start(proc, args);

}
void GitCommand::authorOutput(int exitCode, QProcess::ExitStatus exitStatus)
{
    //QByteArray result = gitSetAuthorProcess->readAll();
    //QString resultString=result;

}
void GitCommand::log()
{
    QSettings settings;
    QString proc = settings.value("gitPath").toString();
    QStringList args = *defaultArgs;
    args << "log";
    gitLogProcess->start(proc,args);

}


void GitCommand::logOutput(int exitCode, QProcess::ExitStatus exitStatus)
{
    QByteArray result = gitLogProcess->readAll();
    QString resultString(result);
    emit log(result);

}
QStringList GitCommand::branchList()
{
    QSettings settings;
    QString proc = settings.value("gitPath").toString();
    QStringList args = *defaultArgs;
    args << "branch" << "--color=never";
    gitBranchListProcess->start(proc,args);
    gitBranchListProcess->waitForFinished(5000);
    QByteArray result = gitBranchListProcess->readAll();
    QString resultString(result);
    QStringList branchStringList = resultString.split('\n',QString::SkipEmptyParts);
    return branchStringList;

}
QStringList GitCommand::remoteBranchList()
{
    QSettings settings;
    QString proc = settings.value("gitPath").toString();
    QStringList args = *defaultArgs;
    args << "branch" << "-r" << "--color=never";
    gitBranchListProcess->start(proc,args);
    gitBranchListProcess->waitForFinished(5000);
    QByteArray result = gitBranchListProcess->readAll();
    QString resultString(result);
    QStringList branchStringList = resultString.split('\n',QString::SkipEmptyParts);
    return branchStringList;
}
void GitCommand::add(QString filename)
{
    QSettings settings;
    QString proc = settings.value("gitPath").toString();
    QStringList args = *defaultArgs;
    args << "add" << filename;
    gitAddProcess->start(proc, args);
    gitAddProcess->waitForFinished(5000);
}

void GitCommand::setRepo(QString repo)
{
    *defaultArgs = QStringList() << "--git-dir" << repo + "/.git" << "--work-tree" << repo;
}
