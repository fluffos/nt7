// This program is a part of NT MudLIB
// research.c

#include <skill.h>
#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int *query_scale(string skill);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        string skill, skill_name;
        int jing_cost, times;
        int level, neili_cost, t1, t2, t3, t4;
        int is_force_skill;
        int is_parry_skill;
        int is_dodge_skill;
        int lvl;
        string *ks;
        int *ls, *scale;
        int improve;
        int diff;
        int i;
        int r;
        int c;
        int n;
        int t = time();
        int vip_level;

        if( !where ) return notify_fail("你周围环境出现问题，请联系巫师解决。\n");
        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if( t == query_temp("time/research", me) )
                return notify_fail("你刚刚才研究过（如果你要连续研究，可以指明"
                                   "研究的次数）。\n");

        if( query("no_fight", where) && query("doing", me) != "scheme" )
                return notify_fail("这里太纷杂，你没法作研究。\n");

        if (! arg)
                return notify_fail("research|yanjiu <技能> <次数>\n");

        if (sscanf(arg, "%s %d", skill, times) != 2)
        {
                skill = arg;
                times = 1;
        }

        c=200+me->query_all_buff("research_times");
        if( query("special_skill/clever", me) ) 
                c += 50;
        // 转世技能增加研究次数
        if( query("special_skill/wisdom", me) )
                c += 800;
        if( query("special_skill/musha", me) )
                c += c * 50 / 100;

        if( me->query_skill("huitong-tianxia", 1) > 500 )
                c += c * 20 / 100 + 10;

	// 奇筋异骨提高研究次数2倍
        if( query("special_skill/qijin", me) )
                c *= 2;

        if( objectp(where) && query("penglai", where) )
                c *= 2;

        if( objectp(where) && query("dongtianfudi", where) )//洞天福地
                c += query("dongtianfudi", where);

        if( n = ACTION_D->query_action("yanjiu_times") )
                c *= n;

        if (times < 1 || times > c)
                return notify_fail("研究次数最少一次，最多也不能超过" + chinese_number(c) + "次。\n");

        if (me->is_fighting())
                return notify_fail("临阵磨枪？来不及啦。\n");

        if (! (lvl = me->query_skill(skill, 1)))
                return notify_fail("这项技能你还不会，研究什么？\n");

        if ((string) SKILL_D(skill)->type() == "knowledge")
                return notify_fail(to_chinese(skill) + "只能靠你学习才能提高的。\n");

        if (lvl < 180)
                return notify_fail("你对" + to_chinese(skill) + "的掌握程度还"
                                   "未到研究的程度。\n");

        notify_fail("依你目前的能力，没有办法研究这种技能。\n");

        if (! SKILL_D(skill)->valid_learn(me)
           || ! SKILL_D(skill)->valid_research(me))
                // 不能学习或是不能研究
                return 0;

        if (! XUE_CMD->can_learn(me, skill))
                return 0;

        if( (query("potential", me)-query("learned_points", me))<times )
                return notify_fail("你的潜能不够研究这么多次了。\n");

        // Lookup skills for relation skills

        write(HIG "你开始研究" + chinese_number(times) + "次有关「" +
              to_chinese(skill) + HIG "」的奥秘。\n" NOR);
        message("vision", me->name() + "在冥神思索。\n", where, ({ me }));

        // calculate the basic effect
        is_force_skill = SKILL_D(skill)->valid_enable("force");
        is_parry_skill = SKILL_D(skill)->valid_enable("parry") && (! is_force_skill);
        is_dodge_skill = SKILL_D(skill)->valid_enable("dodge") && (! is_force_skill);

        ks = keys(me->query_skills());
        ls = ({ });

        for (i = 0; i < sizeof(ks); i++)
        {
                mapping action;
                int eff;

                if (ks[i] == skill)
                        continue;

                if (SKILL_D(ks[i])->main_skill()
                   && SKILL_D(ks[i])->main_skill() != ks[i])
                        continue;

                if (SKILL_D(skill)->valid_enable(ks[i]))
                        ls += ({ me->query_skill(ks[i], 1) });

                if (SKILL_D(ks[i])->valid_enable(skill)
                   || is_force_skill
                   && SKILL_D(ks[i])->valid_enable("force"))
                {
                        // Relation skill
                        action = SKILL_D(ks[i])->query_action(me, 0);
                        eff = (int)me->query_skill(ks[i], 1);

                        if (action)
                        {
                                // do more effect
                                eff += (action["force"] + action["damage"] +
                                        action["attack"] + action["parry"] +
                                        action["dodge"]) * eff / 1000;
                        }
                        ls += ({ eff });
                }
        }
        ls = sort_array(ls, -1);
        scale = query_scale(skill);
        improve = 0;

        for (i = 0; i < sizeof(ls) && i < sizeof(scale); i++)
        {
                if (lvl >= 10000) 
                        improve += ls[i] * scale[i] / 10; 
                else
                if (lvl >= 5000) 
                         improve += ls[i] * scale[i] / 8; 
                else
                if (lvl >= 3000)
                        improve += ls[i] * scale[i] / 6;
                else
                if (lvl >= 2000)
                        improve += ls[i] * scale[i] / 4;
                else
                if (lvl >= 1000)
                        improve += ls[i] * scale[i] / 2;
                else
                        improve += ls[i] * scale[i];
        }

        if (lvl >= 10000)
                improve+=lvl/250+query("int", me)/25;
        else
        if (lvl >= 5000)
                improve+=lvl/200+query("int", me)/20;
        else
        if (lvl >= 3000)
                improve+=lvl/150+query("int", me)/15;
        else
        if (lvl >= 2000)
                improve+=lvl/100+query("int", me)/10;
        else
        if (lvl >= 1000)
                improve+=lvl/75+query("int", me)/6;
        else
                improve+=lvl/50+query("int", me)/3;

        improve+=improve*query("research_improve", where)/100;
        // 喝过腊八粥就能提升研究的速度
        if( query("gift/labazhou", me) )
                improve += improve * (10 + random(5)) / 100;

        // 套装提升研究的速度
        if( intp(r=me->query_all_buff("research_effect")) )
        {
                if( r > 20000 ) r = 2000;
                r = r/2 + random(r/2);
                improve += improve * r / 100;
        }

        // 转世技能六阴鬼脉提升内功技能的研究速度
        if( query("special_skill/ghost", me) && SKILL_D(skill)->valid_enable("force") )
                improve += improve * 50 / 100;

        if( query("special_skill/wisdom", me) )
                improve += improve * 50 / 100;

        // 转世技能群邪辟易提升研究效果
        if( query("special_skill/nopoison", me) )
                improve += improve * 50 / 100;

        if( query("special_skill/musha", me) )
                improve += improve * 50 / 100;

        // 踏雪无痕提高轻功研究速度50%
        if( query("special_skill/taxue", me) && is_dodge_skill )
                improve += improve / 2;
        
        vip_level = me->query_viplevel();
        if( vip_level < 1 )
                ;
        else if( vip_level < 2 )
                improve += improve * 10 / 100;
        else if( vip_level < 3 )
                improve += improve * 30 / 100;
        else if( vip_level < 4 )
                improve += improve * 60 / 100;
        else if( vip_level < 5 )
                improve += improve;
        else if( vip_level < 6 )
                improve += improve * 150 / 100;
        else if( vip_level < 7 )
                improve += improve * 2;
        else
                improve += improve * 3;
        
        if( query("yuanshen_level", me) )
                improve += improve * query("yuanshen_level", me) / 100 / 2;

        if( query("time_reward/study", me) )
                improve += improve * 25 / 100;
        
        // 帮派荣誉点
        if( me->query_bunch() && BUNCH_D->query_bunch_efficient(me->query_bunch(), "yanjiu") )
                improve += improve * 20 / 100;

        if( me->query_family() && FAMILY_D->query_family_efficient(me->query_family(), "yanjiu") )
                improve += improve * 20 / 100;
                
        diff = SKILLS_D->query_skill_difficult(skill);
        if (! diff) diff = SKILL_D(skill)->difficult_level();
        improve = improve / 30 / (300 + diff);
        if (improve < 1) improve = 1;

        jing_cost=1000/query("int", me);

        if( query("eff_jing", me)<jing_cost )
                return notify_fail("你觉得你精力不济，实在没有办法进行研究。\n");

        if (! me->can_improve_skill(skill))
        {
                write("也许是缺乏实战经验，你感到难以继续研究" +
                      to_chinese(skill) + "的问题了。\n");
                return 1;
        }

        set_temp("time/research", t, me);

        t1=query("jing", me)/jing_cost;
        t2 = times - t1;
        if (t2 > 0)
        {
                level = me->query_skill("force");
                if (level <= 0) level = 1;

                neili_cost =  jing_cost * 60 / level;
                if( query("breakup", me) )
                        neili_cost = neili_cost * 7 / 10;

                if (neili_cost < 20) neili_cost = 20;

                if( query("neili", me) >= neili_cost*t2 )
                {
                        t4 = times;
                        addn("neili", -neili_cost*t2, me);
                }
                else
                {
                        t3=query("neili", me)/neili_cost;
                        t4 = t1 + t3;
                        if (t4 == 0)
                        {
                                write("你今天太累了，结果什么也没有研究成。\n");
                                return 1;
                        }

                        set("neili", 0, me);
                }
        } else
                t4 = times;

        if (times > t1)
                me->receive_damage("jing", jing_cost * t1);
        else
                me->receive_damage("jing", jing_cost * times);

        if( query("env/auto_regenerate", me) )
                SKILL_D("force/regenerate")->exert(me, me);

        addn("learned_points", t4, me);
	// 奇筋异骨在研究完后补10%潜能
	if( query("special_skill/qijin", me) && t4 > 10)
                addn("potential", t4 / 10, me);

        me->improve_skill(skill, t4 * improve);

        skill_name = SKILL_D(skill)->query_skill_name(lvl);
        if (skill_name)
                write(sprintf(HIM "你研究了一会，对「%s」这一"
                              "招似乎想通了些什么。\n" NOR,
                              skill_name));
        else
                write(sprintf(HIM "你研究了一会，似乎对「%s」"
                              "有些新的领悟。\n" NOR,
                              to_chinese(skill)));

        if (t4 > 0 && t4 < times)
                write("你觉得太累了，研究了" + chinese_number(t4) +
                      "次后只好停下来休息。\n");

        return 1;
}

int *query_scale(string skill)
{
        if (SKILL_D(skill)->valid_enable("force"))
                skill = "force";

        switch (skill)
        {
        case "parry":
                return ({ 5, 20, 140, 70, 50, 30, 10, 5, 4, 3, 2, 1 });

        case "dodge":
                return ({ 80, 100, 30, 10, 8, 5, 2, 1 });

        case "force":
                return ({ 150, 120, 50, 40, 20, 8, 5, 2, 1 });

        default:
                return ({ 80, 120, 90, 55, 30, 15, 5, 2, 1 });
        }
}

int help(object me)
{
        write(@HELP
指令格式：research | yanjiu <技能> <次数>

这个指令可以让你研究一种技能的疑难问题，当你师傅这项技能的级
别不如你的时候，可以通过研究自己来提高，进度的速度要和你对这
项技能的掌握程度和相关技能的熟悉情况相关，当然悟性也会起的一
定的作用，但是关键还是看技能的水平。一般来说相关的技能越多越
好，研究起来可能会事半功倍，如果会得太少，可能恰恰相反。

其他相关指令：apprentice, practice, skills, study, learn
HELP);
        return 1;
}
