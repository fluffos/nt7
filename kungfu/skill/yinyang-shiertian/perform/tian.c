#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

string name() { return HIY "十二重天" NOR; }



////////////////////////////////////////
//1  判断内力
//2  判断音律修养
//3  判断佛学及道学修养
//4  判断江湖阅历
//5  判断先天臂力
//6  判断后天臂力及unarmed
//7  判断先天悟性
//8  判断后天悟性及literate
//9  判断先天根骨
//10 判断后天根骨及force
//11 判断先天身法
//12 判断后天身法及dodge
///////////////////////////////////////

string final(object me, object target, int damage);

int perform(object me, object target)
{
        int damage, damage1;
        int p;
        string msg, cl, wp;
        int ap, dp, dp1;
        int lvl;
        object weapon, cloth;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("force", 1) < 1200)
                return notify_fail("你内功修为不够，难以施展" +name()+ "。\n");

        if( query("max_neili", me)<50000 )
                return notify_fail("你内力修为不够，难以施展" +name()+ "。\n");

        if( query("max_jingli", me)<10000 )
                return notify_fail("你精力修为不够，难以施展" +name()+ "。\n");

        lvl = (int)me->query_skill("yinyang-shiertian", 1);
        if (lvl < 1200)
                return notify_fail("你阴阳九转十二重天火候不够，难以施展" +name()+ "。\n");

        if( query("neili", me)<12000 )
                return notify_fail("你现在真气不够，难以施展" +name()+ "。\n");

        if (me->query_skill("martial-cognize", 1) < 500)
                return notify_fail("你武学修养不足，难以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        message_combatd(HIM "\n$N" HIM "口中默念：天道无常。心神沉入十二重天境界，"
                     "连空间似乎也扭曲了起来。$n" HIM "大惊失色，仿佛已身在异界！\n" NOR, me, target);


        ap = attack_power(me, "force");

        damage = damage_power(me, "force");

        if( query_temp("weapon", me) )
        {
                damage+=query_temp("apply/damage", me);
        } else
        {
                damage+=query_temp("apply/unarmed_damage", me);
        }

        damage *= 10;

        dp = defense_power(target, "dodge") + target->query_skill("yinyang-shiertian", 1);

        // 第一招，判断对方内力
        message_combatd(HIW "$N" HIW "双臂一震，一股浑厚至极的内劲汹涌澎湃，"
                     "带着排山倒海之势向$n" HIW "席卷而至。\n" NOR, me, target);

        damage1 = 0;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg = HIW "$n" HIW "举臂欲挡,然而$N" HIW "浑厚的内力无可抵御，"
                              "刹那间就将$n" HIW "全身骨头压碎。" NOR "( $n" RED "受伤过重，已"
                              "经有如风中残烛，随时都可能断气。" NOR ")\n";
                        damage1 = -1;
                        addn("neili", -2000, me);
                } else
                {
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage / 2, me);
                        target->receive_damage("jing", damage / 4, me);
                        target->receive_wound("jing", damage / 8, me);
                        p=query("qi", target)*100/query("max_qi", target);

                        msg = HIY "$n" HIY "思虑未定，$N" HIY "的内劲已破体而入，"
                              "$n" HIY "受此重击，喉口一甜，呕出数口" HIR "鲜血" HIY "。\n" NOR;
                        msg += "( $n" + eff_status_msg(p) + " )\n";

                        addn("neili", -500, me);
                }
        } else
        {
                msg = CYN "$n" CYN "知道$N这招无可抵挡，"
                       CYN "当即飞身跃起丈许，躲闪开来。\n" NOR;
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        if (damage1 < 0)
        {
                me->start_busy(2);
                target->receive_wound("qi", damage, me);
                set("qi", 1, target);
                set("eff_qi", 1, target);
                set("jing", 1, target);
                set("eff_jing", 1, target);
                target->unconcious(me);
                return 1;
        }

        // 第二招，判断对方音律修养
        dp1 = target->query_skill("guzheng-jifa", 1) + target->query_skill("tanqin-jifa", 1) +
              target->query_skill("chuixiao-jifa", 1) + dp;

        message_combatd(HIW "\n$N" HIW "一声清啸，凭借浑厚的内力，凭空吹奏起莫名的曲子,"
                     HIW "欢快中带着一丝淡淡的忧伤，仿佛又回到了遥远的童年。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage / 2, me);
                target->receive_wound("qi", damage / 4, me);
                target->receive_damage("jing", damage * 2 / 3, me);
                target->receive_wound("jing", damage / 2, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$N" HIY "吹奏间隙缓步而上，$n" HIY "却仍沉浸在回忆之中，"
                      HIY "$N" HIY "一击得手。\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";
        } else
        {
                msg = CYN "幸而$n" CYN "精通音律，严阵以待，$N" CYN "无处下手。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第三招，判断对方佛学及道学修养
        dp1 = target->query_skill("buddhism", 1) + target->query_skill("lamaism", 1) +
              target->query_skill("taoism", 1) + dp;

        message_combatd(HIW "\n$N用内力将一股醉人的幽香弥漫开来，便似一个温柔"
                     HIW "美丽的女子卧在身侧一般\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage / 2, me);
                target->receive_wound("qi", damage / 4, me);
                target->receive_damage("jing", damage * 2 / 3, me);
                target->receive_wound("jing", damage / 2, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "霎时间$n" HIY "只感心头滚热，喉干舌燥，说不出的难受。\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";
        } else
        {
                msg = CYN "$n" CYN "凝神守一，丝毫不为所动。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第四招，判断对方江湖阅历
        dp1=query("score", target);
        dp1 /= 20000;
        if (dp1 > 10000)
                dp1 = 10000;
        if (dp1 > 2000)
        {
                dp1 -= 2000;
                dp1 /= 5;
                dp1 += 2000;
        }

        dp1 += dp;

        message_combatd(HIW "\n$N摇身一晃，顿时显现千百人影，$n"
                     HIW "环顾左右，不知$N" HIW "真身何在。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80 + random(15),
                                          (: final, me, target, damage :));
        } else
        {
                msg = CYN "$n" CYN "见多识广，危急时刻终于看清$N"
                      CYN "招式来路，连忙飞身避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第五招，判断对方先天臂力及基本招架
        dp1=query("str")*30+target->query_skill("parry", target)+dp;

        message_combatd(HIW "\n$N" HIW "大喝一声，一招攻向$n" HIW "，虽然"
                     "简单明了，却有石破天惊之势！\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 2, me);
                target->receive_damage("jing", damage / 4, me);
                target->receive_wound("jing", damage / 8, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$n" HIY "面对威力如此强大的一招，根本无法招架，被重重击中，\n"
                      HIY "五脏六腑翻腾不休，口中" HIR "鲜血" HIY "如箭般喷出！\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";

                if( objectp(weapon=query_temp("weapon", target) )
                    && query("stable", weapon)<100
                   && ap / 2 + random(ap) > dp1)
                {
                        wp = weapon->name();
                        msg += HIW "只听“锵”的一声脆响，$n" HIW "手"
                               "中的" + wp + HIW "在$N" HIW "内力激荡"
                               "下应声而碎，脱手跌落在地上。\n" NOR;
                        addn("neili", -150, me);
                        set("consistence", 0, weapon);
                        weapon->move(environment(target));
                }
        } else
        {
                msg = CYN "$n" CYN "见这招来势凶猛，身形疾退，瞬间飘出三"
                      "丈，方才躲过$N" CYN "这招。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第六招，判断对方后天臂力及基本拳脚
        dp1 = target->query_str() * 2 + target->query_skill("unarmed", 1) + dp;

        message_combatd(HIW "\n$N" HIW "前招未落，后招又起，威势十足的向$n"
                     HIW "当面击到！\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                addn("neili", -(lvl+random(lvl)), target);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIY "只听$n" HIY "一声惨叫，被$N" HIY "内劲击中胸前，"
                                          "“喀嚓喀嚓”断了几根肋骨。。\n" NOR, me , target);
        } else
        {
                msg = CYN "$n" CYN "气贯双臂，凝神以对，竟将$N" CYN "之力卸去。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第七招，判断对方先天悟性及基本招架
        dp=query("int")*30+target->query_skill("parry", target)+dp1;

        message_combatd(HIW "\n$N" HIW "一招击向$n" HIW "身前空挡，"
                     "浑厚的内力竟然形成了一个旋涡。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage * 3 / 2, me);
                target->receive_wound("qi", damage * 2 / 3, me);
                target->receive_damage("jing", damage / 4, me);
                target->receive_wound("jing", damage / 8, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$n" HIY "未料到$N" HIW "此招竟击在必经之路，"
                      HIY "来不及变招，身子已经撞入内劲旋涡之中！\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";
        } else
        {
                msg = CYN "$n" CYN "急忙变招，勉强从旋涡旁边掠过。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第八招，判断对方后天悟性及读书写字
        dp1 = target->query_int() * 2 + target->query_skill("literate", 1) + dp;

        message_combatd(HIW "\n$N" HIW "双手其出，胸腹之间竟然露出一个极大的破绽！\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 95 + random(10),
                                          HIY "$n" HIY "一声冷笑，击向$N" HIY "胸前。"
                                          "不想招式未到,$N" HIY "的破绽早已不是破绽！\n" NOR, me , target);
        } else
        {
                msg = CYN "$n" CYN "看破此招乃是诱敌，凝神防守，并不出击。\n" NOR;
        }
        message_combatd(msg, me, target);

                // 第九招，判断对方先天根骨及基本招架
        dp1=query("con")*30+target->query_skill("parry", target)+dp;

        message_combatd(HIW "\n$N连发数招，层层叠叠的内劲便如一堵无形气墙，向前疾冲而"
                     HIW "去。$n" HIW "只觉无路可退，心中大惊。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 2, me);
                target->receive_damage("jing", damage / 4, me);
                target->receive_wound("jing", damage / 8, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$n还在思考如何闪避，如山般的内劲"
                      HIY "已经压了过来，重重击在$n" HIY "的胸口。\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";

                if( objectp(cloth=query_temp("armor/armor", target) )
                    && query("stable", cloth)<100
                   && ap / 2 + random(ap) > dp1)
                {
                        cl = cloth->name();
                        msg += HIW "只听“轰”的一声闷响，$n" HIW "身"
                               "着的" + cl + HIW "在$N" HIW "内力激荡"
                               "下应声而裂，化成一块块碎片。\n" NOR;
                        addn("neili", -150, me);
                        set("consistence", 0, cloth);
                        cloth->move(environment(target));
                }
        } else
        {
                msg = CYN "$n" CYN "会心一笑，一招击在气墙中心，竟将此招破去。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第十招，判断对方后天根骨及基本内功
        dp1 = target->query_con() * 2 + target->query_skill("force", 1) + dp;

        message_combatd(HIW "\n$N" HIW "双臂陡然暴长数尺。只听破空之声骤响，"
                     HIW "双掌幻出漫天掌影，铺天盖地向$n" HIW "攻去。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("jing", damage / 2, me);
                target->receive_wound("jing", damage / 4, me);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                             HIY "$n躲闪不及，被$N" HIY "一招击飞了出去。\n" NOR, me , target);
        } else
        {
                msg = CYN "$n" CYN "面对$N" CYN "这排山倒海攻势，完全"
                                          CYN "无法抵挡，唯有退后几步，凝神应对。\n" NOR;
        }

        message_combatd(msg, me, target);

        // 第十一招，判断对方先天身法及基本招架
        dp1=query("dex")*30+target->query_skill("parry", target)+dp;

        message_combatd(HIW "\n$N" HIW "身体猛然旋转不定，旋起无数小气旋，"
                     HIW "宛若流星赶月，向$n" HIW "电射而去。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 2, me);
                target->receive_damage("jing", damage / 4, me);
                target->receive_wound("jing", damage / 8, me);
                p=query("qi", target)*100/query("max_qi", target);

                msg = HIY "$n" HIY "腾挪闪躲，竭尽全力，也没办法躲开气旋，被击了个正着！\n" NOR;
                msg += "( $n" + eff_status_msg(p) + " )\n";

                if( objectp(cloth=query_temp("armor/cloth", target) )
                    && query("stable", cloth)<100
                   && ap / 2 + random(ap) > dp1)
                {
                        cl = cloth->name();
                        msg += HIW "只听“轰”的一声闷响，$n" HIW "身"
                               "着的" + cl + HIW "在$N" HIW "内力激荡"
                               "下应声而碎，化成一块块碎片。\n" NOR;
                        addn("neili", -150, me);
                        set("consistence", 0, cloth);
                        cloth->move(environment(target));
                }
        } else
        {
                msg = CYN "$n大吃一惊，连忙退后，居然"
                      CYN "侥幸躲开了这一招！\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第十二招，判断对方后天身法及基本轻功
        dp1 = target->query_dex() * 2 + target->query_skill("dodge", 1) + dp;

        message_combatd(HIW "\n$N将身法发挥到极至，幻化出千万人形，一起扑向$n。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp1)
        {
                if (! target->is_busy())
                        target->start_busy(4 + random(lvl / 400));
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIY "$n犹如和数十人战斗，哪里还能抵挡的住，"
                                          HIY "仅仅数息之间，已经身中数招！\n" NOR, me , target);
        } else
        {
                msg = CYN "$n在身边布下层层内劲，将$N" CYN "凌厉的攻势尽数抵挡。\n" NOR;
        }
        message_combatd(msg, me, target);

        me->start_busy(2 + random(5));
        addn("neili", -4000-random(4000), me);
        return 1;
}

/* 12t出现无限降低属性的bug (redl 2014)
string final(object me, object target, int ap)
{
        addn_temp("apply/avoid_busy", -90, target);
        addn_temp("apply/reduce_busy", -36, target);
        addn_temp("apply/avoid_weak", -90, target);
        addn_temp("apply/avoid_locked", -90, target);
        set_temp("no_perform", 1, target);
        remove_call_out("tian_end");
        call_out("tian_end", 10 + random(ap / 50), me, target);
        return HIY "$n" HIY "丝毫不懂此招奥妙，一个疏神，丹田已遭重创！\n" NOR +
               WHT "$n" WHT "感到自身的忽视虚弱，忽视忙乱、忽视绝招冷冻能力被封印。\n" NOR;
}

void tian_end(object me, object target)
{
        if( target && query_temp("no_perform", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被扰乱的真气"
                                            "慢慢平静了下来。\n" NOR);
                }
        addn_temp("apply/avoid_busy", 90, target);
        addn_temp("apply/reduce_busy", 36, target);
        addn_temp("apply/avoid_weak", 90, target);
        addn_temp("apply/avoid_locked", 90, target);
        tell_object(target, HIR "你的忽视虚弱，忽视忙乱、忽视绝招冷冻能力终于解除封印。\n" NOR);
                delete_temp("no_perform", target);
        }
        return;
}

*/
string final(object me, object target, int ap)
{
        if (query_temp("pfm_flag/12t", target)) {
                remove_call_out("tian_end");
                call_out("tian_end", 10 + random(ap / 50), me, target);
        return HIY "$n" HIY "丝毫不懂此招奥妙，一个疏神，丹田已遭重创！\n" NOR +
               WHT "$n" WHT "感到自身的忽视虚弱，忽视忙乱、忽视绝招冷冻能力被封印。\n" NOR;
        }
        set_temp("pfm_flag/12t", 1, target);

        addn_temp("apply/avoid_busy", -90, target);
        addn_temp("apply/reduce_busy", -36, target);
        addn_temp("apply/avoid_weak", -90, target);
        addn_temp("apply/avoid_locked", -90, target);
        set_temp("no_perform", 1, target);
        remove_call_out("tian_end");
        call_out("tian_end", 10 + random(ap / 100), me, target);
        return HIY "$n" HIY "丝毫不懂此招奥妙，一个疏神，丹田已遭重创！\n" NOR +
               WHT "$n" WHT "感到自身的忽视虚弱，忽视忙乱、忽视绝招冷冻能力被封印。\n" NOR;
}

void tian_end(object me, object target)
{
        if (!target) {
                return;
        }
        if (!query_temp("pfm_flag/12t", target)) {
                return;
        }
        addn_temp("apply/avoid_busy", 90, target);
        addn_temp("apply/reduce_busy", 36, target);
        addn_temp("apply/avoid_weak", 90, target);
        addn_temp("apply/avoid_locked", 90, target);
        delete_temp("no_perform", target);
        tell_object(target, HIR "你的忽视虚弱，忽视忙乱、忽视绝招冷冻能力终于解除封印。\n" NOR);
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被扰乱的真气"
                                            "慢慢平静了下来。\n" NOR);
                }
        delete_temp("pfm_flag/12t", target);
        return;
}
