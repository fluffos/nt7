
inherit "/inherit/room/house_base";

void create()
{
    set("short", "清名桥畔");
    set("long", @LONG
下得清名桥向东走，沿着护城河畔一条青黄色花岗石铺就的小路
曲折前行，远处隐约可见有好大的一片宅院，看上去似乎是某个帮会
的驻地所在。
LONG);

    set("exits",
    ([
        "west"  : "/d/wuxi/qiao3",
    ]));

    set("outdoors", "wuxi");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
