// This program is a part of NT MudLIB
// bboard.c

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

#define NOTICE                  RED" 曾经沧海难为水，除去巫山不是云" NOR

// 最多容纳 100 个贴子
#define MAX_PLAN                3000

// 假如贴子超过了 MAX_PLAN，删掉前 20 个
#define DEL_TO                  20

// 是否保存所有原来的贴子，是则设为0，否则设为 1
#define SAVE_ALL_OLD_PLAN       0

// 如果需要显示整理情况（很长很长），请：
#define DEBUG                   1

// 最大的标题长度
#define MAX_TITLE_LEN           30

// 发表文章需要的能力
#define NEED_EXP                10000
#define NEED_AGE                15

// 返回note[num]的内容和回文内容
string content(mapping *notes, int num);
string makeup_space(string s, int max);

void setup()
{
        string loc;
        string my_long, my_id;

        if( stringp(loc = query("location")) )
                move(loc);

        my_long = query("long");
        my_id = query("board_id");

        restore();

        set("no_get", 1);
        set("long", my_long);
        set("id", "board");
        set("location", loc);
}

void init()
{
        add_action("do_post", "post");
        add_action("do_followup", "re");
        add_action("do_followup", "followup");
        add_action("do_read", "read");
        add_action("do_discard", "delete");
        add_action("do_discard", "discard");
        add_action("do_banzhu", "banzhu");
        add_action("do_hold", "hold");
        add_action("do_mark", "mark");
        add_action("do_from", "from");
        add_action("do_search", "search");
}

string query_save_file()
{
        string id;

        if( !stringp(id = query("board_id")) ) return 0;
        return DATA_DIR + "board/" + id;
}

string short()
{
        mapping *notes;
        int i, unread, last_read_time;

        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
                return ::short() + " [ 没有任何贴子 ]";

        if( this_player() )
        {
                last_read_time = (int)query("board_last_read/" +
                                 (string)query("board_id"), this_player());
                for (unread = 0, i = sizeof(notes) - 1; i >= 0; i--, unread ++)
                        if( notes[i]["time"] <= last_read_time ) break;
        }
        if( unread )
                return sprintf( HIC "%s" NOR " [ " HIW "%d" NOR " 个贴子，" HIR "%d" NOR " 篇未读 ]",
                                ::short(), sizeof(notes), unread);
        else
                return sprintf("%s [ " HIW "%d" NOR " 个贴子 ]", ::short(), sizeof(notes));
}

string long()
{
        mapping *notes;
        int i, last_time_read;
        string msg;

        msg = query("long");
        if( msg[<1] != '\n' )
                msg += "\n";

        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
                return msg + "\n留言版的使用方法请见 help board。\n" ;

        msg += (query("banzhu") ? ("这个版的的版主是 " WHT + query("banzhu") + NOR "。\n") : "") +
               "───────────────────────────────────\n";

        last_time_read = query("board_last_read/" + (string)query("board_id"), this_player());

        for (i = 0; i < sizeof(notes); i++)
        {
                msg += sprintf("%s[" WHT "%3d" NOR "]" NOR "  %-30s  %12s (%s)\n",
                        (notes[i]["time"] > last_time_read ? HIY: ""),
                        i + 1, notes[i]["title"], notes[i]["author"],
                        TIME_D->replace_ctime(notes[i]["time"]) );
        }

        msg += "───────────────────────────────────\n";
        return msg;
}

int do_from(string arg)
{
        mapping *notes;
        int i,j,last_time_read;
        string msg;

        notes = query("notes");
        msg = query("long");
        if( msg[<1] != '\n' )
                msg += "\n";
        if( !pointerp(notes) || !sizeof(notes) )
                return notify_fail(msg + "\n留言版的使用方法请见 help board。\n");

        if( !arg ) i = 0;
        else i = atoi(arg) - 1;

        if( i < 0 ) i = 0;
        if( i > sizeof(notes) )
                return notify_fail(msg + "\n留言版的使用方法请见 help board。\n");

        msg += (query("banzhu") ? ("这个版的的版主是 " WHT + query("banzhu") + NOR "。\n") : "") +
               "───────────────────────────────────\n";
        last_time_read = query("board_last_read/" + (string)query("board_id"), this_player());

        j = 0;
        for (; i < sizeof(notes); i++)
        {
                msg += sprintf("%s[" WHT "%3d" NOR "]" NOR "  %-30s  %12s (%s)\n",
                        (notes[i]["time"] > last_time_read ? HIY: ""),
                        i + 1, notes[i]["title"], notes[i]["author"],
                        TIME_D->replace_ctime(notes[i]["time"]) );
                j ++;
                if( j > 1000 ) break;
        }

        msg += "───────────────────────────────────\n";
        this_player()->start_more(msg);
        return 1;
}

void done_post(object me, mapping note, int n, string text)
{
        int i, j;
        int pl;
        string sign;
        string pure;
        mapping *notes;
        string *lines;
        string msg = "";

        if( !stringp(text) )
                return;

        if( strlen(text) > 64 * 2048 )
        {
                tell_object(me, "你的留言太长了，请略去一些不必要的。\n");
                return;
        }

        lines = explode(text, "\n");
        i = sizeof(lines);
        if( i > 2000 )
        {
                tell_object(me, "你的留言太长了，请略去一些不必要的。\n");
                return;
        }

        if( i > 20 && strlen(text) / i < 10 )
        {
                tell_object(me, "你的留言中短句太多了，请调整一下以便他人阅读。\n");
                return;
        }

        while (i--)
        {
                // scan all lines
                if( strlen(lines[i]) > 200 )
                {
                        tell_object(me, "你留言中有些行太长了，请分行以便他人阅读。\n");
                        return;
                }
        }

        if( !n ) n = query("env/default_sign", me);
        if( !stringp(sign = query(sprintf("env/sign%d", n), me)) )
        {
                // auto select the first none null sign
                for (i = 1; i <= 4; i++)
                {
                        sign = query(sprintf("env/sign%d", i), me);
                        if( stringp(sign) ) break;
                }
        }

        if( stringp(sign) )
        {
                sign = replace_string(sign, "~", "\"");
                sign = replace_string(sign, "", "\\");
                sign = replace_string(sign, "\\n", "\n");
                sign = trans_color(sign, 1);
                pure = filter_color(sign);
                if( strlen(pure) >= 1 &&
                    pure[strlen(pure) - 1] != '\n')
                        sign += "\n";

                pure = filter_color(text);
                pl = strlen(pure);
                if( pl >= 1 && pure[pl - 1] != '\n')
                        text += "\n\n" + sign;
                else
                if( pl >= 2 && pure[pl - 2] != '\n')
                        text += "\n" + sign;
                else
                        text += sign;
        }

        text = trans_color(text, 3);
        note["msg"] = text;
        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
                notes = ({ note });
        else
        {
                i = sizeof(notes) - 1;
                if( note["time"] <= notes[i]["time"] )
                        note["time"] = notes[i]["time"] + 1;
                notes += ({ note });
        }

        set("notes", notes);
        tell_object(me, HIW "新贴子完成。\n" NOR);
        save();

        if( sizeof(query("notes")) > MAX_PLAN )
        {
                // DEL_TO 以前的贴子将保存到 /data/board/这里的board_id 文件中
                // 删除目前 board 里的 DEL_TO 以前的贴子
                // 需对mark文章保留
                i = 0;
                j = 0;
                while (i<sizeof(notes))
                {
                        if( notes[i]["mark"] != "M" )
                        {
                                msg = content(notes, i);
                                write_file(DATA_DIR + "board/" + query("board_id") + ".old", msg, SAVE_ALL_OLD_PLAN);
                                //notes = notes[0..i-1] + notes[i+1..<1];
                                notes[i] = 0;
                                j ++;
                        }
                        //else  i ++;
                        i ++;

                        if( j == DEL_TO ) break;
                }
                notes -= ({ 0 });
                set("notes", notes);
                save();
                tell_object(me, HIR"……整理完毕，删除 "HIW+(DEL_TO+1)+HIR" 号以前的贴子。\n"NOR);
        }
        return;
}

int do_post(string arg, int n)
{
        mapping note, fam;
        int noname_board;
        string poster_lvl, family;
        object me = this_player();
        string holded;

        poster_lvl = query("poster_level");

        if( !stringp(poster_lvl) )
                poster_lvl = "(player)";

        // write("Board Restricted to " + poster_lvl + " and above.\n");

        if( (int)SECURITY_D->check_wiz_level(me, poster_lvl) < 0 )
                return notify_fail("本板不接受你的投稿。\n");

        if( stringp(holded = query("hold")) &&
            strsrch(holded, "*"+query("id", me)+"*") >= 0 && !wizardp(me) )
                return notify_fail("你在本版的权限已经被封了。\n");

        family = query("poster_family");
        fam = query("family", me);
        noname_board = query("noname_board");

        // write("Board Restricted to " + family + " players only.\n");

        if( stringp(family )
                && (int)SECURITY_D->check_wiz_level(me, "(immortal)") < 0
                && (!mapp(fam) || fam["family_name"] != family) )
                return notify_fail("非本派弟子不得向本板乱涂乱写。\n");

        if( query("avoid_flood")
                && query("combat_exp", me) < NEED_EXP
                && query("age", me) < NEED_AGE )
                return notify_fail("你暂时还没有权力在这里发表文章，需要 " WHT +
                                   NEED_EXP + NOR " 点经验值或者 " WHT + NEED_AGE + NOR " 岁的年龄。\n");

        if( !arg ) return notify_fail("新贴子请指定一个标题。\n");

        if( sscanf(arg, "%s with %d", arg, n) != 2 )
                n = 0;

        if( replace_string(arg, " ", "") == "")
                arg = "无标题";
        /*
        else
                arg = trans_color(arg, 3);
        */
        if( strlen(arg) > MAX_TITLE_LEN )
                return notify_fail("这个标题太长了，请换一个简洁一点的。\n");

        note = allocate_mapping(5);
        note["title"] = arg;

        if( noname_board )
        {
                note["owner"] = "NULL";
                note["author"] = "匿名";
        }
        else
        {
                note["owner"] = query("id", me);
                note["author"] = me->name(1);
        }
        note["time"] = time();
        me->edit((: done_post, me, note, n :));
        return 1;
}

int do_followup(string arg)
{
        int n, num, noname_board;
        string title, file, msg = "";
        mapping note, *notes, fam;
        string poster_lvl, family;
        object me = this_player();
        string holded;

        poster_lvl = query("poster_level");

        if( !stringp(poster_lvl) )
                poster_lvl = "(player)";

        // write("Board Restricted to " + poster_lvl + " and above.\n");

        if( (int)SECURITY_D->check_wiz_level(me, poster_lvl) < 0)
                return notify_fail("本板不接受你的投稿。\n");

        if( stringp(holded = query("hold")) &&
            strsrch(holded, "*"+query("id", me)+"*") >= 0 && !wizardp(me) )
                return notify_fail("你在本版的权限已经被封了。\n");

        family = query("poster_family");
        fam = query("family", me);
        noname_board = query("noname_board");

        // write("Board Restricted to " + family + " players only.\n");

        if( stringp(family)
                && (int)SECURITY_D->check_wiz_level(me, "(immortal)") < 0
                && (!mapp(fam) || fam["family_name"] != family) )
                return notify_fail("非本派弟子不得向本板乱涂乱写。\n");

        if( query("avoid_flood")
                && query("combat_exp", me) < NEED_EXP
                && query("age", me) < NEED_AGE )
                return notify_fail("你暂时还没有权力在这里发表文章，需要 " WHT +
                                   NEED_EXP + NOR " 点经验值或者 " WHT + NEED_AGE + NOR " 岁的年龄。\n");

        if( !arg )
                return notify_fail("请输入欲回复的文章编号或 last 回复最后一篇文章。\n");

        notes = query("notes");

        if( arg == "last" ) num = sizeof(notes);
        else
        if( sscanf(arg, "%d %s", num, title) < 1 )
                return notify_fail("请输入欲回复的文章编号。\n");

        if( sscanf(arg, "%d %s with %d", num, title, n) != 3
                && sscanf(arg, "%d with %d", num, n) != 2 )
                n = 0;

        if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
                return notify_fail("没有这张留言。\n");

        if( title && strlen(title) > MAX_TITLE_LEN )
                return notify_fail("这个标题太长了，请换一个简洁一点的。\n");

        num--;
        file = notes[num]["msg"];

        foreach( string word in explode( file, "\n" ) )
        {
                if( word == "" || word[0..7]=="[1;30m>" ) continue;
                else if( word[0..5] == "[33m>" ) msg += "[1;30m> "+word[5..]+"\n";
                else if( word[0..5] == "[36m>" ) msg += "[33m> "+word[5..]+"\n";
                else msg += "[36m> "+word+"\n";
        }

        if( msg[0..5] == "[36m>" )
                msg = "[36m> ◎" + notes[num]["author"] + " 在 " + TIME_D->replace_ctime(notes[num]["time"]) + " 留下这篇留言：\n" + msg;

        msg += "\n◎" + me->query_idname() + " 在 " + TIME_D->replace_ctime(notes[num]["time"]) + " 留下这篇留言：\n";

        note = allocate_mapping(5);
        if( !title )
                title = (notes[num]["title"][0..5] != "回复：" ? "回复：" : "") + notes[num]["title"];

        note["title"] = title;
        if( noname_board )
        {
                note["owner"] = "NULL";
                note["author"] = "匿名";
        }
        else
        {
                note["owner"] = query("id", me);
                note["author"] = me->name(1);
        }
        note["time"] = time();
        me->edit((: done_post, me, note, n :), msg);
        return 1;
}

int do_read(string arg)
{
        int num/*, rep*/, last_read_time/*, i, last*/, arc, private_board;
        mapping *notes, fam;
        string myid, msg, file;
        string family;
        object me = this_player();
        int len = 0;

        last_read_time = query("board_last_read/" + query("board_id"), me);
        myid    = query("board_id");
        notes   = query("notes");
        arc = query("wizard_only");
        private_board = query("private_board");

        if( arc && !wizardp(me) )
                return notify_fail("巫师内部交流不得窥视。\n");

        family = query("poster_family");
        fam = query("family", me);

        //write("Board Restricted to " + family + " players only.\n");

        if( stringp(family)
                && !wizardp(me)
                && (!mapp(fam) || fam["family_name"] != family) )
                return notify_fail("非本派弟子不得窥视本派内部交流。\n");

        if( !pointerp(notes) || !sizeof(notes) )
                return notify_fail("板子上目前没有任何贴子。\n");

        if( !arg ) return notify_fail("指令格式：read <贴子编号>|new|next|old\n");

        // 显示以前备份的旧贴子
        if( arg == "old" )
        {
                file = DATA_DIR + "board/" + query("board_id") + ".old";
                if( file_size(file) <= 0 )
                        return notify_fail("对不起，目前本版没有保存的旧贴。\n");
                else
                {
                        if( private_board && !wizardp(me) )
                                return notify_fail("对不起，由于旧贴涉及到一些个人隐私，故不开放阅读。\n");

                        msg = read_file(file);
                        me->start_more(msg);
                        return 1;
                }
        }
        // 显示未读的贴子
        if( arg == "new" || arg == "next" )
        {
                if( !intp(last_read_time) || undefinedp(last_read_time) )
                        num = 1;
                else
                        for (num = 1; num <= sizeof(notes); num++)
                        {
                                if( notes[num-1]["time"] > last_read_time )
                                {
                                        if( private_board )
                                        {
                                                if( wizardp(me) ) break;
                                                else if( !strcmp(query("id", me), notes[num - 1]["owner"]) ) break;
                                        } else break;
                                }
                        }

        } else
        if( !sscanf(arg, "%d", num) )
                return notify_fail("你要读第几个贴子？\n");

        if( num < 1 || num > sizeof(notes) )
                return notify_fail("没有这个贴子。\n");
        num--;

        if( !wizardp(me) && private_board && strcmp(query("id", me), notes[num]["owner"]) )
                return notify_fail("这个帖子不是你留的，所以你不能阅读。\n");

        msg = sprintf(  CYN "----------------------------------------------------------------------\n"
                        BWHT BLU " 标 题 " BBLU WHT " %-62s\n"
                        BWHT BLU " 作 者 " BBLU WHT " %-19s   ╭====================================╮\n"
                        BWHT BLU " 篇 数 " BBLU WHT " %-11d           ║"HIR"请文明使用，否则"HIY"你"HIR"或"HIY"帖子"HIR"可能会被删除"NOR BBLU WHT"║\n"
                        BWHT BLU " 时 间 " BBLU WHT " %-19s   ╰====================================╯\n" NOR
                        CYN "----------------------------------------------------------------------\n\n" NOR "%s\n",
                        notes[num]["title"], notes[num]["author"] + "(" + notes[num]["owner"] + ")", num + 1, TIME_D->replace_ctime(notes[num]["time"]),
                        notes[num]["msg"]);

#ifndef LONELY_IMPROVED
        len = color_len(NOTICE);
#endif
        msg +=sprintf(  CYN "----------------------------------------------------------------------\n"
                        CYN "|" NOR "%|"+(68+len)+"s" NOR CYN "|\n" NOR
                        CYN "----------------------------------------------------------------------\n" NOR, NOTICE);

        me->start_more(msg);

        if( notes[num]["time"] > last_read_time )
                me->set("board_last_read/" + query("board_id"),
                        notes[num]["time"]);

        return 1;
}

int do_banzhu(string arg)
{
        string opt;

        if( !arg ) return notify_fail("指令格式： banzhu +|- <版主id>\n");

        if( sscanf(arg, "%s %s", opt, arg) != 2 || opt != "+" && opt != "-" )
                return notify_fail("指令格式： banzhu +|- <版主id>\n");

        if( !wizardp(this_player(1)) && query("owner_id") != query("id", this_player()) )
                return notify_fail("你不是巫师，不可以任命版主。\n");

        if( !stringp(arg) || strlen(arg) < 3 )
                return notify_fail("没有这个人。\n");

        if( opt == "+" )
        {
                if( query("banzhu") == arg )
                        return notify_fail("目前的版主就是 " + arg + "，不需要任命。\n");

                set("banzhu", arg);
                save();
                write("任命 " HIY + arg + NOR " 为" + name() + "版主成功。\n");
        }
        else
        {
                if( !query("banzhu") )
                        return notify_fail("目前没有版主，不需要撤换。\n");

                if( query("banzhu") != arg )
                        return notify_fail("目前的版主不是 " + arg + "，不能撤换。\n");

                delete("banzhu");
                save();
                write("撤换 " HIY + arg + NOR " " + name() + "版主职位成功。\n");
        }
        return 1;
}

int do_hold(string arg)
{
        string opt, holded;

        if( !arg ) return notify_fail("指令格式： hold +|- <id>\n");

        if( sscanf(arg, "%s %s", opt, arg) != 2 || opt != "+" && opt != "-" )
                return notify_fail("指令格式： hold +|- <id>\n");

        if( !stringp(arg) || strlen(arg) < 3 )
                return notify_fail("没有这个人。\n");

        if( !wizardp(this_player(1)) &&
            query("banzhu") != query("id", this_player(1)) )
                return notify_fail("你不是版主，不可以封玩家权限。\n");

        if( !query("hold") ) holded = "0";
        else holded = query("hold");

        if( opt == "+" )
        {
                if( strsrch(holded, "*"+arg+"*") >= 0 )
                        return notify_fail(arg + "已经被封，不需要再费劲了。\n");

                set("hold", query("hold")+"*"+arg+"*");
                save();
                write("封杀 "HIY + arg + NOR" 权限成功。\n");
        }
        else
        {
                if( holded == "0" )
                        return notify_fail("目前没封过人，不需要解封。\n");

                if( !strsrch(holded, "*"+arg+"*") >= 0 )
                        return notify_fail(arg+"没被封权限，不需要解封。\n");

                holded = replace_string(holded, "*"+arg+"*", "");

                set("hold", holded);
                save();
                write("解封 "HIY+arg+NOR" 权限成功。\n");
        }
        return 1;
}

int do_discard(string arg)
{
        mapping *notes;
        int num;

        if( !arg || sscanf(arg, "%d", num) != 1 )
                return notify_fail("指令格式：delete <贴子编号>\n");

        notes = query("notes");
        if( !arrayp(notes)|| num < 1 || num > sizeof(notes) )
                return notify_fail("没有这张贴子。\n");

        else
        {
                num--;
                if( notes[num]["owner"] != (string)query("id", this_player(1))
                        && query("banzhu") != query("id", this_player(1))
                        && wiz_level(this_player(1)) < 6)
                        return notify_fail("这个贴子不是你写的，你又不是版主。\n");

                notes = notes[0..num-1] + notes[num+1..sizeof(notes)-1];
                set("notes", notes);
                write("删除第 " + (num + 1) + " 号贴子....Ok。\n");
                save();
                return 1;
        }
}

int do_mark(string arg)
{
        mapping *notes;
        int num;

        if( !arg || sscanf(arg, "%d",num) != 1 )
                return notify_fail("指令格式：mark <贴子编号>\n");

        notes = query("notes");
        if( !arrayp(notes)|| num <1 || num > sizeof(notes) )
                return notify_fail("没有这张贴子。\n");

        num--;
        if( query("banzhu") != query("id", this_player(1)) &&
            !wizardp(this_player(1)) )
                return notify_fail("你不是版主，无法保留文章。\n");

        if( notes[num]["mark"] == "M" )
        {
                notes[num]["mark"] = " ";
                write("去除第 " + (num+1) + " 号贴子的保留标志成功。\n");
        }
        else
        {
                notes[num]["mark"] = "M";
                write("保留第 " + (num+1) + " 号贴子成功。\n");
        }
        save();
        return 1;
}

string content(mapping *notes, int num)
{
        string msg;

        msg = sprintf("[" WHT "%3d" NOR "]  %-30s  %18s (" WHT "%s" NOR ")\n"
                      "───────────────────────────────────\n%s\n",
                      num + 1,
                      notes[num]["title"],
                      notes[num]["author"] + "(" + notes[num]["owner"] + ")",
                      TIME_D->replace_ctime(notes[num]["time"])[0..9],
                      notes[num]["msg"]);
        return msg;
}

string makeup_space(string s, int max)
{
        string *ansi_char = ({
                BLK,   RED,   GRN,   YEL,   BLU,   MAG,   CYN,   WHT,
                BBLK,  BRED,  BGRN,  BYEL,  BBLU,  BMAG,  BCYN,
                       HIR,   HIG,   HIY,   HIB,   HIM,   HIC,   HIW,
                       HBRED, HBGRN, HBYEL, HBBLU, HBMAG, HBCYN, HBWHT,
                NOR
        });

        string space = s;
        int i, space_count;

        for (i = 0; i < sizeof(ansi_char); i ++)
                space = replace_string(space, ansi_char[i], "", 0);

        space_count = sizeof(s) - sizeof(space);
        if( sizeof(s) >= max )
                space_count = max - sizeof(space);

        space = "";

        for (i = 0; i < space_count; i ++) space += " ";
        return space;
}

int do_search(string arg)
{
        mapping *notes;
        int i, last_time_read, j = 0;
        string msg, topic, note;
        object me = this_player();

        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
        {
                tell_object(me, "目前没有任何帖子。\n");
                return 1;
        }

        if( !arg )
        {
                tell_object(me, "你想搜索那一条帖子？\n");
                return 1;
        }

        if( sscanf(arg, "%s %s", topic, arg) != 2 )
        {
                tell_object(me, "你只能搜索标题(title)、作者(author)、内容(document)。\n");
                return 1;
        } else
        {
                if( topic == "title" ) note = "标题";
                else if( topic == "author" ) note = "作者";
                else if( topic == "document" ) note = "内容";
                else
                {
                        tell_object(me, "你只能搜索标题(title)、作者(author)、内容(document)。\n");
                        return 1;
                }
        }

        last_time_read = query("board_last_read/" + (string)query("board_id"), this_player());
        i = sizeof(notes);

        msg = sprintf("根据 " HIY "%s" NOR " 搜索 " HIY "%s" NOR " 得到如下符合条件帖子：\n"
                      "───────────────────────────────────\n" NOR,
                      arg, note);

        while (i--)
        {
                if( topic == "document" )
                {
                        if( strsrch(notes[i]["msg"], arg) == -1 )
                                continue;
                } else
                {
                        if( strsrch(notes[i][topic], arg) == -1 )
                                continue;
                }
                msg += sprintf("%s[" WHT "%3d" NOR "]" NOR "  %-30s  %12s (%s)\n",
                               (notes[i]["time"] > last_time_read ? HIY: ""),
                               i + 1, notes[i]["title"], notes[i]["author"],
                               TIME_D->replace_ctime(notes[i]["time"]) );

                j ++;
                if( j > 19 ) break;
        }

        msg += "───────────────────────────────────\n";

        if( j == 0 )
        {
                tell_object(me, "根据 " HIY + arg + NOR " 搜索 " HIY + note + NOR " 没有找到符合条件的帖子。\n");
                return 1;
        }

        if( j > 19 )
                msg += "由于搜索到的结果太多，因此只显示二十条留言，请使用更明确的关键字|词。\n";

        me->start_more(msg);
        return 1;
}
