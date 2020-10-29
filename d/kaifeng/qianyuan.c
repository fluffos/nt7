inherit ROOM;

void create()
{
        set("short", "前院");
        set("long", @LONG
一带粉成黄色的围墙圈起这个院子，一条青石道通向北面的天王
殿，南面就是相国寺的大门，东边一座高楼是鼓楼，西面是钟楼。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"xianguosi",
                  "north" : __DIR__"tianwang",
                  "east" : __DIR__"gulou",
                  "west" : __DIR__"zhonglou",
        ]));
        set("outdoors", "xiangguosi");

	set("coor/x", -5040);
	set("coor/y", 2180);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
