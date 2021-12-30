#include <stdio.h>
#include <math.h>

// solve the quadratic formula
int main() {
	
	double a = 1;
	double b = 1;
	double c = 1;
	
	printf("a = "); scanf("%lf", &a);
	printf("b = "); scanf("%lf", &b);
	printf("c = "); scanf("%lf", &c);
	
	double x1 = (-b+sqrt(pow(b,2)-4*a*c))/(a*2);
	double x2 = (-b-sqrt(pow(b,2)-4*a*c))/(a*2);
	
	printf("x1 = %lf\n", x1);
	printf("x2 = %lf\n", x2);
	
	return 0;
}
