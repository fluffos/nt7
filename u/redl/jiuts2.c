#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "九头蛇领地");
        set("long",@LONG
这是九头蛇的领地，周围尽是潮湿阴深的湿地，恐怖之极。(scheme、research)
LONG);


        set("exits", ([
                "out"    : "/maze/jiutoushe/haitan",
                
        ]));

        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
        set("no_rideto", 1);
        set("no_flyto", 1);
        set("no_user_kill", 1); 
        set("dongtianfudi", 999999); 

        set("sleep_room", 1); 

        setup();
}
