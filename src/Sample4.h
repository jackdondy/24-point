/*

UpDown:   (atom[0] ope[0] (atom[1] ope[1] atom[2])) ope[2] atom[3] = 24



			atom[0]
			ope[0] = r2
	atom[1]
	ope[1]  = r1
	atom[2]
					ope[2]	= 24
					atom3

    ֻ���ǣ�
	(a - (b * c)) ? d(ע��b>=c)	��	(a - (b / c)) ? d   (��? = +,��a >= d)
	
	(a / (b - c)) ? d	��	(a / (b + c)) ? d(ע��b>=c) 
		//(��? = *,��a >= d)	��©�� (10 / (1 + 4)) * 12�����
		
	ע��:
		?��Ϊ - �� / ,��Ϊ a���ܴ��� 13��- �� / ֮��ֻ�ܸ�С�������3������Ϊ - �� / �򲻹� 24
	*/

//����r�����ope[2]��atom[3]
//ope[2]��Ϊ - �� /
void _Calculate(int r){
	if(1 >= r)  return ;    //�϶��޽�
	
	for(int i = 2; i < 14; i++){
		atom[3] = i;
		if(r + i == 24){
			ope[2] = '+';
			//��ope[0] = - ,��ʱ����atom[0]  >= atom[3]
			if('-' == ope[0]){
				if(atom[0] >= atom[3])  Count();
			}else Count();
		}
		if(r * i == 24){
			ope[2] = '*';
			//��ope[0] = /
			//��ʱ����	atom[0] >= atom[3]
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
	//(a - (b * c)) ? d(ע��b>=c)	��	(a - (b / c)) ? d   (��? = +,��a >= d)
	//��ʱatom[0]>=3
	for(int i = 3; i < 14; i++){
		atom[0] = i;

		ope[1] = '*';
		for(int j = 1; j < i; j++){
			atom[1] = j;
			
			for(int k = 1; k <= j; k++){
				if(i <= j * k)	break;  //����k�����󣬺���϶�������
				atom[2]= k;	//��ʱatom[1] >= atom[2]��j >= k��
				
				//�������ope[2],atom[3]
				_Calculate(atom[0] - atom[1] * atom[2]);
			}
		}
		
		ope[1] = '/';
		for(int j = 1; j < 14; j++){
			atom[1] = j;
			for(int k = 1; k <= j; k++){
				if(j % k == 0 && i > (j / k)){
					atom[2] = k;
					
					//�������ope[2],atom[3]
					_Calculate(atom[0] - atom[1] / atom[2]);
				}
			}
		}
	}
	
	ope[0] = '/';
	//(a / (b - c)) ? d	��	(a / (b + c)) ? d(ע��b>=c) 
	//(��? = *,��a >= d)	����©�� (10 / (1 + 4)) * 12�����
	for(int i = 2; i < 14; i++){
		atom[0] = i;
		
		ope[1] = '-';
		for(int j = 2; j < 14; j++){
			atom[1] = j;
			
			for(int k = 1; k < j; k++){
				atom[2] = k;
				if(atom[0] % (atom[1] - atom[2]) == 0){
					//�������ope[2],atom[3]
					_Calculate(atom[0] / (atom[1] - atom[2]));
				}
				
			}
		}
		
		ope[1] = '+';
		for(int j = 1; j < 14; j++){
			atom[1] = j;
			
			for(int k = 1; k <= j; k++){
				atom[2] = k;    //��ʱatom[1] >= atom[2]
				
				if(atom[0] % (atom[1] + atom[2]) == 0){
					//�������ope[2],atom[3]
					_Calculate(atom[0] / (atom[1] + atom[2]));
				}
			}
		}
	}
}
