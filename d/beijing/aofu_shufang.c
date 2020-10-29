#include <ansi.h>
#include <room.h>
inherit ROOM;

string look_hua();
int valid_leave();

void create()
{
        set("short", "鳌拜书房");
        set("long", @LONG
这里是鳌拜书房，却没有一本书。各种古玩琳琅满目，商
周青铜、汉瓦当、唐三彩，珍珠宝石，应有尽有，只要拥有其
中一件，就够你吃一辈子了。北面墙上有一副画(hua)。
LONG);

        set("exits", ([
                "east" : __DIR__"aofu_zoulang3",
        ]));
        set("objects", ([
                "/d/beijing/npc/shizhe" : 1,
        ]));
        set("item_desc", ([
                "hua" : (: look_hua :),
        ]));
        set("coor/x", -2840);
        set("coor/y", 7790);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_xian", "xian");
        add_action("do_turn", "turn");
}

string look_hua()
{
        object me = this_player();

        if (query("score", me) < 3000)
                return WHT "\n这是一幅陈旧的画卷，没有"
                       "什么不同。\n" NOR;

        set_temp("marks/画1", 1, me);
        return WHT "\n这是一幅陈旧的画卷，画中一处微微"
               "隆起，你忍不住便想掀开看看。\n" NOR;
}

int do_xian(string arg)
{
        object me = this_player();

        if (! arg || arg != "hua")
                return 0;

        if( !query_temp("marks/画1", me) )
                return 0;

        write(HIC "\n你掀开画卷，发现后面竟隐藏着一个把"
              "手，似乎可以转动。\n" NOR);
        set_temp("marks/画2", 1, me);
        return 1;
}

int do_turn(string arg)
{
        object ob, me = this_player();

        if (! arg || arg != "bashou")
                return 0;

        if( !query_temp("marks/画2", me) )
                return 0;

        if (query("exits/down"))
                return notify_fail("你拉了拉把手，但似乎没什么作用。\n");

        message_vision(HIY "\n$N" HIY "拉了拉把手，地面忽然「喀"
                       "喀喀」现出一个洞口。\n\n" NOR, me);
        set("exits/down", __DIR__"aofu_mishi");
        remove_call_out("close");
        call_out("close", 8, this_object());

        return 1;
}

void close(object room)
{
        message("vision", WHT "地面忽然「喀喀喀」缩回原地，把密道的入口挡"
                          "住了。\n" NOR, room);
        delete("exits/down", room);
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/画1", me);
        delete_temp("marks/画2", me);
        return ::valid_leave(me, dir);
}
