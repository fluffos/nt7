#include <room.h>
inherit ROOM;

void create()
{
        set("short", "打铁铺");
        set("long", @LONG
这是永内东街的一家简陋的打铁铺，中心摆着一个火炉，炉火把
四周照得一片通红，你一走进去就感到浑身火热。打铁铺的墙角堆满
了已完工和未完工的菜刀、铁锤、铁棍、匕首、盔甲等物。一位铁匠
满头大汗挥舞着铁锤，专心致志地在打铁。
LONG );
       set("exits", ([
                "north" : "/d/beijing/yong_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/tiehuoji" : 1,
                "/d/beijing/npc/tiejiang" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}