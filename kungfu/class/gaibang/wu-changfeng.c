#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include "fight.h"

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("吴长风", ({ "wu changfeng", "wu", "changfeng" }));
        set("long", @LONG
吴长风乃丐帮元老，武功甚为了得。
LONG);
        set("nickname", HIR "大勇长老" NOR);
        set("title", "丐帮九袋长老");
        set("gender", "男性");
        set("age", 45);
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
        set("combat_exp", 2500000);
        set("score", 300000);
        set("shen_type", 1);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("unarmed", 180);
        set_skill("cuff", 180);
        set_skill("changquan", 180);
        set_skill("jueming-tui", 180);
        set_skill("strike", 240);
        set_skill("xiaoyaoyou", 220);
        set_skill("parry", 220);
        set_skill("staff", 180);
        set_skill("fengmo-zhang", 180);
        set_skill("blade", 240);
        set_skill("liuhe-zhang", 240);
        set_skill("liuhe-dao", 240);
        set_skill("begging", 250);
        set_skill("checking", 250);
        set_skill("literate", 180);
        set_skill("martial-cognize", 220);

        map_skill("force", "huntian-qigong");
        map_skill("cuff", "changquan");
        map_skill("strike", "liuhe-zhang");
        map_skill("staff", "jiaohua-bangfa");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "liuhe-dao");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("strike", "liuhe-zhang");

        create_family("丐帮", 18, "长老");

        set("inquiry", ([
                "乌龙探海" : (: ask_skill1 :),
                "闪刀诀"   : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.shan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(__DIR__"obj/guitou-blade")->wield();
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

        if( query("can_perform/liuhe-zhang/tan", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与在下素不相识，不知此话从何说起？";

        if (me->query_skill("liuhe-zhang", 1) < 1)
                return "你连六合掌法都未曾学过，哪里来绝招？";

        if( query("family/gongji", me)<50 )
                return "你在我们丐帮内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<3000 )
                return "你侠义正事做得不够，这招我先不忙传你。";

        if (me->query_skill("force") < 100)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("liuhe-zhang", 1) < 60)
                return "你的六合掌法火候未到，还得多练习练习。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，也不答话，忽然间单掌飕"
                     "的探出，正向$N" HIY "胸前拍落。$N" HIY "登时大惊"
                     "失色，急忙向后跃开数尺，可已然不及，$n" HIY "的"
                     "单掌正搭在$N" HIY "的胸部左侧，招术甚为奇巧。\n"
                     "\n" NOR, me, this_object());

        if( query("gender", me) == "女性" )
        {
                command("ah");
                command("say …对…对不住…我…我忘了你是女的。");
        } else
                command("haha");

        command("say 招式便是如此，自己下去练习吧。");
        tell_object(me, HIC "你学会了「乌龙探海」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuhe-zhang"))
                me->improve_skill("liuhe-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuhe-zhang/tan", 1, me);
        addn("family/gongji", -50, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/liuhe-dao/shan", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与在下素不相识，不知此话从何说起？";

        if (me->query_skill("liuhe-dao", 1) < 1)
                return "你连六合刀法都未曾学过，哪里来绝招？";

        if( query("family/gongji", me)<200 )
                return "你在我们丐帮内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<5000 )
                return "你侠义正事做得不够，这招我先不忙传你。";

        if (me->query_skill("force") < 100)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("liuhe-dao", 1) < 80)
                return "你的六合刀法火候未到，还得多练习练习。";

        message_sort(HIY "\n$n" HIY "对$N" HIY "笑了笑，拔出腰间佩刀"
                     "握在手中，说道：“这六合刀法的要诀不过是展、抹"
                     "、钩、剁、砍、劈六势，看好了。”说完便只见$n" HIY
                     "手中钢刀吞吐不定，形若游龙，势如猛虎。接连变换"
                     "了数种方位，最后只听哧的一声砍落，刀身震得嗡嗡"
                     "直响。\n" NOR, me, this_object());

        command("nod");
        command("say 只要掌握了四象六合的方位，这招便不难练习。");
        tell_object(me, HIC "你学会了「闪刀诀」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("liuhe-dao"))
                me->improve_skill("liuhe-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuhe-dao/shan", 1, me);
        addn("family/gongji", -200, me);
        return 1;
}
