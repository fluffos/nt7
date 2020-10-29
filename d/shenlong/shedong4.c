inherit DEMONROOM;

void create()
{
        set("short", "毒蛇窟");
        set("long",@LONG
这是蛇洞内的毒蛇窟，只见四周满是毒蛇，恐怖非常。
LONG);


	set("exits", ([
		"north"  : __DIR__"shedong1",		
		"south"  : __DIR__"shedong4.1",
	]));

		set("n_time", 60);
		set("n_npc", 3); 
		set("n_max_npc", 5);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
