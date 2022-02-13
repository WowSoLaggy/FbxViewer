#include "stdafx.h"
#include "Session.h"

#include "Object.h"


std::shared_ptr<Object>& Session::getBackground() { return d_background; }
const std::shared_ptr<Object>& Session::getBackground() const { return d_background; }


std::shared_ptr<Object>& Session::getObject() { return d_object; }
const std::shared_ptr<Object>& Session::getObject() const { return d_object; }


void Session::udpate(double i_dt) const
{
  if (d_background)
    d_background->update(i_dt);
  if (d_object)
    d_object->update(i_dt);
}
