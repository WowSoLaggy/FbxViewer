#pragma once

#include "Fwd.h"
#include "IngameGui.h"
#include "ObjectInfo.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/Vector.h>


class MenuCreator
{
public:
  MenuCreator(Game& i_game);

  void clearAll(Dx::IControl& i_parent) const;
  void createMainMenu(Dx::IControl& i_parent) const;

  std::shared_ptr<Dx::IControl> createDebugMenu(Dx::IControl& i_parent) const;
  ObjectInfo createObjectInfo(Dx::IControl& i_parent) const;
  IngameGui createIngameGui(Dx::IControl& i_parent) const;

private:
  Game& d_game;
};
