// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;

int do_suicide1(string arg);
int do_suicide2(string arg);
void create()
{
        set("short", "洞穴");
        set("long", @LONG
山岩下秘洞，曲折深邃，有如诸葛武侯之八卦迷阵一般，幽谜繁
复处尤有过之。越是深入越是阴湿黝暗，到后来竟已难见五指。洞穴
四面都是山，都是树，雨后的山谷潮湿而新鲜，就像是个初浴的处女。
洞穴的四壁画满了图画，画的却不是人间，而是天上。
LONG
        );
        set("coor/x",2000);
        set("coor/y",-210);
        set("coor/z",0);
        set("no_magic",1);
        set("no_spells",1);
        set("no_fight",1);
        set("no_get_from",1);
        setup();
}

void init()
{
        add_action("do_suicide1", ({ "ci hou", "ci" }));
        add_action("do_suicide2", ({ "zhuang qiang", "zhuang" }));
}

int do_suicide1(string arg)
{
        object weapon;
        object me = this_player();

        weapon=query_temp("weapon", me);
        
        if (! weapon)
                return notify_fail("你没有拿武器怎么刺喉自杀？\n");

        tell_object(me, HIW "你回忆起以前的经历，想想现在的处境，顿时心灰意冷，觉得已无意念继续活下去。\n\n" NOR);
             
        message_vision(HIW "$N" HIW "拿起手中的" + weapon->name() + HIW "朝自己喉咙刺去。\n" NOR, me);        
        message_vision("突然一条淡淡的影子，带着种淡淡的香气，从$N" 
                                   "面前飞了过去，瞬间夺下" + weapon->name() + "后消失不见。\n", me); 
        
        weapon->move("/d/yuanyue/gu5");
        
        tell_object(me, HIW "此时的你一心想自杀，连手中兵器被夺，也未去细想。\n" NOR);
        set_temp("mojiao/suicide", 1, me);
        return 1;
}

int do_suicide2(string arg)
{
        object me = this_player();
                
        if( !query_temp("mojiao/suicide", me) )
                return notify_fail("你想要干什么？\n");
                
        tell_object(me, HIW "你此时一心只想自杀，口中喃喃念道：没有兵器我撞墙还不行吗？！\n\n" NOR);
             
        message_vision(HIW "$N" HIW "腾空飞起将头朝洞穴的墙壁直撞而去。\n" NOR, me);  
        
        message_vision(HIW "突然只闻一声娇呼“且慢”，一条身影飞驰而过将$N" HIW "的身体从空拉住，\n"
                           "却不知为时已晚，$N" HIW "的头部已经撞上洞穴的墙壁，顿时昏了过去。\n" NOR, me);  
                                 
        tell_room(environment(me),"说时迟，那时快，那条身影毫无停留将"+query("name", me)+
                                   "抱起，朝洞穴深处飞了过去，瞬间消失不见。\n", me); 
        
        me->unconcious(); 
        me->move("/d/yuanyue/gu5");
        me->revive();
        
        delete_temp("mojiao/suicide", me);
        return 1;
}
