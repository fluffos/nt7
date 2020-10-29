// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
inherit F_NOCLONE;

#define CONTRACT        "/d/reborn/obj/contract"

mixed ask_me1();
mixed ask_me2();
mixed ask_me3();
mixed ask_me4();
mixed ask_me5();
mixed ask_me6();
mixed ask_reborn();
mixed ask_buchang();
mixed ask_duanwu();
int full_all();

void create()
{
        set_name("南贤", ({ "nan xian", "nan", "xian" }));
        set("long", @LONG
此人衣着青杉，须发皆白。看似其貌不扬，实
却为世上头号人物。这便是武林中号称「南贤
北丑」的南贤。其为人亦正亦邪，年轻时曾干
下了无数轰天动地的大举。生平决战无数，仅
在北丑手下失过手。
LONG);
        set("nickname", HIW "天下至贤" NOR);
        set("title", HIC "武林泰斗" NOR);
        set("gender", "男性" );
        set("age", 74);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);
        set("level", 100);

        set_skill("force", 500);
        set_skill("huntian-baojian", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("lunhui-jian", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("buddhism", 500);
        set_skill("taoism", 500);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("unarmed", "huntian-baojian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("sword", "lunhui-jian");

        prepare_skill("unarmed", "huntian-baojian");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "name" : "姓名不过是一种代号而已，问它有何意义？",
                "北丑" : "你尽提那个龌龊的家伙做甚？",
                "状态回复": (: full_all :),
                "状态恢复": (: full_all :),
                "恢复": (: full_all :),
                "端午礼物": (: ask_duanwu :),
/*
                "泥潭" : (: ask_me1 :),
                "礼物" : (: ask_me1 :),
                "gift" : (: ask_me1 :),
*/
                "高效练功": (: ask_me2 :),
                "双倍经验": (: ask_me3 :),
                "比武"    : (: ask_me4 :),
                "比武大会": (: ask_me4 :),
                "华山绝顶": (: ask_me4 :),
                "参加比武": (: ask_me4 :),
                "鉴定会员": (: ask_me5 :),
                "鉴定会员级别": (: ask_me5 :),
                "鉴定会员等级": (: ask_me5 :),
                //"新手导师评价票": (: ask_me6 :),
/*
                "转世重生" : (: ask_reborn :),
                "转世" : (: ask_reborn :),
                "重生" : (: ask_reborn :),
                "转生" : (: ask_reborn :),
*/
                //"补偿" : (: ask_buchang :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

        /*
        if (! clonep(this_object()))
        {
                move("/d/city/wumiao");
                message_vision(WHT "\n突然间你眼前一花，身后似乎多了个"
                               "人影。\n" NOR, this_object());
                set("startroom", "/d/city/wumiao");
        }
        */
        set("startroom", "/d/city/wumiao");
        check_clone();
}

void init()
{
/*
        object ob; 
        ::init();

        if (interactive(ob = this_player()) && ! is_fighting()) 
        if (interactive(ob = this_player()) && ! is_fighting() && ! query("welcomegift", ob)) 
        {
                remove_call_out("greeting"); 
                call_out("greeting", 1, ob); 
        }
*/
}

void greeting(object ob) 
{
        if ( ! ob || environment(ob) != environment() ) return; 
        say( CYN "南贤微微一笑道：这位" + RANK_D->query_respect(ob) + CYN + "是新人吧，我这里有个礼物送给你(ask nan xian about 礼物)。\n" NOR); 
}

// 接受询问
mixed accept_ask(object who, string topic)
{
        object me;
        object ob_hlp;
        int i;

        me = this_player();

        if (topic == "寻找帝王符图")
        {
                //if (! me->query("reborn/times")) return "你还没有经过转世重生，无法领取任务！\n";
/*
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return "对不起，帝王符图任务只针对有效会员开放！\n";
*/
                if( query("quest_tuteng/end", me) )
                        return "不错，不错，阁下了却了南贤的心愿，多谢！\n";
                if( query("quest_tuteng/start", me) )
                        return "你已经领取了该任务，请尽快搜集七张帝王符图交给我吧！\n";
                if( query("balance", me)<100000000 )
                        return "你的银库(bank)存款不足，领取该任务需要支付1万两黄金。\n";

                addn("balance", -100000000, me);
                set("quest_tuteng/start", 1, me);

                return "好吧，你就去寻找帝王符图吧。\n";
        }

        if (topic == "任务完成")
        {
                string *spks = ({
                        "zhuque",
                        "tianshen",
                        "qijin",
                        "taxue",
                        "diwang",
                });
//              int n;
                string mapsk;
                string sepk;

                // 检查是否是有效会员
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return "对不起，帝王符图任务只针对有效会员开放！\n";
                // 检查是否领取过任务
                if( !query("quest_tuteng/start", me) )
                        return "我好象没有交给你任务吧。\n";
                // 检查任务是否已完成
                if( query("quest_tuteng/end", me) )
                        return "不错，不错，阁下了却了南贤的心愿，多谢！\n";

                if (me->query_skill("badao", 1) > 0 && me->query_skill("badao", 1) < 600)
                        return "阁下既会霸刀，但修习不深，不如等你再修习一段时间再来吧，以免错失良机。\n";

                // 检查是否存在7张帝王图
                for (i = 1; i <= 7; i ++)
                {
                        if (! objectp(ob_hlp = present("diwang futu" + sprintf("%d", i), me)))
                                return "怎么样，我要的7张帝王图搜集齐了吗\n";

                        if (base_name(ob_hlp) != "/clone/tuteng/futu" + sprintf("%d", i))
                                return "怎么样，我要的7张帝王图搜集齐了吗？\n";
                }

                // 齐全：摧毁7张图
                for (i = 1; i <= 7; i ++)
                {
                        ob_hlp = present("diwang futu" + sprintf("%d", i), me);
                        destruct(ob_hlp);
                }

                // 1、给予奖励--随机SP2（五种）
                //    如果已经购买过SP2了，则不获得该SP2，但可获得经验奖励
                if( !query("quest_tuteng/end3", me) )
                {
                        spks -= keys(query("special_skill", me));
                        if( sizeof(spks) > 0 )
                        {
                                sepk = spks[random(sizeof(spks))];
                                set("special_skill/"+sepk, 1, me);
                                if( sepk == "diwang" )
                                {
                                        addn("int", 2, me);
                                        addn("str", 2, me);
                                        addn("dex", 2, me);
                                        addn("con", 2, me);
                                }
                                write("获取随机图腾技能！ \n");
                        }
                }

                // 2、exp 150万  pot 200 万 weiwang 100万 阅历 100万
                GIFT_D->delay_bonus(me,
                                    ([ "exp"      : 1500000,
                                       "pot"      : 2000000,
                                       "weiwang"  : 1000000,
                                       "score"    : 1000000,
                                       "prompt"   : "你完成帝王符图任务之后"]), 999);

                // 3、所有基本技能及激发在基本技能之上的技能熟练度大幅度提升（最多提升一级）
                mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("dodge");
                if (me->can_improve_skill("dodge"))
                        me->improve_skill("dodge", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("parry");
                if (me->can_improve_skill("parry"))
                        me->improve_skill("parry", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("staff");
                if (me->can_improve_skill("staff"))
                        me->improve_skill("staff", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("unarmed");
                if (me->can_improve_skill("unarmed"))
                        me->improve_skill("unarmed", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("sword");
                if (me->can_improve_skill("sword"))
                        me->improve_skill("sword", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("blade");
                if (me->can_improve_skill("blade"))
                        me->improve_skill("blade", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("finger");
                if (me->can_improve_skill("finger"))
                        me->improve_skill("finger", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("claw");
                if (me->can_improve_skill("claw"))
                        me->improve_skill("claw", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("hand");
                if (me->can_improve_skill("hand"))
                        me->improve_skill("hand", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("strike");
                if (me->can_improve_skill("strike"))
                        me->improve_skill("strike", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("cuff");
                if (me->can_improve_skill("cuff"))
                        me->improve_skill("cuff", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                mapsk = me->query_skill_mapped("whip");
                if (me->can_improve_skill("whip"))
                        me->improve_skill("whip", 15000000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 15000000);

                if (me->can_improve_skill("riding"))
                        me->improve_skill("riding", 15000000);

                if (me->can_improve_skill("martial-cognize"))
                        me->improve_skill("martial-cognize", 15000000);

                // 4、如霸刀等级超过600lv，则传授绝招且霸刀提升5个等级的熟练度，至多可提升5级。
                if (me->query_skill("badao",1) >= 600)
                {
                        message_sort(HIC "\n南贤继续对$N说道：阁下既会霸刀，南贤不才，也略知一二，如谋不弃，"
                                         "就由在下将所知与你讲解一番 ……\n" NOR, me);

                        tell_object(me, HIW "你听了南贤的讲解后，对霸刀有了新的体会！\n" NOR);
                        tell_object(me, HIW "恭喜你，学会了「雄霸天下」及「阿鼻道第一刀」。\n" NOR);
                        set("can_perform/badao/xiong", 1, me);
                        set("can_perform/badao/san-1", 1, me);
                        for (i = 0; i < 5; i ++)
                        {
                                if (me->can_improve_skill("badao"))
                                        me->improve_skill("badao", 15000000);
                        }
                        tell_object(me, HIM "南贤悄悄对你说道：据说，只要你霸刀达到800级，这阿鼻道第二刀可找阴长生学习。\n" NOR);
                        tell_object(me, HIM "南贤又对你说道：可是阴长生不会白教你，需要找到天下第一神酒--天乙神酒与他交换。\n" NOR);
                }
                // 设置任务完成标志
                set("quest_tuteng/end", 1, me);

                me->save();
                log_file("diwang-quest",query("id", me)+"于"+ctime(time())+"完成帝王符图任务！\n");

                return 1;
        }
        if (topic == "修罗道")
        {

                if( query("int", me)<32 || 
                    query("con", me)<32 || 
                    query("str", me)<32 || 
                    query("dex", me)<32 )
                    return "你的先天属性还不足以修炼修罗道，我看你还是先回去吧。\n";
        
                if( query("reborn/times", me)<3 )
                        return "哼，没事别来烦我，走开！\n";
                
                if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                        return "阁下武功已经独步天下，恭喜恭喜！\n";                    

                if (me->query_skill("lunhui-sword",1))
                        return "哼，凡夫俗子，竟然如此贪心！\n";
                                
                // 已经完成任务
                if( query("lunhui-sword_quest/xiuluodao/finish", me) && 
                    me->query_skill("xiuluodao", 1))
                        return "呵呵，多亏你上次帮我，这无敌剑气我已经修炼成功了。\n";
        
                // 分配任务
                if( !query("lunhui-sword_quest/xiuluodao/give_quest", me) )
                {
                        command("hehe");
                        command("say 我正在修炼浑天宝鉴之无敌剑气，急需1把青罡剑练功！");
                        command("ke");
                        command("say 能帮我这个忙吗？");
                        tell_object(me, this_object()->name() + HIG "让你帮他搜集1把青罡剑把，赶快去吧！\n" NOR);
                        set("lunhui-sword_quest/xiuluodao/give_quest", 1, me);
                        me->save();
                        return "事成之后，我会传你几招武功防身！";
                }
                
                // 完成任务
                
                if (! objectp(ob_hlp = present("qinggang jian", me)))
                        return "怎么样，1把青罡剑搜集够了吗？\n";
                        
                if (base_name(ob_hlp) != "/clone/weapon/qinggang-jian")
                        return "怎么样，1把青罡剑搜集够了吗？\n";

                destruct(ob_hlp);
                
                command("hehe");
                command("nod");
                command("say 既然你帮我了这个忙，我就顺便传你一招，相信你以后用得着 ...");
                
                message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳边悄悄说了几句，然后又拿出一本书，指指点点，"
                             "$n" HIC "不住地点头，忽而眉头深锁，忽而低头沉思 ……\n良久，$n" HIC "大笑一声，似乎"
                             "对刚才的疑虑有所顿悟。\n", this_object(), me);
                                        
                tell_object(me, HIG "恭喜你领悟了「修罗道」剑法，目前等级为10级。\n");
                me->set_skill("xiuluodao", 10);
                set("lunhui-sword_quest/xiuluodao/finish", 1, me);
                
                return "明白了？";              
        }
        


        return ULTRA_QUEST_D->accept_ask(this_object(), who, topic);
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        command("say 哼！不知死活。");
        command("exert powerup");
        command("exert sword");
        ::fight_ob(ob);
}

int accept_fight(object who)
{
        command("say 没兴趣。");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("你刚想暗算，可是眼前一花，看不太清楚。\n");
}

mixed ask_me1()
{
        object me = this_player();
        object ob;

        if( query("welcomegift", me) )
        {
                command("say 呵呵～这就是您的不是了！老夫已经给过您礼物了！");
                return 1;
        }
        else
        {
                set("welcomegift", 1, me);
                addn("food", 5000, me);
                addn("water", 10000, me);
                addn("score", 1000, me);
                addn("weiwang", 100, me);
                set("tianfu", 4, me);
                // me->add("potential", 1000);
                me->add_skill("training", 200);

                ob = new("/adm/npc/obj/gift");
                ob->move(me, 1);
                ob = new("/clone/fam/max/zhenyu");
                ob->move(me, 1);
                set("bindable", 3, ob);
                set("bind_owner",query("id",  me), ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
                ob = new("/clone/fam/max/longjia");
                ob->move(me, 1);
                set("bindable", 3, ob);
                set("bind_owner",query("id",  me), ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
                ob = new("/clone/fam/max/xuanhuang");
                ob->move(me, 1);
                set("bindable", 3, ob);
                set("bind_owner",query("id",  me), ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);

                // ob->move(this_object());
                // command("give gift to " + me->query("id"));

                /*
                CHANNEL_D->do_channel(me, "es", sprintf("在下%s今日光临〖泥潭〗（61.128.162.81 : 2001）\n            现已得到南贤的帮助和奖励！即日起开始玩泥巴了！",
                                      me->name(1)));
                */

                message_vision(HIW "$N" HIW "凌空一指，突然天空中一道" HIM "七" HIY "彩" HIR "霞" HIC "光" HIW "笼罩$n，转瞬即逝！\n" NOR,
                               this_object(), me);

                tell_object(me, HIG "南贤送给了你一个礼物（gift），你可以 look gift 来看看是什么礼物。\n" NOR);
                return 1;
        }
}

mixed ask_me2()
{
        int td;
        object me = this_player();

        td = time() / 86400;

        if( query("time_reward/which_day1", me) == td )
                return "你今天已经领过高效练功奖励时间了。";

        if (! MEMBER_D->is_valid_member(me))
        // || (int)MEMBER_D->db_query_member(me, "endtime") < 1888888888)
                return "你不是会员，想要高效练功奖励还是先购买会员卡吧。\n";

/*
        message("member", HIM "\n【泥潭会员】" + me->query_idname() + HIM " 领取二小时的高效练功时间开始计时。\n" NOR,
                all_interactive(), 0);
*/

        tell_object(me, HIR "\n你领取二小时的高效练功时间开始计时，输入指令istat可以查看剩余时间。\n" NOR);

        addn("time_reward/study", 7200, me);
        set("time_reward/which_day1", td, me);
        return 1;
}

mixed ask_me3()
{
        // int t;
        int td;
        object me = this_player();

        td = time() / 86400;

        if( query("time_reward/which_day2", me) != td )
                delete("time_reward/times", me);

        if( query("time_reward/which_day2", me) == td &&
            query("time_reward/times", me) >= 3 )
                return "你今天已经领完所有的双倍经验奖励时间了。";

        if (! MEMBER_D->is_valid_member(me))
                return "你不是会员，想要双倍经验奖励还是先购买会员卡吧。\n";

        /*
        t = localtime(time())[2];
        if (t >= 20 && t < 24)
                return "每天20~24点均为双倍经验时间，现在正处于双倍经验时间段你还是过一会再来领吧。\n";

        message("member", HIM "\n【泥潭会员】" + me->query_idname() + HIM " 领取二小时的双倍奖励时间开始计时。\n" NOR,
                all_interactive(), 0);
        */

        tell_object(me, HIR "\n你领取二小时的双倍经验时间开始计时，输入指令istat可以查看剩余时间。\n" NOR);

        set("time_reward/which_day2", td, me);
        addn("time_reward/quest", 7200, me);
        addn("time_reward/times", 1, me);
        return 1;
}

mixed ask_me4()
{
        object me = this_player();

        tell_object(me, HIY "南贤说道：既然你要参加比武，那么老夫就送你一程！\n" NOR);
        message_vision(HIY "只见南贤伸手一招，一道红光照向$N，$N腾空飞去！\n" NOR, me);
        me->move("/d/huashan/houzhiwangyu");
        return 1;
}

int full_all()
{
        object me, ob;
        int max;

        me = this_object();
        ob = this_player();

        //只开放申请帐号至今不足30天且年龄小于18岁的的ID
        if( time()-query("birthday", ob)>86400*60 )
        {
                command("say 你已经不是新手了，还要我来照顾你的呀？\n");
                return 1;
        }

        max=query("max_jing", ob);
        ob->receive_curing("jing", max);
        ob->receive_heal("jing", max);
        max=query("max_qi", ob);
        ob->receive_curing("qi", max);
        ob->receive_heal("qi", max);
        max=query("max_neili", ob);
        set("neili", max, ob);
        max=query("max_jingli", ob);
        set("jingli", max, ob);
        set("food", ob->max_food_capacity(), ob);
        set("water", ob->max_water_capacity(), ob);
        ob->clear_condition();
        ob->start_busy(2);
        message_vision(CYN "$N微笑着伸手朝$n一拂道声：“好了！”\n" NOR,me, ob);
        tell_object(ob, HIC "你顿感如沫春风，神清意爽，疲惫尽去。\n" NOR);
        return 1;
}

mixed ask_me5()
{
        int value, trans, t;
        object me = this_player();

        t = time();
        if( !wizardp(me) && t-query_temp("identify_member", me)<10 )
                return "你刚刚才鉴定过，还是等会再来吧。\n";

        if (! MEMBER_D->is_member(me))
                return "你不是会员，想要鉴定会员等级还是先购买会员卡吧。\n";

        if (MEMBER_D->db_query_member(me, "vip") == 3)
                return "恭喜你，你已经是白金会员了！\n";

        set_temp("identify_member", t, me);

        value = MEMBER_D->db_query_member(me, "payvalue");
        trans = MEMBER_D->db_query_member(me, "transfervalue");
        value -= trans;

        if (value >= 2000)
        {
                MEMBER_D->db_set_member(me, "vip", 3);
                tell_object(me, HIY "\n你目前的会员等级为★★★白金会员★★★，会员商店购物品享受 8 折！\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 1000)
        {
                MEMBER_D->db_set_member(me, "vip", 2);
                tell_object(me, HIY "\n你目前的会员等级为★★黄金会员★★，会员商店购物品享受 8.8 折！\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 500 && MEMBER_D->db_query_member(me, "vip") < 2)
        {
                MEMBER_D->db_set_member(me, "vip", 1);
                tell_object(me, HIY "\n你目前的会员等级为★白银会员★，会员商店购物品享受 9.5 折！\n\n" NOR);
                return 1;
        }
        else
        {
                if (MEMBER_D->db_query_member(me, "vip") == 2)
                        return "你目前的会员等级为黄金会员！\n";

                if (MEMBER_D->db_query_member(me, "vip") == 1)
                        return "你目前的会员等级为白银会员！\n";

                tell_object(me, HIY "\n你目前的会员等级为普通会员。\n" NOR);
                return 1;
        }
}

mixed ask_me6()
{
        int wd;
        object me = this_player();

        wd = time() / 604800;

        if( query("flowers/which_week", me) == wd )
                return "你本周已经领过新手导师评价票了。";

        if (! MEMBER_D->is_valid_member(me))
                return "你不是会员，想要领取新手导师评价票还是先购买会员卡吧。\n";

        tell_object(me, HIR "\n你领取了一张新手导师评价票，输入指令flowers可以查看你拥有的新手导师评价票数。\n" NOR);

        set("flowers/amount", 1, me);
        set("flowers/which_week", wd, me);
        return 1;
}

mixed ask_buchang()
{
        string id, sql;
        int    jointime, endtime, day;
        object me = this_player();
        object ob;


        if( query("gifter/buchang", me) )
                return "你已经领过补偿了,不要太贪心哦。";

        id=query("id", me);

        if( !MEMBER_D->is_member(id) ) // 非冲值用户肯定不是会员
        {
                day = time() + 15724800; // 补偿半年的会员
                sql = sprintf("INSERT INTO %s SET id = \"%s\", jointime = %d, endtime = %d",
                              "members", id, time(), day);
                DATABASE_D->db_query(sql);
                me->set_srv("quit_save", 86400*365); // 1年的离线物品不掉
                ob = new("/clone/goods/washgift");
                ob->move(me, 1);
                set("no_sell", 1, ob);
                set("bindable", 3, ob);
                set("bind_owner", id, ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
                ob = new("/clone/goods/mask");
                ob->move(me, 1);
                set("no_sell", 1, ob);
                set("bindable", 3, ob);
                set("bind_owner", id, ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);
        } else
        {
                jointime = (int)MEMBER_D->db_query_member(id, "jointime");
                if( jointime < 1 ) jointime = time();

                endtime  = (int)MEMBER_D->db_query_member(id, "endtime");
                if( endtime < 1 )  // 非会员
                {
                        day = time() + 15724800;  // 半年的会员
                        me->set_srv("quit_save", 86400*365);
                        ob = new("/clone/goods/washgift");
                        ob->move(me, 1);
                        set("no_sell", 1, ob);
                        set("bindable", 3, ob);
                        set("bind_owner", id, ob);
                        set("auto_load", 1, ob);
                        set("set_data", 1, ob);
                        ob = new("/clone/goods/mask");
                        ob->move(me, 1);
                        set("no_sell", 1, ob);
                        set("bindable", 3, ob);
                        set("bind_owner", id, ob);
                        set("auto_load", 1, ob);
                        set("set_data", 1, ob);
                }
                else
                {
                        // 是否小于年度
                        if( endtime - jointime < 31536000 ||
                            query("online_time", me)<86400*3)//防止刷nt
                        {
                                if( endtime >= time() + 7948800 )
                                {
                                        log_file("buchang", sprintf("%s %s get buchang but the endtime is %d\n",
                                                                    TIME_D->replace_ctime(time()), id, endtime));
                                        endtime = time() + 7948800;
                                }

                                if( endtime > time() )
                                        day = endtime + 15724800; // 半年的会员时间
                                else
                                        day = time() + 15724800;

                                me->set_srv("quit_save", 86400*365);
                                ob = new("/clone/goods/washgift");
                                ob->move(me, 1);
                                set("no_sell", 1, ob);
                                set("bindable", 3, ob);
                                set("bind_owner", id, ob);
                                set("auto_load", 1, ob);
                                set("set_data", 1, ob);
                                ob = new("/clone/goods/mask");
                                ob->move(me, 1);
                                set("no_sell", 1, ob);
                                set("bindable", 3, ob);
                                set("bind_owner", id, ob);
                                set("auto_load", 1, ob);
                                set("set_data", 1, ob);
                        }
                        else
                        {
                                // 是否终身
                                if( endtime - jointime >= 63072000 )
                                {
                                        day = endtime;
                                        MEMBER_D->db_pay_member(id, 200); // 补偿200nt
                                        me->set_srv("quit_save", 86400*365);
                                }
                                else // 是否年度
                                {
                                        if( endtime > time() )
                                                day = endtime + 7948800; // 1个季度的会员时间
                                        else
                                                day = time() + 7948800;

                                        MEMBER_D->db_pay_member(id, 70); // 补偿70nt
                                        me->set_srv("quit_save", 86400*365);
                                        ob = new("/clone/goods/washgift");
                                        ob->move(me, 1);
                                        set("no_sell", 1, ob);
                                        set("bindable", 3, ob);
                                        set("bind_owner", id, ob);
                                        set("auto_load", 1, ob);
                                        set("set_data", 1, ob);
                                }
                        }
                }
                sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                              "members", jointime, day, id);

                DATABASE_D->db_query(sql);
        }

        set("gifter/buchang", 1, me);
        me->save();
        tell_object(me, HIY "\n你领取了(" HIM "当机补偿" NOR + HIY ")，祝你在王者归来里玩的愉快！\n" NOR);
        return 1;
}

mixed ask_duanwu()
{
        string id;
        int    endtime;
        object me = this_player();

        if( query("gift_2013/duanwu", me) )
                return "你已经领过礼物了,不要太贪心哦。";

        id=query("id", me);

        if( !MEMBER_D->is_member(id) ) // 非冲值用户肯定不是会员
                return "你还是先成为年度会员后再来领取礼物。";
                
        endtime  = (int)MEMBER_D->db_query_member(id, "endtime");
        if( endtime < 0 ) endtime = 0; // 非会员
        if( endtime - time() < 15552000 )
                return "你还是先成为年度会员后再来领取礼物。";
        
        if( query("jingmai/finish", me) )
        {
                tell_object(me, HIC "南贤对你说道：你如今大小周天经脉已经贯通了，无需老夫帮忙了，不过老夫可以送你一些NT币！" NOR);
                MEMBER_D->db_pay_member(id, 50); 
                set("gift_2013/duanwu", 1, me);
                return 1;
        }
                      
        delete("jingmai", me);
        set("jingmai/finish", 1, me);
        set("breakup", 1, me);
        set("gift_2013/duanwu", 1, me);
        addn("int", 1, me);
        addn("jm/int", 1, me);
        addn("str", 1, me);
        addn("jm/str", 1, me);
        
        tell_object(me, HIR "只见南贤突然出手在你全身各大要穴连点一通，然后看着你，微笑不语。\n" NOR);
        tell_object(me, HIC "你顿时感觉有股洪流在体内顺着周天经脉循环起来。\n" NOR);
        tell_object(me, HIR "恭喜你！你的大小周天经脉已然贯通！\n" NOR);
        return 1;
}               
                
mixed ask_reborn()
{
        object ob, who, weapon;
        string map_skill, type;

        who = this_player();

        if( query("reborn/times", who) >= 3 )
        {
                message_vision("$N对$n一拱手，道：你已经历过三世轮回了，我看就不用了吧！\n",
                               this_object(), who);
                return 1;
        }

        if( query("reborn_offer", who) )
        {
                message_vision("$N对$n怒道：老夫已经给过你一份阎王契(Contract)，为何还来找我！\n",
                               this_object(), who);
                return 1;
        }

        if( (!query("reborn/times", who) && query("combat_exp", who)<6000000000) ||
            (query("reborn/times", who) == 1 && query("combat_exp", who)<10000000000) ||
            (query("reborn/times", who) == 2 && query("combat_exp", who)<20000000000) )
        {
                message_vision("$N对$n一拱手，道：经验不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        if( query("betrayer", who) )
        {
                message_vision("$N对$n怒道：你还是先把与判师门派中的纠葛解决了再来！\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("force");
        if (who->query_skillo("force", 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N对$n一拱手，道：内功不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("dodge");
        if (who->query_skillo("dodge", 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N对$n一拱手，道：轻功不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("parry");
        if (who->query_skillo("parry", 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N对$n一拱手，道：招架不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        if (who->query_skillo("martial-cognize", 1) < 3600)
        {
                message_vision("$N对$n一拱手，道：武学修养不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        weapon=query_temp("weapon", who);
        if( !objectp(weapon) ) weapon = query_temp("armor/hands", who);
        if( !objectp(weapon) ) weapon = query_temp("armor/finger", who);
        if( !weapon || /*!weapon->is_ultimate()*/ query("status", weapon) < 6 ||
            query("id", who) != weapon->item_owner() )
        {
                message_vision("$N对$n一拱手，道：你必须拥有一把品质完美的兵器，才能转世重生。\n",
                               this_object(), who);
                return 1;
        }

        type=query("skill_type", weapon);
        if( type )
        {
                map_skill = who->query_skill_mapped(type);
                if (! map_skill)
                {
                        message_vision("$N对$n一拱手，道：你必须先激发和你装备的兵器对应的兵器技能。\n",
                                        this_object(), who);
                        return 1;
                }
        }
        else
        {
                type = "unarmed";
                map_skill = who->query_skill_mapped(type);
                if( !map_skill ) { type = "strike"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "hand"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "cuff"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "finger"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) { type = "claw"; map_skill = who->query_skill_mapped(type); }
                if( !map_skill ) {
                        message_vision("$N对$n一拱手，道：你必须先激发和你装备的兵器对应的兵器技能。\n",
                                       this_object(), who);
                        return 1;
                }
        }

        if (who->query_skillo(type, 1) < 3600 ||
            who->query_skillo(map_skill, 1) < 3600)
        {
                message_vision("$N对$n一拱手，道：" + to_chinese(map_skill) + "不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        if (! ultrap(who))
        {
                message_vision("你还没有到大宗师的境界，还是好好学习锻炼吧。\n",
                               this_object(), who);
                return 1;
        }

        if( !query("breakup", who) )
        {
                message_vision("$N对$n一拱手，道：你还没有打通过任督二脉呢。\n",
                               this_object(), who);
                return 1;
        }

        if( query("reborn/times", who) && !query("animaout", who) )
        {
                message_vision("$N对$n一拱手，道：你还没有修炼元婴出世呢。\n",
                               this_object(), who);
                return 1;
        }

        if( query("reborn/times", who) && !query("death", who) )
        {
                message_vision("$N对$n一拱手，道：你还没有打通过生死玄关呢。\n",
                               this_object(), who);
                return 1;
        }

        if( query("couple/couple_id", who) )
        {
                message_vision("$N对$n一拱手，道：你还是先和你的家庭做个交代再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        if( query("bunch", who) )
        {
                message_vision("$N对$n一拱手，道：你还是先和你的帮派做个交代再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        if( query("brothers", who) )
        {
                message_vision("$N对$n一拱手，道：你还是先和你的结义兄弟做个交代再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        if( query("league", who) )
        {
                message_vision("$N对$n一拱手，道：你还是先和你的同盟做个交代再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        if( query("private_room", who) )
        {
                message_vision("$N对$n一拱手，道：你还是先把你的住房拆毁掉再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        message_vision(CYN "$N叹道：「人间本是百桩磨，既然是有心之士相询，老夫也不藏拙，这物事你便收下吧。」\n" NOR,
                       this_object(), who);

        ob = new(CONTRACT);
        ob->move(who, 1);
        set("bindable", 3, ob);
        set("bind_owner",query("id",  who), ob);
        set("owner",query("id",  who), ob);
        set("no_store", 1, ob);
        set("auto_load", 1, ob);
        set("set_data", 1, ob);

        message_vision(HIC "$N拿出一份阎王契(Contract)给$n。\n" NOR
                       CYN "$N续道：「欲成转世奇缘，需向五岳山君献祭，你这便前往泰山、华山、衡山、恒山与嵩山一行吧。」\n" NOR,
                       this_object(), who);

        message("channel:rumor",HBRED"【转世重生】人间："+query("name", who)+"("+query("id", who)+")"
                HBRED "拿到阎王契，开始前往五岳献祭，欲成转世奇缘！\n\n" NOR, users());

        set("reborn_offer", "start", who);

        return 1;
}

int accept_object(object who, object ob)
{
        int r;

        if (r = ULTRA_QUEST_D->accept_object(this_object(), who, ob))
                return r;

        if (base_name(ob) != CONTRACT ||
            query("owner", ob) != query("id", who) )
                return 0;

        if( sizeof(query("offer", ob))<5 )
                return notify_fail(CYN "南贤摇摇头道：「五岳献祭未成，为时尚早。」\n" NOR);

        delete("bindable", ob);
        delete("bind_owner", ob);
        call_out("to_return", 1, who, ob);
        return 1;
}

int to_return(object who, object ob)
{
        if (! ob || ! who) return 0;

        message_vision(CYN "$N点了点头道：「果真是有心人，竟能捱过五岳山君那般挑剔折磨，来，在这里盖个血指印。」\n" NOR
                       HIC "$n依从$N指示，咬破拇指，在阎王契上盖上血指印。\n" NOR
                       HIM "只见阎王契(Contract)突生紫光，血指印旁凭空现出了$n的名字。\n" NOR
                       CYN "$N续道：「速去昆仑之巅寻那昆仑镜，将阎王契投入其中，方可获得肉身入地狱面见阎王之资格。路程险恶，务必小心。」\n" NOR,
                       this_object(), who);

        set("name", MAG"阎王契"NOR, ob);
        ob->set_name(MAG "阎王契" NOR, ({ "contract" }));
        set("long", MAG"这是一份阎王契，上面血指印旁有"+who->query_idname()+"的名字。\n"NOR, ob);
        ob->move(who, 1);
        set("bindable", 3, ob);
        set("bind_owner",query("id",  who), ob);
        set("reborn_offer", "finish", who);
        tell_object(who, HIC "南贤将泛紫光的阎王契(Contract)还给你。\n" NOR);

        return 1;
}

void unconcious()
{
        die();
}