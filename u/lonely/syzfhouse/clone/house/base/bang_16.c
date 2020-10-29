
inherit "/inherit/room/house_base";

void create()
{
    set("short", "终南山脚");
    set("long", @LONG
这里已是终南山脉地界，一条山道蜿蜒通向山顶的云雾中，从中
仿佛能看见巍峨耸立的重阳宫。一片宅院掩映在道旁的树林间，看上
去似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "northwest" : "/d/quanzhen/shanjiao1",
    ]));

    set("outdoors", "quanzhen");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
