// yingxiong.c

#include <ansi.h>
inherit F_SSERVER;

string name() { return "盖世英雄"; }

int perform(object me, object target)
{
        mapping buff, data;
        int level;
        string msg;
        int ap, dp;

        if( !objectp(target) ) { target = offensive_target(me);}

        if( !target || !target->is_character() || target == me ||
            !me->is_fighting(target) ||
            !living(target) || query_temp("no_living", target) )
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query("gender", me) != "男性" && !wizardp(me) )
                return notify_fail("象你这副娘娘腔，也许练“绝世风姿”恐怕更合适点吧。\n");

        if( (int)me->query_skill("yingxiong-sanzhao", 1) < 150 )
                return notify_fail("你的英雄三招不够娴熟，不会使用"+name()+"。\n");

        if( (int)me->query_skill("force", 1) < 160 )
                return notify_fail("你的基本内功不够娴熟，不会使用"+name()+"。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的内力不足，恐怕没法逞英雄了。\n");

        if( BUFF_D->check_buff(me, "yxsz_yingxiong") )
                return notify_fail("你已经在大摆英雄的谱了，还不够啊？\n");

        level = me->query_skill("yingxiong-sanzhao", 1);
        addn("neili", -200, me);
        me->start_busy(1);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if( ap / 2 + random(ap) > dp )
        {
                msg = HIY"$N"HIY"越斗越是凶猛，激斗中仰天大吼一声：“盖世英雄！！”，一股豪气自$N心中升起，顿时更是凶悍起来。\n" NOR;
                data = ([
                        "attack": level/2,
                        "unarmed_damage": level*2,
                ]);
                buff = ([
                        "caster": me,
                        "target": me,
                        "type"  : "yxsz_yingxiong",
                        "attr"  : "bless",
                        "name"  : "英雄三招·盖世英雄",
                        "time"  : level/10,
                        "buff_data": data,      
                        "buff_msg" : msg,
                        "disa_msg" : HIY"$N突然感到心底一阵失落：“历代英雄，都归孤冢。”一念及此，顿时意兴萧然。\n" NOR,
                        "disa_type": 1,
                        
                ]);
                BUFF_D->buffup(buff);
                if( !target->is_busy() )
                        target->start_busy(random(3)+1);
        }
        else
        {
                message_combatd(HIG"激斗中的$N冲着$n大喊：“盖世。。。”，语意未了，就被$n迫得手忙脚乱。\n" NOR, me, target);
        }
        return 1;
}
