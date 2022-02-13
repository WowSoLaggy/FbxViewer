#include "stdafx.h"
#include "CreateSession.h"


namespace
{
  void createBackground(Session& i_session)
  {
    auto background = std::make_shared<Object>("plane.fbx", "map.jpg");

    background->setPosition({ 0, 0, -0.01f });
    background->setScale({ 1, 1, 1 });

    i_session.getBackground() = std::move(background);
  }

  void createObject(Session& i_session, fs::path i_modelPath)
  {
    auto object = std::make_shared<Object>(std::move(i_modelPath));
    i_session.getObject() = std::move(object);
  }

} // anonym NS


std::unique_ptr<Session> createSession(fs::path i_modelPath)
{
  auto session = std::make_unique<Session>();
  
  createBackground(*session);
  createObject(*session, std::move(i_modelPath));

  return session;
}
