#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", RED "浴血残阳" NOR);
        set("long", HIR "                夕     阳\n" + NOR + RED +
                "已将整个绝顶染成血红色，你仿佛已嗅到一股血腥之气。" + NOR + "\n ");

        set("exits", ([ /* sizeof() == 1 */
        ]));
        set("no_magic", 1);
        set("fight_room", "/d/city/biwu_dating");
        setup();
}

void init()  
{ 
        object me = this_player();  
        add_action("discmds", ({  
                   "steal", "cast", "conjure", "array", "fight", "hit",   
                   "recall", "kill", "ansuan", "touxi", "miss",
        }));  
} 

int discmds() 
{ 
        tell_object(this_player(), "比武是光明正大，不许作弊！\n");  
        return 1;  
} 

void relay_message(string msg)
{
        object look_fight_room, look_room;
        string *msgs;
        int i;
        
        if (! look_fight_room = find_object("/d/city/biwu_dating"))
                look_fight_room = load_object("/d/city/biwu_dating");
                
        if (! look_room = find_object("/d/city/liaotian"))
                look_room = load_object("/d/city/liaotian");
                                
        msgs = explode(msg, "\n");
        for (i = 0; i < sizeof(msgs); i++)
        if (strlen(msgs[i]) > 5)
        {
                message("vision", NOR + BOLD + ">>" + NOR + msgs[i] + "\n", look_fight_room);
                message("vision", NOR + BOLD + ">>" + NOR + msgs[i] + "\n", look_room);
        }
}

