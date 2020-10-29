// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h>

void trans_message(string msgclass, string msg)
{
        object room;
        string roomstr, targetid, tmpstr, subclass;
        string *msgs;
        int i;

                if (!(roomstr = query("trans_msg_to"))) return;
                if (!objectp(room = get_object(roomstr))) return;

        if( sscanf(msgclass, "%s:%s", subclass, msgclass) == 2 )
        {
                switch( subclass ) { 
                        case "channel": 
                        case "outdoor": 
                        case "system": 
                                return;
                }
        }
        
                switch( msgclass ) { 
                        case "system": 
                        case "story": 
                        case "group_quest": 
                        case "EMTMSG" : 
                                return;
                }
                
                //tell_room(room, NOR + BOLD + ">>>[" + subclass + "]:[" + msgclass + "]\n" + NOR);
        msgs = explode(msg, "\n");
        msg = "";
        targetid = query("trans_msg_id");
        //tell_room(room, NOR + BOLD + ">>>[msgs 1]:[" + filter_color(msgs[1],1) + "]\n" + NOR);
        if (msgs[1]) sscanf(filter_color(msgs[1],1), ">>|%*s(%s)|<<", tmpstr);
        //tell_room(room, NOR + BOLD + ">>>[tmpstr]:[" + tmpstr + "]\n" + NOR);
        if (!targetid || (targetid && targetid == tmpstr)) {
                for( i = 0; i < sizeof(msgs); i++ ) {
                        msg += NOR + BOLD + "》》" + NOR + msgs[i] + "\n";
                }
        }

                tell_room(room, msg);
}




