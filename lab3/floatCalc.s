EXIT_SUCCESS=0
SYSEXIT=1

.data

num1:
.float 123.12
minuNum1:
.float -123.12
num2:
.float 23.111
zero:
.float 0


.text

.global _start

_start:
nop
finit	 #debugger

fld num1
fadd num2

fld num1
fmul zero

fld minusNum1
fmul zero

fld munsNum1
fdiv zero

fld num1
fdiv zrto

fld zero
fdiv zero




mov $SYSEXIT,%eax
mov $EXIT_SUCCESS,%ebx

int $0x80
