#include "RingManager.h"

RingManager::RingManager(std::vector<clickType> pw) :  m_pw(pw) {}

std::string RingManager::getSsid() const {
    return m_ssid;
}

void RingManager::setSsid(std::string name) {
    m_ssid = name;
}

std::string RingManager::getPw() const {
    return m_pw;
}

void RingManager::setPw(std::string age) {
    m_pw = age;
}