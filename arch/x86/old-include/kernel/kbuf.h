#ifndef __KBUF_H
#define __KBUF_H
#define KBUF_FLAGS_RW 0x0A
#define KBUF_FLAGS_RO 0x1A
#define KBUF_FLAGS_PUBLIC 0x2A
#define KBUF_FLAGS_PRIVATE 0x3A
struct kbuf{
	char *buffer;
	unsigned long len;
	int flags;
};
void request_kbuf(struct kbuf *kbuf);/*TODO*/
#endif
