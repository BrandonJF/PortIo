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
  explicit PasswordManager(const std::vector<ClickType>& pw);

  

  // Getters and setters
  PasswordStatus registerClick(ClickType clickType);

private:
  const std::vector<ClickType>& m_pw;
  CircularQueue<ClickType> m_pwQueue = CircularQueue<ClickType>(5);
  ClickType m_lastRegisteredClick;
};

#endif // PASSWORDMANAGER_H