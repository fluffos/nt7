// This program is a part of NT MudLIB
// huang.c 黄药师

#include <ansi.h>
#include "taohua.h"

#define TAOHUA    "/clone/book/taohua"
#define XIAOPU    "/clone/book/xiaopu"
#define XUANFENG  "/clone/book/xuanfengtui"
//#define YUXIAO    "/clone/unique/yuxiao"
#define YUXIAO    "/clone/lonely/yuxiao"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_QUESTER;

void   consider();
int    ask_shagu();

mixed  ask_leave();
mixed  ask_book1();
mixed  ask_book2();
mixed  ask_book3();
mixed  ask_book4();
mixed  ask_yuxiao();

mixed  ask_skill1();
mixed  ask_skill2();
mixed  ask_skill3();
mixed  ask_skill4();
mixed  ask_skill5();
mixed  ask_skill6();
mixed  ask_skill7();
mixed  ask_skill8();
mixed  ask_skill9();
mixed  ask_skill10();
mixed  ask_skill11();

mixed  try_to_learn_bibai();
mixed  try_to_learn_count();

string* xuedao = ({
        "风池穴", "风府穴", "强间穴", "大椎穴", "至阳穴",
        "百会穴", "灵台穴", "太阳穴", "膻中穴", "命门穴",
});

void create()
{
        object ob;
        set_name("黄药师", ({"huang yaoshi", "huang", "yaoshi"}));
        set("title", "东海桃花岛岛主");
        set("nickname", HIC "东邪" NOR );
        set("gender", "男性");
        set("age", 42);
        set("long", "他就是桃花岛主。行事好恶全由己心，因此被\n"
                    "人称作「东邪」。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("qi", 7000);
        set("max_qi", 7000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 200);
        set("level", 60);
        set("combat_exp", 4000000);

        set_skill("force", 600);
        set_skill("bibo-shengong", 600);
        set_skill("hand", 620);
        set_skill("finger", 600);
        set_skill("tanzhi-shentong", 600);
        set_skill("unarmed", 600);
        set_skill("strike", 600);
        set_skill("luoying-shenzhang", 600);
        set_skill("xuanfeng-tui", 600);
        set_skill("dodge", 600);
        set_skill("luoying-shenfa", 620);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("throwing", 600);
        set_skill("luoying-shenjian", 600);
        set_skill("yuxiao-jianfa", 600);
        set_skill("lanhua-shou", 600);
        set_skill("whip", 600);
        set_skill("canglang-bian", 600);
        set_skill("qimen-wuxing", 10000);
        set_skill("jingluo-xue", 10000);
        set_skill("count", 10000);
        set_skill("mathematics", 10000);
        set_skill("literate", 10000);
        set_skill("chuixiao-jifa", 600);
        set_skill("bihai-chaosheng", 600);
        set_skill("taohua-yuan", 600);
        set_skill("calligraphy", 600);
        set_skill("medical", 600);
        set_skill("taoism", 400);
        set_skill("taohua-yaoli", 600);
        set_skill("qimen-xuanshu", 600);
        set_skill("martial-cognize", 620);

        map_skill("force", "bibo-shengong");
        map_skill("finger", "tanzhi-shentong");
        map_skill("hand", "lanhua-shou");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("whip", "canglang-bian");
        map_skill("strike", "luoying-shenzhang");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "tanzhi-shentong");
        map_skill("sword", "yuxiao-jianfa");
        map_skill("chuixiao-jifa", "bihai-chaosheng");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("medical", "taohua-yaoli");

        prepare_skill("finger" , "tanzhi-shentong");

        set("no_teach", ([
                "count"           : (: try_to_learn_count :),
                "bihai-chaosheng" : (: try_to_learn_bibai :),
        ]));

        set("inquiry", ([
                "离岛"       : (: ask_leave :),
                "桃花药理"   : (: ask_book1 :),
                "箫谱"       : (: ask_book2 :),
                "旋风扫叶腿" : (: ask_book3 :),
                "河图"       : (: ask_book4 :),
                "洛书"       : (: ask_book4 :),
                "玉箫"       : (: ask_yuxiao :),
                "奇门五转"   : (: ask_skill1 :),
                "兰花拂穴"   : (: ask_skill2 :),
                "影落飞花"   : (: ask_skill3 :),
                "天外清音"   : (: ask_skill4 :),
                "天地情长"   : (: ask_skill5 :),
                "碧海潮生"   : (: ask_skill6 :),
                "定昆仑"     : (: ask_skill7 :),
                "啸沧海"     : (: ask_skill8 :),
                "破九域"     : (: ask_skill9 :),
                "转乾坤"     : (: ask_skill10 :),
                "漫天花雨"     : (: ask_skill11 :),
                "傻姑"       : (: ask_shagu :),
                "碧浪滔天"   : "这招你去让冯默风教你吧。",
                "披星戴月"   : "这招你去让陆乘风教你吧。",
                "狂风绝技"   : "这招你去让陆乘风教你吧。",
                "随波逐流"   : "这招你去让曲灵风教你吧。",
                "黄蓉"       : "你敢直称我女儿的闺名？",
                "九阴真经"   : "如果你能帮我取得真经，我一定重重谢你。",
                "九阴神功"   : "九阴神功恢弘正大，乃盖世奇功！",
                "兰花手"     : "兰花拂穴手…唉…可惜我几个弟子都算不得成才！",
                "弹指神通"   : "…唉…我一身绝艺竟然无人可以继承？",
                "玉萧剑法"   : "不是性情中人，如何能够领会这剑法？",
                "碧波神功"   : "…唉…我桃花岛的内功何等厉害，可惜…",
                "九花玉露丸" : "这个东西难制得紧，你好好学学桃花药理，以后自己制吧。",
                "无常丹"     : "…嗯…等你学通了桃花药理的奥妙，自己慢慢制吧。",
        ]));

        create_family("桃花岛", 1, "岛主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.bihai" :),
                (: perform_action, "sword.qing" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "finger.ding" :),
                (: perform_action, "finger.xiao" :),
                (: perform_action, "finger.po" :),
                (: perform_action, "finger.zhuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();

        if (clonep())
        {
                ob = find_object(YUXIAO);
                if (! ob) ob = load_object(YUXIAO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        set_temp("handing", ob);
                } else
                {
                        set_temp("handing", carry_object("/d/taohua/obj/huaban"));
                }
        }
        carry_object(__DIR__"obj/bupao")->wear();
        // carry_object("/clone/book/jiuyin2");
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()))
        {
                if( query_temp("th_tomb_thief", ob) )
                {
                        command("say " + RANK_D->query_rude(ob) + "，胆敢私闯我夫人墓室，纳命来！\n");
                        start_busy(1);
                        kill_ob(ob);
                }
                if( query("th_killer", ob) || query_temp("th_killer", ob) )
                {
                        command("sneer"+query("id", ob));
                        command("say 孽徒好大胆子，居然同门弟子手足相残！");
                        message_vision(HIR "黄药师说完一抬手，一指戳在$N的" +
                                       xuedao[random(sizeof(xuedao))] + "上。\n" NOR, ob);
                        call_out("move_it", 1, ob);
                }

                if( query("kill_th_traitor", ob )
                 && query("help_chengfeng", ob )
                 && query("help_lingfeng", ob )
                 && query("help_mofeng", ob) )
                {
                        set_temp("huang_recr", 1, ob);
                        command("smile "+query("id", ob));
                }
        }
}

void move_it(object ob)
{
        object *inv;
        int k;

        if (ob)
        {
                set("eff_qi", 10, ob);
                set("eff_jing", 10, ob);
                set("jing", 0, ob);
                delete("th_killer", ob);
                delete_temp("th_killer", ob);

                inv = all_inventory(ob);
                for (k = 0; k < sizeof(inv); k++)
                {
                        if( (query("armor_prop", inv[k]) && query("equipped", inv[k]) )
                         || query("no_get", inv[k]) )
                                continue;
                        destruct(inv[k]);
                }
                ob->unconcious();
                ob->move("/d/taohua/maze/maze"+(random(63)+1));
        }
}

void attempt_apprentice(object ob)
{
        string master;
        string *app = ({ "陆乘风", "曲灵风" });
        object obj;

        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 25)
        {
                command("say 我不收资质差的弟子，您请回吧！");
                return;
        }

        if( query("shen", ob)<-10000
         || query("shen", ob)>10000 )
        {
                command("say 我不与成名人物打交道，您请回吧！");
                return;
        }
        /*
        if( query("combat_exp", ob)<400000 )
        {
                if( stringp(master=query_temp("taohua/master", ob)) )
                {
                        command("say 不是让你和" + master + "学艺吗？你怎么回事？");
                        return;
                }

                if( query("family/family_name", ob) == "桃花岛" && 
                    query("family/master_name", ob) != "黄药师" )
                {
                        command("say你好好跟"+query("family/master_name", ob)+
                                "学艺，水平到了老夫自然会亲自点拨你。");
                        return;
                }

                master = app[random(sizeof(app))];

                command("say 嗯…念你长途跋涉赶来拜师，老夫就收你入桃花岛。");
                command("say 不过你武学方面成就有限，还是先跟我弟子" + master + "学习吧。");
                set_temp("taohua/master", master, ob);
                set("family/family_name", "桃花岛", ob);
                return;
        }
        */

        if( !query_temp("huang_recr", ob) && !query("reborn", ob) )
        {
                tell_object(ob, "黄药师对你睬也不睬。\n");
                return;
        }

        command("say 很好，很好。");
        command("recruit "+query("id", ob));

        obj = new("/d/taohua/obj/bagua");
        obj->move(this_object());

        command("give "+query("id", ob)+" bagua");

        if( query("short", environment(this_object())) != "黄药师居处" )
        {
                write("说完，黄药师飘然而去。\n");
                destruct(this_object());
        }
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/huang/count", me) )
        {
                command("say 你是谁？哪里来的？要干啥？");
                return -1;
        }

        if (skill != "count"
            && skill != "mathematics"
            && skill != "chuixiao-jifa")
        {
                command("say 老叫花教你什么就学什么，你不学就算了。");
                return -1;
        }

        if ((int)me->query_skill("count", 1) > 379)
        {
                command("say 到此为止，你的功力也不差了，剩下的自己去练。");
                return -1;
        }

        return 1;
}

mixed try_to_learn_count()
{
        object ob = this_player();

        if( query("can_learn/huang/count", ob) )
                return 0;

        if (ob->query_skill("mathematics", 1) >= 200)
        {
                command("nod2");
                command("say 看来你对算术也颇有见解，今日老夫就教"
                        "你些阴阳八卦的知识。");
                set("can_learn/huang/count", 1, ob);
                return 0;
        }
        return "阴阳八卦我不轻易传授。";
}

mixed try_to_learn_bibai()
{
        object ob = this_player();

        if( query("can_learn/huang/bihai-chaosheng", ob) )
                return 0;

        if (ob->query_skill("bibo-shengong", 1) >= 120
        &&  ob->query_skill("chuixiao-jifa", 1) >= 120)
        {
                command("sigh");
                command("say 想不到你萧技居然已达此境界，今日老夫"
                        "就传你碧海潮生曲吧。");
                set("can_learn/huang/bihai-chaosheng", 1, ob);
                return 0;
        }
        return "尔非性情中人，这碧海潮生曲并不适合你。";
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/luoying-shenzhang/zhuan", me) )
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？";

        if (me->query_skill("luoying-shenzhang", 1) < 1)
                return "你连落英神剑掌都没学，跑来捣什么乱？";

        if( query("family/gongji", me)<350 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("force") < 180)
                return "你的内功火候尚需提高，练好了再来吧。";

        if (me->query_skill("qimen-wuxing", 1) < 120)
                return "你对奇门五行的研究不够，这招还学不会。";

        if (me->query_skill("luoying-shenzhang", 1) < 120)
                return "哼！等你把落英神剑掌练熟了再来找我！";

        message_sort(HIY "\n$n" HIY "打量了$N" HIY "一眼，随手攻出一掌。$N" HIY
                     "见来势平平，并不见奇，哪知在作出抵挡的一瞬间才发觉$n" HIY
                     "掌力犹如黄河决堤般汹涌而入，$N" HIY "顿时再也把持不住，被"
                     "那掌力带得接连旋转了数圈，好不容易才停了下来。\n\n" NOR,
                     me, this_object());

        command("say 好了，你下去吧。");
        tell_object(me, HIC "你学会了「奇门五转」。\n" NOR);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("luoying-shenzhang"))
                me->improve_skill("luoying-shenzhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/luoying-shenzhang/zhuan", 1, me);
        addn("family/gongji", -350, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/lanhua-shou/fu", me) )
                return "自己下去练，罗嗦什么！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？";

        if (me->query_skill("lanhua-shou", 1) < 1)
                return "你连兰花拂穴手都没学，跑来捣什么乱？";

        if( query("family/gongji", me)<300 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("force") < 160)
                return "你的内功火候尚需提高，练好了再来吧。";

        if (me->query_skill("lanhua-shou", 1) < 120)
                return "等你把兰花拂穴手练熟了再来找老夫。";

        message_sort(HIY "\n$n" HIY "微微点了点头，反手轻轻伸出三指，婉转如一朵"
                     "盛开的兰花，对准$N" HIY "的几处穴道虚击数下。\n\n" NOR,
                     me, this_object());

        command("say 看懂了么？");
        tell_object(me, HIC "你学会了「兰花拂穴」。\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("lanhua-shou"))
                me->improve_skill("lanhua-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lanhua-shou/fu", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/lanhua-shou/fei", me) )
                return "唉…你自己下去练吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？";

        if (me->query_skill("lanhua-shou", 1) < 1)
                return "你连兰花拂穴手都没学，跑来捣什么乱？";

        if( query("family/gongji", me)<400 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("force") < 200)
                return "你的内功火候尚需提高，练好了再来吧。";

        if (me->query_skill("lanhua-shou", 1) < 140)
                return "等你把兰花拂穴手练熟了再来找老夫。";

        message_sort(HIY "\n$n" HIY "一声长叹，伸手将$N" HIY "招至他身旁，低声"
                     "在$N" HIY "耳边细说良久。$N" HIY "一边听一边点头，看来对"
                     "$n" HIY "的教导大有所悟。\n\n" NOR, me, this_object());

        command("say 唉…你自己下去练吧。");
        tell_object(me, HIC "你学会了「影落飞花」。\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("lanhua-shou"))
                me->improve_skill("lanhua-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lanhua-shou/fei", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/yuxiao-jianfa/tian", me) )
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？";

        if (me->query_skill("yuxiao-jianfa", 1) < 1)
                return "你连玉箫剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<350 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("bibo-shengong", 1) < 120)
                return "你碧波神功的修为不够，学不了这一招。";

        if (me->query_skill("yuxiao-jianfa", 1) < 120)
                return "你的玉箫剑法还不够熟练，练高了再来找我。";

        message_sort(HIY "\n$n" HIY "微微点了点头，伸手将$N" HIY "招到面前，在"
                     "$N" HIY "耳边轻声嘀咕了些话。$N" HIY "听了半天，突然间不"
                     "由会心的一笑，看来大有所悟。\n\n" NOR, me, this_object());

        command("nod2");
        command("say 你下去练吧。");
        tell_object(me, HIC "你学会了「天外清音」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yuxiao-jianfa"))
                me->improve_skill("yuxiao-jianfa", 1500000);
        if (me->can_improve_skill("bibo-shengong"))
                me->improve_skill("bibo-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuxiao-jianfa/tian", 1, me);
        addn("family/gongji", -350, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/yuxiao-jianfa/qing", me) )
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？";

        if (me->query_skill("yuxiao-jianfa", 1) < 1)
                return "你连玉箫剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("force") < 200)
                return "你的内功火候尚需提高，练好了再来吧。";

        if (me->query_skill("yuxiao-jianfa", 1) < 150)
                return "就你这点本事？等你把玉箫剑法练熟了再来找我吧！";

        message_sort(HIY "\n$n" HIY "举头望天，若有所思，随手搭在$N" HIY "的肩"
                     "头，$N" HIY "忽然发现内力源源而逝，不由大惊！\n\n" NOR,
                     me, this_object());

        command("sigh");
        command("say 你懂了么？");
        tell_object(me, HIC "你学会了「天地情长」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yuxiao-jianfa"))
                me->improve_skill("yuxiao-jianfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuxiao-jianfa/qing", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/yuxiao-jianfa/bihai", me) )
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？";

        if (me->query_skill("yuxiao-jianfa", 1) < 1
        &&  me->query_skill("bibo-shengong", 1) < 1
        &&  me->query_skill("bihai-chaosheng", 1) < 1)
                return "你玉箫剑法、碧波神功、碧海潮生曲一样都没学，捣什么乱？";

        if( query("family/gongji", me)<1000 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("bibo-shengong", 1) < 180)
                return "你碧波神功的修为不够，学不了这一招。";

        if (me->query_skill("yuxiao-jianfa", 1) < 180)
                return "你的玉箫剑法还不够熟练，练高了再来找我。";

        if (me->query_skill("bihai-chaosheng", 1) < 180)
                return "你的碧海潮生曲练好了吗？";

        message_sort(HIY "\n$n" HIY "更不答话，单手抚按玉箫，只听得箫声如鸣琴击"
                     "玉，发了几声，接着悠悠扬扬，飘下清亮柔和的洞箫声来。只听那"
                     "洞箫声情致飘忽，缠绵宛转，便似一女子一会儿叹息，一会儿又似"
                     "呻吟，一会儿却又软语温存或柔声叫唤。紧跟着那箫声清亮宛如大"
                     "海浩淼，万里无波，远处潮水缓缓推近，渐近渐快，其后洪涛汹涌"
                     "，白浪连山，而潮水中鱼跃鲸浮，海面上风啸鸥飞，再加上水妖海"
                     "怪，群魔弄潮，忽而冰山飘至，忽而热海如沸，极尽变幻之能事。"
                     "时至最后，却听那箫声愈来愈细，几乎难以听闻，便尤如大海潮退"
                     "后水平如镜一般，但海底却又是暗流湍急，汹涌澎湃。直待$n" HIY
                     "这首碧海潮生曲奏完，却发现$N" HIY "早已陶醉在这箫声之中，完"
                     "全无法自拔。\n\n" NOR, me, this_object());

        command("nod");
        command("say 你下去练吧。");
        tell_object(me, HIC "你学会了「碧海潮生按玉箫」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("chuixiao-jifa"))
                me->improve_skill("chuixiao-jifa", 1500000);
        if (me->can_improve_skill("yuxiao-jianfa"))
                me->improve_skill("yuxiao-jianfa", 1500000);
        if (me->can_improve_skill("bibo-shengong"))
                me->improve_skill("bibo-shengong", 1500000);
        if (me->can_improve_skill("bihai-chaosheng"))
                me->improve_skill("bihai-chaosheng", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuxiao-jianfa/bihai", 1, me);
        addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/ding", me) )
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "你连弹指神通都没学，瞎胡闹什么？";

        if( query("family/gongji", me)<450 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("force") < 180)
                return "你的内功火候尚需提高，练好了再来吧。";

        if (me->query_skill("tanzhi-shentong", 1) < 120)
                return "你的弹指神通火候还不够，等你练熟了再来找我。";

        message_sort(HIY "\n$n" HIY "转过头看了$N" HIY "一眼，更不答话，只是轻"
                     "轻伸出两指，合指轻弹，顿时只听“飕”的一声，一缕若有若无"
                     "的罡气已至$n" HIY "指尖射出，朝$N" HIY "电射而去。$N" HIY
                     "顿觉胁下一麻，已被$n" HIY "的指气射中，全身酸软无力，呆立"
                     "当场。\n\n" NOR, me, this_object());

        command("say 招式便是如此，你站在这里琢磨一下吧。");
        tell_object(me, HIC "你学会了「定昆仑」。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/ding", 1, me);
        addn("family/gongji", -450, me);
        me->start_busy(15);

        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/xiao", me) )
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "你连弹指神通都没学，瞎胡闹什么？";

        if( query("family/gongji", me)<800 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("force") < 280)
                return "你的内功火候尚需提高，练好了再来吧。";

        if( query("max_neili", me)<3000 )
                return "你的内力修为太差，还是练高点再来吧。";

        if (me->query_skill("tanzhi-shentong", 1) < 200)
                return "你的弹指神通火候还不够，等你练熟了再来找我。";

        message_sort(HIY "\n$n" HIY "一声长叹，伸手将$N" HIY "招至他身旁，低声"
                     "在$N" HIY "耳边细说良久。$N" HIY "一边听一边点头，看来对"
                     "$n" HIY "的教导大有所悟。\n\n" NOR, me, this_object());

        command("nod2");
        command("say …嗯…你自己练去吧。");
        tell_object(me, HIC "你学会了「啸沧海」。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/xiao", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/po", me) )
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "你连弹指神通都没学，瞎胡闹什么？";

        if( query("family/gongji", me)<1300 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("force") < 250)
                return "你的内功火候尚需提高，练好了再来吧。";

        if( query("max_neili", me)<2500 )
                return "你的内力修为太差，还是练高点再来吧。";

        if (me->query_skill("throwing", 1) < 180)
                return "你的暗器运用还不够娴熟，下去练练再来吧。";

        if (me->query_skill("tanzhi-shentong", 1) < 180)
                return "你的弹指神通火候还不够，等你练熟了再来找我。";

        message_sort(HIY "\n$n" HIY "微微一笑，当下也不作答，随手从身旁桃花树"
                     "上拈下一片花瓣，$N" HIY "正感纳闷，忽闻破空声大作，那片"
                     "花瓣已由$n" HIY "指尖疾弹而出，顿时只听噗嗤一声，已没入"
                     "$N" HIY "身前的青石砖内，石面仅留下一个小孔。\n\n" NOR,
                      me, this_object());

        command("haha");
        tell_object(me, HIC "你学会了「破九域」。\n" NOR);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/po", 1, me);
        addn("family/gongji", -1300, me);

        return 1;
}

mixed ask_skill10()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/zhuan", me) )
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "你连弹指神通都没学，瞎胡闹什么？";

        if( query("family/gongji", me)<2200 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。";

        if (me->query_skill("force") < 300)
                return "你的内功火候尚需提高，练好了再来吧。";

        if( query("max_neili", me)<3500 )
                return "你的内力修为太差，还是练高点再来吧。";

        if (me->query_skill("qimen-wuxing", 1) < 200)
                return "你对奇门五行的研究不够，这招还学不会。";

        if (me->query_skill("tanzhi-shentong", 1) < 220)
                return "你的弹指神通火候还不够，等你练熟了再来找我。";

        message_sort(HIY "\n$n" HIY "凝视了$N" HIY "半天，方道：“想不到我桃花"
                     "岛居然还有你这等人才，想必日后继承老夫衣钵非你莫属了。”"
                     "$n" HIY "说完哈哈一笑，将$N" HIY "招至身旁，低声细说讲解"
                     "良久，全是$N" HIY "平生从未涉入的境界，$N" HIY "一边听一"
                     "边点头，看来对$n" HIY "的教导大有所悟。\n\n" NOR,
                     me, this_object());

        command("haha");
        command("say 能传授的我都已传授了，日后就自己努力吧。");
        tell_object(me, HIC "你学会了「转乾坤」。\n" NOR);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/zhuan", 1, me);
        addn("family/gongji", -2200, me);

        return 1;
}

//增加漫天花雨的PFM
mixed ask_skill11() 
{ 
        object me; 
        
        me = this_player(); 
        
        if( query("can_perform/tanzhi-shentong/huayu", me) )
                return "这一招我不是已经教过你了吗？还罗嗦什么！"; 
        
        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，打听老夫的武功有何企图？"; 
        
        if (me->query_skill("tanzhi-shentong", 1) < 1) 
                return "你连弹指神通都没学，瞎胡闹什么？"; 
        
        if( query("family/gongji", me)<2200 )
                return "你在我桃花岛无所作为，这招老夫暂时还不能传你。"; 
        
        if (me->query_skill("force") < 300) 
                return "你的内功火候尚需提高，练好了再来吧。"; 
        
        if( query("max_neili", me)<3500 )
                return "你的内力修为太差，还是练高点再来吧。"; 
        
        if (me->query_skill("qimen-wuxing", 1) < 200) 
                return "你对奇门五行的研究不够，这招还学不会。"; 
        
        if (me->query_skill("tanzhi-shentong", 1) < 220) 
                return "你的弹指神通火候还不够，等你练熟了再来找我。"; 
        
        message_sort(HIY "\n$n" HIY "凝视了$N" HIY "半天，方道：“想不到我桃花" 
                     "岛居然还有你这等人才，想必日后继承老夫衣钵非你莫属了。”" 
                     "$n" HIY "说完哈哈一笑，将$N" HIY "招至身旁，低声细说讲解" 
                     "良久，全是$N" HIY "平生从未涉入的境界，$N" HIY "一边听一" 
                     "边点头，看来对$n" HIY "的教导大有所悟。\n\n" NOR, 
                     me, this_object());  
        
        command("haha"); 
        command("say 能传授的我都已传授了，日后就自己努力吧。"); 
        tell_object(me, HIC "你学会了「漫天花雨」。\n" NOR); 
        if (me->can_improve_skill("qimen-wuxing")) 
                me->improve_skill("qimen-wuxing", 1500000); 
        if (me->can_improve_skill("qimen-wuxing")) 
                me->improve_skill("qimen-wuxing", 1500000); 
        if (me->can_improve_skill("qimen-wuxing")) 
                me->improve_skill("qimen-wuxing", 1500000); 
        if (me->can_improve_skill("finger")) 
                me->improve_skill("finger", 1500000); 
        if (me->can_improve_skill("finger")) 
                me->improve_skill("finger", 1500000); 
        if (me->can_improve_skill("finger")) 
                me->improve_skill("finger", 1500000); 
        if (me->can_improve_skill("tanzhi-shentong")) 
                me->improve_skill("tanzhi-shentong", 1500000); 
        if (me->can_improve_skill("tanzhi-shentong")) 
                me->improve_skill("tanzhi-shentong", 1500000); 
        if (me->can_improve_skill("tanzhi-shentong")) 
                me->improve_skill("tanzhi-shentong", 1500000); 
        me->improve_skill("martial-cognize", 1500000); 
        set("can_perform/tanzhi-shentong/huayu", 1, me);
        addn("family/gongji", -2200, me);
        
        return 1; 
} 

mixed ask_leave()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) == "桃花岛" )
        {
                message_vision(CYN "$N" CYN "对$n" CYN "怒道：你既然入桃花岛"
                               "门下，桃花阵就伤你不得，要离岛自己走到海边去"
                               "！\n" NOR, this_object(), me);
                return 1;
        }

        command("hmm");
        message_vision(HIW "\n$N" HIW "冷哼一声，挥手招来两个哑仆，将$n" HIW
                       "送了出去。\n\n" NOR, this_object(), me);
        me->move("/d/taohua/haitan");
        message_vision(HIW "\n$N" HIW "跟随哑仆来到了海边。\n\n" NOR, me);
        return 1;
}

mixed ask_book1()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "桃花岛" )
                return "给我滚开！";

        if( query("family/master_id", me) != query("id") )
                return "只有老夫的弟子才配借读此书。";

        if ((int)me->query_skill("taohua-yaoli", 1) < 60)
                return "你对桃花药理的了解太浅，等你有所领悟后再说。";

        ob = find_object(TAOHUA);
        if (! ob) ob = load_object(TAOHUA);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "那本药理不就是你拿着在看吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…桃花药理现在不在我手里。";

                if( query("family/family_name", owner) == "桃花岛" )
                        return "那书现在暂时是你同门"+query("name", owner)+
                               "在看，你要用就去找他吧。";
                else
                return "桃花药理现在落在了"+query("name", owner)+
                       "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        command("say 这本桃花药理你就拿去看吧，可要认真研读。");
        command("give taohua yaoshu to "+query("id", me));
        return 1;
}

mixed ask_book2()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "桃花岛" )
                return "给我滚开！";

        if( query("family/master_id", me) != query("id") )
                return "只有老夫的弟子才配借读此书。";

        if ((int)me->query_skill("chuixiao-jifa", 1) >= 150)
                return "你的箫技到如此地步，那曲谱对你已无多大帮助。";

        ob = find_object(XIAOPU);
        if (! ob) ob = load_object(XIAOPU);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "那本箫谱不就是你拿着在看吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "我的箫谱已经借出去了。";

                if( query("family/family_name", owner) == "桃花岛" )
                        return "箫谱现在暂时是你同门"+query("name", owner)+
                               "在看，你要用就去找他吧。";
                else
                        return "老夫的箫谱现在落在了"+query("name", owner)+
                               "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        command("say 这本箫谱你就拿去看吧。");
        command("give xiao pu to "+query("id", me));
        return 1;
}

mixed ask_book3()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "桃花岛" )
                return "给我滚开！";

        command("say 当年我性子太急，错怪了乘风．．．");
        command("sigh");

        if (! query("xfsy_xinfa_given") || query("xfsy_xinfa_given") < 10)
        {
                command("say 我如今有一套心法，相烦" + RANK_D->query_respect(me) +
                        "交与乘风，照着我这功诀去做，和常人一般慢慢行走却是不难，唉，……");
                ob = new(XUANFENG);
                ob->move(me);
                set("xfsy_xinfa_given", 1);
                message_vision("$N递给$n一张薄纸。\n", this_object(), me);
        } else
                command("say 你去找乘风吧。");
        return 1;
}

mixed ask_book4()
{
        object me = this_player();

        if( query("family/family_name", me) != "桃花岛"
         && !query("can_learn/huang/count", me) )
                return "给我滚开！";

        if( query("combat_exp", me)<1000000 )
                return "你现在的经验太低，还是先多练练基本功。";

        if ((int)me->query_skill("count", 1) < 100)
                return "就算给你也读不懂，和我罗嗦什么。";

        set_temp("taohua/countbook", 1, me);
        command("nod");
        command("say 你去找曲灵风吧，这书我让他在保管。");
        return 1;
}

mixed ask_yuxiao()
{
        object me;
        object ob;
        object owner;
int cost;

        me = this_player();

        if( query("family/family_name", me) != "桃花岛" )
                return "给我滚开！";

        if( query("family/master_id", me) != query("id") )
                return "等你成了老夫的弟子再说。";

        if (me->query_skill("yuxiao-jianfa", 1) < 150)
                return "你还是先将你的玉萧剑法练练高再说。";

        if (me->query_skill("chuixiao-jifa", 1) < 150)
                return "哼！你连箫都吹不好，拿玉萧又有何用？";

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "你为我桃花岛效力还不够，等你拥有足够的师门功绩再来兑换玉箫使用时间吧。";
        ob = find_object(YUXIAO);
        if (! ob) ob = load_object(YUXIAO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "老夫不是把玉萧交给你了吗？还罗嗦什么！";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "玉箫现在不在老夫这里。";

                if( query("family/family_name", owner) == "桃花岛" )
                        return "玉箫现在暂时是你同门"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "老夫的玉箫现在落在了"+query("name", owner)+
                               "手中，你去找他索回吧。";
        }
        ob->move(this_object());
        set_temp("handing", carry_object("/d/taohua/obj/huaban"));
        command("say 念你刻苦用功，今日老夫就将玉箫借给你。");
        command("say 行走江湖万事多加小心，可不要丢了老夫的脸。");
        command("give yu xiao to "+query("id", me));
addn("family/gongji", -cost, me); 
        ob->start_borrowing();
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != "/clone/book/jiuyin1")
        {
                command("say 你给我这种东西干什么？");
                return 0;
        }

        message_sort("黄药师看了看$N送来的秘籍，点了点头，说道：\n"
                     "难得你将真经送回。你送我的东西我就收下了。\n"
                     "作为补偿, 你可以从我这里学点功夫。\n", me);

        command("heihei");
        command("say 好吧，既然这样，我就传你阴阳八卦，你可以随时来问我！");
        destruct(ob);
        set("can_learn/huang/count", 1, me);

        return 1;
}

int ask_shagu()
{
        object me, obj;

        me = this_player();

        command("say 这孩子是我在打听灵风下落时找到的，很可能是灵风之女，可惜不知受了什麽惊吓，变成这种样子。");
        if( (present("amulet",me) || query_temp("play_with_shagu", me)>10 )
         && !query_temp("ask_huang_about_shagu", me) )
        {
                command("say 这孩子脑筋不太好，难得你和她如此投缘，我给你书信一封，如果你见到她爹灵风，烦请转交。");
                obj = new("/d/taohua/obj/shouyu");
                obj->move(me);
                set_temp("ask_huang_about_shagu", 1, me);
                message_vision("$N递给$n一封书信。\n", this_object(), me);
        }

        command("sigh");
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

        case "剑芒" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yuxiao-jianfa/jianmang",
                           "name"    : "剑芒",
                           "sk1"     : "yuxiao-jianfa",
                           "lv1"     : 200,
                           "sk2"     : "bibo-shengong",
                           "lv2"     : 150,
                           "neili"   : 2000,
                           "gongxian": 800, ]));
                break;

        case "剑指相配" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yuxiao-jianfa/jianzhi",
                           "name"    : "剑指相配",
                           "sk1"     : "yuxiao-jianfa",
                           "lv1"     : 120,
                           "sk2"     : "tanzhi-shentong",
                           "lv2"     : 120,
                           "sk3"     : "bibo-shengong",
                           "lv3"     : 120,
                           "gongxian": 800,
                           "neili"   : 1400, ]));
                break;
        case "隔空点穴" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tanzhi-shentong/dian",
                           "name"    : "隔空点穴",
                           "sk1"     : "tanzhi-shentong",
                           "lv1"     : 200,
                           "sk2"     : "bibo-shengong",
                           "lv2"     : 200,
                           "sk3"     : "jingluo-xue",
                           "lv3"     : 200,
                           "gongxian": 3000,
                           "neili"   : 3500, ]));
                break;
        case "灵犀一指" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tanzhi-shentong/lingxi",
                           "name"    : "灵犀一指",
                           "sk1"     : "tanzhi-shentong",
                           "lv1"     : 1000,
                           "sk2"     : "qimen-wuxing",
                           "lv2"     : 200,
                           "sk3"     : "qimen-xuanshu",
                           "lv3"     : 600,
                           "reborn"  : 1,
                           "gongxian": 3000,
                           "neili"   : 3500, ]));
                break;

        default:
                return 0;
        }
}

/*
void unconcious()
{
        die();
}
*/
