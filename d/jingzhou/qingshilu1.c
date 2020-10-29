inherit ROOM;

void create()
{
        set("short", "碎石路" );
        set("long", @LONG
一条碎石铺成的路，平坦宽阔，路的两面。绿树成荫，来往的人
累了都到树下去乘乘凉，歇歇脚，一些小贩也乘机在这里买点吃喝的
东西。
LONG );
        set("exits", ([
                "east" : __DIR__"nanshilu",
                "west" : __DIR__"qingshilu2",
           ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -7110);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}