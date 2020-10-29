//Room: /d/dali/chahua3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花园");
        set("long", @LONG
大理茶花冠绝天下，镇南王府的茶花自然更非凡品。你正走在茶
花园中，层层密密的都是争奇斗妍的茶花。靠南岸边一溜的盆栽的茶
花，微风从水面吹来，摇曳婆娑。
LONG );
        set("objects", ([
           "/d/dali/obj/chahua8": 1,
           "/d/dali/obj/chahua9": 1,
           "/d/dali/obj/chahua10": 1,
        ]));
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "southwest"  : "/d/dali/chahua2",
            "north"      : "/d/dali/chahua6",
            "southeast"  : "/d/dali/chahua5",
        ]));
	set("coor/x", -19071);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}