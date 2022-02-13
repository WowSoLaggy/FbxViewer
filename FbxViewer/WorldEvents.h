#pragma once

#include "Fwd.h"

#include <LaggySdk/IEvent.h>


class ObjectEvent : public Sdk::IEvent
{
public:
  ObjectEvent(Object& i_object)
    : d_object(i_object)
  {
  }

  Object& getObject() const { return d_object; }

private:
  Object& d_object;
};

class ObjectAddedEvent : public ObjectEvent
{
public:
  ObjectAddedEvent(Object& i_object)
    : ObjectEvent(i_object)
  {
  }
};

class ObjectRemovedEvent : public ObjectEvent
{
public:
  ObjectRemovedEvent(Object& i_object)
    : ObjectEvent(i_object)
  {
  }
};
