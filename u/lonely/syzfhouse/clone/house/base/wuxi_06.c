
inherit "/inherit/room/house_base";

void create()
{
    set("short", "皇亭街己号");
    set("long", @LONG
这其实是一条比较宽的巷子，不过在江南就叫做大街了，路上的石
板都是新铺的，既干净又平整。街两边都是民宅。
LONG);

    set("exits",
    ([
        "west"  : __DIR__"wuxi_05",
        "south" : __DIR__"wuxi_08",
        "north" : "/d/wuxi/huangting-xi2",
    ]));

    set("outdoors", "wuxi");
    set("max_build", 4);
    set("can_build", "user");

    setup();
    restore();
}
