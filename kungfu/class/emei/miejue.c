// This program is a part of NT MudLIB

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#include <ansi.h>
#include "emei.h"

string ask_me();
string ask_for_quit();

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();
mixed ask_skill9();
mixed ask_skill10();
mixed ask_skill11();
mixed ask_skill8();
mixed ask_skill9();
mixed ask_skill12();

void create()
{
        set_name("灭绝师太", ({ "miejue shitai", "miejue", "shitai", "mie", "jue"}));
        set("long", "她是峨嵋派的第三代弟子，现任峨嵋派掌门人。\n");
        set("gender", "女性");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("inquiry",([
                "剃度"     : "要剃度找静玄。",
                "出家"     : "要剃度找静玄。",
                // "云海明灯" : "自张无忌应我三掌之约，而我败于他后，我已发誓不用飘雪穿云掌了。",
                // "佛光普照" : "哼，自从光明顶一战后，我早已将这招封存，你找别人吧。",
                "绝招"     : "我峨眉派绝学如此之多，你到底要问什么绝招？",
                "绝技"     : "我峨眉派绝学如此之多，你到底要问什么绝技？",
                "秘籍"     :  (: ask_me :),
                "还俗"     : (: ask_for_quit :),
                "灭剑"     : (: ask_skill1 :),
                "绝剑"     : (: ask_skill2 :),
                "星罗棋布" : (: ask_skill3 :),
                "八式合一" : (: ask_skill4 :),
                "截筋断脉" : (: ask_skill5 :),
                "凌空指穴" : (: ask_skill6 :),
                "无形幻影" : (: ask_skill7 :),
                "佛光初现" : (: ask_skill8 :),
                "伏魔剑诀" : (: ask_skill9 :),
                "倚天剑诀" : (: ask_skill12 :),
                "云海明灯" : (: ask_skill10 :),
                "佛光普照" : (: ask_skill11 :),
        ]));

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4500);
        set("max_jing", 3000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jingli", 1200);
        set("max_jingli", 1200);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 2500000);
        set("score", 50000);
        set("book_count",10);

        set_skill("force", 600);
        set_skill("emei-xinfa", 600);
        set_skill("emei-jiuyang", 600);
        set_skill("linji-zhuang", 600);
        set_skill("dodge", 600);
        set_skill("zhutian-bu", 600);
        set_skill("finger", 600);
        set_skill("tiangang-zhi", 600);
        set_skill("hand", 600);
        set_skill("jieshou-jiushi", 600);
        set_skill("strike", 600);
        set_skill("jinding-zhang", 600);
        set_skill("piaoxue-zhang", 600);
        // set_skill("sixiang-zhang", 460);
        set_skill("sword", 600);
        set_skill("huifeng-jian", 600);
        set_skill("emei-xinfa", 600);
        set_skill("emei-jian", 600);
        set_skill("yitian-jian", 600);
        set_skill("blade", 600);
        set_skill("yanxing-dao", 600);
        set_skill("parry", 600);
        set_skill("martial-cognize", 600);
        set_skill("literate", 600);
        set_skill("mahayana", 600);
        set_skill("buddhism", 600);
	set_skill("jingxin", 600);

        set("no_teach", ([
                "emei-jiuyang" : "这峨嵋九阳功乃残缺不全的九阳神功，临济十二庄"
                "胜之千倍，你还是学它好了。",
        ]));

        map_skill("force", "linji-zhuang");
        map_skill("dodge", "zhutian-bu");
        map_skill("finger", "tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("strike", "jinding-zhang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("parry", "huifeng-jian");

        prepare_skill("strike", "jinding-zhang");
        prepare_skill("hand", "jieshou-jiushi");

        create_family("峨嵋派", 3, "掌门人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.yitian" :),
                (: perform_action, "sword.fumo" :),
                (: perform_action, "finger.ling" :),
                (: perform_action, "strike.bashi" :),
                (: perform_action, "hand.jie" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("master_ob", 5);
        setup();

        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<30000 )
        {
                command("say 你行侠仗义之事做的太少！实在是太少！");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("sigh");
                command("say 你的江湖经验太浅，还是先多锻炼锻炼再说吧。");
                return;
        }

        if ((int)ob->query_skill("mahayana", 1) < 100)
        {
                command("say 你大乘涅磐功修为还不行，好好感悟感悟！");
                return;
        }

        if ((int)ob->query_skill("linji-zhuang",1) < 100)
        {
                command("say 怎么回事？本门内功心法你怎么学的？好好给我练功去！");
                return;
        }

        name=query("name", ob);
        new_name = "静" + name[1..1];
        NAME_D->remove_name(query("name", ob),query("id", ob));
        set("name", new_name, ob);
        NAME_D->map_name(query("name", ob),query("id", ob));

        command("say 好吧，我就收下你了。");
        command("say 以后你就叫作" + new_name + "，要像为师一样，把天下的恶人统统杀光！");
        command("recruit "+query("id", ob));
}

string ask_for_quit()
{
        object me;
        me = this_player();

        if( query("family/family_name", me) != "峨嵋派" )
                return "你是什么人？跑到这里来捣乱？\n";

        if( query("class", me) != "bonze" )
                return "阿弥陀佛！你本是俗家人，何谈还俗？\n";

        set_temp("pending/quit_bonze", 1, me);
        command("heng");
        command ("say 还俗？好！你滚出我们峨嵋派，找别人替你还俗去吧！\n");
        return "你好好的给我安心修炼，以后降妖除魔，别天天满脑子不正经。\n";
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/huifeng-jian/mie", me) )
                return "这招我不是已经教过你了吗？自己下去多练吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("huifeng-jian", 1) < 1)
                return "你连回风拂柳剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<1000 )
                return "哼，你在本派中无所作为，这一招我暂时还不能传你。";

        if (me->query_skill("force") < 180)
                return "你的内功修行太浅，怎能使出这回风拂柳剑法中的精妙之处？";

        if (me->query_skill("huifeng-jian", 1) < 120)
                return "你回风拂柳剑法尚未修炼得精深，哪里能领会其中的微妙之处？";

        if( query("shen", me)<30000 )
                return "哼！你行侠仗义的事情还做得不够！做得不够！";

        message_sort(HIY "\n$n" HIY "微微点了点头，不露半点声色，将$N" HIY
                     "招至跟前，在耳边秘密的说了些什么。$N" HIY "听后会心的"
                     "一笑，似乎明白了什么。\n\n" NOR, me, this_object());

        command("say 以后对那些妖人不要手软，一上来就用这招！");
        tell_object(me, HIC "你学会了「灭剑」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("huifeng-jian"))
                me->improve_skill("huifeng-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huifeng-jian/mie", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/huifeng-jian/jue", me) )
                return "你自己多练练，降妖除魔就靠你们这些人了！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("huifeng-jian", 1) < 1)
                return "你连回风拂柳剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<1800 )
                return "哼，你在本派中无所作为，这一招我暂时还不能传你。";

        if (me->query_skill("force") < 300)
                return "你的内功修行太浅，怎能使出这回风拂柳剑法中的精妙之处？";

        if (me->query_skill("huifeng-jian", 1) < 180)
                return "你回风拂柳剑法尚未修炼得精深，哪里能领会其中的微妙之处？";

        if( query("shen", me)<30000 )
                return "哼！你行侠仗义的事情还做得不够！做得不够！";

        message_sort(HIY "\n$n" HIY "呆呆的望着天空，激动万分，口中喃喃道"
                     "：“我峨嵋派真是后继有人啊。”过了半晌，$n" HIY "才"
                     "回过神来，在$N" HIY "耳边秘密的说了些什么。\n\n" NOR,
                     me, this_object());

        command("say 听好了！以后对那些妖人不要手软，见一个杀一个，"
                "见两个杀一双！");
        tell_object(me, HIC "你学会了「绝剑」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("huifeng-jian"))
                me->improve_skill("huifeng-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huifeng-jian/jue", 1, me);
        addn("family/gongji", -1800, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/sixiang-zhang/xing", me) )
                return "你自己多练练，降妖除魔就靠你们这些人了！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("sixiang-zhang", 1) < 1)
                return "你连四象掌法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<80 )
                return "哼，你在本派中无所作为，这一招我暂时还不能传你。";

        if (me->query_skill("force") < 100)
                return "你的内功修行太浅，尚且学不了这一招。";

        if (me->query_skill("sixiang-zhang", 1) < 70)
                return "你的四象掌法火候未到，尚且学不了这一招。";

        if( query("shen", me)<5000 )
                return "哼！你行侠仗义的事情还做得不够！做得不够！";

        message_sort(HIY "\n$n" HIY "略微点了点头，说道：“看好了！”随即"
                     "一声清啸，双掌纷飞贯出，掌影重重叠叠，虚实难辨，全全"
                     "笼罩$N" HIY "全身。\n\n" NOR, me, this_object());

        command("say 刚才我所施展的便是这式星罗棋布，你自己下去练习吧。");
        tell_object(me, HIC "你学会了「星罗棋布」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("sixiang-zhang"))
                me->improve_skill("sixiang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sixiang-zhang/xing", 1, me);
        addn("family/gongji", -80, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/jinding-zhang/bashi", me) )
                return "你自己多练练，降妖除魔就靠你们这些人了！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("jinding-zhang", 1) < 1)
                return "你连金顶绵掌都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<250 )
                return "哼，你在本派中无所作为，这一招我暂时还不能传你。";

        if (me->query_skill("force") < 120)
                return "你的内功修行太浅，尚且学不了这一招。";

        if (me->query_skill("jinding-zhang", 1) < 100)
                return "你的金顶绵掌火候未到，尚且学不了这一招。";

        if( query("shen", me)<8000 )
                return "哼！你行侠仗义的事情还做得不够！做得不够！";

        message_sort(HIY "\n$n" HIY "朝着$N" HIY "赞许的点了点头，说道：“"
                     "既然如此，今日我便传授你此招！”说完$n" HIY "深深吸"
                     "了一口气，站起身来，提于全身功力于双掌猛力拍出，顿时"
                     "只听“砰”的一声巨响，$N" HIY "面前那张青石桌案应声"
                     "而碎，尘沙四起，石屑飞溅。直看得$N" HIY "目瞪口呆。"
                     "\n\n" NOR, me, this_object());

        command("say 这招并不复杂，只须下去后勤加练习便可。");
        tell_object(me, HIC "你学会了「八式合一」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("jinding-zhang"))
                me->improve_skill("jinding-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinding-zhang/bashi", 1, me);
        addn("family/gongji", -250, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/jieshou-jiushi/jie", me) )
                return "这招我不是已经教过你了吗？自己下去多练吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("jieshou-jiushi", 1) < 1)
                return "你连截手九式都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<300 )
                return "哼，你在本派中碌碌无为，这一招我暂时还不能传你。";

        if( query("max_neili", me)<850 )
                return "你的内力修行太浅，尚且学不了这一招。";

        if (me->query_skill("force") < 120)
                return "你的内功修行太浅，尚且学不了这一招。";

        if (me->query_skill("jieshou-jiushi", 1) < 100)
                return "你的截手九式火候未到，尚且学不了这一招。";

        if( query("shen", me)<12000 )
                return "哼！你行侠仗义的事情还做得不够！做得不够！";

        message_sort(HIY "\n$n" HIY "甚喜，对$N" HIY "点头道：“不错，不"
                     "错。你这孩子，真不亏了我平时的教诲。”说完将$N" HIY
                     "招至跟前，细说良久。\n\n" NOR, me, this_object());

        command("say 这招用来对付妖人再合适不过。你自己下去练吧。");
        tell_object(me, HIC "你学会了「截筋断脉」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("jieshou-jiushi"))
                me->improve_skill("jieshou-jiushi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jieshou-jiushi/jie", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/tiangang-zhi/ling", me) )
                return "这招我不是已经教过你了吗？自己下去多练吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("tiangang-zhi", 1) < 1)
                return "你连天罡指穴法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<250 )
                return "哼，你在本派中碌碌无为，这一招我暂时还不能传你。";

        if( query("max_neili", me)<800 )
                return "你的内力修行太浅，尚且学不了这一招。";

        if (me->query_skill("force") < 100)
                return "你的内功修行太浅，尚且学不了这一招。";

        if (me->query_skill("tiangang-zhi", 1) < 100)
                return "你的天罡指穴法火候未到，尚且学不了这一招。";

        if( query("shen", me)<10000 )
                return "哼！你行侠仗义的事情还做得不够！做得不够！";

        message_sort(HIY "\n$n" HIY "甚喜，对$N" HIY "点头道：“不错，不"
                     "错。你这孩子，真不亏了我平时的教诲。”说完将$N" HIY
                     "招至跟前，细说良久。\n\n" NOR, me, this_object());

        command("say 刚才我所说的你都记住了吗？自己下去练吧。");
        tell_object(me, HIC "你学会了「凌空指穴」。\n" NOR);

        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tiangang-zhi"))
                me->improve_skill("tiangang-zhi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tiangang-zhi/ling", 1, me);
        addn("family/gongji", -250, me);
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();
        if( query("can_perform/yanxing-dao/huan", me) )
                return "这招我不是已经教过你了吗？自己下去多练吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("yanxing-dao", 1) < 1)
                return "你连雁行刀法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<300 )
                return "哼，你在本派中碌碌无为，这一招我暂时还不能传你。";

        if( query("max_neili", me)<800 )
                return "你的内力修行太浅，尚且学不了这一招。";

        if (me->query_skill("force") < 120)
                return "你的内功修行太浅，尚且学不了这一招。";

        if (me->query_skill("yanxing-dao", 1) < 80)
                return "你的雁行刀法火候未到，尚且学不了这一招。";

        if( query("shen", me)<15000 )
                return "哼！你行侠仗义的事情还做得不够！做得不够！";

        message_sort(HIY "\n$n" HIY "微微一笑，沉声道：“要修成这一招，须"
                     "得通晓四象八卦之学。”$N" HIY "点了点头，朗声说道："
                     "“阳分太阳、少阴，阴分少阳、太阴，是为四象。太阳为乾"
                     "兑，少阴为离震，少阳为巽坎，太阴为艮坤。乾南、坤北、"
                     "离东、坎西、震东北、兑东南、巽西南、艮西北。自震至乾"
                     "为顺，自巽至坤为逆。正如师父所教：天地定位，山泽通气"
                     "，雷风相薄，水火不相射，八卦相错。数往者顺，知来者逆"
                     "。”$n" HIY "听后大喜，说道：“不错，不错。我果然没"
                     "看错你，这便传授你此招！”$n" HIY "在$N" HIY "耳畔低"
                     "声细说良久，$N" HIY "听后会心的一笑，似乎领悟到了什"
                     "么。\n\n" NOR, me, this_object());

        command("say 刚才我所说的须记牢了，自己下去练吧。");
        tell_object(me, HIC "你学会了「无形幻影」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("yanxing-dao"))
                me->improve_skill("yanxing-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yanxing-dao/huan", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();
        if( query("can_perform/emei-jian/xian", me) )
                return "这招我不是已经教过你了吗？自己下去多练吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("emei-jian", 1) < 1)
                return "你连峨嵋剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<50 )
                return "哼，你在本派中无所作为，这一招我暂时还不能传你。";

        if (me->query_skill("force") < 80)
                return "你的内功修行太浅，用不了这一招！";

        if (me->query_skill("emei-jian", 1) < 60)
                return "你峨嵋剑法尚未修炼得精深，没法用这招。";

        if( query("shen", me)<3000 )
                return "哼！你行侠仗义的事情还做得不够！做得不够！";

        message_sort(HIY "\n$n" HIY "微微点了点头，不露半点声色，将$N" HIY
                     "招至跟前，在耳边轻声的说了些什么。$N" HIY "听后会心"
                     "的一笑，似乎明白了什么。\n\n" NOR, me, this_object());

        command("say 这招很简单，下去后稍加练习便成。");
        tell_object(me, HIC "你学会了「佛光初现」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("emei-jian"))
                me->improve_skill("emei-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/emei-jian/xian", 1, me);
        addn("family/gongji", -50, me);
        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();
        if( query("can_perform/yitian-jian/fumo", me) )
                return "这招我不是已经教过你了吗？自己下去多练吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("yitian-jian", 1) < 1)
                return "你连倚天剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<500 )
                return "哼，你在本派中无所作为，这一招我暂时还不能传你。";

        if (me->query_skill("force") < 180)
                return "你的内功修行太浅，用不了这一招！";

        if (me->query_skill("yitian-jian", 1) < 120)
                return "你倚天剑法尚未修炼得精深，没法用这招。";

        if( query("shen", me)<20000 )
                return "哼！你行侠仗义的事情还做得不够！做得不够！";

        message_sort(HIY "\n$n" HIY "微微点了点头，不露半点声色，将$N" HIY
                     "招至跟前，在耳边轻声的说了些什么。$N" HIY "听后会心"
                     "的一笑，似乎明白了什么。\n\n" NOR, me, this_object());

        command("sigh");
        command("say 如果那柄倚天剑还在的话，用这招最爽快不过。");
        tell_object(me, HIC "你学会了「伏魔剑诀」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yitian-jian"))
                me->improve_skill("yitian-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yitian-jian/fumo", 1, me);
        addn("family/gongji", -500, me);
        return 1;
}

mixed ask_skill12()
{
        object me;

        me = this_player();
        if( query("can_perform/yitian-jian/yitian", me) )
                return "这招我不是已经教过你了吗？自己下去多练吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪里来的？快给我滚开！";

        if (me->query_skill("yitian-jian", 1) < 1)
                return "你连倚天剑法都没学，还谈什么绝招可言？";

       if (me->query_skill("force") < 200)
               return "你的内功修行太浅，用不了这一招！";

       if (me->query_skill("yitian-jian", 1) < 150)
               return "你倚天剑法尚未修炼得精深，没法用这招。";

       if( query("shen", me)<40000 )
               return "哼！你行侠仗义的事情还做得不够！做得不够！";

       message_sort(HIY "\n$n" HIY "微微点了点头，不露半点声色，将$N" HIY
                    "招至跟前，在耳边轻声的说了些什么。$N" HIY "听后会心"
                    "的一笑，似乎明白了什么。\n\n" NOR, me, this_object());

       command("sigh");
       command("say 如果那柄倚天剑还在的话，用这招最厉害不过。");
       tell_object(me, HIC "你学会了「倚天剑诀」。\n" NOR);

       if (me->can_improve_skill("sword"))
               me->improve_skill("sword", 1500000);
       if (me->can_improve_skill("yitian-jian"))
               me->improve_skill("yitian-jian", 1500000);
       me->improve_skill("martial-cognize", 1500000);
       set("can_perform/yitian-jian/yitian", 1, me);
       return 1;
}

string ask_me()
{
         object ob;
        if( query("family/family_name", this_player()) != "峨嵋派" )
                 return RANK_D->query_respect(this_player()) +
                  "非我弟子，不知此话从何谈起？";
         if (query("book_count") < 1)
                 return "你来晚了，本派的秘籍不在此处。";
         addn("book_count", -1);
         ob = new("/d/emei/obj/fojing");
         ob->move(this_player());
         return "好吧，这本「"+ob->name()+"」你拿回去好好钻研。";
}

mixed ask_skill10()
{
        object me;

        me = this_player();
        if( query("can_perform/piaoxue-zhang/yun", me) )
                return "这一招我不是已经传授予你了吗？还有什么不懂就自己下去练吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "我与阁下素无来往，不知阁下打听这个干嘛？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能学习此招，你还是走吧。";

        if (me->query_skill("piaoxue-zhang", 1) < 1)
                return "你连飘雪穿云掌都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<1800 )
                return "你对峨嵋派所作出的贡献还不够，这招我暂时不能传你。";

        if (me->query_skill("force") < 200)
                return "你的内功修行太浅，尚且学不了这一招。";

        if( query("max_neili", me)<2000 )
                return "你的内力修行太浅，尚且学不了这一招。";

        if (me->query_skill("piaoxue-zhang", 1) < 150)
                return "你的飘雪穿云掌火候未到，尚且学不了这一招。";

        if( query("shen", me)<40000 )
                return "你行侠仗义的事情还做得不够，我暂时还不能传你此招。";

        message_sort(HIY "\n$n" HIY "微微一笑，对$N" HIY "说道：“既然你内"
                     "外功均已达至如此境界，也不枉了我平时的一翻栽培。今日"
                     "我便传你此招，希望日后能将我峨嵋派发扬光大。”说完，"
                     "$n" HIY "将$N" HIY "招至跟前，在$N" HIY "耳旁轻声细说"
                     "良久。\n\n" NOR, me, this_object());

        command("nod");
        command("say 刚才我所说的你都记清了吗？记清了就下去练吧。");
        tell_object(me, HIC "你学会了「云海明灯」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("piaoxue-zhang"))
                me->improve_skill("piaoxue-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/piaoxue-zhang/yun", 1, me);
        addn("family/gongji", -1800, me);
        return 1;
}

mixed ask_skill11()
{
        object me;

        me = this_player();
        if( query("can_perform/piaoxue-zhang/zhao", me) )
                return "这一招我不是已经传授予你了吗？还有什么不懂就自己下去练吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "我与阁下素无来往，不知阁下打听这个干嘛？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能学习此招，你还是走吧。";

        if (me->query_skill("piaoxue-zhang", 1) < 1)
                return "你连飘雪穿云掌都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<2200 )
                return "你对峨嵋派所作出的贡献还不够，这招我暂时不能传你。";

        if (me->query_skill("force") < 300)
                return "你的内功修行太浅，尚且学不了这一招。";

        if( query("max_neili", me)<3500 )
                return "你的内力修行太浅，尚且学不了这一招。";

        if (me->query_skill("piaoxue-zhang", 1) < 180)
                return "你的飘雪穿云掌火候未到，尚且学不了这一招。";

        if( query("shen", me)<40000 )
                return "你行侠仗义的事情还做得不够，我暂时还不能传你此招。";

        message_sort(HIY "\n$n" HIY "轻轻拍了拍$N" HIY "的头，说道：“好"
                     "吧，难得你如此有心，今日我就将此招演示一遍，可得看"
                     "好了！”话音刚落，只见$n" HIY "狂提内劲，周身骨骼无"
                     "不噼啪作响，面赤如血，煞是惊人。随即$n" HIY "一声暴"
                     "喝，双掌携着隐隐风雷之势猛力向前拍出，顿时只听“喀"
                     "嚓”一声巨响，前方崖边一颗碗口粗的松树应声而断，断"
                     "枝仍是余势未尽，向前又飞出数丈，这才跌落至山谷之中"
                     "。须臾，便闻山谷下回声四起，在峨嵋群山中回荡了好一"
                     "阵才消失殆尽。$n" HIY "微微一笑，长吁一口气，缓缓收"
                     "回内劲，朝$N" HIY "望去，见$N" HIY "早已看得目瞪口"
                     "呆。\n\n" NOR, me, this_object());

        command("say 这招你下去后一定要勤加练习，才能发挥出它的威力。");
        tell_object(me, HIC "你学会了「佛光普照」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("piaoxue-zhang"))
                me->improve_skill("piaoxue-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/piaoxue-zhang/zhao", 1, me);
        addn("family/gongji", -2200, me);
        return 1;
}

void reset()
{
        set("book_count",10);
}

/*
void unconcious()
{
        die();
}
*/
     int recognize_apprentice(object me, string skill)
     {
             if( skill != "yitian-jian")
                         return 0;
             if (query("family/family_name", me) != "峨嵋派") return -1 ;
             if(query("family/master_name", me) == "风陵师太" )
{
             message_vision("灭绝师太对$N说道：既然是同门师妹，我就教你倚天剑法吧。\n", me);
             return 1;
     }
     }
