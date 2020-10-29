
inherit "/inherit/room/house_base";

void create()
{
    set("short", "皇亭街癸号");
    set("long", @LONG
这其实是一条比较宽的巷子，不过在江南就叫做大街了，路上的石
板都是新铺的，既干净又平整。向内有好大一片宅院，似乎是某个帮会
的驻地所在。
LONG);

    set("exits",
    ([
        "east"  : "/d/wuxi/huangting-nanjie",
    ]));

    set("outdoors", "wuxi");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
