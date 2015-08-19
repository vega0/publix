#include "launcher.h"
#include "ui_launcher.h"
#include "assist.h"

#define __CLASS__ "{Launcher}"

Launcher::Launcher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Launcher),
    config( new Config( this, tr( ":/gear.json" ) ) ),
    webdispatch( new WebDispatch( this ) ),
    dirdispatch( new DirDispatch( this ) ),
    versioncontrol( new VersionControl( this ) )
{
    ui->setupUi(this);
    connect( webdispatch, SIGNAL(signal_AllSourcesHandled(WebDispatch*)), this, SLOT(WebDispatchAllHandled(WebDispatch*)) );
    connect( versioncontrol, SIGNAL(signal_VersionsSet(QStringList)), this, SLOT(onVersionsChanged(QStringList)) );

    webdispatch->init();
    setWindowTitle( config->GetValueS( "caption" ) );
    ui->comboBox_VersionSelect->addItem("test");

    qDebug() << QUrl( "http://www.google.ru" );

    versioncontrol->setDirDispatcher( dirdispatch );

    this->versions_box = ui->comboBox_VersionSelect;
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::on_pushButton_Launch_clicked()
{
    QString version_selected = this->ui->comboBox_VersionSelect->currentText();
    __debug_p( "Selected item is" << version_selected );

    JsonVersion jversion( Assist::Network::Network_JFromUrl( webdispatch->createVersionConfigLink( version_selected ) ) );

    if( jversion.isValid() )
    {
        __debug_p( "Version is valid" );
    }
}

void Launcher::WebDispatchAllHandled( WebDispatch *dispatch )
{
    __debug_p( "Dispatch Slot Called" );
    versioncontrol->setWebDispatcher( dispatch );

    if( ! versioncontrol->initial() )
    {
        __debug_p( "Version control initialization failed." );
        return;
    }

    versioncontrol->setFilter( tr( "release" ) );

    __debug_p( "Adding versions to dropdown list." );

    QStringList list = versioncontrol->getVersions();

    Q_UNUSED( list );
}

void Launcher::onVersionsChanged(QStringList versions)
{
    if( versions.isEmpty() )
    {
        __debug_p( "Changing versions failed" );
        return;
    }

    //this->versions_box->addItems( versions );
    this->ui->comboBox_VersionSelect->clear();
    this->ui->comboBox_VersionSelect->addItems( versions );
}
