#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "polynomial.h"
#include "polynomail_helper.h"
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
    poly p1, p2;
    char s1[100], s2[100];
    printf("Enter first polynomial  : ");
    gets(s1);
    printf("Enter second polynomial : ");
    gets(s2);
    p1 = s_to_poly(s1);
    p2 = s_to_poly(s2);
    // p1 = s_to_poly("4x^3-3x^2+3x");
    // p2 = s_to_poly("2x^2+1");
    char *s;

    s = poly_to_s(p1);
    printf("P1       : %s\n",s);
    free(s);
    
    s = poly_to_s(p2);
    printf("P2       : %s\n",s);
    free(s);
    
    printf("P1 eval  : %g\n", evaluate_poly(p1,2));
    
    printf("P2 eval  : %g\n", evaluate_poly(p2,2));
    
    poly r1 = add_poly(p1,p2);
    s = poly_to_s(r1);
    printf("Addition : %s\n",s);
    free(s);
    
    poly r2 = subtract_poly(p1,p2);
    s = poly_to_s(r2);
    printf("Subtract : %s\n",s);
    free(s);

    poly r3 = multiply_poly(p1,p2);
    s = poly_to_s(r3);
    printf("Multiply : %s\n",s);
    free(s);
    
    poly r4 = divide_poly(p1,p2);
    s = poly_to_s(r4);
    printf("Divide   : %s\n",s);
    free(s);
    
    poly r5 = modulus_poly(p1,p2);
    s = poly_to_s(r5);
    printf("Modulus  : %s\n",s);
    free(s);
    
    destroy_poly(p1);
    destroy_poly(p2);
    destroy_poly(r1);
    destroy_poly(r2);
    destroy_poly(r3);
    destroy_poly(r4);
    destroy_poly(r5);
    
}
