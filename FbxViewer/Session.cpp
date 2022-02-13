#include "stdafx.h"
#include "Session.h"

#include "Object.h"
#include "Tile.h"


Session::Session(int i_sizeX, int i_sizeY)
  : d_sizeX(i_sizeX)
  , d_sizeY(i_sizeY)
{
}


int Session::getSizeX() const
{
  return d_sizeX;
}

int Session::getSizeY() const
{
  return d_sizeY;
}


std::shared_ptr<Object>& Session::getBackground() { return d_background; }
const std::shared_ptr<Object>& Session::getBackground() const { return d_background; }

std::vector<std::shared_ptr<Tile>>& Session::getTiles() { return d_tiles; }
const std::vector<std::shared_ptr<Tile>>& Session::getTiles() const { return d_tiles; }


Tile& Session::getTile(const Sdk::Vector2I& i_coords) const
{
  const int sizeX = i_coords.y % 2 == 0 ? d_sizeX : d_sizeX - 1;

  CONTRACT_EXPECT(0 <= i_coords.x);
  CONTRACT_EXPECT(i_coords.x < sizeX);
  CONTRACT_EXPECT(0 <= i_coords.y);
  CONTRACT_EXPECT(i_coords.y < d_sizeY);

  const int missedTilesCount = i_coords.y / 2;
  const auto& tile = d_tiles.at(i_coords.x + i_coords.y * d_sizeX - missedTilesCount);

  CONTRACT_ENSURE(tile.get() != nullptr);
  CONTRACT_ENSURE(tile->getCoords() == i_coords);

  return *tile;
}


const Sdk::Vector2I& Session::getPlayerStartTile() const
{
  return d_playerStartTile;
}

void Session::setPlayerStartTile(Sdk::Vector2I i_coords)
{
  d_playerStartTile = std::move(i_coords);
}


void Session::update(double i_dt)
{
  for (const auto& tile : d_tiles)
    tile->update(i_dt);
}
