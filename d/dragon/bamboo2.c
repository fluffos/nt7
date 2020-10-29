// room: well.c
// Jay 4/8/96

#include <ansi.h>
inherit ROOM;

int do_use(string arg);
int do_tui(string arg);

void create()
{
        set("short", "竹径");
        set("long",
"这里竹子很茂密，光线极暗。空气中有淡淡的竹子的清香。在这样的\n"
"地方，会隐藏着什么吗？\n"
);
        set("exits", ([
                "east" : __DIR__"bamboo",
        ]));
        set("no_clean_up", 0);
        set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_use", "use");
        add_action("do_tui", "tui");
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("moonsoul", me))  return 0;
        if( arg=="moonsoul" ) {
             write(
             "你掏出怀中的"+HIC"月魄"NOR+"，"+HIC"月魄"NOR+"发出幽蓝的光芒。岩壁上似乎有道暗门，也许可以试着推(tui)一下。\n"
             );
             set_temp("marks/钻1", 1, this_player());
             return 1;
       }
}

int do_tui(string arg)
{
        object me;
        me = this_player();

        if( query_temp("marks/钻1", me)){
            message("vision", me->name() + "一下子就不见了。\n",
                    environment(me), ({me}) );
            me->move(__DIR__"moonroom");
            message("vision", me->name() + "从岩缝暗门里跌了出来。\n",
                    environment(me), ({me}) );
            delete_temp("marks/钻1", this_player());

            return 1;
        }
        else {
            write("乱推有什么用?!\n");
            return 1;
        }
}
