#pragma once

#include <cmath>


class depth_calculation
{
public:
	depth_calculation();
	depth_calculation(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness);

	double velocity_and_depth(); // Расчет отношения текущей скорости к текущей глубине
	double get_end_depth(); // Расчет конечной глубины 
	unsigned int get_ARRAY_SIZE();
	void reset_udar(); // Обнуление данных ударника
	void set_values(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness); // Установка всех значений
	void set_current_velocity_in_pixel(double current_velocity);  // Установка текущей скорости в пикселях
	void set_current_depth_y(double current_depth_y);  // Установка текущей глубины
	double get_current_velocity_in_pixel();  // Запрос текущей скорости в ПИКСЕЛЯХ
	double get_current_depth_y();  // Запрос текущей глубины
	double get_current_alpha_rad(); // Получить текущий угол полураствора
	double get_start_velocity(); // Получить стартовую скорость
	double get_current_velocity(); // Получить текущую скорость
	
	
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

	
};