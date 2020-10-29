// allemail.c
// Smallfish@Huaxia

#include <ansi.h>

inherit F_CLEAN_UP;

protected string fname(object ob);
protected string examine_player(string name);

void create() { seteuid(getuid()); }

public void search_dir(object me, int raw);

int main(object me, string arg)
{
        int i;
        int copy_user;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return notify_fail("指令格式：allemail <玩家ID> | -all\n");

        if (arg != "-all")
        {
                string r;
                r= examine_player(arg);
                write("检查OK.\n");
                log_file("static/email", filter_color(r));
                return 1;
        }

         message_system("系统进行数据处理中，请耐心等候...\n");
        write(HIG "现在系统将检查所有玩家，稍后汇报。\n"
              HIG "进度：" + process_bar(0) + "\n");
        if (me)
        {
                me->attach_system();
                me->write_prompt();
        }
        search_dir(me, 0);
        return 1;
}

void search_dir(object me, int raw)
{
        string *dir;
        string *result;
        string name;
        string info;
        mixed *ppls;
        int count;
        int total;
        int i;
        int j;

        if (! is_root(previous_object()))
                return;

        dir = get_dir(DATA_DIR + "login/");
        result = ({ });
        for (i = 0; i < sizeof(dir); i++)
        {
                ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/", -1);
                for (j = 0; j < sizeof(ppls); j++)
                {
                        reset_eval_cost();
                        if (sscanf(ppls[j][0], "%s.o", name) == 1)
                        {
                                info = examine_player(name);
                                if (! info) continue;
                                if (member_array(info,result) == -1)
                                        result += ({ info });
                        }
                }
                total += j;
                message("system", ESC + "[1A" + ESC + "[256D"
                                  HIG "进度：" + process_bar((i + 1) * 100 / sizeof(dir)) +
                                  "\n" + (me ? HIR "执行中" NOR "> " : ""),
                                  me ? me : filter_array(all_interactive(), (: wizardp :)));
        }

        info = "";
        for (i = 0; i < sizeof(result); i++)
        {
                info += result[i];
                info += "\n";
                if (i % 20)
                {
                        log_file("static/email", filter_color(info));
                        info = "";
                }
        }

        log_file("static/email", filter_color(info));

        if (me)
        {
                message("system", info, me);
                me->detach_system();
        }
}

protected string examine_player(string name)
{
        object me;
        object login_ob;
        object user_ob;
        int online;
        string result;
        string email,temp1,temp2;

        login_ob = new(LOGIN_OB);
        set("id", name, login_ob);

        if (! login_ob->restore())
        {
                destruct(login_ob);
                return 0;
        }

        if( query("id", login_ob) != name )
        {
                string id;
                id=query("id", login_ob);
                destruct(login_ob);
                return 0;
        }

        if (! objectp(user_ob = find_player(name)))
        {
                online = 0;
                user_ob = LOGIN_D->make_body(login_ob);
                if (! user_ob)
                {
                        destruct(login_ob);
                        return 0;
                }

                if (! user_ob->restore())
                {
                        destruct(login_ob);
                        destruct(user_ob);
                        return 0;
                }
        } else
                online = 1;

        result=0;
        email=query("email", user_ob);

        if (stringp(email) &&
            strlen(email) > 10 &&
            sscanf(email,"%s@%s",temp1,temp2) == 2 &&
            strsrch(temp2,".") != -1)
                result = email;
        else
                result = 0;

        destruct(login_ob);
        if (! online)
                destruct(user_ob);

        return result;
}