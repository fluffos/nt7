// This program is a part of NITAN MudLIB
// youming.c  幽冥鬼影

#include <ansi.h>

inherit F_SSERVER;

string name() { return "幽冥鬼影"; }

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「幽冥鬼影」只能在战斗中使用。\n");

        if ((int)me->query_skill("youming-guizhao", 1) < 120 )
                return notify_fail("你的幽冥鬼爪等级不够，不能呼唤鬼影！\n");

        if ((int)me->query_skill("claw", 1) < 120 )
                return notify_fail("你的基本爪法极不够娴熟，不能呼唤鬼影！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手使用「幽冥鬼影」！\n");

        /*
        if ((int)me->query_skill("xiaowuxiang", 1)<100
                && (int)me->query_skill("bahuang-gong", 1)<100
                && (int)me->query_skill("beiming-shengong", 1)<100)
                return notify_fail("你的逍遥派内功火候不够。\n");

        if (me->query_skill_mapped("force") != "xiaowuxiang"
                && me->query_skill_mapped("force") != "bahuang-gong"
                && me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你没有运用逍遥派内功！\n");
        */

        if (me->query_skill_prepared("claw") != "youming-guizhao"
                || me->query_skill_mapped("claw") != "youming-guizhao"
                || me->query_skill_mapped("parry") != "youming-guizhao")
                return notify_fail("你现在无法呼唤出鬼影进行攻击！\n");

        if( query("neili", me)<800 )
                return notify_fail("你现在真气太弱，不能呼唤鬼影！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你现在内力太弱，不能呼唤鬼影！\n");

        if( BUFF_D->check_buff(me, "ymgz_youming") )
                return notify_fail("你已经呼唤出了幽冥鬼影！\n");

        skill = me->query_skill("claw");

        msg = HIR "突然$N咬破舌尖，高声叫唤天地鬼神，如同疯子一般！跟着地面变得有如水动，只见\n"
                        "一条"HIB"鬼影"HIR"从地底冒出，飞于半空，身行飘渺不定，时而象一火球，时而象一黑影！\n\n" NOR;

        addn("neili", -skill, me);
        
        data = ([
                "defense": skill/2,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "ymgg_youming",
                "attr"  : "bless",
                "name"  : "幽冥鬼爪·幽冥鬼影",
                "time"  : skill/5,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : HIR"地面的波动渐渐减弱，那条"HIB"鬼影"HIR"于半空徘徊了一阵，就消失在地底了！\n"NOR,
                        
        ]);
        BUFF_D->buffup(buff);
        
        call_out("checking", 1, me, target);

        return 1;
}
void checking(object me, object target)
{
        int skill;
        skill = me->query_skill("claw");

        if( !living(me) || me->is_ghost() )
        {
                message_combatd(HIR"那条"HIB"鬼影"HIR"于半空徘徊了一阵，就消失在地底了！\n"NOR, me);
                BUFF_D->debuff(me, "ymgg_youming", 1);
                return ;
        }
        if( !me->is_fighting() )
        {
                message_combatd(HIR"那条"HIB"鬼影"HIR"于半空徘徊了一阵，就消失在地底了！\n"NOR, me);
                BUFF_D->debuff(me, "ymgg_youming", 1);
                return ;
        }
        if( me->query_skill_mapped("force") != "bahuang-gong"
           || me->query_skill_mapped("claw") != "youming-guizhao"
           || me->query_skill_prepared("claw") != "youming-guizhao" )
        {
                tell_object(me,"\n$N骤然变换招数，不能再继续用幽冥鬼影牵制对手的攻击！\n");
                BUFF_D->debuff(me, "ymgg_youming", 1);
                return ;
        }
        else
                call_out("checking", 1, me, target);
        return;
}