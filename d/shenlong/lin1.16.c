inherit DEMONROOM;

void create()
{
        set("short", "东部丛林危险地带");
        set("long",@LONG
这是神龙岛原始丛林深处，再往前走就是危险地带了，小心。
LONG);

	set("exits", ([
		"enter"  : __DIR__"lin1.17", 
		"west"  : __DIR__"lin1.15",
		"south" : __DIR__"xiaoxi1",
		"east" : __DIR__"haitan1",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 1);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/qingshe");

        set("outdoors", "shenlong");
        setup();
}
