inherit NPC;
inherit F_MASTER;

#include <command.h>
#include <ansi.h>
#include "emei.h"
mixed ask_skill1();
mixed ask_skill2();
       mixed ask_skill3(); 

void create()
{
        set_name("周芷若", ({ "zhou zhiruo","zhiruo","zhou"}));
        set("long", "她是峨嵋派的第四代掌门弟子。只见她一张\n"
                    "脸秀丽绝俗。身着一身淡黄衣裳。略显清减\n"
                    "的巧笑中带了些许无奈。\n");
        set("gender", "女性");
        set("age", 20);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("inquiry",([
                "剃度"     : "找我剃度？不对吧。",
                "出家"     : "要出家找我的师姐们去。",
                "还俗"     : "无聊。还俗也找我！",
                "张无忌"   : "这个狠心短命的家伙，我再也不要见他！",
                "赵敏"     : "谁能帮我杀这个贱婢子十次八次泄恨？",
                "倚天剑"   : "倚天不出，谁与争锋？唉！",
                "屠龙刀"   : "你想武林称雄？别做梦了。",
                "灭绝师太" : "师父待我恩重如山，我今生难以回报。",
                "九阴真经" : "那是什么东西？我这可是第一次听说。",
                "天诛龙蛟诀" : (: ask_skill1 :),
                "夺命连环爪" : (: ask_skill2 :),
                "峨眉九阳功" : (: ask_skill3 :), 
        ]));

        set("str", 22);
        set("int", 32);
        set("con", 26);
        set("dex", 24);

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jingli", 2000);
        set("max_jingli", 2000);
        set("jiali", 200);
        set("combat_exp", 2500000);

        set_skill("force", 260);
        set_skill("emei-xinfa", 260);
        set_skill("yijin-duangu", 260);      // 易筋锻骨
        set_skill("linji-zhuang", 200);
        set_skill("dodge", 260);
        set_skill("shexing-lifan", 260);     // 蛇行狸翻
        set_skill("zhutian-bu", 180);
        set_skill("finger", 180);
        set_skill("tiangang-zhi", 180);
        set_skill("hand", 180);
        set_skill("jieshou-jiushi", 180);
        set_skill("strike", 260);
        set_skill("jinding-zhang", 180);
        // set_skill("sixiang-zhang", 180);
        set_skill("cuixin-zhang", 260);      // 催心掌
        set_skill("claw", 260);
        set_skill("jiuyin-baiguzhao", 260);  // 九阴白骨爪
        set_skill("whip", 260);
        set_skill("yinlong-bian", 260);      // 银龙鞭法
        set_skill("sword", 180);
        set_skill("emei-jian", 180);
        set_skill("yitian-jian", 180);
        set_skill("blade", 180);
        set_skill("yanxing-dao", 180);
        set_skill("parry", 260);
        set_skill("martial-cognize", 200);
        set_skill("literate", 200);
        set_skill("mahayana", 100);
        set_skill("buddhism", 100);

        map_skill("force", "yijin-duangu");
        map_skill("dodge", "shexing-lifan");
        map_skill("finger", "tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("strike", "cuixin-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("whip", "yinlong-bian");
        map_skill("sword", "yitian-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("parry", "yinlong-bian");

        prepare_skill("strike", "cuixin-zhang");
        prepare_skill("claw", "jiuyin-baiguzhao");

        create_family("峨嵋派", 4, "掌门弟子");

        set("no_teach", ([
                "linji-zhuang"     : "想学临济十二庄找我师父去。",
                "shexing-lifan"    : "蛇行狸翻？这也是种武功吗？听名字倒是蛮有意思的。",
                "yijin-duangu"     : "你说的那是什么啊？我这可是头一次听说。",
                "cuixin-zhang"     : "催心掌？听名字怪吓人的，这样的武功我可不会。",
                //"jiuyin-baiguzhao" : "九阴白骨爪？这是什么武功啊？光听名字我就毛骨悚然。",
                "yinlong-bian"     : "我只会剑法和刀法，鞭法师父从来没教过我。",
                "yitian-jian"      : "这门功夫是家师独门绝学需找她亲自传授。",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.duo" :),       // 夺命连环
                (: perform_action, "claw.jie" :),       // 九阴刹神抓
                (: perform_action, "strike.cuixin" :),  // 催心破元诀
                (: perform_action, "whip.jiao" :),      // 天诛龙蛟诀
                (: perform_action, "dodge.guiyuan" :),  // 九阴归元劲
                (: perform_action, "sword.yitian" :),
                (: perform_action, "sword.fumo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        set("master_ob", 4);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/emei/obj/ycloth.c")->wear();
}

mixed ask_skill1()
{
        object me = this_player();
        if( query("can_perform/yinlong-bian/zhu", me) )
               return "这招我不是已经教过你了吗？自己下去多练吧！";

        if( query("family/family_name", me) != query("family/family_name") )
               return "你是哪里来的？快给我滚开！";

        if (me->query_skill("yinlong-bian", 1) <130 )
               return "你的银龙鞭法练的还不够纯熟，无发领悟此精妙绝技！";

        if (me->query_skill("yinlong-bian", 1) < 1)
               return "你连银龙鞭法都没学，还谈什么绝招可言？";

        command("say 看好了，以后对那些妖人不要手软，一上来就用这招！");
        command("grin");
        message_vision(HIG "周芷若抽出鞭子，随意挥舞着，将银龙鞭法奥义展现无疑。\n不一会儿，周芷若已是大汗淋漓。\n" NOR,me);
        command("say 这就是银龙鞭法的「天诛龙蛟诀」了，你要认真领悟其奥妙。");
        command("hehe");
        tell_object(me, HIC "你学会了「天诛龙蛟诀」。\n" NOR);
        if (me->can_improve_skill("whip"))
               me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("yinlong-bian"))
               me->improve_skill("yinlong-bian", 1500000);
        set("can_perform/yinlong-bian/zhu", 1, me);
        return 1;
}

mixed ask_skill2()
{
        object me = this_player();
        if( query("can_perform/jiuyin-baiguzhao/duo", me) )
               return "这招我不是已经教过你了吗？自己下去多练吧！";

        //if (me->query("family/family_name") != query("family/family_name"))
               //return "你是哪里来的？快给我滚开！";

        if (me->query_skill("jiuyin-baiguzhao", 1) <120 )
               return "你的九阴白骨爪练的还不够纯熟，无发领悟此精妙绝技！";

         command("say 看好了，以后对那些妖人不要手软，一上来就用这招！");
         command("grin");
       tell_object(me, HIC "你学会了「夺命连环爪」。\n" NOR);
        if (me->can_improve_skill("jiuyin-baiguzhao"))
               me->improve_skill("jiuyin-baiguzhao", 1500000);
        set("can_perform/jiuyin-baiguzhao/duo", 1, me);
        return 1;
}


mixed ask_skill3()//by redl
{
        object me = this_player();
        if (query_temp("marks/kill_zhaomin", me) < 10)
               return "我凭什么要帮你呢？";
        if( query("family/family_name", me) != query("family/family_name") ) 
               return "你是哪里来的？快给我滚开！"; 

        delete_temp("marks/kill_zhaomin", me);
         command("nod");
        
        me->set_skill("emei-jiuyang", 30); 
        me->improve_skill("emei-jiuyang", 5000); 
              command("say 下去好好练习你的飘雪穿云掌和九阴白骨爪吧。"); 
              tell_object(me, NOR HIY "你领悟到周芷若传授的峨眉绝学相互之间的微妙了。\n" NOR); 
        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_int() < 45)
        {
                command("say 这位" + RANK_D->query_respect(ob) + "恐怕资质差了一点。");
                command("say 不过尚大有潜力，还是先回去磨练磨练。");
                return;
        }

        if( !query_temp("marks/宋夫人", ob) )
        {
                command("say "+query("name", this_player())+"你没事就可以走了。\n\n");
                return;
        }

        delete_temp("marks/宋夫人", ob);
        command("say "+query("name", ob)+"看你这么可怜，勉为其难收下你吧。\n");
        command("recruit "+query("id", ob));
}
