// douzhuan-xingyi.c 斗转星移

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
// inherit F_SSERVER;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *parry_msg = ({
        YEL"蓦地里一股力道飞来，将$n一引一带，$n身子轻轻越起，身行落在一旁。\n"NOR,
        BLU"$n当下一股内力冲向$l，$N击向$n的$l的招数莫名奇妙的溜滑向一旁。\n"NOR,
        HIW"$n双手前探，左臂搭上$N右臂，右臂使出$N的招数将$N此招化去。\n"NOR,
        HIY"$n星移斗转，$N这招莫名其妙的在中途转了方向，直奔自己袭来。\n"NOR,
        YEL"$n作壁上观，双手与对方相交数掌，谈笑间竟使出$N成名技艺，使得$N不知如何是好。\n"NOR,
        BLU"$n凝神运气向$N猛攻快打，使出的招数好似$N的成名绝技，把$N的招数化于无行。\n"NOR,
        HIW"只见$n身如飘风，恰似漫天星移，诡异地一式，双掌动向无定不可捉摸地拍向$N的$l。\n"NOR,
        HIY"$n身行飘忽不定，在星移斗转之间反用$N的招数击向$N，却令人$N百思不得其解。\n"NOR,
        HIY"$n轻轻一带，$N发现自己招数回击过来，吓得往后倒退几步。\n"NOR,
        HIY"$n手臂回转，在$N手肘下轻轻一推，$N招数落空。\n"NOR,
        HIY"$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，直往前扑去。\n"NOR,
        HIY"$n双手回圈，$N只觉得前面好象有一堵墙，再也攻不进去。\n"NOR,
});

string *unarmed_parry_msg = ({
        "但是被$p双掌一推，$N的攻势顿时变了方向。\n",
        "$n身形一转，$N只觉得的所有的力道全部都落到了空处。\n",
        "但是$N感觉像打到棉花上一样，说不出的怪异。\n",
});

int valid_enable(string usage) { return usage=="parry"; }
string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}
int valid_learn(object me)
{
//      object ob;
        int d_lvl = (int) me->query_skill("douzhuan-xingyi",1);
        //int s_lvl = (int) me->query_skill("shenyuan-gong",1);
        int s_lvl = (int) me->query_skill("force",1);
        int l_lvl = (int) me->query_skill("literate",1);

        if ((int)me->query_skill("parry", 1) < 100)
                return notify_fail("你的基本招架技巧掌握的还不够熟练，无法学习斗转星移。\n");
        if( (int)me->query_int() < 40 )
                return notify_fail("你仔细地想了一会，还是没明白借力用力的道理。\n");
        if( query("max_neili", me)<600 )
                return notify_fail("你的内力不够，没有办法练斗转星移。\n");
        if( s_lvl < 100)
                return notify_fail("斗转星移必须先学好神元功才能练习。\n");
        if( s_lvl + 30 < d_lvl)
                return notify_fail("你的内功级别不够你真正领会更高级的斗转星移。\n");
        if( l_lvl < 1000 && (l_lvl + 50 < d_lvl) )
                return notify_fail("你的读书写字水平不够你领会更高级的斗转星移。\n");
        return 1;
}
int practice_skill(object me)
{
        return notify_fail("斗转星移只能通过学习来提高。\n");
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1; }

mixed valid_damage(object ob, object me, int damage, object weapon)
{
         mixed result;
         int ap, dp, mp, apr, opr, app, opp, rantemp;
         int lvl, ran;
         string msg;

         if ((int) me->query_skill("douzhuan-xingyi", 1) < 100 ||
          ! living(me) )
              return;

          // 移星换月效果
          if (query_temp("yixinghuanyue", me))
          {
                me->stop_busy();
                me->clear_weak();
          }

          mp = ob->query_skill("count", 1);
          ap = ob->query_skill("force", 1);
          dp = me->query_skill("parry", 1);

          lvl = me->query_skill("douzhuan-xingyi", 1);

          // 特殊反伤害几率
          if (lvl > 280)ran = 50;
          if (lvl > 300)ran = 45;
          if (lvl > 320)ran = 35;
          if (lvl > 350)ran = 30;
          if (lvl > 380)ran = 20;
          if (lvl > 400)ran = 10;
          if (lvl > 450)ran = 8;
          if (lvl > 500)ran = 6;
          if (lvl > 550)ran = 4;
          if (lvl > 600)ran = 2;

          apr = me->query_skill("force", 1) + me->query_skill("dodge", 1) +
          me->query_skill("martial-cognize", 1);
          opr = ob->query_skill("force", 1) + ob->query_skill("parry", 1) +
          ob->query_skill("martial-cognize", 1);

          app = apr - opr;

          if (app > 0)
          {
             if (app > 1500)app=1500;

             //等级差别特殊反伤害几率调整系数

                opp = 10;
             if (lvl > 280)opp = 30;
             if (lvl > 300)opp = 34;
             if (lvl > 320)opp = 43;
             if (lvl > 350)opp = 50;
             if (lvl > 380)opp = 75;
             if (lvl > 400)opp = 150;
             if (lvl > 450)opp = 188;
             if (lvl > 500)opp = 250;
             if (lvl > 550)opp = 375;
             if (lvl > 600)opp = 750;

             rantemp = ran;
             ran = ran - (app / opp);

             if (ran < 2)ran = 2;
             if (ran > rantemp)ran = rantemp;
           }

              // 斗转星移反伤效果

              if (query_temp("yixinghuanyue", me) || (lvl > 280 &&
               //! me->is_busy() &&
               //me->query("max_neili") * 2 / 3 > ob->query("max_neili") &&
               query("neili", me)>500 &&
               mp < 3000 &&
               random(ran) == 1 )
               )
               {
                     set_temp("xingyi/"+query("id", ob), 1, me);
                     me->start_call_out((: call_other, __FILE__, "xingyi",
                                 ob, me :), 1);

                     //if( !query_temp("yixinghuanyue", me) )
                     //   // me->start_busy(2);

                     result = ([ "damage" : -damage ]);
                     result += ([ "msg" : msg ]);

                     return result;

                } else

                if (ap / 3 + random(ap/3) < dp)
                {
                     result = ([ "damage" : -damage ]);

                     switch (random(3))
                      {
                          case 0:
                             result += ([ "msg" : HIC "$n" HIC "身形忽然转个不停，$N"
                                                  HIC "这一招竟然无从下手。\n" NOR ]);
                          break;
                          case 1:
                             result += ([ "msg" : HIC "$n" HIC "单掌一托，$N"
                                                  HIC "登时拿捏不准力道，不禁"
                                                  "泛起一阵有心无力的感觉。\n" NOR ]);
                          break;

                          default:
                             result += ([ "msg" : HIC "$N" HIC "一招眼看击中了$n"
                                                  HIC "，然而$n" HIC "轻轻一卸，"
                                                  "将$N" HIC "的攻击化解于无形。\n" NOR ]);
                          break;
                        }
                     return result;
                  } else

                  if (mp >= 100)
                  {
                        switch (random(3))
                         {
                             case 0:
                               result = HIY "$n" HIY "身形忽然转个不停，然而$N"
                                        HIY "早已看穿其中奥妙，丝毫不受影响，挥招直入。\n" NOR;
                               break;

                              case 1:
                               result = HIY "$n" HIY "单掌一托，$N"
                                        HIY "忽感拿捏不准力道，蓦然警醒，登时变化招式。\n" NOR;
                               break;

                              default:
                               result = HIY "$n" HIY "轻轻一卸力，但是$N"
                                        HIY "已然看出其中四两拨千金的变化，左右腾挪，让$n"
                                        HIY "如意算盘就此落空。\n" NOR;
                               break;
                           }
                          COMBAT_D->set_bhinfo(result);
                    }
}

void xingyi(object ob, object me)
{
        string msg;
        int ap, dp, damage;
        object weapon;
        string menpai;

        if (! ob
        || ! me->is_fighting(ob)
         || !query_temp("xingyi/"+query("id", ob), me) )
                  return;

        menpai=query("family/family_name", ob);
        weapon=query_temp("weapon", me);
        ap = me->query_skill("force");
        dp = ob->query_skill("parry");

        if (dp / 3 + random(dp/3) < ap)
        {
           damage = damage_power(me, "parry");
           damage += query("jiali", me);

           msg = HIY "\n$N" HIY "施展起绝学「斗转星移」  " HIR "----以彼之道，还施彼身----\n" NOR;

              switch (menpai)
               {
                  case "少林派" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIC "$N" HIC "使出达摩剑的绝技「达摩三绝剑」，身法陡然加快！\n"
                                HIR "$n" HIR "大吃一惊，$N" HIR "竟将使出"
                                "$p" HIR"的成名招式。\n"
                                "$n" HIR "一声惨呼，已然闪避不及。\n" NOR);
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");
                         addn("neili", -500, me);
                         // me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIB "$N" HIB "忽然面露凶光，身形变的异常飘渺，在$n"
                                HIB "的四周游走个不停，\n$n" HIB "正迷茫时，$N"
                                HIB "突然近身，毫无声息的一指少林「修罗绝命指」戳"
                                    "出！\n" NOR );
                         addn("neili", -500, me);
                         // me->start_busy(2);
                       }
                       break;

                  case "段氏皇族" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIY "$N" HIY "深吸一口气，脚下步步进击，稳重之极，手中的" +
                                weapon->name() + HIY "使得犹如飞龙一般，缠绕向$n" HIY "！\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");

                         addn("neili", -500, me);
                         // me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, 0, 0,
                                HIY "$N" HIY "陡然使出「" HIR "一指乾坤" HIY "」绝技，单指劲"
                                "点$n" HIY "檀中要穴，招式变化精奇之极！\n" NOR );
                         msg += HIR "$n" HIR "只觉胸口一麻，已被$N"
                                HIR "一指点中，顿时气血上涌，全身酸软"
                                "。\n" NOR;
                         ob->start_busy(5+random(2));

                         addn("neili", -500, me);
                         // me->start_busy(2);
                       }
                       break;

                  case "武当派" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIC "$N" HIC "使出柔云剑法「三环套月」，一招之中另蕴三招，铺天"
                                "盖地罩向$n" HIC "！\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");
                         addn("neili", -500, me);
                         // me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIW "$N" HIW "使出太极拳「震」字诀，左手高，右手低，陡然"
                                "回圈，企图以内力震伤$n" HIW "。\n" NOR );

                         addn("neili", -500, me);
                         // me->start_busy(2);
                       }
                       break;

                  case "峨嵋派" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIY "$N" HIY "跨步上前，手中" + weapon->name() +
                                HIY "将峨嵋剑法运转如飞，剑光霍霍径直逼向$n"
                                HIY "。\n" NOR );
                         addn("neili", -500, me);
                         // me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, 0, 0,
                                HIC "$N" HIC "使出天罡指穴法绝技「凌空指穴」，左手"
                                "一连七指向着$n" HIC "胸前大穴接连戳出。\n" NOR );
                         msg += HIR "结果$p" HIR "不及攻敌，拼力躲避$P"
                                HIR "指力顿时动作大乱！\n" NOR;
                         ob->start_busy(3+random(3));

                         addn("neili", -500, me);
                         // me->start_busy(2);
                       }
                       break;

                  case "逍遥派" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIY "$N" HIY "一声清啸，剑法忽变，手中" + weapon->name() + HIY
                                "轻轻划出，带出一条无比绚丽的剑芒，遥指$n" HIY "而去。\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");

                         addn("neili", -500, me);
                         // me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIR "只听$N" HIR "一声断喝，双掌纷飞，一式「攀阳邀月」接"
                                "二连三向$n" HIR "攻去。\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");

                         addn("neili", -500, me);
                         // me->start_busy(2);
                       }
                       break;

                  case "星宿派" :
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIR "$N" HIR "悄然游走至$n" HIR "跟前，陡然使出"
                                "三阴手绝技「损筋诀」，单掌轻轻拂过$n" HIR "太阳"
                                "穴，不着半点力道。\n" NOR );
                         msg += HIY "$n大吃一惊，却又突然发现，虽然招式套路完全一样，"
                                "但自己却未中半分毒，不禁舒了口长气。\n" NOR;
                         addn("neili", -500, me);
                         // me->start_busy(2+random(2));

                       break;

                  case "血刀门" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIW "$N" HIW "嗔目大喝，将手中武器横握做刀" HIW "一势「"
                                HIR "赤炼神刀" HIW "」迸出漫天血光，铺天盖地洒向$n"
                                HIW "。\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,"");

                         addn("neili", -500, me);
                         // me->start_busy(3+random(3));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIR "$N" HIR "目睚俱裂，一声爆喝，全身骨骼劈啪作响，拳"
                                "头如闪电般击向$n" HIR "的要害！\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIR "$N" HIR "大喝一声，面色赤红，全身骨骼劈啪作响，又"
                                "一拳如闪电般击向$n \n" NOR );

                         addn("neili", -500, me);
                         // me->start_busy(5);
                       }
                       break;

                       default :
                         msg = HIM "\n$N" HIM "默运紫徽心法，施展起绝学「斗转星移」，\n"
                               HIM "一股真气在体内迅速惯行，巧妙地牵引着$n \n"
                               HIM "的招式。\n" NOR;
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 200,
                               HIR "\n$n" HIR "大吃一惊，不料$N" HIR "竟将"
                               "$p" HIR"先前的招式尽数折回反攻向自己。\n猛"
                               "然间$n" HIR "一声惨呼，已然闪避不及。\n" NOR);

                         addn("neili", -500, me);
                         // me->start_busy(2);

                  }

        } else
        {
               msg = HIC "$n" HIC "眼见$P来势汹涌，不敢"
                      "大意，施出浑身解数化解开来。\n" NOR;
        }
           delete_temp("xingyi", me);
           message_combatd(msg, me, ob);
}

string perform_action_file(string action)
{
        return __DIR__"douzhuan-xingyi/" + action;
}
int help(object me)
{
        write(HIC"\n斗转星移："NOR"\n");
        write(@HELP

    姑苏慕容家最拿手的绝技，乃是一门借力打力之技，叫做“斗
转星移”。外人不知底细，见到慕容氏“以彼之道，还施彼身”神
乎其技，凡在致人死命之时，总是以对方的成名绝技加诸其身，显
然天下各门各派的绝技，姑苏慕容氏无一不会，无一不精。其实武
林中绝技千千万万，任他如何聪明渊博，决难将每一项绝技都学会
了，何况既是绝技，自非朝夕之功所能练成。但慕容氏有了这一门
巧妙无比的“斗转星移”之术，不论对方施出何种功夫来，都能将
之转移力道，反击到对方自身。出手的人武功越高，死法就越是巧
妙。慕容氏若非单打独斗，若不是有把握定能致敌死命，这“斗转
星移”的功夫便决不使用，是以姑苏慕容氏名震江湖，真正的功夫
所在，却是谁也不知。将对手的兵刃拳脚转换方向，令对手自作自
受，其中道理，全在“反弹”两字。便如有人一拳打在石墙之上，
出手越重，拳头上所受的力道越大，轻重强弱，不差分毫。只不过
转换有形的兵刃拳脚尚易，转换无形无质的内力气功，那就极难。

        学习要求：
                不叛师
                慕容复的嫡传弟子
                后天悟性40
                神元功100级
                神元功不能低于斗转星移30级
                读书写字不能低于斗转星移50级
                内力600
HELP
        );
        return 1;
}
