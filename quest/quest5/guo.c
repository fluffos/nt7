// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.
// guojing.c 郭靖

inherit NPC;
#include <ansi.h>

string *degree_desc = ({
        BLU "士卒" NOR,
        BLU "游击" NOR,
        HIC "参将" NOR,
        HIC "裨将" NOR,
        HIY "佐将" NOR,
        HIY "副将" NOR,
        HIR "将军" NOR,
        HIR "提督" NOR,
});

string clear_degree(string arg);
string ask_canjun(string arg);
string ask_jianlou();
string ask_lianzhu();
string ask_fuming();
string ask_shoucheng();
string ask_chetui();

int ask_degree();
int add_degree(object ob,int lv);

void create()
{
        set_name("郭靖", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY "北侠" NOR);
        set("title", "襄阳城大将");
        set("gender", "男性");
        set("age", 41);
        set("long",
                "他就是人称北侠的郭靖，既是蒙古成吉思汗的金刀驸马，又是\n"
                "江南七怪、全真派马钰道长、「北丐」洪七公和「老顽童」周\n"
                "伯通等人的徒弟，身兼数门武功。他身着一件灰色长袍，体态\n"
                "魁梧，敦厚的面目中透出一股威严。\n");
        set("attitude", "friendly");
        set_max_encumbrance(100000000);
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set("chat_chance", 1);
        set("chat_msg", ({
                "郭靖叹了口气道：“蒙古兵久攻襄阳不下，一定会再出诡计，蓉儿又不在身边，这....\n",
                "郭靖说道：“华筝公主近来不知可好，抽空一定要回大漠去看看她。\n",
        }));

        set("inquiry", ([
                "周伯通" : "你见到我周大哥了？他现在可好？\n",
                "老顽童" : "周大哥一贯这样，没点正经！\n",
                "洪七公" : "师父除了吃，就是喜欢玩。到处玩，还是为了找吃的。\n",
                "黄药师" : "那是我泰山大人。他云游四海，神龙见首不见尾的。\n",
                "一灯大师" : "在下对大师好生感激。\n",
                "欧阳锋" : "这个老毒物，害死我六位师父，一待襄阳事了，决不与他干休。\n",
                "黄蓉"   : "蓉儿是我的爱妻，你问她做甚？\n",
                "蓉儿"   : "蓉儿就是蓉儿了。你问这么多干嘛？\n",
                "郭芙"   : "这个女儿，又笨又不听话。\n",
                "郭襄"   : "襄儿生于乱世，这辈子又多艰厄。但愿她能快乐一世。\n",
                "郭破虏" : "那是我的小儿子。\n",
                "杨过"   : "过儿确实有出息。\n",
                "马钰"   : "马道长于我有半师之谊。\n",
                "丘处机" : "邱道长义薄云天，是真豪杰。\n",
                "柯镇恶" : "那是我大师父。\n",
                "朱聪"   : "那是我二师父。\n",
                "韩宝驹" : "那是我三师父。\n",
                "南希仁" : "那是我四师父。\n",
                "张阿生" : "那是我五师父。\n",
                "全金发" : "那是我六师父。\n",
                "韩小莹" : "那是我七师父。\n",
                "丐帮"   : "丐帮英雄几百年了，守卫襄阳多亏了他们。\n",
                "拜师"   : "现在蒙古人围攻襄阳，我哪有心情收徒啊！\n",
                "守城"   : (: ask_shoucheng :),
                "复命"   : (: ask_fuming :),
                "撤退"   : (: ask_chetui :),
                "狙击"   : (: ask_jianlou :),
                "连珠箭法":   (: ask_lianzhu :),
                "策封"   :   (: ask_degree :),
                "参军"   :   (: ask_canjun :),
                ]));

        set("qi", 10000);
        set("max_qi", 10000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 34000);
        set("max_neili", 34000);
        set("jiali", 500);

        set("combat_exp", 25000000);
        set("score", 200000);

        set_skill("force", 320);
        set_skill("xiantian-gong", 320);
        set_skill("yijin-duangu", 320);
        set_skill("guoshi-xinfa", 280);
        set_skill("dodge", 300);
        set_skill("feiyan-zoubi", 280);
        set_skill("jinyan-gong", 300);
        set_skill("shexing-lifan", 300);
        set_skill("unarmed", 300);
        set_skill("changquan", 300);
        set_skill("strike", 320);
        set_skill("dragon-strike", 320);
        set_skill("sword", 280);
        set_skill("yuenv-jian", 280);
        set_skill("parry", 320);
        set_skill("literate", 120);
        set_skill("zuoyou-hubo", 400);
        set_skill("martial-cognize", 320);
        set_skill("craft-cognize", 280);
        set_skill("array-cognize", 280);
        set_skill("arrow", 400);
        set_skill("lianzhu-arrow", 400);

        map_skill("arrow", "lianzhu-arrow");
        map_skill("force", "yijin-duangu");
        map_skill("strike", "dragon-strike");
        map_skill("unarmed", "changquan");
        map_skill("sword", "yuenv-jian");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "xianglong-zhang");

        prepare_skill("strike", "dragon-strike");
        
        create_family("郭府", 1, "北侠");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform strike.fei twice") :),
                (: command("perform strike.hui twice") :),
                (: command("perform strike.zhen twice") :),
                (: command("perform strike.qu and strike.hui") :),
                (: command("perform strike.fei and strike.hui") :),
                (: command("perform strike.zhen and strike.hui") :),
                (: command("perform strike.zhen and strike.fei") :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/damage", 300);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 500);

        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object me = this_player();
        object ob;
        ::init();

        if( query("jungong", me)>100 )
                add_action("do_study", "qingjiao");
                
        if (interactive(ob = this_player())
           && userp(ob)
           && !query_temp("mark/guofu_wait", ob )
           && !is_fighting())
        {
/*
                if( query("mark/guofu_over", ob) )
                {
                        command("hmm");
                        command("say 我不是让你另谋出路吗？又跑回来干嘛？");
                        command("say 敦儒，修文，送" + ob->name() + NOR + CYN "出去！");
                        message_vision(HIC "\n只见$N" HIC "一招手，顿时从正厅进来了两"
                                       "位青年，将$n" HIC "架了出去。\n\n",
                                       this_object(), ob);
                        ob->move("/d/xiangyang/westjie1");
                        tell_room(environment(ob), HIC "\n只见两位青年架着" + ob->name() +
                                                   HIC "从郭府大厅走了过来。\n" NOR, ({ ob }));
                } else
                if( query("mark/guofu_out", ob )
                 && query("combat_exp", ob)<100000 )
                {
                        command("say 你现在的武功已经有一定的底子了，应该多走动走动。");
                        command("say 别老是呆在我这里，这对你帮助不大。敦儒，修文，送客！");
                        message_vision(HIC "\n只见$N" HIC "一招手，顿时从正厅进来了两"
                                       "位青年，将$n" HIC "送了出去。\n\n",
                                       this_object(), ob);
                        ob->move("/d/xiangyang/westjie1");
                        tell_room(environment(ob), HIC "\n只见两位青年陪着" + ob->name() +
                                                   HIC "从郭府大厅走了过来。\n" NOR, ({ ob }));
                } else
                if ((int)ob->query_condition("killer"))
                {
                        command("sigh");
                        command("say 你杀性如此之重，我这里也留不得你，你还是走吧。");
                        command("say 敦儒，修文，送客！");
                        message_vision(HIC "\n只见$N" HIC "一招手，顿时从正厅进来了两"
                                       "位青年，将$n" HIC "架了出去。\n\n",
                                       this_object(), ob);
                        ob->move("/d/xiangyang/westjie1");
                        set("mark/guofu_over", 1, ob);
                        delete("mark/guofu_ok", ob);
                        tell_room(environment(ob), HIC "\n只见两位青年架着" + ob->name() +
                                                   HIC "从郭府大厅走了过来。\n" NOR, ({ ob }));
                } else
*/
                // 隐藏情节：郭靖教授三门特殊武功
                if( query("mark/guofu_ok", ob)//①确认被收容于郭府
                   && query("mark/guofu_job", ob)>200//②郭府工作总量大于两百
                   && query("combat_exp", ob)>10000//③确认经验值在一万和两万之间
                   && query("combat_exp", ob)<500000
                   && !query_temp("job_name", ob)//④此时没有领取工作
                   && !query("family/family_name", ob)//⑤没有拜师
                   && !query("can_learn/3skills/guojing", ob)//⑤保证以前未触发此情节
                   && ! stringp(ob->query_skill_mapped("force"))) //⑥ 没有激发特殊内功
                {
                        command("look "+query("id", ob));
                        command("yi");
                        command("whisper "+query("id", ob)+"你在我郭府内工作也有"
                                "一定的时间\n了，怎么连一技之长也没有？以后怎能行走江"
                                "湖啊？…嗯…这\n样好了，从今日起，你每天到我这里来，"
                                "我传授你几项简单的\n特殊武功好了。\n" NOR);
                        set("can_learn/3skills/guojing", 1, ob);
                }
         }
}

string ask_shoucheng()
{
        object *ene;
        object me = this_player();

        if (is_fighting())
        {
                ene = query_enemy();

                if (sizeof(ene) > 1)
                        return "“请" + RANK_D->query_respect(me) + "稍等片刻，我先和这" +
                                sizeof(ene) + "位高手切磋几下！”\n";
                if (sizeof(ene) == 1)
                        return "“请" + RANK_D->query_respect(me) + "稍等片刻，我先和" +
                                ene[0]->name() + "切磋几下！”\n";
        }

        if( query_temp("guo_shoucheng/mark_shadi", me) )
                return "“" + RANK_D->query_respect(me) + "不是已有守城任务了吗！”\n";

        if( query_temp("guo_shoucheng/mark_jianlou", me) )
                return "“" + RANK_D->query_respect(me) + "不是已有狙击任务了吗！”\n";

        if( query("combat_exp", me)<100000 )
                       return "“" + RANK_D->query_respect(me) + "手无缚鸡之力，还是别领任务的为好！”\n";

               if ((int)me->query_skill("force", 1) < 60)
                       return "守城是件危险工作，我看" + RANK_D->query_respect(me) + "的基本内力不足！\n";

               if ((int)me->query_condition("jobshadi_failed"))
               {
                message_vision("$N对着$n摇了摇头说：逃跑失败了还来见我??\n", this_object(), me);
                return "“" + RANK_D->query_respect(me) + "你还是别领任务的为好！”\n";
               }

               if( query_temp("guo_shoucheng/failed", me) )
               {
                 delete_temp("guo_shoucheng", me);
                 me->apply_condition("jobshadi_failed", 4);
                 return "“临阵脱逃，还敢回来见我！！？？”\n";
               }

              if ((int)me->query_condition("jobshadi_limit"))
               {
                message_vision("$N对着$n摇了摇头说：你不是正做着守城任务吗??\n", this_object(), me);
                return "“" + RANK_D->query_respect(me) + "你快点回你的岗位上去！”\n";
               }

               if ((int)me->query_condition("guojob2_busy"))
               {
                message_vision(CYN "$N对着$n摇了摇头说：疲惫之师不利作战！！\n" NOR,
                            this_object(), me);
                return "“" + RANK_D->query_respect(me) + "你还是休息一下再来吧！”\n";
               }

               if( query("shen", me)>0 )
               {
                switch (random(2)) {
                case 0:
                        set_temp("guo_shoucheng/mark_shadi", 1, me);
                        set_temp("guo_shoucheng/carry_location", "eastgate1", me);
                        return "“现在蒙古靼子侵犯中原，这位" +
                                RANK_D->query_respect(me) + "去玄武内门帮助宋军守城吧。";

                       break;
                case 1:
                        set_temp("guo_shoucheng/mark_shadi", 2, me);
                        set_temp("guo_shoucheng/carry_location", "northgate1", me);
                        return "“现在蒙古靼子侵犯中原，这位" + RANK_D->query_respect(me) + "去青龙内门帮助宋军守城吧。";

                               break;
                }
        }
        else
        {
        switch( random(2) ) {
                case 0:
                        set_temp("guo_shoucheng/mark_shadi", 3, me);
                        set_temp("guo_shoucheng/carry_location", "southgate1", me);
                return "“现在蒙古靼子侵犯中原，这位"+RANK_D->query_respect(me)+"去朱雀内门帮助宋军守城吧。";

                       break;
                case 1:
                        set_temp("guo_shoucheng/mark_shadi", 4, me);
                        set_temp("guo_shoucheng/carry_location", "westgate1", me);
                return "“现在蒙古靼子侵犯中原，这位"+RANK_D->query_respect(me)+"去白虎内门帮助宋军守城吧。";

                       break;
                }
        }
}


string ask_jianlou()
{
        object *ene;
        object me = this_player();

        if (is_fighting())
        {
                ene = query_enemy();

                if (sizeof(ene) > 1)
                        return "“请"+RANK_D->query_respect(me) +
                               "稍等片刻，我先和这" + sizeof(ene) + "位高手切磋几下！”\n";
                if (sizeof(ene) == 1)
                        return "“请" + RANK_D->query_respect(me) + "稍等片刻，我先和"
                                + ene[0]->name() + "切磋几下！”\n";
        }

        if( query_temp("guo_shoucheng/mark_shadi", me) )
                return "“"+RANK_D->query_respect(me)+"不是已有守城任务了吗！”\n";

        if( query_temp("guo_shoucheng/mark_jianlou", me) )
                return "“"+RANK_D->query_respect(me)+"不是已有狙击任务了吗！”\n";

        if ((int)me->query_condition("jobshadi_failed"))
        {
                message_vision(
                        "$N对着$n摇了摇头说：逃跑失败了还来见我??\n", this_object(), me);
                return "“"+RANK_D->query_respect(me)+"你还是别领任务的为好！”\n";
        }

        if( query_temp("guo_shoucheng/failed", me) )
        {
                delete_temp("guo_shoucheng", me);
                me->apply_condition("jobshadi_failed",4);
                return "“临阵脱逃，还敢回来见我！！？？”\n";
        }

        if ((int)me->query_skill("arrow", 1) < 50)
        {
                message_vision(CYN"$N对着$n摇了摇头说：你的基本箭法太差了！\n"NOR,
                               this_object(), me);
                return "“"+RANK_D->query_respect(me)+"，我怕你难以胜任啊！”\n";
        }

        if ((int)me->query_condition("jobjianlou_limit"))
        {
                message_vision("$N对着$n摇了摇头说：你不是正做着阻击任务吗？？\n",
                                this_object(), me);
                return "“"+RANK_D->query_respect(me)+"，请你快点回你的岗位上去！”\n";
        }

        if ((int)me->query_condition("guojob2_busy"))
        {
                message_vision(CYN"$N对着$n摇了摇头说：疲惫之师不利作战！！\n"NOR,
                                this_object(), me);
                return "“"+RANK_D->query_respect(me)+"你还是休息一下再来吧！”\n";
        }

        set_temp("guo_shoucheng/mark_jianlou", 2, me);
        set_temp("guo_shoucheng/where", "east_out", me);
        return "“那就有劳这位"+RANK_D->query_respect(me) +
               "前往青龙内门的东城箭楼，负责狙击蒙古箭手的任务吧。\n”";
}

string ask_fuming()
{
        int job_pot, job_exp, job_sco, reward;
        int job_mar;
        object me = this_player();

        if( !me->query_condition("jobshadi_failed") && query_temp("guo_shoucheng/failed", me) )
        {
                delete_temp("guo_shoucheng", me);
                me->apply_condition("jobshadi_failed",4);
                return "“临阵脱逃，还敢回来复命！！？？”\n";
        }

        if( query_temp("guo_shoucheng/help_killed", me )
             && !query_temp("guo_shoucheng/job_over", me) )
        {
                job_exp=(query_temp("guo_shoucheng/help_killed", me))*80;
                job_pot = job_exp / 2;
                job_sco = job_pot / 2;
                job_mar = job_pot / 2;

                if (job_exp > 2000) job_exp = 2000;
                if (job_pot > 1000) job_pot = 1000;

/*
                if( query_temp("warquest/guard", me) )
                {
                        job_exp += 2000;
                        job_pot += 1000;
                        addn_temp("warquest/reward", 200, me);
                }
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(me))
                {
                        job_exp *= 2;
                        job_pot *= 2;
                        job_mar *= 2;
                        job_sco *= 2;
                }
#endif
                addn("combat_exp", job_exp, me);
                addn("potential", job_pot, me);
                addn("score", job_sco, me);
                addn("experience", job_mar, me);
*/
                GIFT_D->bonus(me, ([ "exp" : job_exp, "pot" : job_pot, "mar" : job_mar, "score" : job_sco ]));

/*
                tell_object(me, HIW "你被奖励了" + chinese_number(job_exp) + "点经验值及" +
                                chinese_number(job_pot) + "点潜能和" + chinese_number(job_sco) + "点阅历体会。\n" NOR);
*/
                delete_temp("guo_shoucheng", me);
                me->apply_condition("guojob2_busy", 2);
                //addn("guo_shoucheng/reward_exp", job_exp, me);
                //addn("guo_shoucheng/reward_potential", job_pot, me);

                return "“"+RANK_D->query_respect(me) + "，为国杀敌，不错不错！”\n";
        }

        if( !query_temp("guo_shoucheng/mark_shadi", me )
                 && !query_temp("guo_shoucheng/mark_jianlou", me )
                 || !query_temp("guo_shoucheng/job_over", me) )
                return "“你好象没完成任务吧，还来复什么命？”\n";

        if( query_temp("guo_shoucheng/killed_mgb", me)<1 )
        {
                delete_temp("guo_shoucheng", me);
                return "“你杀了几个敌人啊，就从前线逃回来了？\n";
        }

        message_vision(CYN "$N对$n说道：“"+RANK_D->query_respect(me)+"辛苦了，去休息一下吧！”\n" NOR, this_object(), me);

        job_exp=(query_temp("guo_shoucheng/killed_mgb", me))*100;
        job_exp += query_temp("guo_jianlou/killed_mgb", me)*100;
        job_pot = job_exp / 2;
        job_sco = job_pot / 2;
        job_mar = job_pot / 2;

        if (job_exp > 3000) job_exp = 3000;
        if (job_pot > 1500) job_pot = 1500;
        if( query_temp("warquest/guard", me) )
        {
                job_exp += 1000;
                job_pot += 500;
                addn_temp("warquest/reward", 500, me);
        }

        reward=query_temp("guo_shoucheng/killed_mgb", me)/10+1;

/*
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(me))
                {
                        job_exp *= 2;
                        job_pot *= 2;
                        job_mar *= 2;
                        job_sco *= 2;
                        reward  *= 2;
                }
#endif

        tell_object(me, HIW "你被奖励了" + chinese_number(job_exp) + "点经验值及" +
                        chinese_number(job_pot) + "点潜能和" + chinese_number(job_sco) + "点阅历还有一些威望体会。\n" NOR);
*/

        GIFT_D->bonus(me, ([ "exp" : job_exp, "pot" : job_pot, "mar" : job_mar, "score" : job_sco, "weiwang" : 5 ]));

        me->apply_condition("guojob2_busy", 2);

/*
        addn("combat_exp", job_exp, me);
        addn("potential", job_pot, me);
        addn("weiwang", 5, me);
        addn("score", job_sco, me);
        addn("experience", job_mar, me);
*/

        //addn("guo_shoucheng/reward_exp", job_exp, me);
        //addn("guo_shoucheng/reward_potential", job_pot, me);
        addn("jungong", reward, me);

        delete_temp("guo_shoucheng", me);

        return "“" + RANK_D->query_respect(me) + "，为国杀敌，奋勇当先，当记军功" HIY +
                chinese_number(reward) + NOR + CYN "策！！！”\n" NOR;
}

string ask_chetui()
{
        object me;

        me = this_player();

        if( !query_temp("guo_shoucheng/start_job", me )
                 && !query_temp("guo_shoucheng/mark_jianlou", me )
                 && !query_temp("guo_shoucheng/mark_shadi", me) )
                return "你没有领任务,跑这里瞎嚷嚷什麽？";

        me->apply_condition("jobshadi_limit", 0);
        me->apply_condition("jobjianlou_limit", 0);
        addn("combat_exp", -100+random(20), me);
        me->apply_condition("jobshadi_failed", 4);
        delete_temp("guo_shoucheng", me);

        return "没关系，下次继续努力 。";
}

string ask_lianzhu()
{
        object me = this_player(), ob = this_object();

        if( query("jungong", me)>100 )
        {
                message_sort(HIC "$N哈哈大笑道：“这套连珠箭法(lianzhu-arrow)我就" +
                             "传于你了，望你奋勇杀敌，多立战功，我也无憾了！\n" NOR, ob);
                return "时间紧迫，现在就开始学吧(qingjiao lianzhu-arrow)！\n";
        } else
        {
                message_sort(HIC "$N微微点头道：“这套连珠箭法(lianzhu-arrow)是我的" +
                             "毕生心血之作，\n不便轻易相传！！\n" NOR, ob);
                return "若阁下真有奋勇杀敌，助我大宋之心，日后必慷慨相送！\n";
        }
}

int do_study(string arg)
{
        string skill;
        object me = this_player(), ob = this_object();

        if (! arg || arg != "lianzhu-arrow")
                return notify_fail("你要向郭靖请教(qingjiao)什么？\n");

        if (me->query_skill("lianzhu-arrow", 1) > me->query_skill("arrow", 1))
                return notify_fail("你的基本箭法太差了，无法继续学习连珠箭法。\n");

        if (me->query_skill("lianzhu-arrow", 1) * me->query_skill("lianzhu-arrow", 1) > query("jungong", me)*50 )
                return notify_fail("你的守城军功不够多，郭靖不愿继续教你了！\n");

        if( query("learned_points", me) >= query("potential", me) )
                return notify_fail("你的潜能不够了！\n");

        if( query("jing", me)<100 || query("qi", me)<100 )
                return notify_fail("你现在太累了，先休息一下吧！\n");

        me->receive_damage("qi", 10 + random(40));
        me->receive_damage("jing", 10 + random(40));
        addn("learned_points", 1, me);
        message_vision(HIC "$N指点了$n一些有关" HIW "「连珠箭法」" HIC "的问题，" +
                       "$n似乎有些心得。\n" NOR, ob, me);

        me->improve_skill("lianzhu-arrow", random(me->query_skill("arrow", 1)));

        return 1;
}

int ask_degree()
{
        int lv;
        object ob = this_player();

        if( query_temp("degree_jungong", ob) )
        {
                command("say " + RANK_D->query_respect(ob) + "稍安勿躁，" +
                        "我已经派人前往请封了！\n");
                return 1;
        }
        
        lv=query("degree_jungong", ob);
        if (lv >= sizeof(degree_desc))
        {
                command("say 草民岂敢为大人请封，大人若亲自前往朝纲，前途自不限量！\n");
                return 1;
        }
                
        if( query("degree_jungong", ob) < 0 )
                delete("degree_jungong", ob);

        if( query("jungong", ob)>
            (100*(1+query("degree_jungong", ob))*(1+query("degree_jungong", ob))) )
                lv=query("degree_jungong", ob)+1;

        if( lv <= query("degree_jungong", ob) )
        {
                command("say"+query("name", ob)+"，要获得更高的策封，必须多立军功才可以啊！\n");
                return 1;
        }

        command("say " + RANK_D->query_respect(ob) + "请稍候，我即刻派人前往京城为" +
                RANK_D->query_respect(ob) + "请封！\n");

        call_out("add_degree", 10, ob, lv);
        set_temp("degree_jungong", 1, ob);
        message("channel:rumor", MAG "【大宋襄阳】" + CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                "，一匹快马从襄阳出发，直奔大宋京城！\n" NOR, users());

        return 1;
}

int add_degree(object ob,int lv)
{
        string degree, old_degree;
        degree = degree_desc[lv-1];

        if( query("degree", ob) )
                old_degree=query("degree", ob);
        else old_degree = "";

        message("channel:rumor", HIY "【大宋京城】奉天承命，皇帝诏曰：" +
                "策封"+old_degree+""+HIW+query("name", ob)+
                HIY " 为大宋 " NOR + degree + HIY "，钦此！\n" NOR, users());

        delete_temp("degree_jungong", ob);

        if( query("degree", ob) )
        {
                if( query("degree_ask", ob) )
                        degree=HIM " ☆ " NOR+clear_degree(query("degree", ob))+
                                 HIM " ☆ " NOR + degree + HIM " ☆ " NOR;
                else
                        degree=HIM " ☆ " NOR+clear_degree(query("degree", ob))+
                                 degree + HIM " ☆ " NOR;
        } else
                degree = HIM " ☆ " NOR + degree + HIM " ☆ " NOR;

        set("degree_jungong", lv, ob);
        set("degree", degree, ob);
        addn("weiwang", lv*200, ob);
        return 1;
}

string clear_degree(string arg)
{
        if ((strsrch(arg, BLU "士卒" NOR) >= 0) ||
            (strsrch(arg, BLU "游击" NOR) >= 0) ||
            (strsrch(arg, HIC "参将" NOR) >= 0) ||
            (strsrch(arg, HIC "裨将" NOR) >= 0) ||
            (strsrch(arg, HIY "佐将" NOR) >= 0) ||
            (strsrch(arg, HIY "副将" NOR) >= 0) ||
            (strsrch(arg, HIR "将军" NOR) >= 0) ||
            (strsrch(arg, HIR "提督" NOR) >= 0) ||
            (strsrch(arg, HIM " ☆ " NOR) >= 0))
        {
                arg = replace_string(arg, BLU "士卒" NOR,"");
                arg = replace_string(arg, BLU "游击" NOR,"");
                arg = replace_string(arg, HIC "参将" NOR,"");
                arg = replace_string(arg, HIC "裨将" NOR,"");
                arg = replace_string(arg, HIY "佐将" NOR,"");
                arg = replace_string(arg, HIY "副将" NOR,"");
                arg = replace_string(arg, HIR "将军" NOR,"");
                arg = replace_string(arg, HIR "提督" NOR,"");
                arg = replace_string(arg, HIM " ☆ " NOR,"");
        }
        return arg;
}

string ask_canjun(string arg)
{
        object me = this_player();
        return WAR_D->join_kingwar(me);
}

int recognize_apprentice(object ob, string skill)
{
        if( !query("can_learn/3skills/guojing", ob) )
        {
                command("say 现在蒙古人围攻襄阳，我哪有心情授课啊。");
                command("say 等你将来拜师之后你师父自然会教你，不用心急。");
                return -1;
        }

        if( query("combat_exp", ob)>50000 )
        {
                command("say 你经验也不低了，应该多出去锻炼，呆在这对你帮助不大。\n");
                return -1;
        }

        if (skill != "force"
           && skill != "guoshi-xinfa"
	   && skill != "dodge"
           && skill != "feiyan-zoubi"
           && skill != "unarmed"
           && skill != "changquan")
        {
                command("shake");
                command("say 我最多传授你几项较为基本的特殊技能，复杂了你领悟不了。");
                command("say 你可以跟我学郭氏心法、飞檐走壁、太祖长拳和一些基本技能。\n");
                return -1;
        }

        if( !query_temp("can_learn/guojing", ob) )
        {
                command("nod2");
                command("say 念你勤奋刻苦，我便传授你一些技能，可要认真记好了。");
                set_temp("can_learn/guojing", 1, ob);
        }
        return 1;
}

void unconcious()
{
        full_self();
        return;
}

varargs void die(object killer)
{
        full_self();
        return;
}