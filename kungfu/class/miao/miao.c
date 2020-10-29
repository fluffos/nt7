// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
#include "miao.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();

void create()
{
        object ob;
        set_name("苗人凤", ({ "miao renfeng", "miao", "renfeng" }));
        set("gender", "男性");
        set("nickname", YEL "金面佛" NOR);
        set("title", "打遍天下无敌手");
        set("age", 48);
        set("long", @LONG
他就是号称打遍天下无敌手的「金面佛」苗人
凤。只见他脸色透黄，似乎蒙上了一层淡淡的
金纸。他身材高大魁梧，四肢修长，却是全然
不修篇幅，令人称奇。
LONG );
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 32);
        set("int", 31);
        set("con", 33);
        set("dex", 31);

        set("qi", 5500);
        set("max_qi", 5500);
        set("jing", 4000);
        set("max_jing", 4000);
        set("neili", 6800);
        set("max_neili", 6800);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 4500000);
        set("score", 20000);

        set_skill("force", 600);
        set_skill("lengyue-shengong", 600);
        set_skill("dodge", 600);
        set_skill("taxue-wuhen", 600);
        set_skill("sword", 600);
        set_skill("miaojia-jian", 600);
        set_skill("blade", 600);
        set_skill("hujia-daofa", 600);
        set_skill("strike", 600);
        set_skill("tianchang-zhang", 600);
        set_skill("parry", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
        set_skill("daojian-xiaotianwai", 800);

        map_skill("force", "lengyue-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("sword", "miaojia-jian");
        map_skill("blade", "hujia-daofa");
        map_skill("parry", "miaojia-jian");
        map_skill("strike", "tianchang-zhang");

        prepare_skill("strike", "tianchang-zhang");

        set("no_teach", ([
                "hujia-daofa"     : "胡家刀法乃是我当年从胡世兄处习得，不便外传。",
        ]));

        create_family("中原苗家", 6, "传人");

        set("inquiry", ([
                "云边摘月" : (: ask_skill1 :),
                "黄龙吐珠" : (: ask_skill2 :),
                "剑舞千秋" : (: ask_skill3 :),
                "流星赶月" : (: ask_skill4 :),
                "金面生莲" : (: ask_skill5 :),
                "胡家刀法" : "胡家刀法乃是我当年从胡世兄处习得，当真精妙无比。",
                "胡一刀"   : "当年我中了奸人毒计杀害了他，令我遗憾终生！",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.zhai" :),
                (: perform_action, "sword.zhu" :),
                (: perform_action, "sword.jian" :),
                (: perform_action, "sword.gan" :),
                (: perform_action, "strike.zhan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 中原苗家暂不开放！");
        return;

        if (! permit_recruit(ob))
                return;

        if (ob->name(1) == "苗人凤")
        {
                command("hmm");
                command("say 你怎么也取这个名字？");
                return;
        }

        if (ob->name(1) == "苗若兰")
        {
                command("hmm");
                command("say 你就不能换个别的名字？");
                return;
        }

        if (ob->name(1) == "苗鬼凤" || ob->name(1) == "苗人龙")
        {
                command("hmm");
                command("say 你安心要和我作对是不是？");
                return;
        }

        command("sigh");
        command("recruit "+query("id", ob));
        command("say 我本已打算不收徒弟，让我田家与胡、苗、范三家的纷争得以平息。");
        command("say 可是这祖传三十七势苗家剑就在我处失传，未免太过不孝。");
        return;
}

int recognize_apprentice(object me, string skill)
{
        if( query("family/family_name", me) != "关外胡家" )
        {
                command("say 你是谁？快点滚开！");
                return -1;
        }

        if( query("shen", me)<0 )
        {
                command("sigh");
                command("say 你怎能走上邪路？我可不能教你苗家剑。");
                return -1;
        }

        if( query("combat_exp", me)<400000 )
        {
                command("say 你此时功力太浅，还是先打好基础再说吧。");
                return -1;
        }

        if (skill != "miaojia-jian" && skill != "sword")
        {
                command("say 我只教你基本剑法和苗家剑法，别的就不要来烦我了！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 600)
        {
               command("say 够了！我就教你到这里吧，武功还是"
                       "要靠自己多研究才是！");
               return -1;
        }

        command("say 看在当年我中了奸人毒计杀害了胡一刀，令我遗憾终生的事上，我就传你苗家剑法。");
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/zhai", me) )
                return "自己下去练！还多说什么？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你连苗家剑法都未学，何谈绝招可言？";

        if( query("family/gongji", me)<400 )
                return "你在胡家无所作为，这招我先不忙传你。";

        if( query("shen", me)<13000 )
                return "你侠义正事做得不够，这招我先不忙传你。";

        if (me->query_skill("force") < 120)
                return "你的内功火候不足，学不成这招。";

        if( query("max_neili", me)<800 )
                return "你的内力修为不足，学不成这招。";

        if (me->query_skill("miaojia-jian", 1) < 100)
                return "你的苗家剑法火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "对$N" HIY "点了点头，随手从桌上"
                       "拈起一根筷子，慢慢的\n演示剑招。$N" HIY "只见"
                       "$n" HIY "剑势舒张，吞吐不定，瞬时之间\n已连换"
                       "数种剑势，剑法之巧妙，当真前所未闻。\n" NOR,
                       me, this_object());

        command("nod");
        command("say 此招看似复杂，其实并不难练，你下去后自己体会吧。");
        tell_object(me, HIC "你学会了「云边摘月」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/zhai", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/zhu", me) )
                return "自己下去练！还多说什么？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你连苗家剑法都未学，何谈绝招可言？";

        if( query("family/gongji", me)<600 )
                return "你在胡家无所作为，这招我先不忙传你。";

        if( query("shen", me)<15000 )
                return "你侠义正事做得不够，这招我先不忙传你。";

        if (me->query_skill("force") < 150)
                return "你的内功火候不足，学不成这招。";

        if( query("max_neili", me)<1200 )
                return "你的内力修为不足，学不成这招。";

        if (me->query_skill("miaojia-jian", 1) < 120)
                return "你的苗家剑法火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "对$N" HIY "笑了笑，随即伸出右手，"
                       "中食二指并拢，捏作\n剑诀，“嗤”的一声空点而出"
                       "，霎时破空之声骤响，一股\n气劲从指尖迸发，将$N"
                       HIY "身旁的木几穿透出一个小孔。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 此招不外乎是以剑作媒，以气伤人。");
        tell_object(me, HIC "你学会了「黄龙吐珠」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/zhu", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/qian", me) )
                return "自己下去练！还多说什么？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你连苗家剑法都未学，何谈绝招可言？";

        if( query("family/gongji", me)<1000 )
                return "你在我胡家无所作为，这招我先不忙传你。";

        if( query("shen", me)<18000 )
                return "你侠义正事做得不够，这招我先不忙传你。";

        if (me->query_skill("force") < 220)
                return "你的内功火候不足，学不成这招。";

        if( query("max_neili", me)<1800 )
                return "你的内力修为不足，学不成这招。";

        if (me->query_skill("miaojia-jian", 1) < 160)
                return "你的苗家剑法火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "长叹一声，当下也不答话，从$N" HIY
                       "处接过配剑，将三\n十七势苗家剑连环施出，霎时剑"
                       "光逼人，气芒纵横，龙吟\n不止。只见$n" HIY "所"
                       "施的三十七势剑法竟如一势，交替连\n环，一气呵成"
                       "，并无任何破绽，$N" HIY "只看得目瞪口呆。\n"
                       NOR, me, this_object());

        command("nod");
        command("say 你自己下去练习吧。");
        tell_object(me, HIC "你学会了「剑舞千秋」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/qian", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/gan", me) )
                return "自己下去练！还多说什么？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你连苗家剑法都未学，何谈绝招可言？";

        if( query("family/gongji", me)<2200 )
                return "你在胡家无所作为，这招我先不忙传你。";

        if( query("shen", me)<35000 )
                return "你侠义正事做得不够，这招我先不忙传你。";

        if (me->query_skill("force", 1) < 100)
                return "你的内功火候不足，学不成这招。";

        if( query("max_neili", me)<3000 )
                return "你的内力修为不足，学不成这招。";

        if (me->query_skill("miaojia-jian", 1) < 200)
                return "你的苗家剑法火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "凝视了$N" HIY "半天，缓缓地点了"
                       "点头。当下拔出腰间配\n剑，剑走龙蛇，白光如虹"
                       "，凝重处如山岳巍峙，轻灵处若\n清风无迹，神剑"
                       "之威，当真神鬼难测。舞到急处，$n" HIY "\n一声"
                       "大喝，手中配剑竟然离手射出，化作一道流星，直"
                       "没\n至柄插入$N" HIY "对面的墙壁中。\n" NOR,
                       me, this_object());

        command("nod");
        command("say 这招是我苗家剑法的精髓，可要勤加练习。");
        tell_object(me, HIC "你学会了「流星赶月」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);

        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);

        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/gan", 1, me);
        addn("family/gongji", -2200, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/miaojia-jian/lian", me) )
                return "自己下去练！还多说什么？";

        if (me->query_skill("miaojia-jian", 1) < 1)
                return "你连苗家剑法都未学，何谈绝招可言？";

        if( query("family/gongji", me)<1000 )
                return "你在我胡家无所作为，这招我先不忙传你。";

        if( query("shen", me)<18000 )
                return "你侠义正事做得不够，这招我先不忙传你。";

        if (me->query_skill("force") < 220)
                return "你的内功火候不足，学不成这招。";

        if( query("max_neili", me)<1800 )
                return "你的内力修为不足，学不成这招。";

        if (me->query_skill("miaojia-jian", 1) < 160)
                return "你的苗家剑法火候未到，还得多练习练习。";

        message_sort(HIY "$n哈哈一笑，对$N" HIY "赞道：不"
                     "错，不错。依照你现在苗家剑法的造诣，"
                     "我便传授你金面生莲又有何妨？说完便只"
                     "见$n从怀中摸出一本颇为古旧的小册子，"
                     "指着其中一段对$N" HIY "仔细讲解。$N"
                     HIY "听后沉思良久，若有所悟。" NOR,
                     me, this_object());

        command("nod");
        command("say 你自己下去练习吧。");
        tell_object(me, HIC "你学会了「金面生莲」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("miaojia-jian"))
                me->improve_skill("miaojia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/miaojia-jian/lian", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
}
