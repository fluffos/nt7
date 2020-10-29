// road3.c
// by Xiang

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "黄土路");
        set("long", @LONG
你走在一条黄土路上。西面望去，隐隐可以看到平定州。望东，
北京城快到了。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                "east" : "/d/beijing/ximenwai",
                "west" : __DIR__"pingdingzhou",
        ]));
        setup();
}

void init()
{
        object me = this_player();
        if (!objectp(me) || !userp(me)) return;
        message_vision(HIB "夜已经深了，翻过北边的小高岗可以由小路到万安寺。\n"NOR, me);
        remove_call_out("mes");
        call_out("mes",3,this_player());
        set_temp("want_enter", 1, this_player());
        add_action("do_enter", "enter");
}

void mes(object me)
{
        if (!me) return;
        if (environment(me) == this_object())
        message_vision(HIR "你是否愿意进入(enter)万安寺？\n"NOR, me);
} 

int do_enter()
{
        object me = this_player();
        if( query_temp("want_enter", me) )
        {
                tell_object(me, HIR "你决定进入万安寺。\n" NOR);
                me->move("/d/tulong/yitian/was_damen");
        }
        return 1;
}