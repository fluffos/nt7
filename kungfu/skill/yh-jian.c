#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
        "突然之间，微风吹过，$n身影一花，仿佛没有任何动作，却躲过了$N这一招。\n",
        "$n手掌一竖，$N觉得一股劲风扑面而来不禁眨了一下眼，再看时，$n已经换了个位置。\n",
        "$n手指一点，$N全身一麻，$n慢慢踱到一旁。\n",
        "$n身形飘忽，有如风中柳絮，飘了起来，飘到$N的身后，躲过了$N这一招。\n",
        "$N只觉眼前一花，似乎见到$n身形一幌，但随即又见$n回到原地，却似从未离开。\n",
        "$N眼睛一花，$n已没了踪影。突然$n从身后拍了一下$N的头，轻轻跃开。\n",
        "$n轻轻一笑，高贵之极，$N竟不知如何是好，停住了攻击。\n",
});

string *finger_name = ({ "左手中指", "左手无名指", "左手食指",
                         "右手中指", "右手无名指", "右手食指", }); 

mapping *action = ({
([          "action":"突然之间，微风轻拂，$N向后滑出丈余，立时又回到了原地", // 描述
            "force" : 1600,                                                   // 攻击力
            "attack": 400,                                                    // 命中点
            "parry" : 300,                                                         // 如果该找可以做招架则招架点数
            "dodge" : 1200,                                                          // 轻功点数，同parry
            "damage": 1500,                                                         // 伤害力
            "lvl" : 0,                                                         // 发出该招要求的等级
            "skill_name" : "飘絮追风",                                       // 该找名字
            "damage_type":  "刺伤"                                           // 伤害类型
]),
([          "action":"$N右手伸出，在$n手腕上迅速无比的一按，$n险些击中自己小腹",    
            "force" : 1800,
            "attack": 500,
            "parry" : 300,
            "dodge" : 1350,
            "damage": 1600,
            "lvl" : 20,
            "skill_name" : "黯然神伤",
            "damage_type":  "刺伤"
]),
([          "action":"蓦地里$N猱身而上，蹿到$n的身后，又跃回原地",
            "force" : 2250,
            "attack": 600,
            "parry" : 350,
            "dodge" : 1550,
            "damage": 1700,
            "lvl" : 40,
            "skill_name" : "飘絮戏风",
            "damage_type":  "刺伤"
]),
([          "action":"$N突然间招法一变，$w忽伸忽缩，招式诡奇绝伦。$n惊骇之中方寸大乱",
            "force" : 2300,
            "attack": 700,
            "parry" : 400,
            "dodge" : 1600,
            "damage": 1800,
            "lvl" : 60,
            "skill_name" : "随风摆柳",
            "damage_type":  "刺伤"
]),
([          "action":"$N身形飘忽，有如柳絮，转了几转，移步到$n的左侧",
            "force" : 2400,
            "attack": 800,
            "parry" : 500,
            "dodge" : 1700,
            "damage": 2000,
            "lvl" : 80,
            "skill_name" : "风中飘絮",
            "damage_type":  "刺伤"
]),
([          "action":"$N一声冷笑，蓦地里疾冲上前，一瞬之间，与$n相距已不到一尺，$w随即递出",
            "force" : 2600,
            "attack": 700,
            "parry" : 400,
            "dodge" : 1650,
            "damage": 2200,
            "lvl" : 100,
            "skill_name" : "迎风而上",
            "damage_type":  "刺伤"
]),
([          "action":"$N喝道：“好！”，便即拔出$w，反手刺出，跟着转身离去",
            "force" : 3000,
            "attack": 900,
            "parry" : 450,
            "dodge" : 1800,
            "damage": 2300,
            "lvl" : 120,
            "skill_name" : "回首望月",
            "damage_type":  "刺伤"
]),
([          "action":"$n只觉眼前一花，似乎见到$N身形一幌，但随即又见$N回到原地，却似从未离开",
            "force" : 3400,
            "attack": 800,
            "parry" : 400,
            "dodge" : 1850,
            "damage": 2500,
            "lvl" : 140,
            "skill_name" : "飘絮乱眼",
            "damage_type":  "刺伤"
]),
([          "action":"$N向后疾退，$n紧追两步，突然间$N闪到$n面前，手中$w直指$n的$l",
            "force" : 3800,
            "attack": 1000,
            "parry" : 500,
            "dodge" : 1900,
            "damage": 2700,
            "lvl" : 160,
            "skill_name" : "进退两难",
            "damage_type":  "刺伤"
]),
([          "action":"$N蓦地冲到$n面前，手中$w直刺$n右眼！$n慌忙招架，不想$N的$w突然转向",
            "force" : 4100,
            "attack": 1300,
            "parry" : 550,
            "dodge" : 2100,
            "damage": 3000,
            "lvl" : 180,
            "skill_name" : "暗送秋波",
            "damage_type":  "刺伤"
]),
([          "action":"$N飞身跃起，$n抬眼一望，但见得$N从天直落而下，手中$w刺向$n的$l",
            "force" : 4400,
            "attack": 1300,
            "parry" : 500,
            "dodge" : 2300,
            "damage": 3200,
            "lvl" : 200,
            "skill_name" : "天外飞仙",
            "damage_type":  "刺伤"
]),
([          "action":"$N腰枝猛摆，$n眼前仿佛突然出现了七八个$N，七八只$w一起刺向$n",
            "force" : 4800,
            "attack": 1400,
            "parry" : 600,
            "dodge" : 2700,
            "damage": 3400,
            "lvl" : 220,
            "skill_name" : "柳枝轻摇",
            "damage_type":  "刺伤"
]),
});

// valid_enable()函数返回该技能可激发的种类
int valid_enable(string usage)
{
        return usage == "sword" ||
               usage == "dodge" ||
               usage == "parry" ||
               usage == "unarmed";
}

// 返回1表示该找可以一招两式
int double_attack() { return 1; }

// 这个不用说了吧，是yanjiu和learn的时候调用的函数
int valid_learn(object me)
{
        if (wiz_level(me)==0)
                return notify_fail("不是巫师无法学习炎黄神剑。\n");
  
        if( query("int", me)<100 )
                return notify_fail("你的天资不足，无法理解炎黄神剑的深意。\n");

        if( query("dex", me)<100 )
                return notify_fail("你先天身法孱弱，难以修炼炎黄神剑。\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法造诣太浅，无法理解炎黄神剑。\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("你的基本轻功造诣太浅，无法理解炎黄神剑。\n");

        if (me->query_skill("parry", 1) < 100)
                return notify_fail("你的基本架造造诣太浅，无法理解炎黄神剑。\n");

        if (me->query_skill("sword", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("你的基本剑法造诣有限，无法理解更高深的炎黄神剑。\n");

        if (me->query_skill("dodge", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("你的基本轻功造诣有限，无法理解更高深的炎黄神剑。\n");

        if (me->query_skill("parry", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("你的基本招架造诣有限，无法理解更高深的炎黄神剑。\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("你的基本拳脚造诣有限，无法理解更高深的炎黄神剑。\n");

        return 1;
}

// 这个是标准函数不需要修改
string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

// 这个是标准函数不需要修改
mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yh-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

// 返回闪避信息
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

// 被对方打中后调用的函数，比如将该招激发为招架或轻功
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("yh-jian", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("yh-jian", 1);

        if (ap / 2 + random(ap) < dp)
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
                        result += (["msg" : HIR "$n" HIR "身形飘忽，有如柳絮，随风飘荡"
                                            "，飘到$N" HIR "的身后，躲过了$N" HIR "这"
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
                                 "形一晃。$N" HIY "一声轻笑，已瞬间看破招中虚"
                                 "实。\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "身形飘忽，有如柳絮，随风飘荡，"
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

// 当该招激发为轻功时的轻功效果
int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yh-jian", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 60;
        if (lvl < 150) return 80;
        if (lvl < 200) return 120;
        if (lvl < 250) return 160;
        if (lvl < 300) return 200;
        if (lvl < 350) return 240;
        return 300;
}

// 当打中对方时调用的函数
mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        weapon=query_temp("weapon", me);

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        attack_time = (int)(me->query_skill("yh-jian", 1) / 40);

        if (attack_time > 8)
                attack_time = 8;

        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || victim->is_busy()
           || damage_bonus < 120
            || query("neili", me)<300
            || query_temp("action_flag", me) == 0
           || me->query_skill("yh-jian", 1) < 120)
                return 0;

        // 避免在使用Pfm时讯息重复
        if( !query_temp("yh-jian/hit_msg", me) )
                message_vision(HIW "\n霎时间只见$N" HIW "鬼魅般揉身冲上，" + name +
                               HIW "指指点点，宛如夜雨流星，连续刺向$n" HIW "！\n"
                               NOR, me, victim);

        me->start_busy(1 + random(attack_time));
        addn("neili", -attack_time*20, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, weapon, 0);
        }

        return 1;
}

// 当练习该招时调用的函数
int practice_skill(object me)
{
        return notify_fail(HIC "炎黄神剑只能向[小宝乖乖]学习。\n" NOR);
}

// 该招的学习难度
int difficult_level()
{
        return 15000;
}

// 该招的perform文件位置__DIR__代表当前目录；
string perform_action_file(string action)
{
        return __DIR__"yh-jian/" + action;
}