//Room: /d/dali/shuangheqiao.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","双鹤桥");
        set("long", @LONG
这是一个岔路口，北边是座青石拱桥名叫双鹤桥，此桥跨在绿玉
溪上，桥北即是大理城，由此南去是通往南方的喜州、龙口等城镇的
官道，东去的岔路通往广西，沿绿玉溪南岸西行可达五华楼。
LONG );
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"     : "/d/dali/southgate",
            "west"      : "/d/dali/luyuxi",
            "south"     : "/d/dali/road4",
            "southeast" : "/d/dali/road5",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19130);
	set("coor/y", -6920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}