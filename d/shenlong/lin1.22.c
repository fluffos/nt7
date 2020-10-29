inherit DEMONROOM;

void create()
{
        set("short", "神秘岩洞");
        set("long",@LONG
这是神龙岛东南部的一个岩洞，这里阴暗潮湿，令人觉得毛骨悚然。
LONG);

	set("exits", ([
		"south"  : __DIR__"lin1.23", 
		"north"  : __DIR__"lin1.21",

	]));

		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        set("outdoors", "shenlong");
        setup();
}
