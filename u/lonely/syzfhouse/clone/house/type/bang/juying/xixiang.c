// xixiang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "西厢");
    set("long", @LONG
一间位于西侧的厢房。
LONG);

    set("exits",
    ([
        "east"  : __DIR__"zhongting",
        "south" : __DIR__"xiting",
        "north" : __DIR__"xiwo",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
