#include "PasswordManager.h"

// #ifdef UNIT_TEST
    // #include "ArduinoFake.h"
// #else
    #include "Arduino.h"
// #endif



PasswordManager::PasswordManager(const std::vector<ClickType>& pw) : m_pw(pw) {}

const std::unordered_map<PasswordStatus, String> passwordStatusToString = {
    {ACCEPTED, "accepted"},
    {NOT_ACCEPTED, "not accepted"}
};

const std::unordered_map<ClickType, String> clickTypeToString = {
    {s, "single click"},
    {d, "double click"}
};


PasswordStatus PasswordManager::registerClick(ClickType clickType)
{
  String clickS = clickTypeToString.at(clickType);
  m_lastRegisteredClick = clickType;
  m_pwQueue.enqueue(clickType);
  if (m_pwQueue == m_pw)
  {
    Serial.println("Password Accepted!");
    return ACCEPTED;
  }
  else
  {
    return NOT_ACCEPTED;
  }
}
