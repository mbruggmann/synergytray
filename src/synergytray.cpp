/*
 * synergytray.cpp
 *
 * Copyright (C) 2008 Marc Bruggmann <bruggmann@web.de>
 */
#include "synergytray.h"

SynergyTray::SynergyTray()
    : KXmlGuiWindow(),
      m_view(new MainView(this))
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

    // set up system tray icon
    m_trayIcon = new KSystemTrayIcon(this);
    m_trayIcon->show();

    // create server and client objects
    m_synergyServer = new SynergyServer();
    m_synergyClient = new SynergyClient();

    // store the hostname
    m_hostname = NetworkUtils::getHostname();

    // update configuration
    updateConfig();

    // close running instances of synergy
    stopSynergy();

    // stop on close
    if (Settings::stoponclose()) {
        connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(stopSynergy()));
        connect(qApp, SIGNAL(lastWindowClosed()), this, SLOT(stopSynergy()));
    }

    // autostart
    if (Settings::autostart()) {
        startSynergy();
    }

    // timer
    QTimer *connUpdate = new QTimer(this);
    //connect(connUpdate, SIGNAL(timeout()), this, SLOT(connectionUpdate()));
    //connUpdate->start(30*1000);
}

SynergyTray::~SynergyTray()
{
    delete m_view;
    delete m_synergyServer;
    delete m_synergyClient;
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

#include "synergytray.moc"
