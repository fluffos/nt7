// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "客堂");
        set ("long", @LONG
这里是万家请贵重客人的小客堂。中间一个小圆红木桌上，摆满了
一桌酒席，等着客人上坐。镂雕窗外，可以看到演武场。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "east"   : __DIR__"yanwuchang",
                "west"   : __DIR__"houyuan",
                "south"  : __DIR__"changlang6",
                "north"  : __DIR__"changlang5",
        ]));

        set("coor/x", -1487);
        set("coor/y", -2040);
        set("coor/z", 0);
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
