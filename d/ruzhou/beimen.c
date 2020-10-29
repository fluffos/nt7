inherit ROOM;

void create()
{
        set("short", "北城门");
        set("long", @LONG
这里是汝州的北城门。这里的行人不少。这里有几个官兵正在检查
来往的百姓。旁边还站着几个军官，耀武扬威地站在那里，不停地指手
画脚。
LONG
        );

        set("exits", ([
                "south" : __DIR__"beidajie",
                "north" : "/d/beijing/road10",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
