// setskill.c
// Smallfish@Huaxia

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int i,j,level;
        mapping skill_status;
        object ob;
        string skill,obj;
        string *skills;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if( !arg )
                return notify_fail("setskill <某人> <技能>/all <级别数>。\n");

        if( !arg || sscanf(arg, "%s %s %d", obj, skill, level)!=3 )
                return notify_fail("setskill <某人> <技能>/all <级别数>。\n");

        ob = find_player(obj);

        if( !ob )
                ob = find_living(obj);
        if( !ob )
                ob = present(obj, environment(me));
        if( !ob )
                return notify_fail("找不到这个生物.\n");

        if( (wiz_level(me) < wiz_level(ob)) && userp(ob) )
                return notify_fail("你没有设置" + ob->name() + "技能的权利。\n");

/*
        if( level == 0 && wizardp(ob) )
                return notify_fail("不能用此命令将巫师的功夫删除。\n");
*/

        if (! me->is_admin())
        {
                switch (SECURITY_D->query_site_privilege("call"))
                {
                case "all":
                        break;

                case "self":
                        if (ob != me)
                                return notify_fail("你只能使用该命令呼叫自身的函数。\n");
                        break;

                case "npc":
                        if (playerp(ob) || ! ob->is_character())
                                return notify_fail("你只能呼叫 NPC 的函数。\n");
                        break;

                case "user":
                        if (! playerp(ob))
                                return notify_fail("你只能对玩家使用这个命令。\n");
                        break;

                case "nonechar":
                        if (ob->is_character())
                                return notify_fail("你只能对非角色对象使用这个命令。\n");
                        break;

                case "wizard":
                        if (! wizardp(ob))
                                return notify_fail("你只能对巫师使用这个命令。\n");
                        break;

                default:
                        return notify_fail("你不能使用该命令。\n");
                }
        }

        write(WHT"begin setting skills for "NOR + ob->short(1) + WHT"：\n"NOR);
        if( skill == "all" ) {
                if ( !(skill_status = ob->query_skills()) || !sizeof(skill_status) )
                        return notify_fail("这个人没有学会任何技能，不能用 all 这个参数。\n");
                skills  = keys(skill_status);
                j = sizeof(skill_status);
                for(i=0; i<j; i++) {
                        if( level ==0 ) {
                                ob->delete_skill(skills[i]);
                                write("deleting->" + to_chinese(skills[i]) + 
                                        "(" + skills[i] + ")\n");
                        }
                        else {
                                ob->set_skill(skills[i], level);
                                printf("setting-> %-36s%d\n", to_chinese(skills[i]) + 
                                        "(" + skills[i] + ")", level);
                        }
                }
        }
        else {
                if( level ==0 ) {
                        ob->delete_skill(skill);
                        write("deleting->" + to_chinese(skill) + "(" + skill + ")\n");
                }
                else    {
                        ob->set_skill(skill, level);
                        printf("setting-> %-36s%d\n", to_chinese(skill) + 
                                "(" + skill + ")", level);
                }
        }
        if( userp(ob) && ob!=me ) log_file("static/setskill",
                sprintf("%s(%s) setskill %s(%s) %s to level %d at %s.\n", me->name(),
                        query("id", me),ob->name(),query("id", ob),skill,level,
                        ctime(time()) ) );
        write(WHT"Done.\n"NOR);
        return 1;
}

int help()
{
        write(@LONG
指令格式：setskill  <某人> <技能>/all <级别数>。

用来设定某人的某种技能的级别数, 如果第二项是 all 则将其所有的
技能改为设定的级别数。如果选择了级别数为 0 则删除该人此项技能。

警告：请慎用此命令。
LONG    );
        return 1;
}
