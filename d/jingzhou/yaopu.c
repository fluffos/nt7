inherit ROOM;

void create()
{
        set("short", "药铺");
        set("long", @LONG
这里是一家药铺，一股浓浓的药味让你几欲窒息，那是从药柜上
的几百个小抽屉里散发出来的。神医华陀二世坐在茶几旁，独自喝着
茶，看也不看你一眼。一名小伙计站在柜台后招呼着顾客。
LONG );
        set("objects", ([
                __DIR__"npc/huatuo" : 1,
                __DIR__"npc/huoji" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"beidajie2",
        ]));

        set("coor/x", -7110);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}