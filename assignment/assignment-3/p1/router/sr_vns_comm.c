/*-----------------------------------------------------------------------------
 * File: sr_vns_comm.c
 * Date: Spring 2002
 * Authors: Guido Apanzeller, Vikram Vijayaraghaven, Martin Casado
 * Contact: casado@stanford.edu
 *
 * Based on many generations of sr clients including the original c client
 * and bert.
 *
 * 2003-Dec-03 09:00:52 AM :
 *   - bug sending packets read from client to sr_log_packet.  Packet was
 *     sent in network byte order ... expected host byte order.
 *     Reported by Matt Holliman & Sam Small. /mc
 *
 *  2004-Jan-29 07:09:28 PM
 *   - added check to handle signal interrupts on recv (for use with
 *     alarm(..) for timeouts.  Fixes are based on patch by
 *     Abhyudaya Chodisetti <sravanth@stanford.edu> /mc
 *
 *   2004-Jan-31 01:27:54 PM
 *    - William Chan (chanman@stanford.edu) submitted patch for UMR on
 *      sr_dump_packet(..)
 *
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#include "sr_dumper.h"
#include "sr_router.h"
#include "sr_if.h"
#include "sr_protocol.h"

#include "sha1.h"
#include "vnscommand.h"

static void sr_log_packet(struct sr_instance* , uint8_t* , int );
static int  sr_arp_req_not_for_us(struct sr_instance* sr,
                                  uint8_t * packet /* lent */,
                                  unsigned int len,
                                  char* interface  /* lent */);
int sr_read_from_server_expect(struct sr_instance* sr /* borrowed */, int expected_cmd);

/*-----------------------------------------------------------------------------
 * Method: sr_session_closed_help(..)
 *
 * Provide debugging hints if VNS closes session
 *
 *----------------------------------------------------------------------------*/
static void sr_session_closed_help()
{
}

/*-----------------------------------------------------------------------------
 * Method: sr_connect_to_server()
 * Scope: Global
 *
 * Connect to the virtual server
 *
 * RETURN VALUES:
 *
 *  0 on success
 *  something other than zero on error
 *
 *---------------------------------------------------------------------------*/
int sr_connect_to_server(struct sr_instance* sr,unsigned short port,
                         char* server)
{
    struct hostent *hp;
    c_open command;
    c_open_template ot;
    char* buf;
    uint32_t buf_len;

    /* REQUIRES */
    assert(sr);
    assert(server);

    /* purify UMR be gone ! */
    memset((void*)&command,0,sizeof(c_open));

    /* zero out server address struct */
    memset(&(sr->sr_addr),0,sizeof(struct sockaddr_in));

    sr->sr_addr.sin_family = AF_INET;
    sr->sr_addr.sin_port = htons(port);

    /* grab hosts address from domain name */
    if ((hp = gethostbyname(server))==0)
    {
        perror("gethostbyname:sr_client.c::sr_connect_to_server(..)");
        return -1;
    }

    /* set server address */
    memcpy(&(sr->sr_addr.sin_addr),hp->h_addr,hp->h_length);

    /* create socket */
    if ((sr->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket(..):sr_client.c::sr_connect_to_server(..)");
        return -1;
    }

    /* attempt to connect to the server */
    if (connect(sr->sockfd, (struct sockaddr *)&(sr->sr_addr),
                sizeof(sr->sr_addr)) < 0)
    {
        perror("connect(..):sr_client.c::sr_connect_to_server(..)");
        close(sr->sockfd);
        return -1;
    }

    /* wait for authentication to be completed (server sends the first message) */
    if(sr_read_from_server_expect(sr, VNS_AUTH_REQUEST)!= 1 ||
       sr_read_from_server_expect(sr, VNS_AUTH_STATUS) != 1)
        return -1; /* failed to receive expected message */

    if(strlen(sr->template) > 0) {
        /* send VNS_OPEN_TEMPLATE message to server */
        ot.mLen = htonl(sizeof(c_open_template));
        ot.mType = htonl(VNS_OPEN_TEMPLATE);
        strncpy(ot.templateName, sr->template, 30);
        strncpy(ot.mVirtualHostID, sr->host, IDSIZE);
        /* no source filters specified */

        buf = (char*)&ot;
        buf_len = sizeof(ot);
    }
    else {
        /* send sr_OPEN message to server */
        command.mLen   = htonl(sizeof(c_open));
        command.mType  = htonl(VNSOPEN);
        command.topoID = htons(sr->topo_id);
        strncpy( command.mVirtualHostID, sr->host,  IDSIZE);
        strncpy( command.mUID, sr->user, IDSIZE);

        buf = (char*)&command;
        buf_len = sizeof(command);
    }

    if(send(sr->sockfd, buf, buf_len, 0) != buf_len)
    {
        perror("send(..):sr_client.c::sr_connect_to_server()");
        return -1;
    }

    if(strlen(sr->template) > 0)
        if(sr_read_from_server_expect(sr, VNS_RTABLE) != 1)
            return -1; /* needed to get the rtable */

    return 0;
} /* -- sr_connect_to_server -- */



/*-----------------------------------------------------------------------------
 * Method: sr_handle_hwinfo(..)
 * scope: global
 *
 *
 * Read, from the server, the hardware information for the reserved host.
 *
 *---------------------------------------------------------------------------*/

int sr_handle_hwinfo(struct sr_instance* sr, c_hwinfo* hwinfo)
{
    int num_entries;
    int i = 0;

    /* REQUIRES */
    assert(sr);
    assert(hwinfo);

    num_entries = (ntohl(hwinfo->mLen) - (2*sizeof(uint32_t)))/sizeof(c_hw_entry);

    /* Debug("Received Hardware Info with %d entries\n",num_entries); */

    for ( i=0; i<num_entries; i++ )
    {
        switch( ntohl(hwinfo->mHWInfo[i].mKey))
        {
            case HWFIXEDIP:
                /*Debug("Fixed IP: %s\n",inet_ntoa(
                            *((struct in_addr*)(hwinfo->mHWInfo[i].value))));*/
                break;
            case HWINTERFACE:
                /*Debug("INTERFACE: %s\n",hwinfo->mHWInfo[i].value);*/
                // sr_add_interface(sr,hwinfo->mHWInfo[i].value);
                break;
            case HWSPEED:
                /* Debug("Speed: %d\n",
                        ntohl(*((unsigned int*)hwinfo->mHWInfo[i].value))); */
                break;
            case HWSUBNET:
                /* Debug("Subnet: %s\n",inet_ntoa(
                            *((struct in_addr*)(hwinfo->mHWInfo[i].value)))); */
                break;
            case HWMASK:
                /* Debug("Mask: %s\n",inet_ntoa(
                            *((struct in_addr*)(hwinfo->mHWInfo[i].value)))); */
                break;
            case HWETHIP:
                /*Debug("IP: %s\n",inet_ntoa(
                            *((struct in_addr*)(hwinfo->mHWInfo[i].value))));*/
                sr_set_ether_ip(sr,*((uint32_t*)hwinfo->mHWInfo[i].value));
                break;
            case HWETHER:
                /*Debug("\tHardware Address: ");
                DebugMAC(hwinfo->mHWInfo[i].value);
                Debug("\n"); */
                sr_set_ether_addr(sr,(unsigned char*)hwinfo->mHWInfo[i].value);
                break;
            default:
                printf (" %d \n",ntohl(hwinfo->mHWInfo[i].mKey));
        } /* -- switch -- */
    } /* -- for -- */

    printf("Router interfaces:\n");
    sr_print_if_list(sr);

    return num_entries;
} /* -- sr_handle_hwinfo -- */

int sr_handle_rtable(struct sr_instance* sr, c_rtable* rtable) {
    char fn[7+IDSIZE+1];
    FILE* fp;

    strcpy(fn, "rtable.");
    strcat(fn, rtable->mVirtualHostID);
    fp = fopen(fn, "w");
    if(fp) {
        fwrite(rtable->rtable, ntohl(rtable->mLen) - 8 - IDSIZE, 1, fp);
        fclose(fp);
        return 1;
    }
    else {
        perror("unable to write new rtable file");
        return 0; /* failed */
    }
}

int sr_handle_auth_request(struct sr_instance* sr, c_auth_request* req) {
#define AUTH_KEY_LEN 64
#define SHA1_LEN 20
    char auth_key[AUTH_KEY_LEN+1];
    FILE* fp;
    SHA1Context sha1;
    c_auth_reply* ar;
    char* buf;
    int len, len_username, i, ret;

    /* read in the user's auth key */
    fp = fopen("auth_key", "r");
    if(fp) {
        if(fgets(auth_key, AUTH_KEY_LEN+1, fp) != auth_key) {
            fclose(fp);
            return 0;
        }
        fclose(fp);

        /* compute the salted SHA1 of password from auth_key */
        SHA1Reset(&sha1);
        SHA1Input(&sha1, req->salt, ntohl(req->mLen) - sizeof(*req));
        SHA1Input(&sha1, (unsigned char*)auth_key, AUTH_KEY_LEN);
        if(!SHA1Result(&sha1)) {
            fprintf(stderr, "SHA1 result could not be computed\n");
            return 0;
        }

        /* build the auth reply packet and then send it */
        len_username = strlen(sr->user);
        len = sizeof(c_auth_reply) + len_username + SHA1_LEN;
        buf = (char*)malloc(len);
        if(!buf) {
            perror("malloc failed");
            return 0;
        }
        ar = (c_auth_reply*)buf;
        ar->mLen = htonl(len);
        ar->mType = htonl(VNS_AUTH_REPLY);
        ar->usernameLen = htonl(len_username);
        strcpy(ar->username, sr->user);
        for(i=0; i<5; i++)
            sha1.Message_Digest[i] = htonl(sha1.Message_Digest[i]);
        memcpy(ar->username + len_username, sha1.Message_Digest, SHA1_LEN);

        if(send(sr->sockfd, buf, len, 0) != len) {
            perror("send(..):sr_client.c::sr_handle_auth_request()");
            ret = 0;
        }
        else
            ret = 1;
        free(buf);
        return ret;
    }
    else {
        perror("unable to read credentials from 'auth_key' file");
        return 0; /* failed */
    }
}

int sr_handle_auth_status(struct sr_instance* sr, c_auth_status* status) {
    if(status->auth_ok)
        printf("successfully authenticated as %s\n", sr->user);
    else
        fprintf(stderr, "Authentication failed as %s: %s\n", sr->user, status->msg);
    return status->auth_ok;
}

/*-----------------------------------------------------------------------------
 * Method: sr_read_from_server(..)
 * Scope: global
 *
 * Houses main while loop for communicating with the virtual router server.
 *
 *---------------------------------------------------------------------------*/

int sr_read_from_server(struct sr_instance* sr /* borrowed */)
{
    return sr_read_from_server_expect(sr, 0);
}

int sr_read_from_server_expect(struct sr_instance* sr /* borrowed */, int expected_cmd)
{
    int command, len;
    unsigned char *buf = 0;
    c_packet_ethernet_header* sr_pkt = 0;
    int ret = 0, bytes_read = 0;

    /* REQUIRES */
    assert(sr);

    /*---------------------------------------------------------------------------
      Read a command from the server
      -------------------------------------------------------------------------*/

    bytes_read = 0;

    /* attempt to read the size of the incoming packet */
    while( bytes_read < 4)
    {
        do
        { /* -- just in case SIGALRM breaks recv -- */
            errno = 0; /* -- hacky glibc workaround -- */
            if((ret = recv(sr->sockfd,((uint8_t*)&len) + bytes_read,
                            4 - bytes_read, 0)) == -1)
            {
                if ( errno == EINTR )
                { continue; }

                perror("recv(..):sr_client.c::sr_read_from_server");
                return -1;
            }
            bytes_read += ret;
        } while ( errno == EINTR); /* be mindful of signals */

    }

    len = ntohl(len);

    if ( len > 10000 || len < 0 )
    {
        fprintf(stderr,"Error: command length to large %d\n",len);
        close(sr->sockfd);
        return -1;
    }

    if((buf = malloc(len)) == 0)
    {
        fprintf(stderr,"Error: out of memory (sr_read_from_server)\n");
        return -1;
    }

    /* set first field of command since we've already read it */
    *((int *)buf) = htonl(len);

    bytes_read = 0;

    /* read the rest of the command */
    while ( bytes_read < len - 4)
    {
        do
        {/* -- just in case SIGALRM breaks recv -- */
            errno = 0; /* -- hacky glibc workaround -- */
            if ((ret = read(sr->sockfd, buf+4+bytes_read, len - 4 - bytes_read)) ==
                    -1)
            {
                if ( errno == EINTR )
                { continue; }
                fprintf(stderr,"Error: failed reading command body %d\n",ret);
                close(sr->sockfd);
                return -1;
            }
            bytes_read += ret;
        } while (errno == EINTR); /* be mindful of signals */
    }

    /* My entry for most unreadable line of code - guido */
    /* ... you win - mc                                  */
    command = *(((int *)buf)+1) = ntohl(*(((int *)buf)+1));

    /* make sure the command is what we expected if we were expecting something */
    if(expected_cmd && command!=expected_cmd) {
        if(command != VNSCLOSE) { /* VNSCLOSE is always ok */
            fprintf(stderr, "Error: expected command %d but got %d\n", expected_cmd, command);
            return -1;
        }
    }

    ret = 1;
    switch (command)
    {
        /* -------------        VNSPACKET     -------------------- */

        case VNSPACKET:
            sr_pkt = (c_packet_ethernet_header *)buf;

            /* -- check if it is an ARP to another router if so drop   -- */
            if ( sr_arp_req_not_for_us(sr,
                    (buf+sizeof(c_packet_header)),
                    len - sizeof(c_packet_ethernet_header) +
                    sizeof(struct sr_ethernet_hdr),
                    (char*)(buf + sizeof(c_base))) )
            { break; }

            /* -- log packet -- */
            sr_log_packet(sr, buf + sizeof(c_packet_header),
                    ntohl(sr_pkt->mLen) - sizeof(c_packet_header));

            /* -- pass to router, student's code should take over here -- */
            sr_handlepacket(sr,
                    (buf+sizeof(c_packet_header)),
                    len - sizeof(c_packet_ethernet_header) +
                    sizeof(struct sr_ethernet_hdr),
                    (char*)(buf + sizeof(c_base)));

            break;

            /* -------------        VNSCLOSE      -------------------- */

        case VNSCLOSE:
            fprintf(stderr,"VNS server closed session.\n");
            fprintf(stderr,"Reason: %s\n",((c_close*)buf)->mErrorMessage);
            sr_session_closed_help();

            if(buf)
            { free(buf); }
            return 0;
            break;

            /* -------------        VNSBANNER      -------------------- */

        case VNSBANNER:
            fprintf(stderr,"%s",((c_banner*)buf)->mBannerMessage);
            break;

            /* -------------     VNSHWINFO     -------------------- */

        case VNSHWINFO:
            sr_handle_hwinfo(sr,(c_hwinfo*)buf);
            if(sr_verify_routing_table(sr) != 0)
            {
                fprintf(stderr,"Routing table not consistent with hardware\n");
                return -1;
            }
            printf(" <-- Ready to process packets --> \n");
            break;

            /* ---------------- VNS_RTABLE ---------------- */
        case VNS_RTABLE:
            if(!sr_handle_rtable(sr, (c_rtable*)buf))
                ret = -1;
            break;

            /* ------------- VNS_AUTH_REQUEST ------------- */
        case VNS_AUTH_REQUEST:
            if(!sr_handle_auth_request(sr, (c_auth_request*)buf))
                ret = -1;
            break;

            /* ------------- VNS_AUTH_STATUS -------------- */
        case VNS_AUTH_STATUS:
            if(!sr_handle_auth_status(sr, (c_auth_status*)buf))
                ret = -1;
            break;

        default:
            Debug("unknown command: %d\n", command);
            break;

    }/* -- switch -- */

    if(buf)
    { free(buf); }
    return ret;
}/* -- sr_read_from_server -- */

/*-----------------------------------------------------------------------------
 * Method: sr_ether_addrs_match_interface(..)
 * Scope: Local
 *
 * Make sure ethernet addresses are sane so we don't muck uo the system.
 *
 *----------------------------------------------------------------------------*/

static int
sr_ether_addrs_match_interface( struct sr_instance* sr, /* borrowed */
                                uint8_t* buf, /* borrowed */
                                const char* name /* borrowed */ )
{
    struct sr_ethernet_hdr* ether_hdr = 0;
    struct sr_if* iface = 0;

    /* -- REQUIRES -- */
    assert(sr);
    assert(buf);
    assert(name);

    ether_hdr = (struct sr_ethernet_hdr*)buf;
    iface = sr_get_interface(sr, name);

    if ( iface == 0 ){
        fprintf( stderr, "** Error, interface %s, does not exist\n", name);
        return 0;
    }

    if ( memcmp( ether_hdr->ether_shost, iface->addr, ETHER_ADDR_LEN) != 0 ){
        fprintf( stderr, "** Error, source address does not match interface\n");
        return 0;
    }

    /* TODO */
    /* Check destination, hardware address.  If it is private (i.e. destined
     * to a virtual interface) ensure it is going to the correct topology
     * Note: This check should really be done server side ...
     */

    return 1;

} /* -- sr_ether_addrs_match_interface -- */

/*-----------------------------------------------------------------------------
 * Method: sr_send_packet(..)
 * Scope: Global
 *
 * Send a packet (ethernet header included!) of length 'len' to the server
 * to be injected onto the wire.
 *
 *---------------------------------------------------------------------------*/

int sr_send_packet(struct sr_instance* sr /* borrowed */,
                         uint8_t* buf /* borrowed */ ,
                         unsigned int len,
                         const char* iface /* borrowed */)
{
    c_packet_header *sr_pkt;
    unsigned int total_len =  len + (sizeof(c_packet_header));

    /* REQUIRES */
    assert(sr);
    assert(buf);
    assert(iface);

    /* don't waste my time ... */
    if ( len < sizeof(struct sr_ethernet_hdr) ){
        fprintf(stderr , "** Error: packet is wayy to short \n");
        return -1;
    }

    /* Create packet */
    sr_pkt = (c_packet_header *)malloc(len +
            sizeof(c_packet_header));
    assert(sr_pkt);
    sr_pkt->mLen  = htonl(total_len);
    sr_pkt->mType = htonl(VNSPACKET);
    strncpy(sr_pkt->mInterfaceName,iface,16);
    memcpy(((uint8_t*)sr_pkt) + sizeof(c_packet_header),
            buf,len);

    /* -- log packet -- */
    sr_log_packet(sr,buf,len);

    if ( ! sr_ether_addrs_match_interface( sr, buf, iface) ){
        fprintf( stderr, "*** Error: problem with ethernet header, check log\n");
        free ( sr_pkt );
        return -1;
    }

    if( write(sr->sockfd, sr_pkt, total_len) < total_len ){
        fprintf(stderr, "Error writing packet\n");
        free(sr_pkt);
        return -1;
    }

    free(sr_pkt);

    return 0;
} /* -- sr_send_packet -- */

/*-----------------------------------------------------------------------------
 * Method: sr_log_packet()
 * Scope: Local
 *
 *---------------------------------------------------------------------------*/

void sr_log_packet(struct sr_instance* sr, uint8_t* buf, int len )
{
    struct pcap_pkthdr h;
    int size;

    /* REQUIRES */
    assert(sr);

    if(!sr->logfile)
    {return; }

    size = min(PACKET_DUMP_SIZE, len);

    gettimeofday(&h.ts, 0);
    h.caplen = size;
    h.len = (size < PACKET_DUMP_SIZE) ? size : PACKET_DUMP_SIZE;

    sr_dump(sr->logfile, &h, buf);
    fflush(sr->logfile);
} /* -- sr_log_packet -- */

/*-----------------------------------------------------------------------------
 * Method: sr_arp_req_not_for_us()
 * Scope: Local
 *
 *---------------------------------------------------------------------------*/

int  sr_arp_req_not_for_us(struct sr_instance* sr,
                           uint8_t * packet /* lent */,
                           unsigned int len,
                           char* interface  /* lent */)
{
    struct sr_if* iface = sr_get_interface(sr, interface);
    struct sr_ethernet_hdr* e_hdr = 0;
    struct sr_arp_hdr*       a_hdr = 0;

    if (len < sizeof(struct sr_ethernet_hdr) + sizeof(struct sr_arp_hdr) )
    { return 0; }

    assert(iface);

    e_hdr = (struct sr_ethernet_hdr*)packet;
    a_hdr = (struct sr_arp_hdr*)(packet + sizeof(struct sr_ethernet_hdr));

    if ( (e_hdr->ether_type == htons(ethertype_arp)) &&
            (a_hdr->ar_op      == htons(arp_op_request))   &&
            (a_hdr->ar_tip     != iface->ip ) )
    { return 1; }

    return 0;
} /* -- sr_arp_req_not_for_us -- */
