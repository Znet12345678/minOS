/*
*broken functions
*Public Domain
*Zachary Schlotman
*/
void msleep(unsigned long time){
	int mtime = time * 10000;
	for(int i = 0; i < mtime; i++)
		;
}
void sleep(unsigned long time){
	int stime = time * 25000000;
	for(int i = 0; i < time;i++)
		inb(0x1FC);
}
