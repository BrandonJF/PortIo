#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <string>

class NetworkManager {
public:
    // Default constructor
    NetworkManager();

    // Parameterized constructor
    NetworkManager(std::string ssid, std::string pw);

    // Getters and setters
    std::string getSsid() const;
    void setSsid(std::string ssid);

    std::string getPw() const;
    void setPw(std::string pw);

private:
    std::string m_ssid;
    std::string m_pw;
};

#endif // NETWORKMANAGER_H