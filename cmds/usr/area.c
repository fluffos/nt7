// Copyright (C) 2005, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int do_area_kaifa(object me, string arg);
int do_area_tisheng(object me, string arg);
int show_area_all(object me, string arg);

int sort_areas(string f1, string f2, mapping fame)
{
        if (fame[f2]["bunch_name"] != fame[f1]["bunch_name"])
                return strcmp(fame[f2]["bunch_name"], fame[f1]["bunch_name"]);

        return strcmp(fame[f2]["bunch_name"], fame[f1]["bunch_name"]);
}

void create() { seteuid(getuid()); }

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
        case "kaifa":
                return do_area_kaifa(me, arg);

        case "tisheng":
                return do_area_tisheng(me, arg);

        case "all":
                return show_area_all(me, arg);

        }

        write("无效的参数。\n");
        return 1;
}

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

int do_area_kaifa(object me, string arg)
{
        string fam;
        string *member;
        string area;
        string msg;
        mapping data;
        int j, kaifa, money;
        object npc;

        if( !stringp(fam=query("bunch/bunch_name", me)) )
                return notify_fail("你没有加入任何帮会，无法开发帮会所属地盘。\n");

        if (! arrayp(member = BUNCH_D->query_bunch_areas(fam)))
        {
                write("现在帮派" + fam + "没有任何地盘。\n");
                return 1;
        }

        member -= ({ 0 });

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

        if (! arg)
        {
                msg = sprintf(HIC "\n%-18s%-28s%-8s%-8s%-18s\n" NOR,
                                "地盘名称", "驻守帮众", "开发度", "忠诚度", "上月收入");

                msg += HIY "----------------------------------------------------------------------\n" NOR;

                j = 0;
                foreach (area in member)
                {
                        data = BUNCH_D->query_area_info(area, "dbase");

                        if (! mapp(data)) continue;

                        j++;
                        msg += sprintf(HIC "%-18s%-28s%-8s%-8s%-18s\n" NOR,
                                        data["area_name"],
                                        data["npc_name"] + "(" + data["npc_id"] + ")",
                                        data["kaifa"] + "%",
                                        data["zhongcheng"] + "%",
                                        data["last_money"] / 100 + " 两");
                }

                if (j < 1)
                        return notify_fail(arg + "现在没有任何地盘。\n");

                msg += "\n目前" + HIM + fam + NOR + "共有" + HIM + chinese_number(j) + NOR + "处地盘。\n";
                msg += HIY "----------------------------------------------------------------------\n" NOR;

                write(msg);
                return 1;
        }

        area = base_name(environment(me));

        if (arg != environment(me)->short())
                return notify_fail("你必须到实地才能进行地盘开发！\n");

        if (BUNCH_D->query_area_info(area, "bunch_name") != fam)
                return notify_fail("这里不属于你的帮派地盘，你费什么劲啊！\n");

        if (BUNCH_D->query_area_info(area, "npc_id"))
                npc = present(BUNCH_D->query_area_info(area, "npc_id"), environment(me));

        if (! objectp(npc))
                return notify_fail("负责" + arg + "地盘开发的ＮＰＣ并未就位，无法进行开发！\n");

        data = BUNCH_D->query_all_areas();
        kaifa = data[area]["kaifa"];

        if (kaifa >= 100)
                return notify_fail(arg + "的开发度已达到最大，不需再开发。\n");

        money = kaifa * 10000;

        if( query("balance", me)<money )
        {
                return notify_fail("你帐上的钱不够，开发" + arg + "至少要" +
                                   MONEY_D->money_str(money) + "！\n");
        }

        addn("balance", -money, me);
        me->save();

        BUNCH_D->add_area_info(area, "kaifa", 1);

        write("你花费了" + MONEY_D->money_str(money) + "将地盘" + arg + "的开发度上升了一点！\n");
        return 1;
}

int do_area_tisheng(object me, string arg)
{
        string bunch;
        string someone;
        string *member;
        mapping data;
        int amount;
        int money;
        object ob;
        string area;
        string msg;
        int j;

        if( !stringp(bunch=query("bunch/bunch_name", me)) )
                return notify_fail("你没有参加任何帮会，无法提升任何ＮＰＣ。\n");

        if (! arrayp(member = BUNCH_D->query_bunch_areas(bunch)))
        {
                write("现在帮派" + bunch + "没有任何地盘驻守帮众，你想提升谁的忠诚度呢。\n");
                return 1;
        }

        member -= ({ 0 });

        if (sizeof(member) < 1)
                return notify_fail(bunch + "现在没有任何地盘驻守帮众，你想提升谁的忠诚度呢。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你现在精神不济，无法打听这些消息。\n");

                if (me->is_busy() || me->is_fighting())
                        return notify_fail("你现在正忙，没有时间打听这些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        if (! arg)
        {
                msg = sprintf(HIC "\n%-18s%-28s%-8s%-8s%-18s\n" NOR,
                                "地盘名称", "驻守帮众", "开发度", "忠诚度", "上月收入");

                msg += HIY "----------------------------------------------------------------------\n" NOR;

                j = 0;
                foreach (area in member)
                {
                        data = BUNCH_D->query_area_info(area, "dbase");

                        if (! mapp(data)) continue;

                        j++;
                        msg += sprintf(HIC "%-18s%-28s%-8s%-8s%-18s\n" NOR,
                                        data["area_name"],
                                        data["npc_name"] + "(" + data["npc_id"] + ")",
                                        data["kaifa"] + "%",
                                        data["zhongcheng"] + "%",
                                        data["last_money"] / 100 + " 两");
                }

                if (j < 1)
                        return notify_fail(arg + "现在没有任何地盘驻守帮众。\n");

                msg += "\n目前" + HIM + bunch + NOR + "共有" + HIM + chinese_number(j) + NOR + "处地盘驻守帮众。\n";
                msg += HIY "----------------------------------------------------------------------\n" NOR;

                write(msg);
                return 1;
        }

        if (sscanf(arg, "%d %s", amount, someone) != 2)
                return notify_fail("命令错误，请查看此命令。\n");

        if (amount < 0 || amount > 10)
                return notify_fail("每次提升的值不能小于零也不能大于十点。\n");

        if (! ob = present(someone, environment(me)))
                return notify_fail("这儿没有这么个人。\n");

        if (! ob->is_character())
                return notify_fail("看清楚，它不是生物。\n");

        if (userp(ob))
                return notify_fail("你只能提升本帮ＮＰＣ帮众的技能。\n");

        if (! living(ob))
                return notify_fail("你得先把"+query("name", ob)+"弄醒再说。\n");

        if (ob->is_fighting() || ob->is_busy())
                return notify_fail(query("name", ob)+"正忙着呢。\n");

        if( bunch != query("bunch/bunch_name", ob) )
                return notify_fail("你只能提升本帮会内的ＮＰＣ帮众。\n");

        if (! ob->is_bunch_npc())
                return notify_fail(query("name", ob)+"似乎现在不接受你的提升命令。\n");

        area = base_name(environment(ob));

        if (BUNCH_D->query_area_info(area, "bunch_name") != bunch ||
            BUNCH_D->query_area_info(area,"npc_id") != query("id", ob) )
                return notify_fail(query("name", ob)+"似乎现在不接受你的提升命令。\n");

        if ((int)BUNCH_D->query_area_info(area, "zhongcheng") >=
            query("bunch/max_zhongcheng", ob) )
                return notify_fail(query("name", ob)+"的忠诚度已经达到最大，不需要进行提升了。\n");

        money = amount * 10000;

        if( query("balance", me)<money )
                return notify_fail("你帐上的钱不够，"+query("name", ob)+
                                   "的忠诚度每提升一点需要一两黄金！\n");

        addn("balance", -money, me);
        me->save();

        if ((int)BUNCH_D->query_area_info(area, "zhongcheng") + amount >= 100)
        {
                BUNCH_D->set_area_info(area, "zhongcheng", 100);
                set("bunch/zhongcheng",query("bunch/max_zhongcheng",  ob), ob);
        } else
        {
                BUNCH_D->add_area_info(area, "zhongcheng", amount);
                addn("bunch/zhongcheng", amount, ob);
        }

        write("你花了"+money/10000+"两黄金，将"+query("name", ob)+"的忠诚度提升了"+amount+"点！\n");

        return 1;
}

int show_area_all(object me, string arg)
{
        mapping all_areas;
        string *areas;
        string  city;
        string  area, msg;
        mapping data;
        int     j;

        if (! mapp(all_areas = BUNCH_D->query_all_areas()))
        {
                write("现在泥潭没有任何地盘可被帮派利用。\n");
                return 1;
        }

        areas = keys(all_areas);

        if (sizeof(areas) < 1)
                return notify_fail("泥潭现在没有任何地盘可被帮派利用。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你现在精神不济，无法打听这些消息。\n");

                if (me->is_busy())
                        return notify_fail("你现在正忙，没有时间打听这些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        areas = sort_array(areas, (: sort_areas :), all_areas);
        msg = sprintf(HIC "\n%-18s%-10s%-28s%-14s%-10s\n" NOR,
                      "地盘名称", "城市", "驻守帮众", "所属帮派", "资金(黄金)");

        msg += HIY "--------------------------------------------------------------------------------\n" NOR;

        j = 0;
        foreach (area in areas)
        {
                data = BUNCH_D->query_area_info(area, "dbase");

                if (! mapp(data)) continue;

                city = LOOK_CMD->locate(area);

                j++;
                msg += sprintf(HIC "%-18s%-10s%-28s%-16s%6d\n" NOR,
                               data["area_name"],
                               city,
                               data["npc_name"] + "(" + data["npc_id"] + ")",
                               stringp(data["bunch_name"]) ? data["bunch_name"] : "独 立 中",
                               data["money"] / 10000);
        }

        if (j < 1)
                return notify_fail("现在泥潭没有任何地盘可被帮派利用。\n");

        msg += "\n目前泥潭共有" + HIM + chinese_number(j) + NOR + "处地盘。\n";
        msg += HIY "--------------------------------------------------------------------------------\n" NOR;

        write(msg);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: area kaifa [地盘名] | tisheng [地盘帮众ID] | all

查看目前你所在帮派地盘的各种信息，其中：

kaifa   ：开发帮会中地盘，增加帮会收入。
tisheng ：提升所属帮会中驻守地盘NPC的忠诚度。
all     : 查看所有的地盘信息。

see also: bunch
HELP );
        return 1;
}
