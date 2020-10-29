inherit ROOM;

void create()
{
        set("short", "丛林");
        set("long", @LONG
这里是衡山深处的一片树林，据说黄金白玉虎曾在这里出没。
LONG);
        set("exits", ([ 
               "south"       : __DIR__"shanlu14",
        ]));

        set("outdoors", "henshan");

        if (random(10) == 1)
                set("objects", ([
                        "/kungfu/class/misc/goldtiger"  :  1,
                ]));    

	set("coor/x", -6950);
	set("coor/y", -5500);
	set("coor/z", 20);
	setup();
}
