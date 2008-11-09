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
    SynergyManager();
    virtual ~SynergyManager();

public slots:
    void autostart();
    void startServer();
    void startClient();
    void stop();
    void updateConfig();

private:
    SynergyServer *m_synergyServer;
    SynergyClient *m_synergyClient;

};

#endif // SYNERGYMANAGER_H
