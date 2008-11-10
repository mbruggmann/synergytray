#ifndef SYNERGYMANAGER_H
#define SYNERGYMANAGER_H

#include <QObject>

#include "synergyserver.h"
#include "synergyclient.h"
#include "settings.h"
#include "networkutils.h"

class SynergyManager : public QObject
{
    Q_OBJECT

public:
    enum SynergyState {
        IDLE,
        SERVER_RUNNING,
        CLIENT_RUNNING
    };

public:
    SynergyManager();
    virtual ~SynergyManager();

    SynergyState state;

public slots:
    void autostart();
    void startServer();
    void startClient();
    void stop();
    void updateConfig();

private:
    SynergyServer *m_synergyServer;
    SynergyClient *m_synergyClient;

    void updateState();
};

#endif // SYNERGYMANAGER_H
