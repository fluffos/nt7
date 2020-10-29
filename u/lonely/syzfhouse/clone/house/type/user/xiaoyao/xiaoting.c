// ting.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "客厅");
    set("long", @LONG
一间小小的客厅。
LONG);

    set("exits",
    ([
        "south" : __DIR__"xiaoyuan",
        "north" : __DIR__"wofang",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");
    set("resource/water", "茶水");
    setup();
    restore();
}
