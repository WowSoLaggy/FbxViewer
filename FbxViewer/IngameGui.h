#pragma once

#include <LaggyDx/LaggyDxFwd.h>


class IngameGui
{
public:
  IngameGui(Dx::Panel& i_panel, Dx::Label& i_turnLabel);

  void show();
  void hide();

  void setTurn(int i_turn);

private:
  Dx::Panel& d_panel;
  Dx::Label& d_turnLabel;
};
