/*
 * synergytray.h
 *
 * Copyright (C) 2008 Marc Bruggmann <bruggmann@web.de>
 */
#ifndef SYNERGYTRAY_H
#define SYNERGYTRAY_H

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>
#include <QApplication>
#include <QTimer>

#include <kxmlguiwindow.h>
#include <kconfigdialog.h>
#include <KDE/KLocale>
#include <ksystemtrayicon.h>

#include "settings.h"
#include "synergymanager.h"
#include "iconloader.h"

#include "mainview.h"
#include "ui_config_client.h"
#include "ui_config_server.h"
#include "ui_config_settings.h"

class SynergyTrayView;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for SynergyTray.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Marc Bruggmann <bruggmann@web.de>
 * @version 0.1
 */
class SynergyTray : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    SynergyTray();

    /**
     * Default Destructor
     */
    virtual ~SynergyTray();

private slots:
    void showSettingsDialog();

private:
    SynergyManager *m_synergyManager;

    KSystemTrayIcon *m_trayIcon;

    MainView *m_view;
    Ui::config_client ui_config_client;
    Ui::config_server ui_config_server;
    Ui::config_settings ui_config_settings;
};

#endif // _SYNERGYTRAY_H_
