
inherit "/inherit/room/house_base";

void create()
{
    set("short", "山间平台");
    set("long", @LONG
这里是山路以北的一片宽阔平台，站在这里可以俯看双旗镇的全
景。回过头去，从这里仰望白驼山，你就知道这座山名的由来了。峰
顶上有四时不化之积雪。平台内侧有一处恢宏宅院，好像是某个帮会
的驻地。
LONG);

    set("exits",
    ([
        "east"  : "/d/baituo/guangchang",
    ]));

    set("outdoors", "baituo");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
