// copyskill.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

protected int copy_skill(object me, object ob);
int help();

int main(object me, string arg)
{
        object ob;
        object tob;
        string target;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg)
        {
                help();
                return 1;
        }

        if (sscanf(arg, "%s to %s", arg, target) == 2)
        {
                if (! objectp(tob = present(target, environment(me))))
                        return notify_fail("你眼前没有 " + target + " 这个人。\n");
        } else
                tob = me;

        if (wiz_level(me) <= wiz_level(tob) && me != tob)
                return notify_fail("你只能给权限比自己低的人复制武功。\n");

        if (arg == "me")
                ob = me;
        else
        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("你眼前没有 " + arg + " 这个人。\n");

        if (! is_root(me) && playerp(tob) && ! wizardp(tob))
                return notify_fail("只有天神才能给普通玩家复制武功。\n");

        if (! me->is_admin())
        {
                switch (SECURITY_D->query_site_privilege("copyskill"))
                {
                case "me":
                        if (tob != me)
                                return notify_fail("你只能给自己复制武功。\n");
                case "wizard":
                        if (wiz_level(tob) < 1)
                                return notify_fail("你只能给巫师复制武功。\n");

                case "all":
                        break;

                default:
                        return notify_fail("你不能复制武功。\n");
                }
        }

        if (ob == tob)
                return notify_fail("不需要复制吧。\n");

        if (me != tob)
                log_file("static/copyskill", sprintf("%s %s copy %s(%s)'s skill to %s(%s).\n",
                                                     log_time(), log_id(me),
                                                     ob->name(1),query("id", ob),
                                                     tob->name(1), query("id", tob)));

        copy_skill(tob, ob);
        message_vision(HIM + me->name(1) + HIM "口中念念有词，只见一道红光笼罩了$N"
                       HIM "和$n" HIM "。\n" NOR, tob, ob);
        return 1;
}

protected int copy_skill(object me, object ob)
{
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        string *sname;
        string *mname;
        string *pname;
        int i, temp;

        if (mapp(skill_status = me->query_skills()))
        {
                skill_status = me->query_skills();
                sname = keys(skill_status);

                temp = sizeof(skill_status);
                for (i = 0; i < temp; i++)
                        me->delete_skill(sname[i]);
        }

        if (mapp(skill_status = ob->query_skills()))
        {
                skill_status = ob->query_skills();
                sname = keys(skill_status);

                for (i = 0; i < sizeof(skill_status); i++)
                        me->set_skill(sname[i], skill_status[sname[i]]);
        }
        
        if (mapp(map_status = me->query_skill_map()))
        {
                mname = keys(map_status);

                temp = sizeof(map_status);
                for (i = 0; i < temp; i++)
                        me->map_skill(mname[i]);
        }

        if (mapp(map_status = ob->query_skill_map()))
        {
                mname = keys(map_status);

                for(i = 0; i < sizeof(map_status); i++)
                        me->map_skill(mname[i], map_status[mname[i]]);
        }

        if (mapp(prepare_status = me->query_skill_prepare()))
        {
                pname = keys(prepare_status);

                temp = sizeof(prepare_status);
                for(i = 0; i < temp; i++)
                        me->prepare_skill(pname[i]);
        }

        if (mapp(prepare_status = ob->query_skill_prepare()))
        {
                pname = keys(prepare_status);

                for(i = 0; i < sizeof(prepare_status); i++)
                        me->prepare_skill(pname[i], prepare_status[pname[i]]);
        }

        hp_status = ob->query_entire_dbase();
        my = me->query_entire_dbase();

        my["str"] = hp_status["str"];
        my["int"] = hp_status["int"];
        my["con"] = hp_status["con"];
        my["dex"] = hp_status["dex"];
        my["per"] = hp_status["per"];
        my["kar"] = hp_status["kar"];

        my["mud_age"]     = hp_status["mud_age"];
        my["age"]     = hp_status["age"];
        my["max_qi"]     = hp_status["max_qi"];
        my["eff_qi"]     = hp_status["eff_qi"];
        my["qi"]         = hp_status["qi"];
        my["max_jing"]   = hp_status["max_jing"];
        my["eff_jing"]   = hp_status["eff_jing"];
        my["jing"]       = hp_status["jing"];
        my["max_neili"]  = hp_status["max_neili"];
        my["max_jingli"]  = hp_status["max_jingli"];
        my["neili"]      = hp_status["neili"];
        my["jiali"]      = hp_status["jiali"];
        my["score"]      = hp_status["score"];
        my["shen"]      = hp_status["shen"];
        my["meili"]      = hp_status["meili"];
        my["magic_points"] = hp_status["magic_points"];
        my["potential"] = hp_status["potential"];
        my["learned_points"] = hp_status["learned_points"];
        my["experience"] = hp_status["experience"];
        my["learned_experience"] = hp_status["learned_experience"];
        my["combat_exp"] = hp_status["combat_exp"];
        my["gift"] = hp_status["gift"];
        my["can_perform"] = hp_status["can_perform"];
        my["special_skill"] = hp_status["special_skill"];
        my["family"] = hp_status["family"];
        my["born_family"] = hp_status["born_family"];
        my["character"] = hp_status["character"];
        my["balance"] = hp_status["balance"];
        my["weiwang"] = hp_status["weiwang"];
        my["quest_count"] = hp_status["quest_count"];
        my["degree"] = hp_status["degree"];
        my["degree_jungong"] = hp_status["degree_jungong"];
        my["guo_shoucheng"] = hp_status["guo_shoucheng"];
        my["questdg_times"] = hp_status["questdg_times"];
        my["quesths_times"] = hp_status["quesths_times"];
        my["questkh_times"] = hp_status["questkh_times"];
        my["questsn_times"] = hp_status["questsn_times"];

        me->reset_action();
        return 1;
}

int help()
{
        write(@TEXT
指令格式：copyskill <对象> [to <目的对象>]

这个指令让你复制对象的战斗经验和所有的武功技能。

该命令在可以被授权使用的信息包括：me、wizard、all。
TEXT );
        return 1 ;
}
