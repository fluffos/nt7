// Room: southroad2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "南大街");
        set("long", @LONG
你正走在成都府的南大街上，这是一条宽敞开阔的大路，一直向
两边延伸。路上行人来来往往，好不热闹。一些小商小贩常在这里做
些小买卖。南面是南门，北边一条大道名叫提督街，你一看就知到为
啥那麽安静了。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "north"  : __DIR__"tiduroad",
            "south"  : __DIR__"southgate",
            "east"   : __DIR__"southroad1",
            "west"   : __DIR__"southroad3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}