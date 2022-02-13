#pragma once

#include "Fwd.h"
#include "SessionView.h"

#include <LaggySdk/Vector.h>


class Session
{
public:
  Session(int i_sizeX, int i_sizeY);

  int getSizeX() const;
  int getSizeY() const;

  std::shared_ptr<Object>& getBackground();
  const std::shared_ptr<Object>& getBackground() const;

  std::vector<std::shared_ptr<Tile>>& getTiles();
  const std::vector<std::shared_ptr<Tile>>& getTiles() const;

  Tile& getTile(const Sdk::Vector2I& i_coords) const;

  const Sdk::Vector2I& getPlayerStartTile() const;
  void setPlayerStartTile(Sdk::Vector2I i_coords);

  void update(double i_dt);

private:
  const int d_sizeX = 0;
  const int d_sizeY = 0;
  std::shared_ptr<Object> d_background;
  std::vector<std::shared_ptr<Tile>> d_tiles;

  Sdk::Vector2I d_playerStartTile;
};
