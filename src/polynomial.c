#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"

void swap_char(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

int is_space_between_number(char *s)
{
    int i = 0;
    int j = 0;
    int flag = 0;
    while (s[j] != '\0')
    {
        if (s[j] != ' ')
        {
            // checking if space is between two number
            if (j - i > 1 && isdigit(s[i]) && isdigit(s[j]))
                flag = 1;
            i = j;
        }

        j++;
    }
    return flag;
}

void remove_whitespace(char *s)
{
    int i = 0;
    int j = 0;
    while (s[j] != '\0')
    {
        if (s[j] != ' ')
        {
            s[i] = s[j];
            i++;
        }
        j++;
    }
    s[i] = '\0';
}

poly s_to_poly(char *s)
{
    if (is_space_between_number(s))
    {
        printf("Error: Space between number is not allowed.");
        exit(1);
    }
    remove_whitespace(s);
    int i=0;
    while(s[i]!='\0')
    {
        int sign = 1;
        double coeff=1;
        unsigned int power=0;
        int power_set_flag=0, coeff_set_flag=0;
        if(s[i]=='+' | s[i]=='-')
        {
            if(s[i]=='-')
                sign = -1;
            i++;
        }
        if(s[i]=='x')
        {
            power = 1;
            i++;
            if(s[i]=='^')
            {
                i++;
                scanf(s+i,"%d",&power);
                while(isdigit(s[i]))
                    i++;
                power_set_flag = 1;
            }

            if(s[i]=='*')
            {
                i++;
                scanf(s+i,"%f",&coeff);
                int decimal_flag=0;
                while((s[i]>='0' && s[i]<='9') | s[i]=='.')
                {
                    if(s[i]=='.' && decimal_flag==0)
                    {
                        decimal_flag=1;
                    }
                    else if(s[i]=='.')
                    {
                        break;
                    }
                }
                coeff_set_flag = 1;
            }
        }
        printf("%lf, %ul\n", coeff, power);
    }
}