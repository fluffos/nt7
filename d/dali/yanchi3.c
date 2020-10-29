//Room: /d/dali/yanchi1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","沿池堤岸");
        set("long", @LONG
这里是滇池游客聚集之处，演鄯候高生世就时时承舟优胜于烟水
缈蔼的滇池，欣赏『梵刹于滇波向仰抑』的美景，并常停舟官渡，饮
酒赋诗，被称之为『停舟烟会』。这里的东浦彩虹、西山白雨、空中
鹭鸶、晚霞潮红、归帆远影、无不给人以美的享受。
LONG );
        set("objects", ([
           "/d/dali/npc/guigongzi": 1,
           "/d/dali/npc/enu": 2,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "west"      : "/d/dali/yanchi2",
            "southeast" : "/d/dali/luojiadian",
        ]));
	set("coor/x", -19080);
	set("coor/y", -6860);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}