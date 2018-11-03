/*
	This application was created for test Translate() function. 
	It was made with olcPixelGameEngine framework, that you can find here:
	https://github.com/OneLoneCoder/olcPixelGameEngine
	
	The app displaying kind of "mountains" (they're weird). 
	Use arrows to "move" the camera

*/

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		tx = 0;
		ty = 30;

		// Generating the mountains
		for (int deep = 0; deep < 3; deep++)
		{
			for (int i = 0; i < 48; i++)
			{
				int y = rand() % 20 - (i%2 * 40);
				int x = i * 50;
				std::pair<int, int> point(x, y);

				mountains[deep].push_back(point);
			}
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Exit the application
		if (GetKey(olc::ESCAPE).bPressed)
			return false;

		// Clear the screen 
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(0, 20, 40));

		Translate(-ScreenWidth()*1.5, ScreenHeight()*0.3);


		// Display the mountains
		for (int deep = 0; deep < 3; deep++)
		{
			// Stack translations 
			Translate(tx, ty);

			for (int i = 0; i < mountains[deep].size()-2; i+=2)
			{
				int gray = deep * 20 + 30;
				FillTriangle(mountains[deep][i].first, mountains[deep][i].second, 
							mountains[deep][i + 1].first, mountains[deep][i + 1].second,
							mountains[deep][i + 2].first, mountains[deep][i + 2].second,
							olc::Pixel(gray, gray, gray));
			}
		}
		// Display the translate values
		FillRect(-GetTranslateX(), -GetTranslateY(), 250, 20, olc::Pixel(10, 10, 10));
		std::string trans = "Translation in xy: " + std::to_string(GetTranslateX()) + ", " + std::to_string(GetTranslateY());
		DrawString(-GetTranslateX() + 5, -GetTranslateY() + 5, trans);

		// Move the camera
		int step = -3;

		if (GetKey(olc::UP).bHeld)
			ty -= step;
		if (GetKey(olc::DOWN).bHeld)
			ty += step;
		if (GetKey(olc::LEFT).bHeld)
			tx -= step;
		if (GetKey(olc::RIGHT).bHeld)
			tx += step;

		return true;
	}

private:
	int tx, ty;
	std::vector<std::pair<int, int>> mountains[3];
};


int main()
{
	Example demo;
	if (demo.Construct(600, 400, 1, 1))
		demo.Start();

	return 0;
}
