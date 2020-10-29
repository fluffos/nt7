// who.c
// From ES2

#include <ansi.h>
#include <net/dns.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

//#define PREFIX(ob)    (ob->is_chatter() ? HIC "~" : interactive(ob) ? (query_idle(ob) > 120 ? HIG "*" NOR : " ") : stringp(query("doing", ob)) ? HIY "@" NOR : HIR "#" NOR)
#define PREFIX(ob)    (ob->is_chatter() ? HIC "~" : interactive(ob) ? (query_idle(ob) > 120 ? HIG "*" NOR : " ") : stringp(query("doing", ob)) ? HIY " " NOR : HIR "#" NOR)

int sort_user(object,object);
int sort_user_by_name(object, object, int d);
int help();

mapping party=([
        "duan":         "段氏皇族",
        "emei":         "峨嵋派",
        "gaibang":      "丐帮",
        "gumu":         "古墓派",
        "huashan":      "华山派",
        "hu":           "关外胡家",
        "kunlun":       "昆仑派",
        "mingjiao":     "明教",
        "murong":       "慕容世家",
        "quanzhen":     "全真教",
        "shaolin":      "少林派",
        "shenlong":     "神龙教",
        "songshan":     "嵩山派",
        "taohua":       "桃花岛",
        "tang":         "唐门世家",
        "tianlong":     "天龙寺",
        "tiezhang":     "铁掌帮",
        "wudang":       "武当派",
        "xingxiu":      "星宿派",
        "xueshan":      "大轮寺",
        "lingjiu":      "灵鹫宫",
        "xiaoyao":      "逍遥派",
        "riyue":        "日月神教",
        "ouyang":       "欧阳世家",
        "wudu":       "五毒教",
        "mojiao":       "魔教",
]);

void create() { seteuid(getuid()); }

mixed main(object me, string arg, int remote)
{
        string name, str, *option;
        object *list, *ob, ob1;
        int i, ppl_cnt;
        int opt_interactive;
        int opt_long, opt_wiz, opt_party;
        int opt_chatter, opt_player;
        int opt_male, opt_female, opt_sort;
        int opt_number;
        int opt_master;
        int opt_closed;
        int opt_reborn;
        int cur_time;
        int opt_employ;

        object vob;
        string who_name;
        string who_id;
        string opt_family;

        vob = me;
        opt_chatter = 1;
        opt_player = 1;
        who_name = 0;

        cur_time = time();
        if( !wizardp(me) && cur_time-query_temp("last_who", me)<5 )
        {
              return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");
        }
        set_temp("last_who", cur_time, me);


        if (arg)
        {
                if (arg == "我爱笑傲江湖")
                {
                        str = "";
                        ob = users();
                        i = sizeof(ob);
                        while ( i -- )
                        {
                                if ( !ob[i] )
                                        continue;
                                if (! me->visible(ob[i]))
                                        continue;
                                if( !environment(ob[i]) && !query_temp("waiting_enter", ob[i]) )
                                {
                                        destruct(ob[i]);//有点危险
                                        continue;
                                }
                                str += ADD2(ob[i]);
                        }

                        write(CLEAN2+str);
                        return 1;
                }

                option = explode(arg, " ");
                i = sizeof(option);
                while (i--)
                        switch (option[i])
                        {
                                case "-h": return help();
                                case "-l": opt_long = 1;        break;
                                case "-w": opt_wiz = 1;         break;
                                case "-p": opt_party = 1;       break;
                                case "-fam":
                                           if( !query("family/family_name", me) )
                                                return notify_fail(me->name(1) + "现在还没有加入任何一个门派。\n");
                                           opt_family = me->query_family();    break;
                                case "-f": opt_female = 1;      break;
                                case "-m": opt_male = 1;        break;
                                case "-c": opt_chatter = 1; opt_player = 0;     break;
                                case "-r": opt_player = 1; opt_chatter = 0;     break;
                                case "-u": opt_master = 1;      break;
                                case "-i":
                                case "-s": opt_sort = 1;        break;
                                case "-S": opt_sort = -1;       break;
                                case "-z": opt_reborn = 1;       break;
                                case "-n": opt_number = 1;      break;
                                case "-@": opt_closed = 1;      break;
                                case "-!": opt_interactive = 1; break;
                                case "-v": opt_employ = 1; MYGIFT_D->check_mygift(me, "newbie_mygift/who"); break;
                                default:
                                        if (wizardp(me) &&
                                            option[i][0] == '@')
                                        {
                                                RWHO_Q->send_rwho_q(option[i][1..sizeof(option[i])],
                                                                    me, opt_long);
                                                write("网路讯息已送出，请稍候。\n");
                                                return 1;
                                        }

                                        if (option[i][0] == '-' && !undefinedp(party[option[i][1..<1]]))
                                        {
                                                opt_family = party[option[i][1..<1]];
                                                break;
                                        }

                                        if (i > 0 && option[i - 1] == "is")
                                        {
                                                who_name = option[i];
                                                i--;
                                                break;
                                        }

                                        if (! me) break;
                                        if (environment(me))
                                                ob1 = present(option[i], environment(me));
                                        if (! ob1 || ! me->visible(ob1))
                                                ob1 = find_player(option[i]);
                                        if (! ob1 || ! me->visible(ob1))
                                                ob1 = find_living(option[i]);
                                        if (! ob1 || ! me->visible(ob1))
                                                return notify_fail("没有这个玩家或参数错误。\n指令格式 : who [-h] [-l] [-w] [-p] [-fam] [-m] [-f] [<ID>]\n");
                                        if( !query("family/family_name", ob1) )
                                                return notify_fail(ob1->name(1) + "现在还没有加入任何一个门派。\n");

                                        me = ob1;
                                        opt_family = me->query_family();
                        }
        }

        if (opt_male && opt_female)
        {
                write("参数 -f 和 -m 不能同时使用。\n");
                return 1;
        }

        if (opt_long && me && (vob == this_player()) && ! wizardp(me) && ! remote)
        {
                if( query("jing", me)<5 )
                        return notify_fail("你的精神太差了，没有办法得知其他玩家的详细资料。\n");
                me->receive_damage("jing", 5);
        }

        if (opt_player) ob = users(); else ob = ({ });
        if (opt_chatter && sizeof(MESSAGE_D->query_connection()))
                ob += filter_array(values(MESSAGE_D->query_connection()),
                                   (: objectp :));

        if (opt_party)
        {
                if( !query("bunch/bunch_name", me) )
                        return notify_fail("你现在还没有加入任何一个帮派。\n");
                ob=filter_array(ob,(:query("bunch/bunch_name", $1) ==
                        query("bunch/bunch_name", $2):),me);
        }

        if (opt_family)
        {
                ob = filter_array(ob,(:query("family/family_name", $1) == $(opt_family) :) );
                /*
                if( !query("family/family_name", me) )
                        return notify_fail("你现在还没有加入任何一个门派。\n");
                ob = filter_array(ob,(:query("family/family_name", $1) ==
                        query("family/family_name", $2):),me);
                */
        }

        if (opt_male)
                       ob=filter_array(ob,(:query("gender", $1) == "男性":));

        if (opt_female)
                       ob=filter_array(ob,(:query("gender", $1) == "女性":));

        if (who_name)
        {
                str = WHT + NAME_D->who_is(who_name) + "\n" NOR;
                ob = filter_array(ob, (: $1->name(1) == $(who_name) :));
        } else
                str = "";

        if (opt_wiz)
                ob = filter_array(ob, (: wizardp :));

        if (objectp(vob))
                ob = filter_array(ob, (: $(vob)->visible($1) :));
        else
                ob=filter_array(ob,(:query("env/invisible", $1):));

        if (opt_master)
                ob = filter_array(ob, (: ultrap :));

        if (opt_closed)
        {
                if( !wizardp(me) ) return notify_fail("没有这个玩家或参数错误。\n指令格式 : who [-h] [-l] [-w] [-p] [-fam] [-m] [-f] [<ID>]\n");
                ob=filter_array(ob,(:!interactive($1) && query("doing", $1):));
        }

        if (opt_interactive)
        {
                if( !wizardp(me) ) return notify_fail("没有这个玩家或参数错误。\n指令格式 : who [-h] [-l] [-w] [-p] [-fam] [-m] [-f] [<ID>]\n");
                ob = filter_array(ob, (: interactive($1) :));
        }

        if (opt_reborn)
                ob=filter_array(ob,(:query("reborn/times", $1):));

        if (! sizeof(ob))
        {
                str += "泥潭中现在没有符合条件的玩家。\n";
                if (remote) return str;
                write(str);
                return 1;
        }

        str += HIG "◎" + LOCAL_MUD_NAME() + HIG "◎" + NOR WHT + "  目前江湖中的";
        if (opt_party)
        {
                if( query("bunch/bunch_name", me) )
                        str += HIR + " (" + query("bunch/bunch_name", me) + ") " + NOR WHT;
                else    str += HIC + " (无帮派) " + NOR WHT;
        } else
        if (opt_family)
        {
                str += HIR+"("+opt_family+")"+NOR+WHT;
                /*
                if( query("family/family_name", me) )
                        str+=HIR+"("+query("family/family_name", me)+")"+NOR+WHT;
                else    str += HIC + " (无门派) " + NOR WHT;
                */
        }

        if (! who_name)
                who_name = "";
        else
                who_name = "(" + who_name + ")";

        if (opt_closed)
                str += "修炼中的";

        if (opt_reborn)
                str += "转世重生";

        if (opt_wiz)
                str += (opt_female ? "女性" : opt_male ? "男性" : "") +
                       "巫师" + who_name + "有：";
        else
                if (opt_long) str += (opt_female ? "女性" : opt_male ? "男性" : "") +
                                     (opt_master ? "大宗师" : "玩家") + who_name + "有：";
                else str += (opt_female ? "女性" : opt_male ? "男性" : "") +
                            (opt_master ? "大宗师" : "玩家") + who_name + "有：";

        if (opt_employ)
                str += "<在线的新手导师有>:";

        if (opt_number)
        {
                str += chinese_number(sizeof(ob)) + " 人。\n";
                if (remote) return str;
                write(str);
                return 1;
        }

        str += NOR"\n"HIC"≡" + HIY"---------------------------------------------------------------------------------"HIC"≡\n"NOR;

        if (opt_employ)
        {
                object *virep_ob = ({ });
//              mapping db;
                object cob, eob;
                string *virlist;

                for (i = 0; i < sizeof(ob); i++)
                {
                        cob = ob[i];

                        if (query("viremploy/job", cob))
                        {
                                virep_ob += ({ cob });
                        }
                        continue;
                }
                list = ({ });
                list = virep_ob;
                ppl_cnt = 0;

                str += NOR + HIC "≡" + HIY " 新手导师 " + HIC + "≡\n" NOR;
                ppl_cnt++;
                i = sizeof(list);
                while (i--)
                {
                        if (query("viremploy/job", list[i]) == "新手导师")
                        {
                                ppl_cnt++;
                                str = sprintf("%s%12s%s%s\n",
                                str,
                                RANK_D->query_rank(list[i]),
                                PREFIX(list[i]),
                                list[i]->short(1));
                         }
                }

                if ((query("viremploy/job", me) == "新手导师" || wizardp(me)) && sizeof(virlist = DB_D->query_data("virlist/teacher")))
                {
                        str += NOR + HIC "\n≡"  + HIM "游戏中所有在职导师" + HIC + "≡\n" NOR;
                        for (i = 0; i < sizeof(virlist);i ++)
                        {
                                if (find_player(virlist[i]))
                                {
                                        str += HIY + find_player(virlist[i])->name() + HIY + "(" + virlist[i] + ")--在线\n";
                                }
                                else
                                {
                                        eob = UPDATE_D->global_find_player(virlist[i]);
                                        if( !objectp(eob) ) continue;
                                        str += HIY + eob->name() + HIY + "(" + virlist[i] + ") --离线时间：" + NOR;
                                        str += HIY + sprintf("%d", (time() - query("last_on", eob)) / 86400) + "天\n" NOR;
                                        UPDATE_D->global_destruct_player(eob, 1);

                                }
                        }
                }

                /*
                ppl_cnt++;
                str += NOR "\n" HIC "≡" + HIY " 游戏宣传 " + HIC + "≡\n\n" NOR;
                ppl_cnt++;
                i = sizeof(list);
                while (i--)
                {
                        if (query("viremploy/job", list[i]) == "游戏宣传")
                        {
                                ppl_cnt++;
                                str = sprintf("%s%12s%s%s\n",
                                        str,
                                        RANK_D->query_rank(list[i]),
                                        PREFIX(list[i]),
                                        list[i]->short(1));
                        }
                }
                */

        }
        else
        {

        if (opt_sort)
                list = sort_array(ob, (: sort_user_by_name :), opt_sort);

        else
        {
                // Why I sort the array use too many variable ?
                // Only optimize for speed :)
                // The normal_ob store the ob without family
                // the wiz_ob story the wizards
                // the mapping familys story all the others
                // & why I create generation ? becuase I want
                // to sort the player in one family by the
                // generation, but I won't directly sort them
                // use function:query, it too slow.
                mapping familys = ([ ]);
                mapping generation = ([ ]);
                object *normal_ob = ({ }), *wiz_ob = ({ });
                mapping db;
                mapping fam;
                string fam_name;
                object cob;
                mixed val;

                for (i = 0; i < sizeof(ob); i++)
                {
                        cob = ob[i];
                        if (wizardp(cob))
                        {
                                wiz_ob += ({ cob });
                                continue;
                        }

                        db = cob->query_entire_dbase();
                        if (! mapp(fam = db["family"]) ||
                            ! stringp(fam_name = fam["family_name"]))
                        {
                                normal_ob += ({ cob });
                                continue;
                        }

                        if (! arrayp(familys[fam_name]))
                                familys[fam_name] = ({ cob });
                        else
                                familys[fam_name] += ({ cob });
                        generation[cob] = fam["generation"];
                }

                list = ({ });
                for (i = 0; i < sizeof(val = values(familys)); i++)
                        list += sort_array(val[i], (: $(generation)[$1] -
                                                      $(generation)[$2] :));
                list = wiz_ob + list + normal_ob;
        }

        list = sort_array(list, (: sort_user :));
        ppl_cnt = 0;
        if (opt_long)
        {
                i = sizeof(list);
                while (i--)
                {
                        // Skip those users in login limbo.
                        ppl_cnt++;
                        str = sprintf("%s%12s%s%s\n",
                                str,
                                RANK_D->query_rank(list[i]),
                                PREFIX(list[i]),
                                list[i]->short(1));
                }
        } else
        {
                string fname = "";
                int wiz_cnt,new_cnt;
                int count = 0;
                i = sizeof(list);
                while (i--)
                {
                        // Skip those users in login limbo.
                        who_id = query("id", list[i]);
                        if (! stringp(who_id))
                                who_id = "#" + geteuid(list[i]);

                        if (!wiz_level(list[i]) && fname != query("family/family_name", list[i])) {
                                fname = query("family/family_name", list[i]);
                                if (count % 5) str += "\n";
                                str += sprintf(HIY "%-13s" NOR, (fname?fname:"普通百姓") + "：");
                                count = 1;
                        }

                        if (!new_cnt && wiz_level(list[i]) == 1) {
                                if (count % 5) str += "\n";
                                str += sprintf(HIY "%-13s" NOR, "新手导师：");
                                new_cnt = 1;
                                count = 1;
                        }

                        if (!wiz_cnt && wiz_level(list[i]) > 1) {
                                if (count % 5) str += "\n";
                                str += sprintf(HIY "%-13s" NOR, "管理人员：");
                                wiz_cnt = 1;
                                count = 1;
                        }
                        if (!(count%5)) {
                                count++;
                                str += "             ";
                        }
                        name = query("name", list[i]) + "("+capitalize(who_id)+")";
                        str += sprintf("%s%s%-20s%s",
                                PREFIX(list[i]),
                                wizardp(list[i])?HIY:query("gender", list[i]) == "女性"?HIM:NOR+WHT,
                                name,
                                ++count % 5 ? "" : "\n"
                        );

                        ppl_cnt++;

                        /*
                        name = sprintf("%s%s%-10s(%-12s",
                                        PREFIX(list[i]),
                                        wizardp(list[i])?HIY:query("gender", list[i]) == "女性"?HIM:NOR+WHT,
                                        list[i]->name(1),
                                        capitalize(who_id)+")");

                        str = sprintf("%s%s%s", str, name,
                                      ppl_cnt%3==2?"\n": HIY"│");
                        ppl_cnt++;
                        */
                }
                if( count % 5 ) str += "\n";
                //if (ppl_cnt % 3) str += "\n";
        }
        }

        str += HIC"≡"+HIY"---------------------------------------------------------------------------------"HIC"≡\n"NOR;
        str = sprintf("%s共有 %s 位使用者连线中，系统负担：%s\n "
                      HIG "*" NOR " 表示发呆中，" HIC "~" NOR " 表示聊天中，"
                      HIR "#" NOR " 表示断线中，"HIY"@" NOR" 表示离线修炼中。\n",
                      str, CHINESE_D->chinese_number(ppl_cnt),
                      query_load_average());

        if (remote) return str;
        me->start_more(str);
        return 1;
}

int sort_user_by_name(object ob1, object ob2, int d)
{
        if (wizardp(ob1) && ! wizardp(ob2)) return -1;
        if (wizardp(ob2) && ! wizardp(ob1)) return 1;
        if (wizardp(ob1) && wizardp(ob2))
                return (int)SECURITY_D->get_wiz_level(ob2)
                        - (int)SECURITY_D->get_wiz_level(ob1);

        return strcmp(query("id", ob2),query("id", ob1))*d;
}

int sort_user(object ob1, object ob2)
{
        string name1, name2;
        int l1 = wiz_level(ob1), l2 = wiz_level(ob2);

        if (wizardp(ob1) && ! wizardp(ob2)) return -1;
        if (wizardp(ob2) && ! wizardp(ob1)) return 1;

        if( l1 != l2 ) return l2 - l1;

        //reset_eval_cost();

        name1 = query("family/family_name", ob1);
        name2 = query("family/family_name", ob2);
        if( intp(name1) ) name1 = "";
        if( intp(name2) ) name2 = "";
        return strcmp(name2, name1);
        /*
        if( name1 > name2 ) return -1;
        if( name1 < name2 ) return 1;
        */
        l1 = query("family/generation", ob1);
        l2 = query("family/generation", ob2);
        if( l1 != l2 ) return l1 - l2;

        // sort by playing time.
        return query("online_time", ob2) - query("online_time", ob1);
}

int help()
{
        string *p;
        int i,j;

        write("
指令格式 : who [-h] [-l] [-w] [-p] [-c] [-fam] [-f] [-m] [-s] [-S] [-z] [<ID>] [-n] [is <中文名字>]

这个指令可以列出所有在线上的玩家及其等级。

-h   列出帮助屏幕。
-l   选项列出较长的讯息。
-p   只列出同帮派的玩家。
-fam 只列出同门派的玩家。
-w   只列出线上所有的巫师。
-c   只列出正在聊天的玩家。
-m   只列出江湖中的男性玩家。
-f   只列出江湖中的女性玩家。
-u   只列出江湖中的大宗师们。
-!   只列出江湖中正在连线的玩家
-@   只列出江湖中正在离线修炼的玩家。
-s   按照ID字母升序排列所有的玩家
-S   按照ID字母降序排列所有的玩家
-z   只列出江湖中的转世重生的玩家。
-v   只列出江湖中是新手导师的玩家。
-n   只列出当前符合查找条件的玩家的数目。
<ID> 列出<ID>代表玩家所属门派的玩家。
is   如果使用了这个选项，后面要跟随玩家的中文名字。
-英文代号 只列出该门派的玩家。

"HIG"*"NOR" 表示"HIG"发呆"NOR"中，"HIC "~"NOR" 表示聊天中，"
HIR"#"NOR" 表示"HIR"断线"NOR"中，"HIY"@"NOR" 表示"HIY"离线修炼"NOR"中。

" );
        p = sort_array(keys(party), 1);
        i = sizeof(p);
        j = i;
        write(sprintf("   %-12s%-12s    %-12s%-12s\n","英文代号","门派名","英文代号","门派名"));
        write("----------------------------------------------------------\n");
        for (i=0;i<j/2;i++)
        {
                if (i==(j/2-1))
                {
                        write(sprintf("   %-10s：%-12s\n", p[i], party[p[i]]));
                        continue;
                }
                if (i/2*2==i)
                        write(sprintf("   %-10s：%-12s|", p[i], party[p[i]]));
                else
                        write(sprintf("   %-10s：%-12s\n", p[i], party[p[i]]));
        }
        write("----------------------------------------------------------\n");
        write(@HELP

相关指令： finger
HELP);
        return 1;
}
