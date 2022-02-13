#include "stdafx.h"
#include "ActionsController.h"

#include "CameraController.h"
#include "Game.h"
#include "GameController.h"
#include "Gui.h"


void ActionsController::createActionsInGame(Game& i_game)
{
  Dx::ActionsMap map;


  map.setAction(
    Dx::KeyboardKey::W,
    Dx::Action(std::bind(&CameraController::moveUpStart, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);
  map.setAction(
    Dx::KeyboardKey::W,
    Dx::Action(std::bind(&CameraController::moveUpStop, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnRelease);

  map.setAction(
    Dx::KeyboardKey::S,
    Dx::Action(std::bind(&CameraController::moveDownStart, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);
  map.setAction(
    Dx::KeyboardKey::S,
    Dx::Action(std::bind(&CameraController::moveDownStop, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnRelease);

  map.setAction(
    Dx::KeyboardKey::A,
    Dx::Action(std::bind(&CameraController::moveLeftStart, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);
  map.setAction(
    Dx::KeyboardKey::A,
    Dx::Action(std::bind(&CameraController::moveLeftStop, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnRelease);

  map.setAction(
    Dx::KeyboardKey::D,
    Dx::Action(std::bind(&CameraController::moveRightStart, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);
  map.setAction(
    Dx::KeyboardKey::D,
    Dx::Action(std::bind(&CameraController::moveRightStop, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnRelease);

  map.setAction(
    Dx::KeyboardKey::Q,
    Dx::Action(std::bind(&CameraController::rotateCwStart, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);
  map.setAction(
    Dx::KeyboardKey::Q,
    Dx::Action(std::bind(&CameraController::rotateCwStop, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnRelease);

  map.setAction(
    Dx::KeyboardKey::E,
    Dx::Action(std::bind(&CameraController::rotateCcwStart, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);
  map.setAction(
    Dx::KeyboardKey::E,
    Dx::Action(std::bind(&CameraController::rotateCcwStop, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnRelease);
  

  map.setAction(
    Dx::MouseKey::WheelUp,
    Dx::Action(std::bind(&CameraController::zoomIn, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);
  map.setAction(
    Dx::MouseKey::WheelDown,
    Dx::Action(std::bind(&CameraController::zoomOut, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);


  map.setAction(
    Dx::MouseKey::Middle,
    Dx::Action(std::bind(&CameraController::freeCameraStart, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);
  map.setAction(
    Dx::MouseKey::Middle,
    Dx::Action(std::bind(&CameraController::freeCameraStop, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnRelease);


  map.setAction(
    Dx::KeyboardKey::C,
    Dx::Action(std::bind(&CameraController::resetCamera, &i_game.getSessionView().getCameraController())),
    Dx::ActionType::OnPress);


  map.setAction(
    Dx::MouseKey::Left,
    Dx::Action(std::bind(&GameController::tryPickObject, &i_game.getController())),
    Dx::ActionType::OnPress);


  map.setAction(
    Dx::KeyboardKey::F1,
    Dx::Action(std::bind(&Gui::switchDebugMenu, &i_game.getGui())),
    Dx::ActionType::OnPress);


  i_game.setActionsMap(std::move(map));
}
