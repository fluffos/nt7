// Room: /d/shaolin/shijie5.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "石阶");
        set("long", @LONG
一挂巨大的瀑布白龙出霄般横越山间，水气已浓得仿佛可以滴下
水珠儿来。山峦间升起薄弧的青雾，凝聚不散。哗哗的水声震耳欲聋。
石阶上满是水渍，走上去滑得可以让人打跌。。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie4",
                "northup" : __DIR__"shijie6",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
