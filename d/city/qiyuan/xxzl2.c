//休闲走廊
// redl 2013/2

#include <ansi.h>
inherit  ROOM;

string look_string();

void  create  ()
{
    set  ("short",  "休闲走廊");
        set("long", @LONG
这里是一条走廊，通向各个休闲娱乐活动的房间。
LONG );

        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         


    set("exits",  ([
//    "east"  :  __DIR__"xxzl2",
    "south"  :  __DIR__"qiyuan2",
//    "north"  :  __DIR__"qiyuan2",
    "west" : __DIR__"xxzl1",
    ]));
            set("objects", ([  
            "/u/mud/shizhe":1,
            ]));

   setup();
}



