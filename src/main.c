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
    // int arr1[][2] = {{4,3},{-3,2},{3,1}};
    // int n1 = sizeof(arr1)/sizeof(arr1[0]);
    // int arr2[][2] = {{2,2},{1,0}};
    // int n2 = sizeof(arr2)/sizeof(arr2[0]);
    // poly p1 = array_to_poly(arr1,n1);
    // // poly p1 = init_poly();
    // poly p2 = array_to_poly(arr2, n2);
    // print_poly(p1);
    // printf("\n");
    // print_poly(p2);
    // printf("\n");
    // poly p3 = divide_poly(p1,p2);
    // print_poly(p3);
    // printf("\n");
    // char *s = poly_to_s(p3);
    // printf("string: %s\n",s);
    // free(s);
    // destroy_poly(p1);
    // destroy_poly(p2);
    // destroy_poly(p3);


    poly p1, p2;
    // char s1[100], s2[100];
    // printf("Enter first polynomial  : ");
    // gets(s1);
    // printf("Enter second polynomial : ");
    // gets(s2);
    // p1 = s_to_poly(s1);
    // p2 = s_to_poly(s2);
    p1 = s_to_poly("5x^5-4x^4+3x^3+x^2-10");
    p2 = s_to_poly("x^2-x+2");
    poly r1 = add_poly(p1,p2);
    poly r2 = subtract_poly(p1,p2);
    poly r3 = multiply_poly(p1,p2);
    poly r4 = divide_poly(p1,p2);
    poly r5 = modulus_poly(p1,p2);
    char *s;
    s = poly_to_s(r1);
    printf("Addition : %s\n",s);
    free(s);
    s = poly_to_s(r2);
    printf("Subtract : %s\n",s);
    free(s);
    s = poly_to_s(r3);
    printf("Multiply : %s\n",s);
    free(s);
    s = poly_to_s(r4);
    printf("Divide   : %s\n",s);
    free(s);
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
