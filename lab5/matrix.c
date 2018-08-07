#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void read_matrix(int n,int m,float mat[n][m]);

void set_vector();

void print_matrix();


typedef struct mat_vector{
	float x;
	float y;
	float z;
	float w;
}vector;

vector vec[3];


void count_det(vector ,vector , vector , vector);

int main(void){
   	float mat[4][4];
	int n=4,m=4;
	read_matrix(n, m,mat);
	print_matrix(n,m,mat);
	count_det(vec[0],vec[1],vec[2],vec[3]);	
	
}
void set_vector(int vecnum,int index,int value){
	if(index==0){
		vec[vecnum].x=value;
	}
	else if(index==1){
		vec[vecnum].y=value;
	}
	else if(index==2){
		vec[vecnum].z=value;
	}
	else if(index==3){
		vec[vecnum].w=value;
	}
}

void read_matrix(int n,int m,float mat[n][m]){
    
    
    printf("type values of matrix\n");
    char enter;
    bool valid=true;
    for(int i=0;i<4;i++){
     
    	for (int j=0;j<4;j++){
	    if(valid==true){

	        printf("Matrix [%d] [%d]",i,j);
	        if(scanf("%f%c",&mat[i][j],&enter)!=2 || enter !='\n'){
	            printf("\nPass only numeric values!");
		    valid=false;
	            break;
	        }
	       
	    }
	    else 
 	        break;


	    set_vector(i,j,mat[i][j]);

	}

    }
}

void print_matrix(int n,int m,float mat[n][m]){
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			printf(" %f",mat[i][j]);
			
		}
		printf("\n");
	 
	}
}

void count_det(vector vec1,vector vec2,vector vec3,vector vec4){


	vector result={0};
	
	
	asm(
		"movups %1, %%xmm0 \n" //load vec1 to first xmm register a3 a2 a1 a0
		"movups %2, %%xmm1 \n" //b3 b2 b1 b0 
		

		"shufps $0x48 , %%xmm0,%%xmm0 \n" //a1 a0 a2 a0
		"shufps $0xb1 , %%xmm1,%%xmm1 \n" //b2 b3 b0 b1
		"mulps %%xmm0,%%xmm1\n"    // multiply vectors  // a0*b1 // a2*b0 ...


		"movups %1, %%xmm0 \n" //reset xmm0 with a
		"movups %2, %%xmm2 \n" //set xmm2 with b, in xmm1 we store result 
		
		"shufps $0xb1 , %%xmm0,%%xmm0 \n" //a2 a3 a0 a1
		"shufps $0x48 , %%xmm2,%%xmm2 \n" //b1 b0 b2 b0
		"mulps %%xmm0,%%xmm2\n" 
		
		"subps %%xmm1,%%xmm2\n" //subtract //half line result


		"movups %3, %%xmm1 \n"// c3 c2 c1 c0
		"movups %4, %%xmm3 \n"//d3 d2 d1 d0
						
		"shufps $0x16 , %%xmm1,%%xmm1 \n" //c0 c1 c1 c2
		"shufps $0xef , %%xmm3,%%xmm3 \n" //d3 d2 d3 d3
		"mulps %%xmm1,%%xmm3\n" 

		"movups %3, %%xmm1 \n"// reset c
		"movups %4, %%xmm4 \n"//reset d

		"shufps $0xef , %%xmm1,%%xmm1 \n" //c3 c2 c3 c3
		"shufps $0x16 , %%xmm4,%%xmm4 \n" //d0 d1 d1 d2
		"mulps %%xmm1,%%xmm4\n" 

		"subps %%xmm3,%%xmm4\n" //subtract //

		/*----------------------------------------------*/ 
		"mulps %%xmm2,%%xmm4\n" //multiply results // complete line for first 4 rows
		/* ---------- */
		"movups %1, %%xmm0 \n" //a
		"movups %2, %%xmm1 \n" //b
		
		"shufps $0xe , %%xmm0,%%xmm0 \n"  //a3 a2
		"shufps $0x7 , %%xmm1,%%xmm1 \n"  //b1 b3

		"mulps %%xmm0,%%xmm1\n"	

		"movups %1, %%xmm0 \n" //a
		"movups %2, %%xmm2 \n" //b

		"shufps $0x7 , %%xmm0,%%xmm0 \n"  //a1 a3
		"shufps $0xe , %%xmm2,%%xmm2 \n"  //b3 b2
		
		"mulps %%xmm0,%%xmm2\n"

		"subps %%xmm1,%%xmm2\n"  //subtract

		
		"movups %3, %%xmm0 \n" //c
		"movups %4, %%xmm1 \n" //d
		
		"shufps $0x0 , %%xmm0,%%xmm0 \n"  //c0 c0
		"shufps $0x9 , %%xmm1,%%xmm1 \n"  //d2 d1

		"mulps %%xmm0,%%xmm1\n"

		"movups %3, %%xmm0 \n" //c
		"movups %4, %%xmm3 \n" //d

		"shufps $0x9 , %%xmm0,%%xmm0 \n"  //c2 c1
		"shufps $0x0 , %%xmm3,%%xmm3 \n"  //d0 d0

		"mulps %%xmm0,%%xmm3\n"

		"subps %%xmm1,%%xmm3\n" //subtract

		/* ----------------- */
		"mulps %%xmm2,%%xmm3\n"
		
		"addps %%xmm4,%%xmm3\n"

		"movups %%xmm3, %0 \n" //result
		:"=g"(result)
		:"g"(vec1),"g"(vec2),"g"(vec3),"g"(vec4)
		);

		printf("%f %f %f %f",result.x,result.y,result.z,result.w);

		float final_result = result.x + result.y + result.z + result.w;

		printf("\n DET=%f",final_result);
}


