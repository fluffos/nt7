// hun.c 无名

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str,mapforce;
        object weapon,weapon2;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("nine-finger", 1);

        if (! me->is_fighting(target))
                return notify_fail("无名只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("finger") != "nine-finger") 
                return notify_fail("你没有用九字真言手印，无法使用「无名」绝招！\n");

        if (me->query_skill_prepared("finger") != "nine-finger")
                return notify_fail("你没有准备使用九字真言手印，无法施展「无名」绝招。\n");

        if (skill < 100)
                return notify_fail("你的九字真言手印等级不够，练好了再来！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用指法绝招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("finger") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        weapon2=query_temp("weapon", target);
        
        if (me->query_skill_mapped("force"))
                mapforce = to_chinese(me->query_skill_mapped("force"));
        else
                mapforce = "内力";
                
        msg = MAG "\n$N" NOR MAG "口中默诵九字真言，双手摊开，九式手印不住变幻。\n" +
               "一时之间，漫天手印混杂着强烈的" HIW + mapforce + NOR + 
               MAG "，无坚不摧地杀向$n" NOR MAG "！\n" NOR;
                
        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = "\n忽闻一声大喝" HIW " 临 兵 斗 者 皆 阵 列 在 前 !\n" NOR +  
              "只见$N身形凌空而起，双手合什，宝瓶气从四面八方涌来，充塞天地，即使协生双翼，还是避无可避！ \n" + 
              "正是" HIW "九字真言手印" NOR "终极式： " HIY "九印合一" NOR "！\n" NOR; 

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                if (weapon2)
                        msg += MAG "$n" NOR MAG "见$N" MAG "来势凶猛，不敢正面抵挡，手中" + weapon2->name() + 
                               NOR MAG "满天幻影，防得水泄不通\n" + 
                               "$N" NOR MAG "竟是置若罔闻，" HIW "螺旋劲气" NOR MAG "仍旧绵绵不绝，$n" NOR MAG "无可奈何之下，被击个正着！\n" NOR; 
                else
                        msg += MAG "$n" NOR MAG "见$N" MAG "来势凶猛，不敢正面抵挡，侧身进步双掌奋力侧击$N\n" + 
                               NOR MAG "$N" NOR MAG "竟是置若罔闻，" HIW "螺旋劲气" NOR MAG "仍旧绵绵不绝，$n" + 
                               NOR MAG "无可奈何之下，被击个正着！\n" NOR;
               
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                if (weapon)
                        msg += MAG "$n" NOR MAG "见$N" NOR MAG "来势凶猛，不敢正面抵挡，手中" + weapon2->name() +
                               NOR MAG "满天幻影，防得水泄不通\n" +
                               "$N" NOR MAG "被缓得一缓，" HIW "螺旋劲气" NOR MAG"已然落空！\n" NOR;

                else
                        msg += MAG "$n" NOR MAG "见$N" NOR MAG "来势凶猛，不敢正面抵挡，侧身进步双掌奋力侧击$N\n" + 
                               NOR MAG "$N" NOR MAG "被缓得一缓，" HIW "螺旋劲气" NOR MAG "已然落空，但$n" NOR MAG "也被$N" NOR MAG "震得气血翻涌！\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}
