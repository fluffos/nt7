// dongxiang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "讲武堂");
    set("long", @LONG
这里是帮内人士探讨武功的地方。
LONG);

    set("exits",
    ([
        "west" : __DIR__"xiaoting",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
