// Room: /city/zuixianlou2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "醉仙楼二楼");
        set("long", @LONG
这里是醉仙楼正对着街面的二楼，文人学士在这里吟诗作画，富
商土豪在这里大快朵颐，江湖豪客则自然是貂裘换酒，纵情豪饮了。
东边的几间厢房内则有人在举办喜宴，大宴宾客。
LONG );
	set("item_desc", ([
		"paizi" : "本店出售烤鸭及上等花雕酒。\n",
	]));
	set("objects", ([
		"/d/city/npc/xian" : 1,
		"/d/city/npc/guidao" : 1,
                /*CLASS_D("gaibang") + "/kongkong" : 1,*/
	]));
	set("exits", ([
		"down" : "/d/city/zuixianlou",
                "up"   : "/d/city/zuixianlou3",
                "east": "/d/city/zxlpath",
	]));
//	set("no_clean_up", 0);
	set("coor/x", 10);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
