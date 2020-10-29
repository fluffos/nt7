// Room: /d/xiangyang/yaopu.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "药铺");
        set("long", @LONG
药铺不大，却异常的整洁；正面是柜台，柜台后面是个大柜子几
百个小抽屉上一一用红纸标着药材的名称；靠近屋顶的墙上悬着一块
黑底金字的匾额，写着『妙手回春』。地下几个伙计正在分拣刚刚收
购来的草药。东边一张小韩桌儿，上面放着笔墨纸砚，桌后坐着一位
老郎中。一股刺鼻药味充满了整个房间。
LONG );
        set("exits", ([
                "north" : __DIR__"eastjie1",
        ]));
        set("objects", ([
                "/d/city/npc/huoji" : 1,
        ]));
        set("coor/x", -7810);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}