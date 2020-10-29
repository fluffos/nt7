#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "天脉神剑"; }
string *sname = ({"少冲剑","少泽剑","中冲剑","关冲剑","商阳剑","少商剑",});
string *color = ({HIR,HIG,HIY,HIB,HIM,HIC,});
string *xue_name = ({
"劳宫穴", "膻中穴", "曲池穴", "关元穴", "曲骨穴", "中极穴", "承浆穴", "天突穴", "百会穴",
"幽门穴", "章门穴", "大横穴", "紫宫穴", "冷渊穴", "天井穴", "极泉穴", "清灵穴", "至阳穴", });

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill, fmsk, kurong, ngxy, jingluo;
        int n;
        int time;
        int delta;
        mapping buff;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你还没有悟道，不能施展天脉神剑。\n");

/*
        if( query("family/family_name", me) != "段氏皇族"
         && member_array("段氏皇族", query("reborn/fams", me)) == -1 )
                return notify_fail("你所使用的外功中没有这种功能。\n");
*/

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( me->is_busy() )
                return notify_fail("你正忙着呢。\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你没有准备使用六脉神剑，无法施展" + name() + "。\n");

        skill = me->query_skill("six-finger", 1);
        fmsk = me->query_skill("qimai-liuzhuan", 1);
        kurong = me->query_skill("kurong-changong", 1);
        ngxy = me->query_skill("force-cognize", 1);
        jingluo = me->query_skill("jingluo-xue", 1);
        if (skill < 800)
                return notify_fail("你的六脉神剑修为有限，无法使用" + name() + "！\n");

        if (me->query_skill("force", 1) < 1000)
                return notify_fail("你的内功火候不够，难以施展" + name() + "！\n");

        if( query("max_neili", me)<120000 )
                return notify_fail("你的内力修为不够,无法施展" + name() + "！\n");

        if( query("neili", me)<100000 )
                return notify_fail("你的真气不够，现在无法施展" + name() + "！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必须是空手才能施展" + name() + "！\n");

        if( userp(me) )
        {
                if( (time = BUFF_D->get_buff_overtime(me, "lmsj_tian")) > 0 )
                        return notify_fail(MAG"天脉神剑消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC"               --------天--------\n";
        msg+= HIG"                 ------脉------\n";
        msg+= HIY"                   ----神----\n";
        msg+= HIR"                     --剑--\n\n";
        message_combatd(msg, me, target);
        msg = HIC "$N" HIC "一声清啸，右手五指纷弹，顿觉六脉剑谱已涌上心头，此起"
              "彼伏、连绵不绝。\n霎时剑气如奔，连绵无尽的万道剑气豁然贯向$n" HIM
              "！\n" NOR;
        msg+=color[random(sizeof(color))]+ "┏------------┓\n";
        msg+= "┃   "+sname[random(sizeof(sname))]+"   ┃\n";
        msg+= "┗------------┛\n";
        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");

        // 提高20%
        ap = ap + ap / 5 + me->query_skill("martial-cognize", 1) + me->query_skill("jingluo-xue", 1);
        ap *= 2;
       //▁▂▃▄▅▆▇█▇█
        delta = ABILITY_D->check_ability(me, "ap_power-lmsj-tian"); // 门派ab
        if( delta ) ap += ap*delta/100;

        damage = damage_power(me, "finger") + me->query_skill("martial-cognize", 1) + me->query_skill("jingluo-xue", 1);
        damage+= query("jiali", me);
        damage+= me->query_all_buff("unarmed_damage");
        damage+= damage / 300 * me->query_str();
        damage*= 2;
        delta = ABILITY_D->check_ability(me, "da_power-lmsj-tian"); // 门派ab
        if( delta ) damage += damage*delta/100;
        if( (n = fmsk / 100) >= 1 )
        damage += damage*n*15/100;

        // 有20%几率施展无BUSY
        if (random(5) != 1) me->start_busy(2 + random(3));

        if ((int)target->query_skill("martial-cognize", 1) >= 2000 && target->query_skill("jingluo-xue", 1) >= 200
            && target->query_skill("dodge", 1) >= me->query_skill("six-finger", 1)
            && random (30) == 1 )
        {
                addn("neili", -2000, me);
                msg += HIY "但见$n" HIY "会心一笑，轻拂衣袖，轻易的躲过这一招！\n"NOR;
        } else
        if (ap + random(ap) > dp)
        {
                if( (n = fmsk / 100) >= 1 )
                msg += HIM"$N"HIM"运用气脉流转的辅助，使得天脉神剑伤害更强。\n"NOR;
                addn("neili", -query("max_neili", me)/40, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + random(200),
                                           RED "只听$n" RED "一声惨叫，万道剑气已"
                                           "透体而过，伤口处鲜血顿时狂涌，痛苦难当！\n" NOR);
                if(me->query_skill("sun-finger",1) >= skill /4*3 && random(fmsk) > 200 && random(jingluo)>200
                && random(me->query_skill("finger")) > target->query_skill("dodge") / 3)
                {
                    msg+=  HIB "$N" HIB "凝聚一阳指诀功力，陡然点出一指，变化多端，巧逼$n"HIB"诸处大穴。\n" NOR;
                    msg+=  "$n"HIB"一不留神，"+NOR+HBMAG+HIW+xue_name[random(sizeof(xue_name))]+NOR+HIB"被$N点中，登时手忙脚乱！\n"NOR;
                    if( !target->is_busy() ) target->start_busy(8);
                }

        } else
        {
                addn("neili", -400, me);
                msg += CYN "$n" CYN "见$N" CYN "来势汹涌，不敢轻易"
                       "招架，急忙提气跃开。\n" NOR;
        }

        if(skill > 5000 && random(kurong) > 2500)
        {
            msg += HIG "\n$N" HIG "一声清啸，左手五指纷弹，顿觉六脉剑谱已涌上心头，此起"
                  "彼伏、连绵不绝。\n霎时剑气如奔，连绵无尽的万道剑气豁然贯向$n" HIG
                  "！\n" NOR;
            msg+=color[random(sizeof(color))]+ "┏------------┓\n";
            msg+= "┃   "+sname[random(sizeof(sname))]+"   ┃\n";
            msg+= "┗------------┛\n";

            // 第二招
            if ((int)target->query_skill("martial-cognize", 1) >= 2000
                && target->query_skill("dodge", 1) >= me->query_skill("six-finger", 1)
                && random (30) == 1 )
            {
                    addn("neili", -600, me);
                    msg += HIY "但见$n" HIY "会心一笑，轻拂衣袖，轻易的躲过这一招！\n"NOR;
            } else
            if (ap + random(ap) > dp)
            {
                    if( (n = fmsk / 100) >= 1 )
                    msg += HIM"$N"HIM"运用气脉流转的辅助，使得天脉神剑伤害更强。\n"NOR;
                    addn("neili", -query("max_neili", me)/40, me);
                    msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + random(200),
                                               RED "只听$n" RED "一声惨叫，万道剑气已"
                                               "透体而过，伤口处鲜血顿时狂涌，痛苦难当！\n" NOR);
                if(me->query_skill("sun-finger",1) >= skill /4*3 && random(fmsk) > 200 && random(jingluo)>200
                && random(me->query_skill("finger")) > target->query_skill("parry") / 3)
                {
                    msg+=  HIB "$N" HIB "凝聚一阳指诀功力，陡然点出一指，变化多端，巧逼$n"HIB"诸处大穴。\n" NOR;
                    msg+=  "$n"HIB"一不留神，"+NOR+HBMAG+HIW+xue_name[random(sizeof(xue_name))]+NOR+HIB"被$N点中，登时身子软了下去！\n"NOR;
                    target->set_weak(5);
                }
            } else
            {
                    addn("neili", -400, me);
                    if (random(5) != 1)me->start_busy(5);
                    msg += CYN "$n" CYN "见$N" CYN "来势汹涌，不敢轻易"
                           "招架，急忙提气跃开。\n" NOR;
            }
        }
        if(skill > 10000 && random(kurong) > 5000)
        {
            msg += HIY "\n$N" HIY "一声清啸，左手五指纷弹，顿觉六脉剑谱已涌上心头，此起"
                  "彼伏、连绵不绝。\n霎时剑气如奔，连绵无尽的万道剑气豁然贯向$n" HIG
                  "！\n" NOR;
            msg+=color[random(sizeof(color))]+ "┏------------┓\n";
            msg+= "┃   "+sname[random(sizeof(sname))]+"   ┃\n";
            msg+= "┗------------┛\n";

            // 第三招
            if ((int)target->query_skill("martial-cognize", 1) >= 2000
                && target->query_skill("dodge", 1) >= me->query_skill("six-finger", 1)
                && random (30) == 1 )
            {
                    addn("neili", -600, me);
                    msg += HIY "但见$n" HIY "会心一笑，轻拂衣袖，轻易的躲过这一招！\n"NOR;
            } else
            if (ap + random(ap) > dp)
            {
                    if( (n = fmsk / 100) >= 1 )
                    msg += HIM"$N"HIM"运用气脉流转的辅助，使得天脉神剑伤害更强。\n"NOR;
                    addn("neili", -query("max_neili", me)/40, me);
                    msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + random(200),
                                               RED "只听$n" RED "一声惨叫，万道剑气已"
                                               "透体而过，伤口处鲜血顿时狂涌，痛苦难当！\n" NOR);
                if(me->query_skill("sun-finger",1) >= skill /4*3
                && random(fmsk) > 200
                && random(jingluo)>200
                && random(me->query_skill("finger")) > target->query_skill("force") / 2)
                {
                    msg+=  HIB "$N" HIB "凝聚一阳指诀功力，陡然点出一指，变化多端，巧逼$n"HIB"诸处大穴。\n" NOR;
                    msg+=  "$n"HIB"一不留神，"+NOR+HBMAG+HIW+xue_name[random(sizeof(xue_name))]+NOR+HIB"被$N点中，真气源源而泄！\n"NOR;
                    set("neili",0,target);
                }
            } else
            {
                    addn("neili", -400, me);
                    if (random(5) != 1)me->start_busy(5);
                    msg += CYN "$n" CYN "见$N" CYN "来势汹涌，不敢轻易"
                           "招架，急忙提气跃开。\n" NOR;
            }
        }


        if( query("neili", me)< 0) set("neili",0,me);
        message_combatd(msg, me, target);

        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-lmsj-tian"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
        if( wiz_level(me) > 2) time = 2;
        buff =
        ([
                "caster" : me,

                "target" : me,
                "type"   : "cooldown",
                "type2"  : "lmsj_tian",
                "attr"   : "curse",
                "name"   : "六脉神剑·天脉神剑",
                "time"   : time,
                "buff_msg" : "天脉神剑消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);

        return 1;
}
