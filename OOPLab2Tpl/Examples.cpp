#if !defined(_MSC_VER)
#define VS_CODE
#endif
#include <iostream>
#include <fstream>
using namespace std;
#include <clocale>
#include <string.h>
#if !defined(VS_CODE)
	#include <Windows.h>
#endif
#include "Examples.h"
enum  ConsoleColor : unsigned int
{							//0000 IRGB  
	Black = 0x00,			//0000 0000
	Blue = 0x01,			//0000 0001
	Green = 0x02,			//0000 0010
	Cyan = 0x03,			//0000 0011
	Red = 0x04,				//0000 0100
	Magenta = 0x05,			//0000 0101
	Brown = 0x06,			//0000 0110
	LightGray = 0x07,		//0000 0111 
	DarkGray = 0x08,		//0000 1000
	LightBlue = 0x09,		//0000 1001
	LightGreen = 0x0a,		//0000 1010
	LightCyan = 0x0b,		//0000 1011
	LightRed = 0x0c,		//0000 1100
	LightMagenta = 0x0d,	//0000 1101
	Yellow = 0x0e,			//0000 1110
	White = 0x0f			//0000 1111
};
#if !defined(VS_CODE)
void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, (WORD)((background << 4) | text));
}
#endif
void MenuExamples() {
	#if !defined(VS_CODE)
	SetColor(Blue, Black);
	#endif
	cout << "     Examples   \n";
	#if !defined(VS_CODE)
	SetColor(Green, Black);
	
	cout << "    1.  Приклад переводу цілого числа з десяткової системи в двійкову \n";
	cout << "    2.  Приклад обчислення виразу використовуючи тiльки побiтовi операцiї. \n";
	cout << "    3.  Приклад шифрування рядка в 64 байти   \n";
	cout << "    4.  Приклад розшифрування рядка в 64 байти   \n";
	cout << "    5.   \n";
	cout << "    6.  Exit \n";
	#else
	cout << "    1.  An example of converting an integer from the decimal system to binary \n";
	cout << "    2.  An example of calculating an expression using only bitwise operations. \n";
	cout << "    3.  An example of encrypting a 64-byte string   \n";
	cout << "    4.  An example of deencrypting a string of 64 bytes   \n";
	cout << "    5.   \n";
	cout << "    6.  Exit \n";

	#endif
}
void Examples()
{   // Examples of tasks using bitwise operations
    // Приклади задач з використанням побітових операцій
  
	#if !defined(VS_CODE)
	setlocale(LC_CTYPE, "ukr");  // 
	cout << " Приклади задач з використанням побiтових операцiй \n";
#else
   cout << " Examples of tasks using bitwise operations \n";
#endif
	char ch = '5';
	do {
		system("cls");
		MenuExamples();
		ch = cin.get();

		cin.get();

		switch (ch) {
		case '1': Example1();   break;
		case '2': Example2();   break;
		case '3': Example3();   break;
		case '4': Example4();   break;
		case '5':  Example5();  break;
		case '6': 
		#if !defined(VS_CODE)
		SetColor(White, Black); 
		#endif
		return ;
		}
		cout << " Press any key and enter\n";
		ch = cin.get();
	} while (ch != '6');
#if !defined(VS_CODE)
	SetColor(White, Black);
#endif
	return ;
}

#include <clocale>
// An example of converting an integer from the decimal system to binary  
//  Приклад переводу цілого числа з десяткової системи в двійкову
void Example1()
{
	char out[17];
	int i, in, ix, n = 0;
	double x;
	#if !defined(VS_CODE)
	cout << " Введiть цiле додатне число:";
	#else 
	cout << " Enter a positive integer:";
#endif
	cin >> in;
	auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }

	if (in != 0) {
		x = in;
		do {
			x = x / 2.;
			ix = (int)x;
			if ((x - ix) != 0) out[n] = '1';
			else out[n] = '0';
			n++;
			x = ix;
		} while (x >= 1);
	}
	#if !defined(VS_CODE)
cout << " Результат: \n";
	#else 
	cout << " Rezult:";
#endif
	
	for (i = n - 1; i >= 0; i--)
		cout << out[i];
	cout << endl;
	cin.get();

	return;
}
/*
* Приклад обчислення виразу використовуючи тільки побітові операції.
* Вираз : x = 33 * a + (a * 16 – b * 17) / 8 + (15 * b + 300) / 128.
*
*/
void Example2()
{
	int a, b, x, y;
	#if !defined(VS_CODE)
cout << "Приклад обчислення виразу використовуючи тiльки побiтовi операцiї.\n";
	cout << "Вираз : x = 33 * a + (a * 16 – b * 17) / 8 + (15 * b + 300) / 128. \n";
	cout << " Введiть a  b ";
	#else 
cout << "An example of calculating an expression using only bitwise operations.\n";
	cout << "Expression : x = 33 * a + (a * 16 – b * 17) / 8 + (15 * b + 300) / 128. \n";
	cout << " Input a  b ";
#endif
	
	cin >> a >> b;
    auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }
	x = a + (a << 5) + (((a << 4) - b - (b << 4)) >> 3) + (((b << 4) - b + 300) >> 7);
	y = a * 33 + (a * 16 - b * 17) / 8 + (15 * b + 300) / 128;
	cout << "  x=" << x << "  y=" << y << " a=" << a << "  b=" << b << endl;
	cin.get();
	cin.get();
	return;
}
/*
Задано текст ASCII (текстовий рядок), який складається з 64 букв. 
Написати функції шифрування та розшифрування заданого тексту. 
Кожна при шифруванні буква тексту буде записана у елемент, 
який складається з двох байтів та має структуру:
  -  у бітах 0-3 старша частина, тобто біти 4-7 ASCII - коду букви (4 біти) - СЧКБ,
  -  у бітах 4-10 позиція букви у рядку (7 біти) - ПБР,
  -  у бітах 12-15 молодша частина, тобто біти 0-3 ASCII - коду букви (4 біти) - МЧКБ,
  -  11 біт – біт парності отриманого запису (1 біт)  -БП.
  -    15 14 13 12  11  10 09 08 07 06 05 04 03 02 01 00
       | МЧКБ    | |БП| |     ПБР          | |   СЧКБ  |    
*/
void MyEncryption(char InS[64], unsigned short OutCoding[64])
{
	unsigned char c;
	unsigned short r, t, i, b;
	short j;
    for (i = 0; i < 64; i++)            //
	{
		r = 0;                        // 0000 0000 0000 0000
		c = InS[i];                     // s - 0x73 = 0111 0011
		t = c;
		r |= t >> 4;                  // 0000 0000 0000 0111
		r |= i << 4;                  // 0000 0000 0101 0111  if i=5 -> 0000 0000 0000 0101
		t = c;
		r |= t << 12;                 // 0011 0000 0101 0111  if i=5 0000 0000 0000 0101
		t = 1;
		b = 0;
		for (j = 0; j < 16; j++)         // обчислення біта парності
		{
			if (r & t) {
				if (b == 0) b = 1; else b = 0;
			}
			t <<= 1;
		}
		r |= b << 11;                    // 0011 0000 0101 0111 if i=5 0000 0000 0000 0101
		OutCoding[i] = r;
	}
}
struct TextCode {
	unsigned short schkb	: 4;
	unsigned short posrow	: 7;
	unsigned short bitp		: 1;
	unsigned short mchkb	: 4;

};
unsigned char pbit(unsigned char c)
{
	unsigned char t = 1, b = 0;
	for (int j = 0; j < 8; j++)         // обчислення біта парності
	{
		if (c & t) {
			if (b == 0) b = 1; else b = 0;
		}
		t <<= 1;
	}
	return b;
}
void MyEncryptionS(char InS[64], TextCode OutCoding[64])
{
	unsigned char c;
	unsigned short r, t, i;
	short j;
	for (i = 0; i < 64; i++)            //
	{
		c = InS[i];                     // s - 0x73 = 0111 0011
		OutCoding[i].schkb = c >> 4;
		OutCoding[i].mchkb = c & 0x0f;
		OutCoding[i].posrow = i;
		r = pbit(c);
		t = pbit(static_cast<unsigned char>(i));
		OutCoding[i].bitp = r^t;
	}
}

int MyDecryption(char OutS[64], unsigned short InCoding[64]) {
	
	unsigned char c;
	unsigned short r, t, i, b, p, w;
	short j;
	for (i = 0; i < 64; i++)            //
	{
		// Перевірка парності
		r = InCoding[i];
		t = r & 0b1111011111111111;      //  0xf7ff			1111 0111 1111 1111
		p = r & 0b0000100000000000;      //  0x0800			0000 1000 0000 0000
		w = 1;
		b = 0;
		for (j = 0; j < 16; j++)         // обчислення біта парності
		{
			if (t & w) {
				if (b == 0) b = 1; else b = 0;
			}
			w <<= 1;
		}
		p >>= 11;
		if (p != b)  return -i;
		t = r & 0b1111000000000000;  // 0xf000
		t >>= 12;
		w = r & 0b0000000000001111;  // 0x000f
		w <<= 4;
		t |= w;
		p = r & 0b0000011111110000;  // 0x07f
		p >>= 4;
		OutS[p] = (unsigned char)t;
	}
	return 1;
}
/*
* Приклад шифрування рядка в 64 байти  
*
*/

void Example3() {
	char S[65];
	unsigned short Rez[64];
	unsigned short i, f;
	cout << " Input string from file press 1 <Enter>\n ";
	cin >> f;
	if (f == 1) {
			ifstream ifs("in.txt");
			if (!ifs) {
				cout << "File in.txt not open" << endl; f = 2;
				}
				else {
				ifs.get(S, 64);
				ifs.close();
				}
		}
	if(f!=1) {
		cin.get();
		cout << " Input string (size <=64) \n";
		cin.get(S, 64);
	}
	int n = strlen(S);
	for (int i = n; i < 64; i++) S[i] = '\0';

	MyEncryption(S, Rez);

	for (i = 0; i < 64; i++)
		cout << hex << Rez[i] << endl;
	ofstream ofsb("outb.bin", ios::out | ios::binary);
	if (!ofsb) {
		cout << "File outb.bin not open" << endl;
	}
	else {
		ofsb.write((char*)Rez, 64 * sizeof(unsigned short));
		ofsb.close();
		cout << "Data write to outb.bin " << endl;
		cout << S << endl;
	}
	cin.get();
}
void Example4() {
	char S[65];
	unsigned short InBin[64]{};
	ofstream ofs("out.txt");
	if (!ofs) {
		cout << "File out.txt not open" << endl;
		return;
	}
	ifstream ifsb("outb.bin", ios::in | ios::binary);
	if (!ifsb) {
		cout << "File outb.bin not open" << endl;
		return;
	}
	ifsb.read((char*)InBin, 64 * sizeof(unsigned short));
	ifsb.close();
	cout << "Data read from outb.bin " << endl;
	
	int r;
	r = MyDecryption(S, InBin);
	if (r < 1) {
		cout << "Error  read  " << r << " row " << endl;
	}
	cout << "String  " << S << endl;
	ofs << S << endl;
	cin.get();
}


void Example5() {
	char S[65];
	TextCode Rez[64];
	unsigned short i, f;
	cout << " Input string from file press 1 <Enter>\n ";
	cin >> f;
	if (f == 1) {
		ifstream ifs("in.txt");
		if (!ifs) {
			cout << "File in.txt not open" << endl; f = 2;
		}
		else {
			ifs.get(S, 64);
			ifs.close();
		}
	}
	if (f != 1) {
		cin.get();
		cout << " Input string (size <=64) \n";
		cin.get(S, 64);
	}
	int n = strlen(S);
	for (int i = n; i < 64; i++) S[i] = '\0';

	MyEncryptionS(S, Rez);

	
	ofstream ofsb("outbs.bin", ios::out | ios::binary);
	if (!ofsb) {
		cout << "File outbs.bin not open" << endl;
	}
	else {
		ofsb.write((char*)Rez, 64 * sizeof(TextCode));
		ofsb.close();
		cout << "Data write to outbs.bin " << endl;
		cout << S << endl;
	}
	cin.get();

}