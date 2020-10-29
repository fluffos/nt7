//Room: qixiang2.c

inherit ROOM;

void create ()
{
        set ("short", "麒祥街");
        set("long", @LONG
麒祥街是长安城北一条东西向的大道，街面宽敞洁净，街上十分
热闹，人来人往川流不息。大街的两旁商家云集，大大小小的店铺比
邻而立。街的北边熙熙攘攘的是一家茶馆，茶馆的对面是一家水果店。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/fruit-shop",
                "north" : "/d/changan/tea-shop",
                "west" : "/d/changan/qixiang1",
                "east" : "/d/changan/qixiang3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10740);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}