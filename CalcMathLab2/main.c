//
//  main.c
//  CalcMathLab2
//
//  Created by Alexander Nekhaev on 30.10.2018.
//  Copyright © 2018 Alexander Nekhaev. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FTYPE long double

FTYPE sourceData[7][2] = {{0.17453, 0.000012}, {0.52360, 0.00026}, {0.87267, 0.0025}, {1.22173,
	0.01815}, {1.5708, 0.09763}, {1.91986, 0.40593}, {2.26893,
		1.38035}};
int length = 7;

FTYPE getB(int argc, int* argv, FTYPE source[7][2]) {
	if (argc == 1) {
		return source[argv[0]][1];
	} else {
		int xs1[7];
		int xs2[7];
		int lensub = argc-1;
		for (int i = 0; i<lensub; i++) {
			xs1[i] = argv[i];
		}
		for (int i = 1; i<argc; i++) {
			xs2[i-1] = argv[i];
		}
		FTYPE fa = getB(lensub, xs2, source);
		FTYPE fb = getB(lensub, xs1, source);
		
		return (fa-fb)/(source[argc-1][0]-source[0][0]);
	}
}

FTYPE evaluate(FTYPE* function, FTYPE x) {
	FTYPE result = 0;
	for (int i = 0; i<length; i++) {
		result = function[i] * powl(x, i);
	}
	return result;
}

FTYPE* D(FTYPE* function) {
	FTYPE* result = malloc(sizeof(FTYPE)*6);
	for (int i = 1; i<7; i++) {
		result[i-1] = function[i]*(i);
	}
	return result;
}

int main(int argc, const char * argv[]) {
	FTYPE cache[7][2];
	FTYPE simpleFormOfPolynom[7];
	FTYPE stringOfCoeffs[7];
	for (int i = 0; i<4; i++) {
		cache[i][0] = sourceData[6-i][0];
		cache[6-i][0] = sourceData[i][0];
		cache[i][1] = sourceData[6-i][1];
		cache[6-i][1] = sourceData[i][1];
	}
	printf("Interpolation:\nP_N(x)=");
	for (int i = 0; i<length; i++) {
		int xs[7];
		int len = i+1;
		for (int j = 0; j<=i; j++) {
			xs[j] = j;
		}
		printf("%Lf",getB(len, xs, cache));
		stringOfCoeffs[i] = getB(len, xs, cache);
		for (int j = 0; j<i; j++) {
			printf("(x-%Lf)", cache[j][0]);
		}
		if (i<length-1) {
			printf("+");
		}
	}
	printf("\nSimplified:\n");
	FTYPE brackets[7][2];
	for (int i = 0; i<6; i++) {
		brackets[i][0]=(-1)*cache[i][0];
		brackets[i][1]=1;
	}
	FTYPE last[7];
	for (int i = 0; i<7; i++) {
		last[i] = 0;
	}
	FTYPE lastW[7];
	for (int i = 0; i<7; i++) {
		lastW[i] = last[i];
	}
	last[0] = 1;
	for (int i = 0; i<length; i++) {
		for (int j = 0; j<length; j++) {
			simpleFormOfPolynom[j] += stringOfCoeffs[i]*last[j];
		}
		for (int br = i; br<=i; br++) {
			for (int k = 0; k<2; k++) {
				for (int cf = 0; cf<length; cf++) {
					lastW[cf+k] += last[cf]*brackets[br][k];
				}
			}
			for (int j = 0; j<length; j++) {
				last[j] = lastW[j];
				lastW[j] = 0;
			}
		}
	}
	for (int i = 0; i<length; i++) {
		if (i == 0) {
			printf("%Lf", simpleFormOfPolynom[i]);
		} else {
			printf("%Lf*x^%d", simpleFormOfPolynom[i], i);
			if (i<length-1) {
				printf("+");
			}
		}
	}
	printf("\n");
	return 0;
}
