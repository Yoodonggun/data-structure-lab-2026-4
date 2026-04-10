#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> #include <cstdio>
#define MAX_DEGREE 81
class Polynomial {
	int degree;
	float coef[MAX_DEGREE];
public:
	void add(Polynomial a, Polynomial b) {
		degree = (a.degree > b.degree) ? a.degree : b.degree;
		for (int i = 0; i < MAX_DEGREE; i++) coef[i] = 0;
		for (int i = 0; i <= a.degree; i++) {
			coef[i + (degree - a.degree)] += a.coef[i];
		}
		for (int i = 0; i <= b.degree; i++) {
			coef[i + (degree - b.degree)] += b.coef[i];
		}
	}
	Polynomial() { degree = 0; }
	void read() {
		printf("Enter the highest degree of the polynomial: ");
		(void)scanf("%d", &degree);
		printf("Enter the coefficients for each term (Total: %d):", degree + 1);
		for (int i = 0; i <= degree; i++)
			(void)scanf("%f", coef + i);
	}
	void display(const char* str = " Poly =") {
		printf("\t%s", str);
		for (int i = 0; i < degree; i++)
			printf("%5.1f x^%d +", coef[i], degree - i);
		printf("%4.1f\n", coef[degree]);
	}
};