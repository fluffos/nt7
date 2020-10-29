// This program is a part of NITAN MudLIB
// jingsng.c 金刚拳 大金刚神通

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int d_count, count, qi, maxqi, skill;
        mapping buff, data;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「大金刚神通」只能对战斗中的对手使用。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，无法施展「大金刚神通」！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功修为不够，不能使用大金刚神通！\n");

        if ((int)me->query_skill("cuff") < 150)
                return notify_fail("你的拳法还不到家，无法使用大金刚神通！\n");

        if (me->query_skill_mapped("cuff") != "jingang-quan")
                return notify_fail("你没有激发金刚拳，无法使用大金刚神通！\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        if( BUFF_D->check_buff(me, "atkup") )
                return notify_fail("你已经在运用类似的武功了。\n");
                
        msg = HIY "$N" HIY "使出大金刚拳的绝技「大金刚神通」，臂力陡然增加！\n" NOR;

        qi=query("qi", me);
        maxqi=query("max_qi", me);
        skill = me->query_skill("jingang-quan", 1);
        count = skill*5;
        d_count = skill/10;

        if (qi > (maxqi * 0.4))
        {
                addn("neili", -150, me);
                data = ([
                        "str" : count,
                        "dex" : -d_count,
                ]);

                buff = ([
                        "caster": me,
                        "target": me,
                        "type"  : "atkup",
                        "attr"  : "bless",
                        "name"  : "金刚拳·大金刚神功",
                        "time"  : skill,
                        "buff_data": data,      
                        "buff_msg" : msg,
                        "disa_msg" : "你的大金刚神通运行完毕，将内力收回丹田。\n",
                        
                ]);
                BUFF_D->buffup(buff);
        } else
        {
                msg = HIR "$N" HIR "拼尽毕生功力使出了大金刚拳的终"
                      "极绝技, 全身骨骼一阵爆响, 欲与$n" HIR "同归于尽！\n" NOR;
                message_combatd(msg, me, target);
                addn_temp("apply/str", count*9, me);
                set_temp("jingang", 1, me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                set("neili", 0, me);
                addn("max_neili", -10, me);

                msg = HIR "$N" HIR "用尽了最后一点气力, 喷出一口鲜血, 一头栽倒在地！\n" NOR;
                message_combatd(msg, me, target);
                addn_temp("apply/str", -(count*9), me);
                delete_temp("jingang", me);
                me->unconcious();
        }
        return 1;
}

