#include "stdafx.h"
#include "Game.h"

#include "GameEvents.h"
#include "RenderSettings.h"
#include "Session.h"

#include <LaggyDx/Colors.h>
#include <LaggyDx/GameSettings.h>


namespace
{
  const Dx::GameSettings& getGameSettings()
  {
    static const Dx::GameSettings gameSettings{ 1200, 900, "General", "Data/Assets/" };
    return gameSettings;
  }

} // anon NS


Game::Game(fs::path i_modelPath)
  : Dx::Game(getGameSettings())
  , d_modelPath(std::move(i_modelPath))
{
  getInputDevice().showCursor();
  getRenderDevice().setClearColor(RenderSettings::ClearColor);

  d_controller = std::make_unique<GameController>(*this);
  d_gui = std::make_unique<Gui>(*this);

  notify(GameStartedEvent());
}


const fs::path& Game::getModelPath() const
{
  return d_modelPath;
}


void Game::update(const double i_dt)
{
  if (d_session)
    d_session->udpate(i_dt);
  if (d_sessionView)
    d_sessionView->update(i_dt);

  Dx::Game::update(i_dt);
}


void Game::render()
{
  if (d_sessionView)
    d_sessionView->render();

  Dx::Game::render();
}


void Game::attachSession(std::unique_ptr<Session> i_session)
{
  d_session = std::move(i_session);
}

void Game::attachSessionView()
{
  d_sessionView = std::make_unique<SessionView>(*this);
}


GameController& Game::getController() const
{
  CONTRACT_ASSERT(d_controller);
  return *d_controller;
}

Gui& Game::getGui() const
{
  CONTRACT_ASSERT(d_gui);
  return *d_gui;
}

Session& Game::getSession() const
{
  CONTRACT_ASSERT(d_session);
  return *d_session;
}

SessionView& Game::getSessionView() const
{
  CONTRACT_ASSERT(d_sessionView);
  return *d_sessionView;
}
