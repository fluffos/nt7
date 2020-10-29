// db.c
// created by jjgod

inherit F_CLEAN_UP;

#include "/adm/etc/database.h"
#include <ansi.h>
#include <mudlib.h>

int help(object me);
protected void done_edit(object me, string sql);

int main(object me, string arg)
{
        string sql;
        string msg;
        mixed  ret, res, *arr;
        string db, tb, expr, col;
        int    i, j, n;
        int    cnum, lnum;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        // 无参数则列出服务器中所有数据库
        if (! arg)
        {
                i = 1;
                msg = sprintf(HIC "%s(" HIW "%s" HIC ")的数据库列表：\n" NOR
                              HIW "----数据库名------------表数------\n" NOR,
                              LOCAL_MUD_NAME(), upper_case(INTERMUD_MUD_NAME));

                while (sizeof(ret = DATABASE_D->db_fetch_row("SHOW DATABASES", i)))
                {
                        sql = sprintf("SHOW TABLES FROM %s", ret[0]);
                        msg += sprintf(CYN "   %-18s [ " WHT "%3d" CYN " ]\n" NOR, ret[0],
                                       DATABASE_D->db_query(sql));
                        i++;
                }
                msg += sprintf(HIW "----------------------------------\n" NOR
                               HIC "本机共有 " HIW "%d" HIC " 个数据库。" NOR, i - 1);
        }
        // 列出指定游戏数据库的数据表(显示列数量)
        else
        if (arg == "-d" || sscanf(arg, "-d %s", db) && db == DATABASE)
        {
                i = 1;
                db = DATABASE;
                sql = sprintf("SHOW TABLES FROM %s", db);

                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "没有 " WHT + db + CYN " 这个数据库。\n" NOR);

                msg = sprintf(HIC "数据库(" HIW "%s" HIC ")的数据表：\n" NOR
                              HIW "----数据表名------------------------列------行----\n" NOR, db);

                while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                {
                        res = DATABASE_D->db_query(sprintf("SHOW COLUMNS FROM %s FROM %s", ret[0], db));
                        if (intp(res)) cnum = res;

                        arr = DATABASE_D->db_fetch_row(sprintf("SELECT COUNT(*) FROM %s", ret[0]));
                        if (sizeof(arr)) lnum = arr[0];

                        msg += sprintf(CYN "   %-30s [ " WHT "%2d" CYN " / " WHT "%4d" CYN " ]\n" NOR,
                                       ret[0], cnum, lnum);
                        i++;
                }
                msg += sprintf(HIW "--------------------------------------------------\n" NOR
                               HIC "此数据库共有 " HIW "%d" HIC " 张数据表。" NOR, i - 1);
        }
        // 列出其他数据库中指定数据表的字段信息
        else
        if (sscanf(arg, "-d %s", db))
        {
                i = 1;
                db = stringp(db) ? db : DATABASE;
                sql = sprintf("SHOW TABLES FROM %s", db);

                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "没有 " WHT + db + CYN " 这个数据库。\n" NOR);

                msg = sprintf(HIC "数据库(" HIW "%s" HIC ")的数据表：\n" NOR
                              HIW "----数据表名------------------------列----\n" NOR, db);

                while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                {
                        res = DATABASE_D->db_query(sprintf("SHOW COLUMNS FROM %s FROM %s", ret[0], db));
                        if (intp(res)) cnum = res;

                        msg += sprintf(CYN "   %-30s [ " WHT "%2d" CYN " ]\n" NOR,
                                       ret[0], cnum);
                        i++;
                }
                msg += sprintf(HIW "------------------------------------------\n" NOR
                               HIC "此数据库共有 " HIW "%d" HIC " 张数据表。" NOR, i - 1);
        }
        // 列出游戏数据库中指定数据表的字段信息
        else
        if (sscanf(arg, "-t %s", tb))
        {
                i = 1;
                sql = sprintf("SHOW COLUMNS FROM %s", tb);

                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "没有 " WHT + tb + CYN " 这个数据表。\n" NOR);

                msg = sprintf(HIC "数据表(" HIW "%s" HIC ")的结构：\n" NOR
                              HIW "----字段名----------------------------附加信息------------\n" NOR, tb);

                while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                {
                        res = DATABASE_D->db_fetch_row(sprintf("DESC %s %s", tb, ret[0]));
                        res -= ({ ret[0] });
                        res = filter_array(res, (: $1 != "" :));

                        msg += sprintf(CYN "   %-24s [ " WHT "%s" CYN " ]\n" NOR, ret[0],
                                       implode(res, CYN " | " WHT));
                        i++;
                }
                msg += sprintf(HIW "----------------------------------------------------------\n" NOR
                               HIC "此数据表共有 " HIW "%d" HIC " 个字段。" NOR, i - 1);
        }
        // 按照表达式查询制定数据表中制定字段的内容
        else
        if (sscanf(arg, "-s %s %s", tb, arg) == 2)
        {
                sql = sprintf("SHOW COLUMNS FROM %s", tb);

                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "没有 " WHT + tb + CYN " 这个数据表。\n" NOR);

                // 指定表达式
                if (sscanf(arg, "%s where %s", col, expr) == 2)
                {
                        i = 1;
                        sql = sprintf("SELECT %s FROM %s WHERE %s", col, tb, expr);

                        msg = sprintf(HIC "查询(" HIW "%s" HIC ")的结果：\n" NOR
                              HIW "----字段名------------------------------------------------\n" NOR
                              HIC "   %s\n" NOR
                              HIW "----------------------------------------------查询结果----\n" NOR,
                              sql, col);

                        while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                        {
                                msg += sprintf(CYN "   %" + (stringp(ret[0]) ? "s" : "O") +
                                               "\n" NOR, ret[0]);
                                i++;
                        }
                        msg += sprintf(HIW "----------------------------------------------------------\n" NOR
                                       HIC "此次查询共有 " HIW "%d" HIC " 个符合结果。" NOR, i - 1);
                        if (! (i - 1))
                                return notify_fail(sprintf(CYN "查询：" WHT "%s" CYN "\n没有得到任何结果，请检"
                                                           "查是否无此字段或表达式输入错误。\n" NOR, sql));
                }
                // 不指定表达式
                else
                {
                        col = arg;
                        i = 1;
                        sql = sprintf("SELECT %s FROM %s", col, tb);

                        msg = sprintf(HIC "查询(" HIW "%s" HIC ")的结果：\n" NOR
                              HIW "----字段名------------------------------------------------\n" NOR
                              HIC "   %s\n" NOR
                              HIW "----------------------------------------------查询结果----\n" NOR,
                              sql, col);

                        while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                        {
                                msg += sprintf(CYN "   %" + (stringp(ret[0]) ? "s" : "O") +
                                               "\n" NOR, ret[0]);
                                i++;
                        }
                        msg += sprintf(HIW "----------------------------------------------------------\n" NOR
                                       HIC "此次查询共有 " HIW "%d" HIC " 个符合结果。" NOR, i - 1);
                        if (! (i - 1))
                                return notify_fail(sprintf(CYN "查询：" WHT "%s" CYN "\n没有得到任何结果，请检"
                                                           "查是否无此字段或者数据表为空。\n" NOR, sql));
                }
        }
        // 查询指定一个列的所有信息
        // 向后查询
        else
        if (sscanf(arg, "-n %s where %s", tb, expr) == 2)
        {
                i = 1;

                // 准备要查询的列号
                n=query("db_last_query/"+tb, me)+1;

                // 准备列信息
                sql = sprintf("SHOW COLUMNS FROM %s", tb);
                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "没有 " WHT + tb + CYN " 这个数据表。\n" NOR);

                arr = ({ });
                while (sizeof(res = DATABASE_D->db_fetch_row(sql, i)))
                {
                        arr += ({ res[0] });
                        i++;
                }
                // 准备行信息
                sql = sprintf("SELECT * FROM %s WHERE %s", tb, expr);
                j = DATABASE_D->db_query(sql);
                n = j < n ? j : n;
                ret = DATABASE_D->db_fetch_row(sql, n);

                // 显示信息
                msg = sprintf(HIC "查询(" HIW "%s" HIC ")的第 " HIW "%d" HIC " 行结果：\n" NOR
                              HIW "----字段名------------------------字段内容----------------\n" NOR,
                              sql, n);
                cnum = sizeof(arr);

                if (! cnum || ! sizeof(ret))
                        return notify_fail(sprintf(CYN "查询：" WHT "%s" CYN "\n没有得到任何结果，请检"
                                                   "查是否无此字段或表达式输入错误。\n" NOR, sql));
                for (i = 0; i < cnum; i++)
                        msg += sprintf(CYN "  %-30s " WHT "%O\n" NOR, arr[i], ret[i]);

                msg += sprintf(HIW "----------------------------------------------------------\n" NOR
                               HIC "此列共有 " HIW "%d" HIC " 个字段。" NOR, cnum);

                // 准备下一次查询
                set("db_last_query/"+tb, n, me);
        }
        // 向前查询
        else
        if (sscanf(arg, "-f %s where %s", tb, expr) == 2)
        {
                i = 1;
                n=query("db_last_query/"+tb, me)-1;

                // 准备列信息
                sql = sprintf("SHOW COLUMNS FROM %s", tb);
                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "没有 " WHT + tb + CYN " 这个数据表。\n" NOR);

                arr = ({ });
                while (sizeof(res = DATABASE_D->db_fetch_row(sql, i)))
                {
                        arr += ({ res[0] });
                        i++;
                }
                // 准备行信息
                sql = sprintf("SELECT * FROM %s WHERE %s", tb, expr);
                n = n < 1 ? 1 : n;
                ret = DATABASE_D->db_fetch_row(sql, n);

                // 显示信息
                msg = sprintf(HIC "查询(" HIW "%s" HIC ")的第 " HIW "%d" HIC " 行结果：\n" NOR
                              HIW "----字段名------------------------字段内容----------------\n" NOR,
                              sql, n);
                cnum = sizeof(arr);

                if (! cnum || ! sizeof(ret))
                        return notify_fail(sprintf(CYN "查询：" WHT "%s" CYN "\n没有得到任何结果，请检"
                                                   "查是否无此字段或表达式输入错误。\n" NOR, sql));
                for (i = 0; i < cnum; i++)
                        msg += sprintf(CYN "  %-30s " WHT "%O\n" NOR, arr[i], ret[i]);

                msg += sprintf(HIW "----------------------------------------------------------\n" NOR
                               HIC "此列共有 " HIW "%d" HIC " 个字段。" NOR, cnum);

                // 准备下一次查询
                set("db_last_query/"+tb, n, me);
        }
        // 执行 SQL 语句
        else
        if (arg == "-e" || sscanf(arg, "-e %s", sql))
        {
                if (! stringp(sql) || sql == "")
                {
                        write(HIC "请输入你要执行的语句：\n" NOR);
                        me->edit((: call_other, __FILE__, "done_edit", me :));
                } else
                done_edit(me, sql);
        }

        else return help(me);
        if (stringp(msg) && msg != "") me->start_more(msg);
        return 1;
}

protected void done_edit(object me, string sql)
{
        mixed ret, *res;
        string msg;

        if (! sql || sql == "")
        {
                tell_object(me, HIC "你取消了输入。\n" NOR);
                return;
        }
        if (sql[<1..<0] == "\n") sql = sql[0..<2];
        msg = sprintf(HIC "语句(" HIW "%s" HIC ")的执行结果：\n"
                      HIW "----------------------------------------------------------------"
                      "--------------\n" NOR, sql);
        if (! ret = DATABASE_D->db_query(sql))
        {
                msg += CYN "没有得到任何可用信息。\n" HIW "--------------------------------"
                       "----------------------------------------------\n" NOR;
        } else
        if (stringp(ret))
        {
                msg += sprintf(HIR "错误信息：" NOR WHT "%s\n" NOR
                               HIW "--------------------------------------------------------"
                               "----------------------\n" NOR, ret);
        } else
        {
                res = DATABASE_D->db_all_query(sql);
                msg += sprintf(WHT "%O\n" NOR
                               HIW "--------------------------------------------------------"
                               "----------------------\n" NOR, res);
        }
        tell_object(me, msg);
        return;
}

int help(object me)
{
        write(@HELP
指令格式: db [ -d [ 数据库名 ] ] |
             [ -t <数据表名> ] |
             [ -s <数据表名> <字段名> [ where <表达式> ] ] |
             [ -n <数据表名> where <表达式> ] |
             [ -f <数据表名> where <表达式> ]
             [ -e [ <SQL 语句> ] ]

此指令用于游戏数据库的管理。你可以使用 -d 参数列出数据库的
内容，-t 列出本游戏数据库的数据表的内容。-s 参数用于在数据
库里符合指定表达式的行，若不指定表达式，则显示此表中所有的
列。 考虑到 mud 中显示的问题，这里必须指定字段名，也就是只
能同时显示所有结果一个字段的信息。如果你想获得一个结果所有
字段的信息，可以使用 -n 参数向后查询或者 -f 参数向前查询。

由于游戏的数据库连接的效率问题，本指令不提供对非游戏数据库
的操作。
HELP);
        return 1;
}
