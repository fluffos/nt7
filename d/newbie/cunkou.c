#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "村口");
        set("long", @LONG
这里是一片开阔地，远远可以望见东方升起的阵阵炊烟，听到鸡
鸣犬吠之声。如果你想要出村的话，可以问问新手村的守卫（输入指
令 ask hua about 出村）。
LONG);
        set("exits", ([
                "east" : __DIR__"road1",
        ]));

        set("xinshoucun", 1); 
        set("outdoors", "newbie");
        set("no_fight", 1);

        set("objects", ([
                __DIR__"npc/huabo" : 1,
        ]));

        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}
