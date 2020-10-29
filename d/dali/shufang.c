//Room: /d/dali/shufang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short", "书房");
        set("long", @LONG
这是大理国镇南王的书房，靠窗放着一个大木桌桌上放着不少书，
靠墙的地方还有一个书架，镇南王经常在这里看书。
LONG );
        set("objects",([
            CLASS_D("dali")+"/zhudanchen":1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/dali/tingfang",
        ]));
	set("coor/x", -19091);
	set("coor/y", -6841);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}