#include "stdafx.h"
#include "CreateSession.h"

#include "PrototypeCollection.h"
#include "Tile.h"
#include "TileGridSettings.h"


namespace
{
  void createBackground(Session& i_session)
  {
    const int mapSizeX = i_session.getSizeX();
    const int mapSizeY = i_session.getSizeY();

    auto background = std::make_shared<Object>(PrototypeCollection::get("map"));

    const float middleX = (mapSizeX - 1) * TileGridSettings::TileOffsetX / 2;
    const float middleY = (mapSizeY - 1) * TileGridSettings::TileOffsetY / 2;

    const float scaleX = mapSizeX * TileGridSettings::TileOffsetX / 2;
    const float scaleY = mapSizeY * TileGridSettings::TileOffsetY / 2;

    background->setPosition({ middleX, middleY, -0.1f });
    background->setScale({ scaleX, scaleY, 1 });

    i_session.getBackground() = std::move(background);
  }

  void createMap(Session& i_session)
  {
    const int mapSizeX = i_session.getSizeX();
    const int mapSizeY = i_session.getSizeY();

    auto& tiles = i_session.getTiles();
    auto createTile = [&](const int i_x, const int i_y) -> Tile&
    {
      auto tilePtr = std::make_shared<Tile>();
      tiles.push_back(tilePtr);
      auto& tile = *tilePtr;

      tile.setCoords({ i_x, i_y });

      return tile;
    };

    for (int y = 0; y < mapSizeY; ++y)
    {
      const int sizeXModified = y % 2 == 1 ? mapSizeX - 1 : mapSizeX;
      for (int x = 0; x < sizeXModified; ++x)
        auto& tile = createTile(x, y);
    }
  }

  void createStartObjects(Session& i_session)
  {
    auto createBase = [&](const Sdk::Vector2I& i_coords)
    {
      auto base = std::make_shared<Object>(PrototypeCollection::get("base"));
      base->setAnimation("idle", true);
      i_session.getTile(i_coords).addStructure(std::move(base));
    };

    auto createWorker = [&](const Sdk::Vector2I& i_coords)
    {
      auto worker = std::make_shared<Object>(PrototypeCollection::get("worker"));
      worker->setAnimation("idle", true);
      i_session.getTile(i_coords).addArmy(std::move(worker));
    };

    const std::array<Sdk::Vector2I, 2> StartLocations{ {
      { 0, 0 }, // player
      { 2, 2 }  // AI
    } };

    for (const auto& startLocation : StartLocations)
    {
      createBase(startLocation);
      createBase(startLocation);
      createBase(startLocation);
      createWorker(startLocation);
      createWorker(startLocation);
      createWorker(startLocation);
      createWorker(startLocation);
    }

    i_session.setPlayerStartTile(StartLocations.front());
  }

} // anonym NS


std::unique_ptr<Session> createSession()
{
  auto session = std::make_unique<Session>(3, 3);
  
  createBackground(*session);
  createMap(*session);
  createStartObjects(*session);

  return session;
}
