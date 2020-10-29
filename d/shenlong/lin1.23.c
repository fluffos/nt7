inherit DEMONROOM;

void create()
{
        set("short", "神秘岩洞结冰路面");
        set("long",@LONG
这是神龙岛东南部岩洞，走在此处路面不知何故已经结了冰。
LONG);

	set("exits", ([
		"south"  : __DIR__"lin1.24", 
		"north"  : __DIR__"lin1.22",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 2);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        set("outdoors", "shenlong");
        setup();
}
