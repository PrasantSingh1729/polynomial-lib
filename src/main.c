#include <stdio.h>
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
        term ptr = p->termlist->next;
        while(ptr!=NULL)
        {
            if(ptr->coeff>=0)
                printf("+%0.2fx^%u",ptr->coeff,ptr->power);
            else
                printf("%0.2fx^%u",ptr->coeff,ptr->power);
            ptr = ptr->next;
        }
    }
}

int main()
{
    int arr1[][2] = {{3,2}};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    int arr2[][2] = {{4,2},{6,1},{5,0}};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    // poly p1 = array_to_poly(arr1,n1);
    poly p1 = init_poly();
    poly p2 = array_to_poly(arr2, n2);
    print_poly(p1);
    printf("\n");
    print_poly(p2);
    printf("\n");
    poly p3 = multiply_poly(p1,p2);
    print_poly(p3);
    printf("\n");
    destroy_poly(p1);
    // destroy_poly(p2);
    
}
