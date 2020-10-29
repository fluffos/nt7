#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

// skybook start
#define QUESTDIR  "skybook/天龙八部/"
#define QUESTDIR1 "skybook/天龙八部/凌波微步篇/"
#define QUESTDIR2 "skybook/天龙八部/天龙营救篇/"
#define QUESTDIR3 "skybook/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "skybook/天龙八部/大辽救援篇/"
#define QUESTDIR5 "skybook/天龙八部/复兴天下篇/"
#define QUESTDIR6 "skybook/天龙八部/武功/"

mixed ask_duanyu();
mixed rescue_duanyu();
mixed help_tianlong();
mixed rescue_xiaofeng();
mixed ask_jiumozhi();
// skybook end

mixed ask_wldh();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();

void create()
{
        set_name("段正淳", ({ "duan zhengchun", "duan", "zhengchun" }));
        set("title",  "大理国护国大将军" );
        set("nickname", HIR "镇南王" NOR);
        set("long", "他就是大理国的镇南王，当今皇太弟，是有名的爱情圣手。\n");
        set("gender", "男性");
        set("age", 45);
        set("class", "royal");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 28);
        set("int", 30);
        set("con", 31);
        set("dex", 30);
        set("max_qi", 4500);
        set("max_jing", 3000);
        set("neili", 5800);
        set("max_neili", 5800);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 50000);

        set_skill("force", 220);
        set_skill("duanshi-xinfa", 220);
        set_skill("dodge", 200);
        set_skill("tiannan-bu", 200);
        set_skill("cuff", 220);
        set_skill("jinyu-quan", 220);
        set_skill("strike", 220);
        set_skill("wuluo-zhang", 220);
        set_skill("sword", 220);
        set_skill("staff", 220);
        set_skill("duanjia-jian", 220);
        set_skill("finger", 200);
        set_skill("qiantian-zhi", 200);
        set_skill("sun-finger", 200);
        set_skill("parry", 220);
        set_skill("jingluo-xue", 180);
        set_skill("literate", 240);
        set_skill("martial-cognize", 200);

        map_skill("force", "duanshi-xinfa");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "sun-finger");

        prepare_skill("finger", "sun-finger");

        set("rank_info/respect", "风流王爷");
        create_family("段氏皇族", 15, "传人");

        set("inquiry", ([
                "乾阳神指" : (: ask_skill1 :),
                "风云变幻" : (: ask_skill2 :),
                "金玉满堂" : (: ask_skill3 :),
                "惊天一剑" : (: ask_skill4 :),
                "五绝剑"   : (: ask_skill5 :),
                "哀牢山剑意" : (: ask_skill6 :),
                "一阳剑气"   : (: ask_skill7 :),
                "武林大会" : (: ask_wldh :),
                "聚贤庄"   : (: ask_wldh :),
// skybook
                "段誉"     : (: ask_duanyu :),
                "鸠摩智"   : (: ask_jiumozhi :),
                "营救段誉" : (: rescue_duanyu :),
                "救援段誉" : (: rescue_duanyu :),
                "解救萧峰" : (: rescue_xiaofeng :),
                "营救萧峰" : (: rescue_xiaofeng :),
                "天龙有难" : (: help_tianlong :),       
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "sword.jing" :),
                (: perform_action, "sword.lian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("silver", 50);
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() &&
            query_temp("juxianzhuang_step", ob) == 2){
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        set("inquiry/武林大会", (: ask_wldh :));
        set("inquiry/聚贤庄", (: ask_wldh :));

        //say( "段正淳说道：呵呵，这位" + RANK_D->query_respect(ob) + "，好久不见了啊，近来可好？来我大理有事吗？\n");
        command("say 呵呵，这位" + RANK_D->query_respect(ob) + "，好久不见了啊，近来可好？来我大理有事吗？\n");
        return;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("nod");
        command("say 我就收下你，望你好好学习我段家武技，将来有所作为。");
        command("recruit "+query("id", ob));
        return;
}

mixed ask_wldh()
{
        object me = this_player();

        if( (int)query_temp("in_speech")
         || query_temp("juxianzhuang_step", me) != 2 )
                return notify_fail("段正淳很迷惑的看了看你。。。\n");

        set_temp("in_speech", 1);
        remove_call_out("say_msg");
        call_out("say_msg", 1, me, 1);
        return CYN"原来你是为了聚贤庄武林大会的事情而来的。" NOR;
}

int say_msg(object me, int index)
{
        object ob;

        if( environment() != environment(me) )
                return 0;

        switch( index ) {
        case(1):
                message_vision(CYN"$N说道：你什么都不用说了，我是不会去参加这所谓的“正义”之举的。\n"NOR, this_object(), me);
                break;
        case(2):
                message_vision(WHT"<$N皱了皱眉，脸色微微发青。>\n"NOR, this_object(), me);
                break;
        case(3):
                message_vision(CYN"$N说道：江湖上的流言蜚语我听的多了，从来没听过这么离谱的，乔峰是一个有担当，有责任的大英雄，大侠士。\n"NOR, this_object(), me);
                break;
        case(4):
                message_vision(CYN"$N说道：我觉得这件事情里面肯定有什么误会，所谓的杀父、杀母、杀师的事情一定不是乔峰干的，是有人在陷害他。\n"NOR, this_object(), me);
                break;
        case(5):
                message_vision(CYN"$N说道：乔峰是誉儿的结拜兄弟，是阿朱的知己，又是我的救命恩人，乔峰是契丹人又如何？契丹人难道没有英雄好汉？\n"NOR, this_object(), me);
                break;
        case(6):
                message_vision(CYN"$N说道：大理愿与乔峰共同进退。所以我有两件事情，请你帮忙。\n"NOR, this_object(), me);
                break;
        case(7):
                message_vision(CYN"$N说道：第一件事，是把这封信送给徐长老。我在信中已经说明了我不去参加聚贤庄武林大会的理由。\n"NOR, this_object(), me);
                message_vision(WHT"$N拿出一封信交给了$n。\n"NOR, this_object(), me);
                ob = new("/clone/misc/letter");
                set("long", "这是一封"+this_object()->name()+"写给徐长老的亲笔信函。\n", ob);
                set("send_to", "xuzhanglao", ob);
                set("send_from",query("id",  me), ob);
                set("send_from_name", me->name(), ob);
                ob->move(me, 1);
                break;
        case(8):
                message_vision(CYN"$N说道：第二件事，是请你找机会进入聚贤庄，以乔峰的性格，他一定会在聚贤庄出现的，乔峰现在被千夫所指，一定很需要帮忙。\n"NOR, this_object(), me);
                set_temp("juxianzhuang_step", 3, me);
                break;
        default:
                delete("inquiry/武林大会");
                delete("inquiry/聚贤庄");
                delete_temp("in_speech");
                return 1;
        }
        remove_call_out("say_msg");
        call_out("say_msg", 0, me,++index);
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/qiantian-zhi/zhi", me) )
                return "你不是已经学会了么？还有什么疑问？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我们段家的传人，这话是什么意思？";

        if (me->query_skill("qiantian-zhi", 1) < 1)
                return "你连乾天指法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<50 )
                return "你在族里碌碌无为，叫我如何信得过你？";

        if (me->query_skill("force") < 100)
                return "你内功的修为还不够，练高了再来吧。";

        if( query("max_neili", me)<500 )
                return "你的内力修为还不够，练高点再来吧。";

        if (me->query_skill("qiantian-zhi", 1) < 80)
                return "你的乾天指法功力还不够，练高了再说吧。";

        message_sort(HIY "\n$n" HIY "点了点头，将$N" HIY "招至身边，在"
                     "$N" HIY "耳旁低声细说良久，$N" HIY "一边听一边不"
                     "住的点头，看样子大有所悟。\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say 这招很简单，稍加练习便成。");
        tell_object(me, HIC "你学会了「乾阳神指」。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("qiantian-zhi"))
                me->improve_skill("qiantian-zhi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qiantian-zhi/zhi", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}


mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/wuluo-zhang/bian", me) )
                return "你不是已经学会了么？还有什么疑问？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我们段家的传人，这话是什么意思？";

        if (me->query_skill("wuluo-zhang", 1) < 1)
                return "你连五罗轻烟掌都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<150 )
                return "你在族里碌碌无为，叫我如何信得过你？";

        if (me->query_skill("force") < 100)
                return "你内功的修为还不够，练高了再来吧。";

        if( query("max_neili", me)<500 )
                return "你的内力修为还不够，练高点再来吧。";

        if (me->query_skill("wuluo-zhang", 1) < 100)
                return "你的五罗轻烟掌还不够，练高了再说吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，当下更不答话，伸出右掌轻轻"
                     "一抖，登时化出五道掌影，轻飘飘的拍了出去，却听“噗噗"
                     "噗”几声，$n" HIY "掌影激起的劲风竟在$N" HIY "周围的"
                     "地面印出了五个手印。\n\n" NOR, me, this_object());

        command("say 看懂了么？");
        tell_object(me, HIC "你学会了「风云变幻」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("wuluo-zhang"))
                me->improve_skill("wuluo-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/wuluo-zhang/bian", 1, me);
        addn("family/gongji", -150, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/jinyu-quan/man", me) )
                return "你不是已经学会了么？还有什么疑问？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我们段家的传人，这话是什么意思？";

        if (me->query_skill("jinyu-quan", 1) < 1)
                return "你连金玉拳法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<150 )
                return "你在族里碌碌无为，叫我如何信得过你？";

        if (me->query_skill("force") < 100)
                return "你内功的修为还不够，练高了再来吧。";

        if( query("max_neili", me)<500 )
                return "你的内力修为还不够，练高点再来吧。";

        if (me->query_skill("jinyu-quan", 1) < 80)
                return "你的金玉拳法还不够，练高了再说吧。";

        message_sort(HIY "\n$n" HIY "点了点头，将$N" HIY "招至身边，在"
                     "$N" HIY "耳旁低声细说良久，$N" HIY "一边听一边不"
                     "住的点头，看样子大有所悟。\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say 好了，你自己去练吧。");
        tell_object(me, HIC "你学会了「金玉满堂」。\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("jinyu-quan"))
                me->improve_skill("jinyu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinyu-quan/man", 1, me);
        addn("family/gongji", -150, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/jing", me) )
                return "你不是已经学会了么？还有什么疑问？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我们段家的传人，这话是什么意思？";

        if (me->query_skill("duanjia-jian", 1) < 1)
                return "你连段家剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<300 )
                return "你在族里碌碌无为，叫我如何信得过你？";

        if( query("shen", me)<0 )
                return "算了吧，传你绝招只怕你又去作恶！";

        if (me->query_skill("force") < 120)
                return "你的内功的修为不够，练高了再来吧。";

        if( query("max_neili", me)<800 )
                return "你的内力修为还不够，练高点再来吧。";

        if (me->query_skill("duanjia-jian", 1) < 80)
                return "你的段家剑法还不行，练练再说吧！";

        message_sort(HIY "\n$n" HIY "点了点头，沉声道：“我这就给你演示"
                     "一遍，可看清楚了！”说罢只见$n" HIY "拔出腰间长剑"
                     "，深吸一口气，脚下步步进击，稳重之极，手中长剑使得"
                     "犹如飞龙一般，缠绕向$N" HIY "。招式之巧妙，实乃$N"
                     HIY "前所未闻。\n\n" NOR, me, this_object());

        command("haha");
        command("say 招式已经传你了，你自己练去吧。");
        tell_object(me, HIC "你学会了「惊天一剑」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("duanjia-jian"))
                me->improve_skill("duanjia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/duanjia-jian/jing", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/lian", me) )
                return "你不是已经学会了五绝剑么？你要是有疑问我可答不了你。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我们段家的传人，这是什么意思？";

        if( query("shen", me)<0 )
                return "算了吧，传你绝招只怕你又去作恶！";

        message_vision(CYN "$n" CYN "对$N" CYN "苦笑两声道：我"
                       "武功学得也不好，你还是问问皇兄吧！\n" NOR,
                       me, this_object());

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/ailao", me) )
                return "你不是已经学会了么？还有什么疑问？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我们段家的传人，这话是什么意思？";

        if (me->query_skill("duanjia-jian", 1) < 1)
                return "你连段家剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<500 )
                return "你在族里碌碌无为，叫我如何信得过你？";

        if( query("shen", me)<0 )
                return "算了吧，传你绝招只怕你又去作恶！";

        if (me->query_skill("force") < 200)
                return "你的内功的修为不够，练高了再来吧。";

        if( query("max_neili", me)<1500 )
                return "你的内力修为还不够，练高点再来吧。";

        if (me->query_skill("duanjia-jian", 1) < 150)
                return "你的段家剑法还不行，练练再说吧！";

        message_sort(HIY "\n$n" HIY "点了点头，沉声道：“我这就给你演示"
                     "一遍，可看清楚了！”说罢只见$n" HIY "拔出腰间长剑"
                     "剑法突变，剑气纵横，上六剑，下六剑，前六剑，后六剑"
                     "，左六剑，右六剑，三十六路剑法瞬间完成。\n\n" NOR, me, this_object());

        command("haha");
        command("say 招式已经传你了，你自己练去吧。");
        tell_object(me, HIC "你学会了「哀牢山剑意」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("duanjia-jian"))
                me->improve_skill("duanjia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/duanjia-jian/ailao", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}


mixed ask_skill7()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/yiyang", me) )
                return "你不是已经学会了么？还有什么疑问？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是我们段家的传人，这话是什么意思？";

        if (me->query_skill("duanjia-jian", 1) < 1)
                return "你连段家剑法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<800 )
                return "你在族里碌碌无为，叫我如何信得过你？";

        if( query("shen", me)<0 )
                return "算了吧，传你绝招只怕你又去作恶！";

        if (me->query_skill("force") < 300)
                return "你的内功的修为不够，练高了再来吧。";

        if( query("max_neili", me)<1000 )
                return "你的内力修为还不够，练高点再来吧。";

        if (me->query_skill("duanjia-jian", 1) < 120)
                return "你的段家剑法还不行，练练再说吧！";

        message_sort(HIY "\n$n" HIY "点了点头，沉声道：“我这就给你演示"
                     "一遍，可看清楚了！”说罢只见$n" HIY "拔出腰间长剑"
                     "凝神运气，把一阳指指力灌注到长剑上，长剑变得金白"
                     "。\n\n" NOR, me, this_object());

        command("haha");
        command("say 招式已经传你了，你自己练去吧。");
        tell_object(me, HIC "你学会了「一阳剑气」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("duanjia-jian"))
                me->improve_skill("duanjia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/duanjia-jian/yiyang", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

// skybook
mixed ask_duanyu()
{
        object me;
        
        me = this_player();
        if( me->query_condition("killer") )
        {
                command("fear"+query("id", me));
                return "小儿和中原官府应该没有半点关系，"+RANK_D->query_respect(me) +"还是自我小心通缉！";
        }
        
        if( !query(QUESTDIR1+"start", me) && !query(QUESTDIR2+"start", me) )
        { 
                message_vision(HIC"$N脸上露出气愤的神色。\n", this_object());
                command("heng");

                // 如果激活了天书任务，设定标志
                if( query(QUESTDIR+"active", me) )
                { 
                        set(QUESTDIR+"time",time(),me);
                        set(QUESTDIR+"combat_exp",query("combat_exp",me),me);       
                        set(QUESTDIR1+"start",1,me);
                        set_temp(QUESTDIR1+"start",1,me);
                        set_temp("skybook/busy",1,me); // 与任务系统冲突标志
                        
                        log_file("skybook/TLBB", sprintf("%s(%s) 开始天龙八部第一部分。经验：%d。\n", me->name(1),query("id",me), query("combat_exp",me)) );
                        command("say 小儿不爱学武，和我吵了几句就离家出走了，唉......家门不幸啊！");
                        SKYBOOK_D->check_skybook(me, "天龙八部");
                        return 1;
                }
        }
        
        if( query(QUESTDIR1+"start",me) && !query(QUESTDIR1+"wuliangover",me)&& !query(QUESTDIR1+"over",me) )
        {
                message_vision(HIC"$N脸上露出气愤的神色。\n", this_object());
                command("sigh");
                command("shrug "+query("id",me));
                
                command("say 前段时间有人说在无量山附近看到小儿，不知道现在身在何处。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR1+"start",me) && query(QUESTDIR1+"wuliangover",me)&& !query(QUESTDIR1+"over",me))
        {
 
                command("sigh");
                message_vision(HIC"$N脸上露出担心的神色。\n", this_object());
                //时间一天
                if( query(QUESTDIR+"time", me) && time()-query(QUESTDIR+"time",me) < 86400 )
                {
                        if( random(2) ) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
                        else return "誉儿这几天就可能回来了，"+RANK_D->query_respect(me) +"先行休息去吧！";
                }
                set_temp(QUESTDIR1+"2_start",1,me);

                command("say 小儿日前被四大恶人的南海鳄神掳走了，我们正在设法营救他，有来报目前就在无量山附近的一座石屋内。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR1+"start",me)&& query_temp(QUESTDIR1+"2_start",me) && !query_temp(QUESTDIR1+"yingjiu",me)&& !query(QUESTDIR1+"over",me) )
        {
                command("sigh");
                message_vision(HIC"$N脸上露出担心的神色。\n", this_object());
                command("shrug "+query("id", me));
                command("say 刚有探报，小儿确实就在无量山附近的一座石屋内，不得已只怕要走一次了。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR1+"start", me) && query_temp(QUESTDIR1+"yingjiu", me)&& !query(QUESTDIR1+"over",me) )
        {
                command("sigh");
                command("look "+query("id",me));
                command("nod "+query("id",me));
                message_vision(HIC"$n向$N表示真诚的感谢。\n", me, this_object());
                command("say 刚有探报，小儿确实就在无量山附近的一座石屋内，不过，有"+RANK_D->query_respect(me) +"相助，料无大碍。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR1+"start", me) && query(QUESTDIR1+"over", me)&& !query(QUESTDIR2+"start", me) )
        {
                command("thank "+query("id", me));
                message_vision(HIC"$n向$N表示真诚的感谢。\n", me, this_object());
                command("say 多谢"+RANK_D->query_respect(me) +"搭救小儿，只是这万劫谷之后，身体一直不调，才被送往天龙寺求救去了。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR2+"start", me) && !query(QUESTDIR2+"over", me)&& !query_temp(QUESTDIR2+"caught",me) )
        {
                command("sigh "+query("id", me));
                command("say 小儿自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救去了。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR2+"start", me) && !query(QUESTDIR2+"over", me) )
        {
                command("sigh");
                command("say 竟然惹出鸠摩智这等高手，但愿小儿吉人天相啊。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        command("nod "+query("id", me));
        return "段誉正是犬子，不知道找他何事。";
}

mixed rescue_duanyu()
{
        object me;
        object *obj;
        int i, j;
        
        i =random(5)+2;
        j =random(4)+3;
        me=this_player();

        if( !query(QUESTDIR1+"start", me) )
        {
                command("?");
                return "小儿向来只爱佛法已经，平易近人，援救之说何来之说？";
        }
        
        if( query(QUESTDIR1+"start", me) && !query(QUESTDIR1+"wuliangover", me) && !query(QUESTDIR1+"over", me) )
        {
                command("shrug "+query("id", me));
                command("say 前段时间有人说在无量山附近看到小儿，这等贪玩，就让他去吧。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR1+"start", me) && query(QUESTDIR1+"wuliangover", me) && !query_temp(QUESTDIR1+"2_start", me) && !query(QUESTDIR1+"over", me) )
        {
                command("sigh");
                command("say 小儿最近收了个莫名其妙的弟子，好像叫什么南海鳄鱼？我总是担心啊，千万不要出什么乱子。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR1+"start", me) && query_temp(QUESTDIR1+"2_start", me) && !query_temp(QUESTDIR1+"yingjiu", me) && !query(QUESTDIR1+"over", me) )
        {
                if( query("shen", me)<0 )
                        return ("我看" + RANK_D->query_respect(me) +"面带阴邪之气，恐怕是四大恶人一伙的奸细。");
                if( query("combat_exp", me)<1500000 )
                           return ("四大恶人都是绝顶高手,"+RANK_D->query_respect(me) +"似乎武功不够，和四大恶人相斗会有性命之忧。");
                set_temp(QUESTDIR1+"step", i, me);
                set_temp(QUESTDIR1+"steps", j, me);
                command("look "+query("id", me));
                //增加时间和经验间隔限制
                //时间一天
                if( query(QUESTDIR+"time", me) && time()-query(QUESTDIR+"time", me)<86400 )
                {
                        if(random(2)) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
                        else return "誉儿被那四大恶人擒走，这件事还需从长计议，"+RANK_D->query_respect(me) +"千万不得鲁莽。";
                }
                //考虑很多限制，这里经验差距变得少一点
                if( query(QUESTDIR+"combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"combat_exp", me)<100000 )
                        return "以"+RANK_D->query_respect(me) +"目前的经验就算目前有情况，也帮不上什么忙，还是抓紧练功吧！";

                //设定标志
                set(QUESTDIR+"time", time(), me);
                set(QUESTDIR+"combat_exp",query("combat_exp",  me), me);
                command("touch "+query("id", me));
                set_temp(QUESTDIR1+"yingjiu", 1, me);
                set_temp("skybook/busy", 1, me);//与任务系统冲突标志
                
                log_file("skybook/TLBB",sprintf("%s(%s)开始准备营救段誉（第一章）。经验：%d。\n",me->name(1),query("id", me),query("combat_exp", me)));
                
                message_vision("$N说道：既然"+ RANK_D->query_respect(me) +"有意相助，定会如虎添翼。居我得知，誉儿被四大恶人之首\n"+
                        "段延庆囚在正在无量山附近的一座石屋内，只是路上十分险恶，之前为了探明路线，\n"+
                        "我已损失好几名手下。你先去大理北面去无量山路上的一个小溪那里，向北行五里，\n"+
                        "再向西行"+chinese_number(j)+"里，再向北行"+chinese_number(i)+"里，然后会到一座高山，再往后就要见机行事了。\n\n"+
                        "$N接着说道：好了，准备一下，为了不惊动对方，切记要在晚上行动，路上小心。\n", me, this_object());
                
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR1+"start", me) && query_temp(QUESTDIR1+"yingjiu", me) && !query(QUESTDIR1+"over", me) )
        {
                command("look "+query("id", me));
                command("touch "+query("id", me));
                command("say 有"+RANK_D->query_respect(me) +"相助，料无大碍。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR1+"start", me) && query(QUESTDIR1+"over", me) && !query(QUESTDIR2+"start", me) )
        {
                command("thank "+query("id", me));
                command("say 多谢"+RANK_D->query_respect(me) +"搭救小儿，只是这万劫谷之后，身体一直不调，才被送往天龙寺求救去了。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR2+"start", me) && !query(QUESTDIR2+"over", me) && !query_temp(QUESTDIR2+"caught", me) )
        {
                command("sigh "+query("id", me));
                command("say 小儿自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救去了。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR2+"start", me) && !query(QUESTDIR2+"over", me) )
        {
                command("sigh "+query("id", me));
                command("look "+query("id", me));
                command("say 竟然惹出鸠摩智这等高手，但愿小儿吉人天相啊。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        command("nod "+query("id", me));
        return "小儿向来只爱佛法已经，平易近人，援救之说何来之说？";
}

mixed ask_jiumozhi()
{
        object me;
        
        me = this_player();
        
        if( query(QUESTDIR1+"over", me) && !query(QUESTDIR2+"start", me) )
        {
                command("nod "+query("id", me));
                return "听说，大轮寺第一高僧鸠摩智将来我天龙寺佛法交流，真是我大理之幸啊。";
        }
        
        if( query(QUESTDIR2+"start", me) && !query(QUESTDIR2+"over", me) )
        {
                command("sigh");
                command("? "+query("id", me));
                command("say 这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧，所谓口生莲花，全是一派胡言。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR2+"start", me) && query(QUESTDIR2+"over", me) )
        {
                command("nod "+query("id", me));
                return "鸠摩智妄为西域第一佛法高僧，所谓口生莲花，全是一派胡言。";
        }
        
        command("nod");
        return "大轮明王鸠摩智是吐蕃国的护国法王，但听说他具大智慧，精通佛法，想来武功也是惊人。";
}

mixed rescue_xiaofeng()
{
        object me;
        
        me = this_player();
        if( !query(QUESTDIR3+"start", me) )
        {
                command("hoho");
                return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
        }
        
        if( query(QUESTDIR3+"start", me) && !query(QUESTDIR3+"over", me) )
        {
                command("sigh");
                command("shrug "+query("id", me));
                return "听说这件事情，只是涉及到大辽与大宋之争，实在不好插手。";
        }

        if( query(QUESTDIR3+"bad", me) )
        {
                command("heng");
                command("? "+query("id", me));
                return "萧峰，难不是你所迫出中原，今日所谓搭救不知何意。";
        }
        
        if( query(QUESTDIR3+"start", me) && query(QUESTDIR3+"over", me) && !query(QUESTDIR4+"start", me) )
        {
                command("sigh");
                command("shrug "+query("id", me));
                return "听说这件事情，只是涉及到大辽与大宋之争，实在不好插手。";
        }
        
        if( query(QUESTDIR4+"start", me) && !query(QUESTDIR4+"over", me) )
        {
                command("nod "+query("id", me));
                command("say 萧峰乃小儿之义兄，自然要救。这位"+RANK_D->query_respect(me) +"可先行一步，大理段家弟子随后援到。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR4+"start", me) && query(QUESTDIR4+"over", me) )
        {
                command("haha "+query("id", me));
                return "这一战真是痛快，"+query("name", me)+"更是威震武林，端得厉害啊。";
        }
        
        return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
}

mixed help_tianlong()
{
        object me;
        
        me = this_player();
        if( !query(QUESTDIR1+"over", me) )
        {
                command("haha");
                return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
        }
        
        if( query(QUESTDIR1+"over", me) && !query(QUESTDIR2+"start", me) )
        {
                command("nod "+query("id", me));
                command("say 听说，大轮寺高僧鸠摩智不日将来我天龙寺，不知是喜是祸。");
                return 1;
        }
        
        if( query(QUESTDIR2+"start", me) && !query(QUESTDIR2+"over", me) )
        {
                command("sigh");
                command("say 这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧。");
                SKYBOOK_D->check_skybook(me, "天龙八部");
                return 1;
        }
        
        if( query(QUESTDIR2+"over", me) )
        {
                command("thank "+query("id", me));
                return "多谢"+RANK_D->query_respect(me) +"化解这场天龙危机，还将我侄子得以解救。";
        }
        command("hoho");
        return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
}

/*
void unconcious()
{
        die();
}
*/