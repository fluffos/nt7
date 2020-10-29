//Room: baihu3.c

inherit ROOM;

void create ()
{
        set ("short", "白虎街");
        set("long", @LONG
青龙街是长安城中心大街，青石板路笔直的伸展出去，一路上行
人比肩，笙歌处处。景物之美，直如神仙境地。北面东边传出朗朗的
读书声，那里是当朝的学府国子监。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "north" : "/d/changan/guozijian",
                "west" : "/d/changan/baihu2",
                "east" : "/d/changan/fengxu1",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}