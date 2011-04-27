#include <stdio.h>
#include <stdlib.h>
#include<math.h>

void Matrix_3Mult3(int a1[][3], int a2[][3], int a3[][3] );
void Matrix_3Mult1(int m1[][3], int m2[][1], int answer[][1]);
void PrintMatrix (int ar[][3]);
void PrintMatrix2 (int ar[][1]);

void rotationMatrix(float roll, float pitch, float yaw, float rotation_matrix[][3]);
void transposeMatrix3(float rotation_matrix[][3], float transpose_rotation_matrix[][3]);
void transposeMatrix1(float matrix1[3],float matrix2[][1]);
void Matrix_1Add1(float m1[][1], float m2[][1], float answer[][1] );

//http://www.edcc.edu/faculty/paul.bladek/Cmpsc142/matmult.htm
/* int main(void) */
/* { */
/* 	int m1[3][3] = {{4, 3, 1}, */
/* 					{3, 2, 2}, */
/* 					{3, 4, 2}}; */

/* 	int m2[3][3] = {{3, 3, 3}, */
/* 					{2, 2, 2}, */
/* 					{1, 1, 1}}; */

/* 	int m3[3][1]={{1}, */
/* 				  {2}, */
/* 				  {3}}; */

/* 	int answer1[3][1]={{0}, */
/* 					   {0}, */
/* 					   {0}}; */

/* 	int answer3[3][3] = {{0, 0, 0}, */
/* 						 {0, 0, 0}, */
/* 						 {0, 0, 0}}; */

/* 	Matrix_3Mult3(m1, m2, answer3); */
/* 	PrintMatrix(answer3); */
/* 	Matrix_3Mult1(m1, m3, answer1); */
/* 	PrintMatrix2(answer1); */
    
/* 	return 0; */
/* } */

/*
      0     	1      	2 	 
0 	[0][0] 	[0][1] 	[0][2]
1 	[1][0] 	[1][1] 	[1][2]
2 	[2][0] 	[2][1] 	[2][2]
 */



void rotationMatrix(float roll, float pitch, float yaw, float rotation_matrix[][3]){
	rotation_matrix[0][0]=cos(pitch)*cos(yaw);
	rotation_matrix[0][1]=cos(pitch)*sin(yaw);
	rotation_matrix[0][2]=-sin(pitch);
	rotation_matrix[1][0]=sin(yaw)*sin(pitch)*cos(yaw)-cos(roll)*sin(yaw);
	rotation_matrix[1][1]=cos(roll)*cos(yaw)+sin(roll)*sin(pitch)*sin(yaw);
	rotation_matrix[1][2]=sin(roll)*cos(pitch);
	rotation_matrix[2][0]=cos(roll)*sin(pitch)*cos(yaw)+sin(roll)*sin(yaw);
	rotation_matrix[2][1]=sin(pitch)*cos(roll)*sin(yaw)-sin(roll)*cos(yaw);
	rotation_matrix[2][2]=cos(pitch)*cos(roll);
}


void transposeMatrix3(float rotation_matrix[][3], float transpose_rotation_matrix[][3]){
	transpose_rotation_matrix[0][0]=rotation_matrix[0][0];
	transpose_rotation_matrix[0][1]=rotation_matrix[1][0];
	transpose_rotation_matrix[0][2]=rotation_matrix[2][0];
	transpose_rotation_matrix[1][0]=rotation_matrix[0][1];
	transpose_rotation_matrix[1][1]=rotation_matrix[1][1];
	transpose_rotation_matrix[1][2]=rotation_matrix[2][1];
	transpose_rotation_matrix[2][0]=rotation_matrix[0][2];
	transpose_rotation_matrix[2][1]=rotation_matrix[1][2];
	transpose_rotation_matrix[2][2]=rotation_matrix[2][2];
} 

void transposeMatrix1(float matrix1[3],float matrix2[][1]){
	matrix2[0][0]=matrix1[0];
	matrix2[0][1]=matrix1[1];
	matrix2[0][2]=matrix1[2];
}

void Matrix_1Add1(float m1[][1], float m2[][1], float answer[][1] ){
	int i=0; n =3;
	for (i =0; i<n; i++){
		answer[i][0]=m1[i][0]+m2[i][0];
	}

}




void  Matrix_3Mult3(int m1[][3], int m2[][3], int answer[][3])
{
	int i = 0;
	int j = 0;
	int k = 0;

	for(i = 0; i < 3; i++) { 
		for( j = 0; j < 3; j++) {
			for( k = 0; k < 3; k++) {
				answer[i][j] +=  m1[i][k] * m2[k][j];
			}
		}
	}
}


void  Matrix_3Mult1(int m1[][3], int m2[][1], int answer[][1])
{
	int i = 0;
	int k = 0;

	for(i = 0; i < 3; i++) { 
		for( k = 0; k < 3; k++) {
			answer[i][0] +=  m1[i][k] * m2[k][0];
		}
	}
}


void PrintMatrix (int answer[][3])
{
    int i = 0;
    int j = 0;
    for(i = 0; i < 3; i++)
		{
			for( j = 0; j < 3; j++)
				printf("%4d", answer[i][j]);
			putchar('\n');
		}
}


void PrintMatrix2 (int answer[][1])
{
    int i = 0;
    for(i = 0; i < 3; i++)
		{
			printf("%4d\n", answer[i][0]);
		}
}
