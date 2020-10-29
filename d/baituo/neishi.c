#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "内室");
        set("long", @LONG
这是欧阳克的内室，内部摆设很有情趣。屋角摆着一盆名贵兰花，
正骄傲地吐露芳蕊。花盆(pen)下撒落一些浮土，可能是被人搬出去晒
太阳时撒下的。
LONG );
        set("exits", ([
                "east" : __DIR__"huayuan",
        ]));
 
        set("item_desc", ([
                "pen" : WHT "\n这是一个大花盆，看上去非常坚固结"
                        "实，作工也很考究，仔细\n观察下，不难发"
                        "现地上有些浮土，似乎有人移动(move)过花"
                        "盆。\n" NOR,
        ]));
        set("coor/x", -49990);
        set("coor/y", 20050);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        object me = this_player();

        if (arg != "pen")
                return notify_fail("你要搬什么？\n");

        if( query("born_family", me) != "欧阳世家" )
                return notify_fail("你移动了一下花盆，却没发现什么特别的东西。\n");

        if (! query("exits/down"))
        {
                set("exits/down", __DIR__"midao");
                message_vision(HIY "\n$N" HIY "移动花盆，只见花盆下面"
                               "露出一个黑幽幽的洞口。\n\n" NOR, me);
        } else
        {
                delete("exits/down");
                message_vision(HIY "\n$N" HIY "把花盆搬回原位，洞口顿"
                               "时被封住了。\n\n" NOR, me);
        }
        return 1;
}