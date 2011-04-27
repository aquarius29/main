#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mov_interface.h"

void PrintMatrix3x3 (float ar[][3], int row);
void PrintMatrix3x1 (float ar[][1], int row);


void Matrix_3Mult3(float a1[][3], float a2[][3], float a3[][3] );
void Matrix_3Mult1(float m1[][3], float m2[][1], float answer[][1]);

void rotationMatrix(float roll, float pitch, float yaw, float rotation_matrix[][3]);

void transposeMatrix3x3(float rotation_matrix[][3], float transpose_rotation_matrix[][3]);
void transposeMatrix3x1(float matrix1[][3],float matrix2[][1]);//tested

void MatrixScale3x1(float s, float matrix[][1],float newMatrix[][1], int row);
void MatrixScale3x3(float s, float matrix[][3],float newMatrix[][3], int row);

void Matrix_1Add1(float m1[][1], float m2[][1], float answer[][1] );
void Matrix_1Minus1(float m1[][1], float m2[][1], float answer[][1]);

/* int main(void) */
/* { */
/* 	float m1[3][3] = {{4, 3, 1}, */
/* 					  {3, 2, 2}, */
/* 					  {3, 4, 2}}; */

/* 	float m2[3][3] = {{3, 3, 3}, */
/* 					  {2, 6, 2}, */
/* 					  {1, 1, 1}}; */

/* 	float m3[3][1]={{1}, */
/* 					{2}, */
/* 					{3}}; */

/* 	float answer1[3][1]={{0}, */
/* 						 {0}, */
/* 						 {0}}; */

/* 	float m4[1][3]={{1,2,3}}; */

/* 	float answer3[3][3] = {{0, 0, 0}, */
/* 						   {0, 0, 0}, */
/* 						   {0, 0, 0}}; */


/* 	Matrix_1Minus1(m3,m3,answer1); */
/* 	PrintMatrix3x1(answer1,3); */


    
/* 	return 0; */
/* } */

/*
 *         0     	1      	2 	 
 *   0 	[0][0] 	[0][1] 	[0][2]
 *   1 	[1][0] 	[1][1] 	[1][2]
 *   2 	[2][0] 	[2][1] 	[2][2]
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

/*
 * scale a 3x1 matrix
 */
void MatrixScale3x1(float s, float matrix[][1],float newMatrix[][1], int row) {
	int i;
	for (i=0;i<row;i++){
		newMatrix[i][0]=s*matrix[i][0];
	}
}


/*
 * scale a 3x3 matrix
 */
void MatrixScale3x3(float s, float matrix[][3],float newMatrix[][3], int row) {
	int i, j;
	for (i=0;i<row;i++){
		for (j=0;j<3;j++){
			newMatrix[i][j]=s*matrix[i][j];
		}
	}
}


/*
 * transpose a 3x3 matrix
 */
void transposeMatrix3x3(float rotation_matrix[][3], float transpose_rotation_matrix[][3]){

	int i;
	int j;
	int n=3;
	for (j=0;j<n; j++){
		for (i=0;i<n; i++){
			transpose_rotation_matrix[j][i]=rotation_matrix[i][j];
		}
	}
} 

/*
 * transpose a 1x3 matrix to a 3x1 matrix
 */
void transposeMatrix3x1(float matrix1[][3],float matrix2[][1]){
	int i=0;
	int n=3;
	for (i=0;i<n;i++){
		matrix2[i][0]=matrix1[0][i];
	}
}

/*
 * calculate the Addition of two 3x1 Matrix
 */
void Matrix_1Add1(float m1[][1], float m2[][1], float answer[][1] ){
	int i=0;
	int n =3;
	for (i =0; i<n; i++){
		answer[i][0]=m1[i][0]+m2[i][0];
	}
}

/*
 * calculate the Subtraction of two 3x1 Matrix
 */
void Matrix_1Minus1(float m1[][1], float m2[][1], float answer[][1] ){
	int i=0;
	int n =3;
	for (i =0; i<n; i++){
		answer[i][0]=m1[i][0]-m2[i][0];
	}
}


/*
 * calculate the multiplication of two 3x3 matrix
 */
void  Matrix_3Mult3(float m1[][3], float m2[][3], float answer[][3])
{
	int i, j, k;
	for(i = 0; i < 3; i++) { 
		for( j = 0; j < 3; j++) {
			for( k = 0; k < 3; k++) {
				answer[i][j] +=  m1[i][k] * m2[k][j];
			}
		}
	}
}


/*
 * calculate the multiplication of a 3x3 matrix with a 3x1 matrix
 */
void  Matrix_3Mult1(float m1[][3], float m2[][1], float answer[][1])
{
	int i, k;

	for(i = 0; i < 3; i++) { 
		for( k = 0; k < 3; k++) {
			answer[i][0] +=  m1[i][k] * m2[k][0];
		}
	}
}


/*
 * calculate the multiplication of a 3x1 matrix with a 3x3 matrix
 */
void Matrix_1Mult3(float m1[][1], float m2[][3], float answer[][3]){
	//it seems there's no such thing TT
}


/*
 * print a 3 column array
 */
void PrintMatrix3x3 (float answer[][3],int row)
{
    int i,j;
    for(i = 0; i < row; i++) {

		for( j = 0; j < 3; j++) {
			printf("%4.0f", answer[i][j]);
		}

		putchar('\n');
	}
}

/*
 * print a 1 column array
 */
void PrintMatrix3x1 (float answer[][1], int row)
{
    int i;
    for(i = 0; i < row; i++){
		printf("%4.0f\n", answer[i][0]);
	}
}
