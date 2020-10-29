// Room: /d/suzhou/nandajie2.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
你走在一条繁华的街道上，向南北两头延伸。北边通往城南大街
的中心地段，东面是听雨轩，西面是留园，望南面，是苏州城的南城
门。所谓上有天堂，下有苏杭，此言的确不错。如果在这里生活绝对
是人间福地。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"tingyu",
                "west"  : __DIR__"liuyuan",
                "north" : __DIR__"nandajie1",
                "south" : __DIR__"nanmen",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
}
