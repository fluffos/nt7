//Room: /d/dali/yuxuguanqian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","玉虚观前");
        set("long", @LONG
东面一座庙观，门前匾上写着『玉虚观』三个大字，西边一个碧
水荡漾的小湖，四周绿柳成荫，实乃修心养性的好地方。
LONG );
        set("objects", ([
           "/d/dali/npc/xiaodaogu": 2,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/yuxuguan",
            "south"  : "/d/dali/hudiequan",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}