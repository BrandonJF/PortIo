#ifndef RINGMANAGER_H
#define RINGMANAGER_H

#include "CircularQueue.h"
#include <string>
#include <vector>

enum clickType
{
  s,
  d,
};

class RingManager {
public:
    // Default constructor
    // RingManager();

    // Parameterized constructor
    RingManager(std::vector<clickType> pw);

    // Getters and setters
    void setPw(std::vector<clickType> pw);
    void registerClick(clickType clickType);


private:
    std::vector<clickType> m_pw;
    CircularQueue<clickType> m_pwQueue;
    clickType m_lastRegisteredClick;
};



#endif // RingManager_H