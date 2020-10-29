// This program is a part of NT MudLIB
// li.c 黎生

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include "fight.h"

mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("黎生", ({ "li sheng", "li", "sheng" }));
        set("gender", "男性");
        set("long", "这是位生性刚直，嫉恶如仇的丐帮八袋弟子。\n");
        set("title", "丐帮八袋弟子");
        set("nickname", HIW "行侠仗义" NOR);
        set("age", 42);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 32);
        set("int", 32);
        set("con", 32);
        set("dex", 32);
        set("max_qi", 2400);
        set("max_jing", 1600);
        set("neili", 2200);
        set("max_neili", 2200);
        set("jiali", 180);
        set("combat_exp", 1200000);
        set("level", 15);
        set("shen_type", 1);

        set_skill("force", 160);
        set_skill("huntian-qigong", 140);
        set_skill("dodge", 160);
        set_skill("unarmed", 160);
        set_skill("jueming-tui", 160);
           set_skill("cuff", 160);
        set_skill("changquan", 160);
        set_skill("feiyan-zoubi", 160);
        set_skill("staff", 140);
        set_skill("fengmo-zhang", 140);
        set_skill("hand", 140);
        set_skill("shexing-diaoshou", 140);
        set_skill("strike", 160);
        set_skill("shenlong-baiwei", 160);
        set_skill("xiaoyaoyou", 160);
        set_skill("blade", 160);
        set_skill("liuhe-dao", 160);
        set_skill("parry", 160);
        set_skill("begging", 200);
        set_skill("checking", 200);
        set_skill("literate", 140);
        set_skill("martial-cognize", 160);

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "fengmo-zhang");
        map_skill("strike", "shenlong-baiwei");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "shenlong-baiwei");

        prepare_skill("strike", "shenlong-baiwei");

        set("no_teach/shenlong-baiwei", "这招掌法乃是蒙帮主他老"
                                        "人家所赐，不能轻易传授。");
        /*
        set("no_teach/huntian-qigong",  "这内功便是我也未修炼纯"
                                        "熟，我还是教你点别的吧。");
        */

        create_family("丐帮", 19, "弟子");

        set("coagents", ({
                ([ "startroom" : "/d/gaibang/undertre",
                   "id"        : "liang zhanglao" ]),
                ([ "startroom" : "/d/city/gbandao",
                   "id"        : "jian zhanglao" ]),
        }));

        set("inquiry", ([
                // "五丁开山" : (: ask_skill1 :),
                "绝命一踢" : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",3);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say 你身为丐帮弟子，竟然不做好事？");
                return;
        }
        command("nod");
        command("say 我便收你为徒，日后可得行侠仗义，莫损我丐帮名声。");
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

        if( query("can_perform/tongchui-zhang/kai", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与在下素不相识，不知此话从何说起？";

        if (me->query_skill("tongchui-zhang", 1) < 1)
                return "你连铜锤掌法都没学，何谈绝招可言？";

        if( query("family/gongji", me)<100 )
                return "你在我们丐帮内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<1000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("tongchui-zhang", 1) < 80)
                return "你的铜锤掌法火候还不够，还是下去练高点再来吧。";

        if (me->query_skill("force") < 90)
                return "你现在的内功修为不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，从怀中轻轻取出了一本"
                     "小册子，指着其中的一段对$N" HIY "细说良久，$N"
                     HIY "一边听一边点头。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 招式很简单，你自己下去练吧。");
        tell_object(me, HIC "你学会了「五丁开山」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("tongchui-zhang"))
                me->improve_skill("tongchui-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tongchui-zhang/kai", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/jueming-tui/jue", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与在下素不相识，不知此话从何说起？";

        if (me->query_skill("jueming-tui", 1) < 1)
                return "你连绝命腿法都没学，何谈绝招可言？";

        if( query("family/gongji", me)<150 )
                return "你在我们丐帮内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<3000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("jueming-tui", 1) < 80)
                return "你的绝命腿法火候还不够，还是下去练高点再来吧。";

        if (me->query_skill("force") < 100)
                return "你现在的内功修为不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，伸手将$N" HIY "招到了"
                     "面前，在$N" HIY "耳边轻声嘀咕了些话。$N" HIY "听"
                     "了半天，突然间不由会心的一笑，看来大有所悟。\n\n"
                     NOR, me, this_object());

        command("nod");
        command("say 这招的要诣就是出招连贯，以奇制胜。");
        tell_object(me, HIC "你学会了「绝命一踢」。\n" NOR);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("jueming-tui"))
                me->improve_skill("jueming-tui", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jueming-tui/jue", 1, me);
        addn("family/gongji", -150, me);

        return 1;
}
