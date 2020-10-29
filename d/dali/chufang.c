//Room: /d/dali/chufang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","厨房");
        set("long", @LONG
这是镇南王府的厨房，中央有个大桌子，周围则放着几个圆凳，
这里是段家弟子用餐的地方。
LONG );
        set("objects", ([
            "/d/dali/obj/xueli"       : 4,
            "/d/dali/npc/obj/puercha" : 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/tingfang",
        ]));
	set("coor/x", -19111);
	set("coor/y", -6841);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}