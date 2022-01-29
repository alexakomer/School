/*
DADA function declarations
*/

#ifndef DADA_H
#define DADA_H

/**
 * Get index of the first element of input vector with maximum absolute value.
 * @param   x     input vector
 * @param   len   length of input vector
 * @return        index of first element of input vector with maximum absolute value, or -1 if vector is empty
 */
int amax(
    const double x[], 
    const unsigned int len);

/**
 * Get sum of absolute values of input vector's elements.
 * @param   x       input vector
 * @param   len     length of input vector
 * @return          sum of absolute values of input vector's elements
 */
double asum(
    const double x[], 
    const unsigned int len);

/**
 * Add scalar multiple of vector to input vector: ȳ = a*x̄ + ȳ
 * @param   a       scalar multiple of input vector x
 * @param   x       input vector x
 * @param   y       input vector y
 * @param   len     length of input vectors
 */
void axpy(
    const double a, 
    const double x[], 
    double y[], 
    const unsigned int len);

/**
 * Copy input vector x into input vector y.
 * @param   src     input source vector
 * @param   dest    input destination vector
 * @param   len     length of input vectors
 */
void copy(
    const double x[], 
    double y[], 
    const unsigned int len);

/**
 * Calculate dot product of two input vectors.
 * @param   x       input vector x
 * @param   y       input vector y
 * @param   len     length of input vectors
 * @return          doct product of two input vectors
 */
double dot(
    const double x[], 
    const double y[], 
    const unsigned int len);

/**
 * Calculate Euclidean norm (i.e., magnitude, length) of input vector.
 * @param   x       input vector
 * @param   len     length of input vetor
 * @return          Euclidean norm of input vector
 */
double norm2(
    const double x[],
    const unsigned int len);

/**
 * Multiply input vector by a scalar: x̄ = a*x̄
 * @param   a   input scalar
 * @param   x   input vector
 */
void scale(
    const double a,
    double x[], 
    const unsigned int len);

/**
 * Swap element values between input vectors x and y.
 * @param   x   input vector x
 * @param   y   input vector y
 */
void swap(
    double x[], 
    double y[], 
    const unsigned int len);

#endif
