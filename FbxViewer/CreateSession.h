#pragma once

#include "Session.h"


std::unique_ptr<Session> createSession(fs::path i_modelPath);
