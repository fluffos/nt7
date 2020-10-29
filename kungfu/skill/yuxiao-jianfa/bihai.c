#include <ansi.h>
#include <combat.h>

string name() { return HIW "碧海潮生按玉箫" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;
        object ob;
        int delta;
        int fmsk = me->query_skill("qimen-xuanshu", 1);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(ob=query_temp("handing", me)) || !ob->valid_as_xiao() )
        {
                if( !objectp(ob=query_temp("weapon", me) )
                   /*|| ! ob->valid_as_xiao()*/)
                {
                        // 手里的兵器也不能作为萧使用
                        return notify_fail("你手里没有拿萧，难以施展" + name() + "。\n");
                }
        }

        skill = me->query_skill("yuxiao-jianfa", 1);

        if (skill < 180)
                return notify_fail("你玉箫剑法等级不够, 难以施展" + name() + "。\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 180)
                return notify_fail("你碧波神功修为不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("bihai-chaosheng", 1) < 180)
                return notify_fail("你的碧海潮生曲太低，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("你没有激发玉箫剑法，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的内力不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "sword") +
             me->query_skill("bihai-chaosheng", 1);
        dp = defense_power(target, "force") +
             target->query_skill("bihai-chaosheng", 1);
        
        delta = ABILITY_D->check_ability(me, "ap_power-yxjf-bihai"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        damage = 0;

        msg = HIW "\n只见$N" HIW "手按玉箫，脚踏八卦四方之位，奏出"
              "一曲「碧海潮生按玉箫」。便听得那箫声如鸣琴击玉，轻轻"
              "发了几声，接着悠悠扬扬，飘下清亮柔和的洞箫声来。\n" NOR;

        if (ap + random(ap) + fmsk> dp)
        {
                msg += HIR "$n" HIR "只感心头一震，脸上情不自禁的露"
                       "出了一丝微笑。\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "暗暗凝神守一，对这箫声自是应付"
                       "裕如。\n" NOR;

        msg += HIW "\n突然又听那洞箫声情致飘忽，缠绵宛转，便似一个女"
               "子一会儿叹息，一会儿又似呻吟，一会儿却又软语温存或柔"
               "声叫唤。\n" NOR;

        if (ap + random(ap) + fmsk> dp)
        {
                msg += HIR "$n" HIR "只感全身热血沸腾，就只想手舞足"
                       "蹈的乱动一番。\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "暗暗凝神守一，对这箫声自是应付"
                       "裕如。\n" NOR;

        msg += HIW "\n那箫声清亮宛如大海浩淼，万里无波，远处潮水缓缓"
               "推近，渐近渐快，其后洪涛汹涌，白浪连山，而潮水中鱼跃"
               "鲸浮，海面风啸鸥飞，水妖海怪群魔弄潮，极尽变幻之能事"
               "。\n" NOR;

        if (ap + random(ap) + fmsk> dp)
        {
                msg += HIR "霎时间$n" HIR "只感心头滚热，喉干舌燥，"
                       "说不出的难受。\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "暗暗凝神守一，对这箫声自是应付"
                       "裕如。\n" NOR;

        msg += HIW "\n时至最后，却听那箫声愈来愈细，几乎难以听闻，便"
               "尤如大海潮退后水平如镜一般，但海底却又是暗流湍急，汹"
               "涌澎湃。\n" NOR;

        if (ap + random(ap) + fmsk> dp)
        {
                msg += HIR "此时$n" HIR "已身陷绝境，全身气血逆流，"
                       "再也无法脱身。\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "暗暗凝神守一，对这箫声自是应付"
                       "裕如。\n" NOR;
        
        delta = ABILITY_D->check_ability(me, "da_power-yxjf-bihai"); // 门派ab
        if( delta ) damage += damage*delta/100;
        
        target->receive_damage("jing", damage * 2 / 3, me);
        target->receive_wound("jing", damage / 2, me);

        me->start_busy(2 + random(2));
        addn("neili", -200, me);

        message_combatd(sort_msg(msg), me, target);
        return 1;
}
