#include "stdafx.h"
#include "MenuCreator.h"

#include "Game.h"
#include "GameController.h"
#include "SessionView.h"

#include <LaggyDx/Button.h>
#include <LaggyDx/Checkbox.h>
#include <LaggyDx/IFontResource.h>
#include <LaggyDx/Label.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/Panel.h>


namespace
{
  template <typename T>
  std::shared_ptr<T> createControl(Dx::IControl& i_parent)
  {
    auto ctrl = std::make_shared<T>();
    i_parent.addChild(ctrl);
    return ctrl;
  }

  std::shared_ptr<Dx::Label> createLabel(Dx::IControl& i_parent)
  {
    auto ctrl = createControl<Dx::Label>(i_parent);
    ctrl->setFont("play.spritefont");
    return ctrl;
  };

  std::shared_ptr<Dx::Button> createButton(Dx::IControl& i_parent)
  {
    auto ctrl = createControl<Dx::Button>(i_parent);
    ctrl->setFont("play.spritefont");
    ctrl->setTextureName(Dx::ButtonState::Normal, "btn_normal.png");
    ctrl->setTextureName(Dx::ButtonState::Hover, "btn_light.png");
    ctrl->setTextureName(Dx::ButtonState::Pressed, "btn_pressed.png");
    return ctrl;
  };

  std::shared_ptr<Dx::Checkbox> createCheckbox(Dx::IControl& i_parent)
  {
    auto ctrl = createControl<Dx::Checkbox>(i_parent);
    ctrl->setTextureName(Dx::CheckboxState::Normal, "cb_normal.png");
    ctrl->setTextureName(Dx::CheckboxState::Ticked, "cb_ticked.png");
    ctrl->setTextureName(Dx::CheckboxState::HoverTicked, "cb_hover_ticked.png");
    ctrl->setTextureName(Dx::CheckboxState::HoverUnticked, "cb_hover_unticked.png");
    return ctrl;
  };

  std::shared_ptr<Dx::Panel> createPanel(Dx::IControl& i_parent)
  {
    auto ctrl = createControl<Dx::Panel>(i_parent);
    return ctrl;
  }

} // anon NS


MenuCreator::MenuCreator(Game& i_game)
  : d_game(i_game)
{
}


void MenuCreator::clearAll(Dx::IControl& i_parent) const
{
  i_parent.removeChildren();
}

void MenuCreator::createMainMenu(Dx::IControl& i_parent) const
{
  const auto resolution = d_game.getRenderDevice().getResolution();

  {
    auto versionLabel = createLabel(i_parent);
    versionLabel->setText("Welcome to General!");
    const auto textSize = versionLabel->getFontResource()->getStringRect(versionLabel->getText());
    versionLabel->setPosition({ float(resolution.x - textSize.width()) / 2.0f, 32 });
  }


  auto layoutButtons = std::make_shared<Dx::Layout>();
  i_parent.addChild(layoutButtons);
  layoutButtons->setSize({ (float)resolution.x, (float)resolution.y });
  layoutButtons->setOffset(32);
  layoutButtons->setOffsetFromBorder(64);


  {
    auto btnNewGame = createButton(*layoutButtons);
    btnNewGame->setText("New Game");
    btnNewGame->setOnPress(std::bind(&GameController::onNewGameClick, &d_game.getController()));
  }

  {
    auto btnExitGame = createButton(*layoutButtons);
    btnExitGame->setText("Exit Game");
    btnExitGame->setOnPress(std::bind(&GameController::onExitClick, &d_game.getController()));
  }
}


std::shared_ptr<Dx::IControl> MenuCreator::createDebugMenu(Dx::IControl& i_parent) const
{
  auto debugPanel = createPanel(i_parent);
  debugPanel->setTexture("gray128.png");
  debugPanel->setPosition({ 16, 16 });

  auto cbShowBb = createCheckbox(*debugPanel);
  cbShowBb->setPosition({ 16, 16 });
  auto meow = std::bind(&SessionView::setDrawBb, &d_game.getSessionView());
  cbShowBb->setOnCheck(std::bind(&SessionView::setDrawBb, &d_game.getSessionView(), std::placeholders::_1));

  auto lblShowBb = createLabel(*debugPanel);
  lblShowBb->setText("Show Bounding Boxes");
  const auto textSize = lblShowBb->getFontResource()->getStringRect(lblShowBb->getText());
  lblShowBb->setPosition({ 56, 32.0f - textSize.height2() });

  debugPanel->setSize({ lblShowBb->getPosition().x + textSize.width(), 64 });
  
  return debugPanel;
}

ObjectInfo MenuCreator::createObjectInfo(Dx::IControl& i_parent) const
{
  const auto resolution = d_game.getRenderDevice().getResolution();

  auto panel = createPanel(i_parent);
  panel->setTexture("brown.png");
  panel->setSize({ 300, 75 });
  panel->setPosition({ 16, (float)resolution.y - panel->getSize().y - 16 });

  auto label = createLabel(*panel);
  label->setPosition({ 16, 16 });
  
  return ObjectInfo{ *panel, *label };
}

IngameGui MenuCreator::createIngameGui(Dx::IControl& i_parent) const
{
  const auto resolution = d_game.getRenderDevice().getResolution();

  auto panel = createPanel(i_parent);
  panel->setTexture("brown.png");
  panel->setSize({ (float)resolution.x, 32 });

  auto label = createLabel(*panel);
  label->setPosition({ (float)resolution.x - 150, -3 });

  return IngameGui{ *panel, *label };
}
