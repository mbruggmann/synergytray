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

    ui_mainview.serverIcon->setPixmap(IconLoader::get("synergytray-server"));
    ui_mainview.clientIcon->setPixmap(IconLoader::get("synergytray-client"));

    ui_mainview.clientButton->setIcon(KIcon("media-playback-start"));
    ui_mainview.serverButton->setIcon(KIcon("media-playback-start"));
}

MainView::~MainView()
{

}

void MainView::updateState(SynergyState::Enum newState)
{
    if (newState == SynergyState::ClientRunning) {
        ui_mainview.serverButton->setIcon(KIcon("media-playback-start"));
        ui_mainview.serverButton->setText("Start");
        ui_mainview.clientButton->setIcon(KIcon("media-playback-stop"));
        ui_mainview.clientButton->setText("Stop");

        ui_mainview.clientFrame->setEnabled(true);
        ui_mainview.serverFrame->setEnabled(false);

    } else if (newState == SynergyState::ServerRunning) {
        ui_mainview.clientButton->setIcon(KIcon("media-playback-start"));
        ui_mainview.clientButton->setText("Start");
        ui_mainview.serverButton->setIcon(KIcon("media-playback-stop"));
        ui_mainview.serverButton->setText("Stop");

        ui_mainview.serverFrame->setEnabled(true);
        ui_mainview.clientFrame->setEnabled(false);

    } else {
        ui_mainview.clientButton->setIcon(KIcon("media-playback-start"));
        ui_mainview.clientButton->setText("Start");
        ui_mainview.serverButton->setIcon(KIcon("media-playback-start"));
        ui_mainview.serverButton->setText("Start");

        ui_mainview.serverFrame->setEnabled(true);
        ui_mainview.clientFrame->setEnabled(true);
    }
}

#include "mainview.moc"
