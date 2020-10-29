inherit DEMONROOM;

void create()
{
        set("short", "仙人掌丛林");
        set("long",@LONG
这是神龙岛东部一片仙人掌丛林，这里四处都是一人高的仙人掌。
LONG);

	set("exits", ([
		"west"  : __DIR__"haitan6", 
		"east"  : __DIR__"haitan8",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/xiangweishe");

        set("outdoors", "shenlong");
        setup();
}
