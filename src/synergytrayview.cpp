/*
 * synergytrayview.cpp
 *
 * Copyright (C) 2008 Marc Bruggmann <bruggmann@web.de>
 */
#include "synergytrayview.h"
#include "settings.h"

#include <klocale.h>
#include <QtGui/QLabel>
#include <QApplication>

#include <KConfigDialog>


SynergyTrayView::SynergyTrayView(QWidget *)
{
    ui_mainview.setupUi(this);
    setAutoFillBackground(true);
}

SynergyTrayView::~SynergyTrayView()
{

}

void SynergyTrayView::settingsChanged()
{

}

void SynergyTrayView::on_closeButton_clicked()
{
    qApp->quit();
}

#include "synergytrayview.moc"
