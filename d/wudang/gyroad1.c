inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "果园小路");
        set("long", @LONG
眼前豁然开朗，你轻松地走在果园边的小路上。路上落英缤纷，
两边是桃树林，盛开着粉红的桃花，红云一片，望不到边。还可以看
蜜蜂「嗡嗡」地在花间飞上飞下忙个不停，间或传来猿猴的叽咋声。
LONG );
        set("outdoors", "wudang");

        set("exits", ([
                "west" : __DIR__"tyroad13",
                "east" : __DIR__"gyroad2",
        ]));
        set("objects", ([
                "/clone/beast/mangshe": 1
        ]));
        set("coor/x", -250);
        set("coor/y", -310);
        set("coor/z", 30);
        setup();
}

int valid_leave(object me, string dir)
{
        if ( dir == "east" && objectp(present("mang she", environment(me))))
                return notify_fail(HIG "但见巨蟒一个盘身，顿时挡住了你的去路。\n" NOR);

        return ::valid_leave(me, dir);
}
