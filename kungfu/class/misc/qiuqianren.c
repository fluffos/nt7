#include <ansi.h>
// #include "tiezhang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

void create()
{
        set_name("裘千仞", ({ "qiu qianren", "qiu", "qianren", "ren"}));
        set("nickname", WHT "铁掌水上漂" NOR);
        set("long", "他就是威震川湘的铁掌帮的帮主铁掌水上漂裘千仞。\n"
                    "他头须皆白，身穿黄葛短衫，右手挥着一把大蒲扇。\n" );

        set("gender", "男性");
        set("age", 60);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 600000);
        set("max_qi", 600000);
        set("jing", 300000);
        set("max_jing", 300000);
        set("neili", 800000);
        set("max_neili", 800000);
        set("jiali", 1500);
        set("level", 40);
        set("combat_exp", 400000000);
        set("score", 40000);

        set_skill("force", 800);
        // set_skill("tiezhang-xinfa", 800);
        // set_skill("tianlei-shengong", 800);
        set_skill("dodge", 800);
        // set_skill("dengping-dushui", 800);
        set_skill("strike", 800);
        set_skill("parry", 800);
        set_skill("tie-zhang", 800);
        // set_skill("chuanxin-zhang", 800);
        set_skill("cuff", 800);
        // set_skill("tiexian-quan", 800);
        set_skill("unarmed", 800);
        // set_skill("feilong-zhang", 700);
        set_skill("staff", 700);
        // set_skill("tianlei-dao", 700);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        // map_skill("force", "tianlei-shengong");
        // map_skill("unarmed", "chuanxin-zhang");
        map_skill("strike", "tie-zhang");
        // map_skill("cuff", "tiexian-quan");
        map_skill("parry", "tie-zhang");
        // map_skill("dodge", "dengping-dushui");
        // map_skill("staff", "feilong-zhang");

        prepare_skill("strike", "tie-zhang");

        create_family("铁掌帮", 14, "帮主");

        set("inquiry", ([
                "绝招"    : "你要问什么绝招？",
                "绝技"    : "你要问什么绝技？",
                "铁掌掌谱": "这本秘籍不在我手里，想必已经失落很久了。",
                "上官剑南": "他是我的授业恩师，你问这个干嘛？",
                "裘千丈"  : "哼，大哥老是打着我的名号到处招摇撞骗，总有一天我要……",
                "裘千尺"  : "三妹下嫁到绝情谷去了，你问这个有什么事吗？",
                "绝情谷"  : "绝情谷公孙止那家伙不是个东西，你问这个干嘛？",
                "华山论剑": "哼，去年的华山论剑要不是因为我在闭观，哪里轮得上王重阳那牛鼻子。",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.juesha" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "strike.yin" :),
                (: perform_action, "cuff.kai" :),
                (: perform_action, "unarmed.zhui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        setup();

        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}

void attempt_apprentice(object me)
{
        string purename, name, new_name;

        command("say 铁掌帮暂不开放！\n");
        return;

         /*
        if (! permit_recruit(me))
                return;
         */

        if( query("family/family_name", me) && 
             query("family/family_name", me) == "绝情谷" && 
             query("family/master_name", me) == "裘千尺" )
        {
                command("nod");
                command("say 原来是三妹的后裔，这样也好，我们本来就是一家人。且让"
                "我先看看你的能力。\n");
                set("move_party/绝情谷—铁掌帮", 1, me);
        }

        if( query("shen", me)>-60000 )
        {
                command("heng");
                command("say 我裘千仞可不收心慈手软的人做徒弟。");
                return;
        }

        if( query("combat_exp", me)<800000 )
        {
                command("heng");
                command("say 你这点能力怎能继承我的衣钵？");
                return;
        }

        if ((int)me->query_skill("force") < 260)
        {
                command("say 要学我的铁掌绝技，内功非精纯不可，你还是先多练练吧。");
                return;
        }

        if ((int)me->query_skill("strike", 1) < 180)
        {
                command("say 要学我的铁掌绝技，需要精湛的掌法作基础，我看你在那上"
                        "面下的工夫还不够啊。");
                return;
        }

        command("say 不错，不错！");
        command("say 我就收下你了，希望你苦练铁掌神功，将之发扬光大。");
        command("recruit"+query("id", me));

        if( query("move_party/绝情谷—铁掌帮", me) && 
             query("surname", me) == "公孙" )
        {
                name=query("name", me);
                purename=query("purename", me);

                new_name = "裘" + purename;

                set("surname", "裘", me);
                set("name", new_name, me);
                delete("move_party/绝情谷—铁掌帮", me);

                command("say 公孙止那老家伙不是个东西，你以后还是跟你娘亲姓为好。");
                command("say 从今以后你就叫作" + new_name + "吧。");
        }
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/tie-zhang/juesha", me) )
                return "这招我已经教过你了，还是自己下去多多练习吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本帮素无瓜葛，何出此言？";

        if (me->query_skill("tie-zhang", 1) < 1)
                return "你连铁掌掌法都没学，何谈此言？";

        if( query("shen", me)>-100000 )
                return "心慈手软的人永远干不了大事，这招你不学也罢！";

        if (me->query_skill("tie-zhang", 1) < 200)
                return "你的铁掌掌法还练得不到家，自己下去练练再来吧！";

        if (me->query_skill("tianlei-shengong", 1) < 180)
                return "这一招需求强大的天雷真气做基础，看来你所下的功夫还不够啊！";

        if( query("family/gongji", me)<660 )
                return "你的门派贡献不够，这招我不能传你！";

        message_vision(HIY "$n" HIY "默默注视了$N" HIY "良"
                       "久，说道：“既然如此，今日我便传你"
                       "这招！我只演示一遍，你可要看仔细了"
                       "！”\n\n" NOR + HIR "$n" HIR "说完"
                       "一声怒喝，体内所积存数十载的天雷真"
                       "气澎湃而发，衣衫鼓动，双臂陡然暴\n"
                       "长数尺。只听四周破空之声骤然响之，"
                       "$n" HIR "双掌幻出漫天掌影，铺天盖"
                       "地向四面八方\n云涌而出，当真气势磅"
                       "礴，无与伦比！\n" NOR,
                       me, this_object());
        command("nod");
        command("say 这招「九穹绝刹掌」是我铁掌帮最为精深的招式，你明白了多少？");
        command("say 这其中的奥妙还需要你自己下来勤加练习方能吸收，自己下去多多练习吧。");
        tell_object(me, HIC "你学会了「九穹绝刹掌」这一招。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 960000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 960000);
        if (me->can_improve_skill("tie-zhang"))
                me->improve_skill("tie-zhang", 960000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 960000);
        if (me->can_improve_skill("tianlei-shengong"))
                me->improve_skill("tianlei-shengong", 960000);
        set("can_perform/tie-zhang/juesha", 1, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/feilong-zhangfa/fei", me) )
                return "这招我已经教过你了，还是自己下去多多练习吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本帮素无瓜葛，何出此言？";

        if (me->query_skill("feilong-zhangfa", 1) < 1)
                return "你连飞龙杖法都没学，何谈此言？";

        if( query("shen", me)>-10000 )
                return "嘿嘿嘿，你这样心慈手软能干成什么事？这招你不学也罢！";

        if (me->query_skill("feilong-zhangfa", 1) < 150)
                return "你的飞龙杖法还练得不到家，自己下去练练再来吧！";

        if( query("family/gongji", me)<160 )
                return "你的门派贡献不够，这招我不能传你！";

        message_vision(HIY "$n" HIY "微微点了点头，对$N" HIY
                       "说道：“看好了！”随即顺手抄起一根钢"
                       "杖，注力入腕，「飕」的\n一声掷出，刹"
                       "那只见一道银光飞逝而过，同时只听「扑"
                       "哧」一声碎响，钢杖已没入$N" HIY "身"
                       "后的柱\n子数尺之深。\n" NOR, me, this_object());
        command("nod");
        command("say 这招「龙飞势」并不复杂，下来后自己多加练习就行了！");
        tell_object(me, HIC "你学会了「龙飞势」这一招。\n" NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 960000);
        if (me->can_improve_skill("feilong-zhangfa"))
                me->improve_skill("feilong-zhangfa", 960000);
        set("can_perform/feilong-zhangfa/fei", 1, me);
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

        case "掌心雷" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/lei",
                           "name"    : "掌心雷",
                           "msg1"    : HIY "$N" HIY "投以赞许的"
                                       "一笑，说道：“看好了！”"
                                       "随即只见$N" HIY "猛催内"
                                       "力，双掌登时变得火红，你"
                                       "正惊诧之际$N" HIY "双掌幻"
                                       "为一对掌刀凌空劈\n斩而出"
                                       "，只听「喀嚓」一声，大厅"
                                       "内一张青石桌应声而碎！",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 160,
                           "force"   : 240,
                           "neili"   : 2200,
                           "free"    : 1,
                           "shen"    : -65000, ]));
                break;

        case "九穹绝刹掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/juesha",
                           "name"    : "九穹绝刹掌",
                           "msg1"    : HIY "$N" HIY "默默注视了你"
                                       "良久，说道：“既然如此，今"
                                       "日我便传你这招！我只演示一"
                                       "遍，你可要看仔细了！”说完"
                                       "一声怒喝，体内所积存数十载"
                                       "的天雷真气澎湃而发，衣衫鼓"
                                       "动，双臂陡然暴长数尺。只听"
                                       "四周破空之声骤然响之，$N" HIY
                                       "双掌幻出漫天掌影，铺天盖地向"
                                       "四面八方云涌而出，当真气势磅"
                                       "礴，无与伦比！",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 200,
                           "force"   : 300,
                           "neili"   : 2200,
                           "free"    : 1,
                           "shen"    : -85000, ]));
                break;

        case "无影掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/ying",
                           "name"    : "无影掌",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 100,
                           "force"   : 80,
                           "neili"   : 1300,
                           "free"    : 1,
                           "shen"    : -60000, ]));
                break;

        case "龙影掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/long",
                           "name"    : "龙影掌",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 100,
                           "force"   : 80,
                           "neili"   : 1300,
                           "free"    : 1,
                           "shen"    : -60000, ]));
                break;


        case "五指刀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/dao",
                           "name"    : "五指刀",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 180,
                           "force"   : 280,
                           "neili"   : 2500,
                           "free"    : 1,
                           "shen"    : -90000, ]));
                break;

        case "阴阳磨" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tie-zhang/yin",
                           "name"    : "阴阳磨",
                           "sk1"     : "tie-zhang",
                           "lv1"     : 220,
                           "force"   : 300,
                           "neili"   : 3500,
                           "free"    : 1,
                           "shen"    : -95000, ]));
                break;

        case "春雷炸空" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianlei-dao/zha",
                           "name"    : "春雷炸空",
                           "sk1"     : "tianlei-dao",
                           "lv1"     : 150,
                           "force"   : 140,
                           "neili"   : 1500,
                           "gongxian": 600,
                           "shen"    : -75000, ]));
                break;

        case "五雷连闪" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianlei-dao/shan",
                           "name"    : "五雷连闪",
                           "sk1"     : "tianlei-dao",
                           "lv1"     : 150,
                           "force"   : 150,
                           "neili"   : 1500,
                           "gongxian": 600,
                           "shen"    : -75000, ]));
                break;
/*
        case "镇岳尚方" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : ZHENYUE,
                           "master"  : 1,
                           "sk1"     : "henshan-jian",
                           "lv1"     : 120,
                           "shen"    : 50000, ]));
                break;
*/
        default:
                return 0;
        }
}

void unconcious()
{
        die();
}

int recognize_apprentice(object ob, string skill)
{
        if (ob->query_skill(skill, 1) >= 400)
        {
                command("say 够了！我就教你到这里吧，武功还是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if( query("character", ob) != "阴险奸诈" && 
            query("character", ob) != "心狠手辣" && 
            query("character", ob) != "国士无双" )
        {
                command("say 你是什么人，也想老夫传授你武功？！");
                return -1;
        }

        if( query_temp("can_learn/qiu/tie-zhang", ob) && 
            skill == "tie-zhang")
                return 1;

        if( query_temp("can_learn/qiu/tie-zhang", ob) && 
            skill == "strike")
                return 1;

        if (skill == "tie-zhang")
        {
                message_vision("$N看了看$n，嘿嘿地笑道：铁掌掌法也没有什么难学的。\n",
                               this_object(), ob);
                set_temp("can_learn/qiu/tie-zhang", 1, ob);
                return 1;
        }

        command("say 我只懂得一点铁掌掌法，你可不要烦我。");
        return -1;
}
