
inherit "/inherit/room/house_base";

void create()
{
    set("short", "燕山村西");
    set("long", @LONG
沿着燕山村里的小土路一直西行，来到打谷场边的村头，却发现
有好大一片宅院座落于此，看上去似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "east" : "/d/shanhai-guan/chundao3",
    ]));

    set("outdoors", "shanhai-guan");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
