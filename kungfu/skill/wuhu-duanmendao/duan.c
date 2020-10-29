
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int i, skill;
        int time;
        mapping buff;
 
        if (! me->is_fighting())
                return notify_fail("五虎断门刀「断」字决只能在战斗中使用。\n");
                
        if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");
                
        if( query("neili", me)<200 )
                return notify_fail("你的真气不够！\n");
                
        if ((int)me->query_skill("blade") < 60 ||
            me->query_skill_mapped("blade") != "wuhu-duanmendao")
                return notify_fail("你的「五虎断门刀」还不到家，无法使用「断」字决！\n");
                
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "whdmd_duan")) > 0 ) 
                        return notify_fail(MAG"五虎断门刀「断」字决消耗心神太甚，还需等待"+time+"秒。\n"NOR); 
        }
        msg = HIY "$N猛然伏地，使出「五虎断门刀」断字决，顿时五道白光直向前滚去！\n" NOR;
        message_combatd(msg, me);
        me->clean_up_enemy();
        ob = me->select_opponent();
        addn("neili", -150, me);

        skill = me->query_skill("wuhu-duanmendao", 1)/2;
        addn("apply/attack", skill, me);
        
        for(i = 0; i < 5; i++)
        if( me->is_fighting(ob) && ob->is_fighting(me) && query("eff_qi", ob)>0 )
        {
              set_temp("action_msg", "紧接着", me);
              if( !query("equipped", weapon))break;
              
              COMBAT_D->do_attack(me, ob,weapon, TYPE_LINK);
        } else break;
        addn("apply/attack", -skill, me);

        buff = 
        ([ 
                "caster" : me,
                "target" : me, 
                "type"   : "cooldown", 
                "type2"  : "whdmd_duan", 
                "attr"   : "curse",
                "name"   : "五虎断门刀·断字诀", 
                "time"   : 1,
                "buff_msg" : "五虎断门刀「断」字决消耗心神太甚，还需等待2秒方可再次施展。\n", 
        ]); 
        BUFF_D->buffup(buff);

        return 1;
}
