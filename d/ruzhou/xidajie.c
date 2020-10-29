inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
北面就是汝州城的知府衙门，虽然未经什么修缮，但是略略掉漆的
红木白墙却显现出一番更加威严肃穆的感觉。东去是汝州城中心，这里
也没有什么店铺。
LONG
        );

        set("exits", ([
                "north" : __DIR__"yamen-damen",
                "south" : __DIR__"yingbin-lou1",
                "west" : __DIR__"ximen",
                "east" : __DIR__"ruzhou",
        ]));


        set("outdoors", "ruzhou");
	set("coor/x", -6770);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
