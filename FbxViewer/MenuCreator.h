#pragma once

#include "Fwd.h"
#include "ObjectInfo.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/Vector.h>


class MenuCreator
{
public:
  MenuCreator(Game& i_game);

  void clearAll(Dx::IControl& i_parent) const;

  ObjectInfo createObjectInfo(Dx::IControl& i_parent) const;

private:
  Game& d_game;
};
