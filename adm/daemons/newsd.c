// newsd.c

#include <ansi.h>
#include <mudlib.h>

// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// 数据的排列顺序
#define TITLE   0       // 标题
#define TIME    1       // 时间
#define AUTHOR  2       // 作者
#define MSG     3       // 内容
#define VIEW    4       // 点击

#define NITAN_VER     CHINESE_MUD_NAME
// 最多一千条新闻
#define MAX_NEWS_CAPACITY       1000

#include "/adm/etc/database.h"

// 门派更新优先级
int     last_update_day = 0;

nosave mixed snotes = ({ });

// 查询所有的新闻
#ifdef DB_SAVE
string *query_notes()
{
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();

        snotes = DATABASE_D->db_all_query(sprintf("SELECT * from %s", NEWS_TABLE));

        if (! pointerp(snotes) || ! sizeof(snotes))
        {
                tell_object(this_player(), "由于网络问题，访问数据库速度有些迟缓，请重新查看新闻。\n");
                return ({});
        }

        return sort_array(snotes, (: $1[1] - $2[1] :));
}
#endif

void create()
{
        seteuid(ROOT_UID);
        restore();
}


void remove()
{
        save();
}

void mud_shutdown()
{
        save();
}

// 添加新闻的点击 / 阅读次数
#ifdef DB_SAVE
void add_view_time(mixed* news, int i)
{
        string sql;

        sql = sprintf("UPDATE %s SET view = view + %d WHERE time = %d",
                      NEWS_TABLE, i, news[TIME]);
        // tell_object(this_player(), WHT + sql + "\n" NOR);
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_query(sql);
}
#endif

// 提示用户
void prompt_user(object me)
{
        int num;
        int total;
        mixed *notes;
        int last_read_time;

        last_read_time=query("last_read_news", me);
        if (! last_read_time)
        {
                tell_object(me, WHT "\n欢迎您进入" + LOCAL_MUD_NAME() +
                                WHT "，今后请使用" HIY " news " NOR WHT
                                "命令查阅发布的新闻信息。\n" NOR);
                set("last_read_news", 971000000, me);
                return;
        }
#ifdef DB_SAVE
            notes = query_notes();
#else
        notes = query("notes");
#endif
        if (! arrayp(notes) || ! sizeof(notes))
                return;

        num = sizeof(notes);
        total = 0;
        while (num--)
        {
#ifdef DB_SAVE
                       if (notes[num][TIME] > last_read_time)
#else
                if (notes[num]["time"] > last_read_time)
#endif
                        total++;
                else
                        break;
        }
        if (! total)
                tell_object(me, "\n你目前没有未曾阅读过的新闻。\n");
        else
                tell_object(me, sprintf(WHT "\n你目前一共有 " HIY "%d" NOR
                                        WHT " 条新闻还没有阅读，请使用("
                                        HIY "news" NOR WHT ")命令阅读。\n" NOR, total));

        // 开始定时通知
        if (previous_object() == find_object(LOGIN_D))
                me->start_call_out(bind((: call_other, __FILE__, "auto_notice", me :), me),
                                        10 + random(10));
}

// 显示所有的新闻标题
// raw = 1: 仅显示未读新闻
void show_news(object me, int raw)
{
        mixed *notes;
        int i, last_time_read;
        string msg;

#ifdef DB_SAVE
        notes = query_notes();
#else
        notes = query("notes");
#endif
        if (! pointerp(notes) || ! sizeof(notes))
        {
                tell_object(me, "目前没有任何新闻。\n");
                return;
        }

        msg = "目前游戏中的最新消息如下。\n"
              HIC "≡" HIY "------------------------------------------------------------------------------" HIC "≡\n" NOR;
        last_time_read=query("last_read_news", me);
        i = sizeof(notes);
        while (i--)
        {
#ifdef DB_SAVE

                if (raw && (notes[i][TIME] <= last_time_read))
                        break;

                msg += sprintf("%s[%3d]" NOR " %-" + (40
#ifndef LONELY_IMPROVED
                                                         + color_len(notes[i][TITLE])
#endif
                                                            ) +
                               "s %16s (%s) [%3d]\n",
                               (notes[i][TIME] > last_time_read ? HIY : ""),
                               i + 1, notes[i][TITLE],
                               // notes[i][AUTHOR], ctime(notes[i][TIME])[0..15], notes[i][VIEW]);
                               NITAN_VER, TIME_D->replace_ctime(notes[i][TIME]), notes[i][VIEW]);
#else
                if (raw && (notes[i]["time"] <= last_time_read))
                        break;

                msg += sprintf("%s[%3d]" NOR " %-" + (40 + color_len(notes[i]["title"])) +
                               "s %16s (%s)\n",
                               (notes[i]["time"] > last_time_read ? HIY : ""),
                               i + 1, notes[i]["title"],
                               // notes[i]["author"], ctime(notes[i]["time"])[0..15]);
                               NITAN_VER, TIME_D->replace_ctime(notes[i]["time"]));
#endif
        }

        if (i == sizeof(notes) - 1)
        {
                tell_object(me, "目前没有任何未读过的新闻。\n");
                return;
        }

        msg += HIC "≡" HIY "------------------------------------------------------------------------------" HIC "≡\n" NOR;

        me->start_more(msg);
}

// 此函数当玩家从 F_EDIT 中编辑完成后呼叫
#ifdef DB_SAVE
void done_post(object me, mixed *note, int n, string text)
#else
void done_post(object me, mapping note, int n, string text)
#endif
{
        int i;
        int pl;
        string sign;
        string pure;
        mapping *notes;
#ifdef DB_SAVE
        int t;
        string sql;
#endif

        if( !n)n=query("env/default_sign", me);
        if (! stringp(sign = query(sprintf("env/sign%d", n), me)))
        {
                // 自动选择第一个非空签名
                for (i = 1; i <= 4; i++)
                {
                        sign = query(sprintf("env/sign%d", i), me);
                        if (stringp(sign)) break;
                }
        }

        if (stringp(sign))
        {
                sign = replace_string(sign, "~", "\"");
                sign = replace_string(sign, "", "\\");
                sign = replace_string(sign, "\\n", "\n");
                sign = trans_color(sign, 3);
                pure = filter_color(sign);
                if (strlen(pure) >= 1 &&
                    pure[strlen(pure) - 1] != '\n')
                        sign += "\n";

                pure = filter_color(text);
                pl = strlen(pure);
                if (pl >= 1 && pure[pl - 1] != '\n')
                        text += "\n\n" + sign;
                else
                if (pl >= 2 && pure[pl - 2] != '\n')
                        text += "\n" + sign;
                else
                        text += sign;
        }

        text = color_filter(text) + NOR;
        text = replace_string(text, "\"", "");
#ifdef DB_SAVE
        note[MSG] = text;
        t = sizeof(note);
        sql = "";

        for (i = 0; i < t; i++)
        {
                if (stringp(note[i]))
                        sql += sprintf("\"%s\"", note[i]);
                else if (intp(note[i]))
                        sql += sprintf("%d", note[i]);
                else sql += sprintf("%O", note[i]);

                if (i != t - 1)
                        sql += ",";
        }
        // write(sql);
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_query(sprintf("INSERT INTO %s VALUES (%s)",
                                     NEWS_TABLE, sql));
#else
        note["msg"] = text;
        notes = query("notes");
        if (! pointerp(notes) || ! sizeof(notes))
                notes = ({ note });
        else
        {
                i = sizeof(notes) - 1;
                if (note["time"] <= notes[i]["time"])
                        note["time"] = notes[i]["time"] + 1;
                notes += ({ note });
        }

        // Truncate the notes if maximum capacity exceeded.
        if (sizeof(notes) > MAX_NEWS_CAPACITY)
                notes = notes[MAX_NEWS_CAPACITY / 4 .. MAX_NEWS_CAPACITY];

        set("notes", notes);
#endif
        tell_object(me, "新闻发布完毕。\n");
        message("system", BLINK HIW "\n【新闻精灵】有了最新新闻！各位玩家请用 news 查看。\n\n" NOR,
                users());
        save();
}

// 发布新闻
void do_post(object me, string arg)
{
        int n;
#ifdef DB_SAVE
        mixed *note;
#else
        mapping note;
#endif
        /*
        if (! VERSION_D->is_release_server())
        {
                tell_object(me, "只有在版本发布的站点才能发布新闻。\n");
                return;
        }
        */

        if (! wizardp(me) || ! interactive(me))
        {
                tell_object(me, "只有巫师才能发布新闻。\n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "发布新闻请指定一个标题。\n");
                return;
        }

        if (sscanf(arg, "%s with %d", arg, n) != 2)
                n = 0;

        if (replace_string(arg, " ", "") == "")
                arg = "无标题";
        else
                arg = trans_color(arg, 3) + NOR;
#ifdef DB_SAVE
        note = allocate(5);
        note[TITLE] = arg;
        note[AUTHOR]=me->name(1)+"-"+query("id", me);
        note[TIME] = time();
        note[VIEW] = 0;
#else
        note = allocate_mapping(4);
        note["title"] = arg;
        note["author"]=me->name(1)+"-"+query("id", me);
        note["time"] = time();
#endif
        me->edit(bind((: call_other, __FILE__, "done_post", me, note, n :), me));
}

// 阅读新闻
void do_read(object me, string arg)
{
        int num;
        mixed *notes;
        int last_read_time;

        last_read_time=query("last_read_news", me);
#ifdef DB_SAVE
        notes = query_notes();
#else
        notes = query("notes");
#endif
        if (! pointerp(notes) || ! sizeof(notes))
        {
                tell_object(me, "目前没有任何新闻。\n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "你想读那一条新闻？\n");
                return;
        }

        if (arg == "new" || arg == "next")
        {
                if (! last_read_time)
                        num = 1;
                else
                        for (num = 1; num <= sizeof(notes); num++)
#ifdef DB_SAVE
                                if (notes[num - 1][TIME] > last_read_time)
#else
                                if (notes[num - 1]["time"] > last_read_time)
#endif
                                        break;
        } else
        if (! sscanf(arg, "%d", num))
        {
                tell_object(me, "你要读第几条新闻？\n");
                return;
        }

        if (num < 1 || num > sizeof(notes))
        {
                tell_object(me, "没有这条新闻。\n");
                return;
        }
        num--;
#ifdef DB_SAVE
        me->start_more(sprintf(HIC "≡" HIY "------------------------------------"
                               "------------------------------------------" HIC "≡\n"
                               NOR "[%3d] %-" + (40
#ifndef LONELY_IMPROVED
                                                    + color_len(notes[num][TITLE])
#endif
                                                      ) +
                               "s %16s (%s)\n" HIC "≡" HIY "------------------------------------"
                               "------------------------------------------" HIC "≡\n" NOR,
                               // num + 1, notes[num][TITLE], notes[num][AUTHOR],
                               num + 1, notes[num][TITLE], NITAN_VER,
                               TIME_D->replace_ctime(notes[num][TIME])) + notes[num][MSG]);
        // 添加点击 / 阅读次数
        add_view_time(notes[num], 1);
        // 记录玩家上次阅读新闻的时间
        if (notes[num][TIME] > (int)last_read_time)
                set("last_read_news", notes[num][TIME], me);
#else
        me->start_more(sprintf(HIC "≡" HIY "------------------------------------"
                               "------------------------------------------" HIC "≡\n"
                               NOR " [%3d] %-" + (40 + color_len(notes[num]["title"])) +
                               "s %16s (%s)\n" HIC "≡" HIY "------------------------------------"
                               "------------------------------------------" HIC "≡\n\n" NOR,
                               // num + 1, notes[num]["title"], notes[num]["author"],
                               num + 1, notes[num]["title"], NITAN_VER,
                               TIME_D->replace_ctime(notes[num]["time"])) + notes[num]["msg"]);

        // Keep track which post we were reading last time.
        if (notes[num]["time"] > (int)last_read_time)
                set("last_read_news", notes[num]["time"], me);
#endif
}

// 删除新闻
void do_discard(object me, string arg)
{
        mixed *notes;
        int num;
        string author, aid;
#ifdef DB_SAVE
        string sql;
#endif

        if (! arg || sscanf(arg, "%d", num) != 1)
        {
                tell_object(me, "你想去掉拿一条新闻？\n");
                return;
        }
#ifdef DB_SAVE
        notes = query_notes();
#else
        notes = query("notes");
#endif
        if (! arrayp(notes) || num < 1 || num > sizeof(notes))
        {
                tell_object(me, "没有这条新闻。\n");
                return;
        }

        num--;
#ifdef DB_SAVE
        if ((! stringp(author = notes[num][AUTHOR]) ||
             sscanf(author, "%*s-%s", aid) != 2 ||
             aid != query("id", me)) && !is_root(me) )
            //(string)SECURITY_D->get_status(me) != "(admin)")
        {
                tell_object(me, "只有天神才能去掉他人发布的新闻。\n");
                return;
        }
        sql = sprintf("DELETE FROM %s WHERE title = \"%s\" AND time = %d AND author = \"%s\" AND msg = \"%s\"",
                      NEWS_TABLE, notes[num][TITLE], notes[num][TIME], notes[num][AUTHOR], notes[num][MSG]);
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_query(sql);
#else
        if ((! stringp(author = notes[num]["author"]) ||
             sscanf(author, "%*s-%s", aid) != 2 ||
             aid != query("id", me)) &&
            (string)SECURITY_D->get_status(me) != "(admin)")
        {
                tell_object(me, "只有天神才能去掉他人发布的新闻。\n");
                return;
        }

        notes = notes[0..num - 1] + notes[num + 1..sizeof(notes) - 1];
        set("notes", notes);
        save();
#endif
        tell_object(me, "删除第 " + (num + 1) + " 条新闻....Ok。\n");
}

// 自动通知玩家
void auto_notice(object me)
{
        int num;
        mixed *notes;
        string msg;
        int last_read_time;

        if (! objectp(me))
                return;

        last_read_time=query("last_read_news", me);
#ifdef DB_SAVE
        notes = query_notes();
#else
        notes = query("notes");
#endif

        if (! pointerp(notes) || ! sizeof(notes))
                return;

        num = sizeof(notes) - 1;
#ifdef DB_SAVE
        if (notes[num][TIME] <= last_read_time)
#else
        if (notes[num]["time"] <= last_read_time)
#endif
                return;

        // 还有一些新闻待读，开始新的 call_out
        me->start_call_out(bind((: call_other, __FILE__, "auto_notice", me :), me), 30 + random(30));

        if( !living(me) || query_temp("block_msg/all", me) )
                return;

        while (num-- > 0)
        {
#ifdef DB_SAVE
                if (notes[num][TIME] <= last_read_time)
#else
                if (notes[num]["time"] <= last_read_time)
#endif
                {
                        num++;
                        break;
                }

                // 继续查找下一个
        }

        if (num < 0) num = 0;

        switch (random(5))
        {
        case 0:
                msg = HIM "一阵烟雾过后，新闻精灵出现在你的面前，手里"
                      "捏着一张破破烂烂的纸头，对你宣读起来。\n" NOR;
                break;
        case 1:
                msg = HIM "地上突然开了一个裂缝，冒出一个鬼鬼祟祟的新"
                      "闻精灵，对着你就喋喋不休的罗嗦起来。\n" NOR;
                break;
        case 2:
                msg = HIM "你忽然听见有人喊你，你回头一看，原来是新闻"
                      "精灵满头大汗的跑了过来，\n" NOR;
                break;
        case 3:
                msg = HIM "你刚打了一个哈欠，忽然前面冒出一股烟雾，散"
                      "去以后只见一个新闻精灵懒洋洋的看着你，口中念念有词。\n" NOR;
                break;
        default:
                msg = HIM "“啪啦”一声，新闻精灵狼狈不堪的摔在地上，"
                      "你连忙将他扶起。\n" NOR;
                break;
        }

        msg += HIG "新闻精灵告诉你来自神界的最新消息：\n" NOR;
        tell_object(me, msg);
#ifdef DB_SAVE
        me->start_more(sprintf(HIC "≡" HIY "------------------------------------"
                               "------------------------------------------" HIC "≡\n"
                               NOR "[%3d] %-" + (40 + color_len(notes[num][TITLE])) + "s %16s (%s)\n"
                               HIC "≡" HIY "------------------------------------"
                               "------------------------------------------" HIC "≡\n" NOR,
                               // num + 1, notes[num][TITLE], notes[num][AUTHOR],
                               num + 1, notes[num][TITLE], NITAN_VER,
                               TIME_D->replace_ctime(notes[num][TIME])) + notes[num][MSG]);
        // 添加点击 / 阅读次数
        add_view_time(notes[num], 1);

        // 记录玩家上次阅读新闻的时间
        if (notes[num][TIME] > (int)last_read_time)
                set("last_read_news", notes[num][TIME], me);
#else
        me->start_more(sprintf(HIC "≡" HIY "------------------------------------"
                               "------------------------------------------" HIC "≡\n"
                               NOR "[%3d] %-" + (40 + color_len(notes[num]["title"])) + "s %16s (%s)\n"
                               HIC "≡" HIY "------------------------------------"
                               "------------------------------------------" HIC "≡\n" NOR,
                               // num + 1, notes[num]["title"], notes[num]["author"],
                               num + 1, notes[num]["title"], NITAN_VER,
                               TIME_D->replace_ctime(notes[num]["time"])) + notes[num]["msg"]);

        // Keep track which post we were reading last time.
        if (notes[num]["time"] > (int)last_read_time)
                set("last_read_news", notes[num]["time"], me);
#endif
        tell_object(me, HIM "新闻精灵说完后，消失在一阵烟雾之中。\n" NOR);
}

void do_search(object me, string arg)
{
        mixed *notes;
        int i, last_time_read, j;
        string msg, topic, theway;

#ifdef DB_SAVE
        notes = query_notes();;
#else
        notes = query("notes");
#endif
        if (! arrayp(notes) || ! sizeof(notes))
        {
                tell_object(me, "目前没有任何新闻。\n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "你想搜索那一条新闻？\n");
                return;
        }

        if (sscanf(arg, "%s %s", topic, arg) != 2)
        {
                tell_object(me, "你只能搜索标题(title)、作者(author)、内容(document)。\n");
                return;
        } else
        {
                if (topic == "title")
                        theway = "标题";
                else
                if (topic == "author")
                        theway = "作者";
                else
                if (topic == "document")
                        theway = "内容";
                else
                {
                        tell_object(me, "你只能搜索标题(title)、作者(author)、内容(document)。\n");
                        return;
                }
        }

        last_time_read=query("last_read_news", me);

        msg = sprintf("根据 " HIY "%s" NOR " 搜索 " HIY "%s" NOR " 得到如下符合条件新闻：\n"
                      HIC "≡" HIY "------------------------------------------------------------------------------" HIC "≡\n" NOR,
                      arg, theway);

        i = sizeof(notes);
        j = 0;
        while (i--)
        {
                if (topic == "document")
                {
#ifdef DB_SAVE
                        if (strsrch(notes[i][MSG], arg) == -1)
#else
                        if (strsrch(notes[i]["msg"], arg) == -1)
#endif
                                continue;
                } else
                {
#ifdef DB_SAVE
                        if (topic == "title")
                        {
                                if (strsrch(notes[i][TITLE], arg) == -1)
                                        continue;
                        }  else
                        if (topic == "author")
                        {
                                if (strsrch(notes[i][AUTHOR], arg) == -1)
                                        continue;
                        }
#else
                        if (strsrch(notes[i][topic], arg) == -1)
                                continue;
#endif
                }

                j++;
#ifdef DB_SAVE
                msg += sprintf("%s[%3d]" NOR " %-" + (40 + color_len(notes[i][TITLE])) +
                               "s %16s (%s)\n",
                               (notes[i][TIME] > last_time_read ? HIY : ""),
                               i + 1, notes[i][TITLE],
                               notes[i][AUTHOR], TIME_D->replace_ctime(notes[i][TIME]));
#else
                msg += sprintf("%s[%3d]" NOR " %-" + (40 + color_len(notes[i]["title"])) +
                               "s %16s (%s)\n",
                               (notes[i]["time"] > last_time_read ? HIY : ""),
                               i + 1, notes[i]["title"],
                               notes[i]["author"], TIME_D->replace_ctime(notes[i]["time"]));
#endif
                if (j > 99)
                {
                        msg += HIW "\n由于搜索到的结果太多，因此只显示一百条新闻，请使用更明确的关键字|词。\n" NOR;
                        break;
                }
        }

        if (j == 0)
        {
                tell_object(me, "根据 " HIY + arg + NOR " 搜索 " HIY + theway + NOR " 没有找到符合要求的新闻。\n");
                return;
        }

        msg += HIC "≡" HIY "------------------------------------------------------------------------------" HIC "≡\n" NOR;

        me->start_more(msg);
}

string query_save_file() { return DATA_DIR "newsd"; }
