#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "polynomial.h"

/* create a term with provided coefficient and power */
term create_term(double coeff, unsigned int power)
{
    term t = (term)malloc(sizeof(node));
    t->coeff = coeff;
    t->power = power;
    t->next = NULL;
    return t;
}

/* allocate memory and initialize termlist with header node */
poly init_poly()
{
    poly p = (poly)malloc(sizeof(struct __poly));
    /* create a header node in termlist */
    p->termlist = create_term(0, 0);
    return p;
}

/* return duplicate termlist of given termlist */
term duplicate_termlist(term list)
{

    term dub_list = NULL;
    if (list != NULL)
    {
        /* coping first term in duplicate list */
        dub_list = create_term(list->coeff, list->power);
        term dub_listptr = dub_list;
        list = list->next;
        while (list != NULL)
        {
            dub_listptr->next = create_term(list->coeff, list->power);
            dub_listptr = dub_listptr->next;
            list = list->next;
        }
    }

    return dub_list;
}

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

/*
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
*/

/* Free the memory occupied by termlist and poly structure */
void destroy_poly(poly p)
{
    if (p != NULL)
    {
        while (p->termlist != NULL)
        {
            term temp = p->termlist;
            p->termlist = p->termlist->next;
            free(temp);
        }
        free(p);
    }
}

/* Add two poly and return resultant poly */
poly add_poly(poly p1, poly p2)
{
    poly result = init_poly();
    /* putting reult term pointer on header so that I can insert in front and move forward*/
    term resultptr = result->termlist;
    /* putting p1 term pointer on first term */
    term p1ptr = p1->termlist->next;
    /* putting p2 term pointer on first term */
    term p2ptr = p2->termlist->next;

    while (p1ptr != NULL && p2ptr != NULL)
    {
        if (p1ptr->power == p2ptr->power)
        {
            resultptr->next = create_term(p1ptr->coeff + p2ptr->coeff, p1ptr->power);
            p1ptr = p1ptr->next;
            p2ptr = p2ptr->next;
        }
        else if (p1ptr->power > p2ptr->power)
        {
            resultptr->next = create_term(p2ptr->coeff, p2ptr->power);
            p2ptr = p2ptr->next;
        }
        else
        {
            resultptr->next = create_term(p1ptr->coeff, p1ptr->power);
            p1ptr = p1ptr->next;
        }
        resultptr = resultptr->next;
    }
    if (p1ptr != NULL)
    {
        resultptr->next = duplicate_termlist(p1ptr);
    }
    else if (p2ptr != NULL)
    {
        resultptr->next = duplicate_termlist(p2ptr);
    }
    return result;
}

/* Subtract two poly and return resultant poly */
poly subtract_poly(poly p1, poly p2)
{
    poly result = init_poly();
    /* putting reult term pointer on header so that I can insert in front and move forward*/
    term resultptr = result->termlist;
    /* putting p1 term pointer on first term */
    term p1ptr = p1->termlist->next;
    /* putting p2 term pointer on first term */
    term p2ptr = p2->termlist->next;

    while (p1ptr != NULL && p2ptr != NULL)
    {
        if (p1ptr->power == p2ptr->power)
        {
            resultptr->next = create_term(p1ptr->coeff - p2ptr->coeff, p1ptr->power);
            p1ptr = p1ptr->next;
            p2ptr = p2ptr->next;
        }
        else if (p1ptr->power > p2ptr->power)
        {
            resultptr->next = create_term(p2ptr->coeff, p2ptr->power);
            p2ptr = p2ptr->next;
        }
        else
        {
            resultptr->next = create_term(p1ptr->coeff, p1ptr->power);
            p1ptr = p1ptr->next;
        }
        resultptr = resultptr->next;
    }
    if (p1ptr != NULL)
    {
        resultptr->next = duplicate_termlist(p1ptr);
    }
    else if (p2ptr != NULL)
    {
        resultptr->next = duplicate_termlist(p2ptr);
    }
    return result;
}

/* Multiply one term with given poly and return resultant poly */
poly multiply_one_term_with_poly(term t, poly p)
{
    /* t * p = result */
    poly result = init_poly();
    /* putting resultptr on header node */
    term resultptr = result->termlist;
    /* putting pptr on first term of poly p*/
    term pptr = p->termlist->next;
    while (pptr != NULL)
    {
        /* multiplying term with term and appending into result */
        resultptr->next = create_term((pptr->coeff) * (t->coeff),
                                      (pptr->power) + (t->power));
        resultptr = resultptr->next;
        pptr = pptr->next;
    }
    return result;
}

/* Multiply two poly and return resultant poly */
poly multiply_poly(poly p1, poly p2)
{
    poly result = init_poly();
    /* putting p1ptr on first term of poly p1*/
    term p1ptr = p1->termlist->next;
    /* Picking one term at a time from p1 and multiplying with p2 */
    /* Summing up into result poly*/
    while (p1ptr != NULL)
    {
        poly prev_result = result;
        poly temp = multiply_one_term_with_poly(p1ptr, p2);
        result = add_poly(temp,prev_result);
        p1ptr = p1ptr->next;
        destroy_poly(prev_result);
        destroy_poly(temp);
    }
    return result;
}