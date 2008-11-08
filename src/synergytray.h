/*
 * synergytray.h
 *
 * Copyright (C) 2008 Marc Bruggmann <bruggmann@web.de>
 */
#ifndef SYNERGYTRAY_H
#define SYNERGYTRAY_H

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>

#include <kxmlguiwindow.h>
#include <kconfigdialog.h>
#include <kactioncollection.h>
#include <kstandardaction.h>
#include <kiconloader.h>
#include <KDE/KLocale>

#include "settings.h"
#include "synergytrayview.h"
#include "synergyserver.h"
#include "iconloader.h"
#include "networkutils.h"

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

public:
    QString m_hostname;

private slots:
    void showSettingsDialog();
    void updateServer();
    void toggleSynergyServer();

private:
    void setupActions();

private:
    SynergyTrayView *m_view;
    SynergyServer *m_synergyServer;

    Ui::config_client ui_config_client;
    Ui::config_server ui_config_server;
    Ui::config_settings ui_config_settings;
};

#endif // _SYNERGYTRAY_H_
