#pragma once

#include "Object.h"


class Tile : public Object
{
public:
  Tile();

  void setCoords(Sdk::Vector2I i_coords);
  const Sdk::Vector2I& getCoords() const;

  virtual Sdk::Vector3F getPosition() const override;
  virtual void update(double i_dt) override;

  const std::vector<std::shared_ptr<Object>>& getStructures() const;
  void addStructure(std::shared_ptr<Object> i_structure);
  void removeStructure(Object& i_structure);

  const std::vector<std::shared_ptr<Object>>& getArmies() const;
  void addArmy(std::shared_ptr<Object> i_army);
  void removeArmy(Object& i_army);

private:
  Sdk::Vector2I d_coords;
  float d_xPosOffset = 0.0f;

  std::vector<std::shared_ptr<Object>> d_structures;
  std::vector<std::shared_ptr<Object>> d_armies;

  Sdk::Vector3F getFloorPosition() const;

  void repositionStructures() const;
  void repositionArmies() const;
};
