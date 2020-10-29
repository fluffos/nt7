#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

string ask_me();
mixed ask_skill1();
mixed ask_skill2();
string ask_recover();
int do_answer(string arg);

void create()
{
            set_name("一灯大师", ({ "yideng dashi", "yideng", "dashi" }));
            set("long", @LONG
一灯大师乃江湖中人称“东邪西毒，南帝北丐”中
的南帝段皇爷，当年凭着段氏“一阳指”而独步武
林，罕逢敌手。但却在中年时因一段悲情而出家为
僧，之后大彻大悟，成为一位得道高僧。
LONG );
            set("title", "大理国退位皇帝");
            set("nickname", HIY "南帝" NOR);
            set("gender", "男性");
            set("age", 71);
            set("shen_type", 1);
            set("attitude", "friendly");

            set("str", 33);
            set("int", 35);
            set("con", 38);
            set("dex", 33);

            set("qi", 6500);
            set("max_qi", 6500);
            set("jing", 5000);
            set("max_jing", 5000);
            set("neili", 8000);
            set("max_neili", 8000);
            set("jiali", 200);
            set("combat_exp", 4000000);
            set("score", 500000);

        set_skill("force", 640);
        set_skill("xiantian-gong", 600);
        set_skill("duanshi-xinfa", 640);
        set_skill("kurong-changong", 640);
        set_skill("dodge", 640);
        set_skill("tiannan-bu", 640);
        set_skill("cuff", 600);
        set_skill("jinyu-quan", 600);
        set_skill("strike", 600);
        set_skill("wuluo-zhang", 600);
        set_skill("sword", 600);
        set_skill("staff", 600);
        set_skill("duanjia-jian", 600);
        set_skill("finger", 640);
        set_skill("qiantian-zhi", 640);
        set_skill("sun-finger", 640);
        set_skill("parry", 600);
        set_skill("jingluo-xue", 10000);
        set_skill("buddhism", 640);
        set_skill("literate", 600);
        set_skill("sanscrit", 600);
        set_skill("qimai-liuzhuan", 700);
        set_skill("martial-cognize", 640);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "sun-finger");

        prepare_skill("finger", "sun-finger");

        create_family("段氏皇族", 11, "传人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.jian" :),
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "finger.die" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

            set("inquiry",([
                  "王重阳"   : "中神通王重阳名动江湖，老衲很是佩服。",
                  "瑛姑"     : "那是老衲出家前的一段孽缘，不提也罢。",
                  "老顽童"   : "呵呵，那人武功高强，可是心机却如顽童一般。",
                  "周伯通"   : "呵呵，那人武功高强，可是心机却如顽童一般。",
                  "郭靖"     : "哦，那个憨小子心地善良，忠厚老实，没黄蓉一定要吃亏。",
                 "黄蓉"     : "是郭靖那憨小子的伴侣吧，人倒很是机灵。",
                  "知识"     : "我可以传授你禅宗心法和梵文，其它的找你的师父学习吧。",
                  "传授"     : "我可以传授你禅宗心法和梵文，其它的找你的师父学习吧。",
                  "阳关三叠" : (: ask_skill1 :),
                "一阳指"   : (: ask_me :),
                "乾阳剑气" : (: ask_skill2 :),
                "疗伤"     : (: ask_recover :),
                "治疗"     : (: ask_recover :),
            ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

            set("master_ob", 5);
        setup();
            carry_object("/clone/cloth/seng-cloth")->wear();
}

void init()
{
        object ob;
        ::init();
        add_action("do_answer","answer");

                 if (interactive(ob = this_player()) && ! is_fighting())
                 {
                   remove_call_out("greeting");
                   call_out("greeting", 1, ob);
                   }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        if( query("shen", ob)<-50000 )
                command("say 这位施主眼中戾气深重，劝施主好自为知。");

        else
        if( query("shen", ob)<-5000 )
                command("say 这位施主，切记魔从心起，其道必诛。");

        else
        if( query("shen", ob)<0 )
                command("say 这位施主，人行江湖，言行当正，切务走进邪魔歪道。");

        else
        if( query("shen", ob)>50000 )
                command("say 施主行事光明磊落，日后必为武林翘楚。");

        else
                command("say 这位施主，光明正道任人走，望施主多加保重。");

        return;
}

int recognize_apprentice(object me, string skill)
{
        if( query("shen", me)<0 )
        {
                command("say 施主眼中戾气深重，多行善事之后老衲自会传授给你。");
                return -1;
        }

        if (skill != "sanscrit" && skill != "buddhism" && skill != "jingluo-xue")
        {
                command("say 这些还是向你的师父学吧，老衲只能传授些知识给你。");
                return -1;
        }

        if (skill == "buddhism" && me->query_skill("buddhism", 1) > 5000)
        {
                command("haha");
                command("say 你的佛法造诣已经非同凡响了，剩下的自己去研究吧。");
                return -1;
        }

        if( !query_temp("can_learn/yideng", me) )
        {
                command("say 南无阿弭佗佛。");
                command("say 既然施主有心面佛，老衲自当竭力传授。");
                set_temp("can_learn/yideng", 1, me);
        }

        return 1;
}
string ask_me()
{
        object me;

        me = this_player();

        if( query("shen", me)<0 )
                return "施主眼中戾气深重，多行善之后老衲自会传授给你。";

        if (me->query_skill("sun-finger", 1) > 600)
               return "你的一阳指练到了这种境界，老衲已没什么可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
               return "不是老衲吝啬，你不是我段家之人，若由老衲之手将这绝学传于它处，恐怕不妥。";

        if( query("combat_exp", me)<500000 )
               return "武功最注重根基，切莫贪图捷径，你把基本功练好后老衲自会传授给你。";

        addn_temp("can_learn/yideng/sun-finger", 1, me);
               return "好吧！老衲就传授一阳指绝技给你，但切记人行江湖，言行当正，不要走进邪魔歪道！";
}
mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/sun-finger/die", me) )
                return "你一阳指练到这种境界，老衲已没什么可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "施主与老衲素不相识，不知施主此话从何说起？";

        if (me->query_skill("sun-finger", 1) < 1)
                return "你连一阳指诀都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<2500 )
                return "你为段氏所作出的贡献还不够，这招老衲暂时还不能传你。";

        if( query("shen", me)<50000 )
                return "你的侠义正事还做得不够，这招老衲暂时还不能传你。";

        if (me->query_skill("force") < 300)
                return "你内功的修为还不够，练高了再来吧。";

        if( query("max_neili", me)<5000 )
                return "你的内力修为还不够，练高点再来吧。";

        if (me->query_skill("jingluo-xue", 1) < 200)
                return "你对经络学的了解还不透彻，研究透了再来找我吧。";

        if (me->query_skill("sun-finger", 1) < 200)
                return "你的一阳指诀功力还不够，练高了再说吧。";

        message_sort(HIY "\n$n" HIY "凝视了$N" HIY "好一会儿，随即点了点"
                     "头，将$N" HIY "招至身边，在耳旁低声细说良久，$N" HIY
                     "听后会心的一笑，看来对$n" HIY "的教导大有所悟。\n\n"
                     NOR, me, this_object());

        command("buddhi");
        command("say 老衲已将此绝技传授给你，切记莫走进邪魔歪道！");
        tell_object(me, HIC "你学会了「阳关三叠」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sun-finger/die", 1, me);
        addn("family/gongji", -2500, me);

        return 1;
}
mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/xiantian-gong/jian", me) )
                return "你先天功的乾阳剑气练到这种境界，老衲已没什么可教的了。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "施主与老衲素不相识，不知施主此话从何说起？";

        if (me->query_skill("sun-finger", 1) < 1)
                return "你连一阳指诀都没学，还谈什么绝招可言？";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "这招暂时不能传授于你，等你学会先天功再来找我吧。";

        if( query("family/gongji", me)<2500 )
                return "你为段氏所作出的贡献还不够，这招老衲暂时还不能传你。";

        if( query("shen", me)<50000 )
                return "你的侠义正事还做得不够，这招老衲暂时还不能传你。";

        if (me->query_skill("force") < 600)
                return "你内功的修为还不够，练高了再来吧。";

        if( query("max_neili", me)<5000 )
                return "你的内力修为还不够，练高点再来吧。";

        if (me->query_skill("xiantian-gong", 1) < 600)
                return "你的先天功功力还不够，练高了再说吧。";

        message_sort(HIY "\n$n" HIY "凝视了$N" HIY "好一会儿，随即点了点"
                     "头，将$N" HIY "招至身边，在耳旁低声细说良久，$N" HIY
                     "听后会心的一笑，看来对$n" HIY "的教导大有所悟。\n\n"
                     NOR, me, this_object());

        command("buddhi");
        command("say 这本是中神通的绝技，现老衲已将此绝技传授给你，切记莫走进邪魔歪道！");
        tell_object(me, HIC "你学会了「乾阳剑气」。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1500000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xiantian-gong/jian", 1, me);
        addn("family/gongji", -2500, me);

        return 1;
}

string ask_recover()
{
        object me;
        me = this_player();

        if (environment(me)!=find_object("/d/heizhao/houyuan"))
                return "施主问的是什么？贫僧不知道啊。\n";
        if( query_temp("yideng_asked", me) )
                return "你需要治疗吗？\n";
        else {
                if( query("family/family_name", me) == "段氏皇族" )
                {
                        set_temp("yideng_asked", 1, me);
                        return "你虔心向佛，老衲自然有义务为你治疗，但不知你是否需要？\n";
                }
                else {
                        set_temp("yideng_asked", 1, me);
                        return "施主既然有缘到来舍下，贫僧自有义务尽地主之宜为阁下治疗，不知阁下是否需要？\n";
                }
        }
}

int do_answer(string arg)
{
        object me;
        me=this_player();

        if( arg == "需要治疗" && query_temp("yideng_asked", me) )
        {
                tell_object(me, "你请求一灯大师为你运功治疗。\n");
                delete_temp("yideng_asked", me);
                if( query("dali/yideng_rewarded", me) )
                {
                        // command("look "+getuid(me));
                        command("say 由老衲治疗一次，你已经得尽天缘了，唉。。。");
                        command("say 为人岂可贪得无厌，唉，请你离开这里吧。");
                        message_vision("$N羞愧难当，面色通红，灰溜溜地离开了。\n", me);
                        me->move("/d/heizhao/maze1");
                        return 1;
                }
                if( query("family/family_name", me) == "段氏皇族" )
                {
                        command("pat "+getuid(me));
                        command("smile");
                        command("say 好的，老衲这就给你治疗。你随我到禅房来。");
                        set_temp("yideng_waitreward", 1, me);
                        delete_temp("yideng_asked", me);
                        this_object()->move("/d/heizhao/chanfang");
                        me->move("/d/heizhao/chanfang");
                        command("say 你准备好了就告诉我。");
                        return 1;
                }
                if( query("kar", me)>random(30) )
                {
                        // command("look "+getuid(me));
                        command("smile");
                        command("say 好的，老衲这就给你治疗。你随我到禅房来。");
                        set_temp("yideng_waitreward", 1, me);
                        delete_temp("yideng_asked", me);
                        this_object()->move("/d/heizhao/chanfang");
                        me->move("/d/heizhao/chanfang");
                        command("say 你准备好了就告诉我。");
                        return 1;
                }
                else {
                        // command("look "+getuid(me));
                        command("sigh");
                        command("say 实在抱歉，施主您缘分不够，老衲不能为你治疗。");
                        command(":(");
                        delete_temp("yideng_asked", me);
                        set("dali/yideng_rewarded", 1, me);
                        return 1;
                }
        }
        if (arg == "我准备好了"
                 && query_temp("yideng_waitreward", me )
                && environment(me)==find_object("/d/heizhao/chanfang"))
        {
                command("nod");
                command("say 你坐正，我这就开始为你治疗了。");
                write("一灯当即闭目垂眉，入定运功，忽的跃起，左掌捂胸，右手伸出 \n");
                write("食指，缓缓的向你头顶百会穴点去。你身不由几的微微一跳，\n");
                write("只觉的一股热气从顶门直透下来。\n");
                write("一灯一指点过，立即缩回，第二指已向点向你的百会穴后一寸五\n");
                write("分处的后顶穴，接着强间，脑户，风府，大锥，陶道，身柱，\n");
                write("神道，灵台一路点将下来。一支香燃了一半，已将你督脉的三十 \n");
                write("大穴顺次点到。\n");
                message_vision(HIR "$N突然觉得一股暖流自顶而入，眼前一黑就什么也看不见了！\n" NOR, me );
                me->unconcious();

                // if (me->query("family/family_name") == "段氏皇族")
                {
                        addn("con", 2, me);
                        addn("dex", 1, me);
                        addn("str", 1, me);
                }
                addn("max_neili", 150, me);
                addn("combat_exp", 15000, me);
                set("dali/yideng_rewarded", 1, me);
                delete_temp("yideng_waitreward", me);
                this_object()->move("/d/heizhao/houyuan");
                me->move("/d/heizhao/houyuan");
                return 1;
        }
        write("你想回答什么(你的回答好像不对)\n");
        return 1;
}
