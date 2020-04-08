#include<stdint.h>
long long getFingerPrint(unsigned char atom[4]){
	int count[13] = {0};
	count[atom[0] - 1] ++;
	count[atom[1] - 1] ++;
	count[atom[2] - 1] ++;
	count[atom[3] - 1] ++;
	
	long long fingerPrint = 0LL;    //64bits
	for(int i = 0 ; i < 13 ; i++){
		#ifdef DEBUG
		printf("\n%d", count[i]);
		#endif
		fingerPrint <<= 3;
		fingerPrint ^= (count[i] & 7);  //最大可表示4
	}
	return fingerPrint;
}
