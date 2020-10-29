// This program is a part of NITAN MudLIB
// zhang.c 张三丰

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
// inherit F_NOCLONE;
inherit F_QUESTER;

#include <ansi.h>
#include "wudang.h"

#define CANPIAN         "/kungfu/class/wudang/obj/canpian"
// #define ZHENWU_SWORD    "/clone/unique/zhenwu_jian"
#define ZHENWU_SWORD    "/clone/lonely/zhenwu"

mixed ask_jian();
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
mixed ask_skill12();
mixed ask_medicine();
mixed ask_to_learn_jy();
int try_to_learn_jy();


void create()
{
        object ob;
        set_name("张三丰", ({ "zhang sanfeng", "zhang" }));
        set("nickname", "邋遢真人");
        set("long",
                "这就是武当派开山鼻祖、当今武林的泰山北斗张三丰真人。\n"
                "但见他身穿一袭污秽的灰布道袍，身形高大异常，须发如银，\n"
                "脸上红润光滑，笑眯眯的甚是可亲，此外也无特异情状。\n");
        set("gender", "男性");
        set("age", 100);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 14123);
        set("max_jing", 3173);
        set("wudang_book", 1);
        set("eff_jingli", 9000);
        set("max_jingli", 9000);
        set("neili", 12000);
        set("max_neili", 12000);
        set("jiali", 300);
        set("combat_exp", 6500000);
        set("score", 650000);

        set_skill("array", 600);
        set_skill("zhenwu-jianzhen", 600);
        set_skill("force", 600);
        set_skill("taiji-shengong", 600);
        set_skill("wudang-jiuyang", 600);
        set_skill("yinyun-ziqi", 600);
        set_skill("dodge", 600);
        set_skill("tiyunzong", 600);
        set_skill("cuff", 600);
        set_skill("taiji-quan", 600);
        set_skill("strike", 600);
        set_skill("wudang-zhang", 600);
        set_skill("hand", 600);
        set_skill("paiyun-shou", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("wudang-jian", 600);
        set_skill("blade", 600);
        set_skill("taiji-dao", 600);
        set_skill("taiji-jian", 600);
        set_skill("literate", 600);
          set_skill("taoism", 10000);
        set_skill("wudang-yaoli", 600);
        set_skill("medical", 600);
        set_skill("liandan-shu", 600);
        set_skill("martial-cognize", 600);
        set_skill("tianwei-zhengqi", 600);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        map_skill("hand", "paiyun-shou");
        map_skill("strike", "wudang-zhang");
        map_skill("blade", "taiji-dao");

        prepare_skill("cuff", "taiji-quan");

        create_family("武当派", 1, "开山祖师");
        set("class", "taoist");

        set("inquiry", ([
                "真武剑"     : (: ask_jian : ),
                "鹤嘴劲"     : (: ask_skill1 :),
                "震字诀"     : (: ask_skill2 :),
                "引字诀"     : (: ask_skill3 :),
                "挤字诀"     : (: ask_skill4 :),
                "粘字诀"     : (: ask_skill5 :),
                "太极图"     : (: ask_skill6 :),
                "缠字诀"     : (: ask_skill7 :),
                "随字诀"     : (: ask_skill8 :),
                "驾字诀"     : (: ask_skill9 :),
                "剑轮岚转"   : (: ask_skill10 :),
                "真武除邪"   : (: ask_skill11 :),
                "太极剑意"   : (: ask_skill12 :),
                "炼丹术"     : (: ask_medicine :),
                "制药"       : (: ask_medicine :),
                "武当九阳"   : (: ask_to_learn_jy :),
                "三黄宝腊丹" : "等你学好了炼丹术，以后自己制吧。",
                "玉清散"     : "嗯...等你通晓了炼丹术的奥妙，自己慢慢制吧。",
                "绕指柔剑"   : "唉，你去问问你莫师兄把......",
        ]));

        set("no_teach", ([
                   "wudang-jiuyang" : (: try_to_learn_jy() :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.jia" :),
                (: perform_action, "sword.sui" :),
                (: perform_action, "sword.zhuan" :),
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "cuff.tu" :),
                (: perform_action, "cuff.zhen" :),
                (: perform_action, "cuff.zhan" :),
                (: perform_action, "cuff.ji" :),
                (: perform_action, "cuff.yin" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set("master_ob", 5);
        setup();
        if (clonep())
        {
                ob = find_object(ZHENWU_SWORD);
                if (! ob) ob = load_object(ZHENWU_SWORD);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changjian");
                        ob->move(this_object());
                        ob->wield();
                }
        }
        carry_object("/d/wudang/obj/greyrobe")->wear();

        set("startroom", "/d/wudang/xiaoyuan");
        // check_clone();
}

void scan()
{
        ::scan();

        if (! query_temp("weapon"))
                map_skill("parry", "taiji-quan");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("yinyun-ziqi", 1) < 120)
        {
                command("say 我武当派乃内家武功，最重视内功心法。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应该在氤氲紫气上多下点功夫？");
                return;
        }

        if( query("shen", ob)<80000 )
        {
                command("say 学武之人，德义为先，功夫的高低倒还在其次，未练武，要先学做人。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否还做得不够？");
                return;
        }

        if (ob->query_skill("taoism", 1) < 120)
        {
                command("say 我武当派武功全从道藏悟出。");
                command("say 你对道家心法的领悟还不够。");
                command("say " + RANK_D->query_respect(ob) + "还是多研究研究道学心法吧。");
                return;
        }

        if (ob->query_int() < 32)
        {
                command("say 我武当派武功极需靠自己领悟。");
                command("say 要能达到炉火纯青之境，体质什么的倒是无关紧要，悟性却是半点也马虎不得。");
                command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
                return;
        }

        command("smile");
        command("say 想不到老道在垂死之年，又觅得一个可塑之才，真是可喜可贺。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-shengong/dian", me) )
                return "我不是已经教给你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-shengong", 1) < 1)
                return "你连太极神功都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<800 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<150000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-shengong", 1) < 100)
                return "你的太极神功修为太浅，修炼好了再来吧。";

        if( query("max_neili", me)<1500 )
                return "你的内力修为太浅，修炼高了再来吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，伸出一指，出手如风，陡然"
                     "点在$N" HIY "耳缘三分处，$N" HIY "顿时只觉$n" HIY
                     "内力的源源不绝，澎湃涌入，全身一阵酸麻，不禁大惊"
                     "失色。\n\n" NOR, me, this_object());

        command("say 你懂了吗？");
        tell_object(me, HIC "你学会了「鹤嘴劲点龙跃窍」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("taiji-shengong"))
                me->improve_skill("taiji-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-shengong/dian", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/zhen", me) )
                return "你自己慢慢体会吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你连太极拳都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<300 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<100000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "你的太极拳修为太浅，修炼好了再来吧。";

        if( query("max_neili", me)<1200 )
                return "你的内力修为太浅，修炼高了再来吧。";

        message_sort(HIY "\n$n" HIY"当不答话，缓缓站起身来，两臂慢慢提"
                     "起至胸前，左臂半环，掌面对成阴掌，右掌翻过成阳掌"
                     "，至揽雀尾、单鞭、提手上势、如封似闭、十字手、抱"
                     "虎归山……一招一式演了下去。当$n" HIY "使到上步高"
                     "探马，上步揽雀尾，单鞭而合太极，神定气闲的站在当"
                     "地。最后$n" HIY "双手合抱太极圈，这才向$N" HIY
                     "问道：“这套拳术中「虚灵顶劲、涵胸拔背、松腰垂臀"
                     "、沉肩坠肘」的诀窍，你又做到了多少？”\n\n" NOR,
                     me, this_object());

        command("say 纯以意行，最忌用力，形神合一，是这路拳法的要旨。");
        command("say 道理便是如此，下去后慢慢体会吧。");
        tell_object(me, HIC "你学会了「震字诀」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-quan/zhen", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/yin", me) )
                return "你自己慢慢体会吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你连太极拳都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<200 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<100000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "你的太极拳修为太浅，修炼好了再来吧。";

        if( query("max_neili", me)<1200 )
                return "你的内力修为太浅，修炼高了再来吧。";

        message_sort(HIY "\n$n" HIY"当不答话，缓缓站起身来，两臂慢慢提"
                     "起至胸前，左臂半环，掌面对成阴掌，右掌翻过成阳掌"
                     "，至揽雀尾、单鞭、提手上势、如封似闭、十字手、抱"
                     "虎归山……一招一式演了下去。当$n" HIY "使到上步高"
                     "探马，上步揽雀尾，单鞭而合太极，神定气闲的站在当"
                     "地。最后$n" HIY "双手合抱太极圈，这才向$N" HIY
                     "问道：“这套拳术中「虚灵顶劲、涵胸拔背、松腰垂臀"
                     "、沉肩坠肘」的诀窍，你又做到了多少？”\n\n" NOR,
                     me, this_object());

        command("say 用意不用力，太极圆转，无使自断绝。");
        command("say 道理便是如此，下去后慢慢体会吧。");
        tell_object(me, HIC "你学会了「引字诀」。\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-quan/yin", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/ji", me) )
                return "你自己慢慢体会吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你连太极拳都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<400 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<120000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "你的太极拳修为太浅，修炼好了再来吧。";

        if( query("max_neili", me)<1200 )
                return "你的内力修为太浅，修炼高了再来吧。";

        message_sort(HIY "\n$n" HIY"当不答话，缓缓站起身来，两臂慢慢提"
                     "起至胸前，左臂半环，掌面对成阴掌，右掌翻过成阳掌"
                     "，至揽雀尾、单鞭、提手上势、如封似闭、十字手、抱"
                     "虎归山……一招一式演了下去。当$n" HIY "使到上步高"
                     "探马，上步揽雀尾，单鞭而合太极，神定气闲的站在当"
                     "地。最后$n" HIY "双手合抱太极圈，这才向$N" HIY
                     "问道：“这套拳术中「虚灵顶劲、涵胸拔背、松腰垂臀"
                     "、沉肩坠肘」的诀窍，你又做到了多少？”\n\n" NOR,
                     me, this_object());

        command("say 当牢记借力而生，着力而发，反施其身。");
        command("say 道理便是如此，下去后慢慢体会吧。");
        tell_object(me, HIC "你学会了「挤字诀」。\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-quan/ji", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/zhan", me) )
                return "你自己慢慢体会吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你连太极拳都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<500 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<140000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-quan", 1) < 150)
                return "你的太极拳修为太浅，修炼好了再来吧。";

        if( query("max_neili", me)<1200 )
                return "你的内力修为太浅，修炼高了再来吧。";

        message_sort(HIY "\n$n" HIY"当不答话，缓缓站起身来，两臂慢慢提"
                     "起至胸前，左臂半环，掌面对成阴掌，右掌翻过成阳掌"
                     "，至揽雀尾、单鞭、提手上势、如封似闭、十字手、抱"
                     "虎归山……一招一式演了下去。当$n" HIY "使到上步高"
                     "探马，上步揽雀尾，单鞭而合太极，神定气闲的站在当"
                     "地。最后$n" HIY "双手合抱太极圈，这才向$N" HIY
                     "问道：“这套拳术中「虚灵顶劲、涵胸拔背、松腰垂臀"
                     "、沉肩坠肘」的诀窍，你又做到了多少？”\n\n" NOR,
                     me, this_object());

        command("say 你只需懂得太极图圆转不断、阴阳变化之意即可。");
        command("say 道理便是如此，下去后慢慢体会吧。");
        tell_object(me, HIC "你学会了「粘字诀」。\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("taiji-quan"))
                me->improve_skill("taiji-quan", 1500000);
        set("can_perform/taiji-quan/zhan", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-quan/tu", me) >= 10 )
                return "该学的你都已经学了，以后要善加利用！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-quan", 1) < 1)
                return "你连太极拳都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<3000 )
                return "你为我武当派效力还不够，这招我不忙传你。";

        if( query("shen", me)<250000 )
                return "你行侠仗义的事情做得还不够多，我不能放心传你绝招！";

        if (me->query_skill("taiji-quan", 1) < 250)
                return "你的太极拳法还不到家，要多练练！";

        if (me->query_skill("taiji-shengong", 1) < 300)
                return "你的太极神功还不到家，好好修行吧！";

        if (me->query_skill("taoism", 1) < 300)
                return "你的道学心法研究的还不够明白，要下功夫苦学才是！";

        if( query("max_jingli", me)<1000 )
                return "你的精力不济，就算传给你太极图你也难以运用。";

        message_sort(HIY "\n$n" HIY "点点头，双手轻轻划了一个圈子，地上"
                     "土雾无端吸起，又渐渐落下。\n" NOR, me,
                     this_object());

        command("say 你看懂了多少？");

        if( query("potential", me)<query("learned_points", me)+100 )
        {
                tell_object(me, "你看了半天，没有研究出什么新"
                      "的东西，看来是潜能还不够！\n");
                return 1;
        }

        addn("learned_points", 100, me);

        if( addn("can_perform/taiji-quan/tu", 1, me)<10 )
        {
                message_vision(HIY "$N" HIY "迷迷茫茫的点了"
                               "点头，深思良久。\n\n" NOR, me);
                tell_object(me, HIC "你对太极图有了一点领悟。\n" NOR);
        } else
        {
                message_sort(HIY "$N" HIY "脸露笑容，喜道：我已经明白了"
                             "，所谓真与幻象其实并无分别啊！$n" HIY "哈"
                             "哈长笑道：明白就好，明白就好，以后勿得轻易"
                             "使用，你去吧。\n\n", me, this_object());

                tell_object(me, HIC "你学会了道家密技「太极图」。\n" NOR);
                if (me->can_improve_skill("taoism"))
                        me->improve_skill("taoism", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("taiji-shengong"))
                        me->improve_skill("taiji-shengong", 1500000);
                if (me->can_improve_skill("cuff"))
                        me->improve_skill("cuff", 1500000);
                if (me->can_improve_skill("taiji-quan"))
                        me->improve_skill("taiji-quan", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                addn("family/gongji", -3000, me);
                set("can_perform/taiji-quan/tu", 10, me);
        }
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/chan", me) )
                return "你自己慢慢体会吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你连太极剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<300 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<80000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-jian", 1) < 80)
                return "你的太极剑法还不到家，要多练练！";

        message_sort(HIY "\n$n" HIY "微微笑了笑，伸出一指，以指作剑，开"
                     "始慢慢的演示剑招。从起手势一直到五十三式「指南针」"
                     "，双手同时画圆，复成第五十四式「持剑归原」。直待一"
                     "套剑法演示完毕，$n" HIY "这才向$N" HIY "问到：“这"
                     "太极剑招中的剑意，你又明白了多少？”\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 你只需记住剑意无定，绵绵不绝便成。");
        command("say 道理便是如此，下去后慢慢体会吧。");
        tell_object(me, HIC "你学会了「缠字诀」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/chan", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/sui", me) )
                return "你自己慢慢体会吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你连太极剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<200 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<80000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-jian", 1) < 60)
                return "你的太极剑法还不到家，要多练练！";

        message_sort(HIY "\n$n" HIY "微微笑了笑，伸出一指，以指作剑，开"
                     "始慢慢的演示剑招。从起手势一直到五十三式「指南针」"
                     "，双手同时画圆，复成第五十四式「持剑归原」。直待一"
                     "套剑法演示完毕，$n" HIY "这才向$N" HIY "问到：“这"
                     "太极剑招中的剑意，你又明白了多少？”\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 讲究从心而发，从心而收，便能圆转如意。");
        command("say 道理便是如此，下去后慢慢体会吧。");
        tell_object(me, HIC "你学会了「随字诀」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/sui", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/jia", me) )
                return "你自己慢慢体会吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你连太极剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<600 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<100000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-jian", 1) < 150)
                return "你的太极剑法还不到家，要多练练！";

        message_sort(HIY "\n$n" HIY "微微笑了笑，伸出一指，以指作剑，开"
                     "始慢慢的演示剑招。从起手势一直到五十三式「指南针」"
                     "，双手同时画圆，复成第五十四式「持剑归原」。直待一"
                     "套剑法演示完毕，$n" HIY "这才向$N" HIY "问到：“这"
                     "太极剑招中的剑意，你又明白了多少？”\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 借力打力，四两拨千斤，是之为太极。");
        command("say 道理便是如此，下去后慢慢体会吧。");
        tell_object(me, HIC "你学会了「驾字诀」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/jia", 1, me);
        addn("family/gongji", -600, me);

        return 1;
}

mixed ask_skill10()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/zhuan", me) )
                return "你自己慢慢体会吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你连太极剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<800 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<120000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-jian", 1) < 160)
                return "你的太极剑法还不到家，要多练练！";

        message_sort(HIY "\n$n" HIY "微微笑了笑，伸出一指，以指作剑，开"
                     "始慢慢的演示剑招。从起手势一直到五十三式「指南针」"
                     "，双手同时画圆，复成第五十四式「持剑归原」。"
                     "太极剑招中的剑意，你又明白了多少？”\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 心无拘囿，以意驭剑。");
        command("say 道理便是如此，下去后慢慢体会吧。");
        tell_object(me, HIC "你学会了「剑轮岚转」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/zhuan", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill11()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/zhenwu", me) )
        return "自己好好多练习吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("taiji-jian", 1) < 1)
                return "你连太极剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<2000 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<120000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！";

        if (me->query_skill("taiji-jian", 1) < 180)
                return "你的太极剑法还不到家，要多练练！";

        message_sort(HIY "\n$n" HIY "微微颔首，随手拣起一根树枝向$N" HIY
                     HIY "扫来，$N" HIY "见来招平淡无奇，心中颇为疑惑，"
                     "只是随手一挡。忽然只见$n" HIY "剑势大变，气度非凡"
                     "，变化无穷，$N" HIY "大吃一惊，慌乱不迭。\n\n" NOR,
                     me, this_object());

        command("say 你可明白了？");
        tell_object(me, HIC "你学会了「真武除邪」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/taiji-jian/zhenwu", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill12()
{
        object me;

        me = this_player();
        if( query("can_perform/taiji-jian/jian", me) )
                return "自己好好多练习吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

/*
        if( !query("reborn/times", me) )
                return notify_fail("你还没有经历转世重生的考验，无法领悟此招真谛。\n");
*/
                
        if (me->query_skill("taiji-jian", 1) < 1)
                return "你连太极剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<5000 )
                return "你为我武当派效力还不够，这招我先不忙传你。（需要5000点门派贡献）";

        if( query("shen", me)<500000 )
                return "你行侠仗义的事情做的还很不够，我不能传你绝招！（需要正气50万）";

        if (me->query_skill("taiji-jian", 1) < 1000)
                return "你的太极剑法还不到家，要多练练！";

        if (me->query_skill("tianwei-zhengqi", 1) < 200)
                return "你的门派技能天威正气还没有修炼到家，要多练练！";
        
        message_sort(HIY "\n$n" HIY "身形一转，手中之剑轻灵而出，犹如碧波荡漾，蜿蜒"
                              "而出，形态飘逸潇洒之极，颇具$HIG$太極$HIY$之意……\n\n$N" 
                              HIY "接着道：这招的关键就是要领悟太极真意，从而将太极剑"
                              "威力发挥到极至。\n\n" NOR, me, this_object());

        command("haha");
        command("say 你可明白了？");        
        tell_object(me, HIC "你学会了「太極劍意」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("taiji-jian"))
                me->improve_skill("taiji-jian", 1500000);
        if (me->can_improve_skill("martial-cognize"))             
                me->improve_skill("martial-cognize", 1500000);
                
        set("can_perform/taiji-jian/jian", 1, me);
        addn("family/gongji", -5000, me);

        return 1;
}

mixed ask_jian()
{
        int cost;
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "武当派" )
                        message_vision(CYN "$N" CYN "大怒，对$n" CYN "道：“你身为武当弟子，"
                                       "反而误入魔道，还不快快醒转？”\n" NOR,
                                       this_object(), me);
                else
                message_vision(CYN "$N" CYN "大怒，对$n" CYN "喝道：“好一个邪魔外"
                               "道，居然敢窥测真武剑？”\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "武当派" )
                return "真武剑是我们武当镇派之宝，你打听它干什么？";

        if( query("family/master_id", me) != query("id") )
                return "只有我的弟子才能用真武剑，你还是请回吧。";

        if( query("shen", me)<60000 )
                return "你行侠仗义的事情做得不够，我不能把真武剑交给你。";

        if( query("family/first", me) ) cost = 250;
        else cost = 500;
        if( query("family/gongji", me) < cost )
                return "你为我武当派效力还不够，等你拥有足够的师门功绩再来兑换真武剑使用时间吧。";

        ob = find_object(ZHENWU_SWORD);
        if (! ob) ob = load_object(ZHENWU_SWORD);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "真武剑不是在你的手中么，怎么反而来找我呢？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "我已经把真武剑已经借出去了。";

                if( query("family/master_id", owner) == query("id") )
                        return "真武剑现在在"+query("name", owner)+
                               "手中，你要想用就去找他吧。";
                else
                        return "真武剑现在落在"+query("name", owner)+
                               "手中，你去把他找回来吧。";
        }

        ob->move(this_object());
        ob->start_borrowing();
        message_vision(CYN "$N" CYN "点点头道：“好，你用这真武剑要多作一些行"
                       "侠仗义的事情！”\n" NOR, this_object(), me);
        command("give zhenwu jian to "+query("id", me)); 
        addn("family/gongji", -cost, me);
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != ZHENWU_SWORD)
        {
                command("say 你给我这种东西干什么？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 多谢这位" + RANK_D->query_respect(me) + "将真武剑交回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}

mixed ask_medicine()
{
        object me;
        object ob;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
        {
                command("say 你是什么人，打听我的医书有何目的？");
                return 1;
        }

        if ((int)me->query_skill("liandan-shu", 1) < 100)
        {
                command("say 你对炼丹术的了解太浅，等你学得再"
                        "好一些我才能把秘本传与你。");
                return 1;
        }

        if (query("wudang_book") < 1)
        {
                command("say 真是可惜，你来晚了，书我已经借出去了。");
                return 1;
        }

        addn("wudang_book", -1);
        ob = new("/clone/book/wudang");
        message_vision("$n翻出一本泛黄的薄册子递给$N，叮嘱"
                       "道：“唔，就是这本，好好看。”\n",
                       me, this_object());
        ob->move(me, 1);
        return 1;
}

/*
mixed ask_to_learn_jy()
{
        object *obs, obj, player = this_player();

        if( query("family/master_id", player) != "zhangsanfeng" )
        {
                return "太极神功是我武当派镇派之宝。\n";
        }
        switch (random(10))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
                return "先师觉远大师传授经文，我所学不全，至今虽闭关数次，"+
                       "苦苦钻研，仍只能想通得三四成。\n";
        case 5:
        case 6:
        case 7:
        case 8:
                return "先师觉远大师学得《九阳真经》，圆寂之前背诵经文，郭襄女侠、"+
                       "少林派无色大师和我三人各自记得一部分，\n" +
                       "因而武当、峨嵋、少林三派武功大进，数十年来分庭抗礼，名震武林。\n";
        case 9:
                if (player->query_skill("taiji-shengong", 1) < 200)
                {
                        return "你的功力尚浅，好好学全了武当太极功再说吧。\n";
                }

                obj = 0;
                obs = filter_array(children(CANPIAN), (: clonep :));
                if (sizeof(obs) > 0) obj = obs[0];

                if (objectp(obj) && objectp(environment(obj)) &&
                    userp(environment(obj)))
                {
                        return "九阳神功残篇被你师兄弟借走了，你去问他们吧\n";
                }
                if (! objectp(obj)) obj = new(CANPIAN);
                obj->move(player);
                message_vision("$N给$n一部九阳神功残篇。\n", this_object(), player);
                command("rumor"+query("name", this_player())+"弄到了一部"NOR+YEL"九阳神功残篇"HIM"。"NOR);
                return "我将心中记得的一些九阳神功笔录在此，\n"+
                       "你可找一位少林派高手与之共同参悟(canwu)，也好让这功夫不至于失传。\n";
        }
        return 0;
}
*/

mixed ask_to_learn_jy()
{
        object ob;
        object me;
        me = this_player();

        if( query("can_learn/jiuyang-shengong/wudang", me) )
                return "老道已经答应传授你武当九阳功了，你怎么还那么罗嗦？";

        if( !query("can_learn/jiuyang-shengong/kunlun", me) )
                return "昔日《九阳真经》在我师父觉远大师手中丢失，现在也不知道流落何方。";

        if( !query("can_learn/jiuyang-shengong/shaolin", me) )
                return "唉，如果当时能够追回《九阳真经》，觉远大师也不至于落难。";

        message_vision(CYN "\n张三丰仔细打量了$N" CYN "好一阵，目光陡然一亮。\n\n" NOR, me);

        command("say 你不就是当年还送经书予觉远大师之人吗？");
        command("say 所谓‘大恩不言谢’，这九阳神功老道倒是通晓一点，现已化为武当九阳功。");
        command("say 如果阁下不嫌弃，老道倒是可以将这套九阳功传授于你。");

        tell_object(me, HIC "张三丰同意传授你「武当九阳功」。\n" NOR);

        if (me->can_improve_skill("martial-cognize"))
                improve_skill("martial-cognize", 1500000);

        set("can_learn/jiuyang-shengong/wudang", 1, me);
        return 1;
}

int try_to_learn_jy()
{
        object me = this_player();

        if( !query("can_learn/jiuyang-shengong/wudang", me) )
        {
                if( query("family/master_id", me) != query("id") )
                {
                        command("say 武当九阳神功乃是九阳神功的分支，我少"
                                "年时得师父觉远大师所授。");
                        command("say 但阁下与贫道素不相识，怎谈得上“指点"
                                "”二字？");
                        return -1;
                } else
                {
                        command("say 武当九阳神功乃是九阳神功的分支，我少"
                                "年时得师父觉远大师所授。");
                        command("say 虽然这武功在我手里有所改动，但它还是"
                                "少林的武功，就算是我的弟子也不传授。");
                        return -1;
                }
        }

        if (me->query_skill("wudang-jiuyang") > 400)
        {
                command("say 你的武当九阳功力已颇为深厚了，以后你就自己研究吧。");
                return -1;
        }

        if( query("shen", me)<0 )
        {
                command("say 老道倒是有心传你九阳功，可是你中邪魔外道如此之深。");
                command("say 等你改过自新后再来找老道我吧。");
                return -1;
        }
        return 0;
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/jiuyang-shengong/wudang", me) )
        {
                if( query("family/master_id", me) != query("id") )
                {
                        command("say 武当九阳神功乃是九阳神功的分支，我少"
                                "年时得师父觉远大师所授。");
                        command("say 但阁下与贫道素不相识，怎谈得上“指点"
                                "”二字？");
                        return -1;
                } else
                {
                        command("say 武当九阳神功乃是九阳神功的分支，我少"
                                "年时得师父觉远大师所授。");
                        command("say 虽然这武功在我手里有所改动，但它还是"
                                "少林的武功，就算是我的弟子也不传授。");
                        return -1;
                }
        }

        if (skill != "wudang-jiuyang")
        {
                command("say 武学杂而不精也是无用，你还是专心学习武当九阳功吧。");
                return -1;
        }
        return 1;
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

        case "纵字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tiyunzong/zong",
                           "name"    : "纵字诀",
                           "sk1"     : "tiyunzong",
                           "lv1"     : 150,
                           "sk2"     : "dodge",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 600,
                           "shen"    : 24000, ]));
                break;

        case "连字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/taiji-jian/lian",
                           "name"    : "连字诀",
                           "sk1"     : "taiji-jian",
                           "lv1"     : 120,
                           "sk2"     : "taiji-shengong",
                           "lv2"     : 120,
                           "gongxian": 800,
                           "neili"   : 1400,
                           "shen"    : 28000, ]));
                break;
        case "按字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/taiji-quan/an",
                           "name"    : "按字诀",
                           "sk1"     : "taiji-quan",
                           "lv1"     : 200,
                           "sk2"     : "taiji-shengong",
                           "lv2"     : 200,
                           "gongxian": 800,
                           "neili"   : 1400,
                           "shen"    : 28000, ]));
                break;

/*
        case "太极剑意" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/taiji-jian/jian",
                           "name"    : "太极剑意",
                           "sk1"     : "taiji-jian",
                           "lv1"     : 1000,
                           "sk2"     : "taiji-shengong",
                           "lv2"     : 1000,
                           "gongxian": 3000,
                           "neili"   : 2000,
                           "reborn"  : 1,
                           "shen"    : 28000, ]));
                break;
*/

        default:
                return 0;
        }
}
