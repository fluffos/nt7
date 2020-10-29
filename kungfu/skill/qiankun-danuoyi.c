// This program is a part of NT MudLIB
// qiankun-danuoyi.c 乾坤大挪移

#include <ansi.h>;
#include <combat.h>

inherit SKILL;

string type() { return "martial"; }
string martialtype() { return "parry"; }
int qk_layer(object me);
//string main_skill() { return "yinyang-shiertian"; }

string *parry_msg = ({
        HIY"$N一招击在$n身上，却被$n暗运乾坤大挪移，将内力尽数移入地下。\n"NOR,
        HIW"$n轻轻一带，$N发现自己招数回击过来，吓得往后倒退几步。\n"NOR,
        HIC"$n手臂回转，在$N手肘下轻轻一推，$N招数落空。\n"NOR,
        HIG"$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，直往前扑去。\n"NOR,
        MAG"$n身形不动，$N一招击下，有如石沉大海，不觉呆住了。\n"NOR,
        HIM"$n左牵右引，$N如身处漩流，连续转了好几个圈。\n"NOR,
        GRN"$n双手回圈，$N只觉得前面好象有一堵墙，再也攻不进去。\n"NOR,
        HIY"$n轻轻一转，$N一招击在地上，只打得尘土飞扬。\n"NOR,
});
mapping *action = ({
([      "action": "$n轻轻一转，一招击在地上，只打得尘土飞扬。",
        "force" : 350,
        "attack": 90,
        "dodge" : -90,
        "parry" : -90,
        "damage": 100,
        "damage_type":  "刺伤"
]),
});
string *pfail_msg = ({
        "$n暗运乾坤大挪移，试图将内力尽数移入地下，然而$N早已勘破其中奥妙，内力变化莫测。\n",
        "$n轻轻一带，$N发现自己招数回击过来，急忙变招，身转如意，反让$n防不胜防。\n",
        "$n手臂回转，在$N手肘下轻轻一推，然而$N招数忽的一变，并未落空。\n",
        "$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，顺势变招扑前直击。\n",
        "$n左牵右引，$N如身处漩流，顺势变招，圆转如意，随心所欲。\n",
        "$n双手回圈，$N只觉得前面好象有一堵墙，猛然警醒，聚力于一点，力攻对方。\n",
});
string *dodge_msg = ({
        "$N一招击在$n身上，却被$n暗运乾坤大挪移，将内力尽数移入地下。\n",
        "$n轻轻一带，$N发现自己招数回击过来，吓得往后倒退几步。\n",
        "$n手臂回转，在$N手肘下轻轻一推，$N招数落空。\n",
        "$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，直往前扑去。\n",
        "$n身形不动，$N一招击下，有如石沉大海，不觉呆住了。\n",
        "$n左牵右引，$N如身处漩流，连续转了好几个圈。\n",
        "$n双手回圈，$N只觉得前面好象有一堵墙，再也攻不进去。\n",
        "$n轻轻一转，$N一招击在地上，只打得尘土飞扬。\n",
});

int valid_enable(string usage)
{
        return (usage == "parry") /*|| (usage == "dodge") || (usage=="move")*/;
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int valid_research(object me)
{
        int canlvl;
        canlvl = ((int)query("int", me) - 30 ) * 50;

        if (query("int", me) < 34 &&
                me->query_skill("qiankun-danuoyi", 1) >= canlvl )
                return notify_fail(HIG "你觉得更深层次的乾坤大挪移实在是深奥无比，全然无法理解。\n" NOR);

        if (me->query_skill("qiankun-danuoyi", 1) < 310)
                return notify_fail(HIG "你对乾坤大挪移的认识还不足以自行研究提高！\n" NOR);

        return 1;
}

int valid_learn(object me)
{
        int layer;

        if( (!me->query_family() ||
            me->query_family() != "明教") && (!query("reborn/times", me) || member_array("明教", query("reborn/fams", me)) == -1) )
                return notify_fail("你不是明教中人，无法修习！\n");

        if (query("gender", me) == "无性" &&
            me->query_skill("qiankun-danuoyi", 1) >= 50)
                return notify_fail("你试图按照心法修炼大挪移，却"
                                   "觉得心中一阵迷茫，难以继续。\n");

        if (me->query_condition("qiankun-except"))
                return notify_fail("你现在体内若冰、四肢皆寒、面赤"
                                   "如火，无法继续修炼神功。\n");

        layer = (int)me->query_skill("qiankun-danuoyi", 1) / 50;
        if (layer > 7) layer = 7;

        if (query("int", me) < 27 + layer)
                return notify_fail("你觉得第" + chinese_number(layer) +
                                   "层乾坤大挪移实在是深奥无比，全然无法理解。\n");

        if ((int)query("max_neili", me) < 6000)
                return notify_fail("你的内力修为太差，无法修炼乾坤大挪移。\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("你的内功火候不够，无法修炼乾坤大挪移。\n");

        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("你的基本招架火候有限，无法体会更高深的乾坤大挪移。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("你的基本内功火候有限，无法体会更高深的乾坤大挪移。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        mapping sk, ma;
        int ap, dp, mp;
        string wn, na;
                string vid;
                
        if (!ob || ! living(ob))
                return; 
                vid = query("id", ob);          
        sk = ob->query_skills();
        ma = ob->query_skill_map();

        if ((int)me->query_skill("qiankun-danuoyi", 1) < 100
           || ! living(me))
                return;
       
        mp = ob->query_skill("count", 1);
        ap = attack_power(ob,"force") + mp;
        dp = defense_power(me,"parry");
        
                //计算乾坤大挪移的层数
                ap+= ap*qk_layer(me)/10; 
                
        // 挪移乾坤效果
        if (query_temp("nuozhuan", me))
        {
                me->stop_busy();
                me->clear_weak();
                me->clear_freeze();
        }

        if( (ap / 3 + random(ap/3) < dp || (query_temp("nuozhuan", me) && random(100) < 90))
        //&&  !me->is_busy()
        && playerp(me)
        &&  !query_temp("nuoyi", me)
        &&  !query_temp("nuoyi", ob)
        &&  me->query_skill("qiankun-danuoyi", 1) > 350
        //&&  query("max_neili", me) > random(query("max_neili", ob))
        &&  sizeof(sk)
        &&  sizeof(ma) != 0
        &&  mapp(ma))
        {
                if (objectp(weapon = query_temp("weapon", ob)))
                {
                        wn = query("skill_type", weapon);
                        na = ob->query_skill_mapped(wn);
                } else

                if (ob->query_skill_prepared("finger"))
                        na = ob->query_skill_mapped("finger");
                else

                if (ob->query_skill_prepared("strike"))
                        na = ob->query_skill_mapped("strike");
                else

                if (ob->query_skill_prepared("claw"))
                        na = ob->query_skill_mapped("claw");
                else

                if (ob->query_skill_prepared("cuff"))
                        na = ob->query_skill_mapped("cuff");
                else

                if (ob->query_skill_prepared("hand"))
                        na = ob->query_skill_mapped("hand");
                else
                        na = ob->query_skill_mapped("unarmed");

                msg = HIM "\n$N" HIM "一招攻出，却见$n" HIM "迎身而"
                      "上，冷笑道：「区区" + CHINESE_D->chinese(na) +
                      HIM "，能奈我何？」\n$n" HIM "当即运起乾坤大挪"
                      "移第七层心法，企图挪移$N" HIM "的攻势。\n\n" NOR;
                                          
                set_temp("nuoyi/"+vid, 1, me);
                me->start_call_out((: call_other, __FILE__, "nuoyi",
                                      ob, me, damage, vid :), 1);
                // me->start_busy(2);

                result = ([ "damage" : -damage,
                            "msg"    : msg ]);

                return result;
        } else
        if (ap / 4 + random(ap/4) < dp || (query_temp("nuozhuan", me) && random(100) < 90))
        {
                msg = parry_msg[random(sizeof(parry_msg))];
                msg = replace_string(msg, "$N", "$N" HIG);
                msg = replace_string(msg, "$n", "$n" HIG);
                msg = HIG + msg + NOR;

                result = ([ "damage": -damage,
                            "msg"   : msg ]);

                return result;
        } else
        if (mp >= 100)
        {
                msg = pfail_msg[random(sizeof(pfail_msg))];
                msg = replace_string(msg, "$N", "$N" HIY);
                msg = replace_string(msg, "$n", "$n" HIY);
                msg = HIY + msg + NOR;
                COMBAT_D->set_bhinfo(msg);
        }
}

void skill_improved(object me)
{
        int lvl;
        int layer;

        lvl = me->query_skill("qiankun-danuoyi", 1);
        layer = lvl / 50;
        if (layer > 7) layer = 7;

        if (! layer)
        {
                tell_object(me, HIM "你潜心修炼乾坤大挪"
                            "移心法，若有所悟。\n" NOR);
        } else
        if ((lvl % 50) == 0)
        {
                tell_object(me, HIM "你修炼成了第" + chinese_number(layer) +
                            "层的乾坤大挪移心法。\n" NOR);
        } else
                tell_object(me, HIM "你对第" + chinese_number(layer) +
                            "层的乾坤大挪移心法又加深了一层了解。\n" NOR);

        if( query("special_skill/nopoison", me) ) return;
        if (lvl > me->query_skill("force") * 2 / 3)
        {
                if (lvl < me->query_skill("force") * 2 / 3 + 10)
                {
                        tell_object(me, HIG "你觉得内息一阵紊乱，丹田时冷时"
                                        "热，不由得大吃一惊。\n心想莫非是走"
                                        "火入魔？丹田越来越是寒冷，极为难受"
                                        "。\n" NOR);

                        message("vision", HIG + me->name() + HIG "的脸色忽红"
                                          "忽绿，变得不停，只是浑身颤抖，似"
                                          "乎十分痛苦。\n" NOR,
                                          environment(me), ({ me }));
                        return;
                }
                tell_object(me, HIB "你忽然觉得丹田腾起一阵寒意，霎时间四肢"
                                "百赅一起变得寒冷无比，忍不住大声呻吟。\n" NOR);

                message("vision", HIB + me->name() + HIB "忽然一抖，脸色忽然"
                                  "变得惨白，隐然笼罩了一股绿气，呻吟不止。"
                                  "\n" NOR, environment(me), ({ me }));
        } else

        if (lvl < 350 && (lvl * 20 + 4000) > query("max_neili", me))
        {
                if ((lvl * 20 + 4000) < query("max_neili", me) + 200)
                {
                        tell_object(me, HIR "你试着运转了一下内息，一时觉得内"
                              "力不济，看来还是不要贸然修炼大挪移神功。\n" NOR);
                        return;
                }

                tell_object(me, HIR "你试着运转了一下内息，忽然觉得一口气"
                      "竟然转不过来，顿时心中绞痛，接连吐了几口鲜血。\n" NOR);
                message("vision", HIR + me->name() + HIR "脸色忽然"
                        "一变，呕出几口鲜血，触目惊心。\n" NOR,
                        environment(me), ({ me }));
        } else
                return;

        me->apply_condition("qiankun-except", lvl +
           (int)me->query_condition("qiankun-except"));
}

void nuoyi(object ob, object me, int damage,string vid)
{
        string msg;
        int ap, dp, delta, jy, qk, fmsk, flagremote;

        if (! ob
           || ! living(me)
           || ! me->is_fighting(ob)
           || ! query_temp("nuoyi/" + vid, me))
                   {
                      set_temp("nuoyi/"+vid, 0, me);
              return;
                        }

        set_temp("nuoyi/"+vid, 0, me);
        msg = HIM "\n$N" HIM "乾坤大挪移第七层心法施展出来，顿将先前所积蓄"
              "的十余道力量归并为一掌，朝$n" HIM "疾拍而出，这便如一座大湖"
              "在山洪爆发时储满了洪水却突然崩决，洪水急冲而出一般。\n" NOR;
                          
        jy = me->query_skill("jiuyang-shengong",1);
                qk = me->query_skill("qiankun-danuoyi",1);
                fmsk = me->query_skill("guangming-jing",1);
                
                if(jy > 6000  || qk > 5000) flagremote = SPECIAL_ATTACK;
                if(jy > 12000 || qk > 10000) flagremote = REMOTE_ATTACK;
                
        ap = attack_power(me, "unarmed");
        dp = defense_power(ob, "force");
        ap+= ap*fmsk/100*5/100;
        // me->start_busy(2);
        delta = ABILITY_D->check_ability(me, "power-qkdny-nuozhuan"); // 门派ab
        if( delta ) 
                {
                    ap += ap*delta/100;
            damage += damage*delta/100;
                }
        damage *= 10;
        if (dp / 2 + random(dp) < ap)
        {
                msg += COMBAT_D->do_damage(me, ob, flagremote, damage, 200+fmsk/10,
                                           HIR "只听$n" HIR "一声惨叫，将$N"
                                           HIR "返回的力道受了个十足，全身喀"
                                           "嚓喀嚓一阵脆响，腕骨、臂骨、肩骨"
                                           "、肋骨竟然一齐折断。\n" NOR);
        } else
        {
                msg += HIC "$n" HIC "眼见$P来势汹涌，不敢"
                       "大意，施出浑身解数化解开来。\n" NOR;
        }
 
        message_sort(msg, me, ob);
}

int practice_skill(object me)
{
        return notify_fail("乾坤大挪移只能通过读<<乾坤大挪移心法>>提高。\n");
}
int qk_layer(object me)
{
        int lvl;
                lvl = me->query_skill("qiankun-danuoyi", 1);
                
                if(lvl < 30)    return 1;
                if(lvl <240)    return 2;
                if(lvl <810)    return 3;
                if(lvl <1920)   return 4;
                if(lvl <3750)   return 5;
                if(lvl <6780)   return 6;
                if(lvl <10290)  return 7;
                return 8;
}
int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("qiankun-danuoyi", 1);
        if (lvl < 50) return 50;
        if (lvl < 100) return 80;
        if (lvl < 150) return 100;
        if (lvl < 200) return 120;
        if (lvl < 250) return 130;
        if (lvl < 300) return 140;
        if (lvl < 350) return 150;
        if (lvl < 400) return 200;
        return 220;
}

string perform_action_file(string action)
{
        return __DIR__"qiankun-danuoyi/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.5; }

int help(object me)
{
        write(HIC"\n乾坤大挪移："NOR"\n");
        write(@HELP

    “乾坤大挪移”是明教历代相传一门最厉害的武功，是明教的
护教神功。为波斯大盗山中老人所创，专门讲述运气使力的法门。
中原会用的人甚少，自明教三十三代教主阳顶天死后，几乎失传，
但后来张无忌一番奇遇，以其深厚的内功一朝而成。乾坤大挪移只
作招架和轻功用，不具攻击。其威力之所在是可以把别人的招数尽
数还于对方。
    乾坤大挪移神功的主旨，乃在颠倒一刚一柔、一阴一阳的乾坤
二气，脸上现出青红之色，便是体内血液沉降、真气变换之象。练
至第六层时，全身都能忽红忽青，但到第七层时，阴阳二气转换于
不知不觉之间，外形上便半点也瞧不出表征了。其根本道理也并不
如何奥妙，只不过先求激发自身潜力，然后牵引挪移敌劲，但其中
变化神奇，却是匪夷所思。

        学习要求：
                基本内功100级并不得低于乾坤大挪移的级别
                九阳神功不得低于乾坤大挪移的级别
                内力1500并不得低于乾坤大挪移的级别的15倍
                太监无法领悟100级以上的乾坤大挪移
HELP
        );
        return 1;
}

