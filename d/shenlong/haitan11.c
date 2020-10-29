inherit DEMONROOM;

void create()
{
        set("short", "海边");
        set("long",@LONG
这是神龙岛东部沿岸海边。
LONG);

	set("exits", ([
		"west"  : __DIR__"haitan10", 
		"east"  : __DIR__"haitan12",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 7);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/shuishe");

        set("outdoors", "shenlong");
        setup();
}
