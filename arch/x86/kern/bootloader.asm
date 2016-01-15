section .bootsig
int 0x55
int 0xAA
section .text
global _start
extern Start
extern realmode
_start:
	;call realmode
	mov edx,len
	mov ecx,msg
	mov ebx,1
	mov eax,4
	;int 0x80
	call Start

section .data
	msg db 'Loading...'
	len equ $ - msg
times 510 - ( $ - $$ ) db 0
dw 0xaa55
