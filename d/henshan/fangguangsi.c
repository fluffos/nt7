inherit ROOM;

void create()
{
        set("short", "方广寺");
        set("long", @LONG
方广寺在莲花峰之下。莲花峰有八个山头，犹如金莲瓣瓣，方广
寺就建在这莲花中心的一片平地上。深邃幽雅，有「不游方广寺，不
知南岳之深」之说，故「方广寺之深」为衡山大四绝之一。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"shanjian",
                "eastup"     : __DIR__"shanlu10",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 4,
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6990);
	set("coor/y", -5550);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}