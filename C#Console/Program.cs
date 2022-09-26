using System;

namespace FactorSolver;

class Program
{
    private static char[] nums = new char[] {'0','1','2','3','4','5','6','7','8','9'};

    private static bool NoDeci(float a) { return a % 1 == 0; }
    private static int GCF(int a, int b)
    {
        int gcf = -1;
        for(int i = 1; i < 50; i ++)
        {
            if(NoDeci((float)a / (float)i) && NoDeci((float)b / (float)i))
            {
                gcf = i;
            }
        }
        return gcf;
    }
    private static string AIsOne(int b, int c, char? varChar)
    {
        if(varChar is null) varChar = 'x';

        for(int i = -1000; i < 1000; i++)
        {
            for(int k = -1000; k < 1000; k++)
            {
                if(i + k == b && i * k == c)
                {
                    string sign1 = "+";
                    string sign2 = "+";
                    if(i < 0) sign1 = "";
                    if(k < 0) sign2 = "";
                    string out1 = "(" + varChar + sign1 + i.ToString() + ")";
                    string out2 = "(" + varChar + sign2 + k.ToString() + ")";
                    if(out1 == out2) out2 = "^2";
                    return out1 + out2;
                }
            }
        }
        return "No Solution";
    }
    private static string AGOne(int a, int b, int c, char? varChar)
    {
        if(varChar is null) varChar = 'x';
        int c1 = c;
        c *= a;
        for(int i = -1000; i < 1000; i++)
        {
            for(int k = -1000; k < 1000; k++)
            {
                if(i + k == b && i * k == c)
                {
                    int[] group1 = new int[]{a,i};
                    int[] group2 = new int[]{k,c1};
                    int g1gcf = GCF(group1[0], group1[1]);
                    //Console.WriteLine("g1GCF: " + g1gcf.ToString());
                    int g2gcf = GCF(group2[0], group2[1]);
                    string sign1 = "+";
                    string sign2 = "+";
                    if(i / g1gcf < 0) sign1 = "";
                    if(c1 / g2gcf < 0) sign2 = "";
                    string par1 = '(' + (a / g1gcf).ToString() + varChar + sign1 + (i / g1gcf).ToString() + ')';
                    string par2 = '(' + (k / g2gcf).ToString() + varChar + sign2 + (c1 / g2gcf).ToString() + ')';
                    //Console.WriteLine("1: " + par1);
                    //Console.WriteLine("2: " + par2);
                    if(par1 != par2)
                    {
                        par2 = '(' + (k / (-1 * g2gcf)).ToString() + varChar + sign2 + (c1 / (-1 * g2gcf)).ToString() + ')';
                        //Console.WriteLine("3: " + par2);
                        if(par1 != par2) return "No Solution";
                        g2gcf *= -1;
                    }
                    sign2 = "+";
                    if(g2gcf < 0) sign2 = "";
                    par2 = '(' + g1gcf.ToString() + varChar + sign2 + g2gcf + ')';
                    par1 = par1.Replace("-1x", "-x");
                    par1 = par1.Replace("1x", "x");
                    par2 = par2.Replace("-1x", "-x");
                    par2 = par2.Replace("1x", "x");
                    if(par1 == par2) par2 = "^2";
                    return par1 + par2;

                }
            }
            
        }
        return "No Solution";
    }
    static void Main()
    {
        int a = 0;
        int b = 0;
        int c = 0;
        bool validIn = true;
        string in1;
        string in2;
        string in3;
        
        do
        {
            Console.Clear();
            validIn = true;
            Console.Write("A: ");
            in1 = Console.ReadLine();
            Console.Write("B: ");
            in2 = Console.ReadLine();
            Console.Write("C: ");
            in3 = Console.ReadLine();
            try
            {
                a = int.Parse(in1);
            }
            catch
            {
                Console.WriteLine("A Is Not A Number");
                validIn = false;
            }
            try
            {
                b = int.Parse(in2);
            }
            catch
            {
                Console.WriteLine("B Is Not A Number");
            }
            try
            {
                c = int.Parse(in3);
            }
            catch
            {
                Console.WriteLine("C Is Not A Number");
            }
        }
        while(!validIn);
        string output = "";
        //if(a == 1) output = AIsOne(b,c, null);
        //else output = AGOne(a,b,c,null);
        output = AGOne(a,b,c,null);
        Console.WriteLine(output);
    }
}