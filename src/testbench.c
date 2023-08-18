#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "polynomial.h"


poly array_to_poly(int arr[][2], int n)
{
    poly p = init_poly();
    term pptr = p->termlist;
    for(int i=0;i<n;i++)
    {
        pptr->next = create_term(arr[i][0],arr[i][1]);
        pptr = pptr->next;
    }
    return p;
}

void print_poly(poly p)
{
    if(p!=NULL)
    {
        int is_first_term = 1;
        term ptr = p->termlist->next;
        while(ptr!=NULL)
        {
            if(is_first_term)
            {
                printf("%g",ptr->coeff);
                is_first_term = 0;
            }
            else
            {
                printf("%+g",ptr->coeff);
            }
            if(ptr->power==1)
            {
                printf("x");
            }
            else if(ptr->power!=0)
            {
                printf("x^%u",ptr->power);
            }
            ptr = ptr->next;
        }
    }
}

int main()
{
    return 0;
}