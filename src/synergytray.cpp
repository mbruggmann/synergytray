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

    // create synergy manager
    m_synergyManager = new SynergyManager();

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

    // timer
    QTimer *connUpdate = new QTimer(this);
    connect(connUpdate, SIGNAL(timeout()), m_synergyManager, SLOT(autostart()));
    connUpdate->start(30*1000);
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

    connect(dialog, SIGNAL(settingsChanged(QString)), m_synergyManager, SLOT(updateConfig()));

    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

#include "synergytray.moc"
