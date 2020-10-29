// This program is a part of NT MudLIB
// murongbo.c 慕容博

#include <ansi.h>
#include "murong.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_me();
mixed try_learn_sk();
int try_learn_chz();
string ask_book1();
string ask_book2();
mixed ask_wuxue();

#define HUPO "/clone/unique/hupohuan"

void create()
{
        set_name("慕容博", ({ "murong bo", "murong", "bo" }));
        set("long", @LONG
他是姑苏慕容的传人，可以说是自慕容龙城以下武功最为杰出
之人。不仅能贯通天下百家之长，更是深为精通慕容家绝技。
LONG );
        set("nickname", HIM "以彼之道 还施彼身" NOR);
        set("gender", "男性");
        set("age", 54);
        set("shen_type",-1);
        set("attitude", "peaceful");

        set("str", 31);
        set("int", 37);
        set("con", 34);
        set("dex", 33);

        set("qi", 5700);
        set("max_qi", 5700);
        set("jing", 2800);
        set("max_jing", 2800);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 145);
        set("level", 40);
        set("combat_exp", 2650000);

        // base skill
        set_skill("force", 650);
        set_skill("jingluo-xue", 650);
        set_skill("literate", 650);
        set_skill("unarmed", 650);
        set_skill("cuff", 650);
        set_skill("finger", 650);
        set_skill("strike", 650);
        set_skill("hand", 650);
        set_skill("claw", 650);
        set_skill("club", 650);
        set_skill("sword", 650);
        set_skill("blade", 650);
        set_skill("staff", 650);
        set_skill("dodge", 650);
        set_skill("parry", 650);

        // shaolin skill. No teach
        set_skill("banruo-zhang", 600);
        set_skill("cibei-dao", 600);
        set_skill("damo-jian", 600);
        set_skill("fengyun-shou", 600);
        set_skill("fumo-jian", 600);
        set_skill("hunyuan-yiqi", 600);
        set_skill("shaolin-xinfa", 600);
        set_skill("jingang-quan", 600);
        set_skill("longzhua-gong", 600);
        set_skill("luohan-quan", 600);
        set_skill("nianhua-zhi", 600);
        set_skill("pudu-zhang", 600);
        set_skill("qianye-shou", 600);
        set_skill("sanhua-zhang", 600);
        set_skill("riyue-bian", 600);
        set_skill("shaolin-shenfa", 600);
        set_skill("weituo-gun", 600);
        set_skill("wuchang-zhang", 600);
        set_skill("xiuluo-dao", 600);
        set_skill("yingzhua-gong", 600);
        set_skill("yizhi-chan", 600);
        set_skill("zui-gun", 600);

        // murong skill
        set_skill("zihui-xinfa", 650);
        set_skill("shenyuan-gong", 650);
        set_skill("douzhuan-xingyi", 650);
        set_skill("beidou-xianzong", 650);
        set_skill("canhe-zhi", 650);
        set_skill("xingyi-zhang", 650);
        set_skill("qixing-quan", 650);
        set_skill("murong-daofa", 650);
        set_skill("murong-jianfa",650);
        set_skill("huitong-tianxia", 600); 
        set_skill("martial-cognize", 600);

        map_skill("force", "zihui-xinfa");
        map_skill("dodge", "beidou-xianzong");
        map_skill("cuff",  "qixing-quan");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("finger", "canhe-zhi");
        map_skill("strike", "xingyi-zhang");
        map_skill("blade", "murong-daofa");
        map_skill("sword", "murong-jianfa");

        prepare_skill("finger", "canhe-zhi");
        prepare_skill("cuff", "qixing-quan");

        set("no_teach", ([
                "banruo-zhang"  : (: try_learn_sk :),
                "cibei-dao"     : (: try_learn_sk :),
                "damo-jian"     : (: try_learn_sk :),
                "fengyun-shou"  : (: try_learn_sk :),
                "fumo-jian"     : (: try_learn_sk :),
                "hunyuan-yiqi"  : (: try_learn_sk :),
                "shaolin-xinfa" : (: try_learn_sk :),
                "jingang-quan"  : (: try_learn_sk :),
                "longzhua-gong" : (: try_learn_sk :),
                "luohan-quan"   : (: try_learn_sk :),
                "nianhua-zhi"   : (: try_learn_sk :),
                "pudu-zhang"    : (: try_learn_sk :),
                "qianye-shou"   : (: try_learn_sk :),
                "sanhua-zhang"  : (: try_learn_sk :),
                "riyue-bian"    : (: try_learn_sk :),
                "shaolin-shenfa": (: try_learn_sk :),
                "weituo-gun"    : (: try_learn_sk :),
                "wuchang-zhang" : (: try_learn_sk :),
                "xiuluo-dao"    : (: try_learn_sk :),
                "yingzhua-gong" : (: try_learn_sk :),
                "yizhi-chan"    : (: try_learn_sk :),
                "zui-gun"       : (: try_learn_sk :),
                "canhe-zhi"     : (: try_learn_chz :),
        ]));

        create_family("慕容世家", 15, "庄主");
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "finger.canhe" :),
                (: perform_action, "parry.yi" :),
                (: perform_action, "finger.lian" :),
                (: perform_action, "finger.zhi" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 200);

        set("inquiry", ([
                "绝招"   : (: ask_me :),
                "绝技"   : (: ask_me :),
                "斗转星移": (: ask_me :),
                "紫徽心法": (: ask_book1 :),
        "斗转星移书": (: ask_book2 :),
                "武学修养": (: ask_wuxue :),
        ]));

        set("zihui_count", 1);
        set("douzhuan_count", 1);

        set("master_ob",5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 100);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-36000 )
        {
                command("say 我慕容博向来不与你们这些所谓正道人士交往。");
                command("say 你还是请回吧！");
                return;
        }
        if( query("combat_exp", ob)<500000 )
        {
                command("say 你现在经验尚浅，还是多在江湖上走走吧。");
                return;
        }
        if ((int)ob->query_skill("douzhuan-xingyi", 1) < 130)
        {
                command("say 斗转星移乃我慕容世家绝技，你不好好练习到我这来做甚？。");
                return;
        }
        if ((int)ob->query_skill("shenyuan-gong", 1) < 120)
        {
                command("say 我慕容世家武功讲究心神合一，最重视基本心法。");
                command("say 你的神元功还不够熟练，下去练练再来吧。");
                return;
        }
        if ((int)ob->query_skill("dodge") < 200)
        {
                command("say 我慕容世家武功需配合灵巧的身法。");
                command("say 你是否还应该在轻功修为上多下点功夫？");
                return;
        }

        command("haha");
        command("pat"+query("id", ob));
        command("recruit "+query("id", ob));
        message_vision("慕容博大喜：我们慕容家真是英才迭出，复国有望啊！\n",
                       this_object());
}

mixed try_learn_sk()
{
        object me;

        me = this_player();
        if( query_temp("has_asked/murongbo", me) )
                return "你还是安心学本门功夫吧。";

        command("shake");
        command("say 据说少林的武功学了对身体有害，你就不要学了。");
        set_temp("has_asked/murongbo", 1, me);
        return -1;
}
// 演练后到120级，自修20级后方可学习。
int try_learn_chz()
{
       object me = this_player();

       if( query("shen", me)>0 )
       {
                command("heng");
                command("我最讨厌你们这些所谓正派人士，你还是请回吧！");
                return -1;
       }
/*
       if( query("born_family", me) != "慕容世家" && !query("reborn/times", me) ) 
       {
                command("sneer");
                command("say 你不是我们慕容家的人，我怎敢妄加指点。");
                command("say 阁下还是请回吧！");
                return -1;
       }
*/
       if( query("family/master_id", me) != query("id", this_object()) )
       {
            command("shake");
                command("say 阁下与我毫无瓜葛，我怎敢妄加指点？");
                return -1;
       }
       /*
       if (me->query_skill("canhe-zhi", 1) < 150)
       {
                command("shake");
                command("say 你参合指火候还不够，还得下去多多练习。");
                return -1;
       }
       */

       return 0;
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

        case "莲花指" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/lian",
                           "name"    : "莲花指",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 160,
                           "sk2"     : "shenyuan-gong",
                           "lv2"     : 180,
                           "force"   : 160,
                           "gongxian": 900,
                           "shen"    : -60000, ]));
                break;

        case "七星指穴" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/zhi",
                           "name"    : "七星指穴",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 140,
                           "dodge"   : 140,
                           "force"   : 140,
                           "gongxian": 600,
                           "shen"    : -75000, ]));
                break;

        case "幽冥剑气" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/you",
                           "name"    : "幽冥剑气",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 140,
                           "force"   : 150,
                           "gongxian": 800,
                           "shen"    : -80000, ]));
                break;

        case "金刚剑气" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/jin",
                           "name"    : "金刚剑气",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 160,
                           "force"   : 160,
                           "gongxian": 1000,
                           "shen"    : -95000, ]));
                break;

        case "参合剑气" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/canhe",
                           "name"    : "参合剑气",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 160,
                           "force"   : 180,
                           "gongxian": 1200,
                           "shen"    : -160000, ]));
                break;

        case "参合一指" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/ci",
                           "name"    : "参合一指",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 160,
                           "force"   : 180,
                           "gongxian": 1200,
                           "shen"    : -160000, ]));
                break;
        case "参商剑气" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/canhe-zhi/canshang",
                           "name"    : "参商剑气",
                           "sk1"     : "canhe-zhi",
                           "lv1"     : 120,
                           "force"   : 120,
                           "gongxian": 300,
                           "shen"    : -16000, ]));
                break;
        case "移星换月" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/douzhuan-xingyi/huan",
                           "name"    : "移星换月",
                           "sk1"     : "douzhuan-xingyi",
                           "lv1"     : 1000,
                           "force"   : 1200,
                           "gongxian": 10000,
                           "reborn"  : 1,
                           "shen"    : -16000, ]));
                break;
        /*
        case "琥珀神环" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : HUPO,
                           "master"  : 1,
                           "sk1"     : "zihui-xinfa",
                           "lv1"     : 180,
                           "shen"    : -50000, ]));
                break;
        */

        default:
                return 0;
        }
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/douzhuan-xingyi/yi", me) )
                return "你还不快去练功去？光复大燕不是靠嘴上说的！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是什么人？有何居心？";

        if (me->query_skill("douzhuan-xingyi", 1) < 100)
                return "斗转星移是我们慕容家的绝学，你练好没有？";

        message_vision(HIY "$n" HIY "看看$N" HIY "，示意$N"
                       HIY "攻自己一招，$N" HIY "疑疑惑惑的"
                       "拍出一掌，只见$n" HIY "伸手轻轻一擦，"
                       HIY "$N的招式方向\n忽然大变，反而攻向自"
                       "己！蓬的一声这一掌结结实实的打在了$P"
                       HIY "自己的肩头！\n" NOR,
                       me, this_object());
        command("nod");
        command("say 这其中的奥妙乃是用巧妙的招式配合我"
                "慕容家的紫徽心法，你要好好体会，去吧！");
        tell_object(me, HIG "你学会了斗转星移。\n" NOR);
        if (me->can_improve_skill("douzhuan-xingyi"))
                me->improve_skill("douzhuan-xingyi", 90000);
        if (me->can_improve_skill("zihui-xinfa"))
                me->improve_skill("zihui-xinfa", 90000);
        set("can_perform/douzhuan-xingyi/yi", 1, me);
        return 1;
}

string ask_book1()
{
        mapping fam;
        object ob;
        object me;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(this_player()) +
                       "与我慕容家素无来往，不知此话从何谈起？";

        if (me->query_skill("zihui-xinfa", 1) < 100)
                return "你的紫徽心法水平还不够，还用不着这本秘籍。";

        if (query("zihui_count") < 1)
                return "你来晚了，紫徽秘籍我已经借出去了。";

        addn("zihui_count", -1);
        ob = new("/clone/book/zihui-book");
        ob->move(this_player());
        return "好吧，这本紫徽心法你拿去好好研读！";
}

string ask_book2()
{
        mapping fam;
        object ob;
        object me;

        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(this_player()) +
                       "与我慕容家素无来往，不知此话从何谈起？";

        if (me->query_skill("douzhuan-xingyi", 1) < 100)
                return "你的斗转星移连的还不到家，我还不能给你这本秘籍。";

        if (query("douzhuan_count") < 1)
                return "你来晚了，秘籍我已经借出去了。";

        addn("douzhuan_count", -1);
        ob = new("/clone/book/douzhuan-book");
        ob->move(this_player());
        return "这本斗转星移你可以收好了。";
}

mixed ask_wuxue()
{
        object me = this_player(), ob = this_object();

        if( query("family/family_name", me) != "慕容世家" )
        {
                write(ob->name() + "说道：你不是我慕容世家的人，给我滚一边去！\n");
                return 1;
        }

        if (me->is_busy() || me->is_fighting())
        {
                write(ob->name() + "说道：你正忙着呢。\n");
                return 1;
        }

        // write("你向" + ob->name() + "请教关于「武学修养」的疑问。\n");

        if( query("potential", me)-query("learned_points", me)<20 )
        {
                write(ob->name()+"说道：你的潜能不足以领悟「武学修养」的精妙所在。\n");
                return 1;
        }

        if( query("jing", me)<50 )
        {
                write(ob->name()+"说道：" + RANK_D->query_respect(me) + "先休息一下吧。\n");
                return 1;
        }

        if (me->query_skill("martial-cognize") > 800)
        {
                write(ob->name()+"说道：" + RANK_D->query_respect(me) +
                        "的「武学修养」造诣已经很高了，我已不能指点你更深一层。\n");
                return 1;
        }
        write("你听了" + ob->name() + "的指点，对「武学修养」的体会又深了一层。\n");

        me->receive_damage("jing", 50);
        addn("learned_points", random(20), me);
        me->improve_skill("martial-cognize", me->query_int() * 10);
        me->start_busy(1 + random(2));
        return 1;
}

void reset()
{
        set("zihui_count", 1);
        set("douzhuan_count", 1);
}

/*
void unconcious()
{
        die();
}

*/
