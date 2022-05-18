#include "Header.h"


void init() // Функция инициализация окна 
{
	SDL_Init(SDL_INIT_EVERYTHING); // Инициализация библиотеки SDL Со всеми подсистемами 
	gWindow = SDL_CreateWindow("Wedge penetration v0.3" ,  20 ,  50 ,  SCREEN_WIDTH ,  SCREEN_HEIGHT ,  SDL_WINDOW_SHOWN); // Присвоение окна
	gScreenSurface = SDL_GetWindowSurface(gWindow); // Получаем поверхность нашего окна 
	gRenderer = SDL_CreateRenderer(gWindow ,  -1 ,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Получаем рендер для нашего окна
	SDL_UpdateWindowSurface(gWindow); // Обновляем поверхность окна 
}

void display()
{
	SDL_SetRenderDrawColor(gRenderer ,  255 ,  255 ,  255 ,  0);
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer ,  0 ,  0 ,  0 ,  0);
	SDL_RenderSetViewport(gRenderer ,  NULL);
	SDL_RenderDrawRect(gRenderer ,  &rect_PDSK);
	SDL_RenderDrawRect(gRenderer ,  &rect_info_PDSK);
	SDL_RenderDrawRect(gRenderer ,  &rect_info_Num);
	SDL_RenderPresent(gRenderer);
}

void close() // Функция выхода 
{
	// Освобождение памяти
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gScreenSurface = NULL;
	SDL_Quit();
}

bool enter(depth_calculation *udar) // Функция ввода данных в объект
{
	double mass = -1; // Масса 
	double start_velocity = -1; // Начальная скорость
	double alpha_rad = -1; // Угол альфа в радианах 
	double density = -1; // Плотность
	double tangent = -1; // Касательное сопротивление
	double dynamic_hardness = -1; // Динамическая твердость 
	double h0 = 1; // Высота ударной чатси
	double h1 = 2; // Высота основания 
	static int count = 0; // Номер элемента массива 
	bool flag = true;
	
	system("cls");
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (true)
	{
		printf("Данные для %d клина\n", count + 1);
		cout << "Введите массу клина в кг: ";
		cin >> mass;
		cout << "Введите начальную скорость клина в м/с: ";
		cin >> start_velocity;
		cout << "Введите угол полураствора клина в градусах: ";
		cin >> alpha_rad;
		cout << "Введите плотность преграды в кг/м^2: ";
		cin >> density;
		cout << "Введите касательное сопротивление преграды в H: ";
		cin >> tangent;
		cout << "Введите динамическую твердость преграды в Па: ";
		cin >> dynamic_hardness;

		cout << "Введите h0 в см (высота ударной части): ";
		cin >> h0;

		cout << "Введите h1 в см (высота основания): ";
		cin >> h1;

		if (mass > 0 && start_velocity > 0 && alpha_rad > 0 && alpha_rad < 90 && density > 0 && tangent > 0 && dynamic_hardness > 0 && h0 > 0 && h1 > 0) // Если все значения верно занесены
		{
			alpha_rad = alpha_rad * M_PI / 180;
			break;
		}
		else // Если в буфер попало не нужное нам значение или отрицательное значение
		{
			mass = -1 ,  start_velocity = -1 ,  alpha_rad = -1 ,  density = -1 ,  tangent = -1 ,  dynamic_hardness = -1;
			cin.clear(); // Отчистка 
			cin.ignore(1024 ,  '\n'); // Отчистка потока 
			system("cls");
			cout << "Не правильно введенны значения!" << endl;
		}
	}
	udar[count].set_values(mass ,  start_velocity ,  alpha_rad ,  density ,  tangent ,  dynamic_hardness, h0, h1); // Присвоение полям объекта наших данных
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef Test
	cout << endl << "Продолжить набор значений? Да - Enter ,  Нет - ESC" << endl;
	while (true)
	{
		switch (_getch())
		{
		case 27:
			system("cls");
			flag = false;
			return flag;
		case 13:
			system("cls");
			return flag;
		}
	}
#endif

	count++;
	if (count == udar->get_ARRAY_SIZE()) // Если заполнили весь массив 
	{
		flag = false;
		return flag;
	}
}

int main(int argc ,  char* args[])
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
#ifndef Test
	int ARRAY_SIZE;
	do
	{
		cout << "Введите количество клинов для тестов: ";
		cin >> ARRAY_SIZE;
		cin.clear(); // Отчистка 
		cin.ignore(1024, '\n'); // Отчистка потока 
	} while (ARRAY_SIZE <= 0);

	depth_calculation* udar = new depth_calculation[ARRAY_SIZE]();
	while (enter(udar)); // Заполнение объекта данными 
	system("cls");
#endif // !Test

	

////////////////
#ifdef Test
	depth_calculation udar[ARRAY_SIZE] = { depth_calculation(100 , 3 ,  45 * M_PI / 180 , 180 , 800 , 110, 1, 2),
										depth_calculation(150, 9, 10 * M_PI / 180, 380,400,410,1 ,2 ),
										depth_calculation(300, 4, 15 * M_PI / 180, 880,100,10, 1, 2),
										depth_calculation(200, 7, 65 * M_PI / 180, 70,600,90,1,2) ,
										depth_calculation(600, 2, 35 * M_PI / 180, 380,1100,200,1,2)
   };
#endif

	init();
	display();

	int count = 0; // Значение для экрана по умолчанию / Объект в массиве по умолчанию 

	motion_display motion_udar;
	bool quit = false; // Флаг выхода из графического цикла
	bool motion = false;
	SDL_Event e; // Отработка событий 
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	motion_udar.display_PDSK();
	SDL_RenderSetViewport(gRenderer, &rect_info_PDSK); // Область для отображения Только область ударника и прочее
	motion_udar.display_info_PDSK();
	SDL_RenderSetViewport(gRenderer, &rect_PDSK); // Область для отображения Только область ударника и прочее
	motion_udar.scaling_PDSK(&udar[count]); // Выполняем масштбаирование 
	motion_udar.display_motion_klin(&udar[count]);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	SDL_RenderPresent(gRenderer);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (!quit) // Цикл отображения на экране
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_w:
					motion = true;
					break;
				case SDLK_1: // Предыдущий клин
					count--;
					if (count < 0)
						count = ARRAY_SIZE - 1;

					display(); // Отобразить рамки экранов 
					udar[count].reset_udar(); // Обнулить данные ударника 
					motion_udar.scaling_PDSK(&udar[count]); // Выполняем масштбаирование
					motion_udar.display_PDSK(); // Отобразить PDSK
					SDL_RenderSetViewport(gRenderer, &rect_PDSK); // Переключиться на экран с главной PDSK 
					motion_udar.display_motion_klin(&udar[count]); // ОТобразить начальное положение клина 

					SDL_RenderSetViewport(gRenderer, &rect_info_PDSK); // Область для отображения Только область ударника и прочее
					motion_udar.display_info_PDSK(); // Отобразить ПДСК в окне с информацией	

					SDL_RenderPresent(gRenderer); // Обновить экран
					break;
				case SDLK_2: // Следующий клин 
					count++;
					if (ARRAY_SIZE - count == 0)
						count = 0;

					display(); // Отобразить рамки экранов 
					udar[count].reset_udar(); // Обнулить данные ударника 
					motion_udar.scaling_PDSK(&udar[count]); // Выполняем масштбаирование
					motion_udar.display_PDSK(); // Отобразить PDSK
					SDL_RenderSetViewport(gRenderer, &rect_PDSK); // Переключиться на экран с главной PDSK 
					motion_udar.display_motion_klin(&udar[count]); // ОТобразить начальное положение клина 

					SDL_RenderSetViewport(gRenderer, &rect_info_PDSK); // Область для отображения Только область ударника и прочее
					motion_udar.display_info_PDSK(); // Отобразить ПДСК в окне с информацией

					SDL_RenderPresent(gRenderer); // Обновить экран
					break;
				
				case SDLK_0: // Вернутся к начальному клину 
					count = 0;
					display(); // Отобразить рамки экранов 
					udar[count].reset_udar(); // Обнулить данные ударника
					motion_udar.scaling_PDSK(&udar[count]); // Выполняем масштбаирование
					motion_udar.display_PDSK(); // Отобразить PDSK
					SDL_RenderSetViewport(gRenderer, &rect_PDSK); // Переключиться на экран с главной PDSK 
					motion_udar.display_motion_klin(&udar[count]); // ОТобразить начальное положение клина 

					SDL_RenderSetViewport(gRenderer, &rect_info_PDSK); // Область для отображения Только область ударника и прочее
					motion_udar.display_info_PDSK(); // Отобразить ПДСК в окне с информацией

					SDL_RenderPresent(gRenderer); // Обновить экран
					break;
				}			
			}
			if (e.type == SDL_QUIT)
				quit = true;
		}

		if (motion == true)
		{
			SDL_SetRenderDrawColor(gRenderer ,  255 ,  255 ,  255 ,  255);
			SDL_RenderClear(gRenderer);
			display();
			SDL_RenderSetViewport(gRenderer, &rect_PDSK); // Область для отображения Только область ударника и прочее
			motion_udar.display_PDSK();
			udar[count].reset_udar();
			
			while (true)
			{			
				udar[count].set_current_depth_y(udar[count].get_current_depth_y() + udar[count].get_current_velocity_in_pixel());
				udar[count].set_current_velocity_in_pixel(udar[count].velocity_and_depth() / motion_udar.get_PIKSEL_IN_ON_M_MOTION());

				if (udar[count].get_current_velocity_in_pixel() == 0)
				{
					motion = false;
					SDL_RenderSetViewport(gRenderer, &rect_PDSK); // Область для отображения 
					motion_udar.display_motion_klin(&udar[count]);
					cout << endl << "Конечная глубина проникания ударника: " << udar[count].get_end_depth() << "м" << endl;
					break;
				}
				
				SDL_RenderSetViewport(gRenderer ,  &rect_PDSK); // Область для отображения Только область ударника и прочее
				motion_udar.display_PDSK(); // Отобразить систему координат
				motion_udar.display_motion_klin(&udar[count]); // Отобразить движение клина	


				SDL_RenderSetViewport(gRenderer, &rect_info_PDSK); // Область для отображения Только область ударника и прочее
				motion_udar.display_info_PDSK();
				motion_udar.display_info_PSDK_V_and_L(&udar[count]);

				SDL_RenderPresent(gRenderer);
			}

		}

		
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	close();

	SDL_Delay(63);
	return 0;
}

