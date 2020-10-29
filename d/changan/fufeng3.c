//Room: fufeng3.c

inherit ROOM;

void create ()
{
        set ("short", "扶风道");
        set("long", @LONG
扶风道是长安城中心大街，青石板路笔直的伸展出去，一路上行
人比肩，笙歌处处。景物之美，直如神仙境地。西面有一条大路通往
长安城的西城门。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "north" : "/d/changan/fufeng2",
                "south" : "/d/changan/fufeng4",
                "west" : "/d/changan/xian-dadao",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10740);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}