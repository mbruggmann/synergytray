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

    // set up system tray icon
    m_trayIcon = new KSystemTrayIcon(this);
    m_trayIcon->show();

    // set up buttons
    connect(m_view->ui_mainview.configButton, SIGNAL(clicked()), this, SLOT(showSettingsDialog()));
    connect(m_view->ui_mainview.closeButton, SIGNAL(clicked()), m_trayIcon, SLOT(toggleActive()));

    // create synergy manager
    m_synergyManager = new SynergyManager();
    connect(m_synergyManager, SIGNAL(stateChanged(SynergyState::Enum)), this, SLOT(updateState(SynergyState::Enum)));
    connect(m_synergyManager, SIGNAL(stateChanged(SynergyState::Enum)), m_view, SLOT(updateState(SynergyState::Enum)));
    connect(m_view->ui_mainview.clientButton, SIGNAL(clicked()), m_synergyManager, SLOT(toggleClient()));
    connect(m_view->ui_mainview.serverButton, SIGNAL(clicked()), m_synergyManager, SLOT(toggleServer()));

    // update configuration
    m_synergyManager->updateConfig();

    // stop on close
    if (Settings::stoponclose()) {
        connect(qApp, SIGNAL(aboutToQuit()), m_synergyManager, SLOT(stop()));
        connect(qApp, SIGNAL(lastWindowClosed()), m_synergyManager, SLOT(stop()));
    }

    // autostart
    if (Settings::autostart()) {
        m_synergyManager->autostart();
    }
    if (Settings::serverstart()) {
        m_synergyManager->startServer();
    }

    // timer
    QTimer *connUpdate = new QTimer(this);
    connect(connUpdate, SIGNAL(timeout()), m_synergyManager, SLOT(autostart()));
    connUpdate->start(10*1000);

    // update state
    updateState(m_synergyManager->state);
    m_view->updateState(m_synergyManager->state);
}

SynergyTray::~SynergyTray()
{
    delete m_view;
    delete m_synergyManager;
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
    ui_config_server.hostname->setText(NetworkUtils::getHostname());

    // load the icons
    QPixmap screen = IconLoader::getSmall("video-display");
    QPixmap keyboard = IconLoader::get("input-keyboard");
    ui_config_server.computerIcon->setPixmap(keyboard);
    ui_config_server.leftScreen->setPixmap(screen);
    ui_config_server.topScreen->setPixmap(screen);
    ui_config_server.rightScreen->setPixmap(screen);
    ui_config_server.bottomScreen->setPixmap(screen);

    // show clear buttons
    ui_config_server.kcfg_client_left->setClearButtonShown(true);
    ui_config_server.kcfg_client_top->setClearButtonShown(true);
    ui_config_server.kcfg_client_right->setClearButtonShown(true);
    ui_config_server.kcfg_client_bottom->setClearButtonShown(true);
    ui_config_client.kcfg_server->setClearButtonShown(true);

    dialog->addPage( configServer, i18n("Server"), "synergytray-server" );
    dialog->addPage( configClient, i18n("Client"), "synergytray-client" );
    dialog->addPage( configSettings, i18n("Behaviour"), "preferences-system" );

    connect(dialog, SIGNAL(settingsChanged(QString)), m_synergyManager, SLOT(updateConfig()));

    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void SynergyTray::updateState(SynergyState::Enum newState)
{
    QString icon = "synergytray";

    if (newState == SynergyState::ServerRunning) {
        icon = "synergytray-server";
    } else if (newState == SynergyState::ClientRunning) {
        icon = "synergytray-client";
    }

    m_trayIcon->setIcon(m_trayIcon->loadIcon(icon));
    setWindowIcon(m_trayIcon->loadIcon(icon));
}

#include "synergytray.moc"
