#pragma once

#include "Fwd.h"

#include <LaggyDx/LaggyDxFwd.h>


class ObjectInfo
{
public:
  ObjectInfo(Dx::Panel& i_panel, Dx::Label& i_label);

  void show() const;
  void hide() const;

  void setObject(const Object& i_object) const;

private:
  Dx::Panel& d_panel;
  Dx::Label& d_label;
};
