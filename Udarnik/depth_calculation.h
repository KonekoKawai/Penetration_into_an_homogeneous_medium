#pragma once

#include <cmath>


class depth_calculation
{
public:
	depth_calculation();
	depth_calculation(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness, double h0, double h1);

	double velocity_and_depth(); // ������ ��������� ������� �������� � ������� �������
	double velocity_and_depth(double current_depth_y); // ��� �������� 

	double get_end_depth(); // ������ �������� ������� 
	unsigned int get_ARRAY_SIZE();
	void reset_udar(); // ��������� ������ ��������
	void set_values(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness, double h0, double h1); // ��������� ���� ��������
	void set_current_velocity_in_pixel(double current_velocity);  // ��������� ������� �������� � ��������
	void set_current_depth_y(double current_depth_y);  // ��������� ������� �������
	double get_current_velocity_in_pixel();  // ������ ������� �������� � ��������
	double get_current_depth_y();  // ������ ������� �������
	double get_current_alpha_rad(); // �������� ������� ���� ������������
	double get_start_velocity(); // �������� ��������� ��������
	double get_current_velocity(); // �������� ������� ��������
	double get_h0(); // ������� h0
	double get_h1(); // ������� h1
	
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

	double h0; // ������ ������� �����
	double h1; // ������ �������� ����� 
	double h; // ����� ������ ��������
};