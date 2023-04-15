#include "NetworkManager.h"

NetworkManager::NetworkManager( ) : m_ssid(""), m_pw(0) {}

NetworkManager::NetworkManager(std::string ssid, std::string pw) : m_ssid(ssid), m_pw(pw) {}

std::string NetworkManager::getSsid() const {
    return m_ssid;
}

void NetworkManager::setSsid(std::string name) {
    m_ssid = name;
}

std::string NetworkManager::getPw() const {
    return m_pw;
}

void NetworkManager::setPw(std::string age) {
    m_pw = age;
}