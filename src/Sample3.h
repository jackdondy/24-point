/*//Straight:  [ (atom[0] ope[0] atom[1]) ope[1] atom[2] ] ope[2] atom[3] = 24

	(a + b - c) * d     //�޳�(a - c + b) * d֮��
	(a * b + c) * d
	a * b * c + d
	(a + b) * c - d
	(a + b) * c / d
	a * b + c + d           //
	a + b + c - d           //�� + - ������1��+,������+��-
	a * b / c * d           //�� * / ������1��*,������*��/
	*/
	
	/*
	��ֹ����˳�����������ظ���
		���ǰһ������Ϊ -���򲻳��� +;
		���ǰһ������Ϊ /���򲻳��� *;
	��ֹ������ͬ�����ֵ������ظ���
        ���������2��������ǰ�������� + �� *���������ܱȵ�1������;
        �������3�������4������
			��ǰ��������ǰǰ��������ͬ (ͬΪ + - * /)����������ܱ�ǰһ������;

	*/

//����ʽ�ӽ��

void calculate(){
	int sum = atom[0];
	for(int i = 0; i <= 2 ; i++){
		switch (ope[i]){
			case '/':
				if((sum % atom[i + 1]) != 0)    return ;//����/ʱ��ע���Ƿ�����
				sum /= atom[i + 1];
				break;
			case '*':
				sum *= atom[i + 1];
				break;
			case '-':
				sum -= atom[i + 1];
				if(sum < 0) return ;    //����-ʱ��ע�ⲻ��Ϊ��
				break;
			case '+':
				sum += atom[i + 1];
				break;
		}
	}
	if(24 == sum)   Count();
}

void get_num(int i);

//����i������������ope[i]
void get_ope(int i){
	if(i > 2){
		calculate();
		return ;
	}
	//�Ȳ鿴ǰһ���������Ƿ�Ϊ - /
	if(i > 0){
		if('-' == ope[i - 1]){
			//������+
			ope[i] = '-';
			get_num(i + 1);
			ope[i] = '*';
			get_num(i + 1);
			ope[i] = '/';
			get_num(i + 1);
			return ;
		}
		if('/' == ope[i - 1]){
			//������*
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


//����i����λ����atom[i]
//
void get_num(int i){
	if( ((1 == i) && ('+' == ope[0] || '*' == ope[0]))
		|| ((i >= 2) && (ope[i - 1] == ope[i - 2])) ){
		//���������ܳ���ǰһ����
		for(int j = 1; j <= atom[i - 1]; j++){
			atom[i] = j;
			get_ope(i);
		}
	}else{
		//�����Ϊ1~13
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
