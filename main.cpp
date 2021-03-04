#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
#include "view.h"
#include "mission.h"
#include <sstream>
using namespace sf;

class Player { // класс Игрока
public:
 float x, y, w, h, dx, dy, speed ; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
 int dir ; //направление (direction) движения игрока
 std::string File; //файл с расширением
 Image image;//сфмл изображение
 Texture texture;//сфмл текстура
 Sprite sprite;//сфмл спрайт

  Player(std::string F, float X, float Y, float W, float H){ //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
     dx=0;dy=0;speed=0;dir=0;
     File = F;//имя файла+расширение
     w = W; h = H;//высота и ширина
     x = X; y = Y;//координата появления спрайта
     image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
     texture.loadFromImage(image);//закидываем наше изображение в текстуру
     sprite.setTexture(texture);//заливаем спрайт текстурой
     sprite.setTextureRect(IntRect(x, y, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
  }

  void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
     {
         switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
         {
             case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
             case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
             case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
             case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
         }

         x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
         y += dy*time;//аналогично по игреку

         speed = 0;//зануляем скорость, чтобы персонаж остановился.
         sprite.setPosition(x,y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
    }
};

int main()
{
    std::string heroImg = "hero.png";
    Player p(heroImg,535,245,85,140);

	RenderWindow window(sf::VideoMode(800, 400), "no mercy morning");

    Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

    Clock clock;
    Image heroimage;
    Texture herotexture;
    Sprite herosprite;

    float CurrentFrame=0;

	heroimage.loadFromFile("images/hero.png");//загружаем в него файл
    heroimage.createMaskFromColor(Color(254, 254, 254));
	herotexture.loadFromImage(heroimage);
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(535,245,85,140));//стоя

	//290px



	//анимация движения
	//herosprite.setTextureRect(IntRect(390,245,85,140));
    //herosprite.setTextureRect(IntRect(245,245,85,140));
	//herosprite.setTextureRect(IntRect(100,245,85,140));

	herosprite.setPosition(50, 25);


	while (window.isOpen())
	{
		sf::Event event;
        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time/800; //скорость игры

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            p.dir = 1; p.speed = 0.1;
            CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) {
                p.sprite.setTextureRect(IntRect(245,245,85,140));
                CurrentFrame -= 3;
			}
            p.sprite.move(-0.1*time, 0);
            p.sprite.setTextureRect(IntRect(390,245,85,140));
            p.sprite.setScale(-1, 1);
        }
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
            p.dir = 0; p.speed = 0.1;
            CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
		    p.sprite.move(0.1*time, 0);
            p.sprite.setTextureRect(IntRect(390,245,85,140));
        }
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
		    p.dir = 3; p.speed = 0.1;
		    CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
            p.sprite.move(0, -0.1*time);
            std::cout << 1;
        }
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
		    p.dir = 2; p.speed = 0.1;
		    CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
            p.sprite.move(0, 0.1*time);
        }

        //p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


			s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

			window.draw(s_map);//рисуем квадратики на экран
            }
        }

		window.draw(p.sprite);//рисуем спрайт объекта p класса player
		window.display();
	}

	return 0;
}

