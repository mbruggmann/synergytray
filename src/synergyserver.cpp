#include "synergyserver.h"

SynergyServer::SynergyServer()
{
    m_serverPid = 0;
    m_confFileName = (QDir::toNativeSeparators(QDir::homePath() + "/.synergytray.conf"));
}

SynergyServer::~SynergyServer()
{

}

void SynergyServer::setHostname(QString hostname)
{
    m_hostname = hostname;
}

void SynergyServer::setClients(QString left, QString up, QString right, QString down)
{
    m_left = left;
    m_up = up;
    m_right = right;
    m_down = down;
}

bool SynergyServer::writeConfigFile()
{
    QString result;

    QString clients[4] = {m_left, m_up, m_right, m_down};
    QString pos[4] = {"left", "up", "right", "down"};
    QString invpos[4] = {"right", "down", "left", "up"};

    // screen section
    result += "section: screens\n";
    result += ("\t"+m_hostname+":\n");
    for (int i = 0; i <=3; i++) {
        if (clients[i] != QString()) {
            result += ("\t" + clients[i] + ":\n");
        }
    }

    result += "end\n";

    // links section
    result += "section: links\n";

    // host
    result += ("\t"+m_hostname+":\n");
    for (int j = 0; j<=3; j++) {
        if (clients[j] != QString()) {
            result += ("\t\t" + pos[j] + " = " + clients[j] + "\n");
        }
    }

    // clients
    for (int k = 0; k<=3; k++) {
        if (clients[k] != QString()) {
            result += ("\t" + clients[k] + ":\n");
            result += ("\t\t" + invpos[k] + " = " + m_hostname+"\n");
        }
    }
    result += "end\n";

    // save config file
    QFile file(m_confFileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(result.toUtf8());
        return true;
    } else {
        return false;
    }
}

bool SynergyServer::start()
{
    if (isRunning()) {
        return false;
    }

//    m_serverProcess->clearEnvironment();
//    m_serverProcess->clearProgram();
//
//    *m_serverProcess << "synergys" << "--config" << m_confFileName;
//    int pid = m_serverProcess->startDetached();

    KProcess *p = ProcessUtils::getNew("synergys","--config", m_confFileName);
    int pid = p->startDetached();

    if (pid == 0) {
        delete p;
        return false;
    } else {
        m_serverPid = pid;
        delete p;
        return true;
    }
}

void SynergyServer::stop()
{
//    m_serverProcess->clearEnvironment();
//    m_serverProcess->clearProgram();
//
//    *m_serverProcess << "killall" << "synergys";
//    m_serverProcess->start();
    KProcess *p = ProcessUtils::getNew("killall", "synergys");
    p->start();
    m_serverPid = 0;
    delete p;
}

bool SynergyServer::restart()
{
    stop();
    return start();
}

bool SynergyServer::isRunning()
{
    return (m_serverPid != 0);
}
