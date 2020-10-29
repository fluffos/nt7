inherit DEMONROOM;

void create()
{
        set("short", "蛇洞外");
        set("long",@LONG
这是神龙岛蛇洞外，据说洞内毒蛇遍布，洞中住有蛇精，没有人进去后
能再活着出来。
LONG);

	set("exits", ([
		"north"   : __DIR__"dong2.15",
		"enter"   : __DIR__"shedong1",

	]));

		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
