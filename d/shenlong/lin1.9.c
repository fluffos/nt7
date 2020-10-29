inherit DEMONROOM;

void create()
{
        set("short", "东部丛林");
        set("long",@LONG
这是一片原始丛林，阳关被四周高耸的树木遮蔽，异常阴暗。
LONG);

	set("exits", ([
		"east"  : __DIR__"lin1.10", 
		"west"  : __DIR__"lin1.8",

	]));


		
		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/mangshe");

        set("outdoors", "shenlong");
        setup();
}
