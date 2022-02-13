#include "stdafx.h"
#include "TileView.h"

#include "Object.h"
#include "Tile.h"
#include "WorldEvents.h"

#include <LaggyDx/ISimpleRenderer.h>


TileView::TileView(Tile& i_tile, const Dx::IResourceController& i_resourceController)
  : d_resourceController(i_resourceController)
  , d_tileView(i_tile, i_resourceController)
{
  auto createViews = [&](const auto i_objs)
  {
    for (const auto objPtr : i_objs)
      addView(*objPtr);
  };

  createViews(i_tile.getStructures());
  createViews(i_tile.getArmies());

  connectTo(i_tile);
}


void TileView::update()
{
  for (auto& view : d_objectViews)
    view->update();
}

void TileView::render(Dx::ISimpleRenderer& i_renderer) const
{
  i_renderer.draw(d_tileView);

  for (auto& view : d_objectViews)
    i_renderer.draw(*view);
}


void TileView::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* objectAddedEvent = dynamic_cast<const ObjectAddedEvent*>(&i_event))
    onObjectAdded(objectAddedEvent->getObject());
  else if (const auto* objectRemovedEvent = dynamic_cast<const ObjectRemovedEvent*>(&i_event))
    onObjectRemoved(objectRemovedEvent->getObject());
}


void TileView::addView(Object& i_object)
{
  auto objectViewPtr = std::make_shared<ObjectView>(i_object, d_resourceController);
  d_objectViews.push_back(objectViewPtr);

  i_object.attachView(*objectViewPtr);
}

void TileView::removeView(Object& i_object)
{
  d_objectViews.erase(std::remove_if(d_objectViews.begin(), d_objectViews.end(),
    [&](const auto& i_ptr) { return &i_ptr->getObject() == &i_object; }), d_objectViews.end());

  i_object.dettachView();
}


void TileView::onObjectAdded(Object& i_object)
{
  addView(i_object);
}

void TileView::onObjectRemoved(Object& i_object)
{
  removeView(i_object);
}
