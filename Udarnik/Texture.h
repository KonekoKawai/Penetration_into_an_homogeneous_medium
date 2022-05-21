#pragma once
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
#include <vector>

using std::string;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int FONT_SIZE;

extern SDL_Window* gWindow; // ���������� ���� ��� �����
extern SDL_Surface* gScreenSurface; // ���������� ����������� ��� ����������� ���� 
extern SDL_Renderer* gRenderer; // ���������� ��������� ���������� �������� ��������� �������� �� �����


extern SDL_Rect rect_info_Num;

enum Sprite_Frame_Enum
{
    SPRITE_FRAME_ALL = 6 , 
    SPRITE_FRAME_14 = 14 , 
};

class Work_With_Texture
{
public:
    Work_With_Texture();
    ~Work_With_Texture();

    void loadTexture(string path);
    void loadTexture(string path ,  int R ,  int G ,  int B);

    void setFontOnSurface(string str); // �������� ������ ����� ������� ����
    void setFontOnSurfaceUNICODE(const Uint16* str); // �������� ������ ���� ���� ������ UNICODE
    void setTexture(string path); // �������� ����� �������� ��� ������������ ������ ����� ��������
    void setTexture(string path ,  int R ,  int G ,  int B); // �������� ����� �������� � ���������� ������������ ������ ����� ��������
    void setTexture(string path ,  int width_Smash ,  int height_Smash); // �������� ���������� ������� �� ����� / ��������� ����������� �� ������� ��� ������������ ������ ����� ��������
    void setTexture(string path ,  int width_Smash ,  int height_Smash ,  int R ,  int G ,  int B); // �������� ���������� ������� �� ����� / ��������� ����������� �� ������� ������������ ������ ����� ��������

    void TransferToRenderFont(int x, int y);
    void TransferToRender(int x ,  int y); // ����������� ����� �������� �� ������ 
    void TransferArrayToRender(int x ,  int y ,  int frame); // ����������� �� ���������� ������� ������������� ������ �� ������ 
    
    void SetAlphaTransparency(int alphaTransparency); // ��������� ������������
    void SetAngelFlip_Center(int angel_Flip ,  int x ,  int y);

    void free(); // ������������ ������ ��� ����������� �������

private:
    int steps_Width;
    int steps_Height; 

    int alphaTransparency;
    
    int angel_Flip;
    int center_flip_x ,  center_flip_y;
    
    SDL_Texture* array_Smash_Texture[SPRITE_FRAME_ALL] = {0};
    SDL_Texture* mTexture;

    int splits_count;

    int width_Texture;
    int height_Texture;

    int width_Smash;
    int height_Smash;

    TTF_Font* Font; // ����� 
};
