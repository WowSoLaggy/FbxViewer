#include "stdafx.h"
#include "GameStateTransition.h"


GameStateTransition::GameStateTransition(std::shared_ptr<GameState> i_sourceState, std::shared_ptr<GameState> i_destState)
  : d_sourceState(std::move(i_sourceState))
  , d_destState(std::move(i_destState))
{
  CONTRACT_EXPECT(d_sourceState);
  CONTRACT_EXPECT(d_destState);
}


std::shared_ptr<Sdk::IState> GameStateTransition::getSourceState() const
{
  return d_sourceState;
}

std::shared_ptr<Sdk::IState> GameStateTransition::getDestState() const
{
  return d_destState;
}
