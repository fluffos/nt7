inherit ROOM;

void create()
{
        set("short", "南树林");
        set("long", @LONG
这里长满了高大的树木，尽是碗口般粗大的树木，
在树木的掩映下，光线也昏暗下来。各种小动物在林
间跳来跳去，使这里充满了勃勃生机。
LONG);
        set("exits", ([
                "west" : __DIR__"zhulin",
                "north" : __DIR__"beishulin",
        ]));

        set("xinshoucun", 1);
            set("outdoors", "newbie");

           set("objects", ([
                "/clone/quarry/tu" : 40 + random(30),
           ]));
        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}