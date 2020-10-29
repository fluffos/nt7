inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "山麓");
        set("long", @LONG
这里是襄阳城外的山麓，也是南下蒙古军队的必经之路，道路曲
折盘旋，十分难走，但是对于出征的大军来说，走这样难走的路都好
象已经成了极平常的事了。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
               "south"  : __DIR__"conglin1",
               "north"  : __DIR__"shanlu1",
        ]));

        setup();
} 
