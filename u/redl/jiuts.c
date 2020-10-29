#include <ansi.h>

inherit DEMONROOM;

void create()
{
        set("short", "九头蛇领地");
        set("long",@LONG
这是九头蛇的领地，周围尽是潮湿阴深的湿地，恐怖之极。
LONG);


        set("exits", ([
                "out"    : "/maze/jiutoushe/haitan",
                    "enter"    : "/u/redl/jiuts2", 
                
        ]));
                set("no_rideto", 1);         // 设置不能骑马到其他地方
                set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
                set("n_time", 3);
                set("n_npc",30); 
                set("n_max_npc", 30);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/jiutoushe");

        setup();
}


