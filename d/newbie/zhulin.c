inherit ROOM;

void create()
{
        set("short", "竹林");
        set("long", @LONG
这里是一片苍翠的竹林，轻风吹过，竹影摇动。竟让人心里格外
安宁。
LONG);
        set("exits", ([
                "east" : __DIR__"shulin",
                "south" : __DIR__"luanshigang",
        ]));

        set("objects", ([
                 "/clone/quarry/tu" : 30 + random(20),
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("no_pk", 1);
	setup();
}

void init()
{
        object me = this_player();

        if( query("newbie_quest/leixing", me) == "move" )
        set("newbie_quest/completed", 1,  me);
                
}