#include <bitset>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

struct charBit {
  unsigned char starshaChastyna : 4;
  unsigned char pos : 7; // 2^7 = 128-1 = [0,127]
  unsigned char molodChastyna : 4;
  bool parity : 1;
};

short getParity(unsigned int n) {
  bool parity = 1;
  // cout << "Number: " << n << endl;
  // cout << "bitset: " << bitset<16>(n) << endl;
  for (int i = 1; i < 16; i++) {
    if (((n >> i) & 1) == // move all bits one time right and get last bit
        1) { // 1 - 0001. 1111 & 1 =  0001; 1110 & 1 = 0000. Get last bit.
      parity = !parity; // if it '1' then !parity.
    }
  }
  return parity;
}

void task1() {
  // Обчислення виразів з використанням побітових операцій
  // Calculation of expressions using bitwise operations
  cout << " Calculation of expressions using bitwise operations\n";
  // 8 Variant 37*b+(d*31+12*a)/2048 - 65*c + d*14
  //  a * 32 == a * 2^5 == a << 5
  //  a / 32 == a / 2^5 == a >> 5
  // 37*b = 5b + 32b = b + 4b + 32b = b + b*2^2 + b*2^5 = b + b << 2 + b << 5
  // and so on...
  cout << "Input a, b, c, d: ";
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  cout << "Result using default operations: "
       << ((37 * b) + (d * 31 + 12 * a) / 2048) - 65 * c + d * 14 << endl;
  cout << "Result using bitwise operations: "
       << ((b + (b << 2) + (b << 5)) +
           (((d << 5) - d + (a << 4) - (a << 2)) >> 11)) -
              ((c << 6) + c) + (d << 4) - (d << 1)
       << endl;
}

void task2Encrypt() {
  // Шифрування даних з використання побітових операцій
  // Data encryption using bitwise operations
  cout << " Data encryption using bitwise operations\n";
  char input[128];
  short symCounter = 0;
  cout << "1. Input from file input.txt" << endl;
  cout << "2. Input from stdin" << endl;
  cout << "Choose: ";
  char choose;
  cin >> choose;
  switch (choose) {
  case '1': {
    ifstream inputFile("/home/ob3r0n/cpp/input.txt", ios::in);
    if (inputFile.is_open()) {
      while (!inputFile.eof()) {
        char symbol;
        inputFile.get(symbol);
        if (!inputFile)
          break;
        input[symCounter++] = symbol;
      }
      break;
    } else {
      cout << "Can't open file" << endl;
    }
  }
  case '2': {
    cout << "Input text: ";
    string inp;
    cin >> inp;
    symCounter = inp.length();
    strcpy(input, inp.c_str());
  } break;
  }

  for (int i = symCounter; i < 128; i++) {
    input[i] = ' ';
  }

  unsigned short *result = new unsigned short[128];
  for (int i = 0; i < 128; i++) {
    result[i] = 0;
    // s - 0000 0000 0111 0011

    // cout << "result <<4:  " << bitset<16>(result[0]) << endl;
    result[i] |= input[i] >> 4; // write ASCII first 4 bits
    // cout << "Writed first 4 bit of ASCII: " << bitset<16>(result[i]) << endl;
    //  cout << "result &i " << bitset<16>(result[0]) << endl;
    result[i] <<=
        7; // moving writed 4 bits 7 times left. Free space for pos<=127
    // cout << "result <<7 " << bitset<16>(result[i]) << endl;
    result[i] |= i; // write to last 7 bits number i, this is position
    // cout << "result + pos:  " << bitset<16>(result[i]) << endl;
    result[i] <<= 4; // moving writed 7 bits 4 times left. Free space for ASCII
                     // last 4 bits
    result[i] |=
        input[i] & 0x0F; // 1111 1111 = 0000 1111. Leaving only last 4 bits.
    // cout << "result |= 0111:  " << bitset<16>(result[0]) << endl;
    result[i] <<= 1; // free space for one parity bit.
    // cout << "result <1:  " << bitset<16>(result[0]) << endl;
    short parity;
    parity = getParity(result[i]);
    result[i] |= parity; // write 1 bit of parity
    cout << "Encrypted " << (char)input[i]
         << " successfully. Result is: " << bitset<16>(result[i]) << endl;
  }
  ofstream outputb("/home/ob3r0n/Desktop/outb.dat",
                   ios::out | ios::binary); // create binary file for output
  outputb.write(
      (char *)result,
      128 * sizeof(unsigned short)); // write whole result array to binary file
  outputb.close();                   // close bin file
}

void task2Decrypt() {
  // Decrypt data from binary file, print it and write to another file
  ifstream inputBinary;
  inputBinary.open("/home/ob3r0n/Desktop/outb.dat", ios::in | ios::binary);
  unsigned short fromBinary[128];
  inputBinary.read((char *)&fromBinary, 128 * sizeof(unsigned short));
  char result[128];
  for (int i = 0; i < 128; i++) {
    // cout << "decoding " << bitset<16>(fromBinary[i]) << endl;
    short parity = (fromBinary[i]) & 1;
    // cout << "decoded parity: " << parity << endl;
    unsigned short lowerChast =
        (fromBinary[i] >> 1) & 0b1111; // starsha - zliva 0111 for 's'
    // cout << bitset<16>(lowerChast) << endl;

    unsigned short position = (fromBinary[i] >> 5) & 0b1111111;
    // cout << "pos: " << position << endl;
    unsigned short starshaChast = (fromBinary[i] >> 12) & 0b1111;
    // cout << bitset<16>(starshaChast) << endl;
    char symbol = starshaChast << 4 | lowerChast;
    // cout << symbol << endl;
    //	cout << bitset<16>(encr[0]) << endl;
    //	cout << bitset<16>(encr[0] >> 4 & 1) << endl;
    short parCheck = getParity(fromBinary[i]);
    cout << "Parity: " << parity << ", parCheck: " << parCheck << endl;
    if (parity == parCheck && position == i) {
      cout << "Decoding " << symbol
           << " succesfull. Position and parity bit match." << endl;
    } else {
      cout << "Error!" << endl;
      cout << "symbol: " << symbol << endl;
    }

    result[i] = symbol;
  }
  cout << endl << endl;
  ofstream out("/home/ob3r0n/Desktop/output.txt", ios::out | ios::app);
  cout << "Printing decrypted array: ";
  for (int i = 0; i < 128; i++) {
    cout << result[i];
  }
  out.write(result, 128);
  cout << endl;
}

void task3Encrypt() {
  // Шифрування даних з використання побітових операцій
  // Data encryption using bitwise operations
  cout << " Data encryption using bitwise operations\n";
  char input[128];
  short symCounter = 0;
  cout << "1. Input from file input.txt" << endl;
  cout << "2. Input from stdin" << endl;
  cout << "Choose: ";
  char choose;
  cin >> choose;
  switch (choose) {
  case '1': {
    ifstream inputFile("/home/ob3r0n/cpp/input.txt", ios::in);
    if (inputFile.is_open()) {
      while (!inputFile.eof()) {
        char symbol;
        inputFile.get(symbol);
        if (!inputFile)
          break;
        input[symCounter++] = symbol;
      }
      break;
    } else {
      cout << "Can't open file" << endl;
    }
  }
  case '2': {
    cout << "Input text: ";
    string inp;
    cin >> inp;
    symCounter = inp.length();
    strcpy(input, inp.c_str());
  } break;
  }

  for (int i = symCounter; i < 128; i++) {
    input[i] = ' ';
  }

  charBit *result = new charBit[128];
  for (int i = 0; i < 128; i++) {
    // s - 0000 0000 0111 0011
    result[i].starshaChastyna = input[i] >> 4; // write ASCII first 4 bits
    result[i].pos = i;                         // write number i, it is position
    result[i].molodChastyna =
        (input[i] &
         0x0F); // 1111 1111 & 0x0F = 0000 1111. Leaving only last 4 bits.
    short parity;
    unsigned short currentRes = 0;
    currentRes |= result[i].starshaChastyna;
    currentRes <<= 7;
    currentRes |= result[i].pos;
    currentRes <<= 4;
    currentRes |= result[i].molodChastyna;
    parity = getParity(currentRes);
    currentRes <<= 1;
    currentRes |= parity;
    result[i].parity = parity; // write 1 bit of parity
    cout << "Encrypted " << (char)input[i]
         << " successfully. Result is: " << bitset<16>(currentRes) << endl;
    cout << "Symbol: " << bitset<8>(input[i]) << endl;
    cout << "Starha: " << bitset<8>(result[i].starshaChastyna) << endl;
    cout << "Pos: " << bitset<8>(result[i].pos) << endl;
    cout << "Molod: " << bitset<8>(result[i].molodChastyna) << endl;
    cout << "Parity: " << bitset<2>(result[i].parity) << endl;
  }
  ofstream outputb("/home/ob3r0n/Desktop/outb.dat",
                   ios::out | ios::binary); // create binary file for output
  outputb.write((char *)result,
                128 *
                    sizeof(charBit)); // write wholl result array to binary file
  outputb.close();                    // close bin file
}

void task3Decrypt() {
  // Decrypt data from binary file, print it and write to another file
  ifstream inputBinary;
  inputBinary.open("/home/ob3r0n/Desktop/outb.dat", ios::in | ios::binary);
  charBit fromBinary[128];
  inputBinary.read((char *)&fromBinary, 128 * sizeof(charBit));
  char result[128];
  for (int i = 0; i < 128; i++) {
    short parity = fromBinary[i].parity;
    short starshaChast = fromBinary[i].starshaChastyna;
    short position = fromBinary[i].pos;
    short lowerChast = fromBinary[i].molodChastyna;
    char symbol = starshaChast << 4 | lowerChast;
    unsigned short currentRes = 0;
    currentRes |= starshaChast;
    currentRes <<= 7;
    currentRes |= position;
    currentRes <<= 4;
    currentRes |= lowerChast;
    currentRes <<= 1;
    // currentRes |= parity;
    short parCheck = getParity(currentRes);
    cout << "Starha: " << bitset<8>(starshaChast) << endl;
    cout << "Pos: " << bitset<8>(position) << endl;
    cout << "Molod: " << bitset<8>(lowerChast) << endl;
    cout << "Parity: " << bitset<2>(parity) << endl;
    //	cout << "Parity: " << parity << ", parCheck: " << parCheck << endl;
    if (parity == parCheck && position == i) {
      cout << "Decoding " << symbol
           << " succesfull. Position and parity bit match." << endl;
    } else {
      cout << "Error!" << endl;
      cout << "symbol: " << symbol << endl;
    }

    result[i] = symbol;
  }
  cout << endl << endl;
  ofstream out("/home/ob3r0n/Desktop/output.txt", ios::out | ios::app);
  cout << "Printing decrypted array: ";
  for (int i = 0; i < 128; i++) {
    cout << result[i];
  }
  out.write(result, 128);
  cout << endl;
}

void task4() { // Задача із використання побітових операцій
  // The problem of using bitwise operations
  // Calculate (20 * y - x * 120) / 32 + (x + 32 * y) / 128 + (x + y) % 16
  // Using bitwise operators
  // Calculation will be same as task 1.
  // x % 16 == x & 16-1 == x & 15.
  cout << " Calculate problem using bitwise operations\n";
  int x, y;
  cout << "Input x, y: ";
  cin >> x >> y;
  double resDefault =
      ((20 * y - x * 120) >> 5) + ((x + 32 * y) >> 7) + ((x + y) % 16);
  double resBit = (((y << 2) + (y << 4) - ((x << 7) - (x << 3))) >> 5) +
                  ((x + (y << 5)) >> 7) + ((x + y) & 15);
  cout << "Result using default operations: " << resDefault << endl;
  cout << "Result using bitwise operations: " << resBit << endl;
}

int main() {
  cout << "1. Task 1" << endl;
  cout << "2. Task 2" << endl;
  cout << "3. Task 3" << endl;
  cout << "4. Task 4" << endl;
  cout << "Choose: ";
  int choose = 0;
  do {
    cin >> choose;
  } while (choose < 0 && choose > 4);
  switch (choose) {
  case 1: {
    task1();
    break;
  }
  case 2: {
    cout << "Encryption" << endl;
    task2Encrypt();
    cout << "Decryption" << endl;
    task2Decrypt();
    break;
  }
  case 3: {
    cout << "Encryption" << endl;
    task3Encrypt();
    cout << "Decryption" << endl;
    task3Decrypt();
    break;
  }
  case 4: {
    task4();
    break;
  }
  }

  return 0;
}
