// xiaoyuan.c

inherit "/inherit/room/house_door";

void create()
{
    set("short", "大门");
    set("long", @LONG
眼前一片宅院，门头高约两丈，朱红油漆大门各是八八六十四只大铜
钉，碗口大的虎头门扣分列门上。门旁石狮张牙舞爪，气势迫人。两边白
垣乌瓦，院墙蜿蜒，不知占地有多少亩。
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
    set("set_entry", "wuchang");
    set("max_laodu", 3000);
    set("now_laodu", 3000);

    setup();
    restore();
}
