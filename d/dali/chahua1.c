//Room: /d/dali/chahua1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花园门");
        set("long", @LONG
大理茶花冠绝天下，镇南王府的茶花自然更非凡品。你站在茶花
园口，对着满园春色，不禁大喜过望。东边就进园了，北边是一个库
房。南边是一栋厢房，那里是休息的地方。
LONG );
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/bingqiku",
            "south"  : "/d/dali/xiuxishi",
            "east"   : "/d/dali/chahua2",
            "west"   : "/d/dali/tingyuan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6861);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}