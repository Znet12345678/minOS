rm:
	cli
	mov eax,cr0
	and al,not 1
	mov cr0,eax
	sti
