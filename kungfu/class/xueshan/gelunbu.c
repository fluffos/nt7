#include <ansi.h>
#include "xueshan.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

string ask_fashi();
string ask_for_join();
void create()
{
        set_name("葛伦布", ({ "ge lunbu", "ge", "lunbu" }));
        set("long", @LONG
葛伦布是雪山寺护寺僧兵的头领。同时向本寺
第子传授武功。身穿一件黑色袈裟，头带僧帽。
LONG);
        set("title", "雪山寺僧兵头领");
        set("gender", "男性");
        set("class", "bonze");
        set("age", 30);
        set("attitude", "heroism");
        set("shen_type", -1);

        set("str", 30);
        set("int", 20);
        set("con", 28);
        set("dex", 25);

        set("max_qi", 3000);
        set("max_jing", 2000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 80);
        set("level", 15);
        set("combat_exp", 300000);

        set_skill("force", 120);
        set_skill("mizong-neigong", 120);
        set_skill("dodge", 120);
        set_skill("shenkong-xing", 120);
        set_skill("hammer", 140);
        set_skill("staff", 140);
        set_skill("xiangmo-chu", 140);
        set_skill("hand", 120);
        set_skill("dashou-yin", 120);
        set_skill("cuff", 120);
        set_skill("yujiamu-quan", 120);
        set_skill("parry", 120);
        set_skill("lamaism", 100);
        set_skill("literate", 80);
        set_skill("sanscrit", 200);
        set_skill("martial-cognize", 100);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "xiangmo-chu");
        map_skill("hammer", "xiangmo-chu");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.hong" :),
                (: perform_action, "hand.yin" :),
                (: perform_action, "cuff.jiang" :),
                (: exert_function, "recover" :),
        }));

        create_family("密宗", 5, "喇嘛");

        set("inquiry",([
                "剃度" : (: ask_for_join :),
                "出家" : (: ask_for_join :),
                "准备法事" : (: ask_fashi :),
                "法事" : (: ask_fashi :),
        ]));

        set("coagents", ({
                ([ "startroom" : "/d/xueshan/neidian",
                   "id"        : "jinlun fawang", ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "对$n" CYN "冷喝道："
                                "你给我站住！我们雪山寺岂是由得外"
                                "人随便走动地方？" NOR,
                "refuse_carry": CYN "$N" CYN "对$n" CYN "喝道：你"
                                "背上背的是什么人？还不快给我放下"
                                "来！" NOR,
        ]));

        set("master_ob", 1);
        setup();

        carry_object("/d/xueshan/obj/b-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();
        carry_object("/d/xueshan/obj/senggun")->wield();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "男性" )
        {
                command("say 修习密宗内功需要纯阳之体。");
                command("say 这位" + RANK_D->query_respect(ob) + "还是请"
                        "回吧！");
                return;
        }

        command("say 既然你有心习武，我就传你一些武功吧！");
        if( query("class", ob) != "bonze" )
        {
                command("say 若你打算入寺修行上层武功，却非得先" HIY "剃"
                        "度" NOR + CYN "不可。" NOR);
                set("title", "雪山派俗家弟子", ob);
        }
        command("recruit "+query("id", ob));
}

void init()
{
        object ob;

        add_action("do_kneel", "kneel");
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        int bonus, exp_bonus;

//      if( environment(ob)->query("short") == "雪山祭坛" )
        if( !query_temp("作法事", ob))return ;
        {
                message_vision("葛伦布急急忙忙吩咐小喇嘛们往祭坛里填柴，倒酥油。\n\n", ob);
                message_vision(HIR"$N点燃了祭坛中的木柴与酥油，熊熊烈火冲天而起。\n", ob);
                message_vision(HIB"一丝魂魄升出祭坛，冉冉而起。魂魄受$N佛法感召，徘徊不去。\n", ob);
                message_vision(RED"$N端起颅钵吸进一口水，「噗」的一声猛地朝那熊熊火焰喷将过去。\n", ob);
                message_vision(HIC"$N盘腿打坐，神光内蕴，口中念念有辞，渐渐有一丝魂魄在$N面前凝聚成形。\n", ob);
                message_vision(HIG"魂魄越聚越多，竟然呈出人形！$N手指人形，口念真言，指引往生之路。\n", ob);
                message_vision(HIW"$N手持法铃，边走变摇，高声诵读密传经咒。突然大喝一声。声似雷霆。\n", ob);
                message_vision(HIY"大院里光芒四起，一声巨响过后，又恢复了平静。超度完毕。\n"NOR, ob);
                if( query_temp("作法事", ob)>query("combat_exp", ob) )
                {
                        //〖 超度对象的经验高过你，才能有所收益。对象若是玩家，收益十倍计。〗
//                      bonus=(ob->query_temp("作法事") - ob->query("combat_exp")) * ob->query_skill("lamaism",1) / 200;
                        bonus= ob->query_skill("lamaism",1) / 4;
                        exp_bonus=query("combat_exp", ob)*2*bonus/10000;
                        if (exp_bonus> 2000) exp_bonus= 2000;
                        if( query_temp("玩家法事", ob) )
                                addn("combat_exp", exp_bonus, ob);
                        else
                                addn("combat_exp", exp_bonus/10, ob);
                }
                else
                        message_vision(HIR"\n$N不知道哪里找了个菜鸟煞有介事地来超度，看来是白忙了。\n"NOR, ob);
                delete_temp("作法事", ob);
        }
}

string ask_fashi()
{
        mapping fam;
        object ob = this_player();

        if( query("short", environment(this_object())) != "雪山寺山门" )
                return "这里正在做法事，你没看见麽？";
        if( !(fam=query("family", ob)) || fam["family_name"] != "密宗" )
                return "你是那里跳出来的毛虫，也能做个屁法事？";
        if ( ob->query_skill("lamaism",1) < 30)
                return "你的密宗心法还早得很呢，没法让你开坛做法事。";
        set_temp("法事", 1, ob);
        return "这位上人是要给哪位施主做法事呀？";
}

int accept_object(object who, object ob)
{
//      object myenv;
        if( query("money_id", ob) && ob->value() >= 100 )
        {
                message_vision("葛伦布笑着对$N说：好！这位"+RANK_D->query_respect(who) + "要见活佛就请进吧。\n", who);
                set_temp("marks/xueshangate", 1, this_player());
                return 1;
        }
        if( !query_temp("法事", who) )
        {
                message_vision("葛伦布笑着对$N说：这种臭东西给我有什么用，您还是自己留着吧！\n", who);
                return 0 ;
        }
        delete_temp("法事", who);
        if( query("id", ob) == "corpse" )
        {
                message_vision("葛伦布笑着对$N说：那我们去祭坛吧！\n", who);
                set_temp("作法事",query("combat_exp",  ob), who);
                if( query("userp", ob) )
                        set_temp("玩家法事", 1, who);
//              who->set_leader(this_object());
//              command("go north");
//              command("go west");
//              command("go south");
                message_vision("葛伦布往北方离开。\n", who);
                this_object()->move("/d/xueshan/jitan");
                return 1;
        }
        else
                message_vision("葛伦布对$N说：这种东西还能做法事？直接埋了省事。\n", who);
        return 0;
}

string ask_for_join()
{
        object me;

        me = this_player();

        if( query("class", me) == "bonze" )
                return "你已经是出家人了，还跟我罗嗦些什么？";

        if( query("gender", me) != "男性" )
                return "我们雪山寺历来只收男徒，你还是走吧。";

        set_temp("pending/join_bonze", 1, me);

        return "甚好，甚好！你若真心皈依我佛，请跪下(kneel)受戒。";
}

int do_kneel()
{
        object me = this_player();

        if( !query_temp("pending/join_bonze", me) )
                return 0;

        message_vision(HIC "\n$N" HIC "你双手合十，恭恭敬敬地跪了下来。\n\n"
                       NOR + CYN "$n" CYN "看着$N" CYN "说道：好吧，以后你就"
                       "在本寺修行吧。\n\n" HIY "$n" HIY "伸出手掌，在$N" HIY
                       "头顶轻轻地摩挲了几下，随即便将$N" HIY "的头发尽数剃"
                       "去。\n\n" NOR, me, this_object());

        set("class", "bonze", me);
        set("title", "雪山寺喇嘛", me);

        command("nod");
        command("say 既然出了家，就得一心向佛，再不能还俗。");

        return 1;
}