
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Vector{
   int w;
   int x;
   int y;
   int z;
} vec1,vec2;
enum Operations_simd {ADD,SUB,MUL,DIV};

void set_vec();

void add_simd();
void sub_simd();
void div_simd();
void mul_simd();

void operation(int amount,int operation);
int rand_generator();

void initialize_file(int);
void write_file(char,double);
void delete_file();

int main(void){
   srand(time(0));
   enum Operations_simd operation_type;
   int numbers[3]={2048,4096,8192};

   delete_file(); //delete every time we run a program
   for(int i=0;i<3;i++){
	initialize_file(numbers[i]);
	operation_type=ADD;
        operation(numbers[i],operation_type);
	operation_type=SUB;
	operation(numbers[i],operation_type);
	operation_type=MUL;
	operation(numbers[i],operation_type);
	operation_type=DIV;
	operation(numbers[i],operation_type);
   }
}
int rand_generator(){
   return rand()%100+1;
}
void set_vec(){
    vec1.w=rand_generator();
    vec1.x=rand_generator();
    vec1.y=rand_generator();
    vec1.z=rand_generator();

    vec2.w=rand_generator();
    vec2.x=rand_generator();
    vec2.y=rand_generator();
    vec2.z=rand_generator();

}

void operation(int amount,int operation_type){
    int times=10;
    clock_t total_time=0;
    char sign;
for(int i=0;i<times;i+=1){
    
    clock_t start=clock();
    for(int j=0;j<amount;j++){	
	 if(operation_type==0){
		set_vec();
        	add_simd();
		sign='+';
   	 }

   	 else if(operation_type==1){
		set_vec();
        	sub_simd();
		sign='-';
   	 }
   	 else if(operation_type==2){
		set_vec();
		mul_simd();
		sign='*';
   	 }
   	 else if(operation_type==3){
		set_vec();
		div_simd();
		sign=':';
 	 }
    }
    clock_t stop=clock();
    total_time+=(stop-start);
}
double avg_time=((double)(total_time/times))/(CLOCKS_PER_SEC/1000);

printf("vec  %d",vec1);
 
printf("Time %f\n",avg_time);
write_file(sign,avg_time);
}
void initialize_file(int amount){
   FILE *fp;
   fp=fopen("result.txt","a"); //append
   if(fp==NULL){
   	printf("Can't open the file");
   }
   fprintf(fp,"Typ obliczen: simd\n");
   fprintf(fp,"Liczba liczb: %d\n",amount);
   fprintf(fp,"Sredni czas\n:");
   fclose(fp);

}
void write_file(char sign,double time){
   FILE *fp;
   fp=fopen("result.txt","a");
   if(fp==NULL){
	printf("can't open file to append");
   }
   fprintf(fp,"%c%f\n",sign,time);
   fclose(fp);
}
void delete_file(){
   FILE *fp;
   fp=fopen("result.txt","w+"); //opening file and clearing
   fclose(fp);
}

void add_simd(){
   
   __asm("movups vec1,%xmm0;"
		"movups vec2,%xmm1;"
		"subps %xmm0,%xmm1;"
		"movups %xmm1,vec1");

}
void sub_simd(){
   __asm("movups vec1,%xmm0;"
                "movups vec2,%xmm1;"
                "addps %xmm0,%xmm1;"
                "movups %xmm1,vec1");

}
void mul_simd(){
   __asm("movups vec1,%xmm0;"
                "movups vec2,%xmm1;"
                "mulps %xmm0,%xmm1;"
                "movups %xmm1,vec1");

}
void div_simd(){
   __asm("movups vec1,%xmm0;"
                "movups vec2,%xmm1;"
                "divps %xmm0,%xmm1;"
                "movups %xmm1,vec1");

}

