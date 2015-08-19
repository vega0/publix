#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QMainWindow>
#include <QComboBox>

#include "config.h"
#include "webdispatch.h"
#include "dirdispatch.h"
#include "versioncontrol.h"

namespace Ui {
class Launcher;
}

class Launcher : public QMainWindow
{
    Q_OBJECT

    Config *config;
    WebDispatch * webdispatch;
    DirDispatch * dirdispatch;
    VersionControl *versioncontrol;

    QComboBox *versions_box;
public:
    explicit Launcher(QWidget *parent = 0);
    ~Launcher();

private slots:
    void on_pushButton_Launch_clicked();
    void WebDispatchAllHandled( WebDispatch *dispatch );
    void onVersionsChanged( QStringList versions );

private:
    Ui::Launcher *ui;
};

#endif // LAUNCHER_H
