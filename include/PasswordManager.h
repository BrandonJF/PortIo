#pragma once

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
  PasswordManager(const std::vector<ClickType>& pw);

  

  // Getters and setters
  PasswordStatus registerClick(ClickType clickType);

private:
  const std::vector<ClickType>& m_pw;
  const size_t s = 1000;
  CircularQueue<ClickType> m_pwQueue = CircularQueue<ClickType>(s);
  ClickType m_lastRegisteredClick;
};
