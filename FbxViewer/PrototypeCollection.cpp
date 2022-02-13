#include "stdafx.h"
#include "PrototypeCollection.h"

#include "Prototype.h"


namespace
{
  using PrototypesMap = std::unordered_map<std::string, Prototype>;

  PrototypesMap getPrototypes()
  {
    PrototypesMap map;

    map.insert({ "map", { "map", "plane.fbx", "map.jpg" } });
    map.insert({ "tile", { "tile", "tile.fbx", "tile_grass.png" } });
    map.insert({ "base", { "base", "base.fbx", "base.png" } });
    map.insert({ "worker", { "worker", "worker.fbx", "" } });
    map.insert({ "selection_marker", { "selection_marker", "circle.fbx", "yellow.png" } });

    return map;
  }

} // anonym NS


const Prototype& PrototypeCollection::get(const std::string& i_name)
{
  static const auto prototypes { getPrototypes() };
  return prototypes.at(i_name);
}
