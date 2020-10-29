/*
 * File    : gfinger_q.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is a request for information about a user at another mud.
 */
 

// Ported to ES2 mudlib by Annihilator@ES2 (06/15/95)

#include <net/dns.h>
#include <net/macros.h>

inherit F_CLEAN_UP;

void create() { seteuid(ROOT_UID); }

// Finger a wiz on another mud.
string send_gfinger_q(string mud, string wiz, mixed them)
{
        mapping minfo;

        if(!ACCESS_CHECK(previous_object())) return 0;

        if (!them) them = this_player(1);
        mud = htonn( mud );

        if (mud == mud_nname())
                return 0;

        // make sure we have an entry for the recipient
        minfo = DNS_MASTER->query_mud_info(mud);
        if (!minfo) return LOCAL_MUD_NAME() + "目前并没有和" + mud + "联系上。\n";

        // send the finger
        DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
                sprintf("@@@%s||NAME:%s||PORTUDP:%d||PLAYER:%s||ASKWIZ:%s@@@\n",
                DNS_GFINGER_Q, Mud_name(), udp_port(),
                wiz,objectp(them)?query("id", them):them));
        return "网络信息已经发出，请稍候。\n";
}

void incoming_request(mapping info)
{
        string reply;
        mapping mudinfo;

        if (info["NAME"] && info["PORTUDP"] && info["PLAYER"]) {
                if (info["NAME"] == mud_nname()) return ;

                // if we don't have a record of the mud get it
                if (!DNS_MASTER->dns_mudp(info["NAME"]))
                        PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);

                // send the finger reply
                mudinfo = DNS_MASTER->query_mud_info(info["NAME"]);
                reply = (string)FINGER_D->remote_finger_user(lower_case(info["PLAYER"]), mudinfo["ENCODING"] == "GB");
                DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
                        sprintf("@@@%s||NAME:%s||PORTUDP:%d||ASKWIZ:%s||MSG:%s@@@\n",
                        DNS_GFINGER_A, mud_nname(), udp_port(),
                        info["ASKWIZ"], reply));
        }
}
