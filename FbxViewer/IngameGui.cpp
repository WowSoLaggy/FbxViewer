#include "stdafx.h"
#include "IngameGui.h"

#include <LaggyDx/Label.h>
#include <LaggyDx/Panel.h>


IngameGui::IngameGui(Dx::Panel& i_panel, Dx::Label& i_turnLabel)
  : d_panel(i_panel)
  , d_turnLabel(i_turnLabel)
{
}


void IngameGui::show()
{
  d_panel.setVisible(true);
}

void IngameGui::hide()
{
  d_panel.setVisible(false);
}


void IngameGui::setTurn(const int i_turn)
{
  d_turnLabel.setText("Turn: " + std::to_string(i_turn));
}
