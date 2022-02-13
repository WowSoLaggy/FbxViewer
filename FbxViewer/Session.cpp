#include "stdafx.h"
#include "Session.h"

#include "Object.h"


std::shared_ptr<Object>& Session::getBackground() { return d_background; }
const std::shared_ptr<Object>& Session::getBackground() const { return d_background; }
