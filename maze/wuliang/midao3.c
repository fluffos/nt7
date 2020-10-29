// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "密道");
	set("long", @LONG
这里是密道，黑乎乎的，什么也看不真切，你只能摸索着向前走，很费劲
的钻过一个个的密道。
LONG
	);
        
	set("exits", ([
	     "east" : __DIR__"midao4",
             "north" : __DIR__"midao2",
	]));

	setup();
}