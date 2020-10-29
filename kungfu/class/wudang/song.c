// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "wudang.h"

#define WUDANG    "/clone/book/wudang"
inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;
inherit F_COAGENT;

mixed ask_book1();
mixed ask_book2();
mixed ask_skill();

void create()
{
        set_name("宋远桥", ({ "song yuanqiao", "song" }));
        set("nickname", "武当首侠");
        set("long",
                "他就是张三丰的大弟子、武当七侠之首的宋远桥。\n"
                "身穿一件干干净净的灰色道袍。\n"
                "他已年过六十，身材瘦长，满脸红光。恬淡冲和，沉默寡言。\n");
        set("gender", "男性");
        set("age", 61);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 31);
        set("int", 27);
        set("con", 32);
        set("dex", 30);

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 160);
        set("combat_exp", 1500000);
        set("score", 70000);

        set_skill("force", 200);
        set_skill("yinyun-ziqi", 200);
        set_skill("taiji-shengong", 200);
        set_skill("dodge", 160);
        set_skill("tiyunzong", 160);
        set_skill("unarmed", 185);
        set_skill("taiji-quan", 185);
        set_skill("strike", 185);
        set_skill("wudang-zhang", 185);
        set_skill("zhenshan-zhang", 185);
        set_skill("hand", 185);
        set_skill("paiyun-shou", 185);
        set_skill("parry", 180);
        set_skill("sword", 185);
        set_skill("wudang-jian", 185);
        set_skill("shenmen-jian", 185);
        set_skill("taiji-jian", 185);
        set_skill("taoism", 190);
        set_skill("literate", 120);
        set_skill("medical", 200);
        set_skill("liandan-shu", 200);

        set("no_teach", ([
                "taiji-shengong" : "要想学习太极神功请向张真人请教。",
                "taiji-jian"     : "太极剑必须张真人亲传。",
                "taiji-quan"     : "太极拳必须张真人亲传。",
        ]));

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "zhenshan-zhang");
        map_skill("hand", "paiyun-shou");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("武当派", 2, "弟子");

        set("inquiry", ([
                "武当药理"   : (: ask_book1 :),
                "太极十三式" : (: ask_book2 :),
                "神门刺"     : (: ask_skill :),
                "绝招"       : (: ask_skill :),
        ]));

        set("book_count", 1);

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.zhen" :),
                (: exert_function, "recover" :),
        }) );

        set("coagents", ({
                ([ "startroom" : "/d/wudang/houyuan",
                   "id"        : "yu lianzhou" ]),
        }));

        set("master_ob", 4);
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();

}
void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
        if( query("shen", ob)<25000 )
        {
                command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否还做得不够？");
                return;
        }
        if ((int)ob->query_skill("yinyun-ziqi", 1) < 80)
        {
                command("say 我武当派最注重内功心法" + RANK_D->query_respect(ob)+
                        "是否应该在武当心法上多下点功夫啊?");
                return;
        }
        if ((int)ob->query_skill("taoism", 1) < 80)
        {
                command("say 习武是为了强身健体，一味的练武是不可取的。");
                command("say 我看你还需要在修身养性方面多锻炼锻炼，以提高"
                        "你的道德心法。");
                return;
        }
        command("say 好吧，我就收下你了。");
        command("say 希望你能全心修炼道家心法，领悟道家真髓！");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "taoist" )
                set("class", "taoist", ob);
}

mixed ask_book1()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "武当派" )
                return "你又不是我武当派的传人，这话是什么意思？";

        if( query("shen", me)<10000 )
                return "你侠义正事做得不够，这本书我还不能给你。";

        if ((int)me->query_skill("wudang-yaoli", 1) < 50)
                return "你对武当药理的了解太浅，还是过段时间再说吧。";

        ob = find_object(WUDANG);
        if (! ob) ob = load_object(WUDANG);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "那本药理不就是你拿着在看吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…武当药理现在不在我手里。";

                if( query("family/family_name", owner) == "武当派" )
                        return "那书现在暂时是你同门"+query("name", owner)+
                               "在看，你要用就去找他吧。";
                else
                        return "武当药理经现在落在了"+query("name", owner)+
                               "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        command("say 这本武当药理你就拿去看吧，可要认真研读。");
        command("give liandan miben to "+query("id", me));
        return 1;
}

mixed ask_book2()
{
        object ob;

        if( query("family/family_name", this_player()) != query("family/family_name") )
                return RANK_D->query_respect(this_player()) +
                       "与本派素无来往，不知此话从何谈起？";

        if (query("book_count") < 1)
                return "你来晚了，本派的内功心法不在此处。";

        addn("book_count", -1);
        ob = new("/clone/book/force_book");
        message_vision("$N拿出太极十三式(shu)给$n。\n",
                       this_object(), this_player());
        ob->move(this_player(), 1);
        return "好吧，这本「太极十三式」你拿回去好好钻研。";
}

void reset()
{
        set("book_count", 1);
}

mixed ask_skill()
{
        object me;

        me = this_player();
        if( query("can_perform/shenmen-jian/ci", me) )
                return "你不是已经会了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if( query("shen", me)<140000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("shenmen-jian", 1) < 160)
                return "你的神门十三剑还不到家，要多练练！";

        if( query("family/gongji", me)<200 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        message_vision(HIY "$n" HIY "点了点头，在$N" HIY
                       HIY "耳边轻声嘀咕了几句，又拔出"
                       "腰间长剑，挥舞出几个剑花，然后"
                       "猛地斜斜刺出。\n招式简朴，毫无"
                       "半点华丽可言。\n" NOR,
                       me, this_object());
        command("nod");
        command("say 你可明白了？");
        tell_object(me, HIC "你学会了「神门刺」这一招。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        set("can_perform/shenmen-jian/ci", 1, me);
        addn("family/gongji", -200, me);
        return 1;
}

/*
mixed ask_skill()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/ci", me) )
                return "你不是已经会了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你连太极剑都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<200 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<30000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("force") < 160)
                return "你的内功的修为不够，练高了再来吧。";

        if (me->query_skill("taiji-jian", 1) < 120)
                return "你的太极剑还不到家，要多练练！";

        message_vision(HIY "$n" HIY "点了点头，在$N" HIY "耳边轻声嘀"
                       "咕了几句，又拔出腰间长\n剑，挥舞出几个剑花，"
                       "然后猛地斜斜刺出。招式简朴，毫无\n半点华丽可"
                       "言。\n" NOR, me, this_object());
        command("nod");
        command("say 你可明白了？");
        tell_object(me, HIC "你学会了「神门刺」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/ci", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}
*/

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "绵绵不绝" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/paiyun-shou/mian",
                           "name"    : "绵绵不绝",
                           "sk1"     : "paiyun-shou",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "gongxian": 500,
                           "shen"    : 30000, ]));
                break;

        case "隔山打牛" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhenshan-zhang/da",
                           "name"    : "隔山打牛",
                           "sk1"     : "zhenshan-zhang",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "gongxian": 400,
                           "shen"    : 30000, ]));
                break;

        default:
                return 0;
        }
}
