inherit ROOM;

void create()
{
        set("short", "北树林");
        set("long", @LONG
这里生长的尽是几人合抱的大树，几乎都看不倒路了，光线更加
昏暗。各种动物在林间跳来跳去，使这里充满了勃勃生机。
LONG);
        set("exits", ([
                "south" : __DIR__"shulin",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("objects", ([
                "/clone/quarry/tu" : 40 + random(20),
        ]));
        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}