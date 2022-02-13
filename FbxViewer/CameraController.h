#pragma once

#include "Fwd.h"

#include <LaggyDx/ICamera.h>
#include <LaggySdk/Vector.h>


class CameraController
{
public:
  CameraController(const Game& i_game);

  Dx::ICamera& getCamera();
  const Dx::ICamera& getCamera() const;

  void moveRightStart();
  void moveRightStop();
  void moveLeftStart();
  void moveLeftStop();
  void moveUpStart();
  void moveUpStop();
  void moveDownStart();
  void moveDownStop();
  void rotateCwStart();
  void rotateCwStop();
  void rotateCcwStart();
  void rotateCcwStop();

  void zoomIn();
  void zoomOut();

  void freeCameraStart();
  void freeCameraStop();

  void resetCamera();

  void update(double i_dt);

private:
  const Game& d_game;
  std::unique_ptr<Dx::ICamera> d_camera;

  bool d_moveRight = false;
  bool d_moveLeft = false;
  bool d_moveUp = false;
  bool d_moveDown = false;
  bool d_rotateCw = false;
  bool d_rotateCcw = false;

  bool d_freeCamera = false;
  Sdk::Vector2I d_prevMousePos;

  void createDefaultCamera();

  void updateCameraMovement(double i_dt);
  void updateCameraFreeRotation();
};
