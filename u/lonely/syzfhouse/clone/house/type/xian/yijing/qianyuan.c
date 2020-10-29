// xiaoyuan.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "前院");
    set("long", @LONG
这里似乎非常安静，倒是时不时听见鸟儿唧唧喳喳的叫。院中不少树
木已然有遮天之势，肃穆非常。
LONG);

    set("exits",
    ([
        "south" : __DIR__"xiaoyuan",
        "north" : __DIR__"qianting",
    ]));

    set("owner_name", "某人");
    set("owner", "OWNER");
    set("outdoors", "OUTDOORS");

    setup();
    restore();
}
