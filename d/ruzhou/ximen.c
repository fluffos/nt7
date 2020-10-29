inherit ROOM;

void create()
{
        set("short", "西城门");
        set("long", @LONG
这里是汝州的西城门。这里的行人不少。这里有几个官兵正在检查
来往的百姓。旁边还站着几个军官，耀武扬威地站在那里，不停地指手
画脚。
LONG
        );

        set("exits", ([
                "east" : __DIR__"xidajie",
                "west" : "/d/songshan/taishique",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6780);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
