#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【通天门】" NOR);
        set("long", HIW @LONG
你来到这里，发现这里茫茫一片云海。眼前一座宏伟的敞开的大
门，大门的柱子旁依偎着一位男子，似乎对你的到来毫不在意。
LONG NOR );
        set("exits", ([
                "enter" : __DIR__"sky1",
]));
        set("sleep_room", 1);
        set("objects", ([
                __DIR__"npc/li": 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object ob;

        if ( dir == "enter" && objectp(present("li xunhuan", environment(me)))
             && me->query("sky12/floor") < 1)
        {
                write(HIG "李寻欢说道：要进入天界得先过我这关！\n" NOR);
                return notify_fail("李寻欢挡住了你的去路。\n");
        }

        tell_object(me,  HIW "\n你进入了十二重天之第一重天……\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", HIM "听说" + me->name() + HIM + "闯入天界第一重天。\n\n" NOR);

        return ::valid_leave(me, dir);
}
void init()
{
        object me = this_player();
        
        if (! me->query("sky12/tianmen") && userp(me))
        {
                tell_object(me, HIG "李寻欢对你说道：你没有使用过东皇钟，是怎么到天界来的，哼！\n" NOR);

                me->delete("sky12");
                me->save();
                me->move("/d/city/wumiao");
                
                //destruct(me);                
        }
        return ;        
}
