//Room: fufeng1.c

inherit ROOM;

void create ()
{
        set ("short", "扶风道");
        set("long", @LONG
扶风道是长安城中心大街，青石板路笔直的伸展出去，一路上行
人比肩，笙歌处处。景物之美，直如神仙境地。东边是白虎街。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "south" : "/d/changan/fufeng2",
                "east" : "/d/changan/baihu1",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10740);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}