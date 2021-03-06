#include <SFML/Graphics.hpp>
const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина

/*sf::String TileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0               s                       0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0              s    0000               0",
	"0           000000000000               0",
	"0           000000000000               0",
	"t   f    h  000000000000               0",
	"0000000000000000000000000000000000000000",
};*/

sf::String TileMap[HEIGHT_MAP] = {

	"t                                      p",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"1111111111111111111111111111111111111111",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"0000000000000000000000000000000000000000",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"t                                      p",
	"t                                      p",

};

void randomMapGenerate(){//рандомно расставляем камни

	int randomElementX = 0;//случайный элемент по горизонтали
	int randomElementY = 0;//случ эл-т по вертикали
	srand(time(0));//рандом
	int countStone = 2;//количество камней

	while (countStone>0){
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

		if (TileMap[randomElementY][randomElementX] == ' ')   {//если встретили символ пробел,
			TileMap[randomElementY][randomElementX] = 's'; //то ставим туда камень.
			//std::cout << "coordinate of Stone X:" << randomElementX << "\n" << "coordinate of Stone Y:" << randomElementY << "\n\n";
			countStone--;
		}
	}
}

