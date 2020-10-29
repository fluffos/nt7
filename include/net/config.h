#ifndef __NET__CONFIG_H
#define __NET__CONFIG_H

#ifndef SVC_TCP
#include <net/services.h>
#endif

#include <mudlib.h>
 
#define LISTNODES ([ \
        "FALLING-SUN" : "202.103.184.38 5559",\
        "YH"          : "61.139.77.196 3004",\
        "NTA"          : "221.202.78.197 2004",\
        "HELL.RV"     : "202.104.242.79 2004",\
        "SYZF"        : "202.102.2.158 8892",\
        "HUAXIA"      : "61.166.100.14 8903",\
        "HLXY"        : "202.96.91.29 6670",\
        "KYNC"        : "218.13.253.96 4448",\
        "TY"          : "61.147.119.97 4004",\
        "YX"          : "202.110.52.226 2007",\
        "TU"          : "61.184.100.7 8804",\
        "XKX"         : "210.51.191.89 5559",\
        "TT"          : "219.134.89.94  2004",\
        "SDXL"        : "219.159.104.120 6670",\
        "WMKJ"        : "61.174.213.238 2006",\
        "FYZQ"        : "220.114.4.41 8892",\
        "RWLB"        : "210.59.67.253 4004",\
        "ZHYX"        : "220.167.52.40 5559",\
        "NT.CD"       : "218.89.171.162 2005",\
        "NT.JY"       : "202.102.16.5 2005",\
        "MSR"         : "222.156.192.26 4004",\
        "TXWD"        : "218.15.33.140 5559",\
        "ES"          : "222.156.194.78 4004",\
        "YX"          : "202.99.168.30 2004",\
        "CS"          : "61.191.30.119 5559",\
        "WLWS"        : "61.132.74.86 2003",\
        "THE"         : "140.114.110.8 3996",\
        "THEA"        : "61.166.100.14 8903",\
        "THEB"        : "210.51.25.170 5559",\
])


/* This is the default packet size of outgoing mail messages.  The ideal
 * number is 512, maximum would be about 900, since 1024 is the maximum
 * udp packet size.  Probably best kept at 512
 */
#define MAIL_PACKET_SIZE        512
 
/* These macros are for the name service.  They determine how often the
 * database is refreshed, how often other muds are checked, how often
 * the sequence list is checked for timed out services, and how long a
 * service is allowed to time out.
 */
#define REFRESH_INTERVAL     5*60
#define PING_INTERVAL       30*60
#define SEQ_CLEAN_INTERVAL  60*60
#define SERVICE_TIMEOUT        30
/* The number of muds that we initialy allocate space for.  This speeds
 * up name lookup.
 */
#define MUDS_ALLOC 60
/* This macro controls the level of tcp support used by the mud for
 * services such as finger, tell and mail. Valid values are:
 *  TCP_ALL   - all services available
 *  TCP_ONLY  - only tcp services available
 *  TCP_SOME  - some tcp services are available
 *  TCP_NONE  - no tcp services available
 */
#define TCP_SERVICE_LEVEL TCP_ALL
/* These are the prefered protocols used for certain services which can
 * be done either way.  Mail should be left tcp, the others are up to
 * the individual admin.  If the one you choose is not supported the
 * other type _may_ be used depending on the service.
 */
#define PREF_MAIL         SVC_TCP
#define PREF_FINGER       SVC_TCP
#define PREF_TELL         SVC_UDP
/* These macros are used by the name server to keep a list of muds which
 * do not support the DNS.
 */
#define MUD_ADDRESSES   "/adm/etc/mud_addresses"
#define MUD_SERVICES    "/adm/etc/mud_services"
#endif //__NET__CONFIG_H

