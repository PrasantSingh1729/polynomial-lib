#ifndef __POLYNOMIAL__H
#define __POLYNOMIAL__H

typedef struct __node
{
    double coeff;
    unsigned int power;
}*term,node;

typedef struct __poly
{
    term termlist;
}*poly;

poly s_to_poly(char *s);
char* poly_to_s(poly p);
void destroy_poly(poly p);
poly add_poly(poly p1, poly p2);
poly subtract_poly(poly p1, poly p2);
poly divide_poly(poly p1, poly p2);
poly multiply_poly(poly p1, poly p2);
poly modulus_poly(poly p1, poly p2);
poly evaluate_poly(poly p);


#endif