// wofang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "卧房");
    set("long", @LONG
这里是帮主的卧房。
LONG);

    set("exits",
    ([
        "west"  : __DIR__"xiwo",
        "east"  : __DIR__"dongwo",
        "north" : __DIR__"houyuan",
        "south" : __DIR__"zhongting",
    ]));

    set("sleep_room", 1);
    set("no_fight", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
