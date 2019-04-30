#include "MrHagLibrary.h"
using namespace std;
using namespace core;
using namespace core::Containers;
using namespace core::Files;
using namespace core::StringManipulate;
using namespace core::trifles;






void main()
{

	trifles::local("UKR");
	fontsize(1, 1);
	Fullscreen();
	int *a = GetConsoleCurrentSize();
	int b = a[0];
	int c = a[1];
	int n = b * c;
	

	WORD* mm = new WORD[n];
	//SetColor(ConsoleColor::Black, (ConsoleColor)randomo(0, 14));
	while (true)
	{
		Sleep(60);
		a = GetConsoleCurrentSize();
		b = a[0];
		c = a[1];
		n = b * c;
		delete mm;
		mm = new WORD[n];

		for (int i = 0; i < n; i++)
		{
			//mm[i] = ((randomo(0, 14) << 4) | ' ');
			mm[i] = (randomo(0, 14) << 4);

		}
		print_colored_image(mm, b, c, 3);
	}
	delete mm;

	_getch();
	
	_getch();
}