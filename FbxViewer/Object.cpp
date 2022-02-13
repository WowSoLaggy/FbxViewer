#include "stdafx.h"
#include "Object.h"

#include "ObjectView.h"

#include <LaggyDx/IModel.h>


Object::Object(const Prototype& i_prototype)
  : d_prototype(i_prototype)
{
}


const Prototype& Object::getPrototype() const { return d_prototype; }

Sdk::Vector3F Object::getPosition() const { return d_position; }
Sdk::Vector3F Object::getRotation() const { return d_rotation; }
Sdk::Vector3F Object::getScale() const { return d_scale; }
void Object::setPosition(Sdk::Vector3F i_position) { d_position = std::move(i_position); }
void Object::setRotation(Sdk::Vector3F i_rotation) { d_rotation = std::move(i_rotation); }
void Object::setScale(Sdk::Vector3F i_scale) { d_scale = std::move(i_scale); }


void Object::update(double i_dt)
{
  d_animationTime += i_dt;
}


void Object::setAnimation(std::string i_name, bool i_loop)
{
  d_animationName = std::move(i_name);
  d_animationTime = 0.0;
  d_animationLoop = i_loop;
}

const std::string& Object::getAnimation() const
{
  return d_animationName;
}

bool Object::hasAnimation() const
{
  return !d_animationName.empty();
}

double Object::getAnimationTime() const
{
  return d_animationTime;
}


void Object::onAnimationEnd(const double i_animLength)
{
  if (!d_animationLoop)
  {
    d_animationName = "";
    d_animationTime = 0.0;
  }
  else
    d_animationTime -= i_animLength;
}


void Object::attachView(const ObjectView& i_objectView)
{
  d_objectView = &i_objectView;
}

void Object::dettachView()
{
  d_objectView = nullptr;
}

const ObjectView* Object::getView() const
{
  return d_objectView;
}


std::optional<Dx::Aabb> Object::getAabb() const
{
  if (const auto* view = getView())
    return view->getModel().getAabb();
  return std::nullopt;
}

std::optional<Dx::Obb> Object::getObb() const
{
  if (const auto* view = getView())
    return Dx::Obb{ view->getModel().getAabb(), getPosition(), getRotation() };
  return std::nullopt;
}
