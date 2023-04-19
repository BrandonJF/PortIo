#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Arduino.h"

class NetworkManager {
public:
    // Default constructor
    NetworkManager();

    // Parameterized constructor
    NetworkManager(String ssid, String pw);

    // Getters and setters
    String getSsid() const;
    void setSsid(String ssid);

    String getPw() const;
    void setPw(String pw);

void connect();

private:
    String m_ssid;
    String m_pw;
};

#endif // NETWORKMANAGER_H