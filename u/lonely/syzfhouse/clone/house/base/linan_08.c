
inherit "/inherit/room/house_base";

void create()
{
    set("short", "南山路辛号");
    set("long", @LONG
南山路位于西湖之畔，安静幽美。路的两侧划出了很多地块，供
来自各地的大富豪们在此修筑豪宅美院，因此南山路一带也得了西湖
花园的美称。道路并不是很宽，但处处充溢着西子湖独特的风情，茂
盛的树冠将烈日风雨完全地阻在了身外，走在这里，唯一的心情就是
安静甜美。
LONG);

    set("exits",
    ([
        "north" : "/d/linan/nanshan-lu4",
        "west"  : __DIR__"linan_06",
    ]));

    set("outdoors", "linan");
    set("max_build", 4);
    set("can_build", "user");

    setup();
    restore();
}
