#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "yaowang_poison"; }

string chinese_name() { return HIW "药王谷独门毒药" NOR; }

string update_msg_others()
{
       return HIW "$N脸色发紫，全身不住的颤抖，牙关格格作响。\n" NOR;
}

string update_msg_self()
{
        return HIW "你的药王谷独门之毒发作了！\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 3;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"]/ 2;
}

int dispel(object me, object ob, mapping cnd)
{

        if (me == ob)
        {
                if ((me->query_skill("shennong-xinjing", 1) > 180 && 
                        me->query_skill_mapped("force") == "shennong-xinjing") ||
                        (me->query_skill("yaogu-xinfa", 1) > 250 &&
                        me->query_skill_mapped("force") == "yaogu-xinfa")||
                        (me->query_skill("yaowang-shenxin", 1) > 180 &&
                        me->query_skill_mapped("poison") == "yaowang-shenxin"))
                {                                           
                        return ::dispel(me, ob, cnd);
                }
                                        
                tell_object(me, "你试图运功化解药王谷之毒，突然一感到"
                                "阵撕心裂肺的疼痛，几乎晕厥。\n");
                return -1;
        }
        else
        {
                if ((me->query_skill("shennong-xinjing", 1) > 180 && 
                        me->query_skill_mapped("force") == "shennong-xinjing") ||
                        (me->query_skill("yaogu-xinfa", 1) > 250 &&
                        me->query_skill_mapped("force") == "yaogu-xinfa")||
                        (me->query_skill("yaowang-shenxin", 1) > 180 &&
                        me->query_skill_mapped("poison") == "yaowang-shenxin"))
                {                                           
               addn_temp("apply/dispel-poison", -50, me);
               set_temp("add_dispel", 1, me);
               call_out("clear_dispel", 2, me);
                return ::dispel(me, ob, cnd);
                }


        tell_object(me, "你将真气输入" + ob->name() + "体中，却觉得"
                        "真气运转异常怪异，难以理解，\n突然见" + ob->name() +
                        "汗如雨下，连忙住手。\n");
        tell_object(ob, "你觉得" + me->name() + "将内力缓缓输入你的"
                        "经脉，忽然一阵撕心裂肺的剧痛，\n犹胜药王谷独门之"
                        "毒发作的时候，令你几乎晕厥。\n");
        return -1;
        }
        
}

void clear_dispel(object me)
{
       if( query_temp("apply/dispel-poison", me) && 
           query_temp("add_dispel", me) )
       {
                delete_temp("add_dispel", me);
                addn_temp("apply/dispel-poison", 50, me);
                return;
       }
               
}