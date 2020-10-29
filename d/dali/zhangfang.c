//Room: /d/dali/zhangfang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","帐房");
        set("long", @LONG
这里是镇南王府的帐房，王府每天的银米出入，往来消耗，全由
这里经手，包括家丁下人的薪俸赏赐，在在都是麻烦多多。这里却从
来没出过差错。
LONG );
        set("objects", ([
           "/d/dali/npc/huo": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/wfdating",
        ]));
	set("coor/x", -19131);
	set("coor/y", -6861);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}