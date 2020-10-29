inherit DEMONROOM;

void create()
{
        set("short", "广岛");
        set("long",@LONG
深切哀悼在9·18事变中牺牲的烈士，为我们的英雄报仇吧！
LONG);

	set("exits", ([
		"north"   : __DIR__"changqi2",
		"east"   : __DIR__"guangdao2",
		"west"  : __DIR__"guangdao3",
	    "south"  : __DIR__"guangdao4",

	]));

		set("n_time", 30); 
		set("n_npc", 5); 
		set("n_max_npc", 15);
		set("s_npc", "/clone/dream_npc/japangame/japannpc01");

        setup();
}
