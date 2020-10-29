// This program is a part of NT MudLIB
// su.c 苏荃

#include "shenlong.h"

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_huimou();
mixed ask_hengchen();
mixed ask_huixiang();
void create()
{
        set_name("苏荃", ({ "su quan", "su" }));
        set("title",  HIY"神龙教"NOR"教主夫人" );
        set("long", "她就是神龙教教主洪安通的夫人。\n");
        set("gender", "女性");
        set("age", 23);
        set("attitude", "friendly");
        set("str", 35);
        set("int", 30);
        set("con", 30);
        set("dex", 38);

        set("max_qi", 3500);
        set("max_jing", 1800);
        set("neili", 3700);
        set("max_neili", 3700);
        set("jiali", 50);
        set("level", 30);
        set("combat_exp", 620000);
        set("shen_type", -1);

        set_skill("force", 450);
        set_skill("shenlong-xinfa", 450);
        set_skill("dodge", 480);
        set_skill("yixing-bufa", 460);
        set_skill("hand", 450);
        set_skill("sword", 450);
        set_skill("meiren-sanzhao", 450);
        set_skill("strike", 480);
        set_skill("shenlong-bashi", 450);
        set_skill("huagu-mianzhang", 420);
        set_skill("parry", 450);
        set_skill("staff", 450);
        set_skill("shedao-qigong", 420);
        set_skill("literate", 400);
        set_skill("medical", 400);
        set_skill("shenlong-mixin", 400);
        set_skill("martial-cognize", 200);
        set_skill("shenlong-jian", 400);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixing-bufa");
        map_skill("strike", "huagu-mianzhang");
        map_skill("hand", "shenlong-bashi");
        map_skill("sword", "shenlong-jian");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");

        create_family("神龙教", 1, "教主夫人");

        set("inquiry", ([
                "神龙教" : "一般人是入不了我神龙教的(join shenlongjiao)。",
                "入教"   : "一般人是入不了我神龙教的(join shenlongjiao)。",
                "退教"   : "哈哈哈哈！退教？这么多年我还真听过几起，不过他们已经都死了。",
                "口号"   : "万年不老！永享仙福！寿与天齐！文武仁圣！",
                "rujiao" : "一般人是入不了我神龙教的(join shenlongjiao)。",
                "tuijiao": "哈哈哈哈！退教？这么多年我还真听过几起，不过他们已经都死了。",
              "贵妃回眸" : (: ask_huimou :),
              "小怜横陈" : (: ask_hengchen :),
              "飞燕回翔" : (: ask_huixiang :),
        ]));

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: command("smile") :),
                (: command("haha") :),
                (: command("chat 凭你这" + RANK_D->query_rude(this_player())+",也敢在太岁爷头上动土?\n") :),
                (: command("say 你活得不耐烦了找死啊？\n") :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );
        set("master_ob", 5);
        setup();
        carry_object("/d/shenlong/npc/obj/ycloth")->wear();
        carry_object(__DIR__"obj/duanjian")->wield();
        add_money("silver", 50);
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
        add_action("do_join", "join");
}

void greeting(object ob)
{
        object obj;
        if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                   set("combat_exp", 100000);
                   set("qi", 100);
                   set("jing", 100);
        }
}

void attempt_apprentice(object ob)
{
        command("say 好吧，你就和我学武功吧。");
        command("recruit "+query("id", ob));
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

        case "玉女无情" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/meiren-sanzhao/wuqing",
                           "name"    : "玉女无情",
                           "sk1"     : "meiren-sanzhao",
                           "lv1"     : 100,
                           "sk2"     : "sword",
                           "lv2"     : 100,
                           "sk3"     : "force",
                           "lv3"     : 100,
                           "gongxian": 600,
                           "shen"    : -10000, ]));
                break;

        default:
                return 0;
        }
}

mixed ask_huimou()
{
        object me;

         me = this_player();
         if( query("can_perform/shenlong-bashi/huimou", me) )
                return "自己多练练，少在我面前罗嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪儿来的？找死啊？";

        if( query("shen", me)>-50000 )
                return "你要好好为我神教效力，手段要更狠更毒。我才能传你这门绝招！";

        if (me->query_skill("shenlong-bashi", 1) < 150)
                return "你的神龙八式手法根基不够，还得多练习练习。";

        if (me->query_skill("force", 1) < 150)
                return "你的内功火候不足，学不成这贵妃回眸。";


         message_vision(HIY "$n" HIY "点头对你说道：“你看好了！”然后，又转身对沐剑屏说道：“剑屏，"
                     "你过来！”说罢身子微曲，纤腰轻扭，右足反踢，向沐剑屏小腹踹去。沐"
                     "剑屏连忙后缩相避，$n顺势反过身来，左手搂住沐剑屏的头颈，右手竟已"
                     "轻轻点在沐剑屏后心的穴道上。"NOR, me, this_object());

        tell_object(me, HIG "你学会了贵妃回眸。" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 150000);
        if (me->can_improve_skill("shenlong-bashi"))
                me->improve_skill("shenlong-bashi", 150000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shenlong-bashi/huimou", 1, me);
        return 1;
}

mixed ask_hengchen()
{
        object me;

        me = this_player();
        if( query("can_perform/shenlong-bashi/hengchen", me) )
        return "自己多练练，少在我面前罗嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪儿来的？找死啊？";

        if( query("shen", me)>-80000 )
                return "你要好好为我神教效力，手段要更狠更毒。我才能传你这门绝招！";

        if (me->query_skill("shenlong-bashi", 1) < 150)
                return "你的神龙八式手法根基不够，还得多练习练习。";

        if (me->query_skill("force", 1) < 150)
        return "你的内功火候不足，学不成这小怜横陈。";

        message_vision(HIY"$n" HIY "翻身卧倒并让沐剑屏伸出右足，虚踏她后腰，手中假装持刀架住她"
                       "头颈。蓦见$n脑袋向着她自己胸口钻落，沐剑屏架颈中的一刀自然落空，"
                       "她顺势在地下一个筋斗在沐剑屏胯下钻过，右手轻轻击在沐剑屏后心。"NOR,
                       me, this_object());

        command("say 这就是美女三招的第二招——「小怜横陈」。");
        tell_object(me, HIG "你学会了小怜横陈。" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 150000);
        if (me->can_improve_skill("shenlong-bashi"))
                me->improve_skill("shenlong-bashi", 150000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shenlong-bashi/hengchen", 1, me);
        return 1;
}

mixed ask_huixiang()
{
        object me;

        me = this_player();
        if( query("can_perform/shenlong-bashi/huixiang", me) )
                return "自己多练练，少在我面前罗嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪儿来的？找死啊？";

        if( query("shen", me)>-100000 )
                return "你要好好为我神教效力，手段要更狠更毒。我才能传你这门绝招！";

        if (me->query_skill("shenlong-bashi", 1) < 160)
                return "你的神龙八式手法根基不够，还得多练习练习。";

        if (me->query_skill("force", 1) < 160)
                return "你的内功火候不足，学不成这飞燕回翔。";

        message_vision(HIY"$n" HIY "让沐剑屏左手拿住她双手手腕，右手虚执兵器，架在她的肤光白腻头"
                     "颈之中，$n笑道：“看仔细了！”右足向前轻踢，脱身而出，接着双手回转"
                     "击出一招，正中沐剑屏后心。"NOR, me, this_object());

        command("say 这就是美女三招的第二招——「飞燕回翔」。");
        tell_object(me, HIG "你学会了飞燕回翔。" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 150000);
        if (me->can_improve_skill("shenlong-bashi"))
                me->improve_skill("shenlong-bashi", 150000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shenlong-bashi/huixiang", 1, me);
        return 1;
}
