#include "Common.h"
#include "GameSprite.h"
#include "SpriteCollisions.h"

using namespace std;
using namespace sf;

void TestTransform()
{
   std::cout << "TestTransform" << std::endl;
   //std::cout << "TestTransform\n" << textureFile << std::endl;
   Sprite sprite;
   Image image;
   //auto imageFile = "E:/CppGamesVladimir/Work/Sprites/FW_Demon_Lord/PNG/FW_Demon_Lord_Jumping__000.png";
   auto imageFile = "E:/CppGamesVladimir/Work/Sprites/Test32.png";
   image.loadFromFile(imageFile);
   auto sz = image.getSize();
   std::cout << "Image Size = " << sz.x << ", " << sz.y << std::endl;

   //sprite.setOrigin(10,10);

   sprite.setPosition(100, 100);

   auto& inverse = sprite.getInverseTransform();
   auto p0 = inverse.transformPoint(100, 100);
   auto p1 = inverse.transformPoint(115, 85);
   std::cout << "p0 = " << p0.x << ", " << p0.y << std::endl;
   std::cout << "p1 = " << p1.x << ", " << p1.y << std::endl;

   Color color;
   auto center = spriteColor(sprite, image, 100, 100, color);

   std::cout << "(100, 100) = " << center << " (" << int(color.r) << ", " << int(color.g) << ", " << int(color.b) << "; " << int(color.a) << ")" << std::endl;

   center = spriteColor(sprite, image, 110, 100, color);
   std::cout << "(110, 100) = " << center << " (" << int(color.r) << ", " << int(color.g) << ", " << int(color.b) << "; " << int(color.a) << ")" << std::endl;

   center = spriteColor(sprite, image, 116, 84, color);
   std::cout << "(116, 84) = " << center << " (" << int(color.r) << ", " << int(color.g) << ", " << int(color.b) << "; " << int(color.a) << ")" << std::endl;

   center = spriteColor(sprite, image, 114, 86, color);
   std::cout << "(114, 86) = " << center << " (" << int(color.r) << ", " << int(color.g) << ", " << int(color.b) << "; " << int(color.a) << ")" << std::endl;

   center = spriteColor(sprite, image, 114, 115, color);
   std::cout << "(114, 115) = " << center << " (" << int(color.r) << ", " << int(color.g) << ", " << int(color.b) << "; " << int(color.a) << ")" << std::endl;
}
