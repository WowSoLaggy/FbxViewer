#pragma once

#include "CameraController.h"
#include "Fwd.h"
#include "Object.h"
#include "ObjectView.h"

#include <LaggyDx/LaggyDxFwd.h>


class SessionView
{
public:
  SessionView(Game& i_game);

  CameraController& getCameraController();
  const CameraController& getCameraController() const;

  void render();
  void update(double i_dt);

  void setDrawBb(bool i_drawBb);

private:
  const Game& d_game;
  CameraController d_cameraController;
  Dx::ISimpleRenderer& d_simpleRenderer;
  Dx::IResourceController& d_resourceController;

  Session& d_session;

  ObjectView d_backgroundView;
  std::vector<std::shared_ptr<TileView>> d_tileViews;

  Object d_selectionMarker;
  ObjectView d_selectionMarkerView;

  bool d_drawBb = false;

  void addView(Tile& i_tile);
};
