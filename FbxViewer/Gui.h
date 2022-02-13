#pragma once

#include "Fwd.h"
#include "IngameGui.h"
#include "MenuCreator.h"
#include "ObjectInfo.h"

#include <LaggyDx/LaggyDxFwd.h>


class Gui
{
public:
  Gui(Game& i_game);

  void showMainMenu();
  void hideMainMenu();

  void showIngameGui();
  void hideIngameGui();
  void setTurn(int i_turn);

  void switchDebugMenu();
  void showDebugMenu();
  void hideDebugMenu();

  void showObjectInfo(const Object& i_object);
  void hideObjectInfo();

private:
  Game& d_game;
  MenuCreator d_menuCreator;

  std::shared_ptr<Dx::IControl> d_debugMenu;
  std::optional<IngameGui> d_ingameGui;
  std::optional<ObjectInfo> d_objectInfo;

  bool d_debugMenuShown = false;
};
