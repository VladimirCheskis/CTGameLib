#include "Common.h"
#include "FoldersAndPathes.h"
#include <iostream>

#include <Windows.h>

string WorkFolder;
string ResourcesFolder;
string SoundsFolder;
string FontFile;
string SpritesFolder;
string DemonPNG;
string WizardPNG;
string FontsFolder;

void initFoldersAndPathes()
{
  char buf[1024];
  GetCurrentDirectory(1024, buf);
  std::cout << "dir: " << buf << std::endl;

  WorkFolder = buf;
  if (WorkFolder.back() != '/')
    WorkFolder += '/';

  ResourcesFolder = WorkFolder + "Resources/";

  SoundsFolder  = ResourcesFolder + "Sounds/";
  SpritesFolder = ResourcesFolder + "Sprites/";
  FontsFolder   = ResourcesFolder + "Fonts/";

  FontFile      = FontsFolder + "CyrilicOld.TTF";

  DemonPNG      = SpritesFolder + "FW_Demon_Lord/PNG/FW_Demon_Lord_";
  WizardPNG     = SpritesFolder + "Wizard/PNG/FW_Hero_1_";
}
