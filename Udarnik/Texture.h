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

extern SDL_Window* gWindow; // Глобальное окно для всего
extern SDL_Surface* gScreenSurface; // Глобальная поверхность для глобального окна 
extern SDL_Renderer* gRenderer; // Отображает состояние рендеринга Помогает рендерить текстуры на экран


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

    void setFontOnSurface(string str); // Загрузка текста Через обычный ввод
    void setFontOnSurfaceUNICODE(const Uint16* str); // Загрузка текста Если есть строка UNICODE
    void setTexture(string path); // Загрузка ОДНОЙ текстуры без прозрачности ЗАДНЕЙ ЧАСТИ ТЕКСТУРЫ
    void setTexture(string path ,  int R ,  int G ,  int B); // Загрузка ОДНОЙ текстуры с установкой прозрачносии ЗАДНЕЙ ЧАСТИ ТЕКСТУРЫ
    void setTexture(string path ,  int width_Smash ,  int height_Smash); // Загрузка НЕСКОЛЬКИХ текстур из одной / разбиения поверхности на частицы БЕЗ ПРОЗРАЧНОСТИ ЗАДНЕЙ ЧАСТИ ТЕКСТУРЫ
    void setTexture(string path ,  int width_Smash ,  int height_Smash ,  int R ,  int G ,  int B); // Загрузка НЕСКОЛЬКИХ текстур из одной / разбиения поверхности на частицы ПРОЗРАЧНОСТЬ ЗАДНЕЙ ЧАСТИ ТЕКСТУРЫ

    void TransferToRenderFont(int x, int y);
    void TransferToRender(int x ,  int y); // Отображение ОДНОЙ текстуры на рендер 
    void TransferArrayToRender(int x ,  int y ,  int frame); // Отображение из НЕСКОЛЬКИХ текстур ОПРЕДЕЛЕННОГО ФРЕЙМА на рендер 
    
    void SetAlphaTransparency(int alphaTransparency); // Установка прозрачности
    void SetAngelFlip_Center(int angel_Flip ,  int x ,  int y);

    void free(); // Освобождение памяти При уничтожении объекта

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

    TTF_Font* Font; // Шрифт 
};
