void Sample2(){
	mode = Cross;
	//Cross:    (atom[0] ope[0]  atom[1]) ope[1] (atom[2] ope[2] atom[3]) = 24
	//r1 = (atom[0] ope[0]  atom[1])
	//r2 = (atom[2] ope[2] atom[3])
	
	/*�м�Ϊ + -�� ����Ϊ * /
	��������Ϊ 12 + 12ʱ���涨��
	    ������  * + / ;
	    ���Ϊ a * b + c * d:   a >= c
        ���Ϊ a / b + c / d:   ��������(��Ϊ��ʱֻ�� 12 / 1 + 12 / 1һ�����)
    �����޳���
		3 * 4 + 12 / 1
		2 * 6 + 12 / 1
		1 * 12 + 12 / 1
		
		1 * 12 + 2 * 6
		1 * 12 + 3 * 4
		2 * 6 + 3 * 4
	*/
	ope[1] = '+';
	
	for(int i = 1; i <= 12 ; i++){
		if(24 - i > 13) continue;
		r1 = i, r2 = 24 - i;
		
		//1 <= r1 <= 12, 12 <= r2 <= 23
		ope[0] = '*';
		for(int j = 1; j < r1 ; j++){
			if(j > r1 / j)  break;  //��֤r1 < r2
			if(r1 % j == 0){
				atom[0] = j, atom[1] = r1 / j;
				
				//12 <= r2 <= 23
				ope[2] = '*';
				for(int k = 1; k < r2; k ++){
					if(k > r2 / k)  break;
					if(r2 % k == 0 && r2 / k < 14){
						atom[2] = k, atom[3] = r2 / k;
						
						if(12 == r1 && atom[2] > atom[0])   continue;
						
						Count();
					}
				}
				
				if(12 == r1)    continue;   //��ʱ������ * + /;
				
				ope[2] = '/';
				//ֻ�� 13 / 1 �� 12 / 1
				if(r2 < 14){
					atom[2] = r2, atom[3] = 1;
					Count();
				}
				
			}
		}
		
		//1 <= r1 <= 12
		ope[0] = '/';
		for(int j = 13 ; j >= r1 ; j--){
			// j / () = r1
			if(j % r1 == 0){
				atom[0] = j, atom[1] = j / r1;
				
				//12 <= r2 <= 23
				ope[2] = '*';
				for(int k = 1; k < r2 ; k ++){
					if(k > r2 / k)  break;
					if(r2 % k == 0 && r2 / k < 14){
						atom[2] = k, atom[3] = r2 / k;
						Count();
					}
				}

				ope[2] = '/';
				//ֻ�� 13 / 1 �� 12 / 1
				if(r2 < 14){
					atom[2] = r2, atom[3] = 1;
					Count();
				}
			}
		}
	}
}
