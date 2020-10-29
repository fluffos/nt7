
inherit "/inherit/room/house_base";

void create()
{
    set("short", "莲蓉桥堍");
    set("long", @LONG
莲蓉桥堍颇为空旷，并无多少建筑，行人也甚是稀少。官道之旁
却有一条岔路，延伸向西首，路的尽头有好大一片宅院，看上去似乎
是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "east"  : "/d/wuxi/qiao4",
    ]));

    set("outdoors", "wuxi");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
