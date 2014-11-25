#include "Font_Handler.h"


/****************************************************
* Write method
* Writes text to scene in chosen font.
* Created by:	Mark Murphy		Date: Nov. 25, 2014
* Modified by:	Mark Murphy		Date: Nov. 25, 2014
*****************************************************/
void Font_Handler::Write(bool otherFont, int x, int y, std::string s)
{
	bfont->DrawText(otherFont, x, y, s);
}

/****************************************************
* ChangeFontSize method
* Changes font size.
* Created by:	Mark Murphy		Date: Nov. 25, 2014
* Modified by:	Mark Murphy		Date: Nov. 25, 2014
*****************************************************/
void Font_Handler::ChangeFontSize(float newSize)
{
	if (newSize != fontSize)
	{
		fontSize = newSize;
		//load a font set
		bfont = blit3D->MakeBFont("font.png", "fontMetrics.dat", fontSize);
		assert(bfont != NULL); //make sure it loaded
	}
}

/****************************************************
* Font_Handler constructor
* Sets initial value.
* Created by:	Mark Murphy		Date: Nov. 25, 2014
* Modified by:	Mark Murphy		Date: Nov. 25, 2014
*****************************************************/
Font_Handler::Font_Handler(Blit3D *b3D, float fSize)
{
	blit3D = b3D;

	float fontSize = fSize;

	//load a font set
	bfont = blit3D->MakeBFont("font.png", "fontMetrics.dat", fontSize);
	assert(bfont != NULL); //make sure it loaded
}

/****************************************************
* Font_Handler deconstructor
* Frees memory.
* Created by:	Mark Murphy		Date: Nov. 25, 2014
* Modified by:	Mark Murphy		Date: Nov. 25, 2014
*****************************************************/
Font_Handler::~Font_Handler()
{
	if (bfont) delete bfont;
}