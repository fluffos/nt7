#include <ansi.h>
inherit ROOM;

#define SCBORN_D       "/adm/daemons/scbornd"

void create()
{
        set("short", NOR + WHT "【通天门外】" NOR);
        set("long", HIW @LONG
你来到这里，发现这里茫茫一片云海。不远处有一道大门，门前站
着一个老者，似乎正注视着你。大门的正中央悬挂着一盏金黄色的长明
灯（changmingdeng for xueyi）。
LONG NOR );
        set("exits", ([
                "enter" : __DIR__"tianmen",
]));
        set("sky", 1);
        set("objects", ([
                __DIR__"npc/xing": 1,
                "/clone/misc/changmingdeng" : 1,
        ]));

        set("no_fight", 1);
        setup();
}

void init()
{
        // this_player()->delete("yhjob");
}

int valid_leave(object me, string dir)
{
        object ob;
        object *inv;
        int i;

        //if (! wizardp(me))return notify_fail("暂不开放！\n");

        if (time() - me->query("last_enter_tianmen0") < 86400)                        
        {
                 return notify_fail("对不起，你距离上次进入天界不足24小时，无法再次进入天界。\n");
        }

        // 进入12重天的条件
        if ( dir == "enter" && ! me->query("sky12/floor"))
        {
               ob = present("xingjun yan", environment(me));
               if (! objectp(ob))return notify_fail("物件出错！\n");
               message_vision(HIC "星君眼仔细的看着$N" HIC " ……\n" NOR, me);

               if (! SCBORN_D->check_data(me))
               {
                            message_vision(HIW "星君眼冷冷地对$N" HIW "说道：你的条件还不"
                                           "够闯天界十二重天。\n" NOR, me);
                                         
                            return notify_fail("\n");  
               }
        }

        if (dir == "enter")
        {
                // 背了人则进入不了
                inv = deep_inventory(me);
                for (i = 0; i < sizeof(inv); i++)
                {
                        if (! playerp(inv[i])) continue;
        
                        // 被人背起的用户
                        return notify_fail(HIW "星君眼冷冷地对$N" HIW "说道：“我看你还是先把" + inv[i]->name() + 
                                           HIW "放下再说吧！\n" NOR);                
                }                
        }

        me->set("last_enter_tianmen0", time());

        return ::valid_leave(me, dir);
}
