all : sr

CC = gcc

CFLAGS = -g -Wall -std=c99 -D_DEBUG_ -D_GNU_SOURCE

LIBS= -lm -lpthread

# Add any header files you've added here
sr_HDRS = sr.h sr_forward.h sr_protocol.h sr_if.h sr_rt.h sr_router.h sr_arp.h sr_resource.h

# Add any source files you've added here
sr_SRCS = sr.c sr_forward.c sr_rt.c sr_arp.c sr_resource.c

sr_OBJS = $(patsubst %.c,%.o,$(sr_SRCS))

$(sr_OBJS) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

sr : $(sr_OBJS)
	$(CC) $(CFLAGS) -o sr $(sr_OBJS) $(LIBS) 


clean:
	rm -f *.o  sr