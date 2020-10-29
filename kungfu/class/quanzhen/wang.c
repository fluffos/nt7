// This program is a part of NT MudLIB
// wang.c

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed  ask_skill1();
mixed  ask_skill2();
mixed  ask_skill3();
mixed  ask_skill4();
mixed  ask_skill5();
mixed  ask_skill6();
string ask_jiuyin();
string ask_duan();
string ask_zhipu();

void create()
{
        set_name("王重阳", ({ "wang chongyang", "wang", "chongyang" }));
        set("long", @LONG
他就是全真教的开山祖师、首代掌教王重阳王
真人。他白须飘飘，宽袍缓袖，眉目清癯，颇
有些仙风道骨的味道。他本来一腔热血欲报效
国家力抗金兵，可惜朝廷腐败，于是便心灰意
冷，兼此时又从道德经中悟得了天地万物滋生
的大道，从而手创全真教。
LONG);
        set("title", "全真派开山祖师");
        set("nickname", HIW "中神通" NOR);
        set("age", 76);
        set("gender", "男性");
        set("class", "taoist");
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);
        set("max_qi", 8000);
        set("max_jing", 8000);
        set("neili", 10000);
        set("jingli", 8000);
        set("max_neili", 10000);
        set("max_jingli", 8000);
        set("jiali", 250);
        set("level", 70);
        set("combat_exp", 8000000);
        set("no_get", 1);

        set_skill("force", 650);
        set_skill("quanzhen-jianzhen", 800);
        set_skill("array", 800);
        set_skill("quanzhen-xinfa", 700);
        // set_skill("xuanmen-neigong", 380);
        set_skill("unarmed", 700);
        set_skill("xiantian-gong", 650);
        set_skill("dodge", 700);
        // set_skill("tianshan-feidu", 360);
        set_skill("jinyan-gong", 700);
        set_skill("parry", 700);
        set_skill("jinguan-yusuo", 700);
        set_skill("strike", 700);
        set_skill("chongyang-shenzhang", 660);
        set_skill("haotian-zhang", 700);
        set_skill("finger", 700);
        set_skill("zhongnan-zhi", 660);
        set_skill("sun-finger", 700);
        // set_skill("qixing-shou", 380);
        set_skill("sword", 700);
        // set_skill("qixing-jian", 360);
        // set_skill("tonggui-jian", 360);
        set_skill("quanzhen-jian", 700);
        // set_skill("tiangang-chenfa", 340);
        set_skill("taoism", 10000);
        set_skill("literate", 650);
        set_skill("huajia-su", 700);
        set_skill("martial-cognize", 650);
        set_skill("medical", 680);
        set_skill("liandan-shu", 680);
        set_skill("cuff",680);
        set_skill("whip",680);
        set_skill("chunyang-quan",680);
        set_skill("duanyun-bian",680);
        set_skill("array",650);
        set_skill("beidou-zhenfa", 650);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        // map_skill("whip", "tiangang-chenfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "haotian-zhang");
        map_skill("unarmed", "xiantian-gong");
        map_skill("finger", "sun-finger");
        map_skill("strike", "haotian-zhang");
        // map_skill("hand", "qixing-shou");
        map_skill("cuff",   "chunyang-quan");
        map_skill("whip",   "duanyun-bian");
        prepare_skill("unarmed", "xiantian-gong");

        set("no_teach/sun-finger", "一阳指乃是段家秘传，我不能教你。");

        create_family("全真教", 1, "掌教");

        set("inquiry", ([
                "全真教"     : "我全真教是天下道家玄门正宗。",
                "绝招"       : "你想学什么绝招？",
                "绝技"       : "你想学什么绝招？",
                "九阴真经"   : (: ask_jiuyin :),
                "段皇爷"     : (: ask_duan :),
                "五气朝元"   : (: ask_skill1 :),
                "一气化三清" : (: ask_skill2 :),
                "化三清"     : (: ask_skill2 :),
                "天地混元"   : (: ask_skill3 :),
                "五阴焚灭"   : (: ask_skill4 :),
                "神威浩荡"   : (: ask_skill5 :),
                "三连环"     : (: ask_skill6 :),
                "一阳指"     : (: ask_zhipu :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.hun" :),
                (: perform_action, "unarmed.fen" :),
                (: perform_action, "unarmed.dang" :),
                (: perform_action, "unarmed.jian" :),
                (: perform_action, "parry.suo" :),
                (: exert_function, "hup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(__DIR__"obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 35)
        {
                command("say 你的悟性还不够，还是先找我那几个徒弟学习吧。");
                return;
        }


        if ((int)ob->query_skill("xiantian-gong", 1) < 120
           && (int)ob->query_skill("quanzhen-xinfa", 1) < 120)
        {
                command("say 你的本门内功心法火候不足，只怕难以"
                        "领略更高深的武功。");
                return;
        }

        if( query("combat_exp", ob)<480000 )
        {
                command("say 你的实战经验太差，看来难以领略更高深的武功。");
                return;
        }

        if( query("shen", ob)<80000 )
        {
                command("say 行侠仗义是我辈学武人的宗旨，你多做些侠"
                        "义之事，我方能收你为徒。");
                return;
        }
        command("say 不错，以你资质定可传我衣钵！我就收下你这个徒弟了。");
        command("recruit "+query("id", ob));
}


mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/hup", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "你连先天功都没学，何谈绝招可言？";

        if( query("family/gongji", me)<800 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<100000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("xiantian-gong", 1) < 200)
                return "你先天功的修为不够，还是练高了再来吧。";

        if( query("max_neili", me)<2000 )
                return "你的内力修为仍不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，从怀中轻轻取出了一本"
                     "小册子，指着其中的一段对$N" HIY "细说良久，$N"
                     HIY "一边听一边点头。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 你自己下去练吧。");
        tell_object(me, HIC "你学会了「五气朝元」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/hup", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/quanzhen-jian/hua", me) )
                return "你全真剑法已达如此造诣，我已没什么可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "你连全真剑法都没学，何谈绝招可言？";

        if( query("family/gongji", me)<1600 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<100000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("quanzhen-jian", 1) < 200)
                return "你对我派剑法的了解还不够透彻，研究透了再来找我吧。";

        if (me->query_skill("xiantian-gong", 1) < 100 &&
            me->query_skill("quanzhen-xinfa", 1) < 100)
                return "你全真的内功的修为不够，还是练高了再来吧。";

        if( query("max_neili", me)<4800 )
                return "你的内力修为仍不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，随手从道袍上撕下一角布"
                     "条，内力吞吐间，只见那布条登时变得如同坚铁，伸手"
                     "刺处，变幻无方，宛若三把长剑齐出，招式当真绝妙无"
                     "比。只看得$N" HIY "目瞪口呆。\n\n"
                     NOR, me, this_object());

        command("haha");
        command("say 你自己下去揣摩吧，切记莫走进邪魔歪道！");
        tell_object(me, HIC "你学会了「一气化三清」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        /*
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        */
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1800000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1800000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1800000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/quanzhen-jian/hua", 1, me);
        addn("family/gongji", -1600, me);

        return 1;
}

mixed ask_skill6()
{
        object me;
        me = this_player();

        if( query("can_perform/quanzhen-jian/lian", me) )
                return "你全真剑法已达如此造诣，我已没什么可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("quanzhen-jian", 1) < 1)
                return "你连全真剑法都没学，何谈绝招可言？";

        if( query("family/gongji", me)<1600 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<100000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("quanzhen-jian", 1) < 200)
                return "你对我派剑法的了解还不够透彻，研究透了再来找我吧。";

        if (me->query_skill("quanzhen-xinfa", 1) < 100)
                return "你全真心法的修为不够，还是练高了再来吧。";

        if( query("max_neili", me)<4800 )
                return "你的内力修为仍不足，还是练高点再来吧。";

        command("haha");
        command("say 你自己下去揣摩吧，切记莫走进邪魔歪道！");
        tell_object(me, HIC "你学会了「三连环绝技」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("quanzhen-xinfa"))
                me->improve_skill("quanzhen-xinfa", 1800000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1800000);
        if (me->can_improve_skill("quanzhen-jian"))
                me->improve_skill("quanzhen-jian", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/quanzhen-jian/lian", 1, me);
        addn("family/gongji", -1600, me);

        return 1;
}


mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/hun", me) )
                return "这招你不是已经学会了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "你连先天功都没学，何谈绝招可言？";

        if( query("family/gongji", me)<1800 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<120000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("xiantian-gong", 1) < 200)
                return "你先天功的修为不够，还是练高了再来吧。";

        if( query("max_neili", me)<6800 )
                return "你的内力修为仍不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，对$N" HIY "说道：“你的"
                     "先天功达此境界，实属不凡，今日为师传你这招又有何"
                     "妨？”说罢$n" HIY "便摆开架势，慢慢地演示招数。\n"
                     "\n" NOR, me, this_object());

        command("nod");
        command("say 招式便是如此，能否领悟就靠你自己了。");
        tell_object(me, HIC "你学会了「天地混元」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/hun", 1, me);
        addn("family/gongji", -1800, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/fen", me) )
                return "这招你不是已经学会了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "你连先天功都没学，何谈绝招可言？";

        if( query("family/gongji", me)<2000 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<130000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("xiantian-gong", 1) < 240)
                return "你先天功的修为不够，还是练高了再来吧。";

        if( query("max_neili", me)<6800 )
                return "你的内力修为仍不足，还是练高点再来吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，对$N" HIY "说道：“难得"
                     "你有如此造诣，今日师父就传你这招，可看好了！”$n"
                     HIY "随即一声清哮，全身真气急速运转，引得周围气流"
                     "波动不已。左掌微微一抖，先天真气随招式而荡漾，激"
                     "起千层气浪，威力之强，当可用惊天地、泣鬼神来描述"
                     "，直看得$N" HIY "目瞪口呆。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 招式便是如此，你自己下去练吧。");
        tell_object(me, HIC "你学会了「五阴焚灭」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/fen", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/xiantian-gong/dang", me) )
                return "这招你不是已经学会了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "你连先天功都没学，何谈绝招可言？";

        if( query("family/gongji", me)<2800 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<180000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("xiantian-gong", 1) < 240)
                return "你先天功的修为不够，还是练高了再来吧。";

        if( query("max_neili", me)<8000 )
                return "你的内力修为仍不足，还是练高点再来吧。";

        if( !query("can_perform/xiantian-gong/fen", me) )
                return "此招乃是由「五阴焚灭」升华而来，你还是逐步学习吧？";

        message_sort(HIY "\n$n" HIY "微微点了点头，随手搭在$N" HIY "的"
                     "肩上，突然$N" HIY "陡觉全身筋脉剧震，内息澎湃汹涌"
                     "之极，犹如江河绝堤，便欲冲关破出一般，不由大惊。"
                     "\n\n" NOR, me, this_object());

        command("haha");
        command("say 你可明白了？");
        tell_object(me, HIC "你学会了「神威浩荡」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1800000);
        me->improve_skill("martial-cognize", 1800000);
        set("can_perform/xiantian-gong/dang", 1, me);
        addn("family/gongji", -2800, me);

        return 1;
}

string ask_jiuyin()
{
        mapping fam;
        int lvl_force;

        if( !(fam=query("family", this_player()) )
            || fam["family_name"] != "全真教")
                return RANK_D->query_respect(this_player()) +
                "与本教毫无瓜葛，这话从何说起？";
        if (!(lvl_force = this_player()->query_skill("force", 1))
            || lvl_force < 50)
                return RANK_D->query_respect(this_player()) +
                "的基本内功火候如此之浅，强练真经上的上乘武功有害无益。";
        return "九阴真经是天下武学正宗，我已交给我师弟周伯通保管。";
}

string ask_duan()
{
        object me=this_player();
        if( query_temp("tmark/指", me) == 2 )
        {
                addn_temp("tmark/指", 1, me);
                return("段皇爷号称‘南帝’，家传的一阳指是天下最厉害的指法。\n");
        }
        else {
                set_temp("tmark/指", 0, me);
                return("你问段皇爷做甚么，莫非想与他为难？\n");
        }
}

string ask_zhipu()
{
        object ob,me=this_player();
        if( query_temp("tmark/指", me) == 3 )
        {
                set_temp("tmark/指", 0, me);
                if(query("book_count")>0)
        {
                        ob=new(BOOK_DIR"sun_book");
                        ob->move(me);
                        addn("book_count",-1);
                        message("channel:rumor",MAG"【谣言】某人："+query("name", this_player())+"拿了一阳指诀啦。\n"NOR,users());
                        return("好吧，你历经艰苦，意志甚坚，这本指法谱就交给你了。\n");
                }
                else return("你来晚了，指法谱已经被人取走了。\n");
        }
        else {
                set_temp("tmark/指", 0, me);
                return  RANK_D->query_respect(me) + "不是想跟我较量较量吧？\n";
        }
}

int accept_ask(object me, string topic) 
{ 
        switch (topic) 
        { 
        case "历练" : 
        case "历炼" : 
        case "锻炼" : 
                return QUEST_D->accept_ask(this_object(), me, topic); 
                break; 
        case "先天罡气" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/xiantian-gong/xian", 
                                "name"    : "先天罡气",
                                "sk1"     : "xiantian-gong", 
                                "lv1"     : 1000, 
                                "sk2"     : "unarmed", 
                                "lv2"     : 1000, 
                                "sk3"     : "force",
                                "lv3"     : 1000, 
                                "reborn"  : 1,
                                "gongxian": 3000, ])); 
                break; 
       case "日月无光" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                            ([ "perform" : "can_perform/duanyun-bian/guang", 
                       "name"    : "日月无光",
                 "sk1"     : "duanyun-bian", 
                  "lv1"     : 120, 
                 "neili"   : 1400, 
                    "shen"    : 24000, ])); 
                break; 
        case "断云助日" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/duanyun-bian/duan", 
                        "name"    : "断云助日",
                  "sk1"     : "duanyun-bian", 
                   "lv1"     : 220, 
                  "neili"   : 2400, 
                  "gongxian"   : 1400, 
                              "shen"    : 44000, ])); 
                 break; 
        case "风云变色" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/duanyun-bian/bian", 
                        "name"    : "风云变色",
        "sk1"     : "duanyun-bian", 
         "lv1"     : 320, 
        "neili"   : 4400, 
            "gongxian"   : 2400, 
                                "shen"    : 44000, ])); 
                 break; 
                return 0; 
        } 
} 

/*
void unconcious()
{
        die();
}
*/
