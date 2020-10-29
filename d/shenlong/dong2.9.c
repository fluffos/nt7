inherit DEMONROOM;

void create()
{
        set("short", "幽深隧道");
        set("long",@LONG
这是一条幽深的隧道深不见底。
LONG);

	set("exits", ([
		"north"   : __DIR__"dong2.8",
		"south"   : __DIR__"dong2.10",

	]));

		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 12);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
