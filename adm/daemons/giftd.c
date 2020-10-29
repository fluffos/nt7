
// giftd.c

#include <ansi.h>
#include <quest.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

// 定义提供给外部调用的接口函数
varargs public void bonus(object who, mapping b, int flag);
varargs public void freequest_bonus(object who);
varargs public void gift_bonus(object who, mapping b);
varargs public void work_bonus(object who, mapping b);
varargs public void war_bonus(object who, mapping b);
varargs public void battle_bonus(object who, mapping b);
public void delay_bonus(object who, mapping b);
public void delay_freequest_bonus(object who);
public void delay_gift_bonus(object who, mapping b);
public void delay_work_bonus(object who, mapping b);
public void delay_war_bonus(object who, mapping b);
public void delay_battle_bonus(object who, mapping b);

void create()
{
        seteuid(getuid());
        set("channel_id", "奖励精灵");
}

// override set function
varargs mixed set(string idx, mixed para, object who)
{
        int i, n, s, now_lvl, old_lvl;
        mapping spc_data, my;
        string skill, *files;
        // string *spe_skill = ({
        //         "monster", "nopoison", "demon", "ghost", "wisdom", "stealth",
        // });
        string *reborn_skill = ({
                "sophistry", "capture", "kingkong", "immortal", "musha",
                "recover", "astral",
        });

        if( idx == "combat_exp" )
        {
                if( para > query("combat_exp", who) )
                {
                        old_lvl = query("level", who);
                        if( !old_lvl || old_lvl < 1 ) old_lvl = 1;

                        // 等级封印
                        if( !UPDATE_D->can_improve_level(old_lvl) &&
                            para > to_int(pow(old_lvl, 3.0)*10000) )
                        {
                                //tell_object(ob, HIR "由于你处于等级封印中，你的实战经验无法提升！\n" NOR);
                                return;
                        }

                        for (i = old_lvl; ;i++)
                        {
                                if( to_int(pow(i+1, 3)) > (para / 10000) )
                                {
                                        now_lvl = i;
                                        break;
                                }
                        }

                        if( now_lvl > old_lvl )
                        {
                                n = now_lvl - old_lvl;
                                who->set_db("level", now_lvl);

                                if( now_lvl >= 100 && who->query_skillo("martial-cognize", 1) >= 4500 &&
                                    query("animaout", who) && !query("yuanshen_level", who) )
                                {
                                        addn("energy", 1, who);
                                        set("yuanshen_level", 1, who);
                                        set("yuanshen/attack", 100, who);
                                        set("yuanshen/defense", 100, who);
                                        tell_object(who, HIR "你冲破了瓶颈，元婴成长为元神，你可以修炼元神了！\n");
                                }

                                addn("ability", 4 * n, who);
                                addn("experience", 20 * n, who);
                                addn("potential", 200 * n, who);
                                addn("magic_points", 20 * n, who);

                                tell_object(who, HIY "只见一道红光飞进你的体内，你的人物等级提升了！\n" +
                                        "此次升级，你获得了" + chinese_number(4 * n) +
                                        "点能力点、" + chinese_number(200 * n) +
                                        "点潜能、" + chinese_number(20 * n) +
                                        "点实战体会、" + chinese_number(20 * n) +
                                        "点灵慧！\n" NOR);

                                //UPDATE_D->improve_valid_level(who, now_lvl);
                        }
                }
        } else
        if( idx == "yuanshen_exp" )
        {
                if( para > query("yuanshen_exp", who) )
                {
                        old_lvl = query("yuanshen_level", who);
                        if( !old_lvl || old_lvl < 1 ) old_lvl = 1;

                        for (i = old_lvl; ;i++)
                        {
                                if( to_int(pow(i+1, 3)) > (para / 10000) )
                                {
                                        now_lvl = i;
                                        break;
                                }
                        }

                        if( now_lvl > old_lvl )
                        {
                                n = (now_lvl - old_lvl)*10;
                                who->set_db("yuanshen_level", now_lvl);

                                addn("yuanshen/attack", n, who);
                                addn("yuanshen/defense", n, who);

                                //addn("yuanshen/damage", n, who);
                                //addn("yuanshen/armor", n, who);

                                tell_object(who, HIY "只见一道红光飞进你的体内，你的元神等级提升了！\n" NOR);

                                if( now_lvl % 10 == 0 )
                                {
                                        message_vision(HIY "突然天空出现一道玄光与$N" HIY "身泛起的红光相接，$N" HIY "全体通红！\n" NOR, who);
                                        n = now_lvl / 10;
                                        s = old_lvl / 10;
                                        for( i=s+1;i<=n;i++ ) {
                                        switch( i )
                                        {
                                        //case 0 : tell_object(who, HIY "你的元神等级提升到真元境界！\n" NOR);break;
                                        case 1 : addn("energy", 1, who);tell_object(who, HIY "你的元神等级提升到引魂境界！\n" NOR);break;
                                        case 2 : addn("energy", 2, who);tell_object(who, HIY "你的元神等级提升到元罡境界！\n" NOR);break;
                                        case 3 :
                                                 addn("energy", 2, who);
                                                 addn("int", 2, who);
                                                 addn("str", 2, who);
                                                 addn("con", 2, who);
                                                 addn("dex", 2, who);
                                                 addn("ys/int", 2, who);
                                                 addn("ys/str", 2, who);
                                                 addn("ys/con", 2, who);
                                                 addn("ys/dex", 2, who);
                                                 tell_object(who, HIY "你的元神等级提升到阴阳境界！\n" NOR);
                                                 tell_object(who, HIR "你的各项先天天赋都提高了２点！\n" NOR);
                                                 break;
                                        case 4 : addn("energy", 3, who);tell_object(who, HIY "你的元神等级提升到神丹境界！\n" NOR);break;
                                        case 5 : addn("energy", 3, who);tell_object(who, HIY "你的元神等级提升到神婴境界！\n" NOR);break;
                                        case 6 :
                                                 addn("energy", 4, who);
                                                 set("yuanshen/avoid_weak", 10, who);
                                                 set("yuanshen/research_effect", 100, who);
                                                 tell_object(who, HIY "你的元神等级提升到神通境界！\n" NOR);
                                                 tell_object(who, HIY "你抵抗虚弱的能力提高了１０点！\n" NOR);
                                                 tell_object(who, HIY "你对武功的研究效率提高了１００％！\n" NOR);
                                                 break;
                                        case 7 : addn("energy", 4, who);tell_object(who, HIY "你的元神等级提升到渡虚境界！\n" NOR);break;
                                        case 8 : addn("energy", 5, who);tell_object(who, HIY "你的元神等级提升到神劫境界！\n" NOR);break;
                                        case 9 :
                                                 addn("energy", 5, who);
                                                 set("yuanshen/immortal", 5, who);
                                                 //set("yuanshen/reduce_damage", 50, who);
                                                 tell_object(who, HIY "你的元神等级提升到不灭境界！\n" NOR);
                                                 tell_object(who, HIY "你的元神终于修炼成盘古真身神功！\n" NOR);

                                                 my = who->query_entire_dbase();
                                                 spc_data = ([ "hermit" : 1 ]);
                                                 /*
                                                 skill = spe_skill[random(sizeof(spe_skill))];
                                                 spc_data += ([ skill : 1 ]);
                                                 */
                                                 files = reborn_skill;
                                                 files -= keys(my["special_skill"]); // 去除转世技能重叠的bug
                                                 if( sizeof(files) > 0 )
                                                 {
                                                        skill = files[random(sizeof(files))];
                                                        spc_data += ([ skill : 1 ]);
                                                        files -= ({ skill });

                                                        if( sizeof(files) > 0 && random(10) == 1 ) {
                                                                skill = files[random(sizeof(files))];
                                                                spc_data += ([ skill : 1 ]);
                                                        }
                                                 }
                                                 my["special_skill"] += spc_data;
                                                 tell_object(who, HIY "由于元神修炼到不灭境界，你成功的激活了血脉力量及先天技能！\n" NOR);
                                                 break;
                                        default:
                                                 addn("yuanshen/immortal", 1, who);
                                                 tell_object(who, HIY "你的盘古真身神功触发几率提升了１点！\n" NOR);
                                                 break;
                                        }
                                    }
                                }
                        }
                }
        }
        return who->set_db(idx, para);
}

varargs mixed add(string prop, mixed data, object who)
{
        // string para;
        int old;
        int level;

        if( prop == "combat_exp" )
        {
                if( !(old = query(prop, who)) )
                        return set(prop, data, who);

                if( data < 1 )
                        return who->set_db(prop, old + data);

                level = query("level", who);
                if( !level || level < 1 ) level = 1;
                if( !UPDATE_D->can_improve_level(level) &&
                    old > to_int(pow(level, 3.0)*10000) )
                        return;

                return set(prop, old + data, who);
        } else
        if( prop == "yuanshen_exp" )
        {
                if( !(old = query(prop, who)) )
                        return set(prop, data, who);

                if( data < 1 )
                        return who->set_db(prop, old + data);

                return set(prop, old + data, who);
        } else
                return addn(prop, data, who);
}

// 延迟奖励：因为有时给出奖励的时候应该是在某些事件发生以后，
// 但是在该事件发生时给与奖励更易于书写程序，所以奖励生成的
// 地方在事件正在发生的时候，但是要让玩家看起来是在事件发生
// 以后。比如杀人，人死亡的时候给与奖励是容易做的，但是我希
// 望玩家在看到NPC 的死亡信息以后才看到奖励的信息，这时候就
// 用delay_bonus了。

public void delay_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "bonus", who, b :), 1);
}

public void delay_work_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "work_bonus", who, b :), 1);
}

public void delay_freequest_bonus(object who)
{
        who->start_call_out((: call_other, __FILE__,
                               "freequest_bonus", who :), 3);
}

public void delay_gift_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "gift_bonus", who, b :), 1);
}

public void delay_war_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "war_bonus", who, b :), 1);
}

public void delay_battle_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "battle_bonus", who, b :), 1);
}
public void delay_fuben_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "fuben_bonus", who, b :), 1);
}

public void delay_boss_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "boss_bonus", who, b :), 1);
}

void special_bonus(object me, object who, mixed arg)
{
        // 随机奖励
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/xuantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
                "/clone/gift/jinkuai",
                "/clone/tessera/qinglong",
                "/clone/tessera/baihu",
                "/clone/tessera/zhuque",
                "/clone/tessera/xuanwu",
                "/clone/tessera/qiling",
                "/clone/tessera/mcrystal",
        });

        object ob;

        /*
        message_vision("$n对$N微微一笑，道：干得不赖，辛苦"
                       "了，正好我这里有点东西，你就拿去吧。\n",
                       who, me);
        */

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(who, 1);
        tell_object(who, HIM "你获得了一" + query("unit", ob) + ob->name() +
                        HIM "。\n" NOR);
}

// 门派任务的奖励
varargs public void bonus(object who, mapping b, int flag)
{
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        int shen;               // 奖励的神
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int gongxian;           // 奖励的门派贡献
        int gold;
        int pot_limit;          // 潜能的界限
        int mar_limit;          // 实战体会的界限
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int reborn;
        int quest_times = "/adm/daemons/actiond"->query_action("quest_reward");
        int yuanshen_level;
        int vip_level;

        //蛊虫
        if (who->is_worm2())
                who = who->owner();

        // 获得奖励的百分比
        percent = b["percent"];
        if( percent < 1 )
                percent = 100;

        if( reborn = query("reborn/times", who) ) percent /= 2;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家经验太高，削弱奖励。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        vip_level = who->query_viplevel();
        if( vip_level < 6 )
        {
        }
        else if( vip_level < 7 )
        {
                exp += exp * 30 / 100;
                pot += exp * 30 / 100;
        }
        else
        {
                exp += exp * 50 / 100;
                pot += exp * 50 / 100;
        }

        /*
        if( quest_times=query_temp("apply/add_reward", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_pot", who) && reborn < 3 )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) && reborn < 3 )
                mar += mar*random(quest_times)/100;
        */

        if( quest_times=who->query_all_buff("add_exp") )
        {
                exp += exp*quest_times/100;
        }

        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp")) )
                exp *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot")) )
                pot *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar")) )
                mar *= 2;

        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // 魔幻兽
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        // 元神
        if( exp > 100 && (yuanshen_level = query("yuanshen_level", who)) && yuanshen_level < 100 )
        {
                /*if( yuanshen_level > 50 )
                        yuanshen_exp = exp * 30 / 100;
                else*/ if( yuanshen_level > 40 )
                        yuanshen_exp = exp * 25 / 100;
                else if( yuanshen_level > 30 )
                        yuanshen_exp = exp * 20 / 100;
                else if( yuanshen_level > 20 )
                        yuanshen_exp = exp * 15 / 100;
                else if( yuanshen_level > 10 )
                        yuanshen_exp = exp * 10 / 100;
                else
                        yuanshen_exp = exp * 5 / 100;

                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你获得了";
        else
                msg = HIG "通过这次锻炼，你获得了";

        if (exp > 0) msg += chinese_number(exp) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if (shen > 0) msg += chinese_number(shen) + "点正神、";
        if (shen < 0) msg += chinese_number(-shen) + "点负神、";
        if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "点威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "点门派功绩、";
        if (gold > 0) msg += chinese_number(gold) + "两黄金、";

        if( ob )
        {
                msg += ob->name() + "获得经验" + chinese_number(warcraft_exp) + "点、";
        }

        if( yuanshen_level )
        {
                msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// 普通工作任务的奖励
varargs public void work_bonus(object who, mapping b, int flag, string type/*任务类型,为活动精灵预留接口*/)
{
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        int shen;               // 奖励的神
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int gongxian;           // 奖励的门派贡献
        int gold;
        // int pot_limit;          // 潜能的界限
        // int mar_limit;          // 实战体会的界限
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int reborn;
        int quest_times = "/adm/daemons/actiond"->query_action("work_reward");
        int yuanshen_level;
        int vip_level;

        //蛊虫
        if (who->is_worm2())
                who = who->owner();

        // 获得奖励的百分比
        percent = b["percent"];
        if( percent < 1 )
                percent = 100;

        if( reborn = query("reborn/times", who) ) percent /= 2;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家经验太高，削弱奖励。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        vip_level = who->query_viplevel();
        if( vip_level < 6 )
        {
        }
        else if( vip_level < 7 )
        {
                exp += exp * 30 / 100;
                pot += exp * 30 / 100;
        }
        else
        {
                exp += exp * 50 / 100;
                pot += exp * 50 / 100;
        }

        /*
        if( quest_times=query_temp("apply/add_reward", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_pot", who) && reborn < 3 )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) && reborn < 3 )
                mar += mar*random(quest_times)/100;
        */
        if( quest_times=who->query_all_buff("add_exp") )
        {
                exp += exp*quest_times/100;
        }

        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp")) )
                exp *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot")) )
                pot *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar")) )
                mar *= 2;

        /*
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }
        */

        // 魔幻兽
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 100 && (yuanshen_level = query("yuanshen_level", who)) && yuanshen_level < 100 )
        {
                /*if( yuanshen_level > 50 )
                        yuanshen_exp = exp * 30 / 100;
                else*/ if( yuanshen_level > 40 )
                        yuanshen_exp = exp * 25 / 100;
                else if( yuanshen_level > 30 )
                        yuanshen_exp = exp * 20 / 100;
                else if( yuanshen_level > 20 )
                        yuanshen_exp = exp * 15 / 100;
                else if( yuanshen_level > 10 )
                        yuanshen_exp = exp * 10 / 100;
                else
                        yuanshen_exp = exp * 5 / 100;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIC "\n" + msg + HIC "，你获得了";
        else
                msg = HIC "\n通过这次锻炼，你获得了";

        if (exp > 0) msg += chinese_number(exp) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if (shen > 0) msg += chinese_number(shen) + "点正神、";
        if (shen < 0) msg += chinese_number(-shen) + "点负神、";
        if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "点威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "点门派功绩、";
        if (gold > 0) msg += chinese_number(gold) + "两黄金、";

        if( ob )
        {
                msg += ob->name() + "获得经验" + chinese_number(warcraft_exp) + "点、";
        }

        if( yuanshen_level )
        {
                msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点、";
        }

        msg += "能力得到了提升。\n\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// 中断性质自由任务的奖励
varargs public void freequest_bonus(object who)
{
        object gift;
        int quest;              // 当前任务数量
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        string msg;             // 奖励的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int reborn;
        int quest_times = "/adm/daemons/actiond"->query_action("quest_reward");
        int yuanshen_level;
        int vip_level;

        //蛊虫
        if (who->is_worm2())
                who = who->owner();

        reborn = query("reborn/times", who);

        quest=query("quest_count", who);
        quest *= 20;
        exp = quest + random(quest) + 5000;

        // 因为获得奖励较多且无法累及中断任务，所以暂时不做
        // 上限的限制。
        pot = exp / 3;
        mar = random(quest / 2) + 500;

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( query("special_skill/tianshen", who) )
        {
                exp = exp + exp / 10;
                pot = pot + pot / 10;
                mar = mar + mar / 10;
        }

        vip_level = who->query_viplevel();
        if( vip_level < 6 )
        {
        }
        else if( vip_level < 7 )
        {
                exp += exp * 30 / 100;
                pot += exp * 30 / 100;
        }
        else
        {
                exp += exp * 50 / 100;
                pot += exp * 50 / 100;
        }

        /*
        if( quest_times=query_temp("apply/add_reward", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_pot", who) && reborn < 3 )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) && reborn < 3 )
                mar += mar*random(quest_times)/100;
        */
        if( quest_times=who->query_all_buff("add_exp") )
        {
                exp += exp*quest_times/100;
        }

        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp")) )
                exp *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot")) )
                pot *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar")) )
                mar *= 2;

        // 魔幻兽
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 100 && (yuanshen_level = query("yuanshen_level", who)) && yuanshen_level < 100 )
        {
                /*if( yuanshen_level > 50 )
                        yuanshen_exp = exp * 30 / 100;
                else*/ if( yuanshen_level > 40 )
                        yuanshen_exp = exp * 25 / 100;
                else if( yuanshen_level > 30 )
                        yuanshen_exp = exp * 20 / 100;
                else if( yuanshen_level > 20 )
                        yuanshen_exp = exp * 15 / 100;
                else if( yuanshen_level > 10 )
                        yuanshen_exp = exp * 10 / 100;
                else
                        yuanshen_exp = exp * 5 / 100;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        msg = HIC "\n你在这次的历练过程中，对武学似乎又"
              "有了新的突破。你获得了" +
              chinese_number(exp) + "点经验、" +
              chinese_number(pot) + "点潜能、" +
              chinese_number(mar) + "点实战体会、";

        if( ob )
        {
                msg += ob->name() + "获得经验" + chinese_number(warcraft_exp) + "点、";
        }

        if( yuanshen_level )
        {
                msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点。";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("quest/freequest", -1, who);

        if (query("quest/freequest", who) < 1)
        {
                delete("quest", who);
                message_sort(HIW "\n正在这时，只见一位" +
                             query("family/family_name", who)+
                             "弟子急急忙忙赶到$N" HIW "身边，说"
                             "道：“原来你在这里啊，师傅正到处派"
                             "人找你呢。听说有要紧事交给你办，你"
                             "赶快回去吧！这个包裹是师傅让我转交"
                             "给你的。”\n" NOR, who);

                message_sort("\n"+query("family/family_name", who)+
                             "弟子拿出一个包裹递给$N。\n\n" +
                             query("family/family_name", who)+
                             "弟子急急忙忙地离开了。\n" NOR, who);

                gift = new("/clone/misc/bag");
                gift->move(who, 1);
        }
}

// 特殊事件的奖励
varargs public void gift_bonus(object who, mapping b)
{
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int gongxian;           // 奖励的门派贡献
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息
        string temp;            // 进程记录信息
        int quest_times;
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int reborn;
        int yuanshen_level;
        int vip_level;

        //蛊虫
        if (who->is_worm2())
                who = who->owner();

        // 获得奖励的百分比
        percent = b["percent"];

        if( percent < 1 )
                percent = 100;

        if( reborn = query("reborn/times", who) ) percent /= 2;

        // 进程记录，针对第一次完成有奖励的情节
        temp = b["temp"];

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        vip_level = who->query_viplevel();
        if( vip_level < 6 )
        {
        }
        else if( vip_level < 7 )
        {
                exp += exp * 30 / 100;
                pot += exp * 30 / 100;
        }
        else
        {
                exp += exp * 50 / 100;
                pot += exp * 50 / 100;
        }

        /*
        if( quest_times=query_temp("apply/add_reward", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_pot", who) && reborn < 3 )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) && reborn < 3 )
                mar += mar*random(quest_times)/100;
        */
        if( quest_times=who->query_all_buff("add_exp") )
        {
                exp += exp*quest_times/100;
        }

        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp")) )
                exp *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot")) )
                pot *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar")) )
                mar *= 2;

       // 魔幻兽
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 100 && (yuanshen_level = query("yuanshen_level", who)) && yuanshen_level < 100 )
        {
                /*if( yuanshen_level > 50 )
                        yuanshen_exp = exp * 30 / 100;
                else*/ if( yuanshen_level > 40 )
                        yuanshen_exp = exp * 25 / 100;
                else if( yuanshen_level > 30 )
                        yuanshen_exp = exp * 20 / 100;
                else if( yuanshen_level > 20 )
                        yuanshen_exp = exp * 15 / 100;
                else if( yuanshen_level > 10 )
                        yuanshen_exp = exp * 10 / 100;
                else
                        yuanshen_exp = exp * 5 / 100;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成谣言信息
        if (stringp(msg = b["rumor"]))
        {
                shout(HIR "【武林传闻】" NOR + WHT "听说" +
                      who->name()+WHT"["+query("id", who)+
                      WHT "]" + msg + WHT "。\n" NOR);
        }

        if( !stringp(temp) || !query(temp, who) )
        {
                // 生成提示信息
                if (stringp(msg = b["prompt"]))
                        msg = HIW "\n" + msg + HIW "，你获得了";
                else
                        msg = HIW "\n通过此次经历，你获得了";

                // 记录下进程
                if (stringp(temp))
                        addn(temp, 1, who);

                if (exp > 0) msg += chinese_number(exp) + "点经验、";
                if (pot > 0) msg += chinese_number(pot) + "点潜能、";
                if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
                if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
                if (weiwang > 0) msg += chinese_number(weiwang) + "点江湖威望、";
                if (gongxian > 0) msg += chinese_number(gongxian) + "点门派功绩、";

                if( ob )
                {
                        msg += ob->name() + "获得经验" + chinese_number(warcraft_exp) + "点、";
                }

                if( yuanshen_level )
                {
                        msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点、";
                }
                msg += "能力得到了提升。\n" NOR;
                tell_object(who, sort_msg(msg));

                // bonus
                add("combat_exp", exp, who);
                addn("potential", pot, who);
                addn("experience", mar, who);
                addn("score", score, who);
                addn("weiwang", weiwang, who);
                addn("family/gongji", gongxian, who);
        }
}

varargs public void war_bonus(object who, mapping b)
{
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        int shen;               // 奖励的神
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int gongxian;           // 奖励的门派贡献
        int gold;
        // int pot_limit;          // 潜能的界限
        // int mar_limit;          // 实战体会的界限
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int reborn;
        int quest_times = ACTION_D->query_action("battle_reward");
        int yuanshen_level;
        int vip_level;

        //蛊虫
        if (who->is_worm2())
                who = who->owner();

        // 获得奖励的百分比
        percent = b["percent"];
        if( percent < 1 )
                percent = 100;

        // 转世后奖励大幅度降低，转世奖励高是为了新人适应这里
        if( reborn = query("reborn/times", who) ) percent /= 4;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家经验太高，削弱奖励。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        vip_level = who->query_viplevel();
        if( vip_level < 6 )
        {
        }
        else if( vip_level < 7 )
        {
                exp += exp * 30 / 100;
                pot += exp * 30 / 100;
        }
        else
        {
                exp += exp * 50 / 100;
                pot += exp * 50 / 100;
        }

        /*
        if( quest_times=query_temp("apply/add_reward", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_pot", who) && reborn < 3 )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) && reborn < 3 )
                mar += mar*random(quest_times)/100;
        */
        if( quest_times=who->query_all_buff("add_exp") )
        {
                exp += exp*quest_times/100;
        }

        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp")) )
                exp *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot")) )
                pot *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar")) )
                mar *= 2;

        // 魔幻兽
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 100 && (yuanshen_level = query("yuanshen_level", who)) && yuanshen_level < 100 )
        {
                /*if( yuanshen_level > 50 )
                        yuanshen_exp = exp * 30 / 100;
                else*/ if( yuanshen_level > 40 )
                        yuanshen_exp = exp * 25 / 100;
                else if( yuanshen_level > 30 )
                        yuanshen_exp = exp * 20 / 100;
                else if( yuanshen_level > 20 )
                        yuanshen_exp = exp * 15 / 100;
                else if( yuanshen_level > 10 )
                        yuanshen_exp = exp * 10 / 100;
                else
                        yuanshen_exp = exp * 5 / 100;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你获得了";
        else
                msg = HIG "通过这次锻炼，你获得了";

        if (exp > 0) msg += chinese_number(exp) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if (shen > 0) msg += chinese_number(shen) + "点正神、";
        if (shen < 0) msg += chinese_number(-shen) + "点负神、";
        if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "点威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "点门派功绩、";
        if (gold > 0) msg += chinese_number(gold) + "两黄金、";

        if( ob )
        {
                msg += ob->name() + "获得经验" + chinese_number(warcraft_exp) + "点、";
        }

        if( yuanshen_level )
        {
                msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// BOSS任务的奖励
varargs public void boss_bonus(object who, mapping b, int flag)
{
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        int shen;               // 奖励的神
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int gongxian;           // 奖励的门派贡献
        int gold;
        int pot_limit;          // 潜能的界限
        int mar_limit;          // 实战体会的界限
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int reborn;
        int quest_times = "/adm/daemons/actiond"->query_action("boss_reward");
        int yuanshen_level;
        int vip_level;

        //蛊虫
        if (who->is_worm2())
                who = who->owner();

        // 获得奖励的百分比
        percent = b["percent"];
        if( percent < 1 )
                percent = 100;

        if( reborn = query("reborn/times", who) ) percent /= 2;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;
        if( !gold || gold < 50 ) gold = 50;

        // 玩家经验太高，削弱奖励。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }


        vip_level = who->query_viplevel();
        if( vip_level < 6 )
        {
        }
        else if( vip_level < 7 )
        {
                exp += exp * 30 / 100;
                pot += exp * 30 / 100;
        }
        else
        {
                exp += exp * 50 / 100;
                pot += exp * 50 / 100;
        }


        /*
        if( quest_times=query_temp("apply/add_reward", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_pot", who) && reborn < 3 )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) && reborn < 3 )
                mar += mar*random(quest_times)/100;
        */
        if( quest_times=who->query_all_buff("add_exp") )
        {
                exp += exp*quest_times/100;
        }

        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp")) )
                exp *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot")) )
                pot *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar")) )
                mar *= 2;

        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // 魔幻兽
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 100 && (yuanshen_level = query("yuanshen_level", who)) && yuanshen_level < 100 )
        {
                /*if( yuanshen_level > 50 )
                        yuanshen_exp = exp * 30 / 100;
                else*/ if( yuanshen_level > 40 )
                        yuanshen_exp = exp * 25 / 100;
                else if( yuanshen_level > 30 )
                        yuanshen_exp = exp * 20 / 100;
                else if( yuanshen_level > 20 )
                        yuanshen_exp = exp * 15 / 100;
                else if( yuanshen_level > 10 )
                        yuanshen_exp = exp * 10 / 100;
                else
                        yuanshen_exp = exp * 5 / 100;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你获得了";
        else
                msg = HIG "通过这次锻炼，你获得了";

        if (exp > 0) msg += chinese_number(exp) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if (shen > 0) msg += chinese_number(shen) + "点正神、";
        if (shen < 0) msg += chinese_number(-shen) + "点负神、";
        if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "点威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "点门派功绩、";
        if (gold > 0) msg += chinese_number(gold) + "两黄金、";

        if( ob )
        {
                msg += ob->name() + "获得经验" + chinese_number(warcraft_exp) + "点、";
        }

        if( yuanshen_level )
        {
                msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// 副本任务的奖励
varargs public void fuben_bonus(object who, mapping b, int flag)
{
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        int shen;               // 奖励的神
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int gongxian;           // 奖励的门派贡献
        int gold;
        int pot_limit;          // 潜能的界限
        int mar_limit;          // 实战体会的界限
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int reborn;
        int quest_times = "/adm/daemons/actiond"->query_action("fuben_reward");
        int yuanshen_level;
        int vip_level;

        //蛊虫
        if (who->is_worm2())
                who = who->owner();

        // 获得奖励的百分比
        percent = b["percent"];
        if( percent < 1 )
                percent = 100;

        if( reborn = query("reborn/times", who) ) percent /= 2;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家经验太高，削弱奖励。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        vip_level = who->query_viplevel();
        if( vip_level < 6 )
        {
        }
        else if( vip_level < 7 )
        {
                exp += exp * 30 / 100;
                pot += exp * 30 / 100;
        }
        else
        {
                exp += exp * 50 / 100;
                pot += exp * 50 / 100;
        }

        /*
        if( quest_times=query_temp("apply/add_reward", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_pot", who) && reborn < 3 )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) && reborn < 3 )
                mar += mar*random(quest_times)/100;
        */
        if( quest_times=who->query_all_buff("add_exp") )
        {
                exp += exp*quest_times/100;
        }

        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp")) )
                exp *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot")) )
                pot *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar")) )
                mar *= 2;

        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // 魔幻兽
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 100 && (yuanshen_level = query("yuanshen_level", who)) && yuanshen_level < 100 )
        {
                /*if( yuanshen_level > 50 )
                        yuanshen_exp = exp * 30 / 100;
                else*/ if( yuanshen_level > 40 )
                        yuanshen_exp = exp * 25 / 100;
                else if( yuanshen_level > 30 )
                        yuanshen_exp = exp * 20 / 100;
                else if( yuanshen_level > 20 )
                        yuanshen_exp = exp * 15 / 100;
                else if( yuanshen_level > 10 )
                        yuanshen_exp = exp * 10 / 100;
                else
                        yuanshen_exp = exp * 5 / 100;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你获得了";
        else
                msg = HIG "通过这次锻炼，你获得了";

        if (exp > 0) msg += chinese_number(exp) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if (shen > 0) msg += chinese_number(shen) + "点正神、";
        if (shen < 0) msg += chinese_number(-shen) + "点负神、";
        if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "点威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "点门派功绩、";
        if (gold > 0) msg += chinese_number(gold) + "两黄金、";

        if( ob )
        {
                msg += ob->name() + "获得经验" + chinese_number(warcraft_exp) + "点、";
        }

        if( yuanshen_level )
        {
                msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

varargs public void battle_bonus(object who, mapping b)
{
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        int shen;               // 奖励的神
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int gongxian;           // 奖励的门派贡献
        int gold;
        // int pot_limit;          // 潜能的界限
        // int mar_limit;          // 实战体会的界限
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int reborn;
        int quest_times = ACTION_D->query_action("battle_reward");
        int yuanshen_level;
        int vip_level;

        //蛊虫
        if (who->is_worm2())
                who = who->owner();

        // 获得奖励的百分比
        percent = b["percent"];
        if( percent < 1 )
                percent = 100;

        if( reborn = query("reborn/times", who) ) percent /= 2;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家经验太高，削弱奖励。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }


        vip_level = who->query_viplevel();
        if( vip_level < 6 )
        {
        }
        else if( vip_level < 7 )
        {
                exp += exp * 30 / 100;
                pot += exp * 30 / 100;
        }
        else
        {
                exp += exp * 50 / 100;
                pot += exp * 50 / 100;
        }

        /*
        if( quest_times=query_temp("apply/add_reward", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) && reborn < 3 )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_pot", who) && reborn < 3 )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) && reborn < 3 )
                mar += mar*random(quest_times)/100;
        */
        if( quest_times=who->query_all_buff("add_exp") )
        {
                exp += exp*quest_times/100;
        }

        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp")) )
                exp *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot")) )
                pot *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar")) )
                mar *= 2;

        // 魔幻兽
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 100 && (yuanshen_level = query("yuanshen_level", who)) && yuanshen_level < 100 )
        {
                /*if( yuanshen_level > 50 )
                        yuanshen_exp = exp * 30 / 100;
                else*/ if( yuanshen_level > 40 )
                        yuanshen_exp = exp * 25 / 100;
                else if( yuanshen_level > 30 )
                        yuanshen_exp = exp * 20 / 100;
                else if( yuanshen_level > 20 )
                        yuanshen_exp = exp * 15 / 100;
                else if( yuanshen_level > 10 )
                        yuanshen_exp = exp * 10 / 100;
                else
                        yuanshen_exp = exp * 5 / 100;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你获得了";
        else
                msg = HIG "通过这次锻炼，你获得了";

        if (exp > 0) msg += chinese_number(exp) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if (shen > 0) msg += chinese_number(shen) + "点正神、";
        if (shen < 0) msg += chinese_number(-shen) + "点负神、";
        if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "点威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "点门派功绩、";
        if (gold > 0) msg += chinese_number(gold) + "两黄金、";

        if( ob )
        {
                msg += ob->name() + "获得经验" + chinese_number(warcraft_exp) + "点、";
        }

        if( yuanshen_level )
        {
                msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// 活动的奖励
varargs public void event_bonus(object who, mapping b, int flag)
{
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        int shen;               // 奖励的神
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int gongxian;           // 奖励的门派贡献
        int gold;
        // int pot_limit;          // 潜能的界限
        // int mar_limit;          // 实战体会的界限
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int reborn;
        int quest_times;
        int event;
        int yuanshen_level;
        int vip_level;

        //蛊虫
        if (who->is_worm2())
                who = who->owner();

        // 获得奖励的百分比
        percent = b["percent"];
        if( percent < 1 )
                percent = 100;

        if( reborn = query("reborn/times", who) ) percent /= 2;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // 玩家经验太高，削弱奖励。
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif
        event = ACTION_D->query_action("event_reward");
        if (event)
        {
                exp *= event;
                pot *= event;
                mar *= event;
        }

        vip_level = who->query_viplevel();
        if( vip_level < 6 )
        {
        }
        else if( vip_level < 7 )
        {
                exp += exp * 30 / 100;
                pot += exp * 30 / 100;
        }
        else
        {
                exp += exp * 50 / 100;
                pot += exp * 50 / 100;
        }

        /*
        if( quest_times=query_temp("apply/add_reward", who) && reborn < 3 )
        {
                if( quest_times > 100 ) quest_times = 100;
                if( query("reborn/times", who) && !event ) quest_times /= 3;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) && reborn < 3 )
        {
                if( quest_times > 200 ) quest_times = 200;
                if( query("reborn/times", who) && !event ) quest_times /= 3;
                exp += exp*random(quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_pot", who) && reborn < 3 )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) && reborn < 3 )
                mar += mar*random(quest_times)/100;
        */
        if( quest_times=who->query_all_buff("add_exp") )
        {
                exp += exp*quest_times/100;
        }

        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp")) )
                exp *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot")) )
                pot *= 2;
        if( (who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar")) ||
            (who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar")) )
                mar *= 2;

        /*
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }
        */

        // 魔幻兽
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        // 元神
        if( exp > 100 && (yuanshen_level = query("yuanshen_level", who)) && yuanshen_level < 100 )
        {
                /*if( yuanshen_level > 50 )
                        yuanshen_exp = exp * 30 / 100;
                else*/ if( yuanshen_level > 40 )
                        yuanshen_exp = exp * 25 / 100;
                else if( yuanshen_level > 30 )
                        yuanshen_exp = exp * 20 / 100;
                else if( yuanshen_level > 20 )
                        yuanshen_exp = exp * 15 / 100;
                else if( yuanshen_level > 10 )
                        yuanshen_exp = exp * 10 / 100;
                else
                        yuanshen_exp = exp * 5 / 100;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你获得了";
        else
                msg = HIG "通过这次锻炼，你获得了";

        if (exp > 0) msg += chinese_number(exp) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if (shen > 0) msg += chinese_number(shen) + "点正神、";
        if (shen < 0) msg += chinese_number(-shen) + "点负神、";
        if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "点威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "点门派功绩、";
        if (gold > 0) msg += chinese_number(gold) + "两黄金、";

        if( ob )
        {
                msg += ob->name() + "获得经验" + chinese_number(warcraft_exp) + "点、";
        }

        if( yuanshen_level )
        {
                msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点、";
        }

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}
