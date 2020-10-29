// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        int i;
        if( !query("bunch/bunch_name", me) )
                return notify_fail("你没有参加任何帮会，无法通过切蹉武功征招NPC。\n");
                
        if (! arg)
                return notify_fail("你要和谁切磋武功？\n");
                
        if (! ob = present(arg, environment(me)))
                return notify_fail("这儿没有这么个人。\n");
                
        if (! ob->is_character())
                return notify_fail("看清楚！那并不是个生物。\n");
                
        if (playerp(ob))
                return notify_fail("你只能与NPC切蹉武功。\n");
                
        if (! living(ob)) return notify_fail("你得先把他弄醒再说。\n");
        
        if (me->is_fighting() || me->is_busy())
                return notify_fail("你正忙着呢。\n");
                
        if( query("bunch/zhengzhao", ob) != 1 )
                return notify_fail("这个NPC不能用切磋武功的方式征招。\n");
                
        if( query("bunch/bunch_name", ob) == query("bunch/bunch_name", me) )
                return notify_fail("这个NPC已经是本帮兄弟，不必通过切蹉武功来征招。\n");
                
        if ((object)query_temp("invite/target", ob) != me)
                return notify_fail("你必须要先邀请(yaoqing)这个NPC。\n");
                
        if (ob->is_fighting() || ob->is_busy())
                return notify_fail("对方正忙着呢。\n");
                
        if( query("bunch/bunch_name", ob) && query("bunch/zhongcheng", ob)>query("meili", me) )
                return notify_fail("看样子对方不想和你切蹉武艺。\n");
                
        if( query("qi", ob)*100<query("max_qi", ob)*80 )
                return notify_fail("看样子对方不想和你切蹉武艺。\n");
                
        message_vision(HIY"$N道：“如此" + RANK_D->query_self(ob) +
                       "我便领教"+query("name", me)+"的高招！”\n"NOR,
                       ob, me);
                       
        if( query_temp("invite/target", ob) )
                delete_temp("invite/target", ob);
                
        me->fight_ob(ob);
        ob->fight_ob(me);
        remove_call_out("check_qi");
        call_out("check_qi", 1, me, ob);
        return 1;
}

void check_qi(object me,object ob)
{
        
        if (! objectp(me) || ! objectp(ob)) return;
        
        if( !query("bunch/bunch_name", me))return ;
        
        if (me->is_fighting(ob))
        {
                call_out("check_qi", 1, me, ob);
                return;
        }
        
        if (! environment(ob))   return;
        
        if (environment(me) != environment(ob))    return;
        
        if( query("qi", ob)>query("max_qi", ob)/2 )
        {
                message_vision("$N哈哈一笑，冲着$n道：“看来" + RANK_D->query_respect(me)
                               + "还得苦练才行啊。”\n", ob, me);                
        }
        
        else if (ob->query_last_damage_from() != me) 
        {
                message_vision("$N哼了一声道：“靠他人帮忙算什么意思？”\n",ob);
        }
        else            
        {
                message_vision("$N对$n一抱拳道：“" + RANK_D->query_respect(me)
                               + "果然厉害，" + RANK_D->query_self(ob)
                               + "佩服得紧啊。”\n", ob, me);
                ob->do_join_bunch(me);
        }
}

