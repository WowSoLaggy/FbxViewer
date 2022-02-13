#include "stdafx.h"
#include "ObjectView.h"

#include "Object.h"
#include "Prototype.h"

#include <LaggyDx/FbxResource.h>
#include <LaggyDx/IResourceController.h>


ObjectView::ObjectView(Object& i_object, const Dx::IResourceController& i_resourceController)
  : d_object(i_object)
{
  const auto& ifbxResource = i_resourceController.getFbxResource(d_object.getPrototype().modelFilepath);
  const auto* fbxResource = dynamic_cast<const Dx::FbxResource*>(&ifbxResource);
  CONTRACT_ASSERT(fbxResource);
  d_model = &fbxResource->getModel();

  if (!d_object.getPrototype().textureFilepath.empty())
    d_textureResource = &i_resourceController.getTextureResource(d_object.getPrototype().textureFilepath);
  else
    d_textureResource = nullptr;
}


const Object& ObjectView::getObject() const
{
  return d_object;
}


void ObjectView::update()
{
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
