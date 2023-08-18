#ifndef __POLYNOMIAL__H
#define __POLYNOMIAL__H

typedef struct __node
{
    double coeff;
    unsigned int power;
    struct __node *next;
}*term,node;

typedef struct __poly
{
    term termlist;
}*poly;

/* convert string to poly and return poly */
poly s_to_poly(const char *s);

/* convert poly to string and return pointer to that string */
char* poly_to_s(poly p);

/* Free the memory occupied by termlist and poly structure */
void destroy_poly(poly p);

/* Add two poly and return resultant poly */
poly add_poly(poly p1, poly p2);

/* Subtract two poly and return resultant poly */
poly subtract_poly(poly p1, poly p2);

/* Multiply two poly and return resultant poly */
poly multiply_poly(poly p1, poly p2);

/* Divide two poly and return resultant poly (quotient)*/
poly divide_poly(poly p1, poly p2);

/* Divide two poly and return resultant poly (remainder)*/
poly modulus_poly(poly p1, poly p2);

/* evaluate polynomial for the given value of the variable and return result */
double evaluate_poly(poly p, double x);

#endif