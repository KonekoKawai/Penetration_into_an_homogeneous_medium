#include "depth_calculation.h"


depth_calculation::depth_calculation()
{
	mass = 0; // ����� 
	start_velocity = 0; // ��������� ��������
	current_velocity = 0; // ������� ��������
	alpha_rad = 0; // ���� ����� � �������� 
	density = 0; // ���������
	tangent = 0; // ����������� �������������
	dynamic_hardness = 0;
	current_depth_y = 0;
	finish_depth = 0;
	current_velocity_in_pixel = 0;

}

depth_calculation::depth_calculation(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness)
{
	this->mass = mass;
	this->start_velocity = start_velocity;
	this->alpha_rad = alpha_rad;
	this->density = density;
	this->tangent = tangent;
	this->dynamic_hardness = dynamic_hardness;
	this->current_velocity = 0;
	this->current_depth_y = 0;
	current_velocity_in_pixel = 0;
	this->finish_depth = 0;

}


double depth_calculation::velocity_and_depth() // ������ ��������� ������� �������� � ������� �������
{
	double  A = (2 * dynamic_hardness * tan(alpha_rad) + 2 * tangent) / mass;
	double  B = (2 * pow(sin(alpha_rad) ,  2) * density * tan(alpha_rad)) / mass;
	this->current_velocity = sqrt(-(A / B) + (A / B + pow(start_velocity ,  2)) * exp(-B * pow(current_depth_y ,  2)));
	if ((-(A / B) + (A / B + pow(start_velocity ,  2)) * exp(-B * pow(current_depth_y ,  2))) <= 0.0001)
	{
		this->current_velocity = 0;
		this->current_depth_y = get_end_depth();
	}
	return current_velocity;
}

double depth_calculation::get_end_depth() // ������ �������� ������� ����������
{
	double  A = (2 * dynamic_hardness * tan(alpha_rad) + 2 * tangent) / mass;
	double  B = (2 * pow(sin(alpha_rad) ,  2) * density * tan(alpha_rad)) / mass;
	this->finish_depth = sqrt(1 / B * log(1 + (B * pow(start_velocity ,  2)) / A));
	return finish_depth;
}

void depth_calculation::reset_udar() // ���������� ��� �������� � � ��������� 
{
	this->current_velocity = 0;
	this->current_depth_y = 0;
	this->finish_depth = 0;
}

void depth_calculation::set_values(double mass ,  double start_velocity ,  double alpha_rad ,  double density ,  double tangent ,  double dynamic_hardness) // ������ �� ���� ������
{
	this->mass = mass;
	this->start_velocity = start_velocity;
	this->alpha_rad = alpha_rad;
	this->density = density;
	this->tangent = tangent;
	this->dynamic_hardness = dynamic_hardness;
}

void depth_calculation::set_current_velocity_in_pixel(double current_velocity_in_pixel) /// ���������� ������� �������� � ��������
{
	this->current_velocity_in_pixel = current_velocity_in_pixel;
}

void depth_calculation::set_current_depth_y(double current_depth_y) /// ���������� ������� ������� �������������
{
	this->current_depth_y = current_depth_y;
}

double depth_calculation::get_current_velocity_in_pixel() // �������� ������� �������� � ��������
{
	return current_velocity_in_pixel;
}

double depth_calculation::get_current_velocity() // �������� ������� ��������
{
	return current_velocity;
}


double depth_calculation::get_start_velocity() // �������� ������� ��������
{
	return start_velocity;
}

double depth_calculation::get_current_depth_y() // �������� ������� ������� �������������
{
	return current_depth_y;
}

double depth_calculation::get_current_alpha_rad() // �������� ���� �����
{
	return alpha_rad;
}
