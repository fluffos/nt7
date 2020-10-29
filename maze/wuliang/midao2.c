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
	      "south" : __DIR__"midao3",
              "northup" : __DIR__"midao1",
	]));

	setup();
}