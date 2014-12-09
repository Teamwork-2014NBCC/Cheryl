#ifndef _FONT_HANDLER_H_
#define _FONT_HANDLER_H_

#include <blit3d/Blit3D.h>

class Font_Handler
{
private:
	Blit3D *blit3D = NULL;
	BFont *bfont = NULL;
	float fontSize;

public:
	void Write(bool otherFont, int x, int y, std::string s);
	void ChangeFontSize(float newSize);

	Font_Handler(Blit3D *b3D, float fSize);
	~Font_Handler();
};

#endif