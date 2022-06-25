#include "depth_calculation.h"

int depth_calculation::ARRAY_SIZE = 0;

depth_calculation::depth_calculation()
{
	mass = 0; // ����� 
	start_velocity = 0; // ��������� ��������
	current_velocity = 0; // ������� ��������
	
	density = 0; // ���������
	tangent = 0; // ����������� �������������
	dynamic_hardness = 0;
	current_depth_y = 0;
	finish_depth = 0;
	current_velocity_in_pixel = 0;
	current_velocity_g = 0;

	d = 1;
	h0 = 1;
	h1 = 2;
	alpha_rad = atan(d/(h0*2)); // ���� ����� � �������� 
	h = h0 + h1;
	ARRAY_SIZE++;
	
}

depth_calculation::depth_calculation(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness, double h0, double h1, double d)
{
	this->mass = mass;
	this->start_velocity = start_velocity;
	this->d = d;
	this->alpha_rad = atan(d / (h0 * 2)); // ���� ����� � �������� 
	this->density = density;
	this->tangent = tangent;
	this->dynamic_hardness = dynamic_hardness;
	this->h1 = h1;
	this->h0 = h0;
	h = h1 + h0;
	this->current_velocity = 0;
	this->current_depth_y = 0;
	current_velocity_in_pixel = 0;
	this->finish_depth = 0;
	current_velocity_g = 0;

	ARRAY_SIZE++;
}


double depth_calculation::velocity_and_depth() // ������ ��������� ������� �������� � ������� �������
{
	if (current_depth_y < h0)
	{
		double  A = (2 * dynamic_hardness * tan(alpha_rad) + 2 * tangent) / mass;
		double  B = (2 * pow(sin(alpha_rad), 2) * density * tan(alpha_rad)) / mass;
		this->current_velocity = sqrt(-(A / B) + (A / B + pow(start_velocity, 2)) * exp(-B * pow(current_depth_y, 2)));
		if ((-(A / B) + (A / B + pow(start_velocity, 2)) * exp(-B * pow(current_depth_y, 2))) <= 0.0001)
		{
			this->current_velocity = 0;
			this->current_depth_y = get_end_depth();
		}
	}
	else if (current_depth_y >= h0)
	{
		static double current_velocity_h0 = current_velocity;
		double  A = (2 * dynamic_hardness * tan(alpha_rad) * h0 + 2 * tangent * h0) / mass;
		double  B = (2 * pow(sin(alpha_rad), 2) * density * tan(alpha_rad) * h0) / mass;
		this->current_velocity = sqrt(-(A / B) + (A / B + pow(current_velocity_h0, 2)) * exp(2*B*(h0 - current_depth_y)));
		if (( - (A / B) + (A / B + pow(current_velocity_h0, 2)) * exp(2 * B * (h0 - current_depth_y))) <= 0.0001)
		{
			this->current_velocity = 0;
			this->current_depth_y = get_end_depth();
		}
	}
	return current_velocity;
}

double depth_calculation::velocity_and_depth(double current_depth_y) // ��� ��������!!! ������ ��������� ������� �������� � ������� ������� 
{
	
	if (current_depth_y < h0)
	{
		double  A = (2 * dynamic_hardness * tan(alpha_rad) + 2 * tangent) / mass;
		double  B = (2 * pow(sin(alpha_rad), 2) * density * tan(alpha_rad)) / mass;
		current_velocity_g = sqrt(-(A / B) + (A / B + pow(start_velocity, 2)) * exp(-B * pow(current_depth_y, 2)));
		if ((-(A / B) + (A / B + pow(start_velocity, 2)) * exp(-B * pow(current_depth_y, 2))) <= 0.0001)
		{
			this->current_velocity = 0;
			this->current_velocity_g  = get_end_depth();
		}	
	}
	else if (current_depth_y >= h0)
	{
		static double current_velocity_h0 = current_velocity_g;
		double  A = (2 * dynamic_hardness * tan(alpha_rad) * h0 + 2 * tangent * h0) / mass;
		double  B = (2 * pow(sin(alpha_rad), 2) * density * tan(alpha_rad) * h0) / mass;
		current_velocity_g = sqrt(-(A / B) + (A / B + pow(current_velocity_h0, 2)) * exp(2 * B * (h0 - current_depth_y)));
		if ((-(A / B) + (A / B + pow(current_velocity_h0, 2)) * exp(2 * B * (h0 - current_depth_y))) <= 0.0001)
		{
			this->current_velocity = 0;
			this->current_velocity_g = get_end_depth();
		}
	}
	return current_velocity_g;
}

double depth_calculation::get_end_depth() // ������ �������� ������� ����������
{
	double  A = (2 * dynamic_hardness * tan(alpha_rad) + 2 * tangent) / mass;
	double  B = (2 * pow(sin(alpha_rad) ,  2) * density * tan(alpha_rad)) / mass;
	if(sqrt(1 / B * log(1 + (B * pow(start_velocity, 2)) / A)) <= h0)
		this->finish_depth = sqrt(1 / B * log(1 + (B * pow(start_velocity ,  2)) / A));
	else
	{
		static double start_velocity_h0 = sqrt(-(A / B) + (A / B + pow(start_velocity, 2)) * exp(-B * pow(h0, 2)));
		double  A = (2 * dynamic_hardness * tan(alpha_rad) * h0 + 2 * tangent * h0) / mass;
		double  B = (2 * pow(sin(alpha_rad), 2) * density * tan(alpha_rad) * h0) / mass;
		this->finish_depth = 1 / (2 * B) * log((1 + (B * pow(start_velocity_h0, 2)) / A)) + h0;
	}
	return finish_depth;
}

unsigned int depth_calculation::get_ARRAY_SIZE()
{
	return ARRAY_SIZE;
}

double depth_calculation::get_h0() // ������� ����� 
{
	return h0;
}

double depth_calculation::get_h1() // �������� �����
{
	return h1;
}

double depth_calculation::get_diametr() //������� ��������
{
	return d;
}


void depth_calculation::reset_udar() // ���������� ��� �������� � � ��������� 
{
	this->current_velocity = 0;
	this->current_depth_y = 0;
	this->finish_depth = 0;
}

void depth_calculation::set_values(double mass ,  double start_velocity ,  double alpha_rad ,  double density ,  double tangent ,  double dynamic_hardness, double h0, double h1, double d) // ������ �� ���� ������
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

double depth_calculation::get_current_density() // �������� ���������
{
	return density;
}

double depth_calculation::get_current_mass() // �������� �����
{
	return mass;
}
 
double depth_calculation::get_current_dynamic_hardness() // �������� ������������ ���������
{
	return dynamic_hardness;
}
