//Room: /d/dali/xiaguan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","下关城");
        set("long", @LONG
下关城，又名龙尾城，为阁罗凤所筑，唐代已极繁荣。城区萦抱
苍山南麓数里，洱水绕城南而过，端的风景如画。此去南边不远即是
大理城，东面有太和城，另有道路通向西北。此附近居民以乌夷、台
夷为主，也有少量摆夷。
LONG );
        set("objects", ([
           "/d/dali/npc/tshangfan": 1,
           "/d/dali/npc/wshangfan": 1,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : "/d/dali/cangshan",
            "northwest"  : "/d/dali/cangshanzhong",
            "south"      : "/d/dali/ershuiqiao",
        ]));
	set("coor/x", -19170);
	set("coor/y", -6830);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}