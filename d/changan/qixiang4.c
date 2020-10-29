//Room: qixiang4.c

inherit ROOM;

void create ()
{
        set ("short", "麒祥街");
        set("long", @LONG
麒祥街是长安城北一条东西向的大道，街面宽敞洁净，街上十分
热闹，人来人往川流不息。大街的两旁商家云集，大大小小的店铺比
邻而立。北边是一家钱庄，可以听到叮叮当当的金银声音。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/qunyulou",
                "north" : "/d/changan/bank",
                "west" : "/d/changan/beian-daokou",
                "east" : "/d/changan/qixiang5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}