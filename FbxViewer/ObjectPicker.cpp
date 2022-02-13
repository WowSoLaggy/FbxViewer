#include "stdafx.h"
#include "ObjectPicker.h"

#include "Game.h"
#include "Tile.h"


ObjectPicker::ObjectPicker(const Game& i_game)
  : d_game(i_game)
{
}


Sdk::RayF ObjectPicker::castRay() const
{
  const auto mousePos = d_game.getInputDevice().getMousePosition();
  return d_game.getSessionView().getCameraController().getCamera().screenToWorld(mousePos);
}


const Object* ObjectPicker::pick() const
{
  const auto ray = castRay();

  double tminGlobal = std::numeric_limits<double>::max();
  const Object* closestObject = nullptr;

  auto intersect = [&](const Object& i_object)
  {
    if (const auto obbOpt = i_object.getObb())
    {
      if (const auto tmin = obbOpt->intersect(ray))
      {
        if (*tmin < tminGlobal)
        {
          tminGlobal = *tmin;
          closestObject = &i_object;
        }
      }
    }
  };

  auto checkArray = [&](const auto& i_arr)
  {
    for (const auto& objPtr : i_arr)
      intersect(*objPtr);
  };

  for (const auto& tilePtr : d_game.getSession().getTiles())
  {
    for (const auto& arr : { tilePtr->getStructures(), tilePtr->getArmies() })
      checkArray(arr);
  }

  return closestObject;
}
