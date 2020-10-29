inherit ROOM;

void create()
{
        set("short", "全聚德酒楼");
        set("long", @LONG
这里就是京城中最为著名的全聚德酒楼。方圆数百里内提起全聚
德酒楼的烤鸭可以说是无人不知，无人不晓。楼内玲珑八角，红木铺
地，雕栏玉砌，飞檐上还挂着几个大红灯笼，装潢很是幽雅华丽。店
小二抄着一口流利的京腔热情的招呼着客人。酒楼西墙边有一个楼梯，
通往全聚德酒楼二楼的雅座。
LONG );
        set("exits", ([
                "south" : "/d/beijing/wang_10",
                "up"   : "/d/beijing/quanjudeup",
        ]));
        set("objects", ([
                "/d/beijing/npc/xiaoer1" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}