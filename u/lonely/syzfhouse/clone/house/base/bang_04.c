
inherit "/inherit/room/house_base";

void create()
{
    set("short", "孤山脚下");
    set("long", @LONG
沿路柏翠松苍，阳光自树梢透入，平添了不少的肃穆之气。再向
南行，可见一座微微隆起的山丘，当地人名之曰孤山。山脚下座落着
好大的一片宅院，看上去似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "north"  : "/d/linan/gushan-jiao",
    ]));

    set("outdoors", "linan");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
