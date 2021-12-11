#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "RSA_cryptography.h"

int len = 0;
int text[100];




int p = 7; // Prime 1
int q = 13; // Prime 2
int e = 11; // Public exponent
int n = 0; // n = p * q;
int d = 0; // d = (1/e) mod (phi)
int phi = 0; // (p - 1) * (q - 1)


// 	int c[3];
// 	c[0] = 4;
// 	c[1] = 5;
// 	c[2] = 6;

int c[3] ={0x02,0xff,0x03};

// Find the Greatest Common Divisor between two numbers
int gcd(int num1, int num2){
	int temp;

	while(num2 > 0){
		temp = num1 % num2;
		num1 = num2;
		num2 = temp;
	}
	
	return num1;
}

int mod_inverse(int u, int v)
{
	int inv, u1, u3, v1, v3, t1, t3, q;
	int iter;
	/* Step X1. Initialise */
	u1 = 1;
	u3 = u;
	v1 = 0;
	v3 = v;
	/* Remember odd/even iterations */
	iter = 1;
	/* Step X2. Loop while v3 != 0 */
	while (v3 != 0)
	{
		/* Step X3. Divide and "Subtract" */
		q = u3 / v3;
		t3 = u3 % v3;
		t1 = u1 + q * v1;
		/* Swap */
		u1 = v1; v1 = t1; u3 = v3; v3 = t3;
		iter = -iter;
	}
	/* Make sure u3 = gcd(u,v) == 1 */
	if (u3 != 1)
	return 0;   /* Error: No inverse exists */
	/* Ensure a positive result */
	if (iter < 0)
	inv = v - u1;
	else
	inv = u1;
	return inv;
}



// Check if the input number is a prime number or not
bool check_prime(num)
{

	if(num == 0 || num == 1){
		return false;
	}

	// Return true if the number can only divide 1 and itself
	for(int i = 2; i < num; i++){
		if (num % i == 0 && i != num){
			return false;
		}
	}
	
	return true;
}

// Check if input e is valid
bool check_e(e, phi)
{

	// e and phi must have gcd of 1, 1 < e < phi
	if(gcd(e,phi) == 1 && e > 1 && e < phi){
		return true;
		} else{
		return false;
	}
}

// The Modular Exponentiation Algorithm
int MEA(int p, int e, int n)
{
	
	int r2 = 1;
	int r1 = 0;
	int Q = 0;
	int R = 0;
	
	while( e != 0 ){
		R = (e % 2);
		Q = ((e - R) / 2);
		
		r1 = ((p * p) % n);
		
		if(R == 1){
			r2 = ((r2 * p) % n);
		}
		p = r1;
		e = Q;
	}
	return r2;
}

// Received input from user
void encode(e,n)
{
	int i = 0;
	
	for(i=0; i<4; i++)
	{
		text[i] = MEA(c[i], e, n);
	}

	
}

void decode(d,n)
{
	

	for(int i = 0; i < 4; i++){

		
		text[i] = MEA(text[i], d, n);
	}



}

void clear_input()
{
	// Clears the text array
	memset(text,0,sizeof(text));
	len = 0;
}

int mainRSA()
{
	while(1)
	{
		
		
		

		bool valid_input = true;
		
		if(check_prime(p) == false)
		{
			valid_input = false;

			printf("The number entered is not a prime number. Try again.\n");
		}
		else
		{
			valid_input = true;
		}
		if(check_prime(q) == false)
		{
			valid_input = false;
			printf("The number entered is not a prime number. Try again.\n");
		}
		else
		{
			valid_input = true;
		}
		n = p * q;
		phi = (p-1)*(q-1);
		if(check_e(e,phi) == false)
		{
			valid_input = false;
			printf("The 'e' value is not compatible. Try again.\n");
		}
		else
		{
			valid_input = true;
		}
		d = mod_inverse(e, phi);
		
		
		
		printf("\r\np=%d, q=%d, e=%d, n=%d, d=%d",p,q,e,n,d);
		text[0]=1;
		text[1]=2;
		text[2]=3;
		
		printf("\r\nOriginal Text = %02x %02x %02x ",text[0],text[1],text[2]);
		encode(e,n);
		//printf("\r\nEncode Text = %d %d %d ",text[0],text[1],text[2]);
		printf("\r\nOriginal Text = %02x %02x %02x ",text[0],text[1],text[2]);
		
		decode(d,n);
		
	//	printf("\r\nDecode Text = %d %d %d ",text[0],text[1],text[2]);
		printf("\r\nOriginal Text = %02x %02x %02x ",text[0],text[1],text[2]);
	}
	
}


