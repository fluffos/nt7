//Room: jiulou.c

inherit ROOM;

void create()
{
        set("short", "望星楼");
        set("long", @LONG
望星楼飞檐碧瓦，酒幌高挑，是个二层楼。楼上设有回廊，雕梁
画柱，华丽铺排。下面是青砖墙皮，洞开的小窗绘成红框，十分素雅。
楼上正中，挂着一块黑漆漆的横匾，上面的三个绣金大字『望星楼』
是以狂草书成，笔力雄劲，灵动欲飞。
LONG );
        set("exits", ([
                "south" : "/d/changan/qixiang1",
                "up" : "/d/changan/jiulou2",
        ]));
        set("objects", ([
                "/d/changan/npc/xiaoer2" : 1,
        ]));

        set("coor/x", -10750);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}