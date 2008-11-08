/*
 * mainview.cpp
 *
 * Copyright (C) 2008 Marc Bruggmann <bruggmann@web.de>
 */
#include "mainview.h"
#include "settings.h"

#include <klocale.h>
#include <QtGui/QLabel>
#include <QApplication>

#include <KConfigDialog>


MainView::MainView(QWidget *)
{
    ui_mainview.setupUi(this);
    setAutoFillBackground(true);
}

MainView::~MainView()
{

}

void MainView::on_closeButton_clicked()
{
    qApp->quit();
}

#include "mainview.moc"
