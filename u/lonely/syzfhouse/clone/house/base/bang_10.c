
inherit "/inherit/room/house_base";

void create()
{
    set("short", "侯监林内");
    set("long", @LONG
一片北方旷野中常见的树林，树干高大挺直，枝叶稀疏，林间有
条小路蜿蜒穿越，通向远处。一片宅院掩藏在树林之内，看上去似乎
是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "east" : "/d/houjianji/shulin2",
    ]));

    set("outdoors", "houjianji");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
