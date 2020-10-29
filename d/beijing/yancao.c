#include <room.h>
inherit ROOM;

void create()
{
        set("short", "烟草店");
        set("long", @LONG
从云南运来的烟土在这里可以说是最佳的商品，他的利润是成百
成千倍的翻了上去，北京现在最流行的送礼的方式就送烟。但是永远
记住吸烟是有害健康的，所以这里的老板被鸡蛋打在头上。发昧心财
的人总是被人唾骂的。
LONG );
       set("exits", ([
                "north" : "/d/beijing/caroad_e2",
        ]));
        set("objects", ([
                "/d/beijing/npc/old2" : 1,
        ]));
        set("outdoors", "beijing");
        set("no_fight",1);
	set("coor/x", -2770);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}