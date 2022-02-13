#include "stdafx.h"
#include "Tile.h"

#include "PrototypeCollection.h"
#include "TileGridSettings.h"
#include "TileSettings.h"
#include "WorldEvents.h"


Tile::Tile()
  : Object(PrototypeCollection::get("tile"))
{
}


void Tile::setCoords(Sdk::Vector2I i_coords)
{
  d_coords = std::move(i_coords);

  const bool oddYRow = d_coords.y % 2 == 1;
  d_xPosOffset = oddYRow ? TileGridSettings::TileOffsetXForOddYRow : 0.0f;
}

const Sdk::Vector2I& Tile::getCoords() const
{
  return d_coords;
}


Sdk::Vector3F Tile::getPosition() const
{
  return {
    TileGridSettings::TileOffsetX * d_coords.x + d_xPosOffset,
    TileGridSettings::TileOffsetY * d_coords.y,
    -0.025f
  };
}

Sdk::Vector3F Tile::getFloorPosition() const
{
  auto floorPos = getPosition();
  floorPos.z = 0;
  return floorPos;
}


void Tile::update(double i_dt)
{
  auto update = [&](const auto& i_array)
  {
    for (const auto& obj : i_array)
      obj->update(i_dt);
  };

  update(d_structures);
  update(d_armies);
}


const std::vector<std::shared_ptr<Object>>& Tile::getStructures() const
{
  return d_structures;
}

void Tile::addStructure(std::shared_ptr<Object> i_structure)
{
  if (d_structures.size() < TileSettings::MaxStructures)
    d_structures.push_back(i_structure);

  repositionStructures();

  notify(ObjectAddedEvent(*i_structure));
}

void Tile::removeStructure(Object& i_structure)
{
  d_structures.erase(std::remove_if(d_structures.begin(), d_structures.end(),
    [&](const auto& i_ptr) { return i_ptr.get() == &i_structure; }), d_structures.end());

  repositionStructures();

  notify(ObjectRemovedEvent(i_structure));
}


const std::vector<std::shared_ptr<Object>>& Tile::getArmies() const
{
  return d_armies;
}

void Tile::addArmy(std::shared_ptr<Object> i_army)
{
  if (d_armies.size() < TileSettings::MaxArmies)
    d_armies.push_back(std::move(i_army));

  repositionArmies();

  notify(ObjectAddedEvent(*i_army));
}

void Tile::removeArmy(Object& i_army)
{
  d_armies.erase(std::remove_if(d_armies.begin(), d_armies.end(),
    [&](const auto& i_ptr) { return i_ptr.get() == &i_army; }), d_armies.end());

  repositionArmies();

  notify(ObjectRemovedEvent(i_army));
}


void Tile::repositionStructures() const
{
  for (int i = 0; i < d_structures.size(); ++i)
  {
    d_structures.at(i)->setPosition(getFloorPosition() + TileSettings::StructureOffsets[i]);
    d_structures.at(i)->setRotation({ 0, 0, TileSettings::StructureRotations[i] });
  }
}

void Tile::repositionArmies() const
{
  for (int i = 0; i < d_armies.size(); ++i)
    d_armies.at(i)->setPosition(getFloorPosition() + TileSettings::ArmiesOffsets[i]);
}
