
SYSEXIT=1
EXIT_SUCCESS=0
.section .data
#len=100		#set length of array
.section .text

.globl add_sisd
.type add_sisd,@function

add_sisd:
pushl %ebp
movl %esp,%ebp
movl 8(%ebp),%eax       #first argument ->array pointer
movl 12(%ebp),%ebx      #secound array pointer
movl $3,%edi		#counter for 4 repetitions

mov $0,%ecx

adding:
movl (%eax,%ecx,4),%edx 
movl (%ebx,%ecx,4),%esi 
addl %edx,%esi 	#add

movl %esi,(%eax,%ecx,4)
inc %ecx        #increment counter
cmp %ecx,%edi   #check if finished
je exit
jmp adding



.globl sub_sisd
.type sub_sisd,@function

sub_sisd:
pushl %ebp
movl %esp,%ebp
movl 8(%ebp),%edx       #first argument ->array pointer
movl 12(%ebp),%esi      #secound array pointer
movl $3,%edi            #counter for 4 repetitions

movl $0,%ecx

subtr:
movl (%edx,%ecx,4),%eax 
movl (%esi,%ecx,4),%ebx  
subl %eax,%ebx  #add
movl %eax,(%edx,%ecx,4)
inc %ecx        #increment counter
cmp %ecx,%edi   #check if finished
je exit
jmp subtr


.globl mul_sisd
.type mul_sisd,@function

mul_sisd:
pushl %ebp
movl %esp,%ebp
movl 8(%ebp),%edx       #first argument ->array pointer
movl 12(%ebp),%esi      #secound array pointer
movl $3,%edi            #counter for 4 repetitions

movl $0,%ecx

mult:
cmp $1,%ecx
jae pop_mul
jmp continue_mul

pop_mul:
popl %edx

continue_mul:
movl (%edx,%ecx,4),%eax
movl (%esi,%ecx,4),%ebx
pushl %edx  
mull %ebx  #add
inc %ecx        #increment counter
cmp %ecx,%edi   #check if finished
je exit
jmp mult

.globl div_sisd
.type div_sisd,@function

div_sisd:
pushl %ebp
movl %esp,%ebp
movl 8(%ebp),%edx       #first argument ->array pointer
movl 12(%ebp),%esi      #secound array pointer
movl $3,%edi            #counter for 4 repetitions

movl $0,%ecx

divide:

cmp $1,%ecx
jae popek
jmp continuation

popek:
popl %edx

continuation:

movl (%edx,%ecx,4),%eax 
movl (%esi,%ecx,4),%ebx  
pushl %edx
xor %edx,%edx
divl %ebx  	
inc %ecx        #increment counter
cmp %ecx,%edi   #check if finished
je exit
jmp divide


exit:
movl %ebp,%esp
popl %ebp
ret 



