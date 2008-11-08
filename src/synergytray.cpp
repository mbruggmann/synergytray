/*
 * synergytray.cpp
 *
 * Copyright (C) 2008 Marc Bruggmann <bruggmann@web.de>
 */
#include "synergytray.h"

SynergyTray::SynergyTray()
    : KXmlGuiWindow(),
      m_view(new SynergyTrayView(this))
{
    // set the main widget
    setCentralWidget(m_view);

    // populate gui
    setupGUI();

    // hide the toolbar and menubar
    setStandardToolBarMenuEnabled(false);
    setMenuBar(0);

    // set up buttons
    connect(m_view->ui_mainview.configButton, SIGNAL(clicked()), this, SLOT(showSettingsDialog()));
    connect(m_view->ui_mainview.toggleButton, SIGNAL(clicked()), this, SLOT(toggleSynergyServer()));

    // create server and client objects
    m_synergyServer = new SynergyServer();
    m_synergyClient = new SynergyClient();

    // stop possible running instances of synergy
    m_synergyServer->stop();
    m_synergyClient->stop();

    // update the hostname
    m_hostname = NetworkUtils::getHostname();

    // update configuration
    updateConfig();
}

SynergyTray::~SynergyTray()
{
    delete m_view;
    delete m_synergyServer;
}

void SynergyTray::showSettingsDialog()
{
    if ( KConfigDialog::showDialog( "settings" ) )
      return;

    KConfigDialog* dialog = new KConfigDialog(this, "settings", Settings::self());

    QWidget *configServer = new QWidget;
    QWidget *configClient = new QWidget;
    QWidget *configSettings = new QWidget;

    ui_config_server.setupUi(configServer);
    ui_config_client.setupUi(configClient);
    ui_config_settings.setupUi(configSettings);

    // set the hostname
    ui_config_server.hostname->setText(m_hostname);

    // load the icons
    QPixmap screen = IconLoader::get("video-display");
    QPixmap keyboard = IconLoader::get("input-keyboard");
    ui_config_server.computerIcon->setPixmap(keyboard);
    ui_config_server.leftScreen->setPixmap(screen);
    ui_config_server.topScreen->setPixmap(screen);
    ui_config_server.rightScreen->setPixmap(screen);
    ui_config_server.bottomScreen->setPixmap(screen);

    dialog->addPage( configServer, i18n("Server"), "input-keyboard" );
    dialog->addPage( configClient, i18n("Client"), "video-display" );
    dialog->addPage( configSettings, i18n("Setting"), "preferences-system" );

    connect(dialog, SIGNAL(settingsChanged(QString)), this, SLOT(updateConfig()));

    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void SynergyTray::updateConfig()
{
    // server
    m_synergyServer->setHostname(m_hostname);
    m_synergyServer->setClients(Settings::client_left(), Settings::client_top(), Settings::client_right(), Settings::client_bottom());
    m_synergyServer->writeConfigFile();

    // client
    m_synergyClient->setServer(Settings::server());

    // connect
    startSynergy();
}

void SynergyTray::startSynergy()
{
    // stop running instances
    stopSynergy();

    // start a synergy client if the server is available on the network
    if (NetworkUtils::isHostAvailable(Settings::server())) {
        m_synergyClient->start();
        m_view->ui_mainview.textedit->setText("connected as client to " + Settings::server());
    }

    // start a synergy server if any of the clients are available
    else if (NetworkUtils::isHostAvailable(Settings::client_left()) ||
        NetworkUtils::isHostAvailable(Settings::client_top()) ||
        NetworkUtils::isHostAvailable(Settings::client_right()) ||
        NetworkUtils::isHostAvailable(Settings::client_bottom()) ) {
        m_synergyServer->start();
        m_view->ui_mainview.textedit->setText("started server");
    }

    // no pc found
    else {
        m_view->ui_mainview.textedit->setText("server '" + Settings::server() + "' is not available on the network");
    }

}

void SynergyTray::stopSynergy()
{
    if (m_synergyServer->isRunning()) {
        m_synergyServer->stop();
    }
    if (m_synergyClient->isRunning()) {
        m_synergyClient->stop();
    }
}

void SynergyTray::toggleSynergyServer()
{
    if (m_synergyServer->isRunning()) {
        m_synergyServer->stop();
    } else {
        m_synergyServer->start();
    }
}

#include "synergytray.moc"
