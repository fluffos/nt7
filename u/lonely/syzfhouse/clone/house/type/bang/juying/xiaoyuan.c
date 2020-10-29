// xiaoyuan.c

inherit "/inherit/room/house_door";

void create()
{
    set("short", "大门");
    set("long", @LONG
眼前一片大宅院，门头足足高有三丈。朱红油漆大门各是九九八十一
只大铜钉，碗口大的虎头门扣分列门上。门旁汉白玉雕石狮张牙舞爪，气
势不凡。两边白垣乌瓦，院墙蜿蜒，不知占地有多少亩。
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
    set("max_laodu", 6000);
    set("now_laodu", 6000);

    setup();
    restore();
}
