#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "小房间");
        set("long", @LONG
这是一个小房间，桌上点着蜡烛。房中只有一桌一床，陈设简单，
却十分干净。床上铺着被褥。
LONG );
    set("exits", ([
                "south" : "/d/beijing/zhuang8",
    ]));
    set("objects", ([
        "/d/beijing/npc/furen": 1,
          "/d/beijing/npc/shuanger": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 90);
        set("coor/y", 4740);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}