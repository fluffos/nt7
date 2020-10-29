#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include "fight.h"

mixed ask_skill1();

void create()
{
        set_name("奚长老", ({ "xi zhanglao", "xi", "zhanglao" }));
        set("long", @LONG
奚长老乃丐帮元老，武功甚为了得。
LONG);
        set("nickname", HIR "大智长老" NOR);
        set("title", "丐帮九袋长老");
        set("gender", "男性");
        set("age", 53);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 4300);
        set("max_neili", 4300);
        set("jiali", 180);
        set("level", 30);
        set("combat_exp", 2200000);
        set("score", 300000);
        set("shen_type", 1);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 200);
        set_skill("feiyan-zoubi", 200);
        set_skill("unarmed", 220);
           set_skill("cuff", 200);
        set_skill("changquan", 200);
        set_skill("jueming-tui", 220);
        set_skill("strike", 220);
        // set_skill("tongchui-zhang", 220);
        set_skill("xiaoyaoyou", 220);
        set_skill("blade", 220);
        set_skill("liuhe-dao", 200);
        set_skill("parry", 200);
        set_skill("staff", 240);
        set_skill("fumo-zhang", 240);
        set_skill("begging", 250);
        set_skill("checking", 250);
        set_skill("literate", 180);
        set_skill("martial-cognize", 220);

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "jueming-tui");
        map_skill("strike", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("staff", "fumo-zhang");
        map_skill("parry", "fumo-zhang");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("strike", "xiaoyaoyou");
        prepare_skill("unarmed", "jueming-tui");

        create_family("丐帮", 18, "长老");

        set("inquiry", ([
                "风火轮" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.lun" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<120000 )
        {
                command("say 你的江湖经验不够，还是先向其他师父学习吧。");
                return;
        }

        if( query("shen", ob)<20000 )
        {
                command("say 你身为丐帮弟子，竟然不做好事？");
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
        command("nod");
        command("say 我便收下你，希望日后努力上进，能有所作为。");
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

        if( query("can_perform/fumo-zhang/lun", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与在下素不相识，不知此话从何说起？";

        if (me->query_skill("fumo-zhang", 1) < 1)
                return "你连伏魔杖法都没学，何谈绝招可言？";

        if( query("family/gongji", me)<350 )
                return "你在我们丐帮内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<30000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("fumo-zhang", 1) < 120)
                return "你的二十四路伏魔杖火候不够，下去练高点再来吧。";

        if (me->query_skill("force") < 150)
                return "你现在的内功修为不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "微笑着对$N" HIY "点了点头，蓦"
                     "地起身而立，陡然一声暴喝，手中竹棒挥转如轮，"
                     "残影化出无数个大圈，瞬间已将$N" HIY "团团裹罩"
                     "其中，便似那风火轮一般，气势如虹，招式精奇，"
                     "令人叹为观止。\n\n" NOR, me, this_object());

        command("haha");
        command("say 你自己去领悟吧。");
        tell_object(me, HIC "你学会了「风火轮」。\n" NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("fumo-zhang"))
                me->improve_skill("fumo-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/fumo-zhang/lun", 1, me);
        addn("family/gongji", -350, me);

        return 1;
}
