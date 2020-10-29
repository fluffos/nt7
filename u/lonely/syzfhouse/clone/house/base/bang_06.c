
inherit "/inherit/room/house_base";

void create()
{
    set("short", "龙泉山麓");
    set("long", @LONG
这里是龙泉山路，再往北走可以通向山中的黑龙潭。往南去则是
有名的石林迷宫。路旁岔出一条不是很长的小径，尽头有好大的一片
宅院，看上去似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "south" : "/d/yunnan/hl-road1",
        "north" : "/d/yunnan/hl-tan",
    ]));

    set("outdoors", "yunnan");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
