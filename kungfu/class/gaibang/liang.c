// This program is a part of NT MudLIB
// liang.c 梁长老

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_GUARDER;

#include "fight.h"

mixed  ask_skill1();
string ask_baicao();
string ask_xhwan();

void create()
{
        set_name("梁长老", ({ "liang zhanglao", "liang", "zhanglao" }));
        set("long", @LONG
梁长老是丐帮出道最久，武功最高的长老，在
武林中享名已久。丐帮武功向来较强，近来梁
长老一力整顿，更是蒸蒸日上。
LONG);
        set("nickname", HIR "传功长老" NOR);
        set("title", "丐帮九袋长老");
        set("gender", "男性");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4200);
        set("max_jing", 3200);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 200);
        set("combat_exp", 2200000);
        set("level", 20);
        set("score", 350000);
        set("shen_type", 1);
        set("baicao", 10);
        set("xhwan", 10);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("unarmed", 240);
           set_skill("cuff", 240);
        set_skill("changquan", 240);
        set_skill("hand", 240);
        set_skill("shexing-diaoshou", 240);
        set_skill("strike", 240);
        set_skill("xiaoyaoyou", 240);
        set_skill("parry", 240);
        set_skill("staff", 240);
        set_skill("fengmo-zhang", 240);
        set_skill("jiaohua-bangfa", 240);
        set_skill("blade", 240);
        set_skill("liuhe-dao", 240);
        set_skill("begging", 280);
        set_skill("checking", 280);
        set_skill("literate", 220);
        set_skill("martial-cognize", 240);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("unarmed", "changquan");
        map_skill("strike", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "liuhe-dao");
        map_skill("staff", "fengmo-zhang");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("strike", "xiaoyaoyou");

        create_family("丐帮", 18, "长老");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.lianhuan" :),
                (: perform_action, "blade.shan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "闪刀诀" : (: ask_skill1 :),
                // "雄黄丸" : (: ask_xhwan :),
                // "百草丹" : (: ask_baicao :),
        ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangdao")->wield();
}

void init()
{
        object ob;
        mapping myfam;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting()
        &&  file_name(environment(this_object())) == "/d/city/gbandao")
        {
                myfam=query("family", ob);
                if (! myfam || myfam["family_name"] != "丐帮")
                {
                        remove_call_out("saying");
                        call_out("saying", 1, ob);
                }
        }
}

void saying(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        message_vision("\n粱长老看到$N闯进来，大喝一声：你不是丐帮弟子，给我滚出去！\n\n", ob);
        call_out("kicking", 0, ob);
}

void kicking(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        ob->move("/d/gaibang/inhole");
        message("vision","只听“乒”地一声，"+query("name", ob)+
                "从小门里飞了出来。\n", environment(ob), ob);
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("level", ob)<5 )
        {
                command("say 你的江湖经验不够，还是先向各位长老学习吧。");
                return;
        }

        if( query("family/beggarlvl", ob)<4 )
        {
                command("say 你在本帮的地位太低，还是先向其他师父学习吧。");
                return;
        }

        if (ob->query_skill("force") < 90)
        {
                command("say 你的内功火候还不够，还是先向其他师父学习吧。");
                return;
        }
        command("grin");
        command("say 那你以后就跟着我吧。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/liuhe-dao/shan", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与在下素不相识，不知此话从何说起？";

        if (me->query_skill("liuhe-dao", 1) < 1)
                return "你连六合刀都没学，何谈绝招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我们丐帮内甚无作为，这招我暂时还不能传你。";

        if (me->query_skill("liuhe-dao", 1) < 120)
                return "你的六合刀火候还不够，还是下去练高点再来吧。";

        if (me->query_skill("force") < 150)
                return "你现在的内功修为不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "点了点头，对$N" HIY "说道：“给"
                     "我看清楚了。”突然陡听$n" HIY "一声暴喝，手中钢"
                     "刀一阵乱舞，竟似毫无章理，挥舞出数道刀影，气势"
                     "澎湃，力不可挡。正是六合刀的精要所在。\n\n" NOR,
                     me, this_object());

        command("say 明白了么。");
        tell_object(me, HIC "你学会了「闪刀诀」。\n" NOR);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("liuhe-dao"))
                me->improve_skill("liuhe-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuhe-dao/shan", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

string ask_xhwan()
{
        object me = this_object(), ob = this_player(), wan;

        if( !query("family", ob) || query("family/family_name", ob) != "丐帮" )
        {
                return "你非本帮弟子，怎能索取本帮灵药？\n\n";
        }

        if (! ob->query_condition("xx_poison") || ! ob->query_condition("snake_poison")
        ||  ! ob->query_condition("insect_poison"))
        {
                message_vision("$N向$n脸上仔细地打量了一阵，便皱起眉头。\n", me, ob);
                return "你并未中毒，要雄黄丸干吗？\n\n";
        }

        message_vision("$N向$n脸上仔细地打量了一阵，抓起$n手腕打脉。\n", me, ob);

        if( query("xhwan", me)<1 )
        {
                message_vision("然後$N伸手入怀，但摸索良久，似乎没找着。\n", me);
                return "我身上此刻没有雄黄丸，你还是快到城里去找大夫吧！\n\n";
        }

        addn("xhwan", -1, me);
        wan = new(DRUG_D("xh-wan"));
        wan->move(ob);

        message_vision("然後$N伸手入怀，取出一颗雄黄丸给$n。\n", me, ob);
        return "快把雄黄丸吃下，别要让毒素入侵内腑！\n\n";
}

string ask_baicao()
{
        object me = this_object(), ob = this_player(), wan;

        if( !query("family", ob) || query("family/family_name", ob) != "丐帮" )
        {
                return "你非本帮弟子，怎能索取本帮灵药？\n\n";
        }

        if( query("eff_qi", ob) == query("max_qi", ob )
         && query("eff_jing", ob) == query("max_jing", ob) )
        {
                message_vision("$N向$n脸上仔细地打量了一阵，便皱起眉头。\n", me, ob);
                return "你并未受伤，要百草丹干吗？\n\n";
        }

        message_vision("$N向$n脸上仔细地打量了一阵，抓起$n手腕打脉。\n", me, ob);

        if( query("baicao", me)<1 )
        {
                message_vision("然後$N伸手入怀，但摸索良久，似乎没找着。\n", me);
                return "我身上此刻没有百草丹，你还是快到城里去找大夫吧！\n\n";
        }

        addn("baicao", -1, me);
        wan = new(DRUG_D("baicao-dan"));
        wan->move(ob);

        message_vision("然後$N伸手入怀，取出一颗百草丹给$n。\n", me, ob);
        return "快把百草丹吃下，别要让伤势继续加重！\n\n";
}
