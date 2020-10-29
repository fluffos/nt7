// renwoxing.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

int ask_bijian();
string ask_jing();
mixed no_learn();
mixed ask_pfm();

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed try_to_learn_xixingdafa();

void create()
{
        set_name("任我行", ({ "ren woxing", "ren","woxing" }));
        set("title", GRN "日月神教教主" NOR );
        set("long", "只见他一张长长的脸孔，脸色雪白，更无半分血色，眉目清秀，
身材甚高，一头黑发，穿的是一袭青衫。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("per", 27);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("yijinjing_count", 1);

        set("max_qi", 7000);
        set("max_qi", 700000);
        set("max_jing", 50000);
        set("neili", 90000);
        set("max_neili", 90000);
        set("jiali", 400);
        set("combat_exp", 40000000);
        set("score", 50000);

        set_skill("force", 700);
        set_skill("riyue-xinfa", 700);
        set_skill("xixing-dafa", 700);
        set_skill("tianhuan-shenjue", 900);
        set_skill("yijinjing", 600);
        set_skill("tianmo-jian", 700);
        set_skill("riyue-jian", 700);
        set_skill("strike", 900);
        set_skill("guzhuo-zhang", 900);
        set_skill("qingmang-zhang", 900);
        set_skill("cuff", 700);
        set_skill("zhenyu-quan", 900);
        set_skill("xuwu-piaomiao", 700);
        set_skill("hand", 700);
        set_skill("lansha-shou", 900);
        set_skill("huanmo-longtianwu", 700);
        set_skill("claw", 900);
        set_skill("poyue-zhao", 900);
        set_skill("literate", 700);
        set_skill("dodge", 700);
        set_skill("unarmed", 700);
        set_skill("piaomiao-shenfa", 700);
        set_skill("parry", 700);
        set_skill("sword", 700);
        set_skill("yuanshi-jian", 900);
        set_skill("damo-jian", 600);
        set_skill("taiji-jian", 600);
        set_skill("huifeng-jian", 600);
        set_skill("taishan-sword", 600);
        set_skill("hengshan-jian", 600);
        set_skill("hengshan-sword", 600);
        set_skill("huashan-sword", 600);
        set_skill("songshan-sword", 600);
        set_skill("blade", 900);
        set_skill("danding-dao", 900);
        set_skill("throwing", 900);
        set_skill("heixue-shenzhen", 900);
        set_skill("literate", 320);
        set_skill("martial-cognize", 900);
        set_skill("richu-dongfang", 600);        

        map_skill("dodge", "piaomiao-shenfa");
        map_skill("force", "xixing-dafa");
        map_skill("strike", "guzhuo-zhang");
        map_skill("sword", "yuanshi-jian");
        map_skill("parry", "guzhuo-zhang");
        map_skill("hand", "lansha-shou");
        map_skill("cuff", "zhenyu-quan");
        map_skill("claw", "poyue-zhao");
        map_skill("blade", "danding-dao");
        map_skill("throwing", "heixue-shenzhen");

        prepare_skill("strike", "guzhuo-zhang");

        set("no_teach", ([
                "xixing-dafa"    : (: try_to_learn_xixingdafa :),
                "yijinjing"      : "易筋经神功乃少林绝技，我虽习得，却也未得要领。",
                "damo-jian"      : (: no_learn :),
                "taiji-jian"     : (: no_learn :),
                "huifeng-jian"   : (: no_learn :),
                "taishan-sword"  : (: no_learn :),
                "hengshan-jian"  : (: no_learn :),
                "hengshan-sword" : (: no_learn :),
                "huashan-sword"  : (: no_learn :),
                "songshan-sword" : (: no_learn :),
        ]));

        create_family("日月神教", 1, "教主");
        
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("inquiry", ([
                "吸星大法" : "我写的拓本还遗留在梅庄未曾取回，你去找找吧。\n",
                "比剑"     : (: ask_bijian :),
                "剑法"     : (: ask_bijian :),
                "易筋经"   : (: ask_jing :),
                "黑木令"   : "要拿黑木令？老夫想先看看你的剑法！\n",
                "绝招"     : (: ask_pfm :),
                "一剑穿心" : (: ask_pfm :),
                "天地归元" : (: ask_skill1 :),
                "天旋地转" : (: ask_skill2 :),
                "大巧若拙" : (: ask_skill3 :),
                "大智若愚" : (: ask_skill4 :),
                "反璞归真" : (: ask_skill5 :),
        ]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.gui" :),
		(: perform_action, "sword.xuan" :),
                (: perform_action, "strike.zhuo" :),
                (: perform_action, "strike.yu" :),
                (: perform_action, "strike.zhen" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: exert_function, "suck" :),
	}) );

        set("master_ob", 5);
        setup();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void attempt_apprentice(object ob)
{
        if(! permit_recruit(ob))  return;

        if( query("shen", ob)>-80000 )
        {
                command("sneer");
                command("say 老夫平生最痛恨的就是你这样的假仁假义之徒。");
                return;
        }

        if( query("combat_exp", ob)<500000 )
        {
                command("say 你现在江湖经验太浅，还是先跟随几位长老学习吧。");
                return;
        }

	if (ob->query_int() < 34)
	{
		command("hmm");
		command("say 你悟性那么差，怎么领会我的武功？");
		return;
	}

        if (ob->query_skill("tianhuan-shenjue", 1) < 150
           && ob->query_skill("riyue-xinfa", 1) < 150)
        {
                command("hmm");
                command("say 你连本门最基本的内功都没修好，怎么学习上乘武学。");
                return;
        }

        command("nod2");
        command("say 念在你如此有心，对本教又忠心耿耿，今日我便收你为徒。");
        command("say 我日月神教一统江湖的千秋大业，就全靠你们了。");
        command("recruit "+query("id", ob));
        set("title", HIR"日月神教大护法"NOR, ob);
        return;
}

mixed try_to_learn_xixingdafa()
{
        object ob = this_player();

        if (query("can_learn/xixing-dafa/ren", ob))
                return 0;

        if (ob->query_skill("force", 1) > 180)
        {
                command("say 你此时的功力已颇为深厚，今日我就传你吸星大法。");
	        command("whisper " + query("id", ob) + " 压抑内力反噬的口诀"
                        "是%X&$&$%$$#$#，可记好了。");
                set("can_learn/xixing-dafa/ren", 1, ob);
                return 0;
        }

        return "你此时功力太浅，强修此功会走火入魔。";
}
int ask_bijian()
{
        object obj, me = this_player(), ob = this_object();
        message_vision("$N躬身说道：“晚辈今日有幸拜见任老前辈，还望多加指教。”\n$n笑道：“不用客气，你来解我寂寞，可多谢你啦。”\n", me, ob );
        message_vision("$N道：“不敢。”\n$n点了点头，说道：“我只想瞧瞧你的剑法，并非真的过招，再说，我也未必能胜得了你。”\n\n", me, ob);
        command("enable sword damo-jian");
        say(HIR"任我行大喝一声：“少林剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才一招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword taiji-jian");
        say(HIR"任我行大喝一声：“武当剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才两招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword huifeng-jian");
        say(HIR"任我行大喝一声：“峨嵋剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才三招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword songshan-sword");
        say(HIR"任我行大喝一声：“嵩山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才四招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }

        command("enable sword taishan-sword");
        say(HIR"任我行大喝一声：“泰山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才五招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword huashan-sword");
        say(HIR"任我行大喝一声：“华山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才六招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword hengshan-sword");
        say(HIR"任我行大喝一声：“衡山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“才七招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword hengshan-jian");
        say(HIR"任我行大喝一声：“恒山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("任我行叹了口气，说道：“还是没过八招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        if( query_temp("heimuling", me) )
                say("任我行说道：“哈哈，这位" + RANK_D->query_respect(me) +"武功不错，快去帮我杀了东方不败那个阉贼！”\n");
        else
        {
                say("任我行说道：“这位" + RANK_D->query_respect(me) +"不错，我就送你一块黑木令吧。”\n");
                set_temp("heimuling", 1, me);
        }
        obj = new("/d/heimuya/obj/heimu-ling");
        obj -> move(me);
        command("enable sword tianmo-jian");
        return 1;
}

mixed no_learn()
{
        command("shake");
        command("say 这功夫是我闲时练来玩的，也不知练得对不对，你就不要学了。");
        return -1;
}

mixed ask_pfm()
{
        object me = this_player();

        if( query("can_perform/tianmo-jian/chuanxin", me) )
                return RANK_D->query_respect(me) + "是想和老夫切磋一下武艺？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "本教武功独步武林，这位" + RANK_D->query_respect(me) +
                       "既然想学，不如入我日月神教如何？";

        if (me->query_skill("tianmo-jian", 1) < 250)
                return "你的天魔剑法尚欠火候，还领悟不了这招，再多练练去吧！";

        message_vision(HIY "$n" HIY "对$N" HIY "点了点头：这招讲究以意驭剑，瞧仔细了。\n" HIW
                       "只见$n" HIW "双足一点，腾空而起，手中长剑前探，紧跟着身子连转" HIW
                       "数圈，一道白影笔直向$N" HIW "射来。\n" NOR,
                       me, this_object());
        
        say(HIC"任我行飘然而落，还剑入鞘，微笑道：“看懂了没有？”\n"NOR);
        tell_object(me, HIY "你学会了「一剑穿心」这一招。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        set("can_perform/tianmo-jian/chuanxin", 1, me);
        return 1;
}

string ask_jing()
{
        object me, ob;
        string msg;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
                return "少林易筋经神功名满江湖，若有幸习得，终生受用不尽。";

        if( query("family/master_id", me) != query("id") )
                return "据说曾有少林高僧将经文记录下来，不知是真是假。";


        if (objectp(present("yijinjing", me)))
                return "你不是已有经书了，还问我做什么。";

        if( query_temp("ask_jing", me) && time()-query_temp("ask_jing", me)<120 )
                return "跟你说了经书不在老夫身上，你不相信么？";

        if (random(3) != 0 || query("yijinjing_count") < 1)
        {
                if( query_temp("ask_jing", me) )
                        msg = "老夫还未曾将经书找回，你再等等吧。";
                else
                        msg = "经书此时并不在老夫身上。";
                set_temp("ask_jing", time(), me);
                return msg;
        }

        addn("yijinjing_count", -1);
        ob = new("/clone/book/yijinjing");
        ob->move(me);
        return "这卷经文你可要小心收好，千万勿示于他人。";
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/yuanshi-jian/gui", me) )
                return "这一招我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑来捣什么乱？";

        if (me->query_skill("yuanshi-jian", 1) < 1)
                return "你连原始剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<500 )
                return "你在教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)>-120000 )
                return "你这样心慈手软，就算学会这招又有什么用？";

        if (me->query_skill("force") < 200)
                return "你的内功火候尚需提高，练好了再来找我吧。";

        if (me->query_skill("yuanshi-jian", 1) < 140)
                return "你的原始剑法还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "点了点头，随即便将$N" HIY "招至身边"
                     "，在耳旁低声细说良久，$N" HIY "听后会心的一笑，看来"
                     "大有所悟。\n\n" NOR, me, this_object()); 

        command("nod2");
        command("say 刚才我说的全是此招的精要，可要记牢了。");
        tell_object(me, HIC "你学会了「天地归元」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yuanshi-jian"))
                me->improve_skill("yuanshi-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuanshi-jian/gui", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/yuanshi-jian/xuan", me) )
                return "这一招我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑来捣什么乱？";

        if (me->query_skill("yuanshi-jian", 1) < 1)
                return "你连原始剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<1400 )
                return "你在教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)>-130000 )
                return "你这样心慈手软，就算学会这招又有什么用？";

        if (me->query_skill("force") < 260)
                return "你的内功火候尚需提高，练好了再来找我吧。";

        if (me->query_skill("yuanshi-jian", 1) < 180)
                return "你的原始剑法还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "微微一笑，从怀中轻轻取出了一本剑谱"
                     "，指着其中一段对$N" HIY "细说良久，$N" HIY "一边听"
                     "一边不住地点头。\n\n" NOR, me, this_object());

        command("nod");
        command("say 你只需记住‘以快打慢、制人机先’这八个字便成。");
        tell_object(me, HIC "你学会了「天旋地转」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yuanshi-jian"))
                me->improve_skill("yuanshi-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuanshi-jian/xuan", 1, me);
        addn("family/gongji", -1400, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/guzhuo-zhang/zhuo", me) )
                return "这一招我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑来捣什么乱？";

        if (me->query_skill("guzhuo-zhang", 1) < 1)
                return "你连古拙掌法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<600 )
                return "你在教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)>-120000 )
                return "你这样心慈手软，就算学会这招又有什么用？";

        if( query("max_neili", me)<1800 )
                return "你的内力太差，怎么修炼上乘武功？";

        if (me->query_skill("force") < 220)
                return "你的内功火候尚需提高，练好了再来找我吧。";

        if (me->query_skill("guzhuo-zhang", 1) < 150)
                return "你的古拙掌法还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "冷笑一声，更不答话，只是随手挥出一掌"
                     "，毫无半点招式可言。可哪知这看似不经意的一掌，竟激得"
                     "周围尘沙四起，掌风呼啸而至，直刮得$N" HIY "面庞隐隐"
                     "生疼。招式之巧，实乃$N" HIY "前所未闻。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 明白了吗？");
        tell_object(me, HIC "你学会了「大巧若拙」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("guzhuo-zhang"))
                me->improve_skill("guzhuo-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/guzhuo-zhang/zhuo", 1, me);
        addn("family/gongji", -600, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/guzhuo-zhang/yu", me) )
                return "这一招我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑来捣什么乱？";

        if (me->query_skill("guzhuo-zhang", 1) < 1)
                return "你连古拙掌法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<1200 )
                return "你在教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)>-150000 )
                return "你这样心慈手软，就算学会这招又有什么用？";

        if( query("max_neili", me)<2800 )
                return "你的内力太差，怎么修炼上乘武功？";

        if (me->query_skill("force") < 260)
                return "你的内功火候尚需提高，练好了再来找我吧。";

        if (me->query_skill("guzhuo-zhang", 1) < 180)
                return "你的古拙掌法还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "大笑数声，对$N" HIY "赞道：“想不到你"
                     "的掌法居然已达如此造诣，今日老夫传你这招又有何妨？”"
                     "$n" HIY "随即摆开架势，慢慢的演示招数。\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 只需明白了这个道理，这招大愚掌便已练成了。");
        tell_object(me, HIC "你学会了「大智若愚」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("guzhuo-zhang"))
                me->improve_skill("guzhuo-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/guzhuo-zhang/yu", 1, me);
        addn("family/gongji", -1200, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/guzhuo-zhang/zhen", me) )
                return "这一招我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我日月神教的，跑来捣什么乱？";

        if (me->query_skill("guzhuo-zhang", 1) < 1)
                return "你连古拙掌法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<2200 )
                return "你在教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)>-200000 )
                return "你这样心慈手软，就算学会这招又有什么用？";

        if( !query("can_perform/guzhuo-zhang/zhuo", me )
            || !query("can_perform/guzhuo-zhang/yu", me) )
                return "你连前两招都未练成，怎么学这最后一招？";

        if( query("max_neili", me)<3600 )
                return "你的内力太差，怎么修炼上乘武功？";

        if (me->query_skill("force") < 300)
                return "你的内功火候尚需提高，练好了再来找我吧。";

        if (me->query_skill("guzhuo-zhang", 1) < 220)
                return "你的古拙掌法还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "对$N" HIY "微微点了点头，沉声说道："
                     "“看来你这套古拙掌法已经练得相当纯熟了，今日老夫就"
                     "传你这招。”说完便将$N" HIY "招至跟前细说良久，陡然"
                     "间只见$n" HIY "忽然探出右手，平推而出，$N" HIY "只"
                     "觉掌风澎湃，凌厉之极，顿时胸口一阵郁闷，难受得说不"
                     "出话来。\n\n" NOR, me, this_object());

        command("haha");
        command("say 两招合一便是新招，你明白了吗？");
        tell_object(me, HIC "你学会了「反璞归真」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("guzhuo-zhang"))
                me->improve_skill("guzhuo-zhang", 1500000);
        if (me->can_improve_skill("guzhuo-zhang"))
                me->improve_skill("guzhuo-zhang", 1500000);
        if (me->can_improve_skill("guzhuo-zhang"))
                me->improve_skill("guzhuo-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/guzhuo-zhang/zhen", 1, me);
        addn("family/gongji", -2200, me);

        return 1;
}
void reset()
{
     set("yijinjing_count", 1);
}
