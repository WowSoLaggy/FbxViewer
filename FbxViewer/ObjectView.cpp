#include "stdafx.h"
#include "ObjectView.h"

#include "Object.h"

#include <LaggyDx/FbxResource.h>
#include <LaggyDx/IResourceController.h>


ObjectView::ObjectView(
  Object& i_object,
  const Dx::IResourceController& i_resourceController,
  Dx::IRenderDevice& i_renderDevice)
  : d_object(i_object)
{
  if (!d_object.getTexturePath().empty())
    d_textureResource = &i_resourceController.getTexture(d_object.getTexturePath());
  else
    d_textureResource = nullptr;

  if (i_resourceController.hasResource(d_object.getModelPath()))
  {
    const auto& ifbxResource = i_resourceController.getFbx(d_object.getModelPath());
    const auto* fbxResource = dynamic_cast<const Dx::FbxResource*>(&ifbxResource);
    CONTRACT_ASSERT(fbxResource);
    d_model = &fbxResource->getModel();
  }
  else
  {
    d_fbx = std::make_shared<Dx::FbxResource>(d_object.getModelPath());
    auto* fbxResource = dynamic_cast<Dx::FbxResource*>(d_fbx.get());
    CONTRACT_ASSERT(fbxResource);
    fbxResource->load(i_renderDevice);
    d_model = &fbxResource->getModel();
  }
}


const Object& ObjectView::getObject() const
{
  return d_object;
}


void ObjectView::update()
{
  CONTRACT_ASSERT(d_model);

  if (!d_object.hasAnimation() && !d_model->getAnimations().empty())
    d_object.setAnimation(d_model->getAnimations().begin()->first, true);

  if (const auto* animation = getAnimation())
  {
    if (d_object.getAnimationTime() >= animation->length)
      d_object.onAnimationEnd(animation->length);
  }
}


const Dx::Animation* ObjectView::getAnimation() const
{
  if (!d_object.hasAnimation())
    return nullptr;

  CONTRACT_ASSERT(d_model);
  const auto& animations = d_model->getAnimations();
  const auto it = animations.find(d_object.getAnimation());
  if (it == animations.end())
    return nullptr;

  return &it->second;
}


Sdk::Vector3F ObjectView::getPosition() const
{
  const auto ownPos = d_object.getPosition();

  if (const auto* animation = getAnimation())
  {
    const auto animPos = animation->getTranslation(d_object.getAnimationTime());
    return ownPos + animPos;
  }

  return ownPos;
}

Sdk::Vector3F ObjectView::getRotation() const
{
  const auto ownRot = d_object.getRotation();

  if (const auto* animation = getAnimation())
  {
    const auto animRot = animation->getRotation(d_object.getAnimationTime());
    return ownRot + animRot;
  }

  return ownRot;
}

Sdk::Vector3F ObjectView::getScale() const
{
  const auto ownScale = d_object.getScale();

  if (const auto* animation = getAnimation())
  {
    const auto animScale = animation->getScale(d_object.getAnimationTime());
    return ownScale * animScale;
  }

  return ownScale;
}


const Dx::IModel& ObjectView::getModel() const
{
  CONTRACT_ASSERT(d_model);
  return *d_model;
}

const Dx::ITextureResource* ObjectView::getTextureResource() const
{
  return d_textureResource;
}
