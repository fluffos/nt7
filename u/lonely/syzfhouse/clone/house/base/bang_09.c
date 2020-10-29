
inherit "/inherit/room/house_base";

void create()
{
    set("short", "沧州镇东");
    set("long", @LONG
此处位于沧州镇外不远，沿着中原驿道向西行走，便可进入沧州
镇。道旁杨树林齐齐地立着，衬着其间气派不凡的一大片宅院，看上
去似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "west" : "/d/ruzhou/cang-dong",
    ]));

    set("outdoors", "ruzhou");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
