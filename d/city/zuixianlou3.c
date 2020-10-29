// Room: /city/zuixianlou3.c
// YZC 1995/12/04

inherit ROOM;

void create()
{
        set("short", "醉仙楼三楼");
        set("long", @LONG
这里是三楼，一上来就觉得喧闹无比，和二楼的清雅恰成反比，
简直让你不能相信。几张原本干净整洁的桌子也被糟蹋的一塌糊涂。
汤水淌得满地，酒呃臭屁满屋。几位小二鼻青脸肿的躲在屋角，瑟瑟
发抖，地上还有残留的血迹。
LONG );
        set("objects", ([
                "/d/city/npc/tao1" : 1,
                "/d/city/npc/tao2" : 1,
                "/d/city/npc/tao3" : 1,
                "/d/city/npc/tao4" : 1,
                "/d/city/npc/tao5" : 1,
                "/d/city/npc/tao6" : 1,
        ]));
        set("exits", ([
                "down" : "/d/city/zuixianlou2",
        ]));
//	set("no_clean_up", 0);
	set("coor/x", 10);
	set("coor/y", 20);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}