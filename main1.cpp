#include <iostream>

using namespace std;

union FloatBits
{
    float value;
    unsigned int bits;
};

union DoubleBits
{
    double value;
    unsigned long long bits;
};


//Задание 2
void printBits(int num)
{
    unsigned int bits = num;

    const int order = sizeof(bits) * 8;
    const unsigned int mask = 1u << (order - 1);

    for (int i = 0; i < order; i++)
    {
        char bit = (bits & (mask >> i)) ? '1' : '0';
        if (i == 1)
        {
            cout << " | ";
        }
        else if (i > 1 && i % 4 == 0)
        {
            cout << " ";
        }
        cout << bit;
    }
    cout << endl;
}


//Задание 3
void printBits(float num)
{
    FloatBits u;
    u.value = num;

    const int order = sizeof(u.bits) * 8;
    const unsigned int mask = 1u << (order - 1);

    for (int i = 0; i < order; i++)
    {
        char bit = (u.bits & (mask >> i)) ? '1' : '0';
        if (i == 1 || i == 9)
        {
            cout << " | ";
        }
        cout << bit;
    }
    cout << endl;
}


//задание 4
void printBits(double num)
{
    DoubleBits u;
    u.value = num;

    const int order = sizeof(u.bits) * 8;
    const unsigned long long mask = 1ull << (order - 1);

    for (int i = 0; i < order; i++)
    {
        char bit = (u.bits & (mask >> i)) ? '1' : '0';
        if (i == 1 || i == 12)
        {
            cout << " | ";
        }
        cout << bit;
    }
    cout << endl;
}


//Задание 5
int changeBit(int num, int k, int op)
{
    unsigned int bits = num;
    unsigned int mask = 1u << k;

    if (op == 1)
    {
        bits |= mask;
    }
    else if (op == 0)
    {
        bits &= ~mask;
    }
    else if (op == -1)
    {
        bits ^= mask;
    }
    return bits;
}

float changeBit(float num, int k, int op)
{
    FloatBits u;
    u.value = num;
    unsigned int mask = 1u << k;

    if (op == 1)
    {
        u.bits |= mask;
    }
    else if (op == 0)
    {
        u.bits &= ~mask;
    }
    else if (op == -1)
    {
        u.bits ^= mask;
    }
    return u.value;
}

double changeBit(double num, int k, int op)
{
    DoubleBits u;
    u.value = num;
    unsigned long long mask = 1ull << k;

    if (op == 1)
    {
        u.bits |= mask;
    }
    else if (op == 0)
    {
        u.bits &= ~mask;
    }
    else if (op == -1)
    {
        u.bits ^= mask;
    }
    return u.value;
}



//Инверсия знака 
int invertSign(int num)
{
    return ~num + 1;
}

float invertSign(float num)
{
    return changeBit(num, sizeof(num) * 8 - 1, -1);
}

double invertSign(double num)
{
    return changeBit(num, sizeof(num) * 8 - 1, -1);
}


//Задание 6 
int main()
{
    setlocale(LC_ALL, ".UTF-8");
//Задание 1
    cout << "bool: " << sizeof(bool) << endl
         << "char: " << sizeof(char) << endl
         << "short int: " << sizeof(short int) << endl
         << "int: " << sizeof(int) << endl
         << "long int: " << sizeof(long int) << endl
         << "long long: " << sizeof(long long) << endl
         << "float: " << sizeof(float) << endl
         << "double: " << sizeof(double) << endl
         << "long double: " << sizeof(long double) << endl;

    cout << "\nВведите положительное int:\n";
    int num;
    cin >> num;
    printBits(num);
    cout << "\nВведите отрицательное int:\n";
    cin >> num;
    printBits(num);
    cout << "\nВведите 0:\n";
    cin >> num;
    printBits(num);

    cout << "\nВведите положительный float\n";
    float numf;
    cin >> numf;
    printBits(numf);
    cout << "\nВведите отрицательный float\n";
    cin >> numf;
    printBits(numf);
    cout << "\nВведите 0 float\n";
    cin >> numf;
    printBits(numf);
    cout << "\nВведите деморализированное float\n";
    cin >> numf;
    printBits(numf);
    cout << "+inf: ";
    printBits(1.0f / 0.0f);
    cout << "-inf: ";
    printBits(-1.0f / 0.0f);
    cout << "NaN: ";
    printBits(0.0f / 0.0f);

    cout << "\nВведите положительный double\n";
    double numd;
    cin >> numd;
    printBits(numd);
    cout << "\nВведите отрицательный double\n";
    cin >> numd;
    printBits(numd);

    cout << "\nВведите число, номер бита и номер операции для int\n";
    cout << "Операция 1 -- установить бит в 1\n";
    cout << "Операция 0 -- установить бит в 0\n";
    cout << "Операция -1 -- инвертировать бит\n";
    int k, op;
    cin >> num >> k >> op;
    cout << "Было: ";
    printBits(num);
    num = changeBit(num, k, op);
    cout << "Стало: ";
    cout << num << endl;
    printBits(num);

    cout << "\nВведите число, номер бита и номер операции для float\n";
    cout << "Операция 1 -- установить бит в 1\n";
    cout << "Операция 0 -- установить бит в 0\n";
    cout << "Операция -1 -- инвертировать бит\n";
    cin >> numf >> k >> op;
    cout << "Было: ";
    printBits(numf);
    numf = changeBit(numf, k, op);
    cout << "Стало: ";
    cout << numf << endl;
    printBits(numf);

    cout << "\nВведите число, номер бита и номер операции для double\n";
    cout << "Операция 1 -- установить бит в 1\n";
    cout << "Операция 0 -- установить бит в 0\n";
    cout << "Операция -1 -- инвертировать бит\n";
    cin >> numd >> k >> op;
    cout << "Было: ";
    printBits(numd);
    numd = changeBit(numd, k, op);
    cout << "Стало: ";
    cout << numd << endl;
    printBits(numd);

    cout << "\nВведите int и оно поменяет знак\n";
    cin >> num;
    cout << "invertSign(num) = " << invertSign(num) << endl;
    cout << "Было: ";
    printBits(num);
    cout << "Стало: ";
    printBits(invertSign(num));

    cout << "\nВведите float и оно поменяет знак\n";
    cin >> numf;
    cout << "invertSign(numf) = " << invertSign(numf) << endl;
    cout << "Было: ";
    printBits(numf);
    cout << "Стало: ";
    printBits(invertSign(numf));

    cout << "\nВведите double и оно поменяет знак\n";
    cin >> numd;
    cout << "invertSign(numd) = " << invertSign(numd) << endl;
    cout << "Было: ";
    printBits(numd);
    cout << "Стало: ";
    printBits(invertSign(numd));

    return 0;
}
