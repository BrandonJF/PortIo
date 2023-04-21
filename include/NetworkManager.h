#pragma once

#include "Arduino.h"

enum LOCK_ACTION {
    LOCK, 
    UNLOCK
};

typedef std::function<void()> LockCallback;


class NetworkManager
{
public:
    // Default constructor
    NetworkManager();

    // Parameterized constructor
    NetworkManager(String ssid, String pw, LockCallback callback);

    // Getters and setters
    String getSsid() const;
    void setSsid(String ssid);

    String getPw() const;
    void setPw(String pw);

    void setup_wifi();

    void lockCallback(char *topic, byte *payload, unsigned int length);

    void publish();

    void checkConnected();

    void reconnect();

private:
    String m_ssid;
    String m_pw;
    LockCallback m_callback;
    const char *ID = "PortIO";       // Name of our device, must be unique
    const char *TOPIC = "door/buzz"; // Topic to subcribe to
    const char *APT_DOOR_TOPIC = "building/door/set";
};
