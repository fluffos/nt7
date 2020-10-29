// guojing.c 郭靖

#define RIDE_CMD        "/cmds/std/ride"  
inherit NPC;
#include <ansi.h>

int give_quest(string arg); 
void create()
{
        set_name("郭靖", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY "北侠" NOR);
        set_temp("title", HIW"大宋兵马大元帅"NOR);
        set("gender", "男性");
        set("age", 41);
        set("long",
                "他就是人称北侠的郭靖，既是蒙古成吉思汗的金刀驸马，又是\n"
                "江南七怪、全真派马钰道长、「北丐」洪七公和「老顽童」周\n"
                "伯通等人的徒弟，身兼数门武功。他身着一件灰色长袍，体态\n"
                "魁梧，敦厚的面目中透出一股威严。\n");
        set("attitude", "friendly");
        set_max_encumbrance(100000000);
        set_temp("warquest/party", "song");
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set("chat_chance", 1);
        set("chat_msg", ({
                "郭靖叹了口气道：“蒙古兵久攻襄阳不下，一定会再出诡计，蓉儿又不在身边，这....\n",
                "郭靖说道：“华筝公主近来不知可好，抽空一定要回大漠去看看她。\n",
        }));

        set("inquiry", ([
                "周伯通" : "你见到我周大哥了？他现在可好？\n",
                "老顽童" : "周大哥一贯这样，没点正经！\n",
                "洪七公" : "师父除了吃，就是喜欢玩。到处玩，还是为了找吃的。\n",
                "黄药师" : "那是我泰山大人。他云游四海，神龙见首不见尾的。\n",
                "一灯大师" : "在下对大师好生感激。\n",
                "欧阳锋" : "这个老毒物，害死我六位师父，一待襄阳事了，决不与他干休。\n",
                "黄蓉"   : "蓉儿是我的爱妻，你问她做甚？\n",
                "蓉儿"   : "蓉儿就是蓉儿了。你问这么多干嘛？\n",
                "郭芙"   : "这个女儿，又笨又不听话。\n",
                "郭襄"   : "襄儿生于乱世，这辈子又多艰厄。但愿她能快乐一世。\n",
                "郭破虏" : "那是我的小儿子。\n",
                "杨过"   : "过儿确实有出息。\n",
                "马钰"   : "马道长于我有半师之谊。\n",
                "丘处机" : "邱道长义薄云天，是真豪杰。\n",
                "柯镇恶" : "那是我大师父。\n",
                "朱聪"   : "那是我二师父。\n",
                "韩宝驹" : "那是我三师父。\n",
                "南希仁" : "那是我四师父。\n",
                "张阿生" : "那是我五师父。\n",
                "全金发" : "那是我六师父。\n",
                "韩小莹" : "那是我七师父。\n",
                "丐帮"   : "丐帮英雄几百年了，守卫襄阳多亏了他们。\n",
                "拜师"   : "现在蒙古人围攻襄阳，我哪有心情收徒啊！\n",
                "领取任务" : "格式：lingming houqin-baozhang",
                ]));

        set("qi", 10000);
        set("max_qi", 10000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 34000);
        set("max_neili", 34000);
        set("jiali", 500);

        set("combat_exp", 25000000);
        set("score", 200000);

        set_skill("force", 400);                // 基本内功
        set_skill("huntian-qigong", 400);       // 混天气功
        set_skill("strike", 400);               // 基本拳脚
        set_skill("dragon-strike", 400);        // 降龙十八掌
        set_skill("dodge", 400);                // 基本躲闪
        set_skill("xiaoyaoyou", 400);           // 逍遥游
        set_skill("parry", 400);                // 基本招架
        set_skill("arrow", 400);
        set_skill("lianzhu-arrow", 400);

        map_skill("arrow", "lianzhu-arrow");
        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dragon-strike");
        prepare_skill("strike", "dragon-strike");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dodge.xian" :),
                (: perform_action, "strike.hui" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "strike.leiting" :),
                (: perform_action, "strike.pai" :),
                (: perform_action, "strike.qin" :),
                (: perform_action, "strike.sanhui" :),
                (: perform_action, "strike.xianglong" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shengang" :),
                (: exert_function, "shexin" :),
        }) );

        setup();

        carry_object("/clone/misc/cloth")->wear();
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
