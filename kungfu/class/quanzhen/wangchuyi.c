// This program is a part of NT MudLIB

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

string ask_me();
mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("王处一", ({"wang chuyi", "wang"}));
        set("gender", "男性");
        set("age", 35);
        set("class", "taoist");
        set("nickname",RED"玉阳子"NOR);
        set("long",
                "他就是全真七子之五王处一王真人。他身材修长，服饰整洁，\n"
                "三绺黑须飘在胸前，神态潇洒。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 32);
        set("int", 30);
        set("con", 32);
        set("dex", 30);

        set("title","全真七子之五");
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

        set("qi", 4200);
        set("max_qi", 4200);
        set("jing", 2100);
        set("max_jing", 2100);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 100);

        set("combat_exp", 1200000);

        set_skill("force", 170);
        set_skill("quanzhen-xinfa", 170);
        set_skill("sword", 160);
        set_skill("quanzhen-jian",160);
        set_skill("dodge", 150);
        set_skill("jinyan-gong", 150);
        set_skill("parry", 170);
        set_skill("strike", 170);
        set_skill("chongyang-shenzhang", 170);
        set_skill("haotian-zhang", 170);
        set_skill("literate",100);
        set_skill("finger",150);
        set_skill("zhongnan-zhi", 170);
        set_skill("taoism",100);
        set_skill("medical", 180);
        set_skill("liandan-shu", 180);
        set_skill("cuff",150);
        set_skill("chunyang-quan",150);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike", "haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
                "南帝"   : (: ask_me :),
                "段皇爷" : (: ask_me :),
                "缠字诀" : (: ask_skill1 :),
                "定阳针" : (: ask_skill2 :),
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

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 90 )
        {
                command("say 你的本门内功心法火候不足，难以领略更高深的武功。");
                return;
        }
        if( query("shen", ob)<8000 )
        {
                command("say 我看你还是多做一些侠义之事吧。\n");
                return;
        }
        command("say 好吧，我就收下你这个徒弟了。");
        command("recruit "+query("id", ob));
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

string ask_me()
{
        object me=this_player();

        if( query_temp("tmark/指", me) == 1 )
        {
                addn_temp("tmark/指", 1, me);
                return("去年师傅去过段皇爷那里，据说段皇爷把他最厉害的一阳指功夫传授给我师傅了。\n");
        } else
        {
                set_temp("tmark/指", 0, me);
                return("段皇爷遇上了一件大伤心事，现在出家做了和尚了，唉！");
        }
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/quanzhen-jian/chan", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "你连全真剑法都没学，何谈绝招可言？";

        if( query("family/gongji", me)<200 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<10000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("quanzhen-jian", 1) < 80)
                return "你的全真剑法不够娴熟，练高点再来吧。";

        if (me->query_skill("force") < 100)
                return "你的内功修为不够，修炼高后再来找我吧。";

        message_sort(HIY "\n$n" HIY "微笑着点了点头，说道：“看好了。”说"
                     "罢即抽出腰间长剑，慢慢演示起来。只见$n" HIY "剑招紧"
                     "密圆动，连绵不绝，内力便如细丝般从长剑剑锋透出，带出"
                     "阵阵风声。直看得$N" HIY "目瞪口呆。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 此招无非是以剑招迷惑对手，并无复杂之举。");
        tell_object(me, HIC "你学会了「缠字诀」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/quanzhen-jian/chan", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/quanzhen-jian/ding", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "你连全真剑法都没学，何谈绝招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<12000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("quanzhen-jian", 1) < 100)
                return "你的全真剑法不够娴熟，练高点再来吧。";

        if (me->query_skill("force") < 150)
                return "你的内功修为不够，修炼高后再来找我吧。";

        message_sort(HIY "\n$n" HIY "点了点头，喝道：“看仔细了。”话音刚"
                     "落，只见$n" HIY "脚下左弓右箭，深深吸入一口气，神气"
                     "完足如雷霆五岳，电光火石间一剑斜斜刺出，顿时只听得“"
                     "哧”的一声，$N" HIY "脚下的方砖竟然应声而碎，裂成了"
                     "数块。\n\n" NOR, me, this_object());

        command("nod");
        command("say 此招的精要无非是以气驾剑，达至随心所欲。");
        tell_object(me, HIC "你学会了「定阳针」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/quanzhen-jian/ding", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

int accept_object(object who, object ob)
{
        object obj1,obj2,obj3,obj4;
        object me=this_player();

        if( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("你没有这件东西。\n");

        if( query("name", ob) != HIR"熊胆"NOR
                 && query("name", ob) != HIY"田七"NOR
                 && query("name", ob) != HIW"没药"NOR
                 && query("name", ob) != RED"血竭"NOR )
                    return 0;

        remove_call_out("destroying");
        call_out("destroying", 1, me, ob);
        message_vision("王处一看了看$N送去的药，点了点头道：难为你了，\n"
                       "我可以教你点功夫。\n", who);

        addn_temp("tmark/王", 60, who);
        return 1;
}
