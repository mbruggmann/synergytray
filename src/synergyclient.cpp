#include "synergyclient.h"

SynergyClient::SynergyClient()
{
    m_clientPid = 0;
}

SynergyClient::~SynergyClient()
{

}

void SynergyClient::setServer(QString servername)
{
    m_servername = servername;
}

bool SynergyClient::start()
{
    if (isRunning()) {
        return false;
    }

    KProcess *p = ProcessUtils::getNew(this, "synergyc", "-f", m_servername);
    int pid = p->startDetached();

    if (pid == 0) {
        return false;
    } else {
        m_clientPid = pid;
        return true;
    }
}

void SynergyClient::stop()
{
    KProcess *p = ProcessUtils::getNew(this, "killall", "-9", "synergyc");
    p->start();
    if (!p->waitForFinished())
        return;
    m_clientPid = 0;
}

bool SynergyClient::restart()
{
    stop();
    return start();
}

bool SynergyClient::isRunning()
{
    return (m_clientPid != 0);
}
