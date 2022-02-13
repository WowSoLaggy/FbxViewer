#pragma once

#include "GameState.h"

#include <LaggySdk/ITransition.h>


class GameStateTransition : public Sdk::ITransition
{
public:
  GameStateTransition(std::shared_ptr<GameState> i_sourceState, std::shared_ptr<GameState> i_destState);

  virtual std::shared_ptr<Sdk::IState> getSourceState() const override;
  virtual std::shared_ptr<Sdk::IState> getDestState() const override;

private:
  std::shared_ptr<GameState> d_sourceState;
  std::shared_ptr<GameState> d_destState;
};
