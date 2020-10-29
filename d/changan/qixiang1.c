//Room: qixiang1.c

inherit ROOM;

void create ()
{
        set ("short", "麒祥街");
        set("long", @LONG
麒祥街是长安城北一条东西向的大道，街面宽敞洁净，街上十分
热闹，人来人往川流不息。大街的两旁商家云集，大大小小的店铺比
邻而立。街的北边有一座酒楼，对面是一家客栈。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/kezhan",
                "north" : "/d/changan/jiulou",
                "west" : "/d/changan/yongtai-beikou",
                "east" : "/d/changan/qixiang2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10750);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}