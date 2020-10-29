//Room: gongbu.c

inherit ROOM;

void create ()
{
        set ("short", "工部");
        set("long", @LONG
这里是毗邻南安大道的工部工厂集中地区，并没有行政机构，但
是外地运来的各种珍贵资源都在这里加工形成上好的用材，然后封存
入库或是转运各地。附近的工厂里面尽是天下的能工巧匠。
LONG );
        set("exits",  ([ //sizeof() == 2
                "west"  : __DIR__"nanan-dadao",
                "north" : __DIR__"gongbu-tong",
                "south" : __DIR__"gongbu-shi",
        ]));

        set("coor/x", -10710);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}