// Room: /d/xiangyang/juyilianwu1.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "练功场");
        set("long", @LONG
这里是聚义馆中用来练功的地方。有几个人正在专心致致地练武，
有几个手持兵器，在互相拆招。身法灵动，犹如穿花蝴蝶一般，你不
禁看花了眼，别的人则坐在地上的蒲团上苦练内力。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "west" : __DIR__"juyiyuan",
        ]));
        set("objects", ([
                "/clone/npc/tong-ren" : 3,
        ]));
        set("coor/x", -7830);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}