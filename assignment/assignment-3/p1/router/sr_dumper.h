/** 
 * This header file defines data structures for logging packets in tcpdump
 * format as well as a set of operations for logging.
 */


#ifdef _LINUX_
#include <stdint.h>
#endif /* _LINUX_ */

#ifdef _DARWIN_
#include <inttypes.h>
#endif /* _DARWIN_ */

#include <sys/time.h>

#define PCAP_VERSION_MAJOR 2
#define PCAP_VERSION_MINOR 4
#define PCAP_ETHA_LEN 6
#define PCAP_PROTO_LEN 2

#define TCPDUMP_MAGIC 0xa1b2c3d4

#define LINKTYPE_ETHERNET 1

#define min(a,b) ( (a) < (b) ? (a) : (b) )

/* file header */
struct pcap_file_header {
  uint32_t   magic;         /* magic number */
  uint16_t version_major; /* version number major */
  uint16_t version_minor; /* version number minor */
  int     thiszone;      /* gmt to local correction */
  uint32_t   sigfigs;       /* accuracy of timestamps */
  uint32_t   snaplen;       /* max length saved portion of each pkt */
  uint32_t   linktype;      /* data link type (LINKTYPE_*) */
};

/* packet header */
struct pcap_pkthdr {
  struct timeval ts;     /* time stamp  */
  uint32_t caplen;          /* length of portion present */
  uint32_t len;             /* length this packet (off wire) */
};

/*
 * This is a timeval as stored in disk in a dumpfile.
 * It has to use the same types everywhere, independent of the actual
 * `struct timeval'
 */
struct pcap_timeval {
    int tv_sec;           /* seconds */
    int tv_usec;          /* microseconds */
};


/*
 * How a `pcap_pkthdr' is actually stored in the dumpfile.
 */
struct pcap_sf_pkthdr {
    struct pcap_timeval ts;     /* time stamp */
    uint32_t caplen;         /* length of portion present */
    uint32_t len;            /* length this packet (off wire) */
};

/**
 * Open a dump file and initialize the file.
 */
FILE* sr_dump_open(const char *fname, int thiszone, int snaplen);

/**
 * Write data into the log file
 */
void sr_dump(FILE *fp, const struct pcap_pkthdr *h, const unsigned char *sp);

/**
 * Close the file
 */
void sr_dump_close(FILE *fp);
