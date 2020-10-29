//Room: fengxu3.c

inherit ROOM;

void create ()
{
        set ("short", "冯诩道");
        set("long", @LONG
冯诩道是长安城中心大街，青石板路笔直的伸展出去，一路上行
人比肩，笙歌处处。景物之美，直如神仙境地。东面有一条大路通往
长安城的东城门。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "north" : "/d/changan/fengxu2",
                "south" : "/d/changan/fengxu4",
                "east" : "/d/changan/dongan-dadao",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}