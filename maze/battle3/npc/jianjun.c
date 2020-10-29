#include <ansi.h>
#define RIDE_CMD        "/cmds/std/ride" 
inherit NPC;

int give_quest(string arg);

void create()
{
        set_name("大宋监军", ({"jian jun", "jian", "jun"}));
        set("title", HIR "大内太监" NOR);
        set("gender", "无性");
        set("age", random(20) + 20);

        set("long", "这是一个京城皇宫中的一名太监，负责抗击蒙古军队入侵大宋的监军。\n");
        set("combat_exp", 800000);
        set("attitude", "peaceful");
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("max_neili", 2000);
        set("neili", 1000);
        set("no_get", 1);
        set("inquiry", ([ 
                "领取任务" : "格式：lingming yayun-liangcao",
        ]));

        setup();
        carry_object("clone/cloth/cloth")->wear();
}

void init()
{
        add_action("give_quest", ({ "lingming" }));
}


int give_quest(string arg)
{
        object me, ob, ling;
        object horse;
        int count;
        
        ob = this_player();
        me = this_object();
        
        if (! arg)
        {
                tell_object(ob, "你想要领命去干什么事情？！\n");
                return 1;
        }
        
        if( query_temp("warquest/party", ob) != "song" )
        {
                tell_object(ob, "你还没有参加宋军，如何领命啊？！\n");
                return 1;
        }
                
        switch(arg)
        {
        case "train-infantry":
        case "xunlian-bubing":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "infantry" )
                {
                        tell_object(ob, "你已经另有他职了！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中几无能战之师，\n命你加紧训练一支精锐步兵，以备不时之需，" +
                               "不得有误！\n" NOR, me, ob);
                set_temp("title", HIW"大宋步兵营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "infantry", ob);
                set_temp("warquest/quest", "训练步兵，作战准备", ob);
                ob->command("drill");
                break;

        case "xunlian-qibing":
        case "train-cavalry":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "cavalry" )
                {
                        tell_object(ob, "你已经另有他职了！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中几无能战之师，\n命你加紧训练一支精锐骑兵，以备不时之需，" +
                               "不得有误！\n" NOR, me, ob);

                set_temp("title", HIR"大宋车骑营统领"NOR, ob);
                if (! present("zhan ma", ob))
                {
                        horse = new("/maze/battle3/song/horse");
                        if (horse->move(environment(ob)))
                                RIDE_CMD->do_ride(ob, horse);
                        else destruct(horse);
                }
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }
                set_temp("warquest/train", "cavalry", ob);
                set_temp("warquest/quest", "训练骑兵，作战准备", ob);
                ob->command("drill");
                break;

        case "train-archer":
        case "xunlian-gongnu":
                if( query_temp("warquest/train", ob )
                 && query_temp("warquest/train", ob) != "archer" )
                {
                        tell_object(ob, "你已经另有他职了！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中几无能战之师，\n命你加紧训练一支精锐弓箭手，以备不时之需，" +
                               "不得有误！\n" NOR, me, ob);
                set_temp("title", HIB"大宋神弩营统领"NOR, ob);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        set("owner",query("id",  ob), ling);
                        ling->move(ob);
                }

                set_temp("warquest/train", "archer", ob);
                set_temp("warquest/quest", "训练弓兵，作战准备", ob);
                ob->command("drill");
                break;
                
        case "houqin-baozhang":
                count = 600000;
                if( WAR_D->query_moneys() < 600000 )
                {
                        message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中粮草匮乏，\n命你火速率部，在半月内将京师供应之粮草押解" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);

                        set_temp("title", HIY"大宋军备营统领"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "forage", ob);
                        set_temp("warquest/quest", "押运粮草，补充军备", ob);
                        ob->command("stock");
                } 
                else if( WAR_D->query_soilders(me) < 2000 )
                {        
                        message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中兵员匮乏，\n命你火速率部，赶去襄阳城内招募新兵" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋军备营统领"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "enlist", ob);
                        set_temp("warquest/quest", "招募新兵，补充兵源", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_weapons(me) < 4000 )
                {               
                        message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中兵器和盔甲匮乏，\n命你火速率部，赶去襄阳城内采购兵器和盔甲" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋军备营统领"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "weapon", ob);
                        set_temp("warquest/quest", "购置兵甲，补充军备", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_arrows(me) < 2000 )
                {
                        message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军营箭楼羽箭匮乏，\n命你火速率部，赶去襄阳城内采购羽箭" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋军备营统领"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "arrow", ob);
                        set_temp("warquest/quest", "购置羽箭，补充军备", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_horses(me) < 2000 )
                {
                        message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中战马匮乏，\n命你火速率部，赶去襄阳城内采购战马" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋军备营统领"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "horse", ob);
                        set_temp("warquest/quest", "购置战马，补充军备", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_stones(me) < 2000 )
                {
                        message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中滚石和檑木匮乏，\n命你火速率部，赶去襄阳城内采购石头和木材" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋军备营统领"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "stone", ob);
                        set_temp("warquest/quest", "购置石木，补充军备", ob);
                        WAR_D->change_moneys(-count);
                        ob->command("stock");
                }
                else if( WAR_D->query_economy(me) < 1200000 )
                {
                        message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来蒙古骑兵常骚扰我大宋襄阳城，\n命你火速率部，赶去襄阳驻守城池" +
                               "，如有延误，军法论处！\n" NOR, me, ob);
                        set_temp("title", HIY"大宋后防营统领"NOR, ob);

                        set_temp("warquest/guard", 1, ob);
                        set_temp("warquest/quest", "守卫襄阳，稳固后方", ob);
                        // ob->command("guard");
                        ob->move("/d/xiangyang/guofuting");
                }
                else
                {
                        message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中粮草匮乏，\n命你火速率部，在半月内将京师供应之粮草押解" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);

                        set_temp("title", HIY"大宋军备营统领"NOR, ob);
                        if (! present("ling jian", ob))
                        {
                                ling = new("/adm/npc/obj/lingjian");
                                set("owner",query("id",  ob), ling);
                                ling->move(ob);
                        }
                        set_temp("warquest/purchase", "forage", ob);
                        set_temp("warquest/quest", "押运粮草，补充军备", ob);
                        ob->command("stock");
                }
                break;
        default:
                tell_object(ob, "你想要领命做什么事情？！\n");
                return 1;
        }

        message_vision("众将领大声应道：末将遵命！！\n", me, ob);
        return 1;
}

int accept_hit(object me)
{
        if (playerp(me))
        {
                command("heng");
                command("say 你要想要找死吗！");
                return 0;
        }
}

int accept_fight(object me)
{
        if (playerp(me))
        {
                command("heng");
                command("say 你要想要找死吗！");
                return 0;
        }
}

int accept_kill(object me)
{
        if (playerp(me))
        {
                message_vision(CYN "$N" CYN "大怒道：“看来你是真的想找死！”，说罢一掌把$n" CYN
                               "劈倒在地。\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
}