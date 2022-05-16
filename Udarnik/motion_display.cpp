#include "motion_display.h"

motion_display::motion_display()
{
	start_x = SCREEN_WIDTH_MOTION/2;
	start_y = SCREEN_HEIGHT_MOTION/4;
	current_x = start_x;
	current_y = start_y;
	current_point = { current_x - THICKHNESS_PIKSEL / 2  , current_y - THICKHNESS_PIKSEL / 2 ,  THICKHNESS_PIKSEL ,  THICKHNESS_PIKSEL };
	end_point = { current_x - THICKHNESS_PIKSEL / 2  , current_y - THICKHNESS_PIKSEL / 2 ,  THICKHNESS_PIKSEL ,  THICKHNESS_PIKSEL };

	PIKSEL_IN_ON_M_MOTION = 100;
	PIKSEL_IN_ON_M_INFO_L = 100;
	PIKSEL_IN_ON_M_INFO_V = 100;
}

motion_display::~motion_display()
{
	
}

void motion_display::display_PDSK() // Отображение ПДСК на главном экране
{

	SDL_SetRenderDrawColor(gRenderer ,  0 ,  0 ,  128 ,  0);
	SDL_RenderDrawLine(gRenderer ,  SCREEN_WIDTH_MOTION/2 ,  0 ,  SCREEN_WIDTH_MOTION / 2 ,  SCREEN_HEIGHT); // Ось Y
	SDL_RenderDrawLine(gRenderer ,  0 ,  SCREEN_HEIGHT / 4 ,  SCREEN_WIDTH_MOTION ,  SCREEN_HEIGHT / 4); // Ось X
	int count = 0;
	for (int i = SCREEN_WIDTH_MOTION/2; i < SCREEN_WIDTH_MOTION; i += PIKSEL_IN_ON_M_MOTION/4) // Черточки по линии X -> PIKSEL_IN_ON_M_MOTION/4 т.к Делим на 4 один метр
	{
	
		if(count % 4 == 0) // Каждые 0.25 Ставим большой прочерк
		SDL_RenderDrawLine(gRenderer ,  i ,  (SCREEN_HEIGHT / 4) + (SCREEN_HEIGHT_MOTION / 50) ,  i ,  (SCREEN_HEIGHT / 4) - (SCREEN_HEIGHT_MOTION / 50)); // Каждый метр
		count++;
		SDL_RenderDrawLine(gRenderer ,  i ,  (SCREEN_HEIGHT / 4) + (SCREEN_HEIGHT_MOTION / 100) ,  i ,  (SCREEN_HEIGHT / 4) - (SCREEN_HEIGHT_MOTION / 100)); // Каждые 0.25
	}
	
	count = 0;
	for (int i = SCREEN_WIDTH_MOTION/2; i > 0; i -= PIKSEL_IN_ON_M_MOTION / 4) // Черточки по линии X <-
	{
		if (count % 4 == 0) // Каждые 0.25 Ставим большой прочерк
		SDL_RenderDrawLine(gRenderer ,  i ,  (SCREEN_HEIGHT / 4) + (SCREEN_HEIGHT_MOTION / 50) ,  i ,  (SCREEN_HEIGHT / 4) - (SCREEN_HEIGHT_MOTION / 50)); // Каждый метр 
		count++;
		SDL_RenderDrawLine(gRenderer ,  i  ,  (SCREEN_HEIGHT / 4) + (SCREEN_HEIGHT_MOTION / 100) ,  i  ,  (SCREEN_HEIGHT / 4) - (SCREEN_HEIGHT_MOTION / 100)); // Каждые 0.25

	}
	//////////////// Y
	count = 0;
	for (int i = SCREEN_HEIGHT_MOTION/4; i > 0; i -= PIKSEL_IN_ON_M_MOTION / 4) // Черточки по линии Y вверх
	{
		if (count % 4 == 0) // Каждые 0.25 Ставим большой прочерк
		SDL_RenderDrawLine(gRenderer ,  (SCREEN_WIDTH_MOTION / 2) + (SCREEN_WIDTH_MOTION / 50) ,  i ,  (SCREEN_WIDTH_MOTION / 2) - (SCREEN_WIDTH_MOTION / 50) ,  i);
		count++;
		SDL_RenderDrawLine(gRenderer ,  (SCREEN_WIDTH_MOTION / 2) + (SCREEN_WIDTH_MOTION / 100) ,  i ,  (SCREEN_WIDTH_MOTION / 2) - (SCREEN_WIDTH_MOTION / 100) ,  i);
	}
	count = 0;
	for (int i = SCREEN_HEIGHT_MOTION / 4; i < SCREEN_HEIGHT_MOTION* PIKSEL_IN_ON_M_MOTION/50; i += PIKSEL_IN_ON_M_MOTION / 4) // Черточки по линии Y вниз
	{
		if (count % 4 == 0) // Каждые 0.25 Ставим большой прочерк
		SDL_RenderDrawLine(gRenderer ,  (SCREEN_WIDTH_MOTION / 2) + (SCREEN_WIDTH_MOTION / 50) ,  i ,  (SCREEN_WIDTH_MOTION / 2) - (SCREEN_WIDTH_MOTION / 50) ,  i);
		count++;
		SDL_RenderDrawLine(gRenderer ,  (SCREEN_WIDTH_MOTION / 2) + (SCREEN_WIDTH_MOTION / 100) ,  i ,  (SCREEN_WIDTH_MOTION / 2) - (SCREEN_WIDTH_MOTION / 100) ,  i);
	}
	
}

void motion_display::display_motion_klin(depth_calculation* udar) // Метод для отображения движения клина
{
	// Удаляем предыдующие линии 
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); // Образующуие клина для удаления - цвет
	//Удаляем 3 линии Которые рисуем далее // По сути первый вызов ничего не удаляет
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y - 1, (int)(SCREEN_WIDTH_MOTION / 2 + HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y -1 - HEIGHT_UDARNIK); // Правая образующая 
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y, (int)(SCREEN_WIDTH_MOTION / 2 + HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y - HEIGHT_UDARNIK); // Правая образующая 
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y + 1, (int)(SCREEN_WIDTH_MOTION / 2 + HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y + 1 - HEIGHT_UDARNIK); // Правая образующая 

	//Удаляем 3 линии Которые рисуем далее // По сути первый вызов ничего не удаляет
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y -1 , (int)(SCREEN_WIDTH_MOTION / 2 - HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y -1 - HEIGHT_UDARNIK); // Левая образующая 
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y, (int)(SCREEN_WIDTH_MOTION / 2 - HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y - HEIGHT_UDARNIK); // Левая образующая 
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y + 1 , (int)(SCREEN_WIDTH_MOTION / 2 - HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y + 1 - HEIGHT_UDARNIK); // Левая образующая 

	//  КОнечная точка 
	SDL_SetRenderDrawColor(gRenderer ,  0 ,  140 ,  0 ,  0);  // цвет
	end_point = { current_x - THICKHNESS_PIKSEL / 2  , SCREEN_HEIGHT_MOTION / 4 + (int)(udar->get_end_depth() * PIKSEL_IN_ON_M_MOTION) ,  THICKHNESS_PIKSEL ,  THICKHNESS_PIKSEL };// Расположение
	SDL_RenderFillRect(gRenderer ,  &end_point);

	current_y = SCREEN_HEIGHT_MOTION / 4 + (int)(udar->get_current_depth_y() * PIKSEL_IN_ON_M_MOTION);
	SDL_SetRenderDrawColor(gRenderer ,  0 ,  0 ,  0 ,  0); // Образующуие клина - цвет
	// Рисуем 3 линии Чтобы границы были более толстыми 
	SDL_RenderDrawLine(gRenderer ,  SCREEN_WIDTH_MOTION / 2 ,   current_y -1,  (int)(SCREEN_WIDTH_MOTION / 2 + HEIGHT_UDARNIK/tan((M_PI/2)-udar->get_current_alpha_rad())) ,  current_y -1  - HEIGHT_UDARNIK); // Правая образующая 
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y, (int)(SCREEN_WIDTH_MOTION / 2 + HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y - HEIGHT_UDARNIK); // Правая образующая 
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y + 1, (int)(SCREEN_WIDTH_MOTION / 2 + HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y +1 - HEIGHT_UDARNIK); // Правая образующая 

	// Рисуем 3 линии Чтобы границы были более толстыми 
	SDL_RenderDrawLine(gRenderer ,  SCREEN_WIDTH_MOTION / 2 ,   current_y -1 ,  (int)(SCREEN_WIDTH_MOTION / 2 - HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())) ,    current_y -1 - HEIGHT_UDARNIK); // Левая образующая 
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y, (int)(SCREEN_WIDTH_MOTION / 2 - HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y - HEIGHT_UDARNIK); // Левая образующая 
	SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH_MOTION / 2, current_y + 1, (int)(SCREEN_WIDTH_MOTION / 2 - HEIGHT_UDARNIK / tan((M_PI / 2) - udar->get_current_alpha_rad())), current_y + 1- HEIGHT_UDARNIK); // Левая образующая 


	SDL_SetRenderDrawColor(gRenderer ,  0 ,  0 ,  0 ,  0);
	SDL_RenderDrawRect(gRenderer ,  &rect_PDSK); // Подрисовываем таблицу

}


int motion_display::get_current_y()
{
	return current_y;
}

void motion_display::display_info_PDSK() // Отрисовка PDSK на окне с информацией 
{
	SDL_SetRenderDrawColor(gRenderer ,  0 , 0 ,  0 ,  0);
	SDL_RenderDrawLine(gRenderer, WIDTH_INDENT, HEIGHT_INDENT, WIDTH_INDENT, SCREEN_HEIGHT_INFO / 4 * 3 - HEIGHT_INDENT); // Ось Y
	SDL_RenderDrawLine(gRenderer, WIDTH_INDENT, SCREEN_HEIGHT_INFO / 4 * 3 - HEIGHT_INDENT, SCREEN_WIDTH_INFO - WIDTH_INDENT, SCREEN_HEIGHT_INFO / 4 * 3 - HEIGHT_INDENT); // Ось X

	/// Отобразим черточки Обозначение расстояния 
	int count = 0;
	for (int i = WIDTH_INDENT; i < SCREEN_WIDTH_INFO - WIDTH_INDENT; i += PIKSEL_IN_ON_M_INFO_L / 4) // Черточки по линии X -> PIKSEL_IN_ON_M_MOTION/4 т.к Делим на 4 один метр
	{

		if (count % 4 == 0) // Каждые 0.25 Ставим большой прочерк
			SDL_RenderDrawLine(gRenderer, i, SCREEN_HEIGHT_INFO / 4 * 3 - HEIGHT_INDENT - HEIGHT_INDENT / 2, i, SCREEN_HEIGHT_INFO / 4 * 3 - HEIGHT_INDENT + HEIGHT_INDENT / 2); // Каждые 0.25
		count++;
		SDL_RenderDrawLine(gRenderer, i, SCREEN_HEIGHT_INFO/4*3 -  HEIGHT_INDENT - HEIGHT_INDENT/4, i, SCREEN_HEIGHT_INFO / 4 * 3 - HEIGHT_INDENT + HEIGHT_INDENT/4); // Каждые 0.25
	}

	count = 0;
	for (int i = SCREEN_HEIGHT_INFO / 4 * 3 - HEIGHT_INDENT ; i > HEIGHT_INDENT; i -= PIKSEL_IN_ON_M_INFO_V / 4) // Черточки по линии Y вверх
	{
		if (count % 4 == 0) // Каждые 0.25 Ставим большой прочерк
			SDL_RenderDrawLine(gRenderer, WIDTH_INDENT + HEIGHT_INDENT / 2, i, WIDTH_INDENT - HEIGHT_INDENT / 2, i);
		count++;
		SDL_RenderDrawLine(gRenderer, WIDTH_INDENT + HEIGHT_INDENT/4, i, WIDTH_INDENT - HEIGHT_INDENT/4, i);
	}

}

void motion_display::display_info_PSDK_V_and_L(depth_calculation* udar) // Отрисовка зависимости в PDSK на окне с информацеий 
{
	SDL_SetRenderDrawColor(gRenderer, 0, 140, 0, 0); // Точка конца пути - цвет
	//  КОнечная точка Расположение
	end_point = { current_x - THICKHNESS_PIKSEL / 2  , SCREEN_HEIGHT_MOTION / 4 + (int)(udar->get_end_depth() * PIKSEL_IN_ON_M_MOTION) ,  THICKHNESS_PIKSEL ,  THICKHNESS_PIKSEL };
	SDL_RenderFillRect(gRenderer, &end_point);


	// Начальная точка расположение
	current_point = { WIDTH_INDENT+(int)(udar->get_current_depth_y() * PIKSEL_IN_ON_M_INFO_L)  ,SCREEN_HEIGHT_INFO/4*3 - HEIGHT_INDENT - (int)(udar->get_current_velocity() * PIKSEL_IN_ON_M_INFO_V) ,  4 ,  4};
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0); // Точка начала - цвет
	SDL_RenderFillRect(gRenderer, &current_point);
}



void motion_display::display_motion_point(depth_calculation* udar) // Метод для отображения движения точки
{
	SDL_SetRenderDrawColor(gRenderer ,  0 ,  140 ,  0 ,  0); // Точка конца пути - цвет
	//  КОнечная точка Расположение
	end_point = { current_x - THICKHNESS_PIKSEL / 2  , SCREEN_HEIGHT_MOTION / 4 + (int)(udar->get_end_depth() * PIKSEL_IN_ON_M_MOTION) ,  THICKHNESS_PIKSEL ,  THICKHNESS_PIKSEL };
	SDL_RenderFillRect(gRenderer ,  &end_point);


	// Измненеие текущего Y 
	current_y = SCREEN_HEIGHT_MOTION / 4 + (int)(udar->get_current_depth_y() * PIKSEL_IN_ON_M_MOTION);
	// Измнение точки 
	current_point = { current_x - THICKHNESS_PIKSEL / 2  , current_y - THICKHNESS_PIKSEL / 2 ,  THICKHNESS_PIKSEL ,  THICKHNESS_PIKSEL };
	SDL_SetRenderDrawColor(gRenderer ,  255 ,  0 ,  0 ,  0); // Точка начала - цвет
	SDL_RenderFillRect(gRenderer ,  &current_point);

	SDL_RenderPresent(gRenderer);

	// Появление за точкой Полосы  
	SDL_SetRenderDrawColor(gRenderer ,  0 ,  0 ,  0 ,  0);
	//current_point = { current_x - THICKHNESS_PIKSEL / 2  , current_y - THICKHNESS_PIKSEL / 2 ,  THICKHNESS_PIKSEL ,  THICKHNESS_PIKSEL };
	SDL_RenderFillRect(gRenderer ,  &current_point);
}

int motion_display::get_PIKSEL_IN_ON_M_MOTION()
{
	return PIKSEL_IN_ON_M_MOTION;
}

void motion_display::scaling_PDSK(depth_calculation* udar) // Масштабирует для указанных данных клина
{
	PIKSEL_IN_ON_M_INFO_V = (SCREEN_HEIGHT_INFO/4*3-2*HEIGHT_INDENT) / (int)udar->get_start_velocity() - HEIGHT_INDENT/2;
	PIKSEL_IN_ON_M_INFO_L = (SCREEN_WIDTH_INFO - 3*WIDTH_INDENT) / int(ceil( udar->get_end_depth()));
	PIKSEL_IN_ON_M_MOTION = (SCREEN_HEIGHT / 4 * 3) / int(ceil(udar->get_end_depth()));
}
