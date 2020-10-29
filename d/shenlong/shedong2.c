inherit DEMONROOM;

void create()
{
        set("short", "毒蛇窟");
        set("long",@LONG
这是蛇洞内的毒蛇窟，只见四周满是毒蛇，恐怖非常。
LONG);

	set("exits", ([
		"east"  : __DIR__"shedong1", 
		"west"  : __DIR__"shedong2.1",

	]));

		set("n_time", 15); 
		set("n_npc", 3); 
		set("n_max_npc", 8);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
