// This program is a part of NITAN MudLIB
// feng.c 风清扬

inherit NPC;
inherit F_MASTER;

#include <ansi.h>

string ask_skill();
string ask_skill1();
string ask_skill2();
string ask_skill3();
mapping po_type = ([ "破剑式" : ({ "sword" }),
                     "破刀式" : ({ "blade" }),
                     "破枪式" : ({ "staff" }),
                     "破鞭式" : ({ "hammer", "club", "dagger" }),
                     "破索式" : ({ "whip" }),
                     "破掌式" : ({ "unarmed", "finger", "claw",
                                   "strike", "hand", "cuff" }),
                     "破箭式" : ({ "throwing" }),
                     "破气式" : ({ "force" }), ]);

int check_skill(string skill);
mixed teach_lonely_sword();

void create()
{
        set_name("风清扬", ({ "feng qingyang", "feng", "qingyang" }));
        set("title", "华山剑宗长老");
        set("nickname", HIW "剑气冲霄" NOR);
        set("long", @LONG
这便是当年名震江湖的华山名宿风清扬。他身
著青袍，神气抑郁脸如金纸。身材瘦长，眉宇
间一直笼罩着一股淡淡的忧伤神色，显然对当
年的剑气之争一直难以忘怀。
LONG);
        set("gender", "男性");
        set("age", 68);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6500);
        set("max_neili", 6500);
        set("jiali", 200);
        set("level", 60);
        set("combat_exp", 4000000);

        set_skill("force", 700);
        set_skill("zixia-shengong", 700);
        set_skill("huashan-neigong", 700);
        set_skill("dodge", 700);
        set_skill("feiyan-huixiang", 700);
        set_skill("huashan-shenfa", 700);
        set_skill("parry", 700);
        set_skill("sword", 700);
        set_skill("huashan-sword", 700);
        set_skill("lonely-sword", 700);
        set_skill("blade", 700);
        set_skill("fanliangyi-dao", 700);
        set_skill("strike", 700);
        set_skill("hunyuan-zhang", 700);
        set_skill("cuff", 700);
        set_skill("poyu-quan", 700);
        set_skill("huashan-quan", 700);
        set_skill("huashan-zhang", 700);
        set_skill("literate", 700);
        set_skill("martial-cognize", 700);

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "lonely-sword");
        map_skill("blade", "fanliangyi-dao");
        map_skill("sword", "lonely-sword");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        //create_family("华山剑宗", 0, "高人");
        create_family("华山派", 0, "高人");

        set("inquiry", ([
                "破众"    : (: ask_skill :),
                "笑沧海"  : (: ask_skill1 :),
                "剑魂"    : (: ask_skill2 :),
                "剑心通明": (: ask_skill3 :),
        ]));

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "sword.yi" :),
                (: perform_action, "sword.poqi" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("can_perform/lonely-sword", ({ "sword", "blade", "staff",
                                           "hammer", "club", "dagger",
                                           "whip", "unarmed", "finger",
                                           "claw", "strike", "hand",
                                           "cuff", "force", "throwing" }));

        set("no_teach", ([
                "lonely-sword" : (: teach_lonely_sword :),
        ]));
        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        object ob, me = this_object();

        ::init();

        if (! objectp(me)) return;
        if (file_name(environment(me)) == "/d/huashan/xiaofang")
        {
                if (interactive(ob = this_player()) && ! ob->is_fighting()
                 && sizeof(query_temp("win", ob)) != 6
                &&  ! wizardp(ob))
                {
                        remove_call_out("auto_kill");
                        call_out("auto_kill", 1, ob );
                }else if( !query("see_feng", ob) )
                {
                        remove_call_out("improve_sword");
                        call_out("improve_sword", 1, ob );
                }
        }
}

int auto_kill(object ob)
{
        object me = this_object();

        command("say 好家伙竟敢谋害桃谷六仙，纳命来吧！");
        me->kill_ob(ob);
        ob->fight(me);
        return 1;
}

int improve_sword(object ob)
{
        int my_sword, add_level;

        if (! objectp(ob)) return 1;
        my_sword = ob->query_skill("sword", 1);
        command("say " + RANK_D->query_respect(ob) + "既然一场来到，你我可谓有缘，待我指点你一些剑法吧。");
        message_vision("风清扬开始为$N解说基本剑法的精义。\n", ob);

        if (my_sword < 100)
        {
                add_level = my_sword + 20;
                tell_object( ob, "你的基本剑法增加了二十级！\n");
        } else
        if (my_sword < 120)
        {
                add_level = my_sword + 10;
                tell_object( ob, "你的基本剑法增加了十级！\n");
        } else
        if (my_sword < 150)
        {
                add_level = my_sword + 5;
                tell_object( ob, "你的基本剑法增加了五级！\n");
        }
        else {
                message_vision("风清扬对着$N惊讶地「啊！」了一声。\n", ob);
                command("say " + RANK_D->query_respect(ob) + "的剑法已然登堂入室，老朽不胜佩服！\n");
                tell_object(ob, "你的基本剑法已踌炉火纯青之境，风清扬已没什么可指点于你的了！\n");
                set("see_feng", 1, ob);
                return 1;
        }

        ob->set_skill("sword", add_level);
        set("see_feng", 1, ob);
        addn("combat_exp", 15000, ob);
        return 1;
}

mixed teach_lonely_sword()
{
        object me;

        me = this_player();

        if( query("family/family_name", me) != "华山派"
             && query("family/family_name", me) != "华山剑宗" )
        {
                command("say 走开！非华山的弟子我一概不教。");
                return -1;
        }

        if (me->query_skill("lonely-sword", 1) > 120)
        {
                if( query_temp("feng_has_told", me) )
                {
                        command("say 你自己好好练吧！");
                        return -1;
                }

                command("pat"+query("id", me));
                command("say 这套剑法要靠自己勤练，以后你自己多加钻研吧！");
                set_temp("feng_has_told", 1, me);
                return -1;
        }

        if( query_temp("learnd_lonely_sword", me) )
                return 0;

        set_temp("learnd_lonely_sword", 1, me);
        command("say 很好，很好。这门剑法重在剑意，不在招式。");
        command("say 倘若学习，切不可拘泥于形式。");
        return 0;
}

void attempt_apprentice(object ob)
{
        if( query("family/family_name", ob) != "华山派"
             && query("family/family_name", ob) != "华山剑宗" )
        {
                command("say 走开！非华山的弟子我一概不见。");
                return;
        }

        command("say 我不收徒，你另请高明吧。");
}

int check_skill(string skill)
{
        if (skill != "sword" && skill != "lonely-sword")
        {
                command("say 我只懂剑法，你想学就学，不想学就算了。");
                return -1;
        }
        return 1;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("can_learn/feng/lonely-sword", ob) )
                return check_skill(skill);

        if( query("can_learn/feng/sword", ob )
           && skill != "lonely-sword")
        {
                if (skill == "sword")
                        return 1;

                command("say 教你点基本剑法是看得起你，少跟我罗嗦！");
                return -1;
        }

        if( query_temp("have_asked_feng", ob) )
        {
                command("say 还不快滚！");
                return -1;
        }

        if( query("family/family_name", ob) != "华山派"
             && query("family/family_name", ob) != "华山剑宗" )
        {
                command("say 走开！非华山的弟子我一概不教。");
                return -1;
        }

        if( query("character", ob) == "阴险奸诈"
            || query("character", ob) == "心狠手辣" )
        {
                command("heng");
                command("say 不想死的就给我滚！");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        if( query("character", ob) == "光明磊落" )
        {
                command("hmm");
                command("say 你天性不坏，可是却不适合练习这套剑法。");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        /*
        if( query("shen", ob)<-10000
            || query("shen", ob)>10000
            || query("weiwang", ob)>10000 )
        {
                command("say 我风某从不和成名人士打交道，你走吧。");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }
        */

        if( query("int", ob)<26 )
        {
                command("sneer");
                command("say 你这个呆头鹅，忒笨了点，走吧。");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        if( query("int", ob)<28 )
        {
                command("look "+query("id", ob));
                command("say 你倒是不算笨，有点小聪明，不过…还是差得远啊。");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        if (ob->query_skill("sword", 1) < 100)
        {
                command("say 你人虽不错，可是你的对剑法的理解也未免太差了。");
                return -1;
        }

        if( query("int", ob)<34 )
        {
                if (skill == "sword")
                {
                        command("say 好吧，我就教你一点关于剑法的知识。");
                        set("can_learn/feng/sword", 1, ob);
                        return 1;
                }

                if (skill != "lonely-sword")
                {
                        command("say 我只会剑法，要学其它的本事找别的师傅去吧！");
                        return -1;
                }

                command("sigh");
                command("say 你这人算是聪明，可离独孤九剑还是差之甚远。");
                return -1;
        }

        if (check_skill(skill) == -1)
                return -1;

        message_sort(HIW "\n$N" HIW "点了点头，对$n" HIW "说道：“甚"
                     "好，甚好。虽然我不收徒，不过看你天资实在不错，"
                     "就传你一点剑法吧。这套独孤九剑共分为九势，我先"
                     "传你总诀式，其他破剑式、破刀式、破枪式、破鞭式"
                     "、破索式、破掌式、破箭式、破气式我随后一一分解"
                     "与你听。”\n" NOR, this_object(), ob);

        tell_object(ob, HIC "\n风清扬同意传授你「独孤九剑」。\n" NOR);
        set("can_learn/feng/lonely-sword", 1, ob);
        ob->improve_skill("martial-cognize", 1500000);
        return 1;
}

int accept_ask(object me, string topic)
{
        string *learned, *try_to;
        mixed pot;

        pot=query("potential", me);
        pot = atoi(pot);

        if (! topic || undefinedp(try_to = po_type[topic]))
                return 0;

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                command("say 你会独孤九剑么？就向我问这个？");
                return 1;
        }

        learned=query("can_perform/dugu-jiujian", me);
        if (! arrayp(learned))
                learned = ({ });
        if (member_array(try_to[0], learned) != -1)
        {
                command("say 你不是已经学会" + topic + "了么？");
                return 1;
        }

        command("say 好吧，" + topic + "的要诀你要听仔细了。");
        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                tell_object(me, HIG "你听了风清扬的教导，颇觉迷茫，看"
                                "来是潜能不够了。\n" NOR);
                return 1;
        }

        addn("learned_points", 10, me);
        if (random(2))
        {
                write(HIY "你听了风清扬的教导，颇有心得。\n" NOR);
                return 1;
        }

        learned -= try_to;
        learned += try_to;
        set("can_perform/dugu-jiujian", learned, me);
        tell_object(me, HIC "你学会了独孤九剑之「" + topic + "」。\n");
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("lonely-sword"))
                me->improve_skill("lonely-sword", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        return 1;
}

string ask_skill()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "你会独孤九剑么？就向我问这个？";
        }

        if( query("can_perform/lonely-sword/pozhong", me) )
                return "你不是已经学会了吗？";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌机先，出奇制胜。\n"+
                HIG "你听了风清扬的教导，颇觉迷茫，看"
                        "来是潜能不够了。" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌机先，出奇制胜。\n"HIY "你听了风清扬的教导，颇有心得。" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/po",            //pfm的代码
                                        "name"          : "破众",               //pfm的名称
                                        "sk1"           : "lonely-sword",       //主要的武功的id
                                        "lv1"           : 80,                   //主要的武功的等级
                                        "sk2"           : "sword",              //需要武功sk2的id
                                        "lv2"           : 50,                   //需要武功sk2 的等级
                                        "neili"         : 50,                   //需要基本内功
                                        "free"          : 1,
                                        "gongxian"      : 300,
                                        ]));
}
string ask_skill1()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "你会独孤九剑么？就向我问这个？";
        }

        if( query("can_perform/lonely-sword/xiao", me) )
                return "你不是已经学会了吗？";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌机先，出奇制胜。\n"+
                HIG "你听了风清扬的教导，颇觉迷茫，看"
                        "来是潜能不够了。" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌机先，出奇制胜。\n"HIY "你听了风清扬的教导，颇有心得。" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/xiao",            //pfm的代码
                                        "name"          : "笑沧海",             //pfm的名称
                                        "sk1"           : "lonely-sword",       //主要的武功的id
                                        "lv1"           : 180,                   //主要的武功的等级
                                        "sk2"           : "sword",              //需要武功sk2的id
                                        "lv2"           : 180,                   //需要武功sk2 的等级
                                        "free"          : 1,
                                        "neili"         : 200,                   //需要基本内功
                                        ]));
}

string ask_skill2()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "你会独孤九剑么？就向我问这个？";
        }

        if( query("can_perform/lonely-sword/hun", me) )
                return "你不是已经学会了吗？";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌机先，出奇制胜。\n"+
                HIG "你听了风清扬的教导，颇觉迷茫，看"
                        "来是潜能不够了。" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌机先，出奇制胜。\n"HIY "你听了风清扬的教导，颇有心得。" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/hun",            //pfm的代码
                                        "name"          : "剑魂",             //pfm的名称
                                        "sk1"           : "lonely-sword",       //主要的武功的id
                                        "lv1"           : 1000,                   //主要的武功的等级
                                        "sk2"           : "sword",              //需要武功sk2的id
                                        "lv2"           : 1000,                   //需要武功sk2 的等级
                                        "neili"         : 2000,                   //需要基本内功
                                        "reborn"        : 1,           
                                        "free"          : 1,
                                        "gongxian"      : 3000,
                                        ]));
}

string ask_skill3()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "你会独孤九剑么？就向我问这个？";
        }

        if( query("can_perform/lonely-sword/jian", me) )
                return "你不是已经学会了吗？";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌机先，出奇制胜。\n"+
                HIG "你听了风清扬的教导，颇觉迷茫，看"
                        "来是潜能不够了。" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌机先，出奇制胜。\n"HIY "你听了风清扬的教导，颇有心得。" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/jian",            //pfm的代码
                                        "name"          : "剑心通明",             //pfm的名称
                                        "sk1"           : "lonely-sword",       //主要的武功的id
                                        "lv1"           : 1000,                   //主要的武功的等级
                                        "sk2"           : "sword",              //需要武功sk2的id
                                        "lv2"           : 1000,                   //需要武功sk2 的等级
                                        "neili"         : 2000,                   //需要基本内功
                                        "reborn"        : 1,           
                                        "free"          : 1,
                                        "gongxian"      : 3000,
                                        ]));
}
