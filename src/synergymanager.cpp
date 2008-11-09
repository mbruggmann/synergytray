#include "synergymanager.h"

SynergyManager::SynergyManager()
{
    // create server and client objects
    m_synergyServer = new SynergyServer();
    m_synergyClient = new SynergyClient();
}

SynergyManager::~SynergyManager()
{
    delete m_synergyServer;
    delete m_synergyClient;
}

void SynergyManager::autostart()
{
    if (m_synergyClient->isRunning() || m_synergyServer->isRunning())
        return;

    // start a synergy client if the server is available on the network
    if (NetworkUtils::isHostAvailable(Settings::server())) {
        m_synergyClient->start();
    }

    // start a synergy server if any of the clients are available
    else if (NetworkUtils::isHostAvailable(Settings::client_left()) ||
        NetworkUtils::isHostAvailable(Settings::client_top()) ||
        NetworkUtils::isHostAvailable(Settings::client_right()) ||
        NetworkUtils::isHostAvailable(Settings::client_bottom()) ) {
        m_synergyServer->start();
    }

    // no pc found
    else {
        // do nothing
    }

}

void SynergyManager::startClient()
{
    if (m_synergyServer->isRunning())
        m_synergyServer->stop();

    m_synergyClient->start();
}

void SynergyManager::startServer()
{
    if (m_synergyClient->isRunning())
        m_synergyClient->stop();

    m_synergyServer->start();
}

void SynergyManager::stop()
{
    if (m_synergyServer->isRunning()) {
        m_synergyServer->stop();
    }
    if (m_synergyClient->isRunning()) {
        m_synergyClient->stop();
    }
}

void SynergyManager::updateConfig()
{
    // server
    m_synergyServer->setHostname(NetworkUtils::getHostname());
    m_synergyServer->setClients(Settings::client_left(), Settings::client_top(), Settings::client_right(), Settings::client_bottom());
    m_synergyServer->writeConfigFile();

    // client
    m_synergyClient->setServer(Settings::server());
}
