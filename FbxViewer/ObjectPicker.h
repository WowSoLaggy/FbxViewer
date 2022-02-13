#pragma once

#include "Fwd.h"

#include <LaggySdk/Ray.h>


class ObjectPicker
{
public:
  ObjectPicker(const Game& i_game);

  const Object* pick() const;

private:
  const Game& d_game;

  Sdk::RayF castRay() const;
};
