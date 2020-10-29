
inherit "/inherit/room/house_base";

void create()
{
    set("short", "惠山峰腰");
    set("long", @LONG
此处位于惠山峰腰东侧，山路曲曲折折，满山青松绰约，四周花
草成丛，林荫茂盛。绿树掩映间，隐隐可见有好大一片宅院，似乎是
某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "west"  : "/d/wuxi/shanlu",
    ]));

    set("outdoors", "wuxi");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
