#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GameLib.h"
#include "FileUtils.h"

using namespace std;
using namespace sf;

int main()
{
    /// ������������� ���� � ������ ������ � ������
    initFoldersAndPathes();

    auto test = createAnimatorFromFiles(DemonPNG + "Attack__", false);

    /// ������ �����, (������, ������)
    GameScene gameScene(712,    512   );

    /// ������ � ��������� � ����� �������, ������ ��� ��� �������

    /// ������� ����: ������������ ���������, ����������� �������,
    /// ���� ���� �� �������
	while (gameScene.tick());

	return 0;
}
