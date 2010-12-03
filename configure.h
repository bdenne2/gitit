#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDialog>
#include <QSettings>

namespace Ui {
    class Configure;
}

class Configure : public QDialog
{
    Q_OBJECT

public:
    explicit Configure(QWidget *parent = 0);
    ~Configure();
public slots:
    /// updates the saved configure vars the to the ones user entered
    void accept();
    ///keeps saved configure vars regardless of user entry
    void reject();
private:
    Ui::Configure *ui;
    QSettings settings;
};

#endif // CONFIGURE_H
