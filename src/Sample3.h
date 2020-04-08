/*//Straight:  [ (atom[0] ope[0] atom[1]) ope[1] atom[2] ] ope[2] atom[3] = 24

	(a + b - c) * d     //剔除(a - c + b) * d之类
	(a * b + c) * d
	a * b * c + d
	(a + b) * c - d
	(a + b) * c / d
	a * b + c + d           //
	a + b + c - d           //纯 + - 至少有1个+,规则：先+后-
	a * b / c * d           //纯 * / 至少有1个*,规则：先*后/
	*/
	
	/*
	防止符号顺序调换引起的重复：
		如果前一个符号为 -，则不出现 +;
		如果前一个符号为 /，则不出现 *;
	防止符号相同而数字调换的重复：
        如果是填充第2个数，若前操作符是 + 或 *，此数不能比第1个数大;
        如果填充第3个数或第4个数，
			若前操作符与前前操作符相同 (同为 + - * /)，则此数不能比前一个数大;

	*/

//计算式子结果

void calculate(){
	int sum = atom[0];
	for(int i = 0; i <= 2 ; i++){
		switch (ope[i]){
			case '/':
				if((sum % atom[i + 1]) != 0)    return ;//计算/时，注意是否整除
				sum /= atom[i + 1];
				break;
			case '*':
				sum *= atom[i + 1];
				break;
			case '-':
				sum -= atom[i + 1];
				if(sum < 0) return ;    //计算-时，注意不能为负
				break;
			case '+':
				sum += atom[i + 1];
				break;
		}
	}
	if(24 == sum)   Count();
}

void get_num(int i);

//填充第i个操作符，即ope[i]
void get_ope(int i){
	if(i > 2){
		calculate();
		return ;
	}
	//先查看前一个操作符是否为 - /
	if(i > 0){
		if('-' == ope[i - 1]){
			//不能填+
			ope[i] = '-';
			get_num(i + 1);
			ope[i] = '*';
			get_num(i + 1);
			ope[i] = '/';
			get_num(i + 1);
			return ;
		}
		if('/' == ope[i - 1]){
			//不能填*
			ope[i] = '+';
			get_num(i + 1);
			ope[i] = '-';
			get_num(i + 1);
			ope[i] = '/';
			get_num(i + 1);
			return ;
		}
	}
	ope[i] = '+';
	get_num(i + 1);
	ope[i] = '-';
	get_num(i + 1);
	ope[i] = '*';
	get_num(i + 1);
	ope[i] = '/';
	get_num(i + 1);
}


//填充第i个空位，即atom[i]
//
void get_num(int i){
	if( ((1 == i) && ('+' == ope[0] || '*' == ope[0]))
		|| ((i >= 2) && (ope[i - 1] == ope[i - 2])) ){
		//填充的数不能超过前一个数
		for(int j = 1; j <= atom[i - 1]; j++){
			atom[i] = j;
			get_ope(i);
		}
	}else{
		//填的数为1~13
		for(int j = 1; j < 14 ; j++){
			atom[i] = j;
			get_ope(i);
		}
	}
}

void Sample3(){
	mode = Straight;
	get_num(0);
}
