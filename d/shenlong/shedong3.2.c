inherit DEMONROOM;

void create()
{
        set("short", "毒蛇窟");
        set("long",@LONG
这是蛇洞内的毒蛇窟，只见四周满是毒蛇，恐怖非常。
LONG);

	set("exits", ([
		"south"  : __DIR__"shedong3.1",
		"north"  : __DIR__"shedong3.3"
	]));

		set("n_time", 15);
		set("n_npc", 3); 
		set("n_max_npc", 8);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        setup();
}
