// This program is a part of NT MudLIB
// jian.c 简长老

#include <ansi.h>
#include "gaibang.h"

#define POBU    "/d/gaibang/npc/obj/po-bu"
#define LING    "/d/gaibang/npc/obj/qingzhu-ling"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_me();

void create()
{
        set_name("简长老", ({ "jian zhanglao", "jian", "zhanglao" }));
        set("long", @LONG
简长老是丐邦的执法长老，代帮主执掌法刀以
及青竹令等。他向来嫉恶如仇，弟子中有谁犯
过，出手决不容情。
LONG);
        set("nickname", HIR "执法长老" NOR);
        set("title", "丐帮九袋长老");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "peaceful");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);
        set("max_qi", 4200);
        set("max_jing", 3500);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 180);
        set("combat_exp", 2000000);
        set("level", 20);
        set("score", 500000);
        set("shen_type", 1);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("unarmed", 200);
        set_skill("cuff", 280);
        set_skill("changquan", 200);
        set_skill("hand", 220);
        set_skill("shexing-diaoshou", 220);
        set_skill("strike", 220);
        set_skill("xiaoyaoyou", 220);
        set_skill("parry", 220);
        set_skill("staff", 240);
        set_skill("fengmo-zhang", 220);
        set_skill("jiaohua-bangfa", 220);
        set_skill("blade", 220);
        set_skill("liuhe-dao", 220);
        set_skill("begging", 260);
        set_skill("checking", 260);
        set_skill("literate", 200);
        set_skill("martial-cognize", 200);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "fumo-zhang");
        map_skill("staff", "fengmo-zhang");
        map_skill("strike", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("丐帮", 18, "九袋长老");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.luan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("inquiry", ([
                "青竹令" : (: ask_me :)
        ]));

        set("master_ob",4);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
}

void init()
{
        object ob;
        mapping myfam;

        ::init();
        set_heart_beat(1);
        if (interactive(ob = this_player()) && ! is_fighting()
        &&  file_name(environment(this_object())) == "/d/gaibang/gbandao")
        {
                myfam=query("family", ob);
                if ((! myfam || myfam["family_name"] != "丐帮") &&
                        (! wizardp(ob))) {
                        remove_call_out("saying");
                        call_out("saying", 2, ob);
                }
        }
}

void saying(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        message_sort("\n\n$n看了$N一眼，冷冷地说到：“洪帮主他老人家说我不该"
                     "随意责打丐帮弟子，你又不属我丐帮，我打你总可以吧？”"
                     "说完右腿一抬，$N顺势应了一招青城派的「屁股向后，平沙落雁式」"
                     "－－叭叽\n\n", ob, this_object());
        remove_call_out("kicking");
        call_out("kicking", 1, ob);

}

void kicking(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        ob->move("/d/gaibang/pomiao");
        message("vision","只听“嘭”地一声，紧接着"+query("name", ob)+
                "从小门里飞了出来，屁股上有一个清楚的鞋印。\n", environment(ob), ob);
}

void attempt_apprentice(object ob)
{
        command("hmm");
        command("say 老夫不收徒弟，你还是请回吧。");
}

mixed ask_me()
{
        object ob, me;
        int lvl, gx;

        me = this_player();

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与本帮素无来往，不知此话从何谈起？";

        if( query("combat_exp", me)<10000 )
                return "嘿嘿，你就这点本事也好意思来要青竹令？";

        lvl=query("family/beggarlvl", me);

        if (lvl >= 9)
                return "你已经是本帮长老了，又何去跟后辈们计较。";

        if (lvl <= 0)
                gx = 100;
        else
                gx = lvl * 100 + 200;

        if( query("family/gongji", me)<gx )
                return "你为本帮效力不够，暂时不能给你升袋。";

        if (present("qingzhu ling", me))
                return "你身上不是已经有青竹令了吗？";

        if( time()-query_temp("have_ling", me)<100 )
                return "我不是刚刚才给了你一面吗？稍微等会吧。";

        ob = new(LING);
        ob->move(this_object());

          command("give qingzhu ling to "+query("id", me));
        set_temp("have_ling", time(), me);

        return "凭这面青竹令，你可自由向你的同门大师兄挑战。";
}

int accept_object(object ob, object obj)
{
        object me = this_object();
        int r;
        int lvl, exp, pot, sc, ww, gx;
        string msg;

        if (r = ::accept_object(ob, obj))
                return r;

        if (base_name(obj) != POBU)
        {
                command("say 你给我这种东西干什么？");
                return 0;
        }

        if( query("owner", obj) != ob->name() )
        {
                command("say 你这快破布是从哪里偷来的？");
                return 0;
        }

        if( query_temp("have_cloth", ob)<1 )
        {
                command("say 你真的挑胜了么？我怎么就没听说？");
                return 0;
        }

        lvl=query("family/beggarlvl", ob);

        if (lvl >= 9)
        {
                command("say 你已经是本帮长老了，还想当帮主？");
                return 0;
        }

        if (lvl <= 0)
                gx = 100;
        else
                gx = lvl * 100 + 200;

        if( query("family/gongji", ob)<gx )
        {
                command("say 这个…你为本帮效力不够，暂时不能给你升袋。");
                return 0;
        }

        addn("family/beggarlvl", 1, ob);
        set("title",query_temp("newtitle",  ob), ob);
        delete_temp("have_cloth", ob);
        delete_temp("newtitle", ob);

        message_vision(HIY "\n$N" HIY "接过了破布，然后将其钉"
                       "在$n" HIY "的破衣服上，俨然一个新口袋"
                       "。\n\n" NOR, me, ob);
        command("nod");
        command("say 既然升袋，就当牢记帮规，为民除害！");

        lvl = lvl + 1;
        exp = lvl * 600 + random(lvl * 400);
        pot = lvl * 300 + random(lvl * 200);
        sc = lvl * 80 + random(lvl * 50);
        ww = lvl * 50 + random(lvl * 30);

        addn("combat_exp", exp, ob);
        addn("potential", pot, ob);
        addn("score", sc, ob);
        addn("weiwang", ww, ob);
        addn("family/gongji", -gx, ob);

        msg = HIC "\n通过升袋的经历，你获得了" +
              chinese_number(exp) + "点经验、" +
              chinese_number(pot) + "点潜能、" +
              chinese_number(sc) + "点江湖阅历以及" +
              chinese_number(ww) + "点江湖威望，同时"
              "消耗了" + chinese_number(gx) + "点门"
              "派贡献，武学得到了精进。\n\n" NOR;

        tell_object(ob, sort_string(msg, 54));
        ob->improve_skill("martial-cognize", 1500000);

        destruct(obj);
        return 1;
}

