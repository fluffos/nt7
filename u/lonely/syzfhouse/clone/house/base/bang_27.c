
inherit "/inherit/room/house_base";

void create()
{
    set("short", "山坡");
    set("long", @LONG
这里是少室山之阳的一座山坡，坡上长满了艳红色的不知名的野
花，采蜜的蜂蝶们簇成一团团忙碌着。坡上依山而建一座恢宏大院，
似乎是江湖中哪个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "east"  : "/d/shaolin/xiaojing1",
    ]));

    set("outdoors", "shaolin");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
