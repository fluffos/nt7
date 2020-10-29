#ifndef __MUDLIB__
#define __MUDLIB__

#include <getconfig.h>

//  The base distribution mudlib name.

#define MUDLIB_NAME             ((string) CONFIG_D->query_string("mudlib name"))
#define MUDLIB_VERSION          ((string) CONFIG_D->query_string("mudlib version"))
#define MUDLIB_VERSION_NUMBER   ((string) CONFIG_D->query_string("mudlib version number"))

#define INTERMUD_MUD_NAME       ((string) CONFIG_D->query_string("internet mud name"))
#define CHINESE_MUD_NAME        LOCAL_MUD_NAME()
#define MUD_FULL_NAME           CHINESE_MUD_NAME+"("+INTERMUD_MUD_NAME+")"

#define MUD_HOST_NAME           ((string) CONFIG_D->query_string("hostname"))
#define MUD_LOCATION            ((string) CONFIG_D->query_string("location"))
#define MUD_GROUP               ((string) CONFIG_D->query_string("group"))
#define MUD_ENCODING            ((string) CONFIG_D->query_string("encoding"))
#define MUD_DRIVER              ((string) CONFIG_D->query_string("mudos"))
#define MUD_TYPE                ((string) CONFIG_D->query_string("type"))
#define MUD_ADMIN               ((string) CONFIG_D->query_string("admin"))
#define MUD_WEB                 ((string) CONFIG_D->query_string("web"))

#define DB_HOST                 ((string) CONFIG_D->query_string("mysql host"))
#define DB_USER                 ((string) CONFIG_D->query_string("mysql user"))
#define DATABASE                ((string) CONFIG_D->query_string("mysql database"))
#define LOCAL_STATION           ((string) CONFIG_D->query_string("local host"))

#define SMTP_SERVER             ((string) CONFIG_D->query_string("smtp server"))
#define SMTP_DOMAIN             ((string) CONFIG_D->query_string("smtp domain"))
#define SENDER                  ((string) CONFIG_D->query_string("smtp sender"))

#define MUDLIST_DNS1            ((string) CONFIG_D->query_string("mudlist1"))
#define MUDLIST_DNS2            ((string) CONFIG_D->query_string("mudlist2"))
#define MUDLIST_DNS3            ((string) CONFIG_D->query_string("mudlist3"))
#define MUDLIST_DNS4            ((string) CONFIG_D->query_string("mudlist4"))
#define MUDLIST_DNS5            ((string) CONFIG_D->query_string("mudlist5"))
#define MUDLIST_DNS6            ((string) CONFIG_D->query_string("mudlist6"))
#define MUDLIST_DNS7            ((string) CONFIG_D->query_string("mudlist7"))
#define MUDLIST_DNS8            ((string) CONFIG_D->query_string("mudlist8"))
#define MUDLIST_DNS9            ((string) CONFIG_D->query_string("mudlist9"))
#endif
