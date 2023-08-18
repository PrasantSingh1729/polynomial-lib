#ifndef __POLYNOMIAL_HELPER__H
#define __POLYNOMIAL_HELPER__H
#include "polynomial.h"

/* create a term with provided coefficient and power */
term create_term(double coeff, unsigned int power);

/* allocate memory and initialize termlist with header node */
poly init_poly();

/* return duplicate termlist of given termlist */
term duplicate_termlist(term list);

/* return duplicate poly of given poly */
poly duplicate_poly(poly p);

/* Swap two char */
void swap_char(char *a, char *b);

/* check if there is space in between two number */
int is_space_between_number(char *s);

/* remove whitespace from string */
void remove_whitespace(char *s);

/* remove terms from poly who's coefficient is zero */
void simplify_poly(poly p);

/* if mode=0 add two poly otherwise subtract */
poly add_subtract_helper(poly p1, poly p2, int mode);

/* Multiply one term with given poly and return resultant poly */
poly multiply_one_term_with_poly(term t, poly p);

/* divide two poly and return quotient if mode=0 otherwise return remainder */
poly divide_modulus_helper(poly p1, poly p2, int mode);

/* parse double from string and move pointer ahead of parsed part*/
double parse_double(char *s, int *i);

/* parse unsigned int from string and move pointer ahead of parsed part*/
unsigned int parse_unsigned_int(char *s, int *i);

/* helper function for merge sort split list into two equal part */
void FrontBackSplit(term source,
                    term *frontRef, term *backRef);

/* Helper function for merge-sort Merge the sort sorted termlist */
term SortedMerge(term a, term b);

/* Merge sort the given termlist */
void MergeSort(term *termlist);

/* combine the term in termlist which have same exponent 
provided they are consecutively arranged using merge sort*/
void merge_same_expo(term t);


#endif
