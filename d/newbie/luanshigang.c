inherit ROOM;

void create()
{
        set("short", "乱石岗");
        set("long", @LONG
山路渐渐爬到了尽头，眼前突然出现一片难见的开阔地来。
这是一片怪石林立的小山岗，只见那些石头千姿百态，除了有
点荒凉外，倒是有种诡异的美丽。
LONG);
        set("exits", ([
                "north" : __DIR__"zhulin",
                "west" : __DIR__"houcun-shanlu",
                 "southeast" : __DIR__"luanfengang",
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