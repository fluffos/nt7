inherit ROOM;

void create()
{
        set("short", "小溪");
        set("long",@LONG
这是神龙岛东南的一处小溪。
LONG);

	set("exits", ([
		"north"  : __DIR__"xiaoxi1", 		
		"south" : __DIR__"guanlongting",

	]));

        set("outdoors", "shenlong");
        setup();
}
