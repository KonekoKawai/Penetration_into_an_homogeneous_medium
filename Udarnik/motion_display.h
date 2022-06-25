#pragma once

#include <iostream>
#include <SDL.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <mutex>

#include "depth_calculation.h"
#include "Texture.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int SCREEN_WIDTH_MOTION; // ������ ������ ��� ����������� ��������
extern const int SCREEN_HEIGHT_MOTION; // ������ ������ ��� ����������� ��������

extern const int SCREEN_WIDTH_INFO;
extern const int SCREEN_HEIGHT_INFO;

// ������� ��� ������ � ����������� � ������� � ��� 
const int WIDTH_INDENT = SCREEN_WIDTH / 50;
const int HEIGHT_INDENT = SCREEN_HEIGHT / 30;

extern const int THICKHNESS_PIKSEL; // ������� ����� � ������� �� ������

extern SDL_Renderer* gRenderer; // ���������� ��������� ���������� �������� ��������� �������� �� �����

extern SDL_Rect rect_PDSK; // ������� ��� ����������� ������� ���������
extern SDL_Rect rect_info_PDSK; // ������� ��� ����������� ����������
extern SDL_Rect rect_info_Num; // ������� ��� ����������� ����������


class motion_display
{
public:
	motion_display();
	~motion_display();

	void display_PDSK(Work_With_Texture* numbers); // ���������� ������� ��������� �� 3/4 ������ �����

	void display_info_PDSK(Work_With_Texture* numbers); // ���������� � ���� ���������� PDSK 
	void display_info_PSDK_V_and_L(depth_calculation* udar); // ���������� � ���� ���������� ��������� 

	int get_current_y();
	void display_motion_point(depth_calculation* udar); // ���������� �������� �����
	void display_motion_klin(depth_calculation* udar); // ���������� �������� �����
	
	int get_PIKSEL_IN_ON_M_MOTION();
	void scaling_PDSK(depth_calculation *udar); // �������� ������� PDSK 
private:
	int right_h0_intersection_h1;
	int left_h0_intersection_h1;

	int current_x;
	int current_y;
	int start_x;
	int start_y;
	SDL_Rect current_point;
	SDL_Rect end_point;

	int h0_in_pixel;
	int h1_in_pixel;

    int PIKSEL_IN_ON_M_MOTION; // �������� � ����� ����� ��� ������ � ��������� ��������
	int PIKSEL_IN_ON_M_INFO_L; // �������� � ����� �����  ��� ������ � ���������� � �������� ��������
	int PIKSEL_IN_ON_M_INFO_V; // �������� � ����� �����  ��� ������ � ���������� � �������� ��������

};


