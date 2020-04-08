
void Sample1(){
	mode = Cross;
	//Cross:    (atom[0] ope[0]  atom[1]) ope[1] (atom[2] ope[2] atom[3]) = 24
	//r1 = (atom[0] ope[0]  atom[1])
	//r2 = (atom[2] ope[2] atom[3])

	//中间为 * 或 /,两边为 + -
	ope[1] =  '*';
	//保证r1 < r2
	for(int i = 1 ; i < 5 ; i++){
		
		if(24 % i == 0){
			//可整除
			r1 = i, r2 = 24 / i;    //r1 = 1,2,3,4 , r2 = 24, 12, 8, 6

			ope[0] = '+';
			for(int j = 1; j <= r1 / 2; j++){
				atom[0] = j, atom[1] = r1 - j;

				ope[2] = '+';
				for(int k = 1; k <= r2 / 2; k++){
					atom[2] = k, atom[3] = r2 - k;
					if(r2 - k > 13) continue;
					//写入该样例
					Count();
				}

				ope[2] = '-';
				for(int k = 13; k > r2 ; k--){
					atom[2] = k, atom[3] = k - r2;
					//写入该样例
					Count();
				}

			}

			ope[0] = '-';
			for(int j = 13; j > r1; j--){
				atom[0] = j, atom[1] = j - r1;

				ope[2] = '+';
				for(int k = 1; k <= r2 / 2 ; k++){
					atom[2] = k, atom[3] = r2 - k;
					if(r2 - k > 13) continue;
					//写入该样例
					Count();
				}

				ope[2] = '-';
				for(int k = 13; k > r2 ; k--){
					atom[2] = k, atom[3] = k - r2;
					//写入该样例
					Count();
				}

			}
		}
	}

	ope[1] =  '/';
	//只可能是 24 / 1
	r1 = 24, r2 = 1;

	ope[0] = '+';
	for(int j = 1; j <= 12; j++){
		atom[0] = j, atom[1] = 24 - j;
		if(24 - j > 13) continue;

		ope[2] = '-';
		for(int k = 13; k > 1 ; k--){
			atom[2] = k, atom[3] = k - 1;
			//写入该样例
			Count();
		}

	}


}



