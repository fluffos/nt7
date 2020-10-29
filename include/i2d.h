// i2d.h

#define MUD                     0
#define STREAM                  1
#define DATAGRAM                2
#define STREAM_BINARY           3
#define DATAGRAM_BINARY         4
//-----------------------------------------------
#define I2D_MUD_SERVER          ({"113.31.21.157", 7004})
#define MUDLIST_UPDATE_INTERVAL 600
#define REFRESH_INCOMING_TIME   3*60*60
//----------------------位元运算用-------------------------
#define GB_CODE         1
#define ANTI_AD         2
#define IGNORED         4
#define SHUTDOWN        8
#define ONLINE          16
#define DISCONNECT      32
#define ENCODE_CONFIRM  64


//___________________________________________________
#define LISTNODES ([ \
        "NT5"           : "113.31.21.157 7004",\
        "YHNT"          : "113.31.21.157 8004",\
        "XLQY"          : "113.31.21.157 5559",\
        "ESII"          : "203.204.205.216 4004",\
        "YH3"           : "182.140.133.250 7004",\
        "RW2"           : "210.59.236.38 4004",\
        "NT4"           : "113.31.21.138 7004",\
        "NT4-2"         : "220.135.174.1 6670",\
        "FY5"           : "203.81.26.60 6004",\
        "SJQY"          : "60.29.236.107 5559",\
        "SJZT"          : "112.65.229.105 5559",\
        "YSZZ"          : "122.224.167.198 8004",\
])

#define BANDLIST ([\
])
