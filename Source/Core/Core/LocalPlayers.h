// Copyright 2010 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <string>
#include <vector>
#include "Common/IniFile.h"

#include "Common/CommonTypes.h"

class PointerWrap;

namespace LocalPlayers
{
class LocalPlayers
{
public:
  struct Player
  {
    std::string username, userid;
    std::string LocalPlayerToStr();
    std::string GetUsername();
    std::string GetUserID();
    std::vector<std::string> GetUserInfo(std::string playerStr);
    void SetUserInfo(LocalPlayers::Player player);
  };

  std::vector<LocalPlayers::Player> GetPlayers();
  std::map<std::string, std::string> GetPlayerMap();
  std::map<std::string, int> GetPlayerIndexMap();
  std::map<int, LocalPlayers::Player> GetPortPlayers(); // port num to the full local player string <name>[<uid>]
  LocalPlayers::Player toLocalPlayer(std::string playerStr);
};

}  // namespace LocalPlayers
