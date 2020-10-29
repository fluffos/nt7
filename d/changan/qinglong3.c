//Room: qinglong3.c

inherit ROOM;
void create ()
{
        set ("short", "青龙街");
        set("long", @LONG
青龙街是长安城中心大街，青石板路笔直的伸展出去，一路上行
人比肩，笙歌处处。景物之美，直如神仙境地。南面就是长安府的总
督衙门了。因为有它建在这里，所以这里的治安很好，大街上的行人
也并不用为安全担心。
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "south" : "/d/changan/yamen",
                "west" : "/d/changan/qinglong2",
                "east" : "/d/changan/fengxu5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}