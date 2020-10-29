// warn_poison 朱砂掌毒

#include <ansi.h>;
#include <condition.h>;
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if (me->is_ghost()) return 1;
        if( !living(me) || query_temp("noliving", me) )
        {
                message("vision", me->name()+"喘着粗气，面色赤红。\n", environment(me), me);
        }
        else
        {
                tell_object(me, RED"你只觉浑身燥热难耐，似乎被放在火炉中一样，极为难受！\n" NOR );
                message("vision", RED+me->name()+"突然面色一红，浑身一抖，自头部到手臂隐约可见斑斑红点，极为恐怖。\n"NOR, environment(me), me);
        }
        me->receive_damage("qi", 2500);
        me->receive_wound("jing", 2000);
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)
        {
                set_temp("die_reason", "朱砂掌毒发作死亡");
                return 0;
        }
        me->apply_condition("warm_poison", duration - 1);
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}