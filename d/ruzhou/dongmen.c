inherit ROOM;

void create()
{
        set("short", "东城门");
        set("long", @LONG
这里是汝州的东城门。从这里是通向嵩山去的必经要道，一旦有
大案发生或是战事起来，立即会在此设卡盘查，平时，官兵也懒得过
来多事。
LONG
        );

        set("exits", ([
                "west" : __DIR__"dongdajie",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6740);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
