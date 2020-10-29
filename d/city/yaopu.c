// Room: /city/yaopu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "药铺");
        set("long", @LONG
这是一家药铺，一股浓浓的药味让你几欲窒息，那是从药柜上的
几百个小抽屉里散发出来的。神医平一指坐在茶几旁，独自喝着茶，
看也不看你一眼。一名小伙计站在柜台后招呼着顾客。柜台上贴着一
张发黄的广告(guanggao)。
LONG );
	set("item_desc", ([
		"guanggao" : "本店出售以下药品：
雄黄：\t十两白银
其他神药与老板面议。\n",
	]));
	set("objects", ([
		"/d/city/npc/ping" : 1,
		"/d/city/npc/huoji" : 1,
	]));
        set("no_fight", 1);    
        set("no_sleep_room", 1);
	set("exits", ([
                 "up" : "/d/city/chanfang",
		"south" : "/d/city/dongdajie2",
	]));
	set("coor/x", 20);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}