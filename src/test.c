// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void swap_char(char *a , char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

int is_space_between_number(char *s)
{
    int i=0;
    int j=0;
    int flag = 0;
    while(s[j]!='\0')
    {
        if(s[j]!=' '){
            // checking if space is between two number
            if(j-i>1 && isdigit(s[i]) && isdigit(s[j]))
                flag = 1;
            i=j;
        }
            
        j++;
        
    }
    return flag;
}

int remove_whitespace(char *s){
    int i=0;
    int j=0;
    while(s[j]!='\0')
    {
        if(s[j]!=' ')
        {
            s[i] = s[j];
            i++;
        }
        j++;
    }
    s[i]='\0';
    return 0;
}



void s_to_poly(char *s)
{
    if (is_space_between_number(s))
    {
        printf("Error: Space between number is not allowed.");
        exit(1);
    }
    remove_whitespace(s);
    int i=0;
    printf("%s\n",s);
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
                printf("came1");
                sscanf(s+i,"%u",&power);
                printf("came2");
                while(isdigit(s[i]) && s[i]!='\0')
                    i++;
                power_set_flag = 1;
                
            }

            if(s[i]=='*')
            {
                i++;
                sscanf(s+i,"%lf",&coeff);
                int decimal_flag=0;
                while((s[i]>='0' && s[i]<='9') || s[i]=='.')
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
        if(s[i]!='-' || s[i]!='+' || s[i]!='\0')
            break;
        printf("%lf, %u\n", coeff, power);
    }
}


int main() {
    // Write C code here
    printf("hello world\n");
    char s[] = "x ^2 *2 3 + x^1 + 2";
    int flag = is_space_between_number(s);
    remove_whitespace(s);
    printf("%s \nSpace:%d\n",s,flag);
    s_to_poly(s);
    return 0;
}

