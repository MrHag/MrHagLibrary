#include "MrHagLibrary.h"
using namespace std;

void main()
{

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
	_getch();

}