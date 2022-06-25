#pragma once

#include <cmath>
#include <SDL.h>

class depth_calculation
{
public:
	depth_calculation();
	depth_calculation(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness, double h0, double h1, double d);

	double velocity_and_depth(); // ������ ��������� ������� �������� � ������� �������
	double velocity_and_depth(double current_depth_y); // ��� �������� 

	double get_end_depth(); // ������ �������� ������� 
	unsigned int get_ARRAY_SIZE();
	void reset_udar(); // ��������� ������ ��������
	void set_values(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness, double h0, double h1, double d); // ��������� ���� ��������
	void set_current_velocity_in_pixel(double current_velocity);  // ��������� ������� �������� � ��������
	void set_current_depth_y(double current_depth_y);  // ��������� ������� �������
	double get_current_velocity_in_pixel();  // ������ ������� �������� � ��������
	double get_current_depth_y();  // ������ ������� �������


	double get_start_velocity(); // �������� ��������� ��������
	double get_current_velocity(); // �������� ������� ��������
	
	double get_h0(); // ������� h0
	double get_h1(); // ������� h1
	double get_diametr(); //������� ��������

	double get_current_alpha_rad(); // �������� ������� ���� ������������
	double get_current_density(); // �������� ���������
	double get_current_mass(); // �������� �����
	double get_current_dynamic_hardness();  // �������� ������������ ���������

	
	static int ARRAY_SIZE;
private:
	double mass; // ����� 
	double start_velocity; // ��������� ��������
	double current_velocity; // ������� ��������
	double current_velocity_in_pixel; // ������� �������� � ��������
	double alpha_rad; // ���� ����� � �������� 
	double density; // ���������
	double tangent; // ����������� �������������
	double dynamic_hardness; // ������������ ��������� 
	double current_depth_y; // ������� �������
	double finish_depth; // �������� ������� �������������

	double current_velocity_g;
	double d; // ������� ��������
	double h0; // ������ ������� �����
	double h1; // ������ �������� ����� 
	double h; // ����� ������ ��������
};