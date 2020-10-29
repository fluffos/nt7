inherit DEMONROOM;

void create()
{
        set("short", "神秘岩洞冰窖");
        set("long",@LONG
这是神龙岛东南部岩洞深处的一个冰窖，这里异常寒冷。
LONG);

	set("exits", ([
		"south"  : __DIR__"lin1.25", 
		"north"  : __DIR__"lin1.23",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
