// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.
// bunch.c

#include <ansi.h>
#include <command.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

#include "/adm/npc/npcneed.h"

void create() { seteuid(getuid()); }

int sort_bunch(string f1, string f2, mapping fame)
{
        return fame[f2] - fame[f1];
}

int check_item(string item)
{
        int i;

        i = strlen(item);

        if( (strlen(item) < 4) || (strlen(item) > 16 ) ) {
                return 0;
        }
        while(i--) {
                if( item[i]<=' ' ) {
                        return 0;
                }
        if( i%2==0 && !is_chinese(item[i..<0]) ) {
                        return 0;
        }
        }
        return 1;
}

void delete_target(object npc, string name);
int check_bunch(string fame);
string show_ally(object me, string id);
int sort_hatred(string id1, string id2, mapping hatred);
int sort_member(string id1, string id2);
int show_bunch_info(object me, string arg);
int show_bunch_area(object me, string arg);
int show_bunch_member(object me, string arg);
int show_bunch_hatred(object me, string arg);
int show_bunch_all(object me, string arg);
int expell_bunch_member(object me, string arg);
int dismiss_bunch(object me, string arg);
int appoint_bunch_member(object me, string arg);
int inherit_bunch_master(object me, string arg);
int show_bunch_league(object me, string arg);
int bunch_arrest(object me, string arg);
int bunch_invite(object me, string arg);
int join_bunch(object me, string arg);
int bunch_color(object me, string arg);
int bunch_efficient(object me, string arg); // 高效练功

mapping citys = ([
        "city"     : "扬州",
        "changan"  : "长安",
        "chengdu"  : "成都",
]);

int main(object me, string arg)
{
        object *obs;
        string fname;
        string *args;

        if (! arg) arg = "all";
        args = explode(arg, " ");
        if (sizeof(args) > 1)
                arg = implode(args[1..<1], " ");
        else
                arg = 0;

        switch (args[0])
        {
        case "info":
                // 显示同盟的信息
                return show_bunch_info(me, arg);

        case "member":
                return show_bunch_member(me, arg);

        case "dismiss":
                return dismiss_bunch(me, arg);

        case "expell":
        case "kaichu":
                return expell_bunch_member(me, arg);

        case "top":
                return "/cmds/usr/top2"->main(me, "bunch");

        case "area":
                return show_bunch_area(me, arg);

        case "hatred":
                // 显示同盟的仇人
                return show_bunch_hatred(me, arg);

        case "all":
                return show_bunch_all(me, arg);

        case "appoint":
        case "renming":
                return appoint_bunch_member(me, arg);

        case "inherit":
        case "rangwei":
                return inherit_bunch_master(me, arg);

        case "ally":
        case "league":
                return show_bunch_league(me, arg);

        case "arrest":
        case "tongji":
        case "zhuisha":
                return bunch_arrest(me, arg);

        case "invite":
        case "yaoqing":
                return bunch_invite(me, arg);

        case "join":
        case "jiaru":
                return join_bunch(me, arg);

        case "color":
                return bunch_color(me, arg);

        case "battle":
                return BUNCH_D->query_bunch_battle(me);

        case "honors":
                if( !stringp(fname=query("bunch/bunch_name", me)) )
                        return notify_fail("你现在还没有加入任何帮派呢。\n");
                tell_object(me, "你所在的帮派目前帮派荣誉为 "+BUNCH_D->query_bunch_honors(fname)+" 点。\n");
                return 1;

        case "efficient":
                return bunch_efficient(me, arg);

        case "out":
                if( !stringp(fname=query("bunch/bunch_name", me)) )
                        return notify_fail("你现在还没有加入任何帮派呢。\n");

                if( query_temp("pending/out_bunch", me) )
                {
                        // 同盟的声望下降
                        BUNCH_D->add_bunch_fame(fname,-query("weiwang", me));
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                "听说"+me->name(1)+"("+query("id", me)+
                                ")义无反顾，已经背离『" + fname + "』而去。");
                        delete_temp("pending/out_bunch", me);

                        // 清除该用户在同盟中的信息
                        UPDATE_D->clear_user_data(query("id", me),"bunch");
                        return 1;
                }

                write("你真的想要背弃这个帮派吗？这样做会降低" + fname + "的声望。\n"
                      YEL "如果你确定了，就再输入一次 bunch out 命令。\n" NOR);
                set_temp("pending/out_bunch", 1, me);
                return 1;
        }

        write("无效的参数。\n");
        return 1;
}

// 根据玩家和参数选择同盟的名字
mixed select_bunch(object me, string arg)
{
        string fam;
        object ob;

        if (! wizardp(me))
                // only wizard can show every league's list
                fam = 0;
        else
        if (stringp(arg) && arg != "")
        {
                if( !arrayp(query(arg+"/member", get_object(BUNCH_D))) )
                        fam = 0;
                else
                        fam = arg;

                if (! stringp(fam) && objectp(ob = UPDATE_D->global_find_player(arg)))
                {
                        // 没有 arg 这个同盟，查看是否有该玩家
                        fam=query("bunch/bunch_name", ob);
                        UPDATE_D->global_destruct_player(ob);
                        if (! stringp(fam))
                                return notify_fail("这人现在没有加入任何帮派。\n");
                }

                if (! stringp(fam))
                        return notify_fail("没有这个玩家，不能查阅相关的同盟。\n");
        }

        if (! fam)
        {
                // select my league
                if( !stringp(fam=query("bunch/bunch_name", me)) )
                        return notify_fail("你现在还没有加入任何帮派呢。\n");
        }

        return fam;
}


// 显示同盟的仇人
int show_bunch_hatred(object me, string arg)
{
        mapping hatred;
        string fam;
        string *ids;
        mixed *data;
        string msg;
        string st;
        int count;
        int i;

        if (! stringp(fam = select_bunch(me, arg)))
                return 0;

        hatred = BUNCH_D->query_bunch_hatred(fam);
        if (! mapp(hatred) || ! sizeof(hatred))
        {
                write(fam + "现在没有什么仇人。\n");
                return 1;
        }

        ids = keys(hatred) - ({ 0 });
        ids = sort_array(ids, (: sort_hatred :), hatred);

        count = 0;
        msg = WHT "目前" + fam + "在江湖上的仇敌都有\n" NOR
              HIY "--------------------------------\n" NOR;
        for (i = 0; i < sizeof(ids) && count < 30; i++)
        {
                data = hatred[ids[i]];
                if (! arrayp(data) || sizeof(data) < 2 ||
                    ! stringp(data[0]) || ! intp(data[1]))
                        continue;

                st = sprintf("%s(%s%s%s)", data[0], YEL, ids[i], NOR);
                msg += sprintf("%2d. %-34s  %s%-9d%s\n",
                               ++count, st, HIR, data[1], NOR);
        }

        msg += HIY "--------------------------------\n" NOR;
        if (i < sizeof(ids))
                msg += WHT "江湖上的敌人太多，难以尽数。\n" NOR;
        else
                msg += WHT "目前一共是" + chinese_number(i) +
                       "人。\n" NOR;
        write(msg);
        return 1;
}

// 显示某一个同盟中的人员
int show_bunch_member(object me, string arg)
{
        string *member;
        string id;
        object user;
        string msg;
        int n;

        if (! arg)
        {
                if( !stringp(arg=query("bunch/bunch_name", me)) )
                        return notify_fail("你现在还没有加入任何一个帮派呢。\n");
        }

        if (! arrayp(member = BUNCH_D->query_bunch_members(arg)))
        {
                write("现在江湖上没有(" + arg + ")这个帮派。\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(arg + "现在人丁稀落。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你现在精神不济，无法打听这些消息。\n");

                if (me->is_busy())
                        return notify_fail("你现在正忙，没有时间打听这些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        msg = "";
        n = 0;
        foreach (id in member)
        {
                user = UPDATE_D->global_find_player(id);
                if (! objectp(user))
                        continue;

                n++;
                msg += user->short(1) + "\n";
                UPDATE_D->global_destruct_player(user);
        }

        if (msg == "")
                return notify_fail(arg + "现在人丁稀落。\n");

        write(arg + "目前有以下" + chinese_number(n) + "人：\n" + msg);
        return 1;
}

int show_bunch_all(object me, string arg)
{
        mapping fame;
        string *fam;
        string id, bunch;
        object user;
        string msg;
        int n, area, player;

        if (! mapp(fame = BUNCH_D->query_bunch_fame()))
        {
                write("现在江湖上没有任何有名的帮派。\n");
                return 1;
        }

        fam = keys(fame) - ({ 0 });

        if (sizeof(fam) < 1)
                return notify_fail("目前江湖上没有什么有名的帮派。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你现在精神不济，无法打听这些消息。\n");

                if (me->is_busy())
                        return notify_fail("你现在正忙，没有时间打听这些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        fam = sort_array(fam, (: sort_bunch :), fame);

        msg = sprintf(WHT "%-12s%-20s%-10s%-10s%-12s%-10s\n" NOR,
                      "帮会名称", "帮会帮主", "玩家数", "地盘数", "联盟帮派", "总坛");
        msg += HIY "----------------------------------------------------------------------\n" NOR;

        n = 0;
        foreach (bunch in fam)
        {
                id=query(bunch+"/master", get_object(BUNCH_D));
                area = sizeof(BUNCH_D->query_bunch_areas(bunch));
                player = sizeof(BUNCH_D->query_bunch_members(bunch));

                user = UPDATE_D->global_find_player(id);
                if (! objectp(user))
                        continue;

                n++;
                msg += sprintf(WHT "%-12s%-20s%-10s%-10s%-12s%-10s\n" NOR,
                               bunch,query("name", user)+"("+query("id", user)+")",
                               player + " 人", area + " 处",
                               sizeof(BUNCH_D->query_bunch_league(bunch)) + " 个",
                               citys[BUNCH_D->query_bunch_info(bunch, "room_zone")]);

                UPDATE_D->global_destruct_player(user);
        }

        if (n < 1)
                return notify_fail("现在没有任何帮派信息。\n");

        msg += "\n目前泥潭共有" + HIM + chinese_number(n) + NOR + "个帮派。\n";
        msg += HIY "----------------------------------------------------------------------\n" NOR;

        write(msg);
        return 1;
}

// 显示同盟中的信息
int show_bunch_info(object me, string arg)
{
        string fam;
        object  ob;
        string  msg;
        string *member;
        string  id;
        int i;

        if (! stringp(fam = select_bunch(me, arg)))
                return 0;

        if (! arrayp(member = BUNCH_D->query_bunch_members(fam)))
        {
                write("现在江湖上没有(" + fam + ")这个帮派。\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(fam + "现在没有一个帮派玩家。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你现在精神不济，无法打听这些消息。\n");

                if (me->is_busy())
                        return notify_fail("你现在正忙，没有时间打听这些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        /*
        msg = WHT "\n" + fam + "的帮派玩家列表\n" NOR;
        msg += HIY "------------------------------------------------------\n" NOR;
        member = sort_array(member, (: sort_member :));
        foreach (id in member)
        {
                reset_eval_cost();
                msg += sprintf(WHT "%-10s  ", id);
                if (objectp(ob = find_player(id)))
                        msg += sprintf(HIY "在线    "
                                       NOR WHT "职位：" HIM "%-20s "
                                       NOR WHT "等级：" HIR "%-2d\n" NOR,
                                       query("bunch/title", ob),
                                       query("bunch/level", ob));
                else
                        msg += HIR "不在线\n" NOR;
        }

        */
        msg = WHT "\n" + fam + "的帮派资料汇总表\n" NOR;
        msg += HIY "\n------------------------------------------------------\n" NOR;
        msg += WHT + fam + "上个月收入单表\n" NOR;
        msg += HIY "------------------------------------------------------\n" NOR;
        i=query(fam+"/last_area_money", get_object(BUNCH_D));
        if (! intp(i))   i = 0;
        msg += "地盘收入：" + MONEY_D->money_str(i) + "\n\n";
        i=query(fam+"/last_npc_money", get_object(BUNCH_D));
        if (! intp(i))   i = 0;
        msg += "帮众收入：" + MONEY_D->money_str(i) + "\n\n";
        i=query(fam+"/last_bangzhu_money", get_object(BUNCH_D));
        if (! intp(i))   i = 0;
        msg += "帮主所得：" + MONEY_D->money_str(i) + "\n\n";
        msg+="帮派资产："+MONEY_D->money_str(query(fam+"/money", get_object(BUNCH_D)))+"\n\n";
        msg+="帮派荣誉："+BUNCH_D->query_bunch_honors(fam)+"\n\n";
        msg+="帮派福利：双倍经验 "+BUNCH_D->query_bunch_efficient(fam, "exp")+" 秒、";
        msg+="双倍潜能 "+BUNCH_D->query_bunch_efficient(fam, "pot")+" 秒、";
        msg+="双倍体会 "+BUNCH_D->query_bunch_efficient(fam, "mar")+" 秒\n";
        msg += HIY "------------------------------------------------------\n" NOR;

        msg += sprintf("现在%s在江湖上具有 %s%d%s 点声望。\n",
                       fam, HIY, BUNCH_D->query_bunch_fame(fam), NOR);
        write(msg);

        return 1;
}

int show_bunch_area(object me, string arg)
{
        string fam;
        string *member;
        string id;
        mapping area;
        string msg;
        string city;
        int n;

        if (! stringp(fam = select_bunch(me, arg)))
                return 0;

        if (! arrayp(member = BUNCH_D->query_bunch_areas(fam)))
        {
                write("现在帮派" + fam + "没有任何地盘。\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(fam + "现在没有任何地盘。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你现在精神不济，无法打听这些消息。\n");

                if (me->is_busy())
                        return notify_fail("你现在正忙，没有时间打听这些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        msg = sprintf(HIC "\n%-18s%-10s%-28s%-8s%-8s%-18s\n" NOR,
                      "地盘名称", "城市", "驻守帮众", "开发度", "忠诚度", "上月收入");

        msg += HIY "--------------------------------------------------------------------------------\n" NOR;

        n = 0;
        foreach (id in member)
        {
                area = BUNCH_D->query_area_info(id, "dbase");

                if (! mapp(area)) continue;

                city = LOOK_CMD->locate(id);
                n++;
                msg += sprintf(HIC "%-18s%-10s%-28s%-8s%-8s%-18s\n" NOR,
                               area["area_name"], city, area["npc_name"] + "(" + area["npc_id"] + ")",
                               area["kaifa"] + "%",
                               area["zhongcheng"] + "%",
                               area["last_money"] / 100 + " 两");
        }

        if (n < 1)
                return notify_fail(arg + "现在没有任何地盘。\n");

        msg += "\n目前" + HIM + fam + NOR + "共有" + HIM + chinese_number(n) + NOR + "处地盘。\n";
        msg += HIY "--------------------------------------------------------------------------------\n" NOR;
        // me->start_more(msg);
        write(msg);
        return 1;
}

// 显示某一个同盟中的人员
int dismiss_bunch(object me, string arg)
{
        string *member;
        string id;
        object user;
        string msg;
        int n;

        if (wiz_level(me) < wiz_level("(arch)"))
                return notify_fail("你的权限不够，不能强行解散帮派。\n");

        if (! arg)
                return notify_fail("你要解散哪个帮派？\n");

        if (! arrayp(member = BUNCH_D->query_bunch_members(arg)))
        {
                write("现在江湖上没有(" + arg + ")这个帮派。\n");
                return 1;
        }

        write("你强行解散了" + arg + "。\n");
        BUNCH_D->dismiss_bunch(arg);
        return 1;
}

int expell_bunch_member(object me, string arg)
{
        string fname;
        object ob;

        if( !stringp(fname=query("bunch/bunch_name", me)) )
        {
                write("你现在还没有加入任何帮派呢。\n");
                return 1;
        }

        if( query("bunch/level", me) != 7 ||
            BUNCH_D->query_bunch_info(fname,"master") != query("id", me) )
        {
                write("只有帮主才有权利开除某人出帮会！\n");
                return 1;
        }

        if( arg == query("id", me) )
        {
                write("开除自己？你还不如解散你的帮派！\n");
                return 1;
        }

        if (! objectp(ob = find_player(arg)))
        {
                ob = UPDATE_D->global_find_player(arg);

                if (! objectp(ob))
                {
                        write("没有这个玩家。\n");
                        return 1;
                }

                if( query("bunch/bunch_name", ob) != fname )
                {
                        UPDATE_D->global_destruct_player(ob);
                        write("他不是你的帮派中人，你无权开除他！\n");
                        return 1;

                }
                UPDATE_D->global_destruct_player(ob);

        }

        BUNCH_D->add_bunch_fame(fname, -BUNCH_D->query_bunch_fame(fname) / 20);

        if (objectp(ob))
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说"+query("name", ob)+"("+arg+")"+
                        "被帮派『" + fname + "』给开除了。");

        UPDATE_D->clear_user_data(arg, "bunch");

        return 1;
}

int bunch_efficient(object me, string arg)
{
        string fname;
        object ob;

        if( !stringp(fname=query("bunch/bunch_name", me)) )
        {
                write("你现在还没有加入任何帮派呢。\n");
                return 1;
        }

        if( query("bunch/level", me) != 7 ||
            BUNCH_D->query_bunch_info(fname,"master") != query("id", me) )
        {
                write("只有帮主才有权利使用帮派的荣誉点！\n");
                return 1;
        }

        if( !arg || arg == "" )
        {
                write("你要用帮派荣誉点来干什么？\n");
                return 1;
        }

        if( BUNCH_D->query_bunch_honors(fname) < 500 )
        {
                write("你的帮派荣誉点不够！\n");
                return 1;
        }

        switch (arg)
        {
        case "exp":
                BUNCH_D->add_bunch_honors(fname, -500);
                BUNCH_D->set_bunch_efficient(fname, arg, 7200);
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说帮派『" + fname + HIM"』兑换了荣誉点，全帮双倍经验2小时！\n"NOR);
                write("你开始使用帮派荣誉点200点兑换全帮双倍经验2小时！\n");
                break;

        case "pot":
                BUNCH_D->add_bunch_honors(fname,-500);
                BUNCH_D->set_bunch_efficient(fname, arg, 7200);
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说帮派『" + fname + HIM"』兑换了荣誉点，全帮双倍潜能2小时！\n"NOR);
                write("你开始使用帮派荣誉点200点兑换全帮双倍潜能2小时！\n");
                break;

        case "mar":
                BUNCH_D->add_bunch_honors(fname,-500);
                BUNCH_D->set_bunch_efficient(fname, arg, 7200);
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说帮派『" + fname + HIM"』兑换了荣誉点，全帮双倍体会2小时！\n"NOR);
                write("你开始使用帮派荣誉点200点兑换全帮双倍体会2小时！\n");
                break;

        case "yanjiu":
                BUNCH_D->add_bunch_honors(fname,-500);
                BUNCH_D->set_bunch_efficient(fname, arg, 7200);
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说帮派『" + fname + HIM"』兑换了荣誉点，全帮研究效率增加20%持续2小时！\n"NOR);
                write("你开始使用帮派荣誉点200点兑换全帮研究效率增加20%持续2小时！\n");
                break;

        case "jiqu":
                BUNCH_D->add_bunch_honors(fname,-500);
                BUNCH_D->set_bunch_efficient(fname, arg, 7200);
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说帮派『" + fname + HIM"』兑换了荣誉点，全帮汲取效率增加20%持续2小时！\n"NOR);
                write("你开始使用帮派荣誉点200点兑换全帮汲取效率增加20%持续2小时！\n");
                break;
        default:
                write("你使用帮派荣誉点用来兑换什么呢？！\n");
                break;
        }

        return 1;
}

int appoint_bunch_member(object me, string arg)
{
        object ob;
        string name, item, zhiwei, id, n1, n2;
        string banghui;
        int lvl, flag;

        if( !(banghui=query("bunch/bunch_name", me)) )
              return notify_fail("你没有参加任何帮会，无法任命别人职位。\n");

        flag = 0;

        if( query("bunch/level", me) == 7
         || (intp(query("bunch/level", me) )
         && query("bunch/level", me)>2) )
                flag = 1;

        if (! arg)
                return notify_fail("指令格式：bunch appoint <某人> <职务> 或 bunch appoint <某人> <部门> <职务>\n");

        if (! flag)
                return notify_fail("你在帮内职位太低，无权任命别人职位！\n");

        if (sscanf(arg, "%s %s %s", id, item, zhiwei) == 3)
        {
                ob = present(id, environment(me));

                if (! ob) return notify_fail("这儿没有这么个人。\n");

                if (! ob->is_character())
                        return notify_fail("看清楚，那并不是人！\n");

                if (! playerp(ob))
                        return notify_fail("你只对本帮会的玩家使用这条命令！\n");

                if( banghui != query("bunch/bunch_name", ob) )
                        return notify_fail("你只对本帮会的玩家使用这条命令！\n");

                if( query("bunch/level", me)<query("bunch/level", ob) )
                        return notify_fail("对方在帮中的职位比你高，你任命他？搞笑！\n");

                if( query("bunch/level", me) == query("bunch/level", ob) )
                        return notify_fail("对方在帮中的职位和你一样高，你任命他？搞笑！\n");

                if (me->is_busy() || me->is_fighting())
                        return notify_fail("你正忙着呢！\n");

                if (ob->is_busy() || ob->is_fighting())
                        return notify_fail("对方正忙着呢！\n");

                if (ob == me)
                        return notify_fail("自己任命自己？\n");

                if (! check_item(item))
                        return notify_fail("您任命的职务必须是中文，且为二到八字！\n");

                if (zhiwei != "护法" && zhiwei != "舵主" && zhiwei != "坛主"
                &&  zhiwei != "堂主" && zhiwei != "香主" && zhiwei != "门人"
                &&  zhiwei != "帮众")
                        return notify_fail("任命的职位至上而下为：护法,舵主,坛主,堂主,香主,门人,帮众。\n");

                switch (zhiwei)
                {
                case "副帮主":
                        lvl = 6;
                        break;
                case "长老":
                        lvl = 5;
                        break;
                case "护法":
                        lvl = 4;
                        break;
                case "舵主":
                case "坛主":
                case "堂主":
                case "香主":
                        lvl = 3;
                        break;
                case "门人":
                        lvl = 2;
                        break;
                case "帮众":
                        lvl = 1;
                        break;
                }

                if( query("bunch/level", me) <= lvl )
                        return notify_fail("你职位太低，无权任命别人这个职位！\n");

                else
                {
                        set("bunch/title", item+zhiwei, ob);
                        set("bunch/level", lvl, ob);
                        message_vision("$N任命$n为「" + banghui + "」" + item + zhiwei + "！\n", me, ob);
                        return 1;
                }
        }


        if (sscanf(arg, "%s %s", id, name) == 2)
        {
                ob = present(id, environment(me));

                if (! ob) return notify_fail("这儿没有这么个人。\n");

                if (! ob->is_character())
                        return notify_fail("看清楚，那并不是人！\n");

                if (!userp(ob)) return notify_fail("你只对本帮会的玩家使用这条命令！\n");

                if( banghui != query("bunch/bunch_name", ob) )
                        return notify_fail("你只对本帮会的玩家使用这条命令！\n");

                if( query("bunch/level", me) <= query("bunch/level", ob) )
                        return notify_fail("对方在帮中的职位比你高，你任命他？搞笑！\n");

                if (me->is_busy() || me->is_fighting())
                        return notify_fail("你正忙着呢！\n");

                if (ob->is_busy() || ob->is_fighting())
                        return notify_fail("对方正忙着呢！\n");

                if (ob == me)
                        return notify_fail("自己任命自己？\n");

                if (name != "副帮主" && name != "长老" && name != "护法" && name != "舵主"
                &&  name != "坛主" && name != "堂主" && name != "香主" && name != "门人"
                &&  name != "帮众")
                        return notify_fail("任命的职位至上而下为：副帮主，长老, 护法, 舵主, 坛主, 堂主, 香主, 门人, 帮众 。\n");

                switch (name)
                {
                case "副帮主":
                        lvl = 6;
                        break;
                case "长老":
                        lvl = 5;
                        break;
                case "护法":
                        lvl = 4;
                        break;
                case "舵主":
                case "坛主":
                case "堂主":
                case "香主":
                        lvl = 3;
                        break;
                case "门人":
                        lvl = 2;
                        break;
                case "帮众":
                        lvl = 1;
                        break;
                }

                if( query("bunch/level", me) <= lvl )
                        return notify_fail("你职位太低，无权任命别人这个职位！\n");

                else
                {
                        set("bunch/title", name, ob);
                        set("bunch/level", lvl, ob);
                        message_vision("$N任命$n为「" + banghui + "」" + name + "！\n", me, ob);
                        return 1;
                }
        } else
                return notify_fail("指令格式：bunch appoint <某人> <职务> 或 bunch appoint <某人> <部门> <职务>\n");
}

int inherit_bunch_master(object me, string arg)
{
        string banghui;
        object ob;

        seteuid(getuid());

        if( !stringp(banghui=query("bunch/bunch_name", me)) ||
            query("bunch/level", me) != 7 ||
            BUNCH_D->query_bunch_info(banghui,"master") != query("id", me) )
                return notify_fail("只有帮会的帮主才能使用这条指令。\n");

        if (me->is_fighting() || me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if (! arg)
                return notify_fail("你要让位给谁？\n");

        if( query("id", me) == arg )
                return notify_fail("让位给自己？有必要吗？\n");

        if (! ob = present(arg, environment(me)))
                return notify_fail("这儿没有这么个玩家。\n");

        if (! playerp(ob))
                return notify_fail("你只能让位给玩家。\n");

        if( query("bunch/bunch_name", ob) != banghui )
                return notify_fail("你只能让位给本帮会的玩家。\n");

        if (ob->is_fighting() || ob->is_busy())
                return notify_fail("对方正忙着呢。\n");

        BUNCH_D->add_bunch_info(banghui,"master",query("id", ob));

        set("bunch/level", 7, ob);
        set("bunch/title", "帮主", ob);
        set("bunch/title", "老帮主", me);
        set("bunch/level", 6, me);
        ob->save();
        me->save();
        message_vision("$N将帮会「" + banghui + "」的帮主之位让位给了$n。\n", me, ob);
        return 1;
}

int check_bunch(string fame)
{
        if (BUNCH_D->query_bunch_info(fame, "member"))
                return 1;

        return 0;
}

string show_ally(object me, string id)
{
        string *list;
        string str = "";
        int i;

        str += sprintf("目前%s的同盟帮派有：\n\n", id);

        if (! list = BUNCH_D->query_bunch_league(id))
                str += "贵帮派尚无同盟帮派。\n\n";
        else
        {
                for (i = 0; i < sizeof(list); i++)
                {
                        str += sprintf("%s\n", list[i]);
                }
                str += sprintf("\n共 %d 帮派。\n\n", sizeof(list));
        }
        return me->start_more(str);

}

int show_bunch_league(object me, string arg)
{
        object ob;
        string bname, tname;
        int flag, i, j;

        seteuid(getuid());

        if (me->is_busy())
                return notify_fail("你的动作还没有完成。\n");

        if (me->is_fighting())
                return notify_fail("你还在战斗中。\n");

        if( !stringp(bname=query("bunch/bunch_name", me)) )
                return notify_fail("你还没有组建或加入任何帮派。\n");

        if (! arg)
        {
                show_ally(me, bname);
                return 1;
        }

        if( !query("bunch/level", me) ||
            query("bunch/level", me)<7 )
                return notify_fail("你并不是" + bname + "帮派的龙头老大。\n");

        if (sscanf(arg, "%s %s", arg, tname) != 2)
                return notify_fail("指令格式：bunch ally with|cancel <帮派>\n");
        else
        {
                if (! check_bunch(tname))
                        return notify_fail("没有这个帮派。\n");

                if (arg == "with")
                {
                        if (tname == bname)
                                return notify_fail("你不能跟自己结盟。\n");

                        if (BUNCH_D->bunch_is_league(bname, tname) )
                                return notify_fail("此帮派已经跟贵帮派同盟了。\n");

                        if (! ob = find_player((string)BUNCH_D->query_bunch_info(tname, "master")))
                                return notify_fail("对方的帮主不在，你无法对他提出要求。\n");

                        if( me == query_temp("pending/bunch_ally", ob) )
                        {
                                write(HIY "你正式宣告从现在起" + bname + "与" + tname + "达成同盟协议。\n" NOR);
                                shout(HIY + bname + "正式宣告从现在起与" + tname + "达成同盟协议。\n" NOR);
                                BUNCH_D->add_league_into_bunch(bname, tname);
                                delete_temp("pending/bunch_ally", ob);
                                return 1;
                        }
                        else
                        {
                                write(HIY "你提出与" + tname + "的同盟提议。\n" NOR);
                                tell_object(ob,bname+"的"+query("name", me)+"要求和贵帮派建立同盟关系。\n");
                                tell_object(ob, YEL "如果你同意的话，请用 bunch ally with " + bname + "。\n" NOR);
                                set_temp("pending/bunch_ally", ob, me);
                                return 1;
                        }

                }
                else if (arg == "cancel")
                {
                        if (tname == bname)
                                return notify_fail("你不能跟自己解除结盟。\n");

                        if (! BUNCH_D->bunch_is_league(bname, tname))
                                return notify_fail("此帮派并没有跟贵帮派结成同盟。\n");

                        shout(HIY + me->name() + "代表帮派" + bname + "正式宣告从现在起解除与" + tname + "的同盟协议。\n" NOR);
                        BUNCH_D->remove_league_from_bunch(bname, tname);
                        return 1;

                }
                else
                        return notify_fail("指令格式：bunch ally with|cancel <帮派>\n");
        }
}

int bunch_arrest(object me, string arg)
{
        string banghui, msg;
        string str;
        object target;
        string *vendetta = ({ });
        int    i, cnt;

        if( !stringp(banghui=query("bunch/bunch_name", me)) )
                return notify_fail("你还没有组建或加入任何帮派。\n");

        if(! arg)
        {
                msg = HIR "通缉黑名单\n" NOR;
                msg += "----------------------------------------------\n" NOR;

                vendetta = BUNCH_D->query_bunch_info(banghui, "vendetta");

                if (! arrayp(vendetta) || sizeof(vendetta) < 1)
                        return notify_fail("目前没有被本帮派通缉的人。\n");

                cnt = 0;
                for (i = 0; i < sizeof(vendetta); i++)
                {
                        target = UPDATE_D->global_find_player(vendetta[i]);

                        msg+=sprintf("%-18s%s",query("name", target)+"("+query("id", target)+")",
                                      (cnt % 4 == 3 ? "\n" : ""));
                        cnt++;
                }

                if (cnt == 0 || (cnt % 4))
                        msg += "\n";
                msg += "----------------------------------------------\n" NOR;
                me->start_more(msg);
                return 1;
        }

        if( !query("bunch/level", me) ||
              query("bunch/level", me)<7 )
                return notify_fail("你并不是" + banghui + "帮派的龙头老大。\n");


        if (sscanf(arg,"-a %s", str) == 1)
        {
                target = UPDATE_D->global_find_player(str);

                if (! target)
                        return notify_fail("你想追杀的玩家并不存在。\n");

                if (target == me)
                {
                        UPDATE_D->global_destruct_player(target, 1);
                        return notify_fail("追杀自己？没问题吧。\n");
                }

                if (wizardp(target))
                {
                        UPDATE_D->global_destruct_player(target, 1);
                        return notify_fail("追杀巫师？胆子也太大了吧！\n");
                }

                if( query("age", target)<18 )
                {
                        UPDATE_D->global_destruct_player(target, 1);
                        return notify_fail("追杀无名之辈？没问题吧。\n");
                }

                if( query("vendetta/"+banghui, target) )
                {
                        UPDATE_D->global_destruct_player(target, 1);
                        return notify_fail("此玩家已在黑名单中。\n");
                }

                set("vendetta/"+banghui, 1, target);
                target->save();

                vendetta = BUNCH_D->query_bunch_info(banghui, "vendetta");
                if (! arrayp(vendetta)) vendetta = ({ });
                vendetta+=({query("id", target)});

                BUNCH_D->add_bunch_info(banghui, "vendetta", vendetta);

                if( banghui == query("bunch/bunch_name", target) )
                        message("channel:rumor",
                                HIR"【谣言四起】"+ "某人：帮派「"+banghui+"」开始追杀本帮"+
                                query("name", target)+"("+query("id", target)+")，帮中兄弟见到格杀勿论！\n"NOR,users());
                else
                        message("channel:rumor",
                                HIR"【谣言四起】"+"某人：帮派「"+banghui+"」开始追杀"+query("name", target)+"("+query("id", target)+")，帮中兄弟见到格杀勿论！\n"NOR,users());

                UPDATE_D->global_destruct_player(target, 1);
                return 1;
        }

        if (sscanf(arg, "-d %s", str) == 1)
        {
                target = UPDATE_D->global_find_player(str);
                if(! target)    return notify_fail("本游戏中没有这么个玩家。\n");
                if( !query("vendetta/"+banghui, target) )
                {
                        UPDATE_D->global_destruct_player(target, 0);
                        return notify_fail("此玩家并不在追杀的黑名单中。\n");
                }

                delete("vendetta/"+banghui, target);
                target->save();

                vendetta = BUNCH_D->query_bunch_info(banghui, "vendetta");
                if (! arrayp(vendetta)) vendetta = ({ });
                vendetta-=({query("id", target)});
                vendetta -= ({ 0 });
                BUNCH_D->add_bunch_info(banghui, "vendetta", vendetta);
                message("channel:rumor",
                       HIR"【谣言四起】"+"某人：帮派「"+banghui+"」停止追杀"+query("name", target)+"("+query("id", target)+")，给予特赦。\n"NOR,users());
                UPDATE_D->global_destruct_player(target, 1);
                return 1;
        }

        return notify_fail("指令格式：bunch arrest [-a][-d]<玩家ID>\n");
}

int bunch_invite(object me, string arg)
{
        object ob, *target;
        string bunch;
        int money, i, flag;
        mapping data;
        string *what;
        string stuffid, stuffname;

        if (! arg || arg == "")
                return notify_fail("你要邀请谁加入你的帮会？\n");

        if( !stringp(bunch=query("bunch/bunch_name", me)) )
                return notify_fail("你没有参加任何帮会，无法邀请他人加入。\n");

        flag = 0;

        if( intp(query("bunch/level", me)) &&
            query("bunch/level", me)>4 )
                flag = 1;

        if( query("id", me) == arg )
                return notify_fail("邀请自己？！\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("这儿有没这么个人。\n");

        if (! ob->is_character())
                return notify_fail("你只能邀请「人」加入你的帮会。\n");

        if( query("bunch/bunch_name", ob) == query("bunch/bunch_name", me) )
                return notify_fail(query("name", ob)+"已经是本帮弟兄了。\n");

        if (me->is_fighting() || me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if (ob->is_fighting() || ob->is_busy())
                return notify_fail("对方正忙着呢。\n");

        if (! living(ob)) return notify_fail("你得先弄醒他再说。\n");

        if (playerp(ob) && ! flag)
                return notify_fail("你无权邀请玩家加入「" + bunch + "」！\n");

        message_vision("$N邀请$n参加帮会「" + bunch + "」。\n", me, ob);

        if (! playerp(ob))
        {
                if( !query("bunch/zhengzhao", ob) || !ob->is_bunch_npc() )
                        return notify_fail("看样子"+query("name", ob)+
                                "对你的帮会没有兴趣。\n");

                if (sizeof(BUNCH_D->query_areas_in_bunch(bunch)) > BUNCH_D->query_bunch_fame(bunch) / 500000)
                        return notify_fail("由于你的帮派声望不够，看样子"+query("name", ob)+
                                "对你的帮会没有兴趣。\n");

                switch(query("bunch/zhengzhao", ob) )
                {
                case 1:
                        if( (!stringp(bunch=query("bunch/bunch_name", ob)) ||
                            query("bunch/zhongcheng", ob)<query("meili", me)) &&
                            query("qi", ob)*100>query("max_qi", ob)*80 )
                        {
                                message_vision("$N对$n说道：“即是如此，你我不如切磋(qiecuo)一下武功如何？”\n",
                                               ob, me);
                                set_temp("invite/target", me, ob);
                                return 1;
                        }
                        message_vision("$N冲着$n笑道：“我可不敢高攀贵帮啊。”\n", ob, me);
                        return 1;

                case 2:
                        if( !(bunch=query("bunch/bunch_name", ob)) ||
                            query("bunch/zhongcheng", ob)<query("meili", me) )
                        {
                                money=query("combat_exp", ob)/1000;

                                if (money < 1) money = 1;

                                money = money * 1000;
                                message_vision("$N「嘿嘿」了几声，对$n道：“" +
                                               chinese_number(money / 1000) + "两黄金，少一个子也不行。　盶n",
                                               ob, me);
                                set_temp("invite/target", me, ob);
                                set_temp("invite/money", money, ob);
                                return 1;
                        }
                        message_vision("$N冲着$n笑道：“我可不敢高攀贵帮啊。”\n", ob, me);
                        return 1;

                case 3:
                        if( !(bunch=query("bunch/bunch_name", ob) )
                         || query("bunch/zhongcheng", ob)<query("meili", me) )
                        {
                                data=query_temp("invite/target", ob);

                                if (! mapp(data)) data = ([]);

                                target = keys(data);

                                if( member_array(query("id", me),target) != -1 )
                                {
                                        sscanf(data[query("id", me)],"%s:%s",stuffid,stuffname);
                                        message_vision("$N对$n大声道：我不是说过了吗？把" +
                                                       stuffname + "(" + stuffid + ")给我找来！\n",
                                                       ob, me);
                                        return 1;
                                }

                                if (sizeof(target) >= 4)
                                {
                                        message_vision("$N笑道：承蒙大家看得起，" +
                                                       RANK_D->query_respect(ob) + "不胜感激。\n",
                                                       ob);
                                        return 1;
                                }

                                what = keys(npcneed);
                                stuffid = what[random(sizeof(what))];
                                stuffname = npcneed[stuffid];
                                data[query("id", me)]=stuffid+":"+stuffname;
                                set_temp("invite/target", data, ob);
                                message_vision("$N冲着$n道：只要你能在三分钟之内把" +
                                               stuffname + "(" + stuffid + ")" +
                                               "给我找来，一切好商量。\n",
                                               ob, me);

                                // remove_call_out("delete_target");
                                call_out("delete_target",180,ob,query("id", me));
                                return 1;
                        }
                        message_vision("$N冲着$n笑道：“我可不敢高攀贵帮啊。”\n", ob, me);
                        return 1;
                }
        } else
        {
                tell_object(ob,"如果你愿意加入对方的帮会，请使用bunch join "+query("id", me)+"。\n");
                set_temp("invite/target", me, ob);
                return 1;
        }
}

void delete_target(object npc, string name)
{
        mapping data;

        if (! objectp(npc)) return;

        data=query_temp("invite/target", npc);

        if (! mapp(data))   return;

        map_delete(data, name);
        set_temp("invite/target", data, npc);
}

int join_bunch(object me, string arg)
{
        object ob;
        string bunch;

        if (! arg || arg == "")
                return notify_fail("你要加入谁的帮会？\n");

        if( query("combat_exp", me)<1000 )
                return notify_fail("你才初入江湖，在磨练磨练吧。\n");

        if( stringp(bunch=query("bunch/bunch_name", me)) ||
            stringp(bunch=query("league/league_name", me)) )
                return notify_fail("抱歉，你已经是「" + bunch + "」的人了，无法加入其他帮会。\n");

        if (me->is_fighting() || me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if( query("id", me) == arg )
                return notify_fail("你没法这么做！\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("这儿没有这么个人。\n");

        if( query_temp("invite/target", me) != ob )
                return notify_fail("抱歉，"+query("name", ob)+"并没有邀请你参加他的帮会。\n");

        if( !stringp(bunch=query("bunch/bunch_name", ob)) )
                return notify_fail("抱歉，"+query("name", ob)+"现在不属于任何帮会！\n");

        BUNCH_D->add_member_into_bunch(bunch,query("id", me));
        BUNCH_D->add_bunch_fame(bunch,query("weiwang", me)/10);
        set("bunch/time", time(), me);
        set("bunch/bunch_name", bunch, me);
        set("bunch/bunch_id", BUNCH_D->query_bunch_info(bunch,"bunch_id"), me);
        set("bunch/type", BUNCH_D->query_bunch_info(bunch,"type"), me);
        set("bunch/level", 1, me);
        set("bunch/title", "帮众", me);

        message("channel:rumor",HIM"【泥潭帮会】某人："+query("name", me)+
                                 "("+query("id", me)+")加入帮会「"+bunch+
                                 "」，誓死为「" + bunch + "」效力！\n" NOR, users());

        delete_temp("invite/target", me);

        return 1;
}

int bunch_color(object me, string arg)
{
        string banghui;
        string *color = ({ BLK, RED, GRN, YEL, BLU, MAG,
                           CYN, WHT, HIR, HIG, HIY, HIB,
                           HIM, HIC, HIW, NOR, });

        if( !stringp(banghui=query("bunch/bunch_name", me)) )
                return notify_fail("你还没有组建或加入任何帮派。\n");

        if( !query("bunch/level", me) ||
              query("bunch/level", me)<7 )
                return notify_fail("你并不是" + banghui + "帮派的龙头老大。\n");

        if (! arg || arg == "")
                return notify_fail("你要为帮派选择什么帮派颜色？\n");

        arg = color_filter(arg);
        if (member_array(arg, color) == -1)
                return notify_fail("你要为帮派选择什么帮派颜色有问题，请重新选择！\n");

        BUNCH_D->add_bunch_info(banghui, "color", arg);
        tell_object(me, "你为帮派选择了 " + arg + "颜色显示示例" + NOR + " 的颜色。\n");
        return 1;
}

// 给所有的仇恨对象排序
int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return 1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return -1;

        return d2[1] - d1[1];
}

// 给同盟中的所有结义成员排序
int sort_member(string id1, string id2)
{
        object ob1, ob2;

        ob1 = find_player(id1);
        ob2 = find_player(id2);
        if (! objectp(ob1) && ! objectp(ob2))
                return strcmp(id2, id1);

        if (objectp(ob1) && objectp(ob2))
                return query("combat_exp",ob2)/100 - query("combat_exp",ob1)/100;

        if (objectp(ob1))
                return -1;

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: bunch info [玩家] | hatred [玩家] | member [帮派名字]
          bunch top | out | area | all | expell | appoint | inherit
          ally | war | surrender | agree | arrest | invite | join | color

查看目前你所在帮派的各种信息，其中：

info   ：查看帮派中的人物，成员状态，声望。
hatred ：查看帮派的仇恨对象。
member ：查看某个帮派的成员。
top    ：查看帮派的声望排名。
area   : 查看帮派的地盘信息。
out    : 脱离自己所在的帮派。
all    : 查看所有的帮派信息。
expell : 开除帮派中的成员，会降低帮派声望。
appoint: 任命帮派成员位阶及职衔。
inherit: 禅让出帮主之位给帮里其他人。
ally   : 查看帮派联盟及与其他帮派结盟。
war    : 对某个帮派宣布战争。(未开放)
surrender: 向对战状态的帮派求和。(未开放)
agree  : 接受对战状态的帮派求和。(未开放)
arrest : 帮派通缉令。
invite : 邀请某人加入你的帮会。某人可以是玩家或是可征招的ＮＰＣ。
join   : 加入某个帮派。
tax    : 设定帮派税率。(未开放)
doc    : 编写帮派说明。(未开放)
color  : 帮主为帮派设置帮派的颜色。
battle : 查看当前帮战情况。
efficient:帮主使用帮派荣誉点让全帮高效练功。

巫师可以查看各个帮派的信息，只需要在命令后面加上帮派的名字或
是帮派中的玩家。另外巫师可以使用 bunch dismiss  命令强行解散
一个帮派。

see also: area, faxiang
HELP );
        return 1;
}
