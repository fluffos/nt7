// wofang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "花园");
    set("long", @LONG
这里是位于中庭的花园，种植着许多产自五湖四海，名山大川的奇花
异草，美丽非常。
LONG);

    set("exits",
    ([
        "north" : __DIR__"houting",
        "south" : __DIR__"qianting",
    ]));

    set("outdoors", "OUTDOORS");
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
