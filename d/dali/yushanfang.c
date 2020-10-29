//Room: /d/dali/yushanfang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","御膳坊");
        set("long", @LONG
这里是大理国皇宫的御膳坊，这里的厨具都是金银做成的。皇帝
不在这里也就息火了，往东是长廊。
LONG );
        set("objects", ([
            "/d/dali/npc/taijian": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/hualang",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19150);
	set("coor/y", -6830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}