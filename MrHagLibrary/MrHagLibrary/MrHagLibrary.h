#pragma once

#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <vector>
#include <windows.h>
#include <fstream>


namespace core
{

namespace Containers
{

	//Прототип динамічного масиву
	template<typename T>
	class Marray
	{

	private:

		T* v;
		int len;
		bool destroy;

	public:


		Marray(int a = 1)
		{

			destroy = false;
			len = a;
			v = new T[len];

		}


		Marray(Marray<T>* a)
		{

			v = a->v;
			len = a->len;
			destroy = a->destroy;

		}



		Marray(Marray<T> &a)
		{

			v = new T[a.len];

			for (int i = 0; i < a.len; i++)
				v[i] = a.v[i];

			len = a.len;

			destroy = a.destroy;

		}


		Marray& operator + (Marray &a)
		{

			int tmp_len = (len > a.len) ? a.len : len;

			Marray *n = new Marray(tmp_len);
			for (int i = 0; i < tmp_len; i++)
			{
				n->v[i] = v[i] + a.v[i];
			}
			n->len = len;
			n->destroy = true;
			Marray& k = *n;


			delete_if_destroy(&a);
			delete_if_destroy(this);

			return k;

		}


		Marray& operator + (T &a)
		{

			Marray* n = new Marray(len);
			for (int i = 0; i < len; i++)
				n->v[i] = v[i] + a;

			n->destroy = true;
			Marray& k = *n;
			delete_if_destroy(this);

			return k;
		}

		void operator ++(int)
		{

			add_size(1);

		}

		Marray& operator * (Marray &a)
		{
			int tmp_len = (len > a.len) ? a.len : len;

			Marray *n = new Marray(tmp_len);
			for (int i = 0; i < tmp_len; i++)
				n->v[i] = v[i] * a.v[i];

			n->destroy = true;
			Marray& k = *n;


			delete_if_destroy(&a);
			delete_if_destroy(this);

			return k;
		}

		Marray& operator *(T &a)
		{

			Marray *n = new Marray(len);
			n.destroy = false;
			for (int i = 0; i < len; i++)
				n->v[i] = v[i] * a;

			n->destroy = true;
			Marray& k = *n;


			delete_if_destroy(this);

			return k;
		}

		Marray& operator /(Marray &a)
		{

			int tmp_len = (len > a.len) ? a.len : len;

			Marray *n = new Marray(tmp_len);
			n->destroy = false;

			for (int i = 0; i < tmp_len; i++)
			{
				n->v[i] = v[i] / a.v[i];
			}

			n->destroy = true;
			Marray& k = *n;

			delete_if_destroy(&a);
			delete_if_destroy(this);

			return k;

		}


		Marray& operator / (T &a)
		{

			Marray *n = new Marray(len);
			for (int i = 0; i < len; i++)
			{
				n->v[i] = v[i] / a;
			}

			n->destroy = true;
			Marray& k = *n;

			delete_if_destroy(this);

			return k;
		}

		void operator = (Marray* a)
		{
			if (v)
				delete[] v;
			v = a->v;
			len = a->len;
			destroy = a->destroy;
		}






		void operator = (Marray &a)
		{

			if (v)
				delete[] v;
			v = new T[a.len];

			for (int i = 0; i < a.len; i++)
				v[i] = a.v[i];

			len = a.len;

			delete_if_destroy(&a);

		}


		void operator = (int a)
		{

			if (a != 0)
			{
				int min_len = (len > a) ? a : len;
				Marray tmp(1);

				tmp = *this;

				delete[] v;
				v = new T[a];

				for (int i = 0; i < min_len; i++)
					v[i] = tmp.v[i];
				len = a;
			}

		}

		bool operator ==(Marray &a)
		{

			if (len != a.len)
				return false;
			for (int i = 0; i < len; i++)
			{

				if (v[i] != a[i])
					return false;

			}
			return true;

		}

		bool operator !=(Marray &a)
		{

			if (len != a.len)
				return true;
			for (int i = 0; i < len; i++)
			{

				if (v[i] == a[i])
				{
				}
				else
					return true;

			}
			return false;

		}

		T& operator [](unsigned int a)
		{

			try
			{
				if (a >= len)
				{
					throw a;
				}
				return v[a];
			}
			catch (unsigned int a)
			{
				std::cout << a << " - Индекс вышел за пределы памяти ( " << 0 << " - " << len - 1 << " )" << endl;
			}


		}


		int get_len()
		{

			return len;

		}

		T* get_var()
		{

			return v;

		}

		void set_var(T a, int i)
		{

			v[i] = a;

		}

		void add_back(T a)
		{

			add_size(1);
			v[len - 1] = a;

		}

		void add_top(T a)
		{

			insert(a, 0);

		}


		void add_size(int a)
		{
			int tmp_len = len + a;
			int min_len = (len > len + a) ? len + a : len;
			if (min_len >= 0)
			{
				Marray tmp(1);

				tmp = *this;

				delete[] v;
				v = new T[tmp_len];

				for (int i = 0; i < min_len; i++)
					v[i] = tmp.v[i];
				len = tmp_len;
			}

		}

		void set_size(unsigned int a)
		{

			int min_len = (len > a) ? a : len;
			Marray tmp(1);

			tmp = *this;

			delete[] v;
			v = new T[a];

			for (int i = 0; i < min_len; i++)
				v[i] = tmp.v[i];
			len = a;

		}

		void outsert(unsigned int a)
		{

			if (a < len)
			{
				Marray tmp(1);

				tmp = *this;

				delete[] v;
				v = new T[len - 1];
				for (int i = 0, j = 0; i < len; i++)
				{
					if (i != a)
					{
						v[j++] = tmp[i];
					}

				}
				len--;


			}

		}

		void insert(T c, unsigned int a)
		{

			if (a < len)
			{
				Marray tmp(1);

				tmp = *this;

				delete[] v;
				v = new T[len + 1];
				for (int i = 0, j = 0; i < len + 1; i++)
				{
					if (i == a)
					{

						v[i] = c;

					}
					else
					{

						v[i] = tmp[j];
						j++;

					}



				}

				len++;
			}

		}


		void delete_if_destroy(Marray<T>* a)
		{

			if (a->destroy)
				delete a;

		}


		//friend ostream& operator<<(ostream& cout, Marray<T>& a);
		~Marray()
		{
			if (v)
				delete[] v;

		}





	};


	//Перегрузка cout
	template<typename T>
	std::ostream& operator << (std::ostream& cout, Marray<T>&a)
	{
		cout << "( ";
		for (int i = 0; i < a.get_len(); i++)
		{

			cout << a.get_var()[i];

			if (i < a.get_len() - 1)
				cout << ", ";

		}
		cout << " )";
		return cout;
	}


	std::ostream& operator << (std::ostream& cout, bool* a)
	{
		if (a)
			cout << "true";
		else
			cout << "false";
		return cout;
	}

}


namespace trifles
{
	using namespace Containers;


	namespace Console
	{

		namespace Cursor
		{
			//Ставить курсор консолі на вказані координати
			void SetCursorPos(int x, int y)
			{
				COORD position = { x,y };
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(hConsole, position);
			}

			void SetCursorPos(HANDLE hConsole, COORD position)
			{
				SetConsoleCursorPosition(hConsole, position);
			}

		}


		//Повертає массив розміру вікна консолі в символах
		int *GetConsoleCurrentSize()
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			int columns, rows;

			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			int arr[2] = { columns,rows };
			return arr;
		}


		int *GetConsoleMaxSize()
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			int columns, rows;

			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			columns = csbi.dwMaximumWindowSize.X;
			rows = csbi.dwMaximumWindowSize.Y;
			int arr[2] = { columns,rows };
			return arr;
		}




		void clear() {
			COORD topLeft = { 0, 0 };
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO screen;
			DWORD written;

			GetConsoleScreenBufferInfo(console, &screen);
			FillConsoleOutputCharacterA(
				console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
			);
			FillConsoleOutputAttribute(
				console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
				screen.dwSize.X * screen.dwSize.Y, topLeft, &written
			);
			SetConsoleCursorPosition(console, topLeft);
		}
		

		enum ConsoleColor
		{
			Black = 0,
			Blue = 1,
			Green = 2,
			Cyan = 3,
			Red = 4,
			Magenta = 5,
			Brown = 6,
			LightGray = 7,
			DarkGray = 8,
			LightBlue = 9,
			LightGreen = 10,
			LightCyan = 11,
			LightRed = 12,
			LightMagenta = 13,
			Yellow = 14,
			White = 15
		};

		void SetColor(ConsoleColor text, ConsoleColor background = Black)
		{
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
		}


		void Fullscreen()
		{
			HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD maxWindow = GetLargestConsoleWindowSize(out_handle); // размер самого большого возможного консольного окна
			SMALL_RECT srctWindow = { 0, 0, maxWindow.X - 1, maxWindow.Y - 1 };
			SetConsoleScreenBufferSize(out_handle, maxWindow);
			SetConsoleWindowInfo(out_handle, true, &srctWindow);
			SetWindowPos(GetConsoleWindow(), 0, -10, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}


		void Set_size(int x_symbols, int y_symbols)
		{
			COORD Window;
			Window.X = x_symbols;
			Window.Y = y_symbols;
			HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SMALL_RECT srctWindow = { 0, 0, Window.X - 1, Window.Y - 1 };
			SetConsoleWindowInfo(out_handle, true, &srctWindow);
			SetConsoleScreenBufferSize(out_handle, Window);
			SetConsoleWindowInfo(out_handle, true, &srctWindow);
		}


		void Set_position(int x, int y)
		{
			SetWindowPos(GetConsoleWindow(), 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}

		void fontsize(int a, int b) {
			PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
			lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
			GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, lpConsoleCurrentFontEx);
			lpConsoleCurrentFontEx->dwFontSize.X = a;
			lpConsoleCurrentFontEx->dwFontSize.Y = b;
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, lpConsoleCurrentFontEx);
		}

		//Зчитування та запис в консоль

		struct ConsoleManipulate
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			ConsoleManipulate()
			{

				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

			}
			std::string Read_console()
			{


				COORD coord = { 0,0 };
				DWORD len;

				//std::cout << "My string???" << std::endl;

				char* buffer = new char[csbi.dwSize.X*csbi.dwSize.Y + 1];//Выделяем память для буфера
				ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), buffer, csbi.dwSize.X*csbi.dwSize.Y, coord, &len);//Пишем в буфер
				std::string str = buffer;
				delete[] buffer;

				return str;
			}

			void Write_console(char* buffer)
			{


				COORD coord = { 0,0 };
				DWORD len;

				WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), coord, &len);//Пишем из буфера в консоль
				Cursor::SetCursorPos(GetStdHandle(STD_OUTPUT_HANDLE), csbi.dwCursorPosition);
			}


		};


		void print_colored_image(WORD* content, int width, int height, int key = 3)
		{
			WORD* p = content;
			int n = width * height;
			int l = n / key;

			DWORD d = 0;
			COORD t = { 0, 0 };

			int k = n / l;
			int cc = l;
			for (int i = 0; i < k; i++, cc += l)
			{
				WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p, l, t, &d);
				t.Y = cc / width;
				t.X = cc - t.Y * width;
				p = p + l;
			}
			int g = n - k * l;
			if (g > 0)
			{

				WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p, g, t, &d);

			}


		}



	}


	namespace Windows
	{

		enum MessageBox_types { Error, Question, Warning, Information };

		void MessageBox_Show(char* Content, char* caption, MessageBox_types type)
		{
			UINT t;

			switch (type)
			{
			case MessageBox_types::Error:t = MB_ICONERROR; break;
			case MessageBox_types::Question:t = MB_ICONQUESTION; break;
			case MessageBox_types::Warning:t = MB_ICONWARNING; break;
			case MessageBox_types::Information:t = MB_ICONINFORMATION; break;
			default:t = MB_ICONINFORMATION;
			}

			MessageBoxA(GetForegroundWindow(), Content, caption, t);

		}

	}

	template<typename T, typename T1, typename T2>
	T step(T1 a, T2 b)
	{
		T num = a;
		for (int i = 1; i < b; i++)
		{
			num = num * a;
		}
		if (b == 0)
			return 1;
		return num;
	}



	//Повертає массив мінімального і максимального елемента масиву та їх позиції;
	template<typename T>
	int* min_and_max(T &a, int size)
	{
		int min[2], max[2];
		min[0] = a[0];
		max[0] = a[0];
		for (int i = 0; i < size; i++)
		{
			if (min[0] > a[i])
			{
				min[0] = a[i];
				min[1] = i;
			}

			if (max[0] < a[i])
			{
				max[0] = a[i];
				max[1] = i;
			}

		}
		int arr[2] = { 0 };
		arr[0] = min[1];
		arr[1] = max[1];
		return arr;
	}


	

	//Прототип меню
	template<class T>
	class menu
	{

	public:
		Marray<T> *arr;
		int size, menu_pos, Zsize;


		menu()
		{

			arr = new Marray<T>;

		}
		menu(T *g_arr, int vsize, int Zs = 0)
		{
			arr = new Marray<T>;
			size = vsize;
			*arr = size;
			Zsize = Zs;
			menu_pos = Zsize;
			for (int i = 0; i < size; i++)
			{
				(*arr)[i] = g_arr[i];
			}
		}

		void new_menu(T *g_arr, int vsize, int Zs = 0)
		{
			delete arr;
			arr = new Marray<T>;
			size = vsize;
			*arr = size;
			Zsize = Zs;
			for (int i = 0; i < size; i++)
			{
				(*arr)[i] = g_arr[i];
			}
		}
		void print_menu()
		{
			system("cls");
			for (int i = 0; i < size; i++)
			{
				if (menu_pos == i)
				{
					std::cout << "> ";
				}
				std::cout << (*arr)[i] << endl;
			}
		}

		int active()
		{

			print_menu();
			int a = 0;
			while (a != 13)
			{
				a = _getch();
				if (a == 80)
				{
					menu_pos++;
					if (menu_pos >= size)
						menu_pos = Zsize;
					if (menu_pos < Zsize)
						menu_pos = size - 1;
				}
				else
					if (a == 72)
					{
						menu_pos--;
						if (menu_pos >= size)
							menu_pos = Zsize;
						if (menu_pos < Zsize)
							menu_pos = size - 1;
					}
				print_menu();

			}
			return menu_pos - Zsize;
		}

		~menu()
		{
			delete arr;
		}
	};




	void local(const char* string)
	{

		setlocale(LC_ALL, string);

	}


	/*
Функція рандому в заданому діапазоні
#include(time.h/string)
одноразовий запуск - srand(time(NULL));
*/
	int randomo(const unsigned long long int &a, const unsigned long long int &b)
	{
		if (a > b)
			return 0;
		return a + rand() % ((b - 1) - a);
	}


}


namespace Files
{

	void write_to_file(char* FileName, char* Content)
	{

		std::fstream file;
		file.open(FileName, std::ios::out);

		file << Content;

		file.close();

	}




	std::string read_from_file(char* FileName)
	{

		std::string Content;
		std::fstream file;
		file.open(FileName, std::ios::in);
		std::string tmp;
		while (file >> tmp)
		{
			if (!Content.empty())
				Content += ' ';
			Content += tmp;

		}

		file.close();

		return Content;

	}

}







namespace StringManipulate
{
	using namespace trifles;
	using namespace trifles::Console;
	using namespace Containers;

	//Функція яка повертає розмір константного массиву
	template<typename T>
	int size_const(T &a)
	{
		return sizeof(*a) / sizeof(*a[0]);
	}

	int size_char_string(char *string)
	{
		int i = 0;
		while (string[i++] != '\0')
		{
		}
		return i;
	}

	//Повертає массив вектора від стрічки, яка розбивається символом "key";
	std::vector<std::string> parsing_string(std::string a, char key)
	{
		std::vector<std::string>arr;
		std::string tmp;
		for (int i = 0; i < a.length(); i++)
		{
			if (a[i] == key || i + 1 == a.length())
			{
				arr.push_back(tmp);
				tmp = "";
			}
			else
			{
				tmp = tmp + a[i];
			}
		}
		return arr;
	}

	//Полегшує роботу з cin
	template<typename T1>
	T1 Mwrite()
	{
		T1 a;
		cin >> a;
		return a;
	}



	int char_to_int(char c)
	{
		switch (c)
		{
		case '0':return 0;
		case '1':return 1;
		case '2':return 2;
		case '3':return 3;
		case '4':return 4;
		case '5':return 5;
		case '6':return 6;
		case '7':return 7;
		case '8':return 8;
		case '9':return 9;
		default: return -1;
		}
	}

	template<typename T>
	T string_to_number(char *string, int size = 0, const char* del = "")
	{

		if (size == 0)
			size = size_char_string(string);
		bool chk = true;
		bool negative = false;
		bool numm = false;
		bool point = false;
		int position = -1;
		Marray<int> arr(1);
		bool stop = false;
		for (int i = 0; i < size && !stop; i++)
		{

			int g = char_to_int(string[i]);
			if (g != -1)
			{

				arr[arr.get_len() - 1] = g;
				arr = arr.get_len() + 1;
				numm = true;
				chk = false;
			}
			else
			{

				if (string[i] == '-' && chk)
				{
					if (i + 1 < size)
					{
						g = char_to_int(string[i + 1]);
						if (g != -1)
						{
							chk = false;
							negative = true;
						}
					}
				}
				else
				{


					if ((string[i] == '.' || string[i] == ',') && numm && !point)
					{
						if ((T).1 != (int).1)
						{
							point = true;
							position = arr.get_len() - 1;
						}
						else
						{
							stop = true;
						}
					}

				}
			}
		}

		arr = arr.get_len() - 1;
		T num = 0;
		for (int i = 0; i < arr.get_len(); i++)
		{

			num += step<T>(10, arr.get_len() - 1 - i) * arr[i];

		}
		if (position != -1 && position < arr.get_len())
			num = num / step<T>(10, (arr.get_len() - position));
		if (negative)
			num = -num;
		if (del == "delete")
			delete[] string;
		return num;

	}

	//Прототип для запису стрічки
	class Write
	{
	public:


		int count;
		char *b;
		int pos;
		int pre_size;
		ConsoleManipulate cons;
		void write(std::string* out, const char *pre_str = "")
		{
			int CP = GetConsoleCP();
			SetConsoleCP(1251);
			//SetConsoleOutputCP(1251);

			std::string buffer = cons.Read_console();


			b = new char[1];
			b[0] = '\0';

			count = 1;
			pre_size = strlen(pre_str);
			pos = 0;
			print(pre_str);
			char a = _getch();
			while (a != 13)
			{
				if (a != 0)
				{
					if (a != '\b')
					{
						if (a == -32)
						{

							int b = _getch();
							if (b != 0)
							{
								if (b == 75)
								{
									a = -1;
									pos--;
									if (pos < 0)
									{
										pos = count - 1;
									}

								}
								else
								{
									if (b == 77)
									{
										a = -1;
										pos++;
										if (pos > count - 1)
										{
											pos = 0;
										}
									}
									else if (b == 83)
									{
										outsert(pos, false);
									}
									else
									{

									}
								}
							}
							else
							{
								insert(a, pos++);
							}
						}
						else
						{
							insert(a, pos++);

						}
					}
					else
					{
						outsert(pos - 1);

					}
				}

				print(pre_str);

				a = _getch();
			}

			set(out);


			cons.Write_console((char*)buffer.c_str());
			SetConsoleCP(CP);
			_getch();
		}


		void print(const char* pre_str)
		{

			clear();
			SetConsoleCP(866);
			std::cout << pre_str;
			std::cout << b;
			int y = (int)((pos + pre_size) / GetConsoleMaxSize()[0]);
			Cursor::SetCursorPos((pos + pre_size) - y * GetConsoleMaxSize()[0], y);
			SetConsoleCP(1251);

		}


		void set(std::string* to)
		{
			*to = b;
		}
		char* resize(char *bi, int s)
		{
			char *tmp = new char[count];
			for (int i = 0; i < count; i++)
			{
				tmp[i] = bi[i];
			}

			//Delete();

			int min = 0;
			if (count > s)
				min = s;
			else
				min = count;

			delete[] bi;
			bi = new char[s];
			for (int i = 0; i < min; i++)
			{
				bi[i] = tmp[i];
			}
			count = s;
			delete[] tmp;
			return bi;
		}

		void insert(char c, int p)
		{
			b = resize(b, count + 1);
			for (int i = count - 1; i > p; i--)
			{
				b[i] = b[i - 1];
			}
			b[p] = c;
		}

		void outsert(int p, bool left = true)
		{
			if (p >= 0 && p < count - 1)
			{
				for (int i = p; i < count - 1; i++)
				{
					b[i] = b[i + 1];
				}
				b = resize(b, count - 1);
				if (left)
				{
					pos--;
				}
			}
		}

		~Write()
		{
			if (b)
			{
				delete[] b;
			}

		}
	};


	// Полегшує роботу з класом Write
	std::string My_Mwrite(const char* text = "")
	{
		Write *Buf = new Write;
		std::string string;
		Buf->write(&string, text);
		delete Buf;
		return string;
	}



}







}






/*
class Screen
{
public:




};

*/

