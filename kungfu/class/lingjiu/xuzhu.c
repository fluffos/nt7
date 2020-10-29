// This program is a part of NT MudLIB

#include <ansi.h>
#include "lingjiu.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();

mixed ask_zhenlong();

void create()
{
        set_name("虚竹子", ({ "xuzhu zi", "xuzhu", "xu", "zhu", "zi" }));
        set("long", @LONG
这便是缥缈峰灵鹫宫掌门，道号虚竹子。他看
起来约莫二十五六岁，长得浓眉大眼，大大的
鼻子扁平下塌，容貌颇为丑陋。身穿一件华贵
雅致的长袍，倒使他更显几分精神。
LONG );
        set("title", "缥缈峰灵鹫宫掌门");
        set("gender", "男性");
        set("age", 26);
        set("nickname", HIM "梦郎" NOR);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 35);
        set("int", 15);
        set("con", 35);
        set("dex", 35);

        set("qi", 6000);
        set("max_qi", 6000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 3500000);

        set_skill("force", 600);
        set_skill("xiaowuxiang", 600);
        set_skill("hunyuan-yiqi", 600);
        set_skill("beiming-shengong", 600);
        set_skill("bahuang-gong", 600);
        set_skill("dodge", 600);
        set_skill("yueying-wubu", 600);
        set_skill("shaolin-shenfa", 600);
        set_skill("parry", 600);
        set_skill("hand", 600);
        set_skill("zhemei-shou", 600);
        set_skill("strike", 600);
        // set_skill("piaomiao-zhang", 440);
        set_skill("liuyang-zhang", 600);
        set_skill("cuff", 600);
        set_skill("luohan-quan", 600);
        set_skill("sword", 600);
        set_skill("tianyu-qijian", 600);
        set_skill("throwing", 600);
        set_skill("buddhism", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
        set_skill("fanlao-huantong", 600);

        set("no_teach", ([
                "hunyuan-yiqi"    : "…这…这东西我都没学好。",
                // "xiaowuxiang"      : "唉……这是师尊注如我体内的，教我怎么教给你？",
                "beiming-shengong" : "唉……这是师尊注如我体内的，教我怎么教给你？",
                "shaolin-shenfa"   : "…这个…嗯…我还是教你本门的轻功好了。",
        ]));

        map_skill("force", "bahuang-gong");
        map_skill("dodge", "yueying-wubu");
        map_skill("strike", "liuyang-zhang");
        map_skill("hand", "zhemei-shou");
        map_skill("cuff", "luohan-quan");
        map_skill("parry", "liuyang-zhang");
        map_skill("sword", "tianyu-qijian");
        map_skill("throwing", "liuyang-zhang");

        prepare_skill("hand", "zhemei-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("灵鹫宫", 2, "弟子");

        set("inquiry", ([
                "闪剑诀" : (: ask_skill1 :),
                "幻剑诀" : (: ask_skill2 :),
                "聚剑诀" : (: ask_skill3 :),
                "折梅式" : (: ask_skill4 :),
                "海渊式" : (: ask_skill5 :),
                "生死符" : (: ask_skill6 :),
                "寰阳式" : (: ask_skill7 :),
                "破神诀" : (: ask_skill8 :),
                "珍笼棋局" : (: ask_zhenlong :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhe" :),
                (: perform_action, "hand.hai" :),
                (: perform_action, "strike.huan" :),
                (: perform_action, "strike.zhong" :),
                (: perform_action, "strike.po" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();
        carry_object("/d/lingjiu/obj/changpao")->wear();
        add_money("silver", 50);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say 这位施主…不…是这位阁下眼中似乎邪气太重。");
                command("say 你做点善事之后再来找我吧。");
                return;
        }

        if ((int)ob->query_skill("xiaowuxiang", 1) < 100)
        {
                command("say 这个…这小无相功…应该算是本门修炼内功的基础。");
                command("say 现在嘛…嗯…你还是回去练练吧。");
                return;
        }

        if( query("max_neili", ob)<1200 )
        {
                command("say 这灵鹫宫和少林寺都一样，武功好不好全看内力。");
                command("say 小僧劝…不…是在下劝你还是再回去练练吧。");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("say 你这个…你经验不足，还是去锻炼一下再说吧。");
                return;
        }

        command("nod");
        command("say 今日小僧…在下就收下你，以后你要多做好事。");
        command("say 另外，以后若遇到了少林寺的大师，可千万不能和他们为难。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "dancer" )
                set("class", "dancer", ob);
}

mixed ask_zhenlong()
{
        object me;
        string msg;
        
        me = this_player();
        
        if( query_temp("start_zhenlong", this_object()) )
                return "不好意思，我现在正忙着解这珍笼棋局呢，你还是稍后再来吧。\n";
                
        // 已经帮忙解开珍笼棋局
        if( query("can_perform/liuyang-zhang/hui-quest_end", me) )
                return "阁下是否对珍笼棋局很感兴趣，可惜，在下也没什么好和你切磋的了。\n";
        
        if( !query("can_perform/liuyang-zhang/hui-step1", me) )
        {
                msg = HIG "虚竹子瞪大眼睛对你道：”咦？阁下竟然也知道这珍笼棋局，当年，我也"
                          "是一时幸运，将这棋局解开，不料，竟得一高人将毕生功力相传 ……\n" NOR;
                msg += HIR "你听得连连点头，十分向往，但却未曾见过这传说中的珍笼棋局。\n" NOR;                   
                
                tell_object(me, sort_msg(msg));
                return 1;
        }               
        
        // 如仍未解开24小时内不再帮助解
        if( time() - query("can_perform/liuyang-zhang/hui-quest_last_time", me) < 24 * 3600 )
                return "最近宫中事务繁多，无法抽身，阁下还是过些时候再来吧！\n";
        
        msg = HIG "虚竹子瞪大眼睛对你道：”咦？阁下竟然也知道这珍笼棋局，当年，我也"
                  "是一时幸运，将这棋局解开，不料，竟得一高人将毕生功力相传 ……\n" NOR;
        msg += HIC "你连忙插话道：在下这里正好有一张珍笼棋谱，能否帮忙解之，它日定当涌泉"
                   "相报。说罢，从怀中拿出默写的珍笼棋谱 ……\n" NOR;
        msg += HIG "虚竹子一看，露出一脸微笑对你说道：“不错，当年我曾解开这珍笼棋局，不过，当"
                   "初也是凭借运气胡乱走一通，加上已过多年，现在我也没有十全的把握 ……”\n" NOR;
        if( me->query_family() != "逍遥派" )
        {
                msg += HIR "虚竹子摇了摇头叹道：“我看阁下还是另寻高人吧！\n" NOR;
                tell_object(me, sort_msg(msg));
                return 1;
        }

        msg += HIG "虚竹子略微思索了一下，对你打量一翻道：”天意如此，在下与逍遥派也有一段渊源，"
                   "虽无十足把握，但在下尽管一试，略尽绵力。说罢，接过棋谱专心思索，心无旁骛 ……\n" NOR;
        
        set_temp("start_zhenlong", 1, this_object());
        
        // 1/10几率解成功
        call_out("start_zhenlong", 15, me);        

        tell_object(me, sort_msg(msg));

        set("can_perform/liuyang-zhang/hui-quest_last_time", time(), me);
        me->save();

        return 1;
}

void start_zhenlong(object me)
{
        if (! objectp(me))
        {
                delete_temp("start_zhenlong", this_object());
                return;
        }
        
        if (environment(me) != environment(this_object()))
        {
                delete_temp("start_zhenlong", this_object());
                return;
        }
        
        //if (random(10) != 1)
        if (random(3) != 1)
        {
                tell_object(me, HIW "良久，虚竹子摇头叹气对你道：“看来今天这棋局我是解不开了，我看你还是改日再来吧。\n" NOR);          
                tell_object(me, HIC "你一阵失落，却也无可奈何，寻思还是过段时间再来碰碰运气吧！\n" NOR);
        }
        else
        {
                tell_object(me, HIR "良久，虚竹子大喜道：”好好好，这珍笼棋局已破，阁下快来看看 ……\n" NOR);
                // chess 小于600级无法看懂
                if (me->query_skill("chess", 1) < 600)
                {
                        tell_object(me, HIG "你凑上前去，听虚竹子为你逐一解释破局要点，但是你却听得一头雾水，连连摇头。\n" NOR);
                        tell_object(me, HIC "虚竹子见状叹道：“阁下看来对弈棋之道的领悟还不够，真是可惜！\n" NOR);
                }
                else
                {
                        tell_object(me, sort_msg(HIY "你凑上前去，听虚竹子为你逐一解释破局要点，只见局中“金鸡独立”、“老鼠"
                                                     "偷油”等妙招环环相扣，“倒脱靴”之局也暗含其中。倘若在两侧举棋必输，虚"
                                                     "竹子却在二三路白子一填，黑子跟着倒补，提掉十六个白子后，虚竹子再轻轻"
                                                     "一断，八十余目的黑子全被杀死，真是绝妙之极啊 ……\n" NOR));
                        tell_object(me, HIG "虚竹子笑道：”阁下也是棋艺精湛之人，相信必能将这珍笼棋局破解之法记住。在先还有要事，阁下请便吧。\n" NOR);
                        // 设置解开珍笼棋局标志
                        set("can_perform/liuyang-zhang/hui-quest_end", 1, me);
                        me->save();
                }
        } 
        
        delete_temp("start_zhenlong", this_object());
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/tianyu-qijian/shan", me) )
                return "我…我好象…我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那个…你好象不是我灵鹫宫的人吧？";

        if (me->query_skill("tianyu-qijian", 1) < 1)
                return "你…这个…你好象连天羽奇剑都没学吧，不学哪来绝招？";

        if( query("family/gongji", me)<100 )
                return "…这个…你既然投入了我们灵鹫宫门下，还是…多多少少帮着做点事吧。";

        if (me->query_skill("force") < 100)
                return "…嗯…你的内功火候不足，学不成这招。";

        if (me->query_skill("tianyu-qijian", 1) < 60)
                return "…嗯…你的天羽奇剑还…还得多下功夫练练。";

        message_vision(HIY "$n" HIY "点了点头，从怀中轻轻取出了一本"
                       "剑谱，指着其中的一段对\n$N" HIY "结节不纳的"
                       "细说良久，$N" HIY "一边听一边点头。\n" NOR,
                       me, this_object());


        command("nod");
        command("say 这招的变化很烦琐，需要多多练习。");
        tell_object(me, HIC "你学会了「闪剑诀」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("tianyu-qijian"))
                me->improve_skill("tianyu-qijian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tianyu-qijian/shan", 1, me);
        addn("family/gongji", -100, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/tianyu-qijian/huan", me) )
                return "我…我好象…我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那个…你好象不是我灵鹫宫的人吧？";

        if (me->query_skill("tianyu-qijian", 1) < 1)
                return "你…这个…你好象连天羽奇剑都没学吧，不学哪来绝招？";

        if( query("family/gongji", me)<300 )
                return "…这个…你既然投入了我们灵鹫宫门下，还是…多多少少帮着做点事吧。";

        if (me->query_skill("force") < 160)
                return "…嗯…你的内功火候不足，学不成这招。";

        if (me->query_skill("tianyu-qijian", 1) < 120)
                return "…嗯…你的天羽奇剑还…还得多下功夫练练。";

        message_vision(HIY "$n" HIY "笑了笑，当即从$N" HIY "手中接过"
                       "长剑，慢慢的演示剑招，$N" HIY "见招\n式优美华"
                       "丽，轻盈灵动，实乃前所谓闻，顿时大有所悟。\n"
                       NOR, me, this_object());

        command("nod");
        command("say  …嗯…你自己下去练吧。");
        tell_object(me, HIC "你学会了「幻剑诀」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("tianyu-qijian"))
                me->improve_skill("tianyu-qijian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tianyu-qijian/huan", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/tianyu-qijian/ju", me) )
                return "你…你这个…这招你不是已经学会了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那个…你好象不是我灵鹫宫的人吧？";

        if (me->query_skill("tianyu-qijian", 1) < 1)
                return "你…这个…你好象连天羽奇剑都没学吧，不学哪来绝招？";

        if( query("family/gongji", me)<400 )
                return "…这个…你既然投入了我们灵鹫宫门下，还是…多多少少帮着做点事吧。";

        if (me->query_skill("force") < 180)
                return "…嗯…你的内功火候不足，学不成这招。";

        if (me->query_skill("tianyu-qijian", 1) < 130)
                return "…嗯…你的天羽奇剑还…还得多下功夫练练。";

        message_vision(HIY "$n" HIY "点了点头，从$N" HIY "手中接过"
                       "长剑，手腕轻轻一抖，长剑便化作\n一道彩虹，"
                       "剑光剑花聚为一线，光华眩目，笼罩着$N" HIY
                       "四周。\n" NOR, me, this_object());

        command("nod");
        command("say 能讲的我都讲给你听了，这个…这剩下的就靠你自己了。");
        tell_object(me, HIC "你学会了「聚剑诀」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("tianyu-qijian"))
                me->improve_skill("tianyu-qijian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tianyu-qijian/ju", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/zhe", me) )
                return "你…这个…这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那个…你好象不是我灵鹫宫的人吧？";

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你…这个…你好象连逍遥折梅手都没学吧，不学哪来绝招？";

        if( query("family/gongji", me)<300 )
                return "…这个…你既然投入了我们灵鹫宫门下，还是…多多少少帮着做点事吧。";

        if (me->query_skill("force") < 120)
                return "…嗯…你的内功火候不足，学不成这招。";

        if (me->query_skill("zhemei-shou", 1) < 80)
                return "…嗯…你的逍遥折梅手还…还得多下功夫练练。";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，微微一笑。当下"
                       "一声清啸，合逍遥折梅手诸多变\n化为一式，随手"
                       "轻轻挥出，招数虚虚实实，煞是精妙。直看得$N"
                       HIY "眼\n花缭乱，目瞪口呆。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 招式你都看过了，这…剩下的就靠你自己了。");
        tell_object(me, HIC "你学会了「折梅式」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/zhe", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/hai", me) )
                return "你…这个…这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那个…你好象不是我灵鹫宫的人吧？";

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你…这个…你好象连逍遥折梅手都没学吧，不学哪来绝招？";

        if( query("family/gongji", me)<800 )
                return "…这个…你既然投入了我们灵鹫宫门下，还是…多多少少帮着做点事吧。";

        if (me->query_skill("force") < 200)
                return "…嗯…你的内功火候不足，学不成这招。";

        if (me->query_skill("zhemei-shou", 1) < 130)
                return "…嗯…你的逍遥折梅手还…还得多下功夫练练。";

        message_vision(HIY "$n" HIY "对$N" HIY "点了点头，当下也不答"
                       "话，单手轻轻一挥而出，手出如\n风，单掌顿时变"
                       "化出漫天掌影，虚虚实实，重重叠叠，霎那间已罩"
                       "\n住$N" HIY "周身穴道，$n" HIY "那掌影却只是"
                       "一沾而过，未伤$N" HIY "半毫。招数\n之巧妙，当"
                       "真只能用“无可比拟”四字形容。\n" NOR, me,
                       this_object());

        command("nod2");
        command("say 此招便如海之浩瀚，渊之深绝，可要勤加练习。");
        tell_object(me, HIC "你学会了「海渊式」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/hai", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/zhong", me) )
                return "你…这个…这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那个…你好象不是我灵鹫宫的人吧？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你…这个…你好象连天山六阳掌都没学吧，不学哪来绝招？";

        if( query("family/gongji", me)<600 )
                return "…这个…你既然投入了我们灵鹫宫门下，还是…多多少少帮着做点事吧。";

        if (me->query_skill("force") < 200)
                return "…嗯…你的内功火候不足，学不成这招。";

        if (me->query_skill("liuyang-zhang", 1) < 150)
                return "…嗯…你的天山六阳掌还…还得多下功夫练练。";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，微作迟疑，但接"
                       "着点了点头，将$N" HIY "招至身边，在\n耳旁低声"
                       "细说良久，$N" HIY "听后会心的一笑，看来大有所"
                       "悟。\n" NOR, me, this_object());

        command("buddhi");
        command("say 这…这招厉害得紧，平时可不能胡乱使用。");
        tell_object(me, HIC "你学会了「生死符」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/zhong", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/huan", me) )
                return "你…这个…这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那个…你好象不是我灵鹫宫的人吧？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你…这个…你好象连天山六阳掌都没学吧，不学哪来绝招？";

        if( query("family/gongji", me)<1000 )
                return "…这个…你既然投入了我们灵鹫宫门下，还是…多多少少帮着做点事吧。";

        if (me->query_skill("force") < 200)
                return "…嗯…你的内功火候不足，学不成这招。";

        if (me->query_skill("liuyang-zhang", 1) < 130)
                return "…嗯…你的天山六阳掌还…还得多下功夫练练。";

        message_vision(HIY "$n" HIY "微微一笑，慢悠悠伸出一掌，正搭"
                       "在$N" HIY "的左肩之上，$N" HIY "稍作\n诧异，"
                       "霎时只觉$n" HIY "内力源源不绝的汹涌而入，异"
                       "种真气注满体\n内，全身竟似快要炸裂开来，不禁"
                       "花容失色。\n" NOR, me, this_object());

        command("say 你懂了吗？");
        tell_object(me, HIC "你学会了「寰阳式」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/huan", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/po", me) )
                return "你…你自己下去练习吧。";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "…那个…你好象不是我灵鹫宫的人吧？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你…这个…你好象连天山六阳掌都没学吧，不学哪来绝招？";

        if( query("family/gongji", me)<2200 )
                return "…这个…你既然投入了我们灵鹫宫门下，还是…多多少少帮着做点事吧。";

        if ((int)me->query_skill("bahuang-gong", 1) < 220)
                return "…嗯…你的八荒六合唯我独尊功火候不足，学不成这招。";

        if (me->query_skill("liuyang-zhang", 1) < 220)
                return "…嗯…你的天山六阳掌还…还得多下功夫练练。";

        if( query("max_neili", me)<3500 )
                return "你的内力修为不够，运用这招…嗯…还比较困难。";

        message_vision(HIY "$n" HIY "对$N" HIY "微微一笑，模样颇为赞"
                       "许，说道：“我在这里给你演示\n一遍，能否领悟"
                       "就全靠你的悟性了。”话音刚落，只见$n" HIY "催"
                       "动\n内劲，身形急转，体内真气迸发，长袍随之鼓"
                       "胀。陡然之间，呼的\n一掌猛然拍落，顿时风声四"
                       "起，尘沙弥漫。待得良久，方才烟消云\n散，$N"
                       HIY "到这时才发现$n" HIY "身前青石砖地已被他震"
                       "开了一条长达四\n丈，宽约七尺的裂缝，掌法之玄"
                       "奇，当真惊天地，泣鬼神。\n" NOR, me,
                       this_object());

        command("buddhi");
        command("say 这招乃是我从石壁上习得，想必是童姥生前所创。");
        command("say ……唉…这招的威力太过强盛，切末胡乱使用。");
        tell_object(me, HIC "你学会了「破神诀」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("bahuang-gong"))
                me->improve_skill("bahuang-gong", 1500000);
        if (me->can_improve_skill("bahuang-gong"))
                me->improve_skill("bahuang-gong", 1500000);
        if (me->can_improve_skill("bahuang-gong"))
                me->improve_skill("bahuang-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/po", 1, me);
        addn("family/gongji", -2200, me);
        return 1;
}

/*
void unconcious()
{
        die();
}
*/
