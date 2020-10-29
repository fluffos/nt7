// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.
// purge.c

// #pragma save_binary
#include <ansi.h>

#define SYNTAX  "指令格式：purge [<未上线天数>] | <使用者姓名> because <原因>\n"

inherit F_CLEAN_UP;

protected int do_purge_players(object me, int day);

int main(object me, string arg)
{
        string name, reason;
        int day;
        object ob;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg)
                return notify_fail(SYNTAX);

        if (sscanf(arg, "%d", day) && day >= 0)
                return do_purge_players(me, day);

        if (sscanf(arg, "%s because %s", name, reason) != 2)
                return notify_fail(SYNTAX);

        if (wiz_level(me) <= wiz_level(name) && ! is_root(me))
                return notify_fail("你没有权限删除这个人物。\n");

        seteuid(getuid());
        if (file_size(DATA_DIR + "login/" + name[0..0] + "/" + name + __SAVE_EXTENSION__) < 0)
                return notify_fail("没有这位使用者。\n");

        if (ob = find_player(name))
                CHANNEL_D->do_channel(this_object(), "rumor", "使用者" +
                                      query("name", ob)+"被"+
                                      query("name", me)+"删除了。");

        // remove the user from disk
        UPDATE_D->remove_user(name, 1);

        tell_object(me, "使用者 " + capitalize(name) + " 删除掉了。\n");
        log_file("static/purge", sprintf("%s %s purged %s because %s.\n",
                 log_time(), geteuid(this_player(1)), name, reason));

        return 1;
}

protected int do_purge_players(object me, int day)
{
        int i, j, ppl_cnt, count;
        string *dir, *ppls;
        string name;
        mixed info;

        seteuid(getuid());

        if (day < 30) return notify_fail("您还是手下留情。别连他们都杀了。\n");

        message_system(sprintf("系统开始整理玩家储存档中，并清除超过 %d 天不上线的使用者...", day));
        write(HIG "现在系统将检查所有玩家，稍后汇报。\n"
              HIG "进度：" + process_bar(0) + "\n");

        if (me)
        {
                me->attach_system();
                me->write_prompt();
        }

        count = 0;
        ppl_cnt = 0;
        dir = get_dir(DATA_DIR + "login/");
        for (i = 0; i < sizeof(dir); i++)
        {
                ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/", -1);
                for (j = 0; j < sizeof(ppls); j++)
                {
                        reset_eval_cost();
                        if (sscanf(ppls[j][0], "%s.o", name) == 1)
                        {
                                if ((string)SECURITY_D->get_status(name) != "(player)")
                                        continue;

                                info = stat(DATA_DIR + "login/" + name[0..0] + "/" +
                                          name + __SAVE_EXTENSION__);

                                if (! arrayp(info) || sizeof(info) < 3)
                                        continue;
                                        // 可能没有这个文件

                                if ((time()-(int)info[1]) / 86400 >= day && ! objectp(find_player(name)))
                                {
                                        log_file("static/purge",
                                                 sprintf("%s %s was purged by %s "
                                                         "for didn't login more than %d days\n",
                                                         log_time(), name, geteuid(this_player(1)), day));
                                        UPDATE_D->remove_user(name);
                                        count ++;
                                }
                        }
                }
                ppl_cnt += j;
                message("system", ESC + "[1A" + ESC + "[256D"
                                  HIG "进度：" + process_bar((i + 1) * 100 / sizeof(dir)) +
                                   "\n" + (me ? HIR "执行中" NOR "> " : ""),
                                   me ? me : filter_array(all_interactive(), (: wizardp :)));
        }
        message_system("系统整理批量档案处理完毕，请继续游戏。\n" ESC + "[K");
        if (me)
        {
                me->detach_system();
        }

        write(HIG "原来总共有 " + ppl_cnt + " 位使用者。\n" NOR);
        write(HIG "有 " + count + " 个超过 " + day + " 天未上线的使用者被清除掉了。\n" NOR);
        write(HIG "现在总共有 " + (ppl_cnt - count) + " 位使用者。\n" NOR);

        return 1;

}

int help(object me)
{
write(@HELP
指令格式：purge [<未上线天数>] | <使用者姓名> because <原因>

清除一个使用者或清除超过一定天数不曾上线地使用者。
HELP );
    return 1;
}
