//
//  main.c
//  CalcMathLab2
//
//  Created by Alexander Nekhaev on 30.10.2018.
//  Copyright © 2018 Alexander Nekhaev. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define FTYPE long double

FTYPE sourceData[7][2] = {
	{0.17453, 0.00162},
	{0.5236, 0.00252},
	{0.87267, 0.00498},
	{1.22173, 0.0129},
	{1.5708, 0.03964},
	{1.91986, 0.1207},
	{2.26893, 0.34097}
};

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

int main(int argc, const char * argv[]) {
	FTYPE cache[7][2];
	for (int i = 0; i<4; i++) {
		cache[i][0] = sourceData[6-i][0];
		cache[6-i][0] = sourceData[i][0];
		cache[i][1] = sourceData[6-i][1];
		cache[6-i][1] = sourceData[i][1];
	}
	printf("Interpolation:\nP_N(x)=");
	for (int i = 0; i<7; i++) {
		int xs[7];
		int len = i+1;
		for (int j = 0; j<=i; j++) {
			xs[j] = j;
		}
		printf("%Lf",getB(len, xs, cache));
		for (int j = 0; j<i; j++) {
			printf("(x-%Lf)", cache[j][0]);
		}
		if (i<6) {
			printf("+");
		}
	}
	printf("\n");
	return 0;
}
