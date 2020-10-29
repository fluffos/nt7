
inherit "/inherit/room/house_base";

void create()
{
    set("short", "华山村东");
    set("long", @LONG
沿着华山村内的碎石路一直向东，走出这个小小村落不多远，却
发现有好大一片宅院座落于此，看上去似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "northwest" : "/d/village/eexit",
    ]));

    set("outdoors", "village");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
