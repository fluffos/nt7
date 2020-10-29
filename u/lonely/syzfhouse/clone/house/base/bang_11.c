
inherit "/inherit/room/house_base";

void create()
{
    set("short", "川中驿道");
    set("long", @LONG
这是通往成都的大驿道之侧，路边是丰沃的良田，种着各种各样
的庄稼，经常能看到农民在田里辛勤的工作。向南遥望，隐隐可见有
一大片宅院，看上去似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "northeast" : "/d/sichuan/yidao1",
    ]));

    set("outdoors", "sichuan");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
