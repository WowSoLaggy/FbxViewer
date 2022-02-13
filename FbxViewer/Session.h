#pragma once

#include "Fwd.h"
#include "SessionView.h"

#include <LaggySdk/Vector.h>


class Session
{
public:
  std::shared_ptr<Object>& getBackground();
  const std::shared_ptr<Object>& getBackground() const;

private:
  std::shared_ptr<Object> d_background;
};
