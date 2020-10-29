// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "密道");
	set("long", @LONG
这里是密道，黑乎乎的，你只能摸索着向前走，密道上面的就是你进来的
石屋子。你只能很费劲的钻过一个个的密道。
LONG
	);        

	set("exits", ([
	    "southdown" : __DIR__"midao2",
	]));

	setup();
}