inherit DEMONROOM;

void create()
{
        set("short", "日本岛西岸");
        set("long",@LONG
深切哀悼在9·18事变中牺牲的烈士，为我们的英雄报仇吧！
LONG);

	set("exits", ([
		"west"   : __DIR__"japan3",
		"east"   : __DIR__"changqi1",
		"north"  : __DIR__"daban1",
	    "south"  : __DIR__"siguo1",

	]));

		set("n_time", 30); 
		set("n_npc", 5); 
		set("n_max_npc", 15);
		set("s_npc", "/clone/dream_npc/japangame/japannpc01");

        setup();
}
