// six-fingers.c 六脉神剑
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

//string main_skill() { return "yinyang-shiertian"; }

mapping *action = ({
([      "name":   "少商剑",
        "action": "$N双手拇指同时捺出，嗤嗤两声急响，「" HIW "少商剑" NOR "」有如石破"
                  "天惊、风雨大至",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 0,
        "weapon" : HIW "少商剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少商剑",
        "action": "$N大拇指一按，嗤嗤两指，劲道使得甚巧，「" HIW "少商剑" NOR "」剑气"
                  "如怒潮般涌至",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 10,
        "weapon" : HIW "少商剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少商剑",
        "action": "$N大拇指连挥，「" HIW "少商剑" NOR "」便如是一幅泼墨山水，纵横倚斜"
                  "，剑路雄劲",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 20,
        "weapon" : HIW "少商剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少商剑",
        "action": "$N双手拇指同时捺出，「" HIW "少商剑" NOR "」大开大阖，气派宏伟，每"
                  "一剑都有风雨大至之势",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 30,
        "weapon" : HIW "少商剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "商阳剑",
        "action": "$N食指连动，手腕园转，「" HIW "商阳剑" NOR "」一剑又一剑的刺出，轻"
                  "灵迅速，剑气纵横",
        "force" : 440,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 40,
        "weapon" : HIW "商阳剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "商阳剑",
        "action": "$N变招奇速，右手食指疾从袖底穿出，「" HIW "商阳剑" NOR "」登时幻出"
                  "无数指影",
        "force" : 440,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 50,
        "weapon" : HIW "商阳剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "商阳剑",
        "action": "$N拇指一屈，食指随即点出，嗤嗤两声急响，变成商阳剑法，「" HIW "商"
                  "阳剑" NOR "」激射刺出",
        "force" : 440,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 60,
        "weapon" : HIW "商阳剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "商阳剑",
        "action": "$N以食指急运「" HIW "商阳剑" NOR "」之无形剑气，却不过是手指在数寸"
                  "范围内一点一戳",
        "force" : 480,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 70,
        "weapon" : HIW "商阳剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "中冲剑",
        "action": "$N右手中指一竖，「" HIW "中冲剑" NOR "」向前刺出。真气鼓荡，嗤然声"
                  "响，无形剑气直指$n",
        "force" : 560,
        "attack": 155,
        "dodge" : 10,
        "parry" : 70,
        "damage": 220,
        "lvl"   : 80,
        "weapon" : HIW "中冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "中冲剑",
        "action": "$N将中指向上一刺，「" HIW "中冲剑" NOR "」拔地而起，接着手指向下一"
                  "划，剑气如利刀般砍出",
        "force" : 560,
        "attack": 145,
        "dodge" : 10,
        "parry" : 70,
        "damage": 220,
        "lvl"   : 90,
        "weapon" : HIW "中冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "中冲剑",
        "action": "电光火石之间，$N猛然翻掌，右手陡然探出，中指「" HIW "中冲剑" NOR
                  "」向$n一竖",
        "force" : 560,
        "attack": 135,
        "dodge" : 10,
        "parry" : 70,
        "damage": 220,
        "lvl"   : 100,
        "weapon" : HIW "中冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "关冲剑",
        "action": "$N右手无名指伸出，「" HIW "关冲剑" NOR "」剑路拙滞古朴，一股雄浑无"
                  "比的内力鼓荡而出",
        "force" : 530,
        "attack": 140,
        "dodge" : 100,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 110,
        "weapon" : HIW "关冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "关冲剑",
        "action": "$N俯身斜倚，无名指「" HIW "关冲剑" NOR "」弹射而出，指尖已对准$n发"
                  "出了一缕强烈的劲风",
        "force" : 530,
        "attack": 140,
        "dodge" : 100,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 120,
        "weapon" : HIW "关冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "关冲剑",
        "action": "$N无名指轻轻一挥，「嗤啦」一声，拙滞古朴的「" HIW "关冲剑" NOR "」"
                  "剑气向$n直射而出",
        "force" : 530,
        "attack": 140,
        "dodge" : 100,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 130,
        "weapon" : HIW "关冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少泽剑",
        "action": "$N左手小指一伸，一条气流从少冲穴中激射而出，「" HIW "少泽剑" NOR
                  "」出手入风，指向$n",
        "force" : 500,
        "attack": 160,
        "dodge" : 95,
        "parry" : 92,
        "damage": 270,
        "lvl"   : 140,
        "weapon" : HIW "少泽剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少泽剑",
        "action": "忽见$N左手小指一伸，一条气流从$P少冲穴中激射而出，一股「" HIW "少"
                  "泽剑" NOR "」登时射向$n",
        "force" : 500,
        "attack": 160,
        "dodge" : 95,
        "parry" : 92,
        "damage": 270,
        "lvl"   : 150,
        "weapon" : HIW "少泽剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少冲剑",
        "action": "$N右手小指伸出，真气自少冲穴激荡而出，「" HIW "少冲剑" NOR "」横生"
                  "奇变，飕的刺向$n",
        "force" : 480,
        "attack": 150,
        "dodge" : 90,
        "parry" : 95,
        "damage": 240,
        "lvl"   : 160,
        "weapon" : HIW "少冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少冲剑",
        "action": "$N掌托于胸前，伸出右小指，一招「" HIW "少冲剑" NOR "」缓缓地点向$n"
                  "的周身大穴",
        "force" : 530,
        "attack": 170,
        "dodge" : 90,
        "parry" : 95,
        "damage": 260,
        "lvl"   : 170,
        "weapon" : HIW "少冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少冲剑",
        "action": "$N小指一弹，「" HIW "少冲剑" NOR "」化式「分花拂柳」，剑势如同柳絮"
                  "一般，飘而不乱",
        "force" : 430,
        "attack": 180,
        "dodge" : 90,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 180,
        "weapon" : HIW "少冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少冲剑",
        "action": "$N一招「" HIW "少冲剑" NOR "」，剑气回转无定形，竟从左侧绕了过来，"
                  "点向$n",
        "force" : 530,
        "attack": 180,
        "dodge" : 90,
        "parry" : 95,
        "damage": 240,
        "lvl"   : 190,
        "weapon" : HIW "少冲剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "name":   "少冲剑",
        "action": "$N右手小指一挥，一招「" HIW "少冲剑" NOR "」点点刺刺破空刺出，宛如"
                  "雕花刺画一般",
        "force" : 530,
        "attack": 180,
        "dodge" : 90,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 200,
        "weapon" : HIW "少冲剑气" NOR,
        "damage_type":  "刺伤"
]),
});

mapping sub_skills = ([
        "shaoshang-sword"  : 120,
        "shangyang-sword"  : 120,
        "zhongchong-sword" : 120,
        "guanchong-sword"  : 120,
        "shaoze-sword"     : 120,
        "shaochong-sword"  : 120,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        if( (!query("family/family_name", me) ||
            query("family/family_name", me) != "段氏皇族") )
        {
                tell_object(me, "你研究了一会儿，只觉的不是段氏皇族的根本无法理解其中奥妙\n");
                return 0;
        }

        if( query("int", me)<32 || me->query_int()<44 )
        {
                tell_object(me, "你演练完毕，只感六种剑法毫无牵连，看来依你的悟性，无"
                                "法将其合一。\n");
                return 0;
        }

        if( query("con", me)<26 || me->query_con()<39 )
        {
                tell_object(me, "你演练完毕，只觉全身真气乱窜，眼冒金星，两耳轰鸣，好"
                                "不容易才控制下来。\n");
                return 0;
        }

        if( query("gender", me) == "无性" )
        {
                tell_object(me, "你无根无性，阴阳不调，难以演练六脉神剑。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 200)
        {
                tell_object(me, "你觉得六脉神剑极其深奥，看来多研究一下学问可能更有帮"
                                "助。\n");
                return 0;
        }

        if (me->query_skill("lamaism", 1) < 200)
        {
                tell_object(me, "你演练完毕，发现如果通晓密宗心法应该更有帮助。\n");
                return 0;
        }

        if (me->query_skill("buddhism", 1) < 200)
        {
                tell_object(me, "你演练完毕，发现如果通晓禅宗心法应该更有帮助。\n");
                return 0;
        }

        if ((int)me->query_skill("force") < 300)
        {
                tell_object(me, "你演练完毕，几乎虚脱，自己的内功水平看来还有待提高。\n");
                return 0;
        }

        if( query("max_neili", me)<5000 )
        {
                tell_object(me, "你演练完毕，丹田提不起半点力来，看来应该继续锻炼内力。\n");
                return 0;
        }

        if ((int)me->query_skill("martial-cognize", 1) < 100)
        {
                tell_object(me, "你演练完毕，发现如果武学修养更上一层因该更有所帮助。\n");
                return 0;
        }

        if (random(10) < 5)
        {
                tell_object(me, "你对六脉神剑的奥妙颇有领悟，或许再演练一次就能够融会贯通。\n");
                return 0;
        }

        tell_object(me, HIY "一阵凡尘往事涌上心头，你几欲放声长叹。眼前不断闪现出六脉"
                            "剑法，\n霎那间，你终于通晓六脉神剑。\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}
int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练六脉神剑必须空手。\n");

        if( (!query("family/family_name", me) ||
            query("family/family_name", me) != "段氏皇族") &&
            (!query("yuanshen_level", me) || member_array("段氏皇族", query("reborn/fams", me)) == -1))
                return notify_fail("你研究了一会儿，只觉的不是段氏皇族的根本无法理解其中奥妙\n");

        if( query("int", me)<32 )
                return notify_fail("你研究了半天，只感六种剑法毫无牵连，无法再作研究。\n");

        if( query("con", me)<26 )
                return notify_fail("你研究了一会儿，只觉得眼前金星乱冒，太阳穴突突的跳。\n");

        if (me->query_skill("literate", 1) < 120)
                return notify_fail("你觉得六脉神剑极其深奥，不是你这种学问水平所能研究的。\n");

        if (me->query_skill("lamaism", 1) < 120)
                return notify_fail("你发现这里面有很多奥妙都和密宗心法有关，难以理解。\n");

        if (me->query_skill("buddhism", 1) < 120)
                return notify_fail("你发现这里面有很多奥妙都和禅宗心法有关，难以理解。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的内力太弱，无法学六脉神剑。\n");

        if ((int)me->query_skill("finger", 1) < 120)
                return notify_fail("你的基本指法火候不够。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("six-finger", 1) + 10)
                return notify_fail("你的现在必须先提高你基本内功的水平。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("six-finger", 1) + 10)
                return notify_fail("你的现在必须先提高你基本指法的水平。\n");

        return 1;
}

int practice_skill(object me)
{
        object* ob, obj;
        int i,skill,damage,cost;
        cost=40;
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必须空手才能练习。\n");
        if( query("qi", me)<160 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<160 )
                return notify_fail("你的内力不够练六脉神剑。\n");
        if( skill>100 && query("shen", me)<1 )
                return notify_fail("这种武功当得行侠义事。\n");
        if ((int)me->query_skill("six-finger", 1)>150) cost=80;
        if ((int)me->query_skill("six-finger", 1)>250) cost=150;
        me->receive_damage("qi", cost);
        addn("neili", -150, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        string name;

        if (userp(me))
                attack_time = (int)(me->query_skill("six-finger", 1) / 50);
        else
                attack_time = (int)(me->query_skill("six-finger", 1) / 25);

        // 放宽NPC的攻击力度
        if (userp(me) && attack_time > 6)
                attack_time = 6;

        if (! me->is_busy()
        && living(victim)
        && random(3) == 0
        && !query_temp("action_flag", me)
        && !query_temp("six-finger/hit_msg", me)
        && damage_bonus > 120
        && query("neili", me)>400
        && me->query_skill("martial-cognize", 1) >= 220
        && me->query_skill("six-finger", 1) >= 180
        && me->query_skill("jingluo-xue", 1) >= 200)
        {
                if( !query_temp("six-finger/hit_msg", me) )
                        message_combatd(HIW "\n霎时间$N" HIW "只觉思绪狂涌，六脉剑谱中"
                                       "的六路剑法交替展现，登时十指纷弹，此去彼来，连"
                                       "绵无尽。\n" NOR, me, victim);

                me->start_busy(1);

                addn("neili", -attack_time*50, me);

                set_temp("action_flag", 1, me);
                for (i = 0; i < attack_time; i++)
                {
                        if (! me->is_fighting(victim))
                                break;
                        COMBAT_D->do_attack(me, victim, 0, 3);
                }
                delete_temp("action_flag", me);
        }

        if (damage_bonus > victim->query_dex() / 10
        && damage_bonus > 150
        && query("neili", me)>200
        && me->query_skill("martial-cognize", 1) >= 220
        && me->query_skill("six-finger", 1) >= 160
        && me->query_skill("jingluo-xue", 1) >= 180)
        {
                addn("neili", -50, me);
                victim->receive_wound("qi", damage_bonus, me);
                return random(2) ? HIR "你听到「嗤啦」一声轻响，脸上竟飞溅到了一些血滴"
                                   "！\n" NOR:

                                   HIR "你只听「噗嗤」一声轻响，一股血柱至$n" HIR "身上"
                                   "溅出！\n" NOR;
        }
        return 1;
}


/*
void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);
        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames);
}
*/

int double_attack()
{
        return 1;
}
mapping query_action(object me, object weapon)
{
        int d_e1 = 25;
        int d_e2 = 5;
        int p_e1 = -30;
        int p_e2 = -50;
        int f_e1 = 800;
        int f_e2 = 1000;
        int i, lvl, seq, ttl = sizeof(action);

        if (random(me->query_skill("six-finger",1)) > 60 &&
                me->query_skill("kurong-changong",1) > 60 &&
                query("neili", me)>100 )
        {
                addn("neili", -50, me);
                return ([
                        "action" : "$N忽然觉得剑谱中的六路剑法一一涌向心头，十指纷弹，此去彼来，连绵无尽。剑气纵横，尘烟四起，\n"
                        "六路剑法回转运使，$n顿时心神大乱，但觉全身几处刺痛，几股鲜血从身上标出。忍痛抬头一看，一柱剑气迎面又到\n",
                        "dodge": -50,
                        "parry": -50,
                        "damage": 800,
                        "force": 800,
                        "damage_type": "刺伤"]);
        }
        else
        {
                if (random(10) == 8)
                {
                        addn("neili", -200, me);
                        return ([
                                "action": HIC "$N" HIC "忽然觉得剑谱中的六路剑法一一涌向心头，十指纷弹，此去彼来，连绵无尽。\n" NOR
                                "顿时只见四处剑气纵横，尘烟四起，六路剑法回转运使，$n顿时心神大乱，但觉全身几处刺\n"
                                "痛，几股" HIR "鲜血" NOR "从身上标出。忍痛抬头一看，一柱剑气迎面又到",
                                "attack": 140,
                                "dodge" : -150,
                                "parry" : -120,
                                "damage": 1000,
                                "force" : 1000,
                                "damage_type": "刺伤"]);
                }
                lvl = (int)me->query_skill("six-finger", 1);
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
                        "damage_type" : random(2) ? "内伤" : "刺伤",
                ]);
        }
}

string query_parry_msg(object victim_weapon)
{
        switch (random(4))
        {
        case 0:
                return "$n随意挥洒，道道剑气纵横交错，宛若天网，$N唯有望洋兴叹，徒呼奈何。\n";
        case 1:
                return "$n不闪不避，一招中冲剑直袭$N的胸前大穴，迫得$N只有回身自救。\n";
        case 2:
                return "$n六剑连出，剑气回荡，直割得$N眉毛削落，脸面生通，再也不能前进半分！\n";
        default:
                return "$n一声长笑，无形剑气四处散开，将$N层层裹住，惟有勉强支撑。才约略摆脱了$n的反击。\n";
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("six-finger", 1)) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + ob->query_skill("parry") + mp;
        dp = me->query_skill("parry") / 2 +
             me->query_skill("force") / 2 +
             me->query_skill("six-finger", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);


                result += (["msg" : HIC "$n" HIC "危急之时，心中一乱，随手一指，一道剑气凌锐的直奔$N而去。\n"
                                    HIC "$N" HIC "见这招来势凶狠，不得不收招自守，纵身避开。\n" NOR]);

                return result;
        }
}

/*
int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("six-finger", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

*/
int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"six-finger/" + action;
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("six-finger", 1); 

        if( lvl >= 180 && 
            !query("can_perform/six-finger/qi", me) )  
        { 
                tell_object(me, HIC "你通晓了六脉神剑「" HIR "无形剑气" HIC "」的奥秘。\n" NOR);     
                set("can_perform/six-finger/qi", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 200 && 
            !query("can_perform/six-finger/gz", me) )  
        { 
                tell_object(me, HIC "你通晓了六脉神剑「" HIR "六脉归宗" HIC "」的奥秘。\n" NOR);     
                set("can_perform/six-finger/gz", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
        
        if( lvl >= 220 && 
            !query("can_perform/six-finger/shen", me) )  
        { 
                tell_object(me, HIC "你通晓了六脉神剑「" HIR "六脉惊神" HIC "」的奥秘。\n" NOR);     
                set("can_perform/six-finger/shen", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 240 && 
            !query("can_perform/six-finger/six", me) )  
        { 
                tell_object(me, HIC "你通晓了六脉神剑「" HIR "六脉剑气" HIC "」的奥秘。\n" NOR);     
                set("can_perform/six-finger/six", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 260 && 
            !query("can_perform/six-finger/zong", me) )  
        { 
                tell_object(me, HIC "你通晓了六脉神剑「" HIR "纵横天下" HIC "」的奥秘。\n" NOR);     
                set("can_perform/six-finger/zong", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        }                             

        if( lvl >= 800 && query("yuanshen_level", me) &&
            !query("can_perform/six-finger/tian", me) )  
        { 
                tell_object(me, HIC "你通晓了六脉神剑「" HIR "天脉神剑" HIC "」的奥秘。\n" NOR);     
                set("can_perform/six-finger/tian", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        }                 
} 


int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n六脉神剑："NOR"\n");
        write(@HELP

    六脉神剑是大理段氏不传之秘。天龙寺为大理武学之根本，此
技即为天龙镇寺之宝，俗家弟子无法窥其堂奥。六脉神剑并非普通
剑法，而是以无上内力运指作剑，伤敌于无形，亦即“气剑”。

        学习要求：
                枯荣禅功120级
                内力1200
HELP
        );
        return 1;
}

