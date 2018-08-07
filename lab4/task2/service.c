
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Operations_simd {ADD,SUB,MUL,DIV};

int * set_array(int *);

extern void add_sisd(int *,int *);
extern void sub_sisd(int *,int *);
extern void div_sisd(int *,int *);
extern void mul_sisd(int *,int *);

void operation(int amount,int operation);
int rand_generator();

void initialize_file(int);
void write_file(char,double);
void delete_file();

int main(void){
   srand(time(NULL));
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
   return rand()%(100)+1;
}
int * set_array(int *tab){
 
   for(int i=0;i<=3;i++){
	tab[i]=rand_generator();   

   }
   return tab;
}

void operation(int amount,int operation_type){
    int times=10;
    clock_t total_time=0;
    char sign;
    
    int arr1[3];
    int arr2[3];
    int *arrptr1;
    int *arrptr2;
for(int i=0;i<times;i+=1){
    
    clock_t start=clock();
    for(int j=0;j<amount;j++){	
	 if(operation_type==0){
		arrptr1=set_array(arr1);
		arrptr2=set_array(arr2);
        	add_sisd(arrptr1,arrptr2);
		sign='+';
   	 }

   	 else if(operation_type==1){
		arrptr1=set_array(arr1);
		arrptr2=set_array(arr2);

		sub_sisd(arrptr1,arrptr2);
		sign='-';
		
   	 }
         else if(operation_type==2){
                arrptr1=set_array(arr1);
                arrptr2=set_array(arr2);
	
                mul_sisd(arrptr1,arrptr2);
                sign='*';

         }

         else if(operation_type==3){
                arrptr1=set_array(arr1);
                arrptr2=set_array(arr2);
                div_sisd(arrptr1,arrptr2);
                sign=':';
         }

    
    }
    clock_t stop=clock();
    total_time+=(stop-start);
}
double avg_time=(double)(total_time/times)/(CLOCKS_PER_SEC/1000);
printf("Time %f\n",avg_time);
write_file(sign,avg_time);
}
void initialize_file(int amount){
   FILE *fp;
   fp=fopen("result.txt","a"); //append
   if(fp==NULL){
   	printf("Can't open the file");
   }
   fprintf(fp,"Typ obliczen: sisd\n");
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


