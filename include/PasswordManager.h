#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include "CircularQueue.h"
#include <string>
#include <vector>
#include <unordered_map>

enum ClickType
{
  s,
  d,
};

enum PasswordStatus
{
  ACCEPTED,
  NOT_ACCEPTED,
};


class PasswordManager
{
public:
  // Default constructor
  // PasswordManager();

  // Parameterized constructor
  PasswordManager(std::vector<ClickType> pw);

  // Getters and setters
  void setPw(std::vector<ClickType> pw);
  PasswordStatus registerClick(ClickType clickType);

private:
  std::vector<ClickType> m_pw;
  CircularQueue<ClickType> m_pwQueue;
  ClickType m_lastRegisteredClick;
};

#endif // PASSWORDMANAGER_H