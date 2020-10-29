inherit ROOM;

void create()
{
        set("short", "小溪");
        set("long",@LONG
这是神龙岛东南的一处小溪。
LONG);

	set("exits", ([
		"north"  : __DIR__"lin1.16", 		
		"south" : __DIR__"xiaoxi2",

	]));

        set("outdoors", "shenlong");
        setup();
}
