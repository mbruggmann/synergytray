#ifndef SYNERGYMANAGER_H
#define SYNERGYMANAGER_H

#include <QObject>

#include "synergyserver.h"
#include "synergyclient.h"
#include "settings.h"
#include "networkutils.h"

namespace SynergyState {
    enum Enum {
        Idle,
        ServerRunning,
        ClientRunning
    };
}

class SynergyManager : public QObject
{
    Q_OBJECT

public:
    SynergyManager();
    virtual ~SynergyManager();

    SynergyState::Enum state;

public slots:
    void autostart();
    void startServer();
    void startClient();
    void stop();
    void toggleClient();
    void toggleServer();
    void updateConfig();

signals:
    void stateChanged(SynergyState::Enum newState);

private:
    SynergyServer *m_synergyServer;
    SynergyClient *m_synergyClient;

    void updateState();
};

#endif // SYNERGYMANAGER_H
