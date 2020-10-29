inherit ROOM;

void create()
{
        set("short", "小山坡");
        set("long", @LONG
这里是一处小山，到处长满了过人高的长草，东面是一处乱坟岗，
听说经常闹鬼，所以没人敢去。一阵冷风刮来，吓的你根根体毛竖起！
LONG );
        set("exits", ([
                "southdown" : __DIR__"houmen",
                "eastdown" :__DIR__"luan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7120);
	set("coor/y", -2010);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}