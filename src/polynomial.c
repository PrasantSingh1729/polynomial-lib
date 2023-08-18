/*
 * polynomial.c
 * Implementation of functions for the polynomial library.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "polynomial.h"

/* -------------------- Helper Functions ------------------------------------ */

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

/* return duplicate poly of given poly */
poly duplicate_poly(poly p)
{
    poly dub_poly = init_poly();
    dub_poly->termlist->next = duplicate_termlist(p->termlist->next);
    return dub_poly;
}

/* Swap two char */
void swap_char(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

/* check if there is space in between two number */
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

/* remove whitespace from string */
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

/* remove terms from poly who's coefficient is zero */
void simplify_poly(poly p)
{
    term pptr = p->termlist;
    while (pptr->next != NULL)
    {
        if (pptr->next->coeff == 0.0)
        {
            /* delete term */
            term temp = pptr->next;
            pptr->next = pptr->next->next;
            free(temp);
        }
        else
        {
            pptr = pptr->next;
        }
    }
}

/* if mode=0 add two poly otherwise subtract */
poly add_subtract_helper(poly p1, poly p2, int mode)
{
    poly result = init_poly();
    /* putting result term pointer on header so that I can insert in front and move forward*/
    term resultptr = result->termlist;
    /* putting p1 term pointer on first term */
    term p1ptr = p1->termlist->next;
    /* putting p2 term pointer on first term */
    term p2ptr = p2->termlist->next;

    while (p1ptr != NULL && p2ptr != NULL)
    {
        if (p1ptr->power == p2ptr->power)
        {
            if (mode == 0) // for addition
                resultptr->next = create_term(p1ptr->coeff + p2ptr->coeff, p1ptr->power);
            else // for subtraction
                resultptr->next = create_term(p1ptr->coeff - p2ptr->coeff, p1ptr->power);
            p1ptr = p1ptr->next;
            p2ptr = p2ptr->next;
        }
        else if (p1ptr->power < p2ptr->power)
        {
            if (mode == 0)
                resultptr->next = create_term(p2ptr->coeff, p2ptr->power);
            else
                resultptr->next = create_term(-(p2ptr->coeff), p2ptr->power);
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
        if (mode != 0) // for subtraction
        {
            /* make sign opposite of appended terms from p2 */
            resultptr = resultptr->next;
            while (resultptr != NULL)
            {
                resultptr->coeff = -(resultptr->coeff);
                resultptr = resultptr->next;
            }
        }
    }
    simplify_poly(result);
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

/* check if divisor can further divide dividend */
int can_divide(poly dividend, poly divisor)
{
    /* Dividend not empty and dividend degree is greater than divisor */
    return dividend->termlist->next != NULL &&
           dividend->termlist->next->power >= divisor->termlist->next->power;
}

/* divide two poly and return quotient if mode=0 otherwise return remainder */
poly divide_modulus_helper(poly p1, poly p2, int mode)
{
    poly quotient = init_poly();
    term quotientptr = quotient->termlist;
    poly dividend = duplicate_poly(p1);
    poly divisor = p2;
    /* Divide by zero test */
    if (divisor->termlist->next == NULL)
    {
        printf("Error: Divide by zero error\n");
        exit(1);
    }
    /* while dividend not empty and dividend degree is greater than divisor */
    while (can_divide(dividend, divisor))
    {
        /* generating qterm by dividing first term of both */
        term qterm = create_term(dividend->termlist->next->coeff / divisor->termlist->next->coeff,
                                 dividend->termlist->next->power - divisor->termlist->next->power);

        /* append qterm to quotient */
        quotientptr->next = qterm;
        quotientptr = quotientptr->next;

        poly temp = multiply_one_term_with_poly(qterm, divisor);

        /* reducing dividend by subtracting the product of qterm and divisor from dividend*/
        poly prev_dividend = dividend;
        dividend = subtract_poly(prev_dividend, temp);
        destroy_poly(prev_dividend);
    }
    if (mode == 0)
        return quotient;
    else
        return dividend; /* portion which is not able to divide with divisor is remainder */
}

/* parse double from string and move pointer ahead of parsed part*/
double parse_double(char *s, int *i)
{
    double num;
    sscanf(s + (*i), "%lf", &num);
    int decimal_flag = 0;
    while (s[*i] != '\0' && (isdigit(s[*i]) || s[*i] == '.'))
    {
        if (s[*i] == '.' && decimal_flag == 0)
        {
            decimal_flag = 1;
        }
        else if (s[*i] == '.')
        {
            break;
        }
        (*i)++;
    }
    return num;
}

/* parse unsigned int from string and move pointer ahead of parsed part*/
unsigned int parse_unsigned_int(char *s, int *i)
{
    unsigned int num;
    sscanf(s + (*i), "%d", &num);
    while (s[*i] != '\0' && isdigit(s[*i]))
        (*i)++;
    return num;
}

/* Helper function for merge-sort split termlist into two equal part */
void FrontBackSplit(term source,
                    term *frontRef, term *backRef)
{
    term fast;
    term slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

/* Helper function for merge-sort Merge the sort sorted termlist */
term SortedMerge(term a, term b)
{
    term result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->power >= b->power)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

/* Merge sort the given termlist */
void MergeSort(term *termlist)
{
    term head = *termlist;
    term a;
    term b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    FrontBackSplit(head, &a, &b);
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *termlist = SortedMerge(a, b);
}

/* combine the term in termlist which have same exponent
provided they are consecutively arranged using merge sort*/
void merge_same_expo(term t)
{
    if (t != NULL)
    {
        while (t->next != NULL)
        {
            if (t->next->power == t->power)
            {
                term temp = t->next;
                t->coeff = t->coeff + temp->coeff;
                t->next = temp->next;
                free(temp);
            }
            else
            {
                t = t->next;
            }
        }
    }
}

/* ------------------------------ Main Functions -------------------------------- */

/* convert string to poly and return poly */
poly s_to_poly(const char *user_s)
{
    /* string literal are mutable that's why creating copy */
    int len = strlen(user_s);
    char s[len];
    strcpy(s, user_s);

    /* creating poly to return */
    poly p = init_poly();
    term pptr = p->termlist;

    if (is_space_between_number(s))
    {
        printf("Error: Space between number is not allowed.\n");
        exit(1);
    }
    if (s[len - 1] == '-' || s[len - 1] == '+')
    {
        printf("Error: Sign in end. There should a term after sign.\n");
        exit(1);
    }
    remove_whitespace(s);

    int sign;
    double coeff;
    unsigned int power;
    int i = 0;
    while (s[i] != '\0')
    {
        sign = 1;
        coeff = 1;
        power = 0;
        if (s[i] == '+' || s[i] == '-')
        {
            if (s[i] == '-')
                sign = -1;
            i++;
        }
        // case: x^<power>*<coeff>
        if (s[i] == 'x')
        {
            power = 1;
            i++;
            if (s[i] == '^')
            {
                i++;
                power = parse_unsigned_int(s, &i);
            }

            if (s[i] == '*')
            {
                i++;
                coeff = parse_double(s, &i);
            }
        }
        // case: <coeff>[*]x^<power>
        else if (isdigit(s[i]))
        {
            coeff = parse_double(s, &i);
            if (s[i] == '*')
                i++;
            if (s[i] == 'x')
            {
                power = 1;
                i++;
                if (s[i] == '^')
                {
                    i++;
                    power = parse_unsigned_int(s, &i);
                }
            }
        }
        // not reached next sign or end of string hence error
        if (s[i] != '+' && s[i] != '-' && s[i] != '\0')
        {
            // invalid format
            printf("Error: Invalid input string format\n");
            exit(1);
        }

        coeff = coeff * sign;
        // creating term and inserting into poly
        term temp = create_term(coeff, power);
        temp->next = pptr->next;
        pptr->next = temp;
    }
    MergeSort(&(p->termlist->next));
    merge_same_expo(p->termlist->next);
    simplify_poly(p);
    return p;
}

/* convert poly to string and return pointer to that string */
char *poly_to_s(poly p)
{
    char *result = NULL;
    if (p != NULL)
    {
        char term_str[100]; // any term can't exceed 100 character size
        term_str[0] = '\0';
        int size_of_result = 0;
        int j = 1, i = 0;
        // if j==1 count the number of character required for result
        // if j==2 allocate memory to result and fill result
        while (j <= 2)
        {
            if (j == 2)
            {
                if (size_of_result == 0) // poly have no term
                {
                    // insert zero in string
                    result = (char *)malloc((2) * sizeof(char));
                    result[0] = '0';
                    result[1] = '\0';
                }
                else
                {
                    result = (char *)malloc((size_of_result + 1) * sizeof(char)); // Allocate space for the result string
                    result[0] = '\0';                                             // Initialize result string as an empty string
                }
            }
            int is_first_term = 1;
            term ptr = p->termlist->next;
            while (ptr != NULL)
            {
                term_str[0] = '\0';
                if (is_first_term)
                {
                    if (ptr->coeff == -1 && ptr->power != 0)
                        sprintf(term_str + strlen(term_str), "-");
                    else if (ptr->coeff != 1 || ptr->power == 0)
                        sprintf(term_str + strlen(term_str), "%g", ptr->coeff);
                    is_first_term = 0;
                }
                else
                {
                    if (ptr->coeff == 1 && ptr->power != 0)
                        sprintf(term_str + strlen(term_str), "+");
                    else if (ptr->coeff == -1 && ptr->power != 0)
                        sprintf(term_str + strlen(term_str), "-");
                    else
                        sprintf(term_str + strlen(term_str), "%+g", ptr->coeff);
                }
                if (ptr->power == 1)
                {
                    sprintf(term_str + strlen(term_str), "x");
                }
                else if (ptr->power != 0)
                {
                    sprintf(term_str + strlen(term_str), "x^%u", ptr->power);
                }
                if (j == 1)
                    size_of_result += strlen(term_str);
                else
                {
                    strcpy(result + i, term_str); // fill result
                    i += strlen(term_str);
                }
                ptr = ptr->next;
            }
            j++;
        }
    }
    return result;
}

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
    return add_subtract_helper(p1, p2, 0);
}

/* Subtract two poly and return resultant poly */
poly subtract_poly(poly p1, poly p2)
{
    return add_subtract_helper(p1, p2, 1);
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
        result = add_poly(temp, prev_result);
        p1ptr = p1ptr->next;
        destroy_poly(prev_result);
        destroy_poly(temp);
    }
    return result;
}

/* Divide two poly and return resultant poly (quotient)*/
poly divide_poly(poly p1, poly p2)
{
    return divide_modulus_helper(p1, p2, 0);
}

/* Divide two poly and return resultant poly (remainder)*/
poly modulus_poly(poly p1, poly p2)
{
    return divide_modulus_helper(p1, p2, 1);
}

/* evaluate polynomial for the given value of the variable and return result */
double evaluate_poly(poly p, double x)
{
    /* starting from first term */
    term pptr = p->termlist->next;
    double result = 0;
    while (pptr != NULL)
    {
        /* Summing up all the term and
        calculating each term value by putting x value */
        result += pptr->coeff * pow(x, pptr->power);
        pptr = pptr->next;
    }
    return result;
}

/* ----------------------------------------------------------------------------- */