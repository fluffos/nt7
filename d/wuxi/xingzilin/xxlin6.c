// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h>
inherit DEMONROOM;

void create()
{
                int lv;
        set("short", "杏子林");
        set("long",@LONG
林里密密麻麻地全是杏树，在粉白渗金的花的海洋里一片浓香扑鼻。
杏子树上的花瓣时有往人的头顶飘落，似乎酝酿着某种阴郁情绪。
LONG);

        set("exits", ([
                "north"   : __DIR__"xxlin7",
                //"east"   : __DIR__"xxlin7",
                "west"  : __DIR__"xxlin1",
                //"south"  : __DIR__"xxlin1",
        ]));

                                set("ngroup", 1); 
                                set("no_sleep_room",1);
                                set("no_magic", 1);
                set("n_time", 15); 
                set("n_npc", 1); 
                set("n_max_npc", 2+random(2));
                lv = random(100);
                if (lv < 15) set("s_npc", __DIR__"npc/wushi6");
                                else if (lv < 45) set("s_npc", __DIR__"npc/wushi7");
                                else set("s_npc", __DIR__"npc/wushi8");
        setup();
}

#include "leavelin.h";
