// This program is a part of NT MudLIB

#include <ansi.h>
#include "shenlong.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_fei();
mixed ask_xian();
mixed ask_cui();
string ask_tool();

void create()
{
        set_name("洪安通", ({ "hong antong", "hong" }));
        set("title",  HIY "神龙教" NOR "教主" );
        set("nickname", HIR "永享仙福" NOR);
        set("long", "他就是武功盖世、令江湖人等谈之色变的神龙教教主洪安通。\n");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "friendly");

        set("str", 32);
        set("int", 35);
        set("con", 31);
        set("dex", 32);

        set("max_qi", 6000);
        set("max_jing", 3000);
        set("neili", 6800);
        set("max_neili", 6800);
        set("jiali", 100);
        set("level", 40);
        set("combat_exp", 2200000);
        set("shen_type", -1);

        set_skill("force", 600);
        set_skill("shenlong-xinfa", 600);
        set_skill("dodge", 600);
        set_skill("yixing-bufa", 600);
        set_skill("hand", 600);
        set_skill("shenlong-bashi", 600);
        set_skill("strike", 600);
        set_skill("huagu-mianzhang", 600);
        set_skill("finger", 620);
        set_skill("yingxiong-sanzhao", 600);
        set_skill("parry", 600);
        set_skill("staff", 600);
        set_skill("sword", 600);
        set_skill("shedao-qigong", 600);
        set_skill("unarmed", 600);
        set_skill("literate", 600);
        set_skill("medical", 600);
        set_skill("shenlong-jian", 600);
        set_skill("busi-shenlong", 600);
        set_skill("shenlong-mixin", 600);
        set_skill("shenlong-dafa", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixing-bufa");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        map_skill("unarmed", "shedao-qigong");
        map_skill("sword", "shenlong-jian");
//        map_skill("finger", "yingxiong-sanzhao");

        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");

        create_family("神龙教", 1, "教主");

        set("inquiry", ([
                "神龙教" : "一般人是入不了我神龙教的(join shenlongjiao)。",
                "入教"   : "一般人是入不了我神龙教的(join shenlongjiao)。",
                "洪安通" : "你不想活了是不是？",
                "教主"   : "我就是神龙教教主。",
                "绝招"   : "你想学什么绝技啊？",
                "绝技"   : "你想学什么绝技啊？",
                "飞仙法" : (: ask_fei :),
                "神龙再现" : (: ask_xian :),
                "摧心断肠" : (: ask_cui :),
                "工具"   : (: ask_tool :),
                "tool"   : (: ask_tool :),
                "铁锹"   : (: ask_tool :),
                "神龙锹" : (: ask_tool :),
                "qiao"   : (: ask_tool :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "fei" :),
                (: perform_action, "xian" :),
                (: perform_action, "cui" :),
                (: perform_action, "strike.hua" :),
                (: perform_action, "hand.xian" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 35);
}

int do_flatter(string arg)
{
        if( !query_temp("pending/flatter", this_player()) )
        {
                command("say 你想嚷嚷什么，吵得我心烦意乱的。");
                return 0;
        }

        if (! arg ) return notify_fail("你说我什么？\n");

        set_temp("pending/flatter", 0, this_player());
        message_vision(CYN "$N大声说道：" + arg + "\n" NOR,
                       this_player());

        if (strsrch(arg, "万年不老") >=0 && (strsrch(arg, "永享仙福") >=0 &&
            strsrch(arg, "寿与天齐") >=0 && strsrch(arg, "文武仁圣") >=0))
        {
                command("smile");
                command("say 这还差不多。\n");
                command("recruit "+query("id", this_player()));
        } else
        {
                command("say 你如此不把我放在眼里，我又怎能容你？!");
                kill_ob(this_player());
        }
        return 1;
}

// 万年不老,永享仙福,寿与天齐,文武仁圣

void die()
{
        message_vision("\n$N奇道：“咦,居然有人能杀了我,....”"
                       "说完睁着两眼倒地死了。\n", this_object());
        ::die();
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 4, ob);
        }
        add_action("do_flatter", "flatter");
        add_action("do_join", "join");
}

void greeting(object ob)
{
        object obj;
        if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                set("combat_exp", 1000000);
                set("qi", 500);
                set("jing", 500);
        }
}

mixed ask_fei()
{
        object me;

        me = this_player();
        if( query("can_perform/shedao-qigong/fei", me) )
                return "自己多练练，少在我面前罗嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪儿来的？找死啊？";

        if( query("shen", me)>-40000 )
                return "你的手段还不够毒，我可不能传给你绝招！";

        if( query("family/gongji", me)<800 )
                return "你为我神龙教效力还不够，这招我先不忙传你。";

        if (me->query_skill("shedao-qigong", 1) < 100)
                return "你的蛇岛奇功学好了么？还好意思来问我？";

        message_vision(HIM "$n" HIM "点头道：“看清楚了！”说罢以"
                       "掌为剑“唰唰唰”接连劈出数剑，宛若数把剑在"
                       "手，真是神乎其神！\n" NOR,
                       me, this_object());
        command("say 运用很简单，不过你懂了没有？");
        tell_object(me, HIG "你学会了飞仙术。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shedao-qigong/fei", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

mixed ask_xian()
{
        object me;

        me = this_player();
        if( query("can_perform/shedao-qigong/xian", me) )
                return "自己多练练，少在我面前罗嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪儿来的？找死啊？";

        if( query("shen", me)>-50000 )
                return "你要好好为我神教效力，手段要更狠更毒。我才能传你这门绝招！";

        if( query("family/gongji", me)<800 )
                return "你为我神龙教效力还不够，这招我先不忙传你。";

        if (me->query_skill("shedao-qigong", 1) < 120)
                return "你的蛇岛奇功根基不够，岂能就窥测其中奥妙？";

        message_vision(HIM "$n" HIM "点头道：“你且看着，说罢双掌"
                       "齐推，眼见招式已老，忽然间去势一变，宛若"
                       "龙行天际，曲折婉转不留半点痕迹。\n" NOR,
                       me, this_object());
        command("say 你可懂了其中奥妙？");
        tell_object(me, HIG "你学会了神龙再现。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 90000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 90000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shedao-qigong/xian", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

mixed ask_cui()
{
        object me;

        me = this_player();
        if( query("can_perform/shedao-qigong/cui", me) )
                return "自己多练练，少在我面前罗嗦！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪儿来的？找死啊？";

        if( query("shen", me)>-50000 )
                return "你要好好为我神教效力，手段要更狠更毒。我才能传你这门绝招！";

        if( query("family/gongji", me)<800 )
                return "你为我神龙教效力还不够，这招我先不忙传你。";

        if (me->query_skill("shedao-qigong", 1) < 120)
                return "你的蛇岛奇功根基不够，岂能就窥测其中奥妙？";

        message_vision(HIM "$n" HIM "点头道：“你且看着，只听$n"
                       HIM "大喝一声，一掌击出，隐隐然有风雷之声。\n"
                       "一时间$N" HIM "只觉得呼吸困难，$p" HIM "掌力"
                       "犹如排山倒海一般，撼天动地。\n" NOR,
                       me, this_object());
        command("say 这招不求花巧变化，乃是以力取胜，你可明白？");
        tell_object(me, HIG "你学会了摧心断肠。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 90000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 90000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shedao-qigong/cui", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

void attempt_apprentice(object ob)
{
        if( query("party/party_name", ob) != "神龙教" )
        {
                command("say 你不是本教教众, 想来找死啊!");
                return;
        }

        if( query("shen", ob)>-1000 )
        {
                command("say 林冲拜梁山还要投名状，你不杀两"
                        "个白道人物怎么表示真心？！");
                return;
        }

        if( query_temp("pending/flatter", ob) )
        {
                command("say 你如此不把我放在眼里，我又怎能容你？");
                kill_ob(ob);
                return 0;
        } else
        {
                command("say 我洪安通比起古往今来的圣人怎么样啊？");
                message_vision("洪安通微闭双眼，手捻长须，一副"
                               "等人拍马(flatter)的样子。\n",
                               this_player());
                set_temp("pending/flatter", 1, ob);
                return 0;
        }
}

/*
void unconcious()
{
        die();
}
*/

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "辣手化骨" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huagu-mianzhang/hua",
                           "name"    : "辣手化骨",
                           "sk1"     : "huagu-mianzhang",
                           "lv1"     : 100,
                           "sk2"     : "strike",
                           "lv2"     : 100,
                           "sk3"     : "force",
                           "lv3"     : 100,
                           "gongxian": 1000,
                           "shen"    : -20000, ]));
                break;

        case "英雄三招" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yingxiong-sanzhao/sanzhao",
                           "name"    : "英雄三招",
                           "sk1"     : "yingxiong-sanzhao",
                           "lv1"     : 200,
                           "sk2"     : "strike",
                           "lv2"     : 200,
                           "sk3"     : "force",
                           "lv3"     : 200,
                           "shen"    : -50000, ]));
                break;

        case "盖世英雄" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yingxiong-sanzhao/yingxiong",
                           "name"    : "盖世英雄",
                           "sk1"     : "yingxiong-sanzhao",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 160,
                           "gongxian": 600, 
                           "shen"    : -50000, ]));
                break;

        case "舍身" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yingxiong-sanzhao/sheshen",
                           "name"    : "舍身",
                           "sk1"     : "yingxiong-sanzhao",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 160,
                           "gongxian": 1000, 
                           "shen"    : -50000, ]));
                break;

        case "神龙初现" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenlong-bashi/xian",
                           "name"    : "神龙初现",
                           "sk1"     : "shenlong-bashi",
                           "lv1"     : 100,
                           "sk2"     : "hand",
                           "lv2"     : 100,
                           "sk3"     : "force",
                           "lv3"     : 100,
                           "gongxian": 600,
                           "shen"    : -10000, ]));
                break;
        case "唱仙法" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shedao-qigong/chang",
                           "name"    : "唱仙法",
                           "sk1"     : "shedao-qigong",
                           "lv1"     : 200,
                           "sk2"     : "sword",
                           "lv2"     : 200,
                           "sk3"     : "force",
                           "lv3"     : 200,
                           "shen"    : -50000, ]));
                break;

        case "哼字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shedao-qigong/heng",
                           "name"    : "哼字诀",
                           "sk1"     : "shedao-qigong",
                           "lv1"     : 200,
                           "sk2"     : "sword",
                           "lv2"     : 200,
                           "sk3"     : "force",
                           "lv3"     : 200,
                           "shen"    : -50000, ]));
                break;

        case "吼字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shedao-qigong/hou",
                           "name"    : "吼字诀",
                           "sk1"     : "shedao-qigong",
                           "lv1"     : 200,
                           "sk2"     : "sword",
                           "lv2"     : 200,
                           "sk3"     : "force",
                           "lv3"     : 200,
                           "shen"    : -50000, ]));
                break;

        default:
                return 0;
        }
}
string ask_tool()
{
        mapping fam;
        object ob, me = this_player();

        if( !(fam=query("family", me)) || 
                fam["family_name"] != "神龙教")
                return "这位"+RANK_D->query_respect(me)+ "与本教素无来往，不知此话从何谈起？";
        if( present("shenlong qiao", me) )
                return "你现在身上不是有锹了嘛，怎么又来要了？真是贪得无餍！";
        if( me->query_skill("digging", 1) <= 30)
                return "你拿着东西也没什么用，还是留给别人吧！";
        if( query("count") < 1)
                return "来晚啦，你要的东西给别人先拿走了！";
        ob = new(__DIR__"obj/shenlongqiao");
        ob->move(me);
        addn("count", -1);
        return "好吧，这有一把神龙锹，你就拿去吧。";
}
