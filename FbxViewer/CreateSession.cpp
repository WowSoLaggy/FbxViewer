#include "stdafx.h"
#include "CreateSession.h"

#include "PrototypeCollection.h"


namespace
{
  void createBackground(Session& i_session)
  {
    auto background = std::make_shared<Object>(PrototypeCollection::get("map"));

    background->setPosition({ 0, 0, -0.01f });
    background->setScale({ 1, 1, 1 });

    i_session.getBackground() = std::move(background);
  }

} // anonym NS


std::unique_ptr<Session> createSession()
{
  auto session = std::make_unique<Session>();
  
  createBackground(*session);

  return session;
}
