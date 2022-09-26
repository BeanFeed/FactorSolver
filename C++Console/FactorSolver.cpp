// FactorSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <format>
#include <cmath>

using namespace std;

bool IsEven(int num) { return num % 2 == 0; }
bool NoDeci(float num) { return std::fmod(num, 1) == 0; }
int GCF(int a, int b)
{
    int gcf = -1;
    for (int i = 1; i < 50; i++)
    {
        if (NoDeci((float)a / (float)i) && NoDeci((float)b / (float)i))
        {
            gcf = i;
        }
    }
    return gcf;
}
string AIsOne(int b, int c, char varChar)
{
    for (int i = -1000; i < 1000; i++)
    {
        for (int k = -1000; k < 1000; k++)
        {
            if (i + k == b && i * k == c)
            {
                string sign1 = "+";
                string sign2 = "+";
                if (i < 0) sign1 = "";
                if (k < 0) sign2 = "";
                
                string out1 = format("({}{}{})", varChar, sign1, i);
                string out2 = format("({}{}{})",varChar,sign2,k);
                if (out1 == out2) out2 = "^2";
                return out1 + out2;
            }
        }
    }
    return "No Solution";
}

void replaceAll(string& str, const string& from, const string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

string AGOne(int a, int b, int c, char varChar)
{
    int c1 = c;
    c *= a;
    for (int i = -1000; i < 1000; i++)
    {
        for (int k = -1000; k < 1000; k++)
        {
            if (i + k == b && i * k == c)
            {
                int group1[2] = {a, i};
                int group2[2] = {k, c1};
                int g1gcf = GCF(group1[0], group1[1]);
                //Console.WriteLine("g1GCF: " + g1gcf.ToString());
                int g2gcf = GCF(group2[0], group2[1]);
                string sign1 = "+";
                string sign2 = "+";
                if (i / g1gcf < 0) sign1 = "";
                if (c1 / g2gcf < 0) sign2 = "";
                string par1 = format("({}{}{}{})", (a / g1gcf), varChar, sign1, (i / g1gcf));
                string par2 = format("({}{}{}{})", (k / g2gcf), varChar, sign2, (c1 / g2gcf));
                //Console.WriteLine("1: " + par1);
                //Console.WriteLine("2: " + par2);
                if (par1 != par2)
                {
                    par2 = format("({}{}{}{})", (k / (-1 * g2gcf)), varChar, sign1, (c1 / (-1 * g2gcf)));
                    //Console.WriteLine("3: " + par2);
                    if (par1 != par2) return "No Solution";
                    g2gcf *= -1;
                }
                //sign2 = "+";
                if (g2gcf < 0) sign2 = "";
                par2 = format("({}{}{}{})", g1gcf, varChar, sign2, g2gcf);
                replaceAll(par1, "-1x", "-x");
                replaceAll(par1, "1x", "x");
                replaceAll(par2, "-1x", "-x");
                replaceAll(par2,"1x", "x");
                if (par1 == par2) par2 = "^2";
                return par1 + par2;

            }
        }

    }
    return "No Solution";
}
int main()
{
    string a = "";
    string b = "";
    string c = "";
    cout << "A: ";
    cin >> a;
    cout << "B: ";
    cin >> b;
    cout << "C: ";
    cin >> c;
    if (a == "1")
    {
        cout << AIsOne(stoi(b), stoi(c), 'x') << "\n";
    }
    else
    {
        cout << AGOne(stoi(a), stoi(b), stoi(c), 'x') << "\n";
    }
    return 0;
}