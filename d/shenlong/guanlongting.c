inherit ROOM;

void create()
{
        set("short", "观龙亭");
        set("long",@LONG
这是一处古旧的亭子，不知是什么年代为谁所建。
LONG);

	set("exits", ([
		"north"  : __DIR__"xiaoxi2",
	]));

	set("objects", ([
		__DIR__"npc/yufu" : 1, 
	]));
	//set("no_fight", 1);
        set("outdoors", "shenlong");
        setup();
}
