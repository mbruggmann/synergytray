/*
 * synergyclient.h
 *
 * Copyright (C) 2007 Marc Bruggmann <bruggmann@web.de>
 */

#ifndef SYNERGYCLIENT_H
#define SYNERGYCLIENT_H

#include <QString>

#include <KProcess>

#include "processutils.h"

class SynergyClient : QObject
{
    Q_OBJECT
public:
    SynergyClient();
    virtual ~SynergyClient();

public:
    void setServer(QString servername);

    bool start();
    void stop();
    bool restart();
    bool isRunning();

private:
    QString m_servername;

    int m_clientPid;
};

#endif // SYNERGYCLIENT_H
