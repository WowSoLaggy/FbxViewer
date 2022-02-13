#include "stdafx.h"
#include "Gui.h"

#include "Game.h"

#include <LaggyDx/IControl.h>


Gui::Gui(Game& i_game)
  : d_game(i_game)
  , d_menuCreator(i_game)
{
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
