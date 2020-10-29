//Room: qinglong2.c

inherit ROOM;

void create ()
{
        set ("short", "青龙街");
        set("long", @LONG
青龙街是长安城中心大街，青石板路笔直的伸展出去，一路上行
人比肩，笙歌处处。景物之美，直如神仙境地。往北就是故皇宫的金
水桥了，南面有一条大路通向长安城南门。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "north" : "/d/changan/bridge2",
                "south" : "/d/changan/nanan-dadao",
                "west" : "/d/changan/qinglong1",
                "east" : "/d/changan/qinglong3",
        ]));

        set("objects", ([ //sizeof() == 3
               "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}