//mudong.c
// This is a room made by Wsl.
inherit ROOM;
int do_use(string arg);
void create()
{
        set("short", "墓穴");
        set("long", @LONG
你隐约看到四周的墙上插着六柄火把。
LONG );
        setup();
}
void init()
{
        add_action("do_use", "use");
}
int do_use(string arg)
{
        object me,ob;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if (!present("fire",me)) return 0;
        if( arg=="fire" ) {
        remove_call_out("close");
        call_out("close", 5, this_object());
             write(
"你取出火折一晃，凑上前去点燃了其中的一只火把，也不知是什么机关，
其它的五只火把一一燃了起来。\n");
        set("long", @LONG
洞内一片凌乱，各种盔甲兵刃散落在地上，洞壁上刻了各种各样
的图案，出口四通八达，也不知暗藏了什么机关暗器。
LONG
        );
        set("exits", ([
                "north" : __DIR__"mudong"+random(10),
                "south" : __DIR__"mudong"+random(10),
                "east" : __DIR__"mudong"+random(10),
                "west" : __DIR__"mudong"+random(10),
        ]));
           if ( objectp(ob=present("fire", this_player())) && !userp(ob))     {
            destruct(ob);
        return 1;
       }
        return notify_fail("你想点燃什么？\n");
        }
}

void close(object room)
{
        message("vision","不一会儿，墙上的火把就熄灭了。\n", room);
        set("long", @LONG
你隐约看到四周的墙上插着六柄火把。
LONG
);
        delete("exits", room);
}
