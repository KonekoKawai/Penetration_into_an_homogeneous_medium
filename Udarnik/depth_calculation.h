#pragma once

#include <cmath>
#include <SDL.h>

class depth_calculation
{
public:
	depth_calculation();
	depth_calculation(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness, double h0, double h1, double d);

	double velocity_and_depth(); // Расчет отношения текущей скорости к текущей глубине
	double velocity_and_depth(double current_depth_y); // Для графиков 

	double get_end_depth(); // Расчет конечной глубины 
	unsigned int get_ARRAY_SIZE();
	void reset_udar(); // Обнуление данных ударника
	void set_values(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness, double h0, double h1, double d); // Установка всех значений
	void set_current_velocity_in_pixel(double current_velocity);  // Установка текущей скорости в пикселях
	void set_current_depth_y(double current_depth_y);  // Установка текущей глубины
	double get_current_velocity_in_pixel();  // Запрос текущей скорости в ПИКСЕЛЯХ
	double get_current_depth_y();  // Запрос текущей глубины


	double get_start_velocity(); // Получить стартовую скорость
	double get_current_velocity(); // Получить текущую скорость
	
	double get_h0(); // Вывести h0
	double get_h1(); // Вывести h1
	double get_diametr(); //диаметр ударника

	double get_current_alpha_rad(); // Получить текущий угол полураствора
	double get_current_density(); // Получить плотность
	double get_current_mass(); // Получить массу
	double get_current_dynamic_hardness();  // Получить динамическую твердость

	
	static int ARRAY_SIZE;
private:
	double mass; // Масса 
	double start_velocity; // Начальная скорость
	double current_velocity; // текущая скорость
	double current_velocity_in_pixel; // Текущая скорость в пикселях
	double alpha_rad; // Угол альфа в радианах 
	double density; // Плотность
	double tangent; // Касательное сопротивление
	double dynamic_hardness; // Динамическая твердость 
	double current_depth_y; // Текущая глубина
	double finish_depth; // Конечная глубина проникновения

	double current_velocity_g;
	double d; // Диаметр ударника
	double h0; // высота ударной части
	double h1; // Высота основной части 
	double h; // Общая высота ударника
};