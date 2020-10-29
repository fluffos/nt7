inherit DEMONROOM;

void create()
{
        set("short", "九头蛇洞");
        set("long",@LONG
这是蛇洞内的九头蛇洞，据说，这里是九头蛇出没的地方。
LONG);


	set("exits", ([
		"west"  : __DIR__"shedong4.6",		
		"south"   : __DIR__"shedong4.8",
	]));

		set("n_time", 30);
		set("n_npc",1); 
		set("n_max_npc", 2);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/jiutoushe");

        setup();
}
