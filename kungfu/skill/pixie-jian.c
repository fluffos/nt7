// Written by Lonely@nitan.org
// pixie-jian

#include <ansi.h>
//inherit FORCE;
inherit SKILL;

int valid_force(string force)
{
        return force == "riyue-xinfa" || force == "riyue-guanghua" || force == "kuihua-xinfa";
}

string *dodge_msg = ({
        "突然之间，白影急幌，$n向后滑出丈余，立时又回到了原地，躲过了$N这一招。\n",
        "$n手臂回转，在$N手肘下一推，顺势闪到一旁。\n",
        "$n右手伸出，在$N手腕上迅速无比的一按，顺势跳到一旁。\n",
        "$n身形飘忽，有如鬼魅，转了几转，移步到$N的身后，躲过了$N这一招。\n",
        "$N只觉眼前一花，似乎见到$n身形一幌，但随即又见$n回到原地，却似从未离开。\n",
        "$N眼睛一花，$n已没了踪影。突然$n从身后拍了一下$N的头，轻轻跃开。\n",
        "$n嫣然一笑，诡异之极，$N竟不知如何是好，停住了攻击。\n",
});

string *finger_name = ({ "左手中指", "左手无名指", "左手食指",
                         "右手中指", "右手无名指", "右手食指", });

mapping *weapon_action = ({
([      "action":"突然之间，白影急幌，$N向后滑出丈余，立时又回到了原地",
        "force" : 160,
        "attack": 40,
        "parry" : 30,
        "dodge" : 120,
        "damage": 150,
        "lvl" : 0,
        "skill_name" : "白影急幌",
        "damage_type":  "刺伤"
]),
([      "action":"$N右手伸出，在$n手腕上迅速无比的一按，$n险些击中自己小腹",
        "force" : 180,
        "attack": 50,
        "parry" : 30,
        "dodge" : 135,
        "damage": 160,
        "lvl" : 20,
        "skill_name" : "自己小腹",
        "damage_type":  "刺伤"
]),
([      "action":"蓦地里$N猱身而上，蹿到$n的身后，又跃回原地",
        "force" : 225,
        "attack": 60,
        "parry" : 35,
        "dodge" : 155,
        "damage": 170,
        "lvl" : 40,
        "skill_name" : "猱身而上",
        "damage_type":  "刺伤"
]),
([      "action":"$N突然间招法一变，$w忽伸忽缩，招式诡奇绝伦。$n惊骇之中方寸大乱",
        "force" : 230,
        "attack": 70,
        "parry" : 40,
        "dodge" : 160,
        "damage": 180,
        "lvl" : 60,
        "skill_name" : "招法一变",
        "damage_type":  "刺伤"
]),
([      "action":"$N身形飘忽，有如鬼魅，转了几转，移步到$n的左侧",
        "force" : 240,
        "attack": 80,
        "parry" : 50,
        "dodge" : 170,
        "damage": 200,
        "lvl" : 80,
        "skill_name" : "有如鬼魅",
        "damage_type":  "刺伤"
]),
([      "action":"$N一声冷笑，蓦地里疾冲上前，一瞬之间，与$n相距已不到一尺，$w随即递出",
        "force" : 260,
        "attack": 70,
        "parry" : 40,
        "dodge" : 165,
        "damage": 220,
        "lvl" : 100,
        "skill_name" : "疾冲上前",
        "damage_type":  "刺伤"
]),
([      "action":"$N喝道：“好！”，便即拔出$w，反手刺出，跟着转身离去",
        "force" : 300,
        "attack": 90,
        "parry" : 45,
        "dodge" : 180,
        "damage": 230,
        "lvl" : 120,
        "skill_name" : "反手刺出",
        "damage_type":  "刺伤"
]),
([      "action":"$n只觉眼前一花，似乎见到$N身形一幌，但随即又见$N回到原地，却似从未离开",
        "force" : 340,
        "attack": 80,
        "parry" : 40,
        "dodge" : 185,
        "damage": 250,
        "lvl" : 140,
        "skill_name" : "眼前一花",
        "damage_type":  "刺伤"
]),
([      "action":"$N向后疾退，$n紧追两步，突然间$N闪到$n面前，手中$w直指$n的$l",
        "force" : 380,
        "attack": 100,
        "parry" : 50,
        "dodge" : 190,
        "damage": 270,
        "lvl" : 160,
        "skill_name" : "向后疾退",
        "damage_type":  "刺伤"
]),
([      "action":"$N蓦地冲到$n面前，手中$w直刺$n右眼！$n慌忙招架，不想$N的$w突然转向",
        "force" : 410,
        "attack": 130,
        "parry" : 55,
        "dodge" : 210,
        "damage": 300,
        "lvl" : 180,
        "skill_name" : "直刺右眼",
        "damage_type":  "刺伤"
]),
([      "action":"$N飞身跃起，$n抬眼一望，但见得$N从天直落而下，手中$w刺向$n的$l",
        "force" : 440,
        "attack": 130,
        "parry" : 50,
        "dodge" : 230,
        "damage": 320,
        "lvl" : 200,
        "skill_name" : "飞身跃起",
        "damage_type":  "刺伤"
]),
([      "action":"$N腰枝猛摆，$n眼前仿佛突然出现了七八个$N，七八只$w一起刺向$n",
        "force" : 480,
        "attack": 140,
        "parry" : 60,
        "dodge" : 270,
        "damage": 340,
        "lvl" : 220,
        "skill_name" : "腰枝猛摆",
        "damage_type":  "刺伤"
]),
});

mapping *unarmed_action = ({
([      "action":"突然之间，白影急幌，$N向后滑出丈余，立时又回到了原地",
        "force" : 100,
        "attack": 40,
        "parry" : 20,
        "dodge" : 70,
        "damage": 50,
        "lvl" : 0,
        "skill_name" : "白影急幌",
        "damage_type":  "刺伤"
]),
([      "action":"$N右手伸出，在$n手腕上迅速无比的一按，$n险些击中自己小腹",
        "force" : 120,
        "attack": 50,
        "parry" : 30,
        "dodge" : 65,
        "damage": 60,
        "lvl" : 12,
        "skill_name" : "自己小腹",
        "damage_type":  "刺伤"
]),
([      "action":"蓦地里$N猱身而上，蹿到$n的身后，又跃回原地",
        "force" : 125,
        "attack": 60,
        "parry" : 35,
        "dodge" : 85,
        "damage": 70,
        "lvl" : 25,
        "skill_name" : "猱身而上",
        "damage_type":  "刺伤"
]),
([      "action":"$N突然间招法一变，手臂忽伸忽缩，招式诡奇绝伦。$n惊骇之中方寸大乱",
        "force" : 130,
        "attack": 70,
        "parry" : 40,
        "dodge" : 60,
        "damage": 80,
        "lvl" : 5,
        "skill_name" : "招法一变",
        "damage_type":  "刺伤"
]),
([      "action":"$N身形飘忽，有如鬼魅，转了几转，移步到$n的左侧",
        "force" : 140,
        "attack": 80,
        "parry" : 50,
        "dodge" : 70,
        "damage": 100,
        "lvl" : 35,
        "skill_name" : "有如鬼魅",
        "damage_type":  "刺伤"
]),
([      "action":"$N一声冷笑，蓦地里疾冲上前，一瞬之间，与$n相距已不到一尺，手指随即刺出",
        "force" : 160,
        "attack": 70,
        "parry" : 40,
        "dodge" : 65,
        "damage": 120,
        "lvl" : 45,
        "skill_name" : "疾冲上前",
        "damage_type":  "刺伤"
]),
([      "action":"$N喝道：“好！”，便即反手刺出一指，跟着转身离去",
        "force" : 200,
        "attack": 90,
        "parry" : 45,
        "dodge" : 80,
        "damage": 130,
        "lvl" : 55,
        "skill_name" : "反手刺出",
        "damage_type":  "刺伤"
]),
([      "action":"$n只觉眼前一花，似乎见到$N身形一幌，但随即又见$N回到原地，却似从未离开",
        "force" : 190,
        "attack": 80,
        "parry" : 40,
        "dodge" : 85,
        "damage": 150,
        "lvl" : 65,
        "skill_name" : "眼前一花",
        "damage_type":  "刺伤"
]),
([      "action":"$N向后疾退，$n紧追两步，突然间$N闪到$n面前，手掌忽的劈向$n的$l",
        "force" : 180,
        "attack": 100,
        "parry" : 50,
        "dodge" : 70,
        "damage": 170,
        "lvl" : 75,
        "skill_name" : "向后疾退",
        "damage_type":  "震伤"
]),
([      "action":"$N蓦地冲到$n面前，指尖直刺$n右眼！$n慌忙招架，不想$N的手腕突然转向",
        "force" : 250,
        "attack": 130,
        "parry" : 55,
        "dodge" : 74,
        "damage": 200,
        "lvl" : 85,
        "skill_name" : "直刺右眼",
        "damage_type":  "震伤"
]),
([      "action":"$N飞身跃起，$n抬眼一望，但见得$N从天直落而下，挥掌砍向$n的$l",
        "force" : 340,
        "attack": 130,
        "parry" : 50,
        "dodge" : 80,
        "damage": 220,
        "lvl" : 94,
        "skill_name" : "飞身跃起",
        "damage_type":  "震伤"
]),
([      "action":"$N腰枝猛摆，$n眼前仿佛突然出现了七八个$N，七八只手掌一起拍向$n",
        "force" : 400,
        "attack": 140,
        "parry" : 60,
        "dodge" : 110,
        "damage": 240,
        "lvl" : 120,
        "skill_name" : "腰枝猛摆",
        "damage_type":  "震伤"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" ||
               usage == "parry" ||
               //usage == "force" ||
               //usage == "unarmed" ||
               usage == "dodge";
}

int double_attack() { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("pixie-jian", 1);
        return lvl * lvl * 17 * 15 / 100 / 200;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(weapon_action) - 1; i >= 0; i--)
                if (level >= weapon_action[i]["lvl"])
                        return weapon_action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -40;
        int p_e1 = -80;
        int p_e2 = -60;
        int f_e1 = 150;
        int f_e2 = 230;
        int m_e1 = 240;
        int m_e2 = 340;
        int i, lvl, seq, ttl;
        mapping *action;

        if (objectp(weapon))
                action = weapon_action;
        else
                action = unarmed_action;

        ttl = sizeof(action);
        lvl = (int) me->query_skill("pixie-jian", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : action[seq]["damage_type"],
        ]);
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        if( query("character", me) == "光明磊落" ||
            query("character", me) == "狡黠多变" )
                return notify_fail("你心中暗道：这辟邪剑法损人损己，修炼来何用。\n");

        if( query("gender", me) == "女性" &&
            !query("special_skill/ghost", me) )
                return notify_fail("自古以来没听说过女人可以修习葵花宝典。\n");

        if( query("gender", me) == "男性" &&
            !query("special_skill/ghost", me) )
        {
                me->receive_wound("qi", 50);
                return notify_fail(HIR "\n你试着修炼辟邪剑法，霎时只觉内息忽然大"
                                   "乱，几欲焚身。\n" NOR);
        }

        /*
        if( !query("family/family_name", me) ||
            query("family/family_name", me) != "日月神教" )
                return notify_fail("辟邪剑法只有日月神教的人方能领会。\n");
        */

        if( query("int", me)<34 )
                return notify_fail("你的天资不足，无法理解辟邪剑法的深意。\n");

        if( query("dex", me)<32 )
                return notify_fail("你先天身法孱弱，难以修炼辟邪剑法。\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法造诣太浅，无法理解辟邪剑法。\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("你的基本轻功造诣太浅，无法理解辟邪剑法。\n");

        if (me->query_skill("parry", 1) < 100)
                return notify_fail("你的基本架造造诣太浅，无法理解辟邪剑法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("你的基本剑法造诣有限，无法理解更高深的辟邪剑法。\n");

        if (me->query_skill("dodge", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("你的基本轻功造诣有限，无法理解更高深的辟邪剑法。\n");

        if (me->query_skill("parry", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("你的基本招架造诣有限，无法理解更高深的辟邪剑法。\n");

/*
        if (me->query_skill("unarmed", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("你的基本拳脚造诣有限，无法理解更高深的辟邪剑法。\n");
*/

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("pixie-jian", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("pixie-jian", 1);

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$N" HIR "眼睛一花，$n" HIR "已没了踪"
                                            "影。突然$n" HIR "从身后拍了一下$N" HIR "的"
                                            "头，轻轻跃开。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "眼前一花，似乎见到$n" HIR "身"
                                            "形一晃，但随即又见$n" HIR "回到原地，却似"
                                            "从未离开。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIR "$n" HIR "身形飘忽，有如鬼魅，转了几转"
                                            "，移步到$N" HIR "的身后，躲过了$N" HIR "这"
                                            "一招。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "突然间白影急晃，$n" HIR "向后滑出丈余"
                                            "，立时又回到了原地，躲过了$N" HIR "这一招"
                                            "。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "$N" HIY "眼睛一花，$n" HIY "已没了踪影"
                                 "。可是$N" HIY "精通易理，丝毫不为所乱，尽自"
                                 "出招。\n" NOR;
                        break;
                case 1:
                        result = HIY "$N" HIY "眼前一花，似乎见到$n" HIY "身"
                                 "形一晃。$N" HIY "一声冷笑，已瞬间看破招中虚"
                                 "实。\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "身形飘忽，有如鬼魅，转了几转，"
                                 "可是$N" HIY "理也不理，连续数招径直攻出。\n"
                                 NOR;
                        break;
                default:
                        result = HIY "突然间白影急晃，$n" HIY "向后滑出丈余，"
                                 "可是$N" HIY "不假思索，追身攻上，更是巧妙无"
                                 "方。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("pixie-jian", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 40;
        if (lvl < 200) return 60;
        if (lvl < 250) return 80;
        if (lvl < 300) return 100;
        if (lvl < 350) return 120;
        return 130;
}


void cimu_end(object me, object target)
{
        if( target && query_temp("block_msg/all", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "抹了抹流着的"
                                        HIR "鲜血" HIC "，终于能看"
                                        "见了。\n" NOR, target);

                        tell_object(target, HIR "你终于抹掉了眼前的"
                                            "鲜血，能看见了。\n" NOR);
                }
                delete_temp("block_msg/all", target);
        }
        return;
}

void poyuan_end(object me, object target)
{
        if (target && target->query_condition("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被扰乱的真气"
                                            "慢慢平静了下来。\n" NOR);
                }
                target->clear_condition("no_perform");
        }
        return;
}

void exert_end(object me, object target)
{
        if (target && target->query_condition("no_exert"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到周身穴道不再疼痛，轻松多了。\n" NOR);
                }
                target->clear_condition("no_exert");
        }
        return;
}

mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        // 辟邪劍影特效
        if( random(20)<5 && query_temp("pixie-jian/pfm_jian", me) )
        {
                switch(random(9))
                {
                        case 0:
                        case 4:
                        case 5:
                        case 6:
                                if( !query_temp("block_msg/all", victim) )
                                {
                                        set_temp("block_msg/all", 1, victim);
                                        call_out("cimu_end", 20, me, victim);
                                        message_combatd(HIR "$N" HIR "只觉双目一阵剧痛，眼前一黑，就什么"
                                               "也看不见了，顿时长声痛极而呼。\n" NOR, victim);
                                }
                                break;
                        case 1:
                                if (! victim->query_condition("no_perform"))
                                {
                                        victim->apply_condition("no_perform", 5);
                                        call_out("poyuan_end", 15, me, victim);
                                        message_combatd(HIR "$N" HIR "只觉眼前寒芒一闪而过，随即全身一阵"
                                                "刺痛，几股血柱自身上射出。\n$N陡然间一提真气，"
                                                "竟发现周身力道竟似涣散一般，全然无法控制。\n" NOR, victim);
                                }
                                break;
                        case 2:
                                set("jiali", 0, victim);
                                break;
                        case 3:
                                if (! victim->query_condition("no_exert"))
                                {                       
                                        victim->apply_condition("no_exert", 1);
                                        call_out("exert_end", 30, me, victim);
                                        message_combatd(HIR "$N" HIR "只觉寒光逼人，随即全身一阵"
                                                "刺痛，气门已伤。\n$N陡然间一提真气，"
                                                "竟发现周身穴道具痛无比。\n" NOR, victim);
                                }
                                break;
                        default:
                                if (! victim->is_busy())
                                        victim->start_busy(8);                          
                                break;
                }
        }
        weapon=query_temp("weapon", me);

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        attack_time = (int)(me->query_skill("pixie-jian", 1) / 40);

        if (attack_time > 8)
                attack_time = 8;

        if (me->is_busy()
           || ! living(victim)
           || random(3) < 1
           || damage_bonus < 120
           || query_temp("px_link", me)
           || query_temp("pixie-jian/hit_msg", me)
           || query("neili", me)<300
           || query_temp("action_flag", me) == 1
           || me->query_skill("pixie-jian", 1) < 120)
                return 0;

        if( query_temp("pixie-jian/pfm_jian", me) ) tell_object(me,HIG"---------------------------=\n"NOR);
        // 避免在使用Pfm时讯息重复
        if( !query_temp("pixie-jian/hit_msg", me) )
                message_combatd(HIW "\n霎时间只见$N" HIW "鬼魅般揉身冲上，" + name +
                               HIW "指指点点，宛如夜雨流星，连续刺向$n" HIW "！\n"
                               NOR, me, victim);

//        me->start_busy(1 + random(attack_time / 10));
        addn("neili", -200, me);
        set_temp("px_link", 1, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, weapon, 3);
        }
        delete_temp("px_link", me);
        return 1;
}

int practice_skill(object me)
{
        return notify_fail(HIC "辟邪剑法只能通过研习「辟邪剑谱」或「葵花"
                           "宝典」来学习。\n" NOR);
}

int difficult_level()
{
        return 800;
}

string perform_action_file(string action)
{
            return __DIR__"pixie-jian/" + action;
}

/*
string exert_function_file(string action)
{
        return __DIR__"pixie-jian/exert/" + action;
}
*/
/*
void do_interlink(object me, object victim)
{
        int skill, i, j;
        object *enemy;
        object weapon;

        if( userp(me) && !query("reborn/times", me) )
                return;

        skill = me->query_skill("pixie-jian", 1);
        if( random(skill)>400 && objectp(weapon=query_temp("weapon", me)) )
        {
                enemy = me->query_enemy();
                if (! sizeof(enemy)) return;
                addn_temp("str", skill/10, me);
                addn_temp("dex", skill/10, me);
                // 对所有敌人均自动进行攻击
                for (i = 0; i < sizeof(enemy); i++)
                {
                        for (j = 0; j < (skill / (60 * sizeof(enemy))); j++)
                        if( (me->is_fighting(enemy[i]) || enemy[i]->is_fighting(me)) && query("qi", enemy[i])>0 )
                        {
                                if (environment(me) == environment(enemy[i]))
                                {
                                        COMBAT_D->do_attack(me,enemy[i],query_temp("weapon", me),0);
                                }
                        } else break;
                }
                addn_temp("str", -skill/10, me);
                addn_temp("dex", -skill/10, me);
        }
}
*/

int help(object me)
{
        write(HIC"\n辟邪剑法："NOR"\n");
        write(@HELP

    要说辟邪剑法，就要从《葵花宝典》谈起。

    《葵花宝典》是一位宦官所作。这样一位大高手，为什麽在皇
宫中做太监，那是谁也不知道。至於宝典中所载的武功，却是精深
之极，三百多年来，始终无一人能据书练成。百余年前，这部宝典
为福建莆田少林寺下院所得。其时莆田少林寺方丈红叶禅师，乃是
一位大智大慧的了不起人物，依照他的武功悟性，该当练成宝典上
所载武功才是。但他研究多年，直到逝世，始终没有起始练宝典中
的武功。

    一日华山派的岳肃和蔡子峰到莆田少林寺作客，偷看到《葵花
宝典》。其时匆匆之际，二人不及同时阅遍全书，当下二人分读，
一人读一半，後来回到华山，共同叁悟研讨。不料二人将书中功夫
一加印证，竟然牛头不对马嘴，全然合不上来。二人都深信对方读
错了书，只有自己所记的才是对的。华山的剑气二宗之分由此而起。

    红叶禅师不久发现此事，他知道这部宝典所载武学不仅博大精
深，且蒹凶险之极。这最难的还是第一关，只消第一关能打通，到
後来也没什麽。第一关只要有半点岔差，立时非死即伤。红叶当下
派遣得意弟子渡元禅师前往华山，劝论岳蔡二位，不可修习宝典中
的武学。

    渡元禅师上得华山，岳蔡二人对他好生相敬，承认私阅《葵花
宝典》，一面深致歉意，一面却以经中所载武学向他请教。殊不知
渡元虽是红叶的得意弟子，宝典中的武学却未蒙传授。当下渡元禅
师并不点明，听他们背诵经文，随口加以解释，心中却暗自记下。
渡元禅师武功本极高明，又是绝顶机智之人，听到一句经文，便己
意演绎几句，居然也说来头头是道。

    不过岳蔡二人所记的本已不多，经过这麽一转述，不免又打了
折扣。渡元禅师在华山上住了八日，这才作别，但从此却也没再回
到莆田少林寺去。不久红叶禅师就收到渡元禅师的一通书信，说道
他凡心难抑，决意还俗，无面目再见师父云云。

    由於这一件事，华山派弟子偷窥《葵花宝典》之事也流传於外。
过不多时，魔教十长老来攻华山，在华山脚下一场大战。魔教十长
老多身受重伤，大败而去。但岳肃和蔡子峰两人均在这一役中毙命，
而二人所录《葵花宝典》也被魔教夺了去。

    渡元禅师还俗之後，复了原姓，将法名颠倒过来取名远图，娶
妻生子，创立镖局，在江湖上轰轰烈烈干了一番事业。

    莆田少林寺的红叶禅师园寂之时，召集门人弟子，说明这部宝
典的前因後果，便即将其投如炉中火化。红叶说：这部武学秘笈精
妙奥妙，但其中许多关键之处，当年的撰作人并未能妥为叁通解透，
留下的难题太多。尤其是第一关难过，不但难过，简直是不能过不
可过，流传後世，实非武林之福。

    林远图的辟邪剑法，是从《葵花宝典》残篇中悟出的武功，两
者系出同源。辟邪剑法有七十二路，但一来从不外传，二来使用此
剑法之人个个动作迅捷诡异，外间无人得知其招法的名目，只知道
其招式乃匪夷所思。林远图所自录的《辟邪剑谱》加了许多自己的
解释，故较魔教所藏的《葵花宝典》易入门，但少了些内容。所以
玩家欲习此功，当遵循先易後难之序。致於如何得到这两部武林秘
笈，则一直是江湖上避而不谈的秘密。如泄露此秘，会招来杀身之
祸。

        学习要求：
                自宫做太监
HELP
        );
        return 1;
}
