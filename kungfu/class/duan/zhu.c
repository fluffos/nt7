#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();

void create()
{
        set_name("朱丹臣", ({ "zhu danchen", "zhu", "danchen" }));
        set("title", "大理国护卫" );
        set("nickname", CYN "笔砚生" NOR);
        set("long", "他是大理国四大护卫之一。一副书生酸溜溜的打扮行头。\n");
        set("gender", "男性");
        set("age", 40);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 20);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 1800);
        set("max_jing", 1000);
        set("neili", 2200);
        set("max_neili", 2200);
        set("jiali", 50);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("duanshi-xinfa", 120);
        set_skill("dodge", 120);
        set_skill("tiannan-bu", 120);
        set_skill("cuff", 120);
        set_skill("jinyu-quan", 120);
        set_skill("strike", 120);
        set_skill("wuluo-zhang", 120);
        set_skill("dagger", 140);
        set_skill("qingliang-daxuefa", 140);
        set_skill("parry", 120);
        set_skill("literate", 100000);
        set_skill("martial-cognize", 140);

        map_skill("force", "duanshi-xinfa");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("dagger", "qingliang-daxuefa");
        map_skill("parry", "qingliang-daxuefa");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");

        set("inquiry", ([
                "透骨钉"   : (: ask_skill1 :),
        ]));

        create_family("段氏皇族", 15, "家臣");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dagger.ding" :),
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/d/dali/npc/obj/junfu")->wear();
        carry_object("/d/meizhuang/obj/panguanbi")->wield();
        add_money("silver", 10);
}

void init()
{
        ::init();
        add_action("do_learn","learn");
        add_action("do_learn","xue");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("smile");
        command("say 世子殿下何需如此，只要有事吩咐在下一声便是。");
        command("say 若世子不嫌弃，我这里倒是有一套笔法可以传授予你。");

        return;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "段氏皇族" )
        {
                command("sneer");
                command("say 我与阁下素不相识，不知阁下此话从何说起？");
                return -1;
        }

        if (skill != "qingliang-daxuefa" && skill != "dagger")
        {
                command("say 朱某生平只对笔法一项有所研究，其它功夫所知甚浅。");
                return -1;
        }

        if( !query_temp("can_learn/zhudanchen", ob) )
        {
                command("hehe");
                command("say 既然世子有心习武，在下理当竭尽所能传授。");
                set_temp("can_learn/zhudanchen", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/qingliang-daxuefa/ding", me) )
                return "我不是已经教给你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和我素无瓜葛，何出此言？";

        if (me->query_skill("qingliang-daxuefa", 1) < 1)
                return "你连我清凉打穴法都未学，怎么来绝招一说？";

        if( query("family/gongji", me)<400 )
                return "恕在下无礼，王爷吩咐过，不得传功给无功子弟。";

        if (me->query_skill("force") < 150)
                return "你的内功修为太差，学不了这一招。";

        if( query("max_neili", me)<1200 )
                return "你的内力修为太差，学不了这一招。";

        if (me->query_skill("qingliang-daxuefa", 1) < 100)
                return "你清凉打穴法的火候还不够，回去练练再来吧。";

        message_sort(HIY "\n$n" HIY "微微一笑，伸手将$N" HIY "招到身前，低"
                     "声在$N" HIY "耳旁嘀咕了半天。然后又拔出腰间铁扇翻转数"
                     "下，斜刺而出。似乎是一种颇为独特的打穴法。\n\n" NOR,
                     me, this_object());

        command("smile");
        command("say 这招并不难练，依世子的悟性很快就可以熟练运用了。");
        tell_object(me, HIC "你学会了「透骨钉」。\n" NOR);
        if (me->can_improve_skill("dagger"))
                me->improve_skill("dagger", 1500000);
        if (me->can_improve_skill("qingliang-daxuefa"))
                me->improve_skill("qingliang-daxuefa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qingliang-daxuefa/ding", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

int accept_object(object who, object ob)
{
        int learn;

        learn=who->query_skill("literate",1);
        learn= learn?learn*10:500;

        if( !query("money_id", ob) )
                return 0;

        if( query("dushu", who) + 1 < 1 )
        {
                say(this_object()->name()+"笑道：“这怎么好意思，您上次给的钱还没读完呢！”\n");
                return 0;
        }

        if( ob->value()/15 + query("dushu", who) < 0 )
        {
                say(this_object()->name()+"受宠若惊地说：“这么多钱我可不敢收呀！”\n");
                return 0;
        }

        if( !query("dushu", who) )
        {
                if( ob->value() >= learn )
                {
                        say(this_object()->name()+"点了点头，说道：哦，像你这麽有心的学生还真是不多见，好好努力\n可以向我请教读书写字(literate)的任何问题。\n");
                        set("dushu", ob->value()/15, who);
                        return 1;
                }
                else
                {
                        say(this_object()->name()+"说道：你的诚意不够，这钱还是拿回去吧。\n");
                        return 0;
                }
        }
        else if(ob->value())
        {
                if( ob->value() >= learn )
                {
                        say(this_object()->name()+"点了点头，说道：哦，像你这麽有心的学生还真是不多见，好好努力将来必定前途无量，谢了。\n");
                        addn("dushu", ob->value()/15, who);
                        return 1;
                }
                else
                {
                        say(this_object()->name()+"说道：你的诚意不够，这钱还是拿回去吧。\n");
                        return 0;
                }
        }
        return 1;
}

int do_learn(string arg)
{
        string skill, teacher;
        object me,ob,room;
        int learn,times,i;
        int master_skill, my_skill, gin_cost, my_combat_exp,grade;
        int t1,t2,t3,t4,lvl,neili_cost;
        string *args;
        int c, r, rand;

        me = this_player();
        ob = this_object();

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if(!arg || arg=="?" || arg=="/?")
                return notify_fail("指令格式：learn <某人> [about] <技能> <次数>\n");

        /*
        if ((sscanf(arg, "%s about %s %d", teacher,skill,times)!=3 ))
        if ((sscanf(arg, "%s %s %d", teacher, skill,times)!=3 ))
                return notify_fail("指令格式：learn <某人> [about] <技能> <次数>\n");
        */

        if( (i = sizeof(args = explode(arg, " "))) < 2 )
                return notify_fail("指令格式：learn|xue <某人> <技能> <次数>\n");

        i--;
        if( i >= 2 && sscanf(args[i], "%d", times) && times )
                i--;
        else
                times = 1;
        skill = args[i--];
        if( args[i] == "about" && i >= 1 )
                i--;
        teacher = implode(args[0..i], " ");

        if (!ob->id(teacher))
                return 0;

        if( me->is_fighting() )
                return notify_fail("临阵磨枪？来不及啦。\n");

        c = 200 + query_temp("apply/learn_times", me);
        if( present("learn emblem", me) )
                c += 1000;

        if( present("learn emblem2", me) )
                c += 1500;

        if( query("special_skill/wisdom", me) )
                c += 1000;

        if( times < 1 || times > c ) {
                write("学习次数最少一次，最多也不能超过" + chinese_number(c) +"次。\n");
                return 1;
        }

        if ((int)times<1) {
                write("你要学几次？\n");
                return 1;
        }

        if( !living(ob) )
                return notify_fail("嗯....你得先把" + ob->name() + "弄醒再说。\n");

        if (me->query_skill("literate",1) >=ob->query_skill("literate", 1) && query("dushu",me))
        {
                command("say 嗯...."+me->name()+"，你学习很用功，但我只能教你到这了。天底下已经无人可以教你了。\n");
                return 1;
        }

        learn=me->query_skill("literate",1);

        if( !query("dushu", me) )
        {
                command("say 咦？"+me->name()+"，我不记得收过你这个学生啊....\n");
                return 1;
        }

        if( query("dushu", me)<times ) {
                command("say 咦？"+me->name()+"，你交的钱已经不够学这么多次了啊....\n");
                return 1;
        }

        if (!learn)     learn=10;
        if (skill!="literate") {
                write("这项技能你恐怕必须找别人学了。\n");
                return 1;
        }
        if (! room=find_object(query("startroom",ob)))
                room=load_object(query("startroom",ob));
        if (room!=environment()){
                command("say 我出来办点事，等我回去再说吧！");
                return 1;
        }
        /*
        if (ob->query("jing<30"))
        {
                 ob->set("env/no_teach",1);
                command("say 我今天累了，我要去休息了！");
                return 1;
        }
        */
        my_skill = me->query_skill(skill, 1);
        master_skill = ob->query_skill(skill, 1);
        if( my_skill >= master_skill ) {
                write("这项技能你的程度已经不输你师父了。\n");
                return 1;
        }

        if( (query("level", me) < 60 && my_skill > 10000) ||
            (query("level", me) < 80 && my_skill > 20000) ||
            (query("level", me) < 100 && my_skill > 30000) ) {
                write("这项技能你的程度已经达到封顶上限了。\n");
                return 1;
        }

        if( (query("potential", me) - query("learned_points",me)) < times )
                return notify_fail("你的潜能不够学习这么多次了。\n");

        gin_cost = 150 / (int)me->query_int() + 1;
        if( !my_skill ) {
                gin_cost *= 2;
                me->set_skill(skill,0);
        }
        printf("你向%s请教有关「%s」的疑问。\n", ob->name(), to_chinese(skill));

        t1 = query("jing",me) / gin_cost;
        t2 = times - t1;
        if( t2 > 0 ) {
                lvl = me->query_skill("force");
                if( lvl <= 0 ) lvl = 1;

                neili_cost =  gin_cost * 60 / lvl;
                if( query("breakup", me) )
                        neili_cost = neili_cost * 7 / 10;

                if( neili_cost < 20 ) neili_cost = 20;

                if( (int)query("neili",me) >= neili_cost * t2 ) {
                        t4 = times;
                        addn("neili", -neili_cost * t2, me);
                }
                else {
                        t3 = (int)query("neili",me) / neili_cost;
                        t4 = t1 + t3;
                        if( t4 == 0 ) {
                                write("然而你今天太累了，无法再进行任何学习了。\n");
                                return 1;
                        }

                        set("neili", 0, me);
                }
        } else
                t4 = times;

        if( times > t1 )
                me->receive_damage("jing", gin_cost * t1);
        else
                me->receive_damage("jing", gin_cost * times);

        if( query("env/auto_regenerate", me) )
                SKILL_D("force/regenerate")->exert(me, me);

        my_combat_exp = (int)query("combat_exp",me);
        if(my_combat_exp < 10000)
                grade = 1;
        else if(my_combat_exp < 80000)
                grade = 3;
        else if(my_combat_exp < 500000)
                grade = 7;
        else
                grade = 13;
        if ( grade < 1 )
                grade = 1;

        rand = 10 + random((int)me->query_int() - 9);
        if( my_skill >= 20000 ) rand /= 4;
        else if( my_skill >= 15000 ) rand /= 3;
        else if( my_skill >= 10000 ) rand /= 2;
        else if( my_skill >= 5000 ) rand = rand * 2 / 3;

        if( intp(r = query_temp("apply/learn_effect",me)) )
                rand += rand * r / 100;

        if( query("time_reward/study",me) )
                rand += rand * 50 / 100;

        if( query("special_skill/wisdom",me) )
                rand += rand * 50 / 100;

        printf("你听了%s的指导，似乎有些心得。\n", ob->name());
        addn("learned_points", t4, me);
        // me->improve_skill(skill, t4*grade * (10 + random((int)me->query_int() - 9)));
        me->improve_skill(skill, t4*grade*rand);

        if( t4 > 0 && t4 < times )
                write("但是你今天太累了，学习了" + chinese_number(t4) +
                      "次以后只好先停下来。\n");

        addn("dushu", -t4, me);
        return 1;
}
