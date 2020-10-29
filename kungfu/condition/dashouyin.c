// dashouyin.c

#include <ansi.h>
#include <condition.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int damage, p;
        string msg;
        
        if (me->is_ghost()) return 1;
        damage = me->query_condition("dashouyin") +2;
        damage *= me->query_con();
        
        tell_object(me,"突然你感觉胸口疼痛异常，刚才被大手印拍中的肋骨处好象要裂开了似的，鲜血也从口中喷了出来！\n");
        tell_room(environment(me),HIR + me->name()+"突然一言不发，双手捂胸，蹬蹬磴倒退了数步，接着哇得一声吐出口鲜血来！\n" NOR,({ me }));
        me->receive_damage("qi", damage);
        me->receive_wound("qi", damage/2);
        p=query("qi", me)*100/query("max_qi", me);
        msg = "( $N"+eff_status_msg(p)+" )\n";
        if( living(me) && !query_temp("noliving", me))message_vision(msg,me);
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)
        {
                set_temp("die_reason", "大手印劲力发作死亡", me);
                return 0;
        }
        me->apply_condition("dashouyin", duration - 1);
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "hurt";
}