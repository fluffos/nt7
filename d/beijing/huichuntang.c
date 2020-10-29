#include <room.h>
inherit ROOM;

void create()
{
        set("short", "回春堂药店");
        set("long", @LONG
回春堂药店是整个北京城里最大最有名气的药铺。你还没走进这
里，便闻到一股浓浓的药材气味，那是从药柜上的几百个小抽屉里散
发出来的。一位伙计在柜台后站着，堆着笑脸招呼着客人。
LONG );
       set("exits", ([
                "west" : "/d/beijing/xi_2",
                "east" : "/d/beijing/liandan_neiting",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/yaopuhuoji" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}