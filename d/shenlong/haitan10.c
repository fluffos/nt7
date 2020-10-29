inherit DEMONROOM;

void create()
{
        set("short", "海滩");
        set("long",@LONG
这是神龙岛东部沿岸沙滩。
LONG);

	set("exits", ([
		"west"  : __DIR__"haitan9", 
		"east"  : __DIR__"haitan11",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/qingshe");

        set("outdoors", "shenlong");
        setup();
}
