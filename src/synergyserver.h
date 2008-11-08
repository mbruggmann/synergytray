/*
 * synergyserver.h
 *
 * Copyright (C) 2007 Marc Bruggmann <bruggmann@web.de>
 */

#ifndef SYNERGYSERVER_H
#define SYNERGYSERVER_H

#include <QString>
#include <QDir>
#include <QFile>

#include <KProcess>

#include "processutils.h"

class SynergyServer : QObject
{
    Q_OBJECT
public:
    SynergyServer();
    virtual ~SynergyServer();

public:
    void setHostname(QString hostname);
    void setClients(QString left, QString up, QString right, QString down);
    bool writeConfigFile();

    bool start();
    void stop();
    bool restart();
    bool isRunning();

private:
    QString m_hostname;

    QString m_confFileName;

    QString m_left;
    QString m_up;
    QString m_right;
    QString m_down;

    int m_serverPid;
};

#endif // SYNERGYSERVER_H
