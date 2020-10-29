// xiaoyuan.c

inherit "/inherit/room/house_door";

void create()
{
    set("short", "小院");
    set("long", @LONG
一个不大的院子，穿过院子就是一间小屋，屋门紧闭着。
LONG);

    set("exits",
    ([
        "out"    : __FILE__,
    ]));

    set("owner_name", "某人");
    set("owner", "OWNER");
    set("huyuan", __DIR__"huyuan");
    set("outdoors", "OUTDOORS");
    set("set_exits", "north");
    set("set_entry", "xiaoting");
    set("max_laodu", 1500);
    set("now_laodu", 1500);

    setup();
    restore();
}
