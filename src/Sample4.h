/*

UpDown:   (atom[0] ope[0] (atom[1] ope[1] atom[2])) ope[2] atom[3] = 24



			atom[0]
			ope[0] = r2
	atom[1]
	ope[1]  = r1
	atom[2]
					ope[2]	= 24
					atom3

    只考虑：
	(a - (b * c)) ? d(注意b>=c)	或	(a - (b / c)) ? d   (若? = +,则a >= d)
	
	(a / (b - c)) ? d	或	(a / (b + c)) ? d(注意b>=c) 
		//(若? = *,则a >= d)	遗漏了 (10 / (1 + 4)) * 12的情况
		
	注意:
		?不为 - 或 / ,因为 a不能大于 13，- 或 / 之后只能更小，如果第3个符号为 - 或 / 则不够 24
	*/

//输入r，填充ope[2]，atom[3]
//ope[2]不为 - 或 /
void _Calculate(int r){
	if(1 >= r)  return ;    //肯定无解
	
	for(int i = 2; i < 14; i++){
		atom[3] = i;
		if(r + i == 24){
			ope[2] = '+';
			//若ope[0] = - ,此时考虑atom[0]  >= atom[3]
			if('-' == ope[0]){
				if(atom[0] >= atom[3])  Count();
			}else Count();
		}
		if(r * i == 24){
			ope[2] = '*';
			//若ope[0] = /
			//此时考虑	atom[0] >= atom[3]
			//		||	(atom[3] > atom[0] && atom[3] % (atom[1] +- atom[2]) != 0)
			if('/' == ope[0]){
				if(atom[0] >= atom[3])  Count();
				
				int _atom1_2 = ('+' == ope[1] ? atom[1] + atom[2] : atom[1] - atom[2]);
				if(atom[3] > atom[0] && (atom[3] % _atom1_2) != 0)    Count();
			}else Count();
		}
	}
}

void Sample4(){
	
	mode = UpDown;
	
	ope[0] = '-';
	//(a - (b * c)) ? d(注意b>=c)	或	(a - (b / c)) ? d   (若? = +,则a >= d)
	//此时atom[0]>=3
	for(int i = 3; i < 14; i++){
		atom[0] = i;

		ope[1] = '*';
		for(int j = 1; j < i; j++){
			atom[1] = j;
			
			for(int k = 1; k <= j; k++){
				if(i <= j * k)	break;  //随着k的增大，后面肯定不符合
				atom[2]= k;	//此时atom[1] >= atom[2]【j >= k】
				
				//继续填充ope[2],atom[3]
				_Calculate(atom[0] - atom[1] * atom[2]);
			}
		}
		
		ope[1] = '/';
		for(int j = 1; j < 14; j++){
			atom[1] = j;
			for(int k = 1; k <= j; k++){
				if(j % k == 0 && i > (j / k)){
					atom[2] = k;
					
					//继续填充ope[2],atom[3]
					_Calculate(atom[0] - atom[1] / atom[2]);
				}
			}
		}
	}
	
	ope[0] = '/';
	//(a / (b - c)) ? d	或	(a / (b + c)) ? d(注意b>=c) 
	//(若? = *,则a >= d)	则遗漏了 (10 / (1 + 4)) * 12的情况
	for(int i = 2; i < 14; i++){
		atom[0] = i;
		
		ope[1] = '-';
		for(int j = 2; j < 14; j++){
			atom[1] = j;
			
			for(int k = 1; k < j; k++){
				atom[2] = k;
				if(atom[0] % (atom[1] - atom[2]) == 0){
					//继续填充ope[2],atom[3]
					_Calculate(atom[0] / (atom[1] - atom[2]));
				}
				
			}
		}
		
		ope[1] = '+';
		for(int j = 1; j < 14; j++){
			atom[1] = j;
			
			for(int k = 1; k <= j; k++){
				atom[2] = k;    //此时atom[1] >= atom[2]
				
				if(atom[0] % (atom[1] + atom[2]) == 0){
					//继续填充ope[2],atom[3]
					_Calculate(atom[0] / (atom[1] + atom[2]));
				}
			}
		}
	}
}
