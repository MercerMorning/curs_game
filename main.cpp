#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
#include "view.h"
#include "mission.h"
#include <sstream>
using namespace sf;

class Ball {
    private: float x, y, w, h;
    public:
        std::string File;
         Image image;//сфмл изображение
         Texture texture;//сфмл текстура
         Sprite sprite;//сфмл спрайт
    Ball(std::string F, float X, float Y, float W, float H){
        File = F;
        w = W; h = H;//высота и ширина
         x = X; y = Y;//координата появления спрайта
         image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
         /*image.createMaskFromColor(Color(230, 230, 230));
         image.createMaskFromColor(Color(255, 255, 255));*/
         texture.loadFromImage(image);//закидываем наше изображение в текстуру
         sprite.setTexture(texture);//заливаем спрайт текстурой
         sprite.setTextureRect(IntRect(x, y, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
    }
    void setpos (float Xpos, float Ypos){
        sprite.setPosition(Xpos, Ypos);
    }
};

class Player { // класс Игрока
private: float x,y;
public:
 bool isShot = false;
 float w, h, dx, dy, speed ; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
 int dir,playerScore;//направление (direction) движения игрока
 std::string File; //файл с расширением
 Image image;//сфмл изображение
 Texture texture;//сфмл текстура
 Sprite sprite;//сфмл спрайт

  Player(std::string F, float X, float Y, float W, float H){ //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
     dx=0;dy=0;
     speed=0;dir=0;
     playerScore = 0;
     File = F;//имя файла+расширение
     w = W; h = H;//высота и ширина
     x = X; y = Y;//координата появления спрайта
     image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
     /*image.createMaskFromColor(Color(230, 230, 230));
     image.createMaskFromColor(Color(255, 255, 255));*/
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
         interactionWithMap();
         sprite.setPosition(x,y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
    }

    void interactionWithMap()//ф-ция взаимодействия с картой
	{

			for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
                for (int j = x / 32; j < (x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
                {
                    if (TileMap[i][j] == '0' || TileMap[i][j] == '1')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                    {
                        if (dy>0)//если мы шли вниз,
                        {
                            y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                        }
                        if (dy<0)
                        {
                            y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                        }
                        /*
                        if (dx>0)
                        {
                            x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                        }
                        if (dx < 0)
                        {
                            x = j * 32 + 32;//аналогично идем влево
                            y =  i * 6 * 32;
                        }*/
                    }
                    if (TileMap[i][j] == 't') {

                        if (dx < 0)
                        {

                            x = j * 32 + 32;//аналогично идем влево
                            y =  (i * 32) - (2 * 10);

                        }
                    }
                    if (TileMap[i][j] == 'p') {

                        if (dx > 0)
                        {
                            x = j * 32 - w;
                            y =  (i * 32) + (2 * 10);
                        }
                    }

				if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
                    playerScore++;//если взяли камень, переменная playerScore=playerScore+1;
                    TileMap[i][j] = ' ';
				}
			}
	}

    float getplayercoordinateX(){	//этим методом будем забирать координату Х
		return x;
	}

	float getplayercoordinateY(){	//этим методом будем забирать координату Y
		return y;
	}
};

int main()
{
    std::string heroImg = "hero.png";
    Player p(heroImg,535,245,85,140);
    Ball b(heroImg,535,245,85,140);

    bool showMissionText = true;

	RenderWindow window(sf::VideoMode(800, 400), "no mercy morning");

    view.reset(sf::FloatRect(0, 0, 640, 480));//размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.

    Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше

    Font font;//шрифт
    font.loadFromFile("CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
    Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

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

	/*heroimage.loadFromFile("images/hero.png");//загружаем в него файл
    heroimage.createMaskFromColor(Color(254, 254, 254));
	herotexture.loadFromImage(heroimage);
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(535,245,85,140));//стоя*/

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

        Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)




        /*if (p.isShot)
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
			if (event.key.code == Mouse::Right){//а именно правая
				p.isMove = true;//то начинаем движение
				p.isSelect = false;//объект уже не выбран
				p.sprite.setColor(Color::White);//возвращаем обычный цвет спрайту
				tempX = pos.x;//забираем координату нажатия курсора Х
				tempY = pos.y;//и Y

			}*/

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

             if (event.type == Event::KeyPressed)//событие нажатия клавиши

               if (event.key.code == Keyboard::Q){//а именно левая
                    //if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
                    //{
                        //std::cout << '1';
                        b.setpos(p.getplayercoordinateX(), p.getplayercoordinateY());
                        b.sprite.setColor(Color::Red);//красим спрайт в зеленый,тем самым говоря игроку,что он выбрал персонажа и может сделать ход
                        //p.isShot = true;
                    //}
                }


                 if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ


                     switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

                     case true: {
                             std::ostringstream playerHealthString;//строка здоровья игрока
                             //playerHealthString << p.health; //заносим в строку здоровье
                             std::ostringstream task;//строка текста миссии
                             task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
                             //text.setString("Здоровье: " + playerHealthString.str()+"\n" + task.str());//задаем
                             text.setString("text");
                             /*text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
                             s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока*/
                             showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
                             break;//выходим , чтобы не выполнить условие "false" (которое ниже)
                             }
                         case false: {
                             text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
                             showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
                             break;
                          }
                    }
             }
		}

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            p.dir = 1; p.speed = 0.1;
            CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) {
              //  p.sprite.setTextureRect(IntRect(245,245,85,140));
                CurrentFrame -= 3;
			}
            p.sprite.move(-0.1*time, 0);
            //p.sprite.setTextureRect(IntRect(390,245,85,140));
            //p.sprite.setScale(-1, 1);
        }
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
            p.dir = 0; p.speed = 0.1;
            CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
		    p.sprite.move(0.1*time, 0);
            //p.sprite.setTextureRect(IntRect(390,245,85,140));
        }
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
		    p.dir = 3; p.speed = 0.1;
		    CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
            p.sprite.move(0, -0.1*time);
        }
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
		    p.dir = 2; p.speed = 0.1;
		    CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
            p.sprite.move(0, 0.1*time);
        }

        window.setView(view);
        setplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
        p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ' || TileMap[i][j] == 't' || TileMap[i][j] == 'p')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
            if ((TileMap[i][j] == '1')) s_map.setTextureRect(IntRect(96, 64, 64, 64));

			s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

			window.draw(s_map);//рисуем квадратики на экран
            }
        }

        /*std::ostringstream playerScoreString;
        playerScoreString << p.playerScore;
		text.setString("Rocks:" + playerScoreString.str());
		text.setPosition(view.getCenter().x , view.getCenter().y );//задаем позицию текста, центр камеры*/
        if (!showMissionText) {
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока
			window.draw(s_quest); window.draw(text); //рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
		}

		window.draw(p.sprite);//рисуем спрайт объекта p класса player
		window.draw(text);//рисую этот текст
		 window.draw(b.sprite);
		window.display();
	}

	return 0;
}

