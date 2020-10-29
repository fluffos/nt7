// This program is a part of NT MudLIB

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("刘处玄", ({"liu chuxuan", "liu"}));
        set("gender", "男性");
        set("age", 38);
        set("class", "taoist");
        set("nickname",WHT"长生子"NOR);
        set("long",
                "他就是全真三徒刘处玄刘真人，他身材瘦小，但顾盼间自有一\n"
                "种威严气概。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 30);
        set("int", 30);
        set("con", 28);
        set("dex", 30);

        set("title","全真七子之三");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 4400);
        set("max_qi", 4400);
        set("jing", 2200);
        set("max_jing", 2200);
        set("neili", 4600);
        set("max_neili", 4600);
        set("jiali", 100);
        set("level", 15);
        set("combat_exp", 850000);

        set_skill("force", 160);
        set_skill("quanzhen-xinfa", 160);
        set_skill("sword", 160);
        set_skill("quanzhen-jian",160);
        set_skill("dodge", 140);
        set_skill("jinyan-gong", 140);
        set_skill("parry", 150);
        set_skill("finger",150);
        set_skill("zhongnan-zhi", 150);
        set_skill("literate", 100);
        set_skill("strike", 150);
        set_skill("chongyang-shenzhang", 150);
        set_skill("haotian-zhang", 150);
        set_skill("finger",150);
        set_skill("array",120);
        set_skill("beidou-zhenfa", 120);
        set_skill("taoism",120);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "连环掌"     : (: ask_skill1 :),
                "重阳连环掌" : (: ask_skill1 :),
        ]) );

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greenrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 70 )
        {
                command("say 你的本门内功心法火候不足,难以领略更高深的武功。");
                return;
        }
        if( query("shen", ob)<6000 )
        {
                command("say 多做一些行侠仗义的事情再说吧！。\n");
                return;
        }
        command("say 好吧，我就收下你这个徒弟了。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/chongyang-shenzhang/lian", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("chongyang-shenzhang", 1) < 1)
                return "你连重阳神掌都没学，何谈绝招可言？";

        if( query("family/gongji", me)<100 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<10000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("chongyang-shenzhang", 1) < 100)
                return "你的重阳神掌不够娴熟，练高点再来吧。";

        if (me->query_skill("force") < 120)
                return "你的内功修为不够，修炼高后再来找我吧。";

        message_sort(HIY "\n$n" HIY "眉头一皱，上下打量了$N" HIY "一番"
                     "，当下更不答话，衣袖轻轻一抖，猛然大喝一声，顿时"
                     "双掌纷飞，掌劲朝四面八方云贯而出，气势恢弘之极。"
                     "\n\n" NOR, me, this_object());

        command("say 看懂了么？");
        tell_object(me, HIC "你学会了「重阳连环掌」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("chongyang-shenzhang"))
                me->improve_skill("chongyang-shenzhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/chongyang-shenzhang/lian", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

