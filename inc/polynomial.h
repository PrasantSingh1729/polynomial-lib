/*
 * polynomial.h
 * Library that allows users to perform arithmetic operations on one-variable polynomials.
 * Users can input polynomials in the form of strings
 * Library will handle the parsing, manipulation, and calculations related to these polynomials.
 * Library also support to evaluate the polynomial,
 * and if user wants, he can see resultant polynomial in the form of string
 */

#ifndef __POLYNOMIAL__H
#define __POLYNOMIAL__H

/**
 * Represents a polynomial term stored in the form of a linked list data structure.
 */
typedef struct __node
{
    double coeff;        /**< The coeff of the polynomial term. */
    unsigned int power;  /**< The power of the polynomial term. */
    struct __node *next; /**< The Link to the next polynomial term. */
} *term, node;

/**
 * Represents polynomial and have termlist stored in the form of a linked list data structure.
 * Properties of termlist which always need to be maintained
 *      -Terms should be ordered in termlist in increasing order of the exponents
 *      -No two term have same exponent
 *      -No term can have zero coeff
 */
typedef struct __poly
{
    term termlist; /**< Pointer to the header of the linked list representing the terms of a polynomial. */
} *poly;

/**
 * Convert string to poly and return poly.
 *
 * @param s user string which represent polynomial.
 * @return poly structure of polynomial.
 */
poly s_to_poly(const char *s);

/**
 * Convert poly to string and return pointer to that string.
 *
 * @param p poly.
 * @return string representation of the poly.
 */
char *poly_to_s(poly p);

/**
 * Free the memory occupied by termlist and poly structure
 *
 * @param p poly.
 */
void destroy_poly(poly p);

/**
 * Add two poly and return resultant poly
 *
 * @param p1 poly.
 * @param p2 poly.
 * @return resultant poly (p1+p2)
 */
poly add_poly(poly p1, poly p2);

/**
 * Subtract two poly and return resultant poly
 *
 * @param p1 poly.
 * @param p2 poly.
 * @return resultant poly (p1-p2)
 */
poly subtract_poly(poly p1, poly p2);

/**
 * Multiply two poly and return resultant poly
 *
 * @param p1 poly.
 * @param p2 poly.
 * @return resultant poly (p1*p2)
 */
poly multiply_poly(poly p1, poly p2);

/**
 * Divide two poly and return resultant poly (quotient)
 *
 * @param p1 poly.
 * @param p2 poly.
 * @return resultant quotient poly obtained by p1/p2
 */
poly divide_poly(poly p1, poly p2);

/**
 * Divide two poly and return resultant poly (remainder)
 *
 * @param p1 poly.
 * @param p2 poly.
 * @return resultant remainder poly obtained by p1/p2
 */
poly modulus_poly(poly p1, poly p2);

/**
 * Evaluate polynomial for the given value of the variable and return result
 *
 * @param p poly.
 * @param x value of the variable.
 * @return result of the evaluated polynomial by putting value of variable.
 */
double evaluate_poly(poly p, double x);

#endif