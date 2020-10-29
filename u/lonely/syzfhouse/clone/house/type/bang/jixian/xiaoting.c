// ting.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "客厅");
    set("long", @LONG
这里是帮内招待八方来客的地方。
LONG);

    set("exits",
    ([
        "south" : __DIR__"wuchang",
        "north" : __DIR__"wofang",
        "west"  : __DIR__"xixiang",
        "east"  : __DIR__"dongxiang",
    ]));

    set("objects", __DIR__"board");

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");
    set("resource/water", "茶水");
    setup();
    restore();
}
