#include "stdafx.h"
#include "Gui.h"

#include "Game.h"

#include <LaggyDx/IControl.h>


Gui::Gui(Game& i_game)
  : d_game(i_game)
  , d_menuCreator(i_game)
{
}


void Gui::showMainMenu()
{
  d_menuCreator.clearAll(d_game.getForm());
  d_menuCreator.createMainMenu(d_game.getForm());
}

void Gui::hideMainMenu()
{
  d_menuCreator.clearAll(d_game.getForm());
}


void Gui::showIngameGui()
{
  if (!d_ingameGui)
    d_ingameGui.emplace(d_menuCreator.createIngameGui(d_game.getForm()));
  else
    d_ingameGui->show();
}

void Gui::hideIngameGui()
{
  if (d_ingameGui)
    d_ingameGui->hide();
}

void Gui::setTurn(const int i_turn)
{
  if (d_ingameGui)
    d_ingameGui->setTurn(i_turn);
}


void Gui::switchDebugMenu()
{
  d_debugMenuShown = !d_debugMenuShown;

  if (!d_debugMenuShown)
    hideDebugMenu();
  else
    showDebugMenu();
}

void Gui::showDebugMenu()
{
  if (!d_debugMenu)
    d_debugMenu = d_menuCreator.createDebugMenu(d_game.getForm());
  else
    d_debugMenu->setVisible(true);
}

void Gui::hideDebugMenu()
{
  if (d_debugMenu)
    d_debugMenu->setVisible(false);
}


void Gui::showObjectInfo(const Object& i_object)
{
  if (!d_objectInfo)
    d_objectInfo.emplace(d_menuCreator.createObjectInfo(d_game.getForm()));
  else
    d_objectInfo->show();

  d_objectInfo->setObject(i_object);
}

void Gui::hideObjectInfo()
{
  if (d_objectInfo)
    d_objectInfo->hide();
}
