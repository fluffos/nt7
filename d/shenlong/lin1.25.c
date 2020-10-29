inherit DEMONROOM;

void create()
{
        set("short", "神秘岩洞冰窖分岔口");
        set("long",@LONG
这是神龙岛东南部岩洞深处的一个冰窖，这里异常寒冷。
LONG);

	set("exits", ([
		"north"  : __DIR__"lin1.24",
		"east"   : __DIR__"dong3",
		"west"   : __DIR__"dong1",
		"south"  : __DIR__"dong2",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 2);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
