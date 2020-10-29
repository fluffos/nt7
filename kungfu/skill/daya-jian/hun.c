// hun.c 大雅若俗

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str,force;
        object weapon,weapon2;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("daya-jian", 1);

        if (! me->is_fighting(target))
                return notify_fail("大雅若俗只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("sword") != "daya-jian") 
                return notify_fail("你没有用大雅剑法，无法使用大雅若俗绝招！\n");

        if (skill < 100)
                return notify_fail("你的大雅剑法等级不够，练好了再来！\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("sword") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIC "\n$N" HIC "先行存念，内劲真气勃发，" NOR CYN "大雅古剑法" HIC "顿时挥洒得淋漓尽致！\n" +
              weapon->name() + HIC "如同活了一样，幻化出满天剑影，向$n" HIC "扑面罩来！\n\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        force = me->query_skill_mapped("force");
        if (!stringp(force)) force = "force";
        
        msg = HIM "\n$N" HIM "一阵狂攻之后，忽然招式一缓，身形急退，须臾已在丈许之外。\n"
              "$n" HIM "见$N" HIM "力有不继，正要抢上反击，$N" HIM "突然仗剑而立，双目凝视$n" HIM "。\n"
              "$n" HIM "被这犀利的目光吓得一哆嗦，不解$N" HIM "是何意，心头一阵迷惘。\n"
              "忽闻$N" HIM "大喝一声:\n"
              HIW "风萧萧兮易水寒，壮士一去兮不复还!\n"
              HIM "歌声中混杂着强劲的" HIR + to_chinese(force)+ HIM"，$n" HIM "不由心神大乱。\n"
              "此时，只见$N" HIM "人剑合一，如流星、似闪电，刺向$n" HIM "，正是" NOR CYN "大雅古剑法" HIM "的" HIW "『不归式』" HIM"！！\n\n" NOR;

        weapon2=query_temp("weapon", target);
        
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                if (weapon2)
                        msg += HIM "$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，手中" + weapon2->name() + HIM "一颤侧击" + weapon->name() + HIM "的剑脊\n"
                               "$N" HIM "竟是置若罔闻，" HIW "『不归式』" HIM "仍旧一往直前，$n" HIM "手中" + weapon2->name() + HIM "为$N内力侵灌而入，浑身振颤！\n" NOR;
                else
                        msg += HIM "$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，侧身进步双掌奋力侧击$N" HIM "\n"
                               "$N" HIM "竟是置若罔闻，" HIW "『不归式』" HIM "仍旧一往直前，$n" HIM "无可奈何，被击个正着！\n" NOR;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                if (weapon2)
                        msg += HIM "$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，手中" + weapon2->name() + HIM "一颤侧击" + weapon->name() + HIM "的剑脊\n"
                               "$N" HIM "被缓得一缓，" HIW "『不归式』" HIM "已然落空！\n" NOR;
                else
                        msg += HIM "$n" HIM "见$N" HIM "来势凶猛，不敢正面抵挡，侧身进步双掌奋力侧击$N" HIM "\n"
                               "$N" HIM "被缓得一缓，" HIW "『不归式』" HIM "已然落空，但$n" HIM "也被$N" HIM "震得气血翻涌！\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        addn("neili", -damage/3, me);
        return 1;
}

