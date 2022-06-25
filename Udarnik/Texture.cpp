#include "Texture.h"

Work_With_Texture::Work_With_Texture()
{
	center_flip_x = NULL,  center_flip_y = NULL,  angel_Flip = NULL;

	mTexture = NULL;
	
	alphaTransparency = 255;

	width_Texture = NULL,  height_Texture = NULL;

	width_Smash = NULL,  height_Smash = NULL;
	
	splits_count = NULL,  steps_Width = NULL,  steps_Height = NULL;

	
	Font = TTF_OpenFont("Resources/PFAgoraSlabPro Bold.ttf", FONT_SIZE); // ��������� ������ �� ���������

	ArrayMediaSurface = IMG_Load("Resources/number_dot_min.png"); // �������� �������� �� �����������
}
Work_With_Texture::~Work_With_Texture()
{
	for (int i = 0; i < splits_count; i++)
	{
		SDL_DestroyTexture(array_Smash_Texture[i]);
	}
	SDL_DestroyTexture(mTexture);
	free();
}

void Work_With_Texture::setFontOnSurface(string str) //1104
{
	Uint16* tempSTR = new Uint16[str.length()+1]{};
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] < 0)
			tempSTR[i] = str[i] + 1104 ;
		else
			tempSTR[i] = str[i];
	}
	setFontOnSurfaceUNICODE(tempSTR);
	delete[]tempSTR;
}

void Work_With_Texture::setFontOnSurfaceUNICODE(const Uint16* str)
{
	SDL_Color color = { 0, 0, 0 };
	//SDL_Color backgorund_color = { 255,255,255 };
	SDL_Surface* temp = TTF_RenderUNICODE_Solid(Font,str, color);
	
	mTexture = SDL_CreateTextureFromSurface(gRenderer, temp);
	SDL_QueryTexture(mTexture, NULL, NULL, &width_Texture, &height_Texture); // ��������� ���������� ��������

	SDL_FreeSurface(temp);
}

// �������� ������� �����
void Work_With_Texture::setTexture(string path) // �������� ����� �������� ��� ������������ ������ ����� ��������
{
	SDL_Surface* mediaSurface = IMG_Load(path.c_str());
	mTexture = SDL_CreateTextureFromSurface(gRenderer ,  mediaSurface);
	SDL_QueryTexture(mTexture ,  NULL ,  NULL ,  &width_Texture ,  &height_Texture); // ��������� ���������� ��������

}

void Work_With_Texture::setTexture(string path ,  int R ,  int G ,  int B) // �������� ����� �������� � ���������� ������������ ������ ����� ��������
{
	SDL_Surface* mediaSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(mediaSurface ,  SDL_TRUE ,  SDL_MapRGB(mediaSurface->format ,  R ,  G ,  B));  // ��������� ����� ������������
	mTexture = SDL_CreateTextureFromSurface(gRenderer ,  mediaSurface);
	SDL_QueryTexture(mTexture ,  NULL ,  NULL ,  &width_Texture ,  &height_Texture); // ��������� ���������� ��������
}
// ��� ����������
void Work_With_Texture::setTexture(string path ,  int width_Smash ,  int height_Smash) // �������� ���������� ������� �� ����� / ��������� ����������� �� ������� ��� ������������ ������ ����� ��������
{
	//SDL_Surface* mediaSurface = IMG_Load(path.c_str()); // �������� �������� �� �����������
	mTexture = SDL_CreateTextureFromSurface(gRenderer , ArrayMediaSurface);// �������� ����� ��������

	width_Texture = ArrayMediaSurface->w; // ������ ����������� � �������� ��������
	height_Texture = ArrayMediaSurface->h; // ������ ����������� � �������� ��������

	splits_count = width_Smash * height_Smash; // ����� ������� �� ����� �����������
	steps_Width = width_Texture / width_Smash; // ��� ��� �������� �� �������� ��� ������� �� ���������� X
	steps_Height = height_Texture / height_Smash; // ��� ��� �������� �� �������� ��� ������� �� ���������� Y

	SDL_Rect tempRect; // ������� ��� ��������� 
	int i = 0;
	for (int y = 0; y < height_Texture - 10; y += steps_Height) // �������� ���� �� �����������
	{
		for (int x = 0; x < width_Texture - 10; x += steps_Width) // �������� ������ �� �����������
		{
			tempRect = { x , y , steps_Width , steps_Height }; // ������ ��� ����� ���������
			SDL_BlitScaled(ArrayMediaSurface,  &tempRect ,  gScreenSurface ,  NULL); // ��������� �� ��������� ����������� ������� ��������� ����������� 
			array_Smash_Texture[i] = SDL_CreateTextureFromSurface(gRenderer ,  gScreenSurface); // ���������� � ������ ���� ��������
			i++; // i-1 ����� ���������� �������
		}
	}
}
void Work_With_Texture::setTexture(string path ,  int width_Smash ,  int height_Smash ,  int R ,  int G ,  int B) // �������� ���������� ������� �� ����� / ��������� ����������� �� ������� ������������ ������ ����� ��������
{
	SDL_Surface* mediaSurface = IMG_Load(path.c_str()); // �������� �������� �� �����������
	mTexture = SDL_CreateTextureFromSurface(gRenderer ,  mediaSurface);// �������� ����� ��������

	width_Texture = mediaSurface->w; // ������ ����������� � �������� ��������
	height_Texture = mediaSurface->h; // ������ ����������� � �������� ��������

	splits_count = width_Smash * height_Smash; // ����� ������� �� ����� �����������
	steps_Width = width_Texture / width_Smash; // ��� ��� �������� �� �������� ��� ������� �� ���������� X
	steps_Height = height_Texture / height_Smash; // ��� ��� �������� �� �������� ��� ������� �� ���������� Y

	SDL_Rect tempRect; // ������� ��� ��������� 
	SDL_SetColorKey(gScreenSurface ,  SDL_TRUE ,  SDL_MapRGB(gScreenSurface->format ,  R ,  G ,  B)); // ��������� ����� ������������

	int i = 0; // ����� �������� ������� 
	for (int y = 0; y < height_Texture - 10; y += steps_Height) // �������� ���� �� �����������
	{
		for (int x = 0; x < width_Texture - 10; x += steps_Width) // �������� ������ �� �����������
		{
			tempRect = { x , y , steps_Width , steps_Height }; // ������ ��� ����� ���������
			SDL_BlitScaled(mediaSurface ,  &tempRect ,  gScreenSurface ,  NULL); // ��������� �� ���������� ����������� ������� ��������� ����������� 
			array_Smash_Texture[i] = SDL_CreateTextureFromSurface(gRenderer ,  gScreenSurface); // ���������� � ������ ���� ��������
			i++; // i-1 ����� ���������� �������
		}
	}
}
/////////////////////////////////


void Work_With_Texture::TransferToRenderFont(int x,int y) // ����������� ������ �� ������
{
	SDL_Rect font_rect = { x,y,this->width_Texture,this->height_Texture};
	SDL_RenderCopy(gRenderer, mTexture, NULL, &font_rect);
	SDL_DestroyTexture(mTexture);
}

// ����������� ������� ����� // ��� ���������� 
void Work_With_Texture::TransferToRender(int x ,  int y) // ����������� ����� �������� �� ������
{
	SDL_Rect rect = { x , y , SCREEN_WIDTH , SCREEN_HEIGHT }; // ������� ��� ������
	SDL_Point center = { center_flip_x ,  center_flip_y };
	
	SDL_RenderCopyEx(gRenderer ,  mTexture ,  NULL ,  &rect ,  angel_Flip ,  &center ,  SDL_FLIP_NONE);
}
void Work_With_Texture::TransferArrayToRender(int x ,  int y ,  int frame) // ����������� �� ���������� ������� �� ������ ��� ��������� ����� ��������
{
	//////SDL_SetTextureBlendMode(array_Smash_Texture[frame] ,  SDL_BLENDMODE_BLEND); // �������� ����� ����������� ������������
	SDL_SetTextureAlphaMod(array_Smash_Texture[frame] ,  alphaTransparency); // ��������� ������������

	SDL_Rect rect = { x  ,  y ,  steps_Width/6 ,  steps_Height/6 }; //������� ��� ������ 

	SDL_Point center = {center_flip_x ,  center_flip_y}; // ����� �������� // �� ��������� ����� ������
	SDL_RenderCopyEx(gRenderer ,  array_Smash_Texture[frame] ,  NULL ,  &rect ,  angel_Flip ,  &center ,  SDL_FLIP_NONE);
	
}
/////////////////////////////////

// ��������� ������������
void Work_With_Texture::SetAlphaTransparency(int alphaTransparency)
{
	this->alphaTransparency = alphaTransparency;
	SDL_SetTextureBlendMode(mTexture ,  SDL_BLENDMODE_BLEND); // �������� ����� ����������� ������������
	SDL_SetTextureAlphaMod(mTexture ,  alphaTransparency);
}
// ��������� ���� ��������
void Work_With_Texture::SetAngelFlip_Center(int angel_Flip ,  int center_flip_x ,  int center_flip_y)
{
	this->angel_Flip = angel_Flip;
	this->center_flip_x = center_flip_x;
	this->center_flip_y = center_flip_y;
}

void Work_With_Texture::free() // ������������ ������ ��� ����������� �������
{
	mTexture = NULL;
	width_Texture = NULL;
	height_Texture = NULL;
	for (int i = 0; i < SPRITE_FRAME_ALL; i++)
		array_Smash_Texture[i] = NULL;
}