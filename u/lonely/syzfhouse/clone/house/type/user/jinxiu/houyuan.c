// houyuan.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "后院");
    set("long", @LONG
一间小小的后院。
LONG);

    set("exits",
    ([
        "south" : __DIR__"wofang",
    ]));

    set("outdoors", "OUTDOORS");
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
