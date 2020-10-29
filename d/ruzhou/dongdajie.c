inherit ROOM;

void create()
{
        set("short", "东大街");
        set("long", @LONG
这里是汝州城的东大街，街的北面是一家打铁铺，西去是汝州城中
心，东面是去往嵩山的东门，南面也没有什么店铺。
LONG
        );

        set("exits", ([
                "north" : __DIR__"datiepu",
                "west" : __DIR__"ruzhou",
                "east" : __DIR__"dongmen",
        ]));


        set("outdoors", "ruzhou");
	set("coor/x", -6750);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
