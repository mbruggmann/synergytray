/*
 * mainview.h
 *
 * Copyright (C) 2007 Marc Bruggmann <bruggmann@web.de>
 */
#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QtGui/QWidget>

#include "synergymanager.h"
#include "iconloader.h"

#include "ui_mainview.h"

/**
 * This is the main view class for SynergyTray.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author Marc Bruggmann <bruggmann@web.de>
 * @version 0.1
 */

class MainView : public QWidget, public Ui::mainview
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    MainView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~MainView();

public:
    Ui::mainview ui_mainview;

public slots:
    void updateState(SynergyState::Enum newState);

private slots:
    void on_closeButton_clicked();
};

#endif // MAINVIEW_H
