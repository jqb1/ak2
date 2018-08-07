EXIT_SUCCESS=0
SYSEXIT=1

.data

num1:
    .long 0xF0304001, 0x70110011, 0x45100020, 0x08570030
num2:
    .long 0x1040500C, 0x00220026, 0x32100021, 0x01520031
len=4
.text

.global _start

_start:
clc 
pushf
mov $len,%eax
mov $len,%ebx

clc
pushf
add_loop:
clc
popf

decl %eax
decl %ebx
movl num1(,%eax,4),%ecx
movl num2(,%ebx,4),%edx
adc %ecx,%edx
pushl %edx
pushf

cmp $0,%eax
je exit
jmp add_loop

add_carrier:
mov $0,%ecx
adc %ecx,%ecx
push %ecx
clc
pushf

exit:
clc
popf
jc add_carrier

mov $SYSEXIT,%eax
mov $EXIT_SUCCESS,%ebx
int $0x80
