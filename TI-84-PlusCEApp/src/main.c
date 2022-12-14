#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <stdio.h>
#include <debug.h>
#include <ti/tokens.h>
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

char *AIsOne(int b, int c, char varChar[])
{
    for (int i = -200; i < 200; i++)
    {
        for (int k = -200; k < 200; k++)
        {
            if (i + k == b && i * k == c)
            {
                char *sign1 = "+";
                char *sign2 = "+";
                if (i < 0) sign1 = "";
                if (k < 0) sign2 = "";
                char *out1 = malloc(14);
                char *out2 = malloc(14);
                snprintf(out1,14,"(%s%s%d)",varChar,sign1,i);
                snprintf(out2,14,"(%s%s%d)",varChar,sign2,k);
                char *toReturn;
                if (strcmp(out1,out2) == 0)
                {
                    toReturn = strcat(out1,"^2");
                }else toReturn = strcat(out1,out2);
                return toReturn;
            }
        }
    }
    return "Cannot Factor";
}

int GCF(int a, int b)
{
    int gcf = 1;
    a = abs(a);
    b = abs(b);
    for(int i=1; i <= a && i <= b; i++)
    {
        // Checks if i is factor of both integers
        if(a%i==0 && b%i==0)
        gcf = i;
    }
    return gcf;
}
int GCF3(int a, int b, int c)
{
    int gcf = 1;
    a = abs(a);
    b = abs(b);
    c = abs(c);
    for(int i = 2; i <= a && i <= b && i <= c; i++)
    {
        if(a%i==0&&b%i==0&&c%i==0)
        {
            gcf = i;
        }
    }
    return gcf;
}
char *AGOne(int a, int b, int c, char varChar[])
{
    /*
    int gcf = 0;
    if(GCF3(a,b,c) != 0)
    {
        gcf = GCF3(a,b,c);
        a /= GCF3(a,b,c);
        b /= GCF3(a,b,c);
        c /= GCF3(a,b,c);
    }
    */

    //printf("a:%d\nb:%d\nc:%d\n",a,b,c);
    for(int i = -250; i < 250; i++)
    {
        for(int k = -250; k < 250; k++)
        {
            if(i + k == b && i * k == c * a)
            {
                //printf("checkpoint1\n");
                int group1[2] = {a,i};
                int group2[2] = {k,c};
                //printf("checkpoint2\ng11: %d, g12: %d\n",group1[0],group1[1]);
                //printf("g11: %d, g12: %d\n",group1[0],group1[1]);
                int g1gcf = GCF(group1[0], group1[1]);
                //printf("checkpoint3\n");
                int g2gcf = GCF(group2[0], group2[1]);
                char *sign1 = "+";
                char *sign2 = "+";
                if(i/g1gcf < 0) sign1 = "";
                if((c/g2gcf) < 0) sign2 = "";
                //printf("checkpoint4\n");
                char *out1 = malloc(20);
                char *out2 = malloc(20);
                //printf("checkpoint5\n");
                snprintf(out1,20,"(%d%s%s%d)",(a/g1gcf),varChar,sign1,(i/g1gcf));
                snprintf(out2,20,"(%d%s%s%d)",(k/g2gcf),varChar,sign2,(c/g2gcf));
                //printf("checkpoint6\n");
                //printf("Out1: %s\nOut2: %s\n",out1,out2);
                dbg_printf("out1: %s\nout2: %s\n",out1,out2);
                if(strcmp(out1,out2) != 0)
                {
                    //printf("checkpoint7\n");
                    g2gcf *= -1;
                    if(c/g2gcf < 0) sign2 = "";
                    snprintf(out2,20,"(%d%s%s%d)",(k/g2gcf),varChar,sign2,(c/g2gcf));
                    dbg_printf("out1: %s\nout2: %s\n",out1,out2);
                    //printf("checkpoint9\n");
                    
                }
                if(strcmp(out1,out2) != 0) return "Cannot Factor";
                sign2 = "+";
                if(g2gcf < 0) sign2 = "";
                snprintf(out2,20,"(%d%s%s%d)",g1gcf,varChar,sign2,g2gcf);
                char *toReplace = strcat("1",varChar);
                out1 = str_replace(out1, toReplace,varChar);
                out2 = str_replace(out2, toReplace,varChar);
                if(strcmp(out1,out2) == 0) out2 = "^2";
                //if(gcf != 0) snprintf(out1,20,"%d%s",gcf,out1);
                return strcat(out1,out2);
            }
        }
    }
    return "Cannot Factor";
}

int main()
{
    os_ClrHome();
    os_SetCursorPos(0,0);
    char in0[5];
    char in1[5];
    char in2[5];
    char in3[5];
    os_GetStringInput("Variable: ", in0,5);
    os_SetCursorPos(1,0);
    os_GetStringInput("A: ", in1,5);
    os_SetCursorPos(2,0);
    os_GetStringInput("B: ", in2,5);
    os_SetCursorPos(3,0);
    os_GetStringInput("C: ", in3,5);
    os_SetCursorPos(4,0);
    dbg_printf("1A: %s, B: %s, C: %s\n",in1,in2,in3);
    //dbg_printf("\"\\x%02X\"\n", in2[0]);
    char *iin1 = str_replace(in1,"\x1A", "-");
    char *iin2 = str_replace(in2,"\x1A", "-");
    char *iin3 = str_replace(in3,"\x1A", "-");
    int a = atoi(iin1);
    int b = atoi(iin2);
    int c = atoi(iin3);

    dbg_printf("A: %d, B: %d, C: %d\n",a,b,c);
    if(a == 1)
    {
        char *out = AIsOne(b,c,in0);
        os_PutStrLine(out);
        if(strcmp(out,"Cannot Factor") != 0) free(out);
    }
    else if(a == -1)
    {
        int gcf = -1;
        a *= -1;
        b *= -1;
        c *= -1;
        char out1[60];
        char *out = AIsOne(b,c,in0);
        if(strcmp(out,"Cannot Factor") != 0)
        {
            sprintf(out1,"%d%s",gcf,out);
            os_PutStrLine(out1);
        }
        else os_PutStrLine(out);
        free(out);
    }
    else
    {
        if(b == 0 && a < 0)
        {
            int gcf = -1;
            a *= -1;
            c *= -1;
            char *out = AGOne(a,b,c,in0);
            char out1[60];
            if(strcmp(out,"Cannot Factor") != 0)
            {
                sprintf(out1, "%d%s",gcf,out);
                os_PutStrLine(out1);
            }
            else os_PutStrLine(out);
            free(out);
        }
        else
        {
            int gcf = GCF3(a,b,c);
            dbg_printf("GCF: %d\n",gcf);
            dbg_printf("A: %d, B: %d, C: %d\n",a,b,c);
            if(gcf > 1)
            {
                a /= gcf;
                b /= gcf;
                c /= gcf;
                if(a == 1)
                {
                    char *out = AIsOne(b,c,in0);
                    char out1[60];
                    dbg_printf("%s\n",out);
                    if(gcf != 1) sprintf(out1,"%d%s",gcf,out);
                    dbg_printf("%s\n",out1);
                    os_PutStrLine(out1);
                    free(out);
                }
                else if(a == -1)
                {
                    gcf *= -1;
                    b *= -1;
                    c *= -1;
                    char *out = AIsOne(b,c,in0);
                    char out1[60];
                    if(gcf != 1) sprintf(out1,"%d%s",gcf,out);
                    os_PutStrLine(out1);
                    free(out);
                }
                else
                {
                    char *out = AGOne(a,b,c,in0);
                    char out1[60];
                    dbg_printf("%s\n",out);
                    if(gcf != 1) sprintf(out1, "%d%s",gcf,out);
                    dbg_printf("%s\n",out1);
                    os_PutStrLine(out1);
                    free(out);
                }
            }
            else
            {
                char *out = AGOne(a,b,c,in0);
                os_PutStrLine(out);
                free(out);
            } 
        }
        
        
    }
    os_SetCursorPos(5,0);
    os_PutStrLine("Press Any Key To Exit");
    while(!os_GetCSC());
    return 0; 
}
