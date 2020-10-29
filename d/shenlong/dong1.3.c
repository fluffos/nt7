inherit DEMONROOM;

void create()
{
        set("short", "幽深隧道");
        set("long",@LONG
这是一条幽深的隧道深不见底。
LONG);

	set("exits", ([
		"east"   : __DIR__"dong1.2",
		"west"   : __DIR__"dong1.4",

	]));

		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 5);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
