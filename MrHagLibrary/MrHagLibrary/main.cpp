#include "MrHagLibrary.h"
using namespace std;

void main()
{
	local("UKR");
	Marray<int> a = 0;
	a.add_size(1);
	a[a.get_len() - 1] = 1;
	a.add_size(1);
	a[a.get_len() - 1] = 2;
	a.add_size(1);
	a[a.get_len() - 1] = 3;


	a.insert(5, 1);
	a.insert(5, 1);
	a.outsert(1);

	cout << a << endl;

	a.add_top(10);



	cout << a << a;

	a = a + a + a;

	cout << a << endl;

	int h = 5;

	a = a / h;

	cout << a << endl;
	_getch();

	write_to_file("file.txt",(char*)My_Mwrite("Записать в файл: ").c_str());

	cout << read_from_file("file.txt");


	string text_my_menu[3] = { "Виберiть пункт меню", "Порахувати", "Вийти" };
	menu<string> my_menu(text_my_menu, 3, 1);

	my_menu.active();
	
	_getch();

	

}