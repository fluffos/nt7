inherit DEMONROOM;

void create()
{
        set("short", "浅滩");
        set("long",@LONG
这是神龙岛东部沿岸浅滩，你半身置身于水中。
LONG);

	set("exits", ([
		"west"  : __DIR__"haitan12", 
		//"east"  : __DIR__"haitan14",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 10);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/shuishe");

        set("outdoors", "shenlong");
        setup();
}
