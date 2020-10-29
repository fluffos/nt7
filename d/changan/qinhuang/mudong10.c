//mudong.c
// This is a room made by Wsl.
#include <room.h>
inherit ROOM;
int do_use(string arg);
int do_pull(string arg);
int do_enter(string arg);
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
        add_action("do_pull", "pull");
        add_action("do_enter", "enter");
}
int do_use(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if (!present("fire",me)) return 0;
        if( arg=="fire" ) {
                remove_call_out("cls");
                call_out("cls", 30, this_object());
             write(
"你取出火折一晃，凑上前去点燃了其中的一只火把，也不知是什么机关，
其它的五只火把一一燃了起来。但你发现这样走下去好象永无尽头，难道
真有机关吗？\n");
        set("long", @LONG
洞内一片凌乱，各种盔甲兵刃散落在地上，洞壁上刻了各种各样
的图案，出口四通八达，也不知暗藏了什么机关暗器。
LONG
        );
    set("item_desc", ([
"机关" : "在火把的照明下，你试着仔细观察周围的景象，但始终不能发现什么异样来。\n",
"火把" : "你看了看插在墙上的火把，这火把似乎......\n",
]));
        set("exits", ([
                "north" : __DIR__"mudong"+random(10),
                "south" : __DIR__"mudong"+random(10),
                "east" : __DIR__"mudong"+random(10),
                "west" : __DIR__"mudong"+random(10),
        ]));
        set_temp("dian", 1, me);
        return 1;
       }
        return notify_fail("你想点燃什么？\n");
}
int do_pull(string arg)
{
    string p;
    p=sprintf("%d",query("passwd1", this_player()));
    if( !arg || arg == "" )
    if( !query_temp("dian", this_player()) )
    {
        write("什么？！\n");
        return 1;
    }
    if( arg == p )
    {
        message_vision("$N只觉得一阵地动山摇。\n", this_player());
        message_vision("震动过后，在你脚下的一块石板缓缓的移了开来。\n", this_player());
        set_temp("la1", 1, this_player());
        remove_call_out("close");
        call_out("close", 5, this_player());
        return 1;
    }
    else
    {
        write("你心中不断祈祷，应该是这只吧！！！\n");
        if (random(6) != 4)
                {
            message_vision("$N拉下了其中的一只火把，这时，不知什么地方突然射出一只毒箭，直射向你的脑门。\n", this_player());
            message_vision("$N急忙躲闪开去。但还是被利箭划破了手臂。\n", this_player());
            set_temp("die_for", "被毒箭射", this_player());
            addn("qi", -30000, this_player());
            addn("eff_qi", -20000, this_player());
            return 1;
        }
        else
        {
            if( this_player()->query_skill("dodge",1)<1000 )
            message_vision("$N拉下了其中的一只火把，这时，不知什么地方突然射出一只毒箭，直射向你的脑门。\n", this_player());
            message_vision("$N躲闪不及，毒箭从你的脑门对穿而过......\n",this_player());
            set_temp("die_for", "被毒箭射", this_player());
            this_player()->die();
            return 1;
        }
    }
}
int do_enter(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( !query_temp("la1", me))return 0;
        if( !query("passwd1", me))return 0;
        if( arg=="洞" ) {
             message_vision("$N战战兢兢的爬了进去。\n",me);
        me->move("/d/changan/qinhuang/mumen.c");
        delete_temp("dian", me);
        delete("passwd1", me);
        }       
          return 1;
}
void close(object me)
{
        message("vision","轰隆隆的响声响过之后，石板又合上了。\n", this_object());
        delete_temp("la1", me);
}

void cls(object room)
{
        message("vision","不一会儿，火把就熄灭了。\n", room);
        set("long", @LONG
你隐约看到四周的墙上插着六柄火把。
LONG
);
        delete("item_desc");
        delete("exits", room);
}
