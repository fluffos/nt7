//Room: /d/dali/shulinwai.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","树林外");
        set("long", @LONG
你来到了一片黑森森的树林面前，放眼望去，密密麻麻的都是树
木，而且荆棘丛生，隐约可见有些小路东盘西曲。你仔细观察，发现
这显然是个人造的迷宫。其中暗合五行八卦，奇门遁甲，端的非同小
可，千万不要冒然进去。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/heilongling",
            //"south"      : __DIR__"maze1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19110);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}