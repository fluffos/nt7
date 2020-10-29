inherit ROOM;

void create()
{
        set("short", "碎石路" );
        set("long", @LONG
一条碎石铺成的路，平坦宽阔，路的两面。绿树成荫，来往的人
累了都到树下去乘乘凉，歇歇脚，一些小贩也乘机在这里买点吃喝的
东西。从这里向南看去，隐约可以看见奔腾的长江。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaowu",
                "east" : __DIR__"qingshilu1",
                "southwest" : __DIR__"shandao",
           ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("objects", ([
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("coor/x", -7120);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}