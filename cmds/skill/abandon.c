// abandon.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help();
int main(object me, string arg)
{
        mapping smap, pmap;
        int skill_lvl, lvl, i;
        int jingcost;
        string skill;
        string name;
        int level;
        int lost;

        if (! arg || arg == "")
                return help();

        if (sscanf(arg, "%s to %d", skill, lvl) != 2)
                return help();

        if (me->is_fighting())
                return notify_fail("你正忙着打架呢，哪有时间做这种事？\n");

        if (me->is_busy())
                return notify_fail("你正忙，没法静下心来。\n");

        jingcost=query("int", me)+random(query("int", me));
        if( jingcost>query("jing", me) )
                return notify_fail("你无法集中精力。\n");

        if (skill == "exp")
        {
                lost=query("combat_exp", me);
                if (lost < 100)
                        return notify_fail("你发现自己现在对武学简直就是一无所知。\n");

                if (lvl > lost || lvl < 0)
                        return notify_fail("你发现自己现在对武学理解还没有那么高。\n");

                if (lvl == lost)
                        return notify_fail("你是不是头脑进水了，现在还用放弃吗？\n");

                level = sqrt3(lvl/100) * 10 + 1;
                while ((level + 1)*(level + 1)*(level + 1) <= lvl*10 )
                        level++;

                tell_object(me, HIR "你将放弃EXP到 " + lvl + " 点，仅可支持 " +
                                chinese_number(level) + " 级武学技能。\n\n" NOR);

                tell_object(me, "请务必考虑清楚，确定的话请输入您的管理密码或普通密码：");
                input_to("check_password", 1, me, skill, lvl);
                return 1;

                message("vision", me->name() + "坐下在凝神思索什么。\n",
                        environment(me), me);
                tell_object(me, "你不再想拳脚兵器轻功内功，只是一门心思忘记武功。\n");
                me->start_busy(3 + random(5));
                if( random(query("int", me))>15 )
                {
                        tell_object(me, "可是你发现自己似乎记性太好，没有半点效果。\n");
                        return 1;
                }

                // lost = random(lost / 100) + 1;
                // addn("combat_exp", -lost, me);
                set("combat_exp", lvl, me);
                switch (random(6))
                {
                case 0:
                        tell_object(me, HIR "你又想起了很多温馨"
                                    "的往事，不由得沉浸其中。\n" NOR);
                        break;
                case 1:
                        tell_object(me, HIR "你似乎又看到了遥远"
                                    "的童年，一时忘却了尘世间的烦恼。\n" NOR);
                        break;
                case 2:
                        tell_object(me, HIR "你黯然一声长叹，只觉"
                                    "得自己为了武学荒废一生，实在无谓。\n" NOR);
                        break;
                case 3:
                        tell_object(me, HIR "你心如止水，所有的"
                                    "武功都仿佛离自己远去了。\n" NOR);
                        break;
                case 4:
                        tell_object(me, HIR "你抬头仰望天空，发"
                                    "现它明亮透析，说不出的娇媚，令你身心俱化。\n" NOR);
                        break;
                default:
                        tell_object(me, HIR "你脑海中晃过当年无"
                                    "数刻苦修炼的日子，不由得暗自苦笑。\n" NOR);
                        break;
                }

                // UPDATE_D->check_user(me);
                return 1;
        }

        smap = me->query_skill_map();
        pmap = me->query_skill_prepare();

        name = to_chinese(skill);
        if (name[0] < 160) name = "这项技能";
        skill_lvl = (int)me->query_skill(skill, 1);

        if (! skill_lvl)
        {
                me->delete_skill(skill);
                write("好了。\n");
                return 1;
        }

        if (lvl > skill_lvl || lvl < 0)
                return notify_fail("你发现自己现在对该项武功理解还没有那么高。\n");

        if (lvl == skill_lvl)
                return notify_fail("你是不是头脑进水了，现在还用放弃吗？\n");

        if( me->query_all_buff("add_skill") )
                return notify_fail("你先把你身上能加技能等级的装备都卸载了。\n");

        tell_object(me, HIR "你将放弃技能 " + name + " 至 " + chinese_number(lvl) + " 级。\n\n" NOR);

        tell_object(me, "请务必考虑清楚，确定的话请输入您的管理密码或普通密码：");
        input_to("check_password", 1, me, skill, lvl, name, smap, pmap);
        return 1;

        me->start_busy(1+random(query("int", me)/7));
        if( random(query("int", me))>24 )
                return notify_fail("你集中精力不再想" + name + "，结果发现毫无结果。\n");

        // skill_lvl = random(skill_lvl);
        if (lvl < 1)
        {
                for (i = sizeof(smap)-1; i >= 0; i --)
                        if ((string)smap[keys(smap)[i]] == skill)
                                me->map_skill(keys(smap)[i]);

                for (i = sizeof(pmap)-1; i >= 0; i -- )
                        if ((string) values(pmap)[i] == skill)
                                me->prepare_skill(keys(pmap)[i]);

                SKILLS_D->remove_id_from_abandon(me, skill);
                me->delete_skill(skill);
                me->reset_action();
                write("你集中精力不再想" + name + "，结果终于将它彻底忘记了。\n");
        } else
        {
                me->set_skill(skill, lvl);
                write("你集中精力不再想" + name + "，结果有所效果。\n");
        }
        return 1;
}

varargs void check_password(string passwd, object me, string skill, int lvl, string name, mapping smap, mapping pmap)
{
        int i;
        object link_ob;
        string old_pass;

        link_ob=query_temp("link_ob", me);
        old_pass=query("ad_password", link_ob);
        if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
        {
                old_pass=query("password", link_ob);
                if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
                {
                        write(HIR "密码错误！请注意，放弃武学必须输入管理密码或普通密码。\n");
                        return;
                }
        }

        if (skill == "exp")
        {
                message("vision", me->name() + "坐下在凝神思索什么。\n",
                        environment(me), me);
                tell_object(me, "你不再想拳脚兵器轻功内功，只是一门心思忘记武功。\n");
                me->start_busy(3 + random(5));
                /*
                if( random(query("int", me))>15 )
                {
                        tell_object(me, "可是你发现自己似乎记性太好，没有半点效果。\n");
                        return;
                }
                */

                set("combat_exp", lvl, me);
                switch (random(6))
                {
                case 0:
                        tell_object(me, HIR "你又想起了很多温馨"
                                    "的往事，不由得沉浸其中。\n" NOR);
                        break;
                case 1:
                        tell_object(me, HIR "你似乎又看到了遥远"
                                    "的童年，一时忘却了尘世间的烦恼。\n" NOR);
                        break;
                case 2:
                        tell_object(me, HIR "你黯然一声长叹，只觉"
                                    "得自己为了武学荒废一生，实在无谓。\n" NOR);
                        break;
                case 3:
                        tell_object(me, HIR "你心如止水，所有的"
                                    "武功都仿佛离自己远去了。\n" NOR);
                        break;
                case 4:
                        tell_object(me, HIR "你抬头仰望天空，发"
                                    "现它明亮透析，说不出的娇媚，令你身心俱化。\n" NOR);
                        break;
                default:
                        tell_object(me, HIR "你脑海中晃过当年无"
                                    "数刻苦修炼的日子，不由得暗自苦笑。\n" NOR);
                        break;
                }

                //UPDATE_D->check_user(me);
                return;
        }

        me->start_busy(1+random(query("int", me)/7));
        /*
        if( random(query("int", me))>24 )
        {
                tell_object(me, "你集中精力不再想" + name + "，结果发现毫无结果。\n");
                return;
        }
        */

        if (lvl < 1)
        {
                for (i = sizeof(smap)-1; i >= 0; i --)
                        if ((string)smap[keys(smap)[i]] == skill)
                                me->map_skill(keys(smap)[i]);

                for (i = sizeof(pmap)-1; i >= 0; i -- )
                        if ((string) values(pmap)[i] == skill)
                                me->prepare_skill(keys(pmap)[i]);

                SKILLS_D->remove_id_from_abandon(me, skill);
                me->delete_skill(skill);
                me->reset_action();
                write("你集中精力不再想" + name + "，结果终于将它彻底忘记了。\n");
        } else
        {
                int add;

                add = me->query_all_buff("add_skill");
                lvl -= add;
                if (lvl < 1)
                {
                        tell_object(me, "你如果真的想全部放弃" + name + "请重新指定数字为零。\n");
                        return;
                }
                me->set_skill(skill, lvl);
                me->delete_learn(skill);
                SKILLS_D->check_skillmix(me, 1); 
                write("你集中精力不再想" + name + "，结果有所效果。\n");
        }
        return;
}

int help()
{
        write(@TEXT
指令格式：abandon|fangqi <技能名称> | exp to <数值>

放弃你的实战经验或是某一项你所学过的技能到指定的数值，成功率
和你的天赋有关，只有能够休息的地方才能够静下心来忘记武功。

有时候因为武功相克或者你不再打算在某项技能上再下功夫，就可以
使用这条指令放弃它。
TEXT );
        return 1;
}
