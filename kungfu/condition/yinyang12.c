// freezing.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "yinyang12"; }

string chinese_name() { return "乱气之阴阳"; }

string update_msg_others()
{
        return HIW "$N" HIW "脸上呈现出痛苦的表情，四肢变得僵硬，全身瘫软了下来。\n" NOR;
}

string update_msg_self()
{
        return HIW "你只觉全身酸软无比，竟使不出丝毫气力。\n" NOR;
}

string die_msg_others()
{
        return HIW "$N" HIW "倒在地上，抽搐了一阵，再也没有半点生气了。\n" NOR;
}

string die_reason()
{
        return "乱气之阴阳发作，力乏而尽";
}


int dispel(object me, object ob, mapping cnd)
{
        if ((me->query_skill("jiuyang-shengong", 1) > 180 && 
             me->query_skill_mapped("force") == "jiuyang-shengong") ||
             (me->query_skill("jiuyin-shengong", 1) > 180 &&
              me->query_skill_mapped("force") == "jiuyin-shengong") || 
             (me->query_skill("yinyang-shiertian", 1) > 180 &&
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
       if( query_temp("apply/dispel-poison", me) && 
           query_temp("add_dispel", me) )
       {
                delete_temp("add_dispel", me);
                addn_temp("apply/dispel-poison", -1000, me);
                return;
       }
               
}