inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
这是漆黑的密道，当年白驼山弟子为了直达中原而挖凿的。
LONG );
        set("region", "baituo");
        set("exits" , ([
                "east" : "/d/city/guangchang",
                "up"   : __DIR__"neishi",
        ]));
        set("objects",([
                __DIR__"obj/shenshe" : 1 ,
        ]));

        setup();
        replace_program(ROOM);
}