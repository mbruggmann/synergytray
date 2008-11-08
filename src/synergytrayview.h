/*
 * synergytrayview.h
 *
 * Copyright (C) 2007 Marc Bruggmann <bruggmann@web.de>
 */
#ifndef SYNERGYTRAYVIEW_H
#define SYNERGYTRAYVIEW_H

#include <QtGui/QWidget>

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

class SynergyTrayView : public QWidget, public Ui::mainview
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    SynergyTrayView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~SynergyTrayView();

public:
    Ui::mainview ui_mainview;

signals:


private slots:
    void settingsChanged();
//    void on_configButton_clicked();
    void on_closeButton_clicked();
};

#endif // SynergyTrayVIEW_H
