//Room: /d/dali/changlang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","长廊");
        set("long", @LONG
这里是镇南王府的长廊，两边都是大圆柱。边上假山小湖应有尽
有，显得十分秀丽。北面是一座大建筑，南边是一个小庭院。
LONG );
        set("objects",([
            "/d/dali/npc/duanwuwei" : 1,
        ]));
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/tingfang",
            "south"  : "/d/dali/tingyuan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19101);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}