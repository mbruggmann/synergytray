#include "synergymanager.h"

SynergyManager::SynergyManager()
{
    // create server and client objects
    m_synergyServer = new SynergyServer();
    m_synergyClient = new SynergyClient();

    updateState();
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
//    else if (NetworkUtils::isHostAvailable(Settings::client_left()) ||
//        NetworkUtils::isHostAvailable(Settings::client_top()) ||
//        NetworkUtils::isHostAvailable(Settings::client_right()) ||
//        NetworkUtils::isHostAvailable(Settings::client_bottom()) ) {
//        m_synergyServer->start();
//    }

    // no pc found
    else {
        // do nothing
    }

    updateState();
}

void SynergyManager::startClient()
{
    if (m_synergyServer->isRunning())
        m_synergyServer->stop();

    m_synergyClient->start();

    updateState();
}

void SynergyManager::startServer()
{
    if (m_synergyClient->isRunning())
        m_synergyClient->stop();

    m_synergyServer->start();

    updateState();
}

void SynergyManager::stop()
{
    if (m_synergyServer->isRunning()) {
        m_synergyServer->stop();
    }
    if (m_synergyClient->isRunning()) {
        m_synergyClient->stop();
    }

    updateState();
}

void SynergyManager::toggleClient()
{
    if (m_synergyClient->isRunning()) {
        m_synergyClient->stop();
    } else {
        m_synergyClient->start();
    }

    updateState();
}

void SynergyManager::toggleServer()
{
    if (m_synergyServer->isRunning()) {
        m_synergyServer->stop();
    } else {
        m_synergyServer->start();
    }

    updateState();
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

void  SynergyManager::updateState()
{
    SynergyState::Enum oldState = state;

    if (m_synergyServer->isRunning()) {
        state = SynergyState::ServerRunning;
    } else if (m_synergyClient->isRunning()) {
        state = SynergyState::ClientRunning;
    } else {
        state = SynergyState::Idle;
    }

    if (state != oldState) {
        emit stateChanged(state);
    }
}
