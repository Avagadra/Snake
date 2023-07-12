
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include < tchar.h >
#include <algorithm>

using namespace std;
int MapW, MapH;//высота и ширина карты
int score = 0;//переменная количества очков


char Map[100][100] = {//задана изначальная карта и первое яблоко
"########################################################",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                  O                                   #",
"#                                                      #",
"#                                                      #",
"#                                        X             #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#         $                                            #",
"#                                         @            #",
"#                                                      #",
"#                                                      #",
"########################################################" };

void drowScore(int score)//рисует количество очков
{
	cout << "\n#############" << endl;
	cout << "#Score:" << score;
	cout << "\n#############" << endl;
	cout << "------LEGEND-------" << endl;
	cout << "# - Game Over" << endl;
	cout << "@ +10 score, +1 long, +@ +$ +X" << endl;
	cout << "$ +50 score, +5 long, +@ +$ +X" << endl;
	cout << "O -100 score, delete all apl, +G" << endl;
	cout << "G - 10 score, -5 long" << endl;
	cout << "X - Game Over" << endl;
	cout << "\n-------------------\n" << endl;
}


struct snakeBlock //заданы переменные координат змейки
{
	int x, y;
};

void gotoxy(int x, int y) //задает местоположение курсора
{
	COORD coord = { x,y }; //Структура COORD определяет координаты символьной клетки в консоли
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // задает местоположение курсора
}

void StartGame()//прорисовка заставки
{

	bool exit = false;
	while (exit == false)
	{
		system("cls");

		cout << "########################################################" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#        zzzzzz   zz     z      zz      z   z zzzzzz   #" << endl;
		cout << "#       z         z z    z     z  z     z  z  z        #" << endl;
		cout << "#       zz        z  z   z    z    z    z z   z        #" << endl;
		cout << "#         zz      z   z  z   zzzzzzzz   zz    zzzzz    #" << endl;
		cout << "#           zz    z    z z  z        z  z z   z        #" << endl;
		cout << "#     zzzzz       z    zzz z          z z  z  zzzzzz   #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                         ________                     #" << endl;
		cout << "#         _____          / ______ \\                    #" << endl;
		cout << "#    \\   / o   \\____    / /      \\ \\        /          #" << endl;
		cout << "#     ---| o    ___ \\__/ /        \\ \\_____/ /          #" << endl;
		cout << "#    /   \\_____/   \\____/          \\_______/           #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "########################################################" << endl;

		Sleep(500);
		system("cls");

		cout << "########################################################" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#        zzzzzz   zz     z      zz      z   z zzzzzz   #" << endl;
		cout << "#       z         z z    z     z  z     z  z  z        #" << endl;
		cout << "#       zz        z  z   z    z    z    z z   z        #" << endl;
		cout << "#         zz      z   z  z   zzzzzzzz   zz    zzzzz    #" << endl;
		cout << "#           zz    z    z z  z        z  z z   z        #" << endl;
		cout << "#     zzzzz       z    zzz z          z z  z  zzzzzz   #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#         _____     _____           ______             #" << endl;
		cout << "#    \\   / o   \\___/ ___ \\         / ____ \\            #" << endl;
		cout << "#     ---| o    ____/   \\ \\       / /    \\ \\           #" << endl;
		cout << "#    /   \\_____/         \\ \\_____/ /      \\ \\          #" << endl;
		cout << "#                         \\_______/        \\_\\/        #" << endl;
		cout << "#                                                      #" << endl;
		cout << "#                                                      #" << endl;
		cout << "########################################################" << endl;

		Sleep(500);
		if (GetKeyState(VK_RETURN))
		{
			exit = true;
		}
	}

}


enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


void drawMap(vector <snakeBlock>snake)//прорисовка карты с векторной змейкой построчно
{

	MapH = 0;//высота карты на начало цикла 0 
	system("cls");
	for (int i = 0; Map[i][0]; i++) // рисует карту с добавлением на нее змейки
	{
		MapW = 0;//ширина карты на начало цикла 0
		for (int j = 0; Map[i][j]; j++)//перезавписываем символы карты
		{
			MapW++;
			if (Map[i][j] != ' ')//если символ карты не пробел перемещение курсора
			{
				gotoxy(j, i);
				cout << Map[i][j];
			}
		}
		MapH++;
	}
	drowScore(score);//рисует количество очков
	for (int i = 0; i < snake.size(); i++)
	{
		gotoxy(snake[i].x, snake[i].y);
		cout << char(219);
	}

}

bool checkLose(int x, int y, vector <snakeBlock>& snake) //логический модуль. определяет что делать на данном шаге
														//пока фолс игра выполняется
{
	if (Map[y][x] == '#') //столкновение со стенкой - игра окончена
		return true;
	if (snake.size() > 3) // если размер змеи больше 3
	{
		for (int i = 3; i < snake.size(); i++)
			if (snake[i].x == x && snake[i].y == y) // если змея касается саму себя - игра окончена
				return true;
	}


	if (Map[y][x] == '@') // если берется яблоко змея растет и игра продолжается
	{
		Map[y][x] = ' '; //убирает яблоко с предыдущего места
		score = score + 10;
		snakeBlock newSnake;
		newSnake.x = snake[snake.size() - 1].x;
		newSnake.y = snake[snake.size() - 1].y;
		snake.push_back(newSnake); //добавление элемента в конец вектора//увеличиваем размер змейки
		int rx, ry;//рандомно выбирается место происовки нового яблока
		do {
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = '@';
		do {
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = '$';
		do {
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = 'X';
		drawMap(snake); // рисует карту заного для следующего шага
	}

	if (Map[y][x] == '$') // если берется яблоко змея сильно растет и игра продолжается
	{
		Map[y][x] = ' '; //убирает яблоко с предыдущего места
		score = score + 50;
		snakeBlock newSnake;
		newSnake.x = snake[snake.size() - 1].x;
		newSnake.y = snake[snake.size() - 1].y;
		for (int i = 0; i < 4; i++)//увеличиваем размер змейки на 5
		{
			snake.push_back(newSnake);
		}
		int rx, ry;
		do { //рандомно выбирается место происовки нового яблока
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = '$';
		do {
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = '@';
		do {
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = 'X';
		drawMap(snake); // рисует карту заного для следующего шага
	}

	if (Map[y][x] == 'O') // отнимет 100 очков но в обмен удаляет все яблоки с карты и рандомит по 1 каждого вида на карте
	{
		for (int i = 0; Map[i][0]; i++) // удаляем с карты все
		{

			for (int j = 0; Map[i][j]; j++)
			{

				if (Map[i][j] != ' ' && Map[i][j] != '#')
				{
					Map[i][j] = ' ';
				}
			}

		}
		score = score - 100;//удаляем очки
		snakeBlock newSnake;
		newSnake.x = snake[snake.size() - 1].x;
		newSnake.y = snake[snake.size() - 1].y;

		int rx, ry;
		do { //рандомно выбирается место происовки нового яблока
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = '$';
		do {
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = '@';
		do {
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = 'X';
		do {
			rx = rand() % MapW;
			ry = rand() % MapH;
		} while (checkLose(rx, ry, snake));
		Map[ry][rx] = 'O';
		if (snake.size() > 5) //если змейка размером больше 5 то рандомим яблоко для уменьшения размера
		{
			do {
				rx = rand() % MapW;
				ry = rand() % MapH;
			} while (checkLose(rx, ry, snake));
			Map[ry][rx] = 'G';
		}
		drawMap(snake); // рисует карту заного для следующего шага
	}

	if (Map[y][x] == 'G') //укорачивает змейку
	{
		Map[y][x] = ' '; //убирает с предыдущего места
		score = score - 10;
		snakeBlock newSnake;
		newSnake.x = snake[snake.size() - 1].x;
		newSnake.y = snake[snake.size() - 1].y;
		for (int i = 0; i < 4; i++)//уменьшаем размер змейки на 5
		{
			snake.pop_back();//убираем элемент в конец вектора
		}

		int rx, ry;//рандомно выбирается место происовки нового яблока
		if (snake.size() > 5) //если змейка размером больше 5 то рандомим яблоко для уменьшения размера
		{
			do {
				rx = rand() % MapW;
				ry = rand() % MapH;
			} while (checkLose(rx, ry, snake));
			Map[ry][rx] = 'G';
		}

		drawMap(snake); // рисует карту заного для следующего шага
	}

	if (Map[y][x] == 'X') // если берется game over
		return true;
	return false;
}

void snakeInit(int x, int y, vector<snakeBlock>& snake) //инициализация змейки
{
	snakeBlock newSnake;
	newSnake.x = x;
	newSnake.y = y;
	snake.push_back(newSnake);
}

bool snakeMove(vector<snakeBlock>& snake, short dire[2])//движение змейки с проверкой логического блока
{
	int oldx, oldy, x, y;
	gotoxy(snake[snake.size() - 1].x, snake[snake.size() - 1].y);
	cout << " ";
	oldx = snake[0].x;
	oldy = snake[0].y;
	snake[0].x += dire[0];
	snake[0].y += dire[1];
	gotoxy(snake[0].x, snake[0].y);
	cout << char(219);
	if (snake.size() > 1)
	{
		for (int i = 1; i < snake.size(); i++)
		{
			x = snake[i].x;
			y = snake[i].y;
			snake[i].x = oldx;
			snake[i].y = oldy;
			oldx = x;
			oldy = y;
		}
	}
	if (checkLose(snake[0].x, snake[0].y, snake)) // если игра проиграна движение окончено
		return true;
	return false;
}

int main()
{
	bool GameIsRunning = true; //игра запущена
	int GameSpeed = 200; //скорость движения змейки
	short dire[2] = { 0,1 };
	vector<snakeBlock> snake;
	snakeInit(1, 1, snake); //инициализация змейки с начальными размерами
	StartGame();
	drawMap(snake); //рисуем карту

	while (GameIsRunning) //пока игра запущена 
	{
		if (GetAsyncKeyState(VK_UP)) //нажата клавиша вверх
		{
			if (dire[1] == 0)
			{
				dire[1] = -1;
				dire[0] = 0;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) //нажата клавиша вниз
		{
			if (dire[1] == 0)
			{
				dire[1] = 1;
				dire[0] = 0;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT)) //нажата клавиша влево
		{
			if (dire[0] == 0)
			{
				dire[1] = 0;
				dire[0] = -1;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT)) //нажата клавиша вправо
		{
			if (dire[0] == 0)
			{
				dire[1] = 0;
				dire[0] = 1;
			}
		}
		if (snakeMove(snake, dire)) // если блок выполнится с тру значит в логическом блоке был результат - игра окончена
		{
			system("cls");
			cout << "########################################################" << endl;
			cout << "#                                                      #" << endl;
			cout << "#           ###      #     #     # ####                #" << endl;
			cout << "#          #        # #    # # # # #                   #" << endl;
			cout << "#          #  ##   #   #   #  #  # ###                 #" << endl;
			cout << "#          #  #   #######  #     # #                   #" << endl;
			cout << "#           ###  #       # #     # ####                #" << endl;
			cout << "#                                                      #" << endl;
			cout << "#       ####   #       #   ######   ######             #" << endl;
			cout << "#      #    #  #       #   #        #     #            #" << endl;
			cout << "#      #    #   #     #    ####     ######             #" << endl;
			cout << "#      #    #    #   #     #        #   #              #" << endl;
			cout << "#      #    #     # #      #        #    #             #" << endl;
			cout << "#       ####       #       ######   #     #            #" << endl;
			cout << "#                                                      #" << endl;
			cout << "#                                                      #" << endl;
			cout << "#         _____                                        #" << endl;
			cout << "#    \\   / X   \\___________________________/           #" << endl;
			cout << "#     ---| X    ___________________________/           #" << endl;
			cout << "#    /   \\_____/                                       #" << endl;
			cout << "#                                                      #" << endl;
			cout << "#                                                      #" << endl;
			cout << "#                                                      #" << endl;
			cout << "########################################################" << endl;
			cout << "                    Score:" << score;
			cout << "" << endl;
			system("pause");
			return 0;
		}
		Sleep(GameSpeed); // задает задержку выполнения программы. в нашем случае скорость змейки
	}
}
