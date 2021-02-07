/* Made by Panikos Christou 904311
 *
 * The below program has a lot of helper function that take up the most lines
 * in order to understand how it works, I suggest going at the bottom and
 * check the encrypt function and follow it. If at any point you want to see
 * how the reults are made, then go into the functions used there to see.
 *
 */



#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




unsigned char  binaryToChar(char* str) {
	unsigned char  c = 0;
	int i = 0;
	int power = 128;
	for (i = 0; i < 8; i++) {
		if (str[i] == '1') c += power;
		power /= 2;
	}
	return c;
}

unsigned int binaryToKey(char* str) {

	unsigned int c = 0;
	int i = 0;
	int power = 512; /*2^9 */
	for (i = 0; i < 10; i++) {
		if (str[i] == '1') c += power;
		power /= 2;
	}
	return c;
}
/*
unsigned int binaryToIntLength(char* str, unsigned int len) {

	unsigned int c = 0;
	int i = 0;
	int power = pow(2, len-1);
	for (i = 0; i < 10; i++) {
		if (str[i] == '1') c += power;
		power /= 2;
	}
	return c;
}

unsigned char binaryToCharLength(char* str, unsigned char len) {

	unsigned char c = 0;
	int i = 0;
	int power = pow(2, len - 1);
	for (i = 0; i < 10; i++) {
		if (str[i] == '1') c += power;
		power /= 2;
	}
	return c;
}
*/
char* charToBinary(unsigned char  c) {
	char* str = malloc((8 + 1) * sizeof(char));
	int i = 0;
	for (i = 7; i >= 0; i--) {
		if (c & 1) {
			str[i] = '1';
		}
		else {
			str[i] = '0';
		}

		c = c >> 1;

	}
	str[8] = '\0';
	return (char*)str;
}



char* keyToBinary(unsigned int c) {
	char* str = malloc((10 + 1) * sizeof(char));
	int i = 0;
	for (i = 9; i >= 0; i--) {
		if (c & 1) {
			str[i] = '1';
		}
		else {
			str[i] = '0';
		}

		c = c >> 1;

	}
	str[10] = '\0';
	return (char*)str;

}

char  getBitOfChar(unsigned char  c, int index) {
	c = c >> 7 - index;
	if (c & 1) {
		return '1';
	}
	return  '0';

}
char  getBitOfKey(unsigned int c, int index) {

	c = c >> 9 - index;
	if (c & 1) {
		return '1';
	}
	return  '0';
}
char  getBitOfHalfKey(unsigned int c, int index) {

	c = c >> 4 - index;
	if (c & 1) {
		return '1';
	}
	return  '0';
}

void printInt(unsigned int i) {
	printf("\n%u \n", i);
}
void printStr(char* i) {
	printf("\n %s \n\n", (char*)i);
}
void printChar(unsigned char  i) {
	printf("\n %u \n", i);
}


unsigned char  firstPermutation(unsigned char  c) {

	unsigned char  ar[9];
	ar[8] = '\0';

	ar[0] = getBitOfChar(c, 1);
	ar[1] = getBitOfChar(c, 5);
	ar[2] = getBitOfChar(c, 2);
	ar[3] = getBitOfChar(c, 0);
	ar[4] = getBitOfChar(c, 3);
	ar[5] = getBitOfChar(c, 7);
	ar[6] = getBitOfChar(c, 4);
	ar[7] = getBitOfChar(c, 6);


	unsigned char  ret = binaryToChar(ar);

	return ret;

}

unsigned char  getLeft(unsigned char  ip) {
	unsigned char  ret = 0;
	ret = ip >> 4;
	return ret;
}

unsigned char  getRight(unsigned char  ip) {
	unsigned char  ret = 0;
	ret = ip << 4;
	ret = ret >> 4;
	return ret;
}

unsigned keyFirstPerm(unsigned int c) {
	unsigned char  ar[11];
	ar[10] = '\0';
	ar[0] = getBitOfKey(c, 2);
	ar[1] = getBitOfKey(c, 4);
	ar[2] = getBitOfKey(c, 1);
	ar[3] = getBitOfKey(c, 6);
	ar[4] = getBitOfKey(c, 3);
	ar[5] = getBitOfKey(c, 9);
	ar[6] = getBitOfKey(c, 0);
	ar[7] = getBitOfKey(c, 8);
	ar[8] = getBitOfKey(c, 7);
	ar[9] = getBitOfKey(c, 5);

	unsigned int  ret = binaryToKey(ar);

	return ret;
}

unsigned int getLeftOfKey(unsigned int p10) {
	unsigned int ret = 0;
	ret = p10 >> 5;
	ret = ret & 0x001F;
	return ret;

}

unsigned int getRightOfKey(unsigned int p10) {
	unsigned int ret = 0;
	ret = p10 & 0x001F;
	return ret;

}

unsigned int circularShift5Bits(unsigned int ls1) {

	unsigned int temp = ls1 >> 4;
	temp = temp & 0x0001;
	ls1 = ls1 << 1;
	ls1 = ls1 | temp;
	return ls1 & 0x1F;
}

unsigned char circularShift4Bits(unsigned char ls1) {
	unsigned char temp = ls1 >> 3;
	temp = temp & 00000001;
	ls1 = ls1 << 1;
	ls1 = ls1 | temp;
	return ls1 & (unsigned char)00001111;
}

unsigned char halfKeysToKey(unsigned ls1, unsigned rs1) {
	unsigned char  ar[9];
	ar[8] = '\0';

	ar[0] = getBitOfHalfKey(rs1, 0);
	ar[1] = getBitOfHalfKey(ls1, 2);
	ar[2] = getBitOfHalfKey(rs1, 1);
	ar[3] = getBitOfHalfKey(ls1, 3);
	ar[4] = getBitOfHalfKey(rs1, 2);
	ar[5] = getBitOfHalfKey(ls1, 4);
	ar[6] = getBitOfHalfKey(rs1, 4);
	ar[7] = getBitOfHalfKey(rs1, 3);

	unsigned char  ret = binaryToChar(ar);

	return ret;
}

unsigned char EpPerm(unsigned char c) {

	unsigned char  ar[9];
	ar[8] = '\0';

	ar[0] = getBitOfChar(c, 3);
	ar[1] = getBitOfChar(c, 0);
	ar[2] = getBitOfChar(c, 1);
	ar[3] = getBitOfChar(c, 2);
	ar[4] = getBitOfChar(c, 1);
	ar[5] = getBitOfChar(c, 2);
	ar[6] = getBitOfChar(c, 3);
	ar[7] = getBitOfChar(c, 0);


	unsigned char  ret = binaryToChar(ar);

	return ret;


}
int convertSboxCoord(int s1Col1, int s1Col2) {
	return s1Col2 + s1Col1 * 2;

}

unsigned char findSBOX1(unsigned char xorRes, unsigned char sbox[4][4]) {
	int s1Col1 = getBitOfChar(xorRes, 1) - '0';
	int s1Col2 = getBitOfChar(xorRes, 2) - '0';

	int col = convertSboxCoord(s1Col1, s1Col2);

	int s1row1 = getBitOfChar(xorRes, 0) - '0';
	int s1row2 = getBitOfChar(xorRes, 3) - '0';

	int row = convertSboxCoord(s1row1, s1row2);

	return sbox[row][col];

	/*printf("-----------\n %d \n", col);
	printf("\n %d \n---------", row);
	printf("-----------\n %d \n----------------", res);*/



}

unsigned char findSBOX2(unsigned char xorRes, unsigned char sbox[4][4]) {
	int s1Col1 = getBitOfChar(xorRes, 5) - '0';
	int s1Col2 = getBitOfChar(xorRes, 6) - '0';

	int col = convertSboxCoord(s1Col1, s1Col2);

	int s1row1 = getBitOfChar(xorRes, 4) - '0';
	int s1row2 = getBitOfChar(xorRes, 7) - '0';

	int row = convertSboxCoord(s1row1, s1row2);




	int res = sbox[row][col];


	return sbox[row][col];

	/*printf("-----------\n %d \n", col);
	printf("\n %d \n---------", row);
	printf("-----------\n %d \n----------------", res);*/

}
void printCharDetails(unsigned char c, char* str) {

	printf(" \n %s is : \n", str);
	printChar(c);
	printStr("with binary : ");
	char* temp = charToBinary(c);
	printStr(temp);
	free(temp);
}
void printIntDetails(unsigned int c, char* str) {

	printf(" \n %s is : \n", str);
	printInt(c);
	printStr("with binary : ");
	char* temp = keyToBinary(c);
	printStr(temp);
	free(temp);
}

unsigned char createP4(unsigned char p41, unsigned char p42) {
	char  ar[9];
	ar[8] = '\0';

	ar[0] = '0';
	ar[1] = '0';
	ar[2] = '0';
	ar[3] = '0';
	ar[4] = getBitOfChar(p41, 7);
	ar[5] = getBitOfChar(p42, 7);
	ar[6] = getBitOfChar(p42, 6);
	ar[7] = getBitOfChar(p41, 6);


	unsigned char  ret = binaryToChar(ar);

	return ret;





}

unsigned circularShift10bits(unsigned p10) {
	unsigned int temp = p10 >> 9;
	temp = temp & 0x0001;
	p10 = p10 << 1;
	p10 = p10 | temp;
	return p10 & 0x03FF;

}

unsigned char finalPerm(unsigned char a, unsigned char b) {
	unsigned char  ar[9];
	ar[8] = '\0';

	ar[0] = getBitOfChar(a, 3 + 4);
	ar[1] = getBitOfChar(a, 0 + 4);
	ar[2] = getBitOfChar(a, 2 + 4);
	ar[3] = getBitOfChar(b, 0 + 4);
	ar[4] = getBitOfChar(b, 2 + 4);
	ar[5] = getBitOfChar(a, 1 + 4);
	ar[6] = getBitOfChar(b, 3 + 4);
	ar[7] = getBitOfChar(b, 1 + 4);

	unsigned char  ret = binaryToChar(ar);

	return ret;
}

int  encrypt(char* plaintext, char* key) {

	unsigned char sbox1[4][4] = {
		{1,0,3,2},
		{3,2,1,0},
		{0,2,1,3},
		{3,1,3,2} };

	unsigned char sbox2[4][4] = {
		{0,1,2,3},
		{2,0,1,3},
		{3,0,1,0},
		{2,1,0,3} };




	unsigned char  c = binaryToChar(plaintext);

	char* temp;

	/*printStr("you want to encrypt : ");
	printStr(plaintext);
	printStr("plaintext in value is : ");
	printChar(c);*/

	unsigned int k = binaryToKey(key);

	/*printStr("with key");
	printStr(key);
	printStr("key in value is : ");
	printInt(k);*/

	unsigned int p10 = keyFirstPerm(k);

	////printIntDetails(p10, "p10");

	unsigned int ls1 = getLeftOfKey(p10);
	ls1 = circularShift5Bits(ls1);

	////printIntDetails(ls1, "ls1");

	unsigned int rs1 = getRightOfKey(p10);
	rs1 = circularShift5Bits(rs1);

	////printIntDetails(rs1, "rs1");
	unsigned int t1 = 0;
	t1 = t1 | ls1;

	//// printIntDetails(t1, "t1");
	
	t1 = t1<<5;
	//// printIntDetails(t1, "t1");
	
	t1 = t1 | rs1;

	//// printIntDetails(t1,"t1");
	
	unsigned char p8 = halfKeysToKey(ls1, rs1);
	unsigned char k1 = p8;

	//// printCharDetails(k1, "k1");

	/*---------------------------------------------------------------------------------------------------------*/

	unsigned char  ip = firstPermutation(c);

	////printCharDetails(ip, "ip");

	unsigned char  l0 = getLeft(ip);

	////printCharDetails(l0, "l0");

	unsigned char  r0 = getRight(ip);

	////printCharDetails(r0, "r0");

	unsigned char  ep = EpPerm(r0 << 4);

	////printCharDetails(ep, "ep");

	unsigned char  xorRes = ep ^ k1;

	////printCharDetails(xorRes, "xorRes");


	unsigned char p41 = findSBOX1(xorRes, sbox1);

	////printCharDetails(p41, "p41");


	unsigned char p42 = findSBOX2(xorRes, sbox2);

	////printCharDetails(p42, "p42");

	unsigned char p4 = createP4(p41, p42);

	////printCharDetails(p4, "p4");

	////printCharDetails(l0,"l0");

	unsigned char xorRes2 = p4 ^ l0;

	////printCharDetails(xorRes2, "xorRes2");

	unsigned char l1 = r0;


	////printCharDetails(l1, "l1");

	unsigned char r1 = xorRes2;


	////printCharDetails(r1, "r1");

	/*-------------------------------------------------------------------------------------------------*/

	
	///printIntDetails(t1,"t1");
	
	unsigned int ls2 = getLeftOfKey(t1);
	ls2 = circularShift5Bits(ls2);
	ls2 = circularShift5Bits(ls2);

	////printIntDetails(ls2,"ls2");

	unsigned int rs2 = getRightOfKey(t1);
	rs2 = circularShift5Bits(rs2);
	rs2 = circularShift5Bits(rs2);

	////printIntDetails(rs2, "rs2");

	p8 = halfKeysToKey(ls2, rs2);

	////printCharDetails(p8, "k2");

	unsigned int k2 = p8;

	/*-----------------------------------------------------------------------*/

	unsigned char ep2 = EpPerm(r1 << 4);

	////printCharDetails(ep2, "ep2");

	unsigned char  xorRes_2 = ep2 ^ k2;

	////printCharDetails(xorRes_2, "xorRes_2");


	unsigned char p41_2 = findSBOX1(xorRes_2, sbox1);

	////printCharDetails(p41_2, "p41_2");


	unsigned char p42_2 = findSBOX2(xorRes_2, sbox2);

	////printCharDetails(p42_2, "p42_2");

	unsigned char p4_2 = createP4(p41_2, p42_2);

	////printCharDetails(p4_2, "p4_2");

	unsigned char xorRes2_2 = p4_2 ^ l1;

	////printCharDetails(xorRes2_2, "xorRes2_2");

	unsigned char final_plaintext = finalPerm(xorRes2_2, r1);

	////printCharDetails(final_plaintext,"final_plaintext");

	return final_plaintext;
}

int checkInput(char a[], int len) {
	int i = 0;
	for (i = 0; i < len; i++) {
		if (a[i] != '0' && a[i] != '1') return 0;
	}
	if (a[len] != '\0') return 0;
	return 1;
}
int main(int argc, char* argv[]) {

	/*
	char* plaintext = "01010001";

	char* key = "0101001100";
	*/

	if (argc <= 1) {
		unsigned char final = encrypt("01010001", "0101001100");

		printf("you put : %s \nyou put : %s  \n\n",
			   "01010001", "0101001100");

		printf("\n------------------------------------------------------------------------\n");
		
		printCharDetails(final, "final_encrypted");
		

	}
	else if (argc == 3) {

		printf("you put : %s \nyou put : %s  \ncorrect : %d \ncorrect : %d \n\n",
			   argv[1], argv[2], checkInput(argv[1], 8), checkInput(argv[2], 10));

		if (!(checkInput(argv[1], 8)) || !(checkInput(argv[2], 10))) {

			printf("\n\nyou did not insert correct stuff, see above .. soo i am executing the default one \n\n");
			unsigned char final = encrypt("01010001", "0101001100");
			printf("\n------------------------------------------------------------------------\n");
			printCharDetails(final, "final_encrypted");
			exit(0);
		}
		printf("\n------------------------------------------------------------------------\n");
		unsigned char final = encrypt(argv[1], argv[2]);
		printCharDetails(final, "final_encrypted");

	}
	else {
		printf("\n\nToo many or few arguments, so i am exiting \n\n");
	}


}
