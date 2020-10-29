// hp cmds (Mon  09-04-95)
// Update by Doing
// Update by Lonely

#include <ansi.h>
inherit F_CLEAN_UP;

string status_color(int current, int max);

int main(object me, string arg)
{
        object ob;
        mapping my;
        string sp;
        int craze;

        seteuid(getuid(me));

        if (arg && (arg == "-m"
           || sscanf(arg, "-m %s", arg)
           || sscanf(arg, "%s -m", arg)))
        {
                int ml, mn;
                mixed need, need2;
                // string combat_exp;
                int lv, lv2, level, exp;

                if (arg == "-m")
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");

                my = ob->query_entire_dbase();

                if (userp(ob) && (! stringp(my["born"]) || ! my["born"]))
                        return notify_fail("还没有出生呐，察看什么？\n");

                if (my["max_jing"] < 1 || my["max_qi"] < 1)
                        return notify_fail("无法察看" + ob->name(1) + "的状态。\n");

                // 狂暴铁拳增加加力上限
                if( query("special_skill/might", ob) )
                {
                        ml = (int)ob->query_skill("force") / 2;
                        ml += ml * 20 / 100;
                }
                else
                        ml = (int)ob->query_skill("force") / 2;

                ml += ob->query_all_buff("jiali");

                // 愤怒之心增加加怒上限
                if( query("special_skill/wrath", ob) )
                        mn = ob->query_max_craze() / 70;
                else
                        mn = ob->query_max_craze() / 100;

                exp=query("combat_exp", ob)/100;
                level = to_int(pow(to_float(exp), 1.0 / 3)*10) + 1;

                lv=query("level", ob);
                if (lv < 1) lv = 1;
                need=(lv+1)*(lv+1)*(lv+1)*10000-query("combat_exp", ob);

                if (need < 1) need = 1;

                lv2=query("yuanshen_level", ob);
                if( lv2 < 1 ) need2 = 10000000000-query("combat_exp", ob);
                else if( lv2 == 100 ) need2 = 0;
                else need2 = (lv2+1)*(lv2+1)*(lv2+1)*10000-query("yuanshen_exp", ob);

                sp = (ob == me ? "你" : ob->name()) + "目前的属性上限如下：\n";
                sp += HIC "≡" HIY "----------------------------------------------"
                      "------------------------" HIC "≡\n" NOR;

                sp += sprintf(HIC "【精力上限】 " HIG " %-27d"
                              HIC "【内力上限】 " HIG " %d\n",
                      ob->query_current_jingli_limit(), ob->query_current_neili_limit());

                sp += sprintf(HIC "【潜能上限】 " HIG " %-27d"
                              HIC "【体会上限】 " HIG " %d\n",
                      ob->query_potential_limit()-query("learned_points", ob),
                      ob->query_experience_limit()-query("learned_experience", ob));

                sp += sprintf(HIC "【当前等级】 " NOR + WHT " %-27d"
                              HIC "【升级所需】 " NOR + WHT " %d\n", lv, need);

                sp += sprintf(HIC "【血脉等级】 " NOR + HIR " %-27d"
                              HIC "【升级所需】 " NOR + HIR " %s\n", query("xuemai_level", ob), (100-query("xuemai/points", ob))+"%");

                sp += sprintf(HIC "【元神等级】 " NOR + HIY " %-27d"
                              HIC "【升级所需】 " NOR + HIY " %d\n", lv2, need2);

                sp += sprintf(HIC "【能力点数】 " NOR + WHT " %-27d"
                              HIC "【武功上限】 " NOR + WHT " %d\n",
                      query("ability", ob),level);

                sp += sprintf(HIC "【成就点数】 " NOR + WHT " %-27d"
                              HIC "【活跃点数】 " NOR + WHT " %d\n",
                      query("achievement", ob), query("active", ob));

                sp += sprintf(HIC "【最大加怒】 " NOR + WHT " %-27O"
                              HIC "【最大加力】 " NOR + WHT " %d\n",
                      (mn > 0 ? mn : 0), ml);

#ifdef LONELY_IMPROVED
                sp += HIW "【死亡保护】  " NOR + sprintf("%-27s",
#else
                sp += HIW "【死亡保护】  " NOR + sprintf("%-43s",
#endif
                      (!query("combat/WPK", ob) && !query("no_newbie", ob) && (query("newbie", ob) ||
                      query("combat_exp", ob)<20000000))?HIY"保护中"NOR:
                      HIY "无保护" NOR);

                sp += HIW "【杀戮保护】  " NOR + sprintf("%s",
                      (query("die_protect/last_dead", me)+query("die_protect/duration", me)<time())?HIY"无保护\n"NOR:
                      HIY "保护中\n" NOR);

                sp += HIC "≡" HIY "----------------------------------------------"
                      "------------------------" HIC "≡\n" NOR;
                tell_object(me, sp);
                return 1;
        }

        if (arg && (arg == "-g"
           || sscanf(arg, "-g %s", arg)
           || sscanf(arg, "%s -g", arg)))
        {
                if (arg == "-g")
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");
                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");

                my = ob->query_entire_dbase();

                if (userp(ob) && (! stringp(my["born"]) || ! my["born"]))
                        return notify_fail("还没有出生呐，察看什么？\n");

                if (my["max_jing"] < 1 || my["max_qi"] < 1)
                        return notify_fail("无法察看" + ob->name(1) + "的状态。\n");

                sp = (ob == me ? "你" : ob->name()) + "目前的天赋属性如下：\n";
                sp += HIC "≡" HIY "----------------------------------------------"
                      "------------------------" HIC "≡\n" NOR;
                sp += HIY "【 种 类 】 " HIC "『初始』 『先天』 『成功』 『失败』"
                      " 『故事』 『经脉』 『元神』\n" NOR;
                sp += HIC "≡" HIY "----------------------------------------------"
                      "------------------------" HIC "≡\n" NOR;

                sp += sprintf(HIW "【 膂 力 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]    [" HIY "%3d" NOR + WHT "]\n",
                query("str", ob)-query("gift/str/succeed", ob)-query("gift/sun", ob)-query("jm/str", ob)-query("ys/str", ob),
                query("str", ob),
                query("gift/str/succeed", ob),
                query("gift/str/fail", ob),
                query("gift/sun", ob),
                query("jm/str", ob),
                query("ys/str", ob));

                sp += sprintf(HIW "【 悟 性 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]    [" HIY "%3d" NOR + WHT "]\n",
                query("int", ob)-query("gift/int/succeed", ob)-query("gift/water", ob)-query("jm/int", ob)-query("ys/int", ob),
                query("int", ob),
                query("gift/int/succeed", ob),
                query("gift/int/fail", ob),
                query("gift/water", ob),
                query("jm/int", ob),
                query("ys/int", ob));

                sp += sprintf(HIW "【 根 骨 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]    [" HIY "%3d" NOR + WHT "]\n",
                query("con", ob)-query("gift/con/succeed", ob)-query("gift/lighting", ob)-query("jm/con", ob)-query("ys/con", ob),
                query("con", ob),
                query("gift/con/succeed", ob),
                query("gift/con/fail", ob),
                query("gift/lighting", ob),
                query("jm/con", ob),
                query("ys/con", ob));

                sp += sprintf(HIW "【 身 法 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]    [" HIY "%3d" NOR + WHT "]\n",
                query("dex", ob)-query("gift/dex/succeed", ob)-query("gift/feng", ob)-query("jm/dex", ob)-query("ys/dex", ob),
                query("dex", ob),
                query("gift/dex/succeed", ob),
                query("gift/dex/fail", ob),
                query("gift/feng", ob),
                query("jm/dex", ob),
                query("ys/dex", ob));

                sp += sprintf(HIW "【 容 貌 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]    [" HIY "%3d" NOR + WHT "]\n",
                query("per", ob)-query("gift/per/succeed", ob)-query("gift/pergive", ob)-query("jm/per", ob)-query("ys/per", ob),
                query("per", ob),
                query("gift/per/succeed", ob),
                query("gift/per/fail", ob),
                query("gift/pergive", ob),
                query("jm/per", ob),
                query("ys/per", ob));

                sp += sprintf(HIW "【 福 缘 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]    [" HIY "%3d" NOR + WHT "]\n",
                query("kar", ob)-query("gift/kar/succeed", ob)-query("gift/kargive", ob)-query("jm/kar", ob)-query("ys/kar", ob),
                query("kar", ob),
                query("gift/kar/succeed", ob),
                query("gift/kar/fail", ob),
                query("gift/kargive", ob),
                query("jm/kar", ob),
                query("ys/kar", ob));

                sp += HIC "≡" HIY "----------------------------------------------"
                      "------------------------" HIC "≡\n" NOR;
                sp += sprintf( YEL " 般 若 掌： %s" NOR YEL "   无 常 杖： %s" NOR YEL "   金 刚 拳： %s\n" NOR,
                        query("sl_gift/yzc", ob)?HIY"○":HIC"×",query("sl_gift/zg", ob)?HIY"○":HIC"×",query("sl_gift/str", ob)?HIY"○":HIC"×");
                sp += sprintf( YEL " 一 指 禅： %s" NOR YEL "   火 焰 刀： %s" NOR YEL "   禅宗心法： %s\n" NOR,
                        query("sl_gift/con", ob)?HIY"○":HIC"×",query("sl_gift/huoyandao", ob)?HIY"○":HIC"×",query("sl_gift/int", ob)?HIY"○":HIC"×");
                sp += sprintf( YEL " 桃花密阵： %s" NOR YEL "   一灯疗伤： %s" NOR YEL " 大乘涅磐功： %s\n" NOR,
                        query("taohua_maze", ob)?HIY"○":HIC"×",query("dali/yideng_rewarded", ob)?HIY"○":HIC"×",query("sl_gift/mhyn", ob)?HIY"○":HIC"×");
                sp += sprintf( YEL " 天赋重置： "NOR+HIC"%s\n" NOR, chinese_number(query("gift/washed", ob)) );
                tell_object(me, sp);
                return 1;
        }

        if (! arg)
                ob = me;
        else
        if( wizardp(me) || query("couple/child_id", me) || query("private_room", me) )
        {
                ob = present(arg, environment(me));
                if (! ob || (! ob->is_character() && ! ob->is_owner(me))) ob = find_player(arg);
                if (! ob || (! ob->is_character() && ! ob->is_owner(me))) ob = find_living(arg);
                if (! ob || (! ob->is_character() && ! ob->is_owner(me)) || ! me->visible(ob))
                        return notify_fail("你要察看谁的状态？\n");

                if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) &&
                    ! ob->is_owner(me))
                        return notify_fail("你要察看谁的状态？\n");
        } else
                return notify_fail("只有巫师能察看别人的状态。\n");

        my = ob->query_entire_dbase();

        if (userp(ob) && (! stringp(my["born"]) || ! my["born"]))
                return notify_fail("还没有出生呐，察看什么？\n");

        if (my["max_jing"] < 1 || my["max_qi"] < 1)
                return notify_fail("无法察看" + ob->name(1) + "的状态。\n");

        sp = (ob == me ? "你" : ob->name()) + "目前的状态属性如下：\n";
        sp += HIC "≡" HIY "----------------------------------------------------------------------" HIC "≡\n" NOR;

        sp += sprintf(HIC "【 精 气 】 %s%8d/ %8d %s(%3d%%)"
                      HIC "    【 精 力 】 %s%8d / %8d (+%d)\n",
                status_color(my["jing"], my["eff_jing"]), my["jing"], my["eff_jing"],
                status_color(my["eff_jing"], my["max_jing"]),
                             my["eff_jing"] * 100 / my["max_jing"],
                status_color(my["jingli"], my["max_jingli"]), my["jingli"],
                             my["max_jingli"], my["jiajing"] );

        sp += sprintf(HIC "【 气 血 】 %s%8d/ %8d %s(%3d%%)"
                      HIC "    【 内 力 】 %s%8d / %8d (+%d)\n",
                status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
                status_color(my["eff_qi"], my["max_qi"]),
                             my["eff_qi"] * 100 / my["max_qi"],
                status_color(my["neili"], my["max_neili"]), my["neili"],
                             my["max_neili"], my["jiali"] );

        sp += sprintf(HIW "【 食 物 】 %s%8d/ %8d      " HIW "     【 潜 能 】  %s%d\n",
                status_color(my["food"], ob->max_food_capacity()),
                my["food"], ob->max_food_capacity(),
                query("potential", ob) >= ob->query_potential_limit()?HIM:HIY,
                query("potential", ob)-query("learned_points", ob));

        sp += sprintf(HIW "【 饮 水 】 %s%8d/ %8d      " HIW "     【 体 会 】  %s%d\n",
                status_color(my["water"], ob->max_water_capacity()),
                my["water"], ob->max_water_capacity(),
                my["experience"] >= ob->query_experience_limit() ? HIM : HIY,
                my["experience"] - my["learned_experience"]);

        if (craze = me->query_craze())
        {
                if (me->is_most_craze())
                        sp += HIR "【 愤 " BLINK "怒" NOR HIR " 】  " +
                              sprintf("%-22s",query("character", me) == "光明磊落"?
                                               "竖发冲冠" : "怒火中烧");
                else
                        sp += sprintf(HIR "【 愤 怒 】 %8d/ %8d (+%-3d)    ",
                                      craze, me->query_max_craze(),
                                      query("jianu", me));
        } else
        {
                sp += HIC "【 平 和 】  ------------------------    ";
        }
        sp += sprintf(HIW "【 经 验 】  " HIC "%d\n", my["combat_exp"]);
        sp += HIC "≡" HIY "----------------------------------------------------------------------" HIC "≡\n" NOR;
        tell_object(me, sp);
        return 1;
}

string status_color(int current, int max)
{
        int percent;

        if (max > 0)
                percent = current * 100 / max;
        else
                percent = 100;

        if (percent > 100) return HIC;
        if (percent >= 90) return HIG;
        if (percent >= 60) return HIY;
        if (percent >= 30) return YEL;
        if (percent >= 10) return HIR;
        return RED;
}

int help(object me)
{
        write(@HELP
指令格式：hp [-m] [-g]
          hp [-m] [-g] <对象名称>               （巫师专用）

这个指令可以显示你或指定对象的精气内力等数值。如果添加 -m 参
数则更详细的列出各种数值的最大有效果值。如果添加 -g 参数则会
详细的列出你的天赋属性状态。其中『原始』指你在投胎或转世重生
后本身所具备的原始值。『先天』则是指该项先天属性的总值，这项
属性可以通过吃丹或是激发故事以获得提升。而『成功』和『失败』
是指你所吃增加先天属性类仙丹的效果。『故事』是指你是否曾在游
戏中通过某些故事提升过相应的先天属性。最后的『转世』则表示你
是否通过了转世这个途径来增加了后天属性。

相关指令：score
HELP);
        return 1;
}
