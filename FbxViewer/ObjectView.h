#pragma once

#include "Fwd.h"

#include <LaggyDx/IObject3.h>
#include <LaggyDx/LaggyDxFwd.h>


class ObjectView : public Dx::IObject3
{
public:
  ObjectView(Object& i_object, const Dx::IResourceController& i_resourceController);

  const Object& getObject() const;

  void update();

  virtual Sdk::Vector3F getPosition() const override;
  virtual Sdk::Vector3F getRotation() const override;
  virtual Sdk::Vector3F getScale() const override;

  virtual const Dx::IModel& getModel() const override;
  virtual const Dx::ITextureResource* getTextureResource() const override;

private:
  Object& d_object;

  const Dx::IModel* d_model = nullptr;
  const Dx::ITextureResource* d_textureResource = nullptr;

  const Dx::Animation* getAnimation() const;
};
