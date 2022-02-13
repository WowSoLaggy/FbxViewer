#include "stdafx.h"

#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  std::string filePath = lpCmdLine;
  filePath.erase(remove(filePath.begin(), filePath.end(), '\"'), filePath.end());

  Game(filePath).run();
  return 0;
}
