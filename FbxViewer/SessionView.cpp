#include "stdafx.h"
#include "SessionView.h"

#include "CameraController.h"
#include "Game.h"

#include <LaggyDx/ISimpleRenderer.h>


namespace
{
  float getCharSize(const Object& i_object)
  {
    if (const auto aabbOpt = i_object.getAabb())
    {
      const float xSize = aabbOpt->getMaxX() - aabbOpt->getMinX();
      const float ySize = aabbOpt->getMaxY() - aabbOpt->getMinY();
      return std::max(xSize, ySize);
    }

    return 1.0f;
  }

} // anon NS


SessionView::SessionView(Game& i_game)
  : d_game(i_game)
  , d_cameraController(i_game)
  , d_simpleRenderer(Dx::ISimpleRenderer::getOrCreate(
      i_game.getRenderDevice(), d_cameraController.getCamera(), i_game.getResourceController()))
  , d_session(i_game.getSession())
  , d_resourceController(i_game.getResourceController())
  , d_backgroundView(*i_game.getSession().getBackground(), i_game.getResourceController(), i_game.getRenderDevice())
  , d_objectView(*i_game.getSession().getObject(), i_game.getResourceController(), i_game.getRenderDevice())
{
}


CameraController& SessionView::getCameraController()
{
  return d_cameraController;
}

const CameraController& SessionView::getCameraController() const
{
  return d_cameraController;
}


void SessionView::render()
{
  d_simpleRenderer.setDrawAabb(d_drawBb);

  d_simpleRenderer.draw(d_backgroundView);
  d_simpleRenderer.draw(d_objectView);

  d_simpleRenderer.setDrawAabb(false);
}


void SessionView::update(const double i_dt)
{
  d_cameraController.update(i_dt);
  d_backgroundView.update();
  d_objectView.update();
}


void SessionView::setDrawBb(const bool i_drawBb)
{
  d_drawBb = i_drawBb;
}
