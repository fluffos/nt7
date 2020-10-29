#include <ansi.h>
#include <combat.h>

#define XIN "「" HIR "六道轮回" NOR "」"

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);
string attack3(object me, object target, int damage);
string attack4(object me, object target, int damage);
string attack5(object me, object target, int damage);
string attack6(object me, object target, int damage);

int perform(object me, object target)
{
        mapping buff, data;
        object weapon;
        string wn, msg;
        object sroom, room;
        int ap, dp, damage, wound;
        int delta, delta2;
        int time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))   
                return notify_fail(XIN "只能在战斗中使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" XIN "。\n");

        if ((int)me->query_skill("force") < 380)
                return notify_fail("你内功修为不足，难以施展" XIN "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你内力修为不足，难以施展" XIN "。\n");

        if ((int)me->query_skill("buddhism", 1) < 240)
                return notify_fail("你禅宗心法修为不足，难以施展" XIN "。\n");

        if ((int)me->query_skill("lunhui-jian", 1) < 260)
                return notify_fail("你释迦轮回剑修为不足，难以施展" XIN "。\n");

        if (me->query_skill_mapped("sword") != "lunhui-jian")
                return notify_fail("你还没有激发释迦轮回剑，难以施展" XIN "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你内力不足，难以施展" XIN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "lhj_lun")) > 0 )
                        return notify_fail(MAG"六道轮回消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        wn = weapon->name();

        message_combatd(HIW "$N" HIW "面露拈花之意，祭起手中" + wn +
                        HIW "，霎时碧波流转，华光万丈，说不尽的祥和。"
                        "\n" NOR, me, target);

/*
        //  记录下最初的房间
        if (! objectp(sroom = environment(me)))
                return 1;

        if (base_name(sroom) == "/d/shenlong/shejingdong" ||
            base_name(sroom) == "/d/shenlong/huodong1" ||
sscanf(base_name(sroom), "/d/kaifeng/linggt/%*s") || 
            query("biwu_room", sroom) )
                return notify_fail("这个技能无法在此处施展！\n");
*/
                
        ap = attack_power(me, "sword") + me->query_skill("buddhism", 1);

        dp = defense_power(target, "parry") +
             target->query_skill("buddhism", 1);
        
        if (target->is_bad()) ap += ap / 10; 
        delta = ABILITY_D->check_ability(me, "ap_power-lhj-lun"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        damage = damage_power(me, "sword");
        damage += query("jiali", me);
                damage+= me->query_all_buff("damage");
                damage+= damage / 300 * me->query_str();
                damage*= 5;
        
        delta2 = ABILITY_D->check_ability(me, "da_power-lhj-lun"); // 门派ab
        if( delta2 ) damage += damage*delta2/100;
        
        wound = 60;

                if (me->query_skill("lunhui", 1) > 1)
                {
                        damage = damage + damage * me->query_skill("lunhui", 1) / 250;
                        wound = wound + wound * me->query_skill("lunhui", 1) / 1500;
                }

/*
        // 六道轮回之人间道
        room = find_object("/d/death/liudaolunhui/rendao");
        if (! room) room = load_object("/d/death/liudaolunhui/rendao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }
*/


        message_vision(HIY "\n$N" HIY "左手轻轻一拨，右手所持的" + wn +
                       HIY "叮呤做响，剑姿说不出的潇洒妙曼。\n" NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack1, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

/*
        // 六道轮回之畜生道
        room = find_object("/d/death/liudaolunhui/chushengdao");
        if (! room) room = load_object("/d/death/liudaolunhui/chushengdao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }
*/

        ap *= 2;

        message_vision(HIY "\n却见$N" HIY "面无表情，将手中" + wn +
                       HIY "猛的往前一递，犹如毒蛇般噬向$n" HIY "。\n"
                       NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack2, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

/*
        // 六道轮回之饿鬼道
        room = find_object("/d/death/liudaolunhui/eguidao");
        if (! room) room = load_object("/d/death/liudaolunhui/eguidao");
        
        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }
*/


        message_vision(HIY "\n$N" HIY "一声长叹，左手捏着剑诀，忽闻" +
                       wn + HIY "上血腥之气渐浓，朝$n" HIY "迎头斩落。\n"
                       NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack3, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

/*
        // 六道轮回之修罗道
        room = find_object("/d/death/liudaolunhui/xiuluodao");
        if (! room) room = load_object("/d/death/liudaolunhui/xiuluodao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }
*/


        message_vision(HIY "\n忽见$N" HIY "身形微晃，顿时幻出十数个身"
                       "影，十数柄" + wn + HIY "齐向$n" HIY "刺去。"
                       "\n" NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack4, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

/*
        // 六道轮回之地狱道
        room = find_object("/d/death/liudaolunhui/diyudao");
        if (! room) room = load_object("/d/death/liudaolunhui/diyudao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }
*/


        message_vision(HIY "\n紧接着$N" HIY + wn + HIY "一颤，有若龙吟"
                       "，剑身腾起一道滔天寒流，向四周扩散开去。\n" NOR,
                       me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack5, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

/*
        // 六道轮回之天极道
        room = find_object("/d/death/liudaolunhui/tiandao");
        if (! room) room = load_object("/d/death/liudaolunhui/tiandao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }
*/


        message_vision(HIY "\n$N" HIY "身外化身，剑外化剑，手中" + wn +
                       HIY "便似蛟龙腾空，拨云见日，天地为之失色。\n"
                       NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack6, me, target, damage :));
        } else
        {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

        me->start_busy(3 + random(3));

        addn("neili", -200-random(400), me);

        // 为什么提行？为了画面更为赏心悦目而已
        tell_object(me, "\n\n");
        tell_object(target, "\n\n");

/*
        // 转移回最初的房间
        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(sroom);
                target->move(sroom);
        }
*/

        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-lhj-lunhui"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
                
        buff =  
	([
	        "caster" : me,
	        "target" : me,
	        "type"   : "cooldown",
	        "type2"  : "lhj_lun",
	        "attr"   : "curse",
	        "name"   : "释迦轮回剑·六道轮回",
	        "time"   : time,
	        "buff_msg" : "六道轮回消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
	        "disa_msg" : "",
	        "disa_type": 0,
	]);
	BUFF_D->buffup(buff);

/*
        // 不能通过断线来保命
        if( query("qi", target)<0 )
                target->die(me);
*/
        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

                int p;                

        // 转世后如满足条件则有很大几率出现特效
                // 门派技能六到轮回可提高出特效的几率
                p = 0;
                if( query("yuanshen_level", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                damage = damage * p / 100;

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "只觉得身处幻境，心神不宁，全身"
                   "各处竟不受自己控制。\n" NOR;
                }

        msg = HIR "$n" HIR "只觉心头一阵凄苦，竟忍不住要落"
              "下泪来，喉咙一甜，呕出一口鲜血。\n" NOR;

        if( !query_temp("liudaolunhui", target) )
        {
                msg += WHT "$p忽然察觉到全身的力气竟似一丝"
                       "丝远离自己而去，无助之极。\n" NOR;

                addn_temp("apply/attack", -damage, target);
                addn_temp("apply/parry", -damage, target);
                addn_temp("apply/dodge", -damage, target);
                if( query_temp("apply/attack", target)<0 )
                        set_temp("apply/attack", 0, target);
                if( query_temp("apply/parry", target)<0 )
                        set_temp("apply/parry", 0, target);
                if( query_temp("apply/dodge", target)<0 )
                        set_temp("apply/dodge", 0, target);
                                                                        
                set_temp("liudaolunhui", 1, target);
        }

        return msg;
}

string attack2(object me, object target, int damage)
{
        object weapon;
        string wn, msg;

                int p;                

        // 转世后如满足条件则有很大几率出现特效
                // 门派技能六到轮回可提高出特效的几率
                p = 0;
                if( query("yuanshen_level", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "只觉得身处幻境，心神不宁，全身"
                   "各处竟不受自己控制。\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "忽然间$n" HIR "感到胸口处一阵火热，剑气"
              "袭体，带出一蓬血雨。\n" NOR;

        if( objectp(weapon=query_temp("weapon", target)) && (query("material", weapon) != "tian jing"
        ||      query("material", weapon) != "no name") )
        {
                wn = weapon->name();
                msg += WHT "忽听「锵锵锵」几声脆响，$n" WHT "的" + wn +
                       WHT "竟被$N" WHT "绞成了块块碎片。\n" NOR;

                set("consistence", 0, weapon);
                weapon->move(target);
        }
        return msg;
}

string attack3(object me, object target, int damage)
{
        int shd;
        string msg;

                int p;                

        // 转世后如满足条件则有很大几率出现特效
                // 门派技能六到轮回可提高出特效的几率
                p = 0;
                if( query("yuanshen_level", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "只觉得身处幻境，心神不宁，全身"
                   "各处竟不受自己控制。\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "剑锋过处，卷起漫天血浪，$n" HIR "只感头晕目"
              "眩，四肢乏力，难以再战。\n" NOR;

        if( BUFF_D->check_buff(me, "shield") ) 
        {
                BUFF_D->debuff(me, "shield", 1);

                msg += WHT "$N" WHT "气劲涌至，宛若刀割，顿时将$n"
                       WHT "的护体真气摧毁得荡然无存。\n" NOR;
        }
        return msg;
}

string attack4(object me, object target, int damage)
{
        object cloth, armor;
        string cn, an, msg;

                int p;                

        // 转世后如满足条件则有很大几率出现特效
                // 门派技能六到轮回可提高出特效的几率
                p = 0;
                if( query("yuanshen_level", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "只觉得身处幻境，心神不宁，全身"
                   "各处竟不受自己控制。\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "$n" HIR "顿时大惊失色，瞬间已被$N" HIR "连中"
              "数剑，直削得血肉模糊。\n" NOR;

        if( objectp(cloth=query_temp("armor/cloth", target)) )
        {
                cn = cloth->name();
                msg += WHT "忽听轰然声大作，$n" WHT "身着的" + cn +
                       WHT "在$N" WHT "内力激荡下，竟被震得粉碎。\n"
                       NOR;

                set("consistence", 0, cloth);
                cloth->move(target);
        } else
        if( objectp(armor=query_temp("armor/armor", target)) && (query("material", armor) != "tian jing"
        ||      query("material", armor) != "no name") )
        {
                an = armor->name();
                msg += WHT "忽听「哧啦」一声脆响，$n" WHT "身着的" +
                       an + WHT "竟被$N" WHT "震裂，化成块块碎片。\n"
                       NOR;

                set("consistence", 0, armor);
                armor->move(target);
        }
        return msg;
}

string attack5(object me, object target, int damage)
{
        string msg;

                int p;                

        // 转世后如满足条件则有很大几率出现特效
                // 门派技能六到轮回可提高出特效的几率
                p = 0;
                if( query("yuanshen_level", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "只觉得身处幻境，心神不宁，全身"
                   "各处竟不受自己控制。\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "只见$n" HIR "全身一阵抽搐，被剑锋所携的极寒气流"
              "包裹其中，刺痛难当。\n" NOR;

        if (! target->query_condition("poison"))
        {
                target->affect_by("poison",
                        ([ "level"    : damage / 3,
                           "name"     : "炼狱寒焰",
                           "id":query("id", me),
                           "duration" : damage / 50 ]));

                msg += WHT "霎时间$n" WHT "忽觉一股奇寒散入七经八脉"
                       "，仿佛连血液都停止了流动。\n" NOR;
        }
        return msg;
}

string attack6(object me, object target, int damage)
{

        string msg;

                int p;                

        // 转世后如满足条件则有很大几率出现特效
                // 门派技能六到轮回可提高出特效的几率
                p = 0;
                if( query("yuanshen_level", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "只觉得身处幻境，心神不宁，全身"
                   "各处竟不受自己控制。\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "$N" HIR "剑势迅猛之极，令$n" HIR "毫无招架余地，"
              "竟镇怯当场，素手待毙。\n" NOR;

        if( !query_temp("no_exert", target) )
        {
                set_temp("no_exert", 1, target);

                msg += WHT "$n" WHT "只感到全身真气涣散，丹元瓦解，似"
                       "乎所有的武功竟都消逝殆尽。\n" NOR;
        }
        return msg;
}
