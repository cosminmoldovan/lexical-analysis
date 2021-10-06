#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
using namespace std;

int isKeyword(char buffer[])
{
    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union",
                             "unsigned", "void", "volatile", "while"};
    int i, flag = 0;

    for (i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }

    return flag;
}
void lex(string fis)
{
    char ch, buffer[15], operators[] = "+-*/%=";
    ifstream fin(fis);
    int i, j = 0;
    if (!fin.is_open())
    {
        cout << "eroare la deschiderea fisierului\n";
        exit(0);
    }

    while (!fin.eof())
    {
        ch = fin.get();

        for (i = 0; i < 6; ++i)
        {
            if (ch == operators[i])
                cout << ch << " este operator\n";
        }

        if (isalnum(ch))
        {
            buffer[j++] = ch;
        }
        else if ((ch == ' ' || ch == '\n') && (j != 0))
        {
            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer) == 1)
                cout << buffer << " este cuvant cheie\n";
            else
                cout << buffer << " este identificator\n";
        }
    }
    fin.close();
}
void printCode(string fis)
{
    char ch;
    ifstream fin(fis);
    int i, j = 0;
    if (!fin.is_open())
    {
        cout << "eroare la deschiderea fisierului\n";
        exit(0);
    }

    while (!fin.eof())
    {
        ch = fin.get();
        cout << ch;
    }
    fin.close();
}
void insertCode()
{
    ofstream fout("tastatura.txt");
    if (fout.is_open())
    {
        char ch;
        cin.get(ch);
        while (ch != '#')
        {
            cin.get(ch);
            fout << ch;
        }

        fout.close();
    }
    else
        cout << "eroare la deschiderea fisierului\n";
    lex("tastatura.txt");
}
int main()
{
    cout << "  ANALIZA LEXICALA\n";
    int op;
    do
    {
        cout << "\n";
        cout << "===========================\n";
        cout << "ALEGE OPTIUNEA DORITA\n";
        cout << "===========================\n";
        cout << "1: analizeaza codul din fisier\n";
        cout << "2: afiseaza codul sursa din fisier\n";
        cout << "3: analizeaza codul de la tastatura \n";
        cout << "0: iesire\n";
        cout << "===========================\n";
        cin >> op;
        switch (op)
        {
        case 1:
            lex("program.cpp");
            break;
        case 2:
            printCode("program.cpp");
            break;
        case 3:
            insertCode();
            break;
        case 0:
            exit(0);
            break;
        default:
            cout << "tasta incorecta incearca dinou\n";
            break;
        }

    } while (op != 0);
    return 0;
}