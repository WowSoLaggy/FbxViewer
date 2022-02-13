#pragma once

#include "GameController.h"
#include "Gui.h"
#include "Session.h"
#include "SessionView.h"

#include <LaggyDx/Game.h>
#include <LaggySdk/EventHandler.h>


class Game : public Dx::Game, public Sdk::EventHandler
{
public:
  Game();

  virtual void update(double i_dt) override;
  virtual void render() override;

  void attachSession(std::unique_ptr<Session> i_session);
  void attachSessionView();

  GameController& getController() const;
  Gui& getGui() const;
  Session& getSession() const;
  SessionView& getSessionView() const;

private:
  std::unique_ptr<GameController> d_controller;
  std::unique_ptr<Gui> d_gui;
  std::unique_ptr<Session> d_session;
  std::unique_ptr<SessionView> d_sessionView;
};
