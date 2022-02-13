#pragma once

#include "Fwd.h"

#include <LaggyDx/Obb.h>
#include <LaggySdk/EventHandler.h>
#include <LaggySdk/IUniqueId.h>
#include <LaggySdk/Vector.h>


class Object : public Sdk::EventHandler, public Sdk::IUniqueId
{
public:
  Object(const Prototype& i_prototype);

  const Prototype& getPrototype() const;

  virtual Sdk::Vector3F getPosition() const;
  virtual Sdk::Vector3F getRotation() const;
  virtual Sdk::Vector3F getScale() const;
  virtual void setPosition(Sdk::Vector3F i_position);
  virtual void setRotation(Sdk::Vector3F i_rotation);
  virtual void setScale(Sdk::Vector3F i_scale);

  virtual void update(double i_dt);

  void setAnimation(std::string i_name, bool i_loop);
  const std::string& getAnimation() const;
  bool hasAnimation() const;
  double getAnimationTime() const;

  void onAnimationEnd(double i_animLength);

  void attachView(const ObjectView& i_objectView);
  void dettachView();
  const ObjectView* getView() const;

  std::optional<Dx::Aabb> getAabb() const;
  std::optional<Dx::Obb> getObb() const;

private:
  const Prototype& d_prototype;

  Sdk::Vector3F d_position;
  Sdk::Vector3F d_rotation;
  Sdk::Vector3F d_scale = Sdk::Vector3F::identity();

  std::string d_animationName;
  double d_animationTime = 0.0;
  bool d_animationLoop = false;

  const ObjectView* d_objectView = nullptr;
};
