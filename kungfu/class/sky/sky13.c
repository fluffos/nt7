#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【天外天】" NOR);
        set("long", HIW @LONG

                天         外         天

    这里已是天界的尽头，四周一片天际，茫茫无边。远方不时的有
一两道光芒划过，衬托着原本苍白的天际。俯瞰而去，白云茫茫，云
气正在向四处蔓延，似乎永无止尽。偶尔有阵阵梵音飘荡而出，却又
使这里充满着生气。不远处站着一位老者和一位年亲人，似乎正注视
着你。

LONG NOR );

        set("sleep_room", 1);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/tongtian": 1,
                __DIR__"npc/tianshen": 1,
        ]));

        set("exits", ([
                "out" : "/d/city/wumiao",
        ]));
        set("sky", 1);
        setup();
}

void init()
{
        object me = this_player();
        
        if (! me->query("sky12/tianmen") && userp(me))
        {
                tell_object(me, HIG "通天老仙对你说道：你没有使用过东皇钟，是怎么到天界来的，哼！\n" NOR);

                me->delete("sky12");
                me->save();
                me->move("/d/city/wumiao");
                
                //destruct(me);                
        }
        return ;        
}
