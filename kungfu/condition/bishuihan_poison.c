#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "bishuihan_poison"; }

string chinese_name() { return "碧水寒毒"; }

string update_msg_others()
{
       return HIW "$N" HIW "脸色苍白，突然由白转为绿色，接着又由绿色转为紫色，全身不住的颤抖，似乎非常痛苦。\n" NOR;
}

string update_msg_self()
{
        return HIW "你只感到一股从未有过的奇寒之气从体内犹然而升，沁入全身各处大穴，看来是碧水寒毒发作了！\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        addn("neili", -1 * cnd["level"] * 10, me);
        if (random(3) == 1)me->start_busy(2 + random(3));
        else me->start_busy(1);

        return 1;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] * 600;
}

int dispel(object me, object ob, mapping cnd)
{

        if ((me->query_skill("jiuyang-shengong", 1) > 380 && 
             me->query_skill_mapped("force") == "jiuyang-shengong") ||
            (me->query_skill("yinyang-shiertian", 1) > 380 &&
             me->query_skill_mapped("force") == "yinyang-shiertian"))
        {               
                            
               addn_temp("apply/dispel-poison", 1000, me);
               set_temp("add_dispel", 1, me);               
               call_out("clear_dispel", 2, me);
        }

        return ::dispel(me, ob, cnd);


}

void clear_dispel(object me)
{
       if (query_temp("apply/dispel-poison", me) && 
           query_temp("add_dispel", me))
       {
                delete_temp("add_dispel", me);
                addn_temp("apply/dispel-poison", -1000, me);
                return;
       }
}