
inherit "/inherit/room/house_base";

void create()
{
    set("short", "太平镇北");
    set("long", @LONG
此处位于太平镇北郊之外，平日车马稀少、人迹罕至。稀疏的树
林间掩映着好大的一片宅院，似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "south"  : "/d/wudang/caishi",
    ]));

    set("outdoors", "wudang");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
