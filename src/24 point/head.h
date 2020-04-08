/*
ͷ�ļ�

*/

typedef enum{
	Cross, Straight, UpDown
}Mode;
typedef struct{
	Mode mode;
	unsigned char atom[4], ope[3];
}Sample;
/*
Cross:	(atom[0] ope[0]  atom[1]) ope[1] (atom[2] ope[2] atom[3]) = 24

	atom[0]
	ope[0]  = r1
	atom[1]
			ope[1]  = 24
	atom[2]
	ope[2]  = r2
	atom[3]
	
    ֻ���ǣ�
	(a + b) * (c - d)
	a * b + c / d

Straight:  ( (atom[0] ope[0] atom[1]) ope[1] atom[2] ) ope[2] atom[3] = 24

	atom[0]
	ope[0]  = r1
	atom[1]
			ope[1]  = r2
			atom[2]
					ope[2]  = 24
					atom[3]
					
UpDown:   (atom[0] ope[0] (atom[1] ope[1] atom[2])) ope[2] atom[3] = 24

					
					  
			atom[0]
			ope[0] = r2
	atom[1]			
	ope[1]  = r1	
	atom[2]
					ope[2]	= 24
					atom3
					
    ֻ���ǣ�
	(a - (b * c)) ? d	��	(a - (b / c)) ? d
	(a / (b - c)) ? d	��	(a / (b + c)) ? d
*/


//#define Total 3807  //��

//#define indexTotal 1313
//
///*�Ѷȣ��� (ֻ��һ����)�� (2��3����)�� (4��������)*/
//#define high_level_begin 0
//#define high_level_total 446
//
//#define medium_level_begin 446
//#define medium_level_total 520
//
//#define low_level_begin 966
//#define low_level_total 347


#define Total 3824
Sample allSample[Total];

#define indexTotal 1323

/*�Ѷȣ��� (ֻ��һ����)�� (2��3����)�� (4��������)*/
#define high_level_begin 0
#define high_level_total 451

#define medium_level_begin 451
#define medium_level_total 525

#define low_level_begin 976
#define low_level_total 347