// wofang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "卧房");
    set("long", @LONG
这是主人的卧室，收拾得井井有条。推开窗户可以看到下面的花园，
隐隐可嗅到阵阵花香，非常惬意。
LONG);

    set("exits",
    ([
        "down"  : __DIR__"houting",
    ]));

    set("sleep_room", 1);
    set("no_fight", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
