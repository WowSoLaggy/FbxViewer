#include "stdafx.h"
#include "ObjectInfo.h"

#include "Object.h"
#include "Prototype.h"

#include <LaggyDx/Label.h>
#include <LaggyDx/Panel.h>


ObjectInfo::ObjectInfo(Dx::Panel& i_panel, Dx::Label& i_label)
  : d_panel(i_panel)
  , d_label(i_label)
{
}


void ObjectInfo::show() const
{
  d_panel.setVisible(true);
}

void ObjectInfo::hide() const
{
  d_panel.setVisible(false);
}


void ObjectInfo::setObject(const Object& i_object) const
{
  const std::string text = i_object.getPrototype().name + " (" + std::to_string(i_object.getId()) + ")";
  d_label.setText(text);
}
