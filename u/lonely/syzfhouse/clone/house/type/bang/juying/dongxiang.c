// dongxiang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "东厢");
    set("long", @LONG
一间位于东侧的厢房。
LONG);

    set("exits",
    ([
        "west"  : __DIR__"zhongting",
        "south" : __DIR__"dongting",
        "north" : __DIR__"dongwo",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
