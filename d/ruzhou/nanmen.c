inherit ROOM;

void create()
{
        set("short", "南城门");
        set("long", @LONG
这里是汝州的南城门。从这里是通向南阳去的必经要道，一旦有
大案发生或是战事起来，立即会在此设卡盘查，平时，官兵也懒得过
来多事，城门下一片太平盛世景象。
LONG
        );

        set("exits", ([
                "south" : __DIR__"xiaozheng",
                "north" : __DIR__"nandajie",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1840);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
