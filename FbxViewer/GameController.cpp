#include "stdafx.h"
#include "GameController.h"

#include "ActionsController.h"
#include "CreateSession.h"
#include "Game.h"
#include "GameEvents.h"
#include "ObjectPicker.h"

#include <LaggyDx/IModel.h>


GameController::GameController(Game& i_game)
  : d_game(i_game)
{
  connectTo(d_game);
}


void GameController::processEvent(const Sdk::IEvent& i_event)
{
  if (dynamic_cast<const GameStartedEvent*>(&i_event))
    d_game.getGui().showMainMenu();
}


void GameController::onNewGameClick()
{
  d_game.getGui().hideMainMenu();

  d_game.attachSession(createSession());
  d_game.attachSessionView();

  ActionsController().createActionsInGame(d_game);

  d_game.getGui().showIngameGui();
  onNewTurn();
}

void GameController::onExitClick() const
{
  d_game.stop();
}


void GameController::tryPickObject()
{
  if (const auto* obj = ObjectPicker(d_game).pick())
  {
    if (obj != d_pickedObject)
      pickObject(*obj);
  }
  else if (isObjectPicked())
    unpickObject();
}

void GameController::pickObject(const Object& i_object)
{
  d_pickedObject = &i_object;
  d_game.getGui().showObjectInfo(i_object);
}

void GameController::unpickObject()
{
  d_game.getGui().hideObjectInfo();
  d_pickedObject = nullptr;
}

bool GameController::isObjectPicked() const
{
  return d_pickedObject != nullptr;
}

const Object* GameController::getPickedObject() const
{
  return d_pickedObject;
}


void GameController::onNewTurn()
{
  ++d_turn;
  d_game.getGui().setTurn(d_turn);
}
