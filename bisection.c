#include <stdio.h>    //needed for printf
#include <stdlib.h>   //define variables in heap
#include <math.h> //define to use math primitive functions, such as fabs() for absolute valueof floating point number 

#define MAX_ITERATIONS 100  

//static variables
static double a1 = -4.0;
static double b1 = -2.0;
static double a2 = 2.0;
static double b2 = 4.0;


int bisect_hist(double *hist, double a, double b, double tol);

// Define the function f we want to find the roots of
double f(double x0) {
    return exp(-x0) * (3.2 * sin(x0) - 0.5 * cos(x0)) - 3;
}

int bisect_hist(double *hist, double a, double b, double tol) {
    //bisect function body
    double fa = f(a);
    double fb = f(b);
    double midpoint;
    int iteration = 0;

    //check different signs
    if (fa * fb > 0) {
        printf("No root found in the interval [%.2f, %.2f].\n", a, b);
        return -1;  //no root found
    }

    // Bisection method loop
    do {
        midpoint = (a + b) / 2;
        hist[iteration] = midpoint;  
        double fmid = f(midpoint);

        if (fmid == 0.0) {
            break;  //if root is found or check left and right of midpoint
        } else if (fa * fmid < 0) {
            b = midpoint;  
            fb = fmid;
        } else {
            a = midpoint;  
            fa = fmid;
        }

        iteration++;
    } while (fabs(b - a) > tol && iteration < MAX_ITERATIONS);

    //print root and number of iterations
    printf("Found root x*: %.6f\n", midpoint);
    printf("f(x*): %.6f\n", f(midpoint));
    printf("Iterations: %d\n", iteration);
    
    return iteration;  
}

int main(void) {
    //allocate memory and define tolerance
    double tolerance = 1e-4;  

    
    double *hist1 = (double *)malloc(MAX_ITERATIONS * sizeof(double));
    double *hist2 = (double *)malloc(MAX_ITERATIONS * sizeof(double));

    if (!hist1 || !hist2) {
        fprintf(stderr, "Memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    printf("Interval [%.2f, %.2f]:\n", a1, b1);
    int iterations1 = bisect_hist(hist1, a1, b1, tolerance);
    if (iterations1 != -1) {
        for (int i = 0; i < iterations1; i++) {
            printf("Approximation %d: %.6f\n", i + 1, hist1[i]);
        }
    }

    printf("\nInterval [%.2f, %.2f]:\n", a2, b2);
    int iterations2 = bisect_hist(hist2, a2, b2, tolerance);
    if (iterations2 != -1) {
        for (int i = 0; i < iterations2; i++) {
            printf("Approximation %d: %.6f\n", i + 1, hist2[i]);
        }
    }

    //Allocated memory is unallocated   
    free(hist1);
    free(hist2);

    return 0;
}
