//Room: qinglong1.c

inherit ROOM;

void create ()
{
        set ("short", "青龙街");
        set("long", @LONG
青龙街是长安城中心大街，青石板路笔直的伸展出去，一路上行
人比肩，笙歌处处。景物之美，直如神仙境地。南面有一座很具规模
的寺院。偶尔有颂经之声传出。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "south" : "/d/changan/baoxiangsi",
                "west" : "/d/changan/fufeng5",
                "east" : "/d/changan/qinglong2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10730);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}