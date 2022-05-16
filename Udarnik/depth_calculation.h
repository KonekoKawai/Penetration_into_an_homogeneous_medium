#pragma once

#include <cmath>

class depth_calculation
{
public:
	depth_calculation();
	depth_calculation(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness);

	double velocity_and_depth(); // ������ ��������� ������� �������� � ������� �������
	double end_depth(); // ������ �������� ������� 
	void reset_udar(); // ��������� ������ ��������
	void set_values(double  mass ,  double  start_velocity ,  double  alpha_rad ,  double  density ,  double  tangent ,  double  dynamic_hardness); // ��������� ���� ��������
	void set_current_velocity_in_pixel(double current_velocity);  // ��������� ������� �������� � ��������
	void set_current_depth_y(double current_depth_y);  // ��������� ������� �������
	double get_current_velocity_in_pixel();  // ������ ������� �������� � ��������
	double get_current_depth_y();  // ������ ������� �������
	double get_current_alpha_rad(); // �������� ������� ���� ������������
	double get_start_velocity(); // �������� ��������� ��������
	double get_current_velocity(); // �������� ������� ��������
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

	int PIKSEL_IN_ON_M_INFO_L; // ��������������� ���� �� L
	int PIKSEL_IN_ON_M_INFO_V; // ��������������� ���� �� V
};