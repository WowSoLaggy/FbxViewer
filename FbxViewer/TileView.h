#pragma once

#include "Fwd.h"
#include "ObjectView.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/EventHandler.h>


class TileView : public Sdk::EventHandler
{
public:
  TileView(Tile& i_tile, const Dx::IResourceController& i_resourceController);

  void update();
  void render(Dx::ISimpleRenderer& i_renderer) const;

  virtual void processEvent(const Sdk::IEvent& i_event) override;

private:
  const Dx::IResourceController& d_resourceController;

  ObjectView d_tileView;
  std::vector<std::shared_ptr<ObjectView>> d_objectViews;

  void addView(Object& i_object);
  void removeView(Object& i_object);

  void onObjectAdded(Object& i_object);
  void onObjectRemoved(Object& i_object);
};
