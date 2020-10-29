#include <ansi.h>
inherit ROOM;

int do_ci(string arg);
int do_zhan(string arg);

void create()
{
        set("short", "密室");
        set("long", @LONG
这里是古墓中的密室，四周密不透风，你只能借着墙上昏暗的灯
光来勉强分辨方向。墙是用整块的青石砌合起来的，接合的甚是完美，
你难以从中找出一丝缝隙。你正在欣赏，突然间发觉墙上似乎有几块
砖 (brick)高高凸起，与周围的砖很不和谐。
LONG );

        set("exits", ([
                "up" : __DIR__"hanshuitan",
        ]));

        set("item_desc", ([
        "brick": HIC "\n几块普通的青砖，看不出有什么特别的。\n" NOR,
        ]) );

        setup();
}

void init()
{
        add_action("do_ci", "ci");
        add_action("do_zhan", "zhan");
}


int do_ci(string arg)
{
        object me=this_player();
        object weapon;

        if( !arg || arg != "brick" ) {
                return notify_fail("你要刺什么？\n");
        }

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("要刺墙不用家伙恐怕不行吧！\n");

        message_vision(HIG "\n$N" HIG "拔出兵刃，向青砖轻轻刺去，只听得空空作声，青砖"
                       "的另一头仿佛是空的。\n", this_player());

        set_temp("tmarks/砖", 1, me);
        return 1;
}

int do_zhan(string arg)
{
        object me=this_player();

        if( !arg || arg != "brick" || query_temp("tmarks/砖", me)<1 ) {
                return notify_fail("你要粘住什么？\n");
        }

        message_sort(HIC "\n$N" HIC "双手紧贴青砖，使个‘粘’字诀，轻轻巧巧"
                     "地将这块青砖粘了出来。如此没粘到几块砖，墙壁上就现出了"
                     "一个大洞。\n" NOR,this_player());

        set("exits/down",__DIR__"houting");

        remove_call_out("close");
        call_out("close", 5, this_object());

        set_temp("tmarks/砖", 0, me);
        return 1;

}

void close(object room)
{
        message("vision", NOR + WHT"\n过不多一会儿，梁上落下几块青砖，又"
                "将墙上的洞遮住了。\n" NOR, room);

        delete("exits/down", room);
}
