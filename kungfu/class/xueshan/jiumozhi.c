// This program is a part of NT MudLIB
// /kungfu/class/xueshan/jiumozhi.c 鸠摩智

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "xueshan.h"

mixed ask_me();
mixed ask_skill();

void create()
{
        set_name("鸠摩智", ({ "jiumo zhi", "zhi" ,"ming wang"}));
        set("nickname", HIG "大轮明王" NOR);
        set("long",@LONG
他就是雪山寺的掌门，人称大轮明王的鸠摩智。他对佛法有精深的研究。
身穿一件大红袈裟，头带僧帽。
LONG
        );
        set("title","雪山寺掌门");
        set("gender", "男性");
        set("age", 60);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 32);
        set("int", 40);
        set("con", 31);
        set("dex", 31);

        set("max_qi", 5800);
        set("max_jing", 2900);
        set("neili", 7100);
        set("max_neili", 7100);
        set("jiali", 100);
        set("level", 40);
        set("combat_exp", 2500000);

        set_skill("force", 600);
        set_skill("xiaowuxiang", 600);
        set_skill("mizong-neigong", 600);
        set_skill("dodge", 600);
        set_skill("shenkong-xing", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("sword", 600);
        set_skill("mingwang-jian", 600);
        set_skill("hammer", 600);
        set_skill("dali-chu", 600);
        set_skill("xiangmo-chu", 600);
        set_skill("lamaism", 600);
        set_skill("literate", 600);
        set_skill("strike", 600 );
        set_skill("huoyan-dao", 600);
        set_skill("cuff", 600);
        set_skill("yujiamu-quan", 600);
        set_skill("hand", 600);
        set_skill("dashou-yin", 600);
        set_skill("mizong-zhenyan", 600);
        set_skill("martial-cognize", 600);
        set_skill("longxiang-gong", 600);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");
        map_skill("strike","huoyan-dao");
        map_skill("cuff", "yujiamu-quan");
        map_skill("hammer", "xiangmo-chu");

        prepare_skill("strike", "huoyan-dao");
        prepare_skill("hand", "dashou-yin");

        create_family("密宗", 1, "掌门");
        set("class", "bonze");

        set("inquiry", ([
                "绝招" : (: ask_me :),
                "绝技" : (: ask_me :),
                "焚身" : (: ask_me :),
                "天寰神炎" : (: ask_skill :),
        ]));

        set("master_ob", 5);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xueshan/obj/r-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",50);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/huoyan-dao/fen", me) )
                return "绝技你已经学会了，剩下的就要靠你自己多练习了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "既然不是我们雪山寺之人，有什么好谈的。";

        if (me->query_skill("huoyan-dao", 1) < 120)
                return "你的火焰刀法修为还不够，等你练好了再说吧！";

        if( query("family/gongji", me)<300 )
                return "你为雪山寺效力不够，这招暂时还不能传你。";

        message_vision(HIC "$n" HIC "右掌一竖，几路无形刀气袭击向$N"
                       HIC "，$N" HIC "连忙伸手格挡，不禁发现$n"
                       HIC "的内力运用可谓是奥妙无穷！\n" NOR,
                       me, this_object());
        command("simle");
        tell_object(me, HIG "你通晓了焚身的奥妙。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 90000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huoyan-dao/fen", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

/*
        if( query("gender", ob) != "男性" )
        {
                command("say 修习密宗内功需要纯阳之体。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
        }
*/

        if( query("class", ob) != "bonze" )
        {
                command("say 我佛门的清规戒律甚多。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
        }

        if( query("family/family_name", ob) != "密宗" )
        {
                command("say 这位" + RANK_D->query_respect(ob) +
                        "既非本寺弟子，还是请回吧！");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 150) {
                command("say 入我雪山寺，修习密宗心法是首要的。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "是否还应该多多钻研本门的心法？");
                return;
        }

        command("recruit "+query("id", ob));
        set("title", HIY"法王"NOR, ob);
}

mixed ask_skill()
{
        object me;

        me = this_player();

        if( query("can_perform/huoyan-dao/yan", me) )
                return "你又来干什么？自己下去多练。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "我又不认识你，打听这个干什么？";

        if (me->query_skill("huoyan-dao", 1) < 1)
                return "你连无上火焰刀都没学，哪里来绝招？";

        if( query("family/gongji", me)<400 )
                return "你为雪山寺效力不够，这招暂时还不能传你。";

        if( query("shen", me)>-3000 )
                return "你为人太过心软，这招暂时还不能传你。";

        if (me->query_skill("force") < 120)
                return "你的内功修为不足，还学不了这一招。";

        if( query("max_neili", me)<800 )
                return "你的内力修为不足，还是修炼高点再来吧。";

        if (me->query_skill("huoyan-dao", 1) < 80)
                return "等你把火焰刀练熟了再来找我。";

        message_sort(HIY "\n$n" HIY "对$N" HIY "点了点头，喝道：“瞧仔"
                     "细了。”话音刚落，只见$n" HIY "高举手中的刚刀，在"
                     "空中挥舞成盘，气势惊人！便在此时，那柄刚刀已携带"
                     "着震天撞击之声猛然击落。直把$N" HIY "看得目瞪口呆"
                     "。\n\n" NOR, me, this_object());

        command("nod");
        command("say 看明白了就自己下去练吧。");
        tell_object(me, HIC "你学会了「天寰神炎」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huoyan-dao/yan", 1, me);
        addn("family/gongji", -400, me);

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

        case "修罗降世" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huoyan-dao/xiuluo",
                           "name"    : "修罗降世",
                           "sk1"     : "huoyan-dao",
                           "lv1"     : 100,
                           "sk2"     : "strike",
                           "lv2"     : 120,
                           "gongxian": 800, ]));
                break;

        case "红莲火" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huoyan-dao/honglian",
                           "name"    : "红莲火",
                           "sk1"     : "huoyan-dao",
                           "lv1"     : 150,
                           "sk2"     : "strike",
                           "lv2"     : 150,
                           "gongxian": 800, ]));
        case "十龙十象" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                        ([ "perform" : "can_perform/longxiang-gong/longxiang", 
                           "name"    : "十龙十象", 
                           "sk1"     : "longxiang-gong", 
                           "lv1"     : 1000, 
                           "sk2"     : "force", 
                           "lv2"     : 1000,
                           "reborn"  : 1,
                           "gongxian": 3000, ])); 
                break; 
                break;
        default:
                return 0;
        }
}

