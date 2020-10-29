// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
inherit NPC;

int is_bunch_npc() { return 1; }

int init_area_npc(object ob);
int do_join_bunch(object who);

void setup()
{

        set("bunch/zhengzhao", 1 + random(3));
        ::setup();

        call_out("init_area_npc", 0.5, this_object());
}

string long()
{
        string desc;

        desc = query("long");
        if (! stringp(desc)) desc = "";

        if (query("bunch/bunch_name"))
                return desc;

        desc += HIW + (query("gender") == "男性" ? "他" : "她") +
                "正在寻求帮派势力的庇护，可邀请加入帮派。\n" NOR;

        return desc;
}

int init_area_npc(object ob)
{
        mapping areas, data;
        object room;

        if (! objectp(ob) ||
            ! room = environment(ob))
                return 0;

        if (query("no_fight", room) && query("bunch/zhengzhao") == 1)
                set("bunch/zhengzhao", 3);

        areas = BUNCH_D->query_all_areas();
        // 如果地盘没有加载到系统中，则该地盘没有被帮派占领
        if (undefinedp(areas[base_name(room)]))
                return 0;

        if (areas[base_name(room)]["bunch_name"] == "独立中")
                return 0;

        data = ([ "bunch_name"     : areas[base_name(room)]["bunch_name"],
                  "max_zhongcheng" : 100,
                  "zhongcheng"     : areas[base_name(room)]["zhongcheng"],
                  "zhengzhao"      : query("bunch/zhengzhao"),
        ]);

        set("bunch", data);

        return 1;
}

int accept_object(object who, object ob)
{
        int r;
        mapping data;
        string  *obj;
        string  stuffid, stuffname;

        if (r = ::accept_object(who, ob))
                return r;

        if (!query("bunch/bunch_name", who))
        {
                command("say 即然" + RANK_D->query_respect(who) +
                        "如此客气，那我就收下了。\n");
                return 1;
        }

        if (query("bunch/bunch_name", who) == query("bunch/bunch_name"))
        {
                command("say 都是帮中兄弟，何必如此客气？\n");
                return 0;
        }

        if (query("startroom") != base_name(environment(this_object())))
        {
                command("say 我身体有点不适，你有事等我回去再说吧。\n");
                return 0;
        }

        if (query("bunch/zhengzhao") == 1)
        {
                command("say " + RANK_D->query_self(this_object()) +
                        "只对武功感兴趣，其他一概免谈。\n");
                return 0;
        }

        if (query("bunch/zhengzhao") == 2)
        {
                if (query_temp("invite/target") != who)
                {
                        command("say 无功不受禄，不知" +
                                RANK_D->query_respect(who) + "给我" + ob->name() +
                                "有何用意？\n");
                        return 0;
                }

                if (!query("money_id", ob))
                {
                        command("say " + RANK_D->query_self_rude(this_object()) +
                                 "只对钱有兴趣，你的破玩意自己留着吧。\n");
                        return 0;
                }

                if (ob->value() < query_temp("invite/money") * 10)
                {
                        command("say 我不是说过了吗？" +
                                chinese_number(query_temp("invite/money") / 1000) +
                                "两黄金，少一下子也不行！\n");
                        return 0;
                }

                if (query("bunch/bunch_name") &&
                    query("bunch/zhongcheng") > who->query_kar())
                {
                        command("say 若是收了你的钱，我如何对得起帮中其他弟兄？\n");
                        return 0;
                }

                return do_join_bunch(who);
        }

        if (query("bunch/zhengzhao") == 3)
        {
                data = query_temp("invite/target");

                if (! mapp(data)) data = ([]);

                obj = keys(data);

                if (member_array(query("id", who), obj) == -1)
                {
                        command("say 你我素不相识，为何给" +
                                RANK_D->query_self(this_object()) + ob->name() +
                                "？\n");
                        return 0;
                }

                sscanf (data[query("id", who)], "%s:%s", stuffid, stuffname);

                if (remove_ansi(stuffname) != remove_ansi(query("name", ob))
                ||  stuffid != query("id", ob))
                {
                        command("say " + RANK_D->query_respect(who) +
                                "，我想要的是" + stuffname + "(" +
                                stuffid + ")，不是" + query("name", ob) +
                                "(" + query("id", ob) + ")！\n");
                        return 0;
                }

                if (query("bunch/bunch_name") &&
                    query("bunch/zhongcheng") > query("meili", who))
                {
                        command("say 若是收了你的东西，我如何对得起帮中其他弟兄？\n");
                        return 0;
                }

                return do_join_bunch(who);
        }
}

int do_join_bunch(object who)
{
        string bunch, area;

        if (! stringp(bunch = query("bunch/bunch_name", who)))
        {
                command("say 咦？你没有加入帮会，那我如何加入呢？\n");
                return 0;
        }

        if (bunch == query("bunch/bunch_name"))
        {
                command("say 咱们都是同帮弟兄，有事好商量嘛。\n");
                return 0;
        }

        area = base_name(environment(this_object()));

        command("say 既然" + RANK_D->query_respect(who) +
                "如此看得起" + RANK_D->query_self(this_object()) +
                "，那我也不能对不起你啊。\n");
        message_vision("$N决定加入帮会「" + bunch + "」！\n",
                this_object());

        BUNCH_D->add_area_into_bunch(bunch, area, environment(this_object())->short(), this_object());

        if (query_temp("invite/target"))
               delete_temp("invite/target");

        set("no_clean_up", 1);

        return 1;
}

void die()
{
        mapping areas;
        object room;
        int kaifa, zhongcheng;

        room = environment(this_object());

        areas = BUNCH_D->query_all_areas();
        // 如果地盘没有加载到系统中，则该地盘没有被帮派占领
        if (undefinedp(areas[base_name(room)]))
                return ::die();

        if (query("bunch/bunch_name") == "独立中")
                return ::die();

        kaifa = areas[base_name(room)]["kaifa"];
        kaifa -= (random(10) + 1);
        zhongcheng = areas[base_name(room)]["zhongcheng"];
        zhongcheng -= random(2);

        if (kaifa < 20) kaifa = 20;
        if (zhongcheng < 10) zhongcheng = 10;

        BUNCH_D->set_area_info(base_name(room), "kaifa", kaifa);
        BUNCH_D->set_area_info(base_name(room), "zhongcheng", zhongcheng);

        set("bunch/zhongcheng", zhongcheng);

        message("channel:rumor", HIM "【谣言】某人：由于" + query("name") + "被杀，" +
                                 room->short() + "的开发度降为" + kaifa + "！\n" NOR, users());

        return ::die();
}
