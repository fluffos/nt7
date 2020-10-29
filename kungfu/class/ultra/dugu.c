// dugu.c 独孤求败

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

#define ULTRA_OPINION   "宗师"
#define OPINION_TYPE    HIY "兵器功夫" NOR
#define MY_OPINION      "weapon"

#define QUESTGOODS_D(x) ("/quest/questdg/quest/questgoods" + x)
#define QUESTDG_D(x)    ("/quest/questdg/quest/questdg" + x)
#define DGMSG_D         ("/quest/questdg/dugu-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
int give_quest();
int give_up();
void npc_dest(object npc);
void destory(object ob);
string time_period(int timep);
mixed ask_maze();

string  *my_opinions = ({ "sword", "blade", "staff", "hammer",
                          "club", "whip",  "dagger", });

string *dg_msg = ({
        "独孤求败笑呵呵的说：“",
        "独孤求败慢慢踱着方步道：“",
        "独孤求败低头想了想，说道：“",
        "独孤求败满脸期待的说道：“",
        "独孤求败微笑着道：“",
});

string* qin_msg1 = ({
        "动物是人们的朋友，就算name严重影响了生态环境，关起来也就可以了，",
        "我听说name过多的繁殖，影响了当地的生态，不过还是不应该随便杀动物，",
        "难道name也会给人类带来麻烦？真是稀奇，我倒是想看看它，",
        "我这里的花园养着很多的动物，就是没有name，",
        "在空闲的时候，看看动物的生活能够放松情绪，name其实挺可爱的，",
        "南海神尼是一个很喜欢动物的人，尤其是name，用来送给她做礼物最好不过，",
        "江湖上打打杀杀的，少不了让name也遭受无辜连累，我有心保护它，",
});

string* qin_msg2 = ({
        "你去把它带到这里来吧。”",
        "去找到它，把它带来。”",
        "你能把它带我这里来么？”",
        "你就辛苦一趟去帮我把它找来吧。”",
        "把它弄来给我。”",
});

// 该头文件必须在这里嵌入
#include <ultra.h>

void check_weapon();

void create()
{
        set_name("独孤求败", ({ "dugu qiubai", "dugu" }) );
        set("title", HIC "大宗师" NOR);
        set("gender", "男性");
        set("age", 48);
        set("long",
"这是一个普普通通的老者，一袭粗布衣裳，\n"
"颏下一缕白须，神情详和。目光转动之间，\n"
"隐隐流露出一丝王者之气。\n");
        set("attitude", "peaceful");
        set("no_get", 1);
        set("str", 38);
        set("int", 39);
        set("con", 32);
        set("dex", 33);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "独孤九剑" : "我把天下武功的变化归结在九剑之中，算不得是剑法，若拘\n"
                             "泥于形势就无法理解其中奥妙。\n"
                             "独孤九剑真正的精妙之处不在于其剑招，而是其" HIY "剑意" NOR + CYN "。",
                "剑意"     : "剑招乃其形，而剑意乃其神，吾花费毕生经历于华山一山洞\n"
                             HIY"空室" NOR + CYN"中参悟出独孤九剑之剑意，并将其笔录在「" HIY "独孤九剑残"
                             "本" NOR + CYN"」" NOR + CYN "内。\n" NOR,
                "空室"     : "穿过我身后的山洞就会发现一个峭壁，我将残本藏于其间的\n"
                             "山洞内，并请高手匠人设计出六把不同锁将其锁住，每把琐"
                             "连接着一个开锁\n的机关，机关藏于六个不同的石室内，须得"
                             "将所有" HIY "锁" NOR + CYN "打开方能进入空室。\n" NOR,
                "锁"       : "年深日久，开锁的方法我已不记得了。我只记得如果石门\n"
                             "上的六把火炬都点燃了，石门上的锁也就开了。\n",
                "无招胜有招" : "那就是独孤九剑的最高境界！\n",
                "独孤九剑残本" : "如果你能拿来给话我到是可以把独孤九剑中的精妙之处传\n授于你。\n",
                "评价"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武学修养" : "武学修养(martial-cognize)乃武术大义，可谓是以一通通百通！",
                "任务"     : "独孤求败叹了口气，道：“如今江湖上危机四伏，我正道人士还有很多事情要去做啊！”\n",
                "maze"     : (: ask_maze :),
                "迷宫"     : (: ask_maze :),
        ]));

        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("blade", 500);
        set_skill("staff", 500);
        set_skill("hammer", 500);
        set_skill("club", 500);
        set_skill("whip", 500);
        set_skill("dagger", 500);
        set_skill("throwing", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("never-defeated", 500);
        set_skill("martial-cognize", 500);

        map_skill("sword", "never-defeated");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "never-defeated");
        map_skill("dodge", "never-defeated");
        map_skill("force", "never-defeated");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: check_weapon :),
        }) );

        set("rank_info/self", "在下");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield();

        set("startroom", "/d/huashan/shandong");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        delete_temp("want_opinion", me);
        if (ultrap(me))
        {
                message_vision(CYN "$N" CYN "微微一笑，对$n"
                               CYN "点了点头。\n" NOR,
                               this_object(), me);
        }

        add_action("give_quest", "quest");
        add_action("give_up", "giveup");
}

mixed ask_maze()
{
        object me;
        object ob;
        mapping quest;
        mapping maze;

        me = this_player();
        ob = this_object();
        quest=query("quest_dg", me);

        if (!quest)
                return "你并没有接我的任务，找我问迷宫的事情干什么？";

        if ( undefinedp(quest["maze"]) )
                return "你接的任务跟迷宫无关啊，凑什么热闹呢？";

        /* 取消老的迷宫
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "你的任务看来是无法完成啦，那个迷宫据说已经消失了。";

        message_vision("$N对$n点头道：“既然你已经准备好要去那里，那就祝你一切顺利！”\n", ob, me);
        FUBEN_D->enter_fuben(me, "ultra");

        return 1;
}

void check_weapon()
{
        if (objectp(query_temp("weapon")))
                return;

/*
        message_vision(CYN "$N" CYN "长叹一口气道：我$N"
                       CYN "多年来兵器还从未离过手，罢！罢"
                       "了！我去也！\n" NOR, this_object());
        destruct(this_object());
*/
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if( query("combat_exp", me)<200000 )
                return "呵呵，你这点武功还谈什么评价？";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "哈哈，你兵器方面的修为已经称得上是宗师了！咱们要不要过过招？";

        if (is_fighting(me))
                return "哈哈，废什么话，打赢了我，你自己给自己评价吧！";

        if (me->is_fighting())
                return "你等会儿吧！待我赶走他们。";

        if (objectp(ob = query_temp("opinion")))
        {
                if (ob == me)
                {
                        command("say 你着什么急？不要烦我。");
                        return 1;
                }

                message_vision(CYN "$N" CYN "正在沉思，没有回答$n"
                               CYN "，只是摆了摆手。\n" NOR,
                               this_object(), me);
                return 1;
        }

        switch(query_temp("want_opinion/dugu", me) )
        {
        case 0:
                command("look"+query("id", me));
                command("say 好吧，你用兵器攻我一招，我看看你的水平如何。");
                break;
        case 1:
                command("say 不是说让你来一招我看看吗？");
                break;
        case 2:
                message_vision(CYN "$N" CYN "皱眉对$n" CYN
                               "道：“我看你这人是够罗嗦的。”\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say 给我闭上你的嘴！");
                return 1;
        }

        addn_temp("want_opinion/dugu", 1, me);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;
        mapping action;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

        lvl += me->query_skill(sp, 1);
        action=SKILL_D(sp)->query_action(me,query_temp("weapon", me));
        if (mapp(action))
                lvl += (action["force"] + action["parry"] + action["dodge"] - 250) / 10;
        return lvl;
}

void do_congration(object me)
{
        command("chat 这位" + RANK_D->query_respect(me) +
                "可要善自珍重，须知强中更有强中手。");
}

int accept_hit(object me)
{
        if( query_temp("want_hit/dugu", me) >= 2 )
        {
                command("heng");
                command("say 事不过三，你要找死那就去死吧！");
                kill_ob(me);
                return 1;
        }

        command("shake");
        command("say 这位" + RANK_D->query_respect(me) + "，"
                "练武之人切忌贸然挑衅。");
        addn_temp("want_hit/dugu", 1, me);
        return 0;
}

int accept_fight(object me)
{
        object weapon;

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
        {
                message_vision(CYN "$N" CYN "大喜，对$n" CYN
                               "道：“很好，近年我还没有和宗"
                               "师高手过过招，来吧！”\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( !query_temp("want_opinion/dugu", me) )
        {
                command("say 平白无故动什么手？");
                return 0;
        }

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                command("say 没兵器你动什么手？");
                return 0;
        }

        if( query("qi", me)*100/query("max_qi", me)<80 ||
            query("jing", me)*100/query("max_jing", me)<80 )
        {
                command("say 你现在状态不佳，等休息好了再说吧！");
                return 0;
        }

        command("nod");
        COMBAT_D->do_attack(me, this_object(), weapon);
        COMBAT_D->do_attack(this_object(), me, query_temp("weapon"));

        if( query("qi", me) <= 0 )
        {
                message_vision(CYN "\n$N" CYN "摇摇头对$n" CYN
                               "道：“你现在的武功还差得远，连"
                               "我一招都接不住！”\n" NOR,
                               this_object(), me);
                return notify_fail("看来要好好的修炼功夫了。\n");
        }

        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        delete_temp("want_opinion", me);
        message_vision(CYN "\n$N" CYN "点点头道：“好了，你先等"
                       "会儿，待我想想。”\n" NOR,
                       this_object(), me);
        return notify_fail("看来不能心急，还得等一会儿。\n");
}

int accept_kill(object me)
{
        if( query("combat_exp", me)<500000000 )
        {
                message_vision(CYN "$N" CYN "大怒道：“无名小辈捣"
                               "什么乱？给我滚！”说罢一掌把$n" CYN
                               "劈倒在地。\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say 很好！近年还真没有遇到什么敢和我较量的高手！");
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if( query("character", me) != "狡黠多变" &&
            query("character", me) != "国士无双" )
        {
                command("say 我看你的性格不够机智灵活，不适宜"
                        "向我学习武功，还是算了吧！");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say 想学我的不败神功？你还不够资格，"
                        "等你成了大宗师再说吧！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say 够了！我就教你到这里吧，武功还是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if (skill != "never-defeated")
                return 1;

        if( query_temp("can_learn/dugu/never-defeated", me) )
                return 1;

/*
        set_temp("can_learn/dugu/never-defeated", 1, me);
        command("nod");
        command("say 我可以教你我多年领悟出来的不败神功，可是"
                "你能不能学，还要看你的机缘了！");
        return 1;
*/
        return -1;
}

void unconcious()
{
        /*
        message("vision", "\n"HIR + name() + "脸色一变，吐了一口鲜"
                "血，身形一闪，消逝不见。\n\n" NOR, environment());
        command("chat 罢！罢！罢！在下去也！");
        destruct(this_object());
        */
        full_self();
        return;
}

void die()
{
        /*
        message("vision", "\n"HIR + name() + "大叫一声，狂吐了一口鲜"
                "血，身形一闪，就此不见。\n\n" NOR, environment());
        command("chat 在下去也！");
        destruct(this_object());
        */
        full_self();
        return;
}

int give_quest()
{
        mapping questtemp, questgoods, questdg;
        mapping skills, robot_quest;
        string msg, dest, error, dgmsg, place;
        object ob, npc, thing;
        int time, bonus, level, i, lev, lev1;
        int exp;
        int all_lvl, lvl;
        object maze_target;
        object maze_object;

        ob = this_player();
        exp=query("combat_exp", ob);

        if( (query("character", ob) != "光明磊落") &&
            (query("character", ob) != "国士无双") &&
            (query("character", ob) != "狡黠多变") )
        {
                write("独孤求败看了你一眼，道：“你本性杀气太重，跟我等相处日久必然格格不入，你还是另找他人去吧！”\n");
                return 1;
        }
        /*
        if( query("shen", ob)<0 )
        {
                write("独孤求败对你冷冷道：“道不同，不相为谋，你还是请便罢！”\n");
                return 1;
        }
        */
        if (exp < 500000)
        {
                write("独孤求败看了看你，轻抚白须，道：“江湖险恶，你还是先练好基本功吧。”\n");
                return 1;
        }

        if( mapp(query("quest_dg", ob)) )
        {
                write("独孤求败拍了拍你的肩膀，呵呵笑道：“不要急，先将手头的做完再说。”\n");
                return 1;
        }

        if( mapp(query("quest_hs", ob)) )
        {
                write("独孤求败拍了拍你的肩膀，呵呵笑道：“黄裳那老家伙给你任务了？先去把它完成吧！”\n");
                return 1;
        }


        if( !wizardp(ob) && (time()-query("questdg_giveup_time", ob))<30 )
        {
                write("不要急，慢一点嘛。\n");
                return 1;
        }

        /*if( query("questdg_times", ob)<3
         || (query("questdg_times", ob)>5 && random(20) == 5) )
        */
        if( wizardp(ob) )
        {
                X_QuestD->query_quest(ob, this_object());
                return 1;
        }

        if (random(4) + 1)
        {
                // 以下给任务
                if(exp <= 600000)        level = 0;
                else if(exp <= 900000)   level = 1;
                else if(exp <= 1200000)  level = 2;
                else if(exp <= 1800000)  level = 3;
                else if(exp <= 2500000)  level = 4-random(3);
                else if(exp <= 3200000)  level = 5-random(3);
                else if(exp <= 4000000)  level =6-random(3);
                else
                {
                        if(random(15)==0||(exp>10000000&&random(10)==0))
                                level = 8;
                        else level = 7 - random(3);
                }
                if (level != 8)
                {
                        if (exp > 4000000)
                        {
                                all_lvl = 0;
                                lvl = random(28) + 1;
                                for (i = 1;i < 8;i ++)
                                {
                                        all_lvl += i;
                                        if (lvl > all_lvl - i && lvl <= all_lvl)
                                        {
                                                lvl = i;
                                                break;
                                        }
                                }
                        } else lvl = level;
                        while(1)
                        {
                                questtemp = QUESTDG_D(lvl)->query_questdg(ob);
                                if (questtemp["type"] == "杀" || questtemp["type"] == "擒")
                                {
                                    if( !get_object(questtemp["object"]) || !get_object(questtemp["object"])->is_master() )
                                        break;
                                } else
                                        break;
                        }
                }
                if (level == 8)
                {
                        npc = new(CLASS_D("generate") + "/player_npc.c");
                        FUBEN_D->clear_fuben("ultra",query("id", ob));
                        maze_object=get_object("/f/ultra/"+query("id", ob)+"/maze");
                        maze_object->set_maze_boss(npc);
                        //maze_target = MAZE_D->create_maze(npc);
                        maze_target=get_object("/f/ultra/"+query("id", ob)+"/maze/exit");
                        npc->move(maze_target);
                        /*
                        NPC_D->place_npc(npc,query("combat_exp", ob)<500000?({"大理一带","终南山","关外","西域"}):
                                              query("combat_exp", ob)<800000?({"大理一带","终南山","西域"}):({"大理一带","西域"}));
                        */
                        npc->set_from_me(ob, 1);
                        addn_temp("apply/attack", npc->query_skill("force")/3, npc);
                        addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
                        addn_temp("apply/parry", npc->query_skill("force")/3, npc);
                        addn_temp("apply/damage", 200+random(100), npc);
                        addn_temp("apply/unarmed_damage", 200+random(100), npc);
                        addn_temp("apply/armor", 200+random(300), npc);
                        set_temp("quester",query("id",  ob), npc);
                        set("auto_perform", 1, npc);
                        /*
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);

                        place=query("place", npc);
                        */
                        set("shen", -20000, npc);
                        /*
                        msg = "独孤求败面色凝重道：“" + npc->name(1) +
                              "居然又重现江湖，你速去除了这一害，\n此人可能会在" + place +
                              "附近，慢了就找不到了。”\n",
                        */
                        msg = "独孤求败面色凝重道：“"+npc->name(1)+
                              "居然又重现江湖，你速去除了这一害，\n此人喜欢躲在迷宫(maze)中，慢了就找不到了。”\n",

                        questtemp = ([
                                //"maze" : maze_target->query("maze/mazename"),
                                "maze" : maze_object,
                                "name" : npc->name(1),
                                "id":query("id", npc),
                                "bonus": (200+random(51)),
                                "type" : "杀",
                                "level" : level,
                                //"chinese_w" : place,
                                //"where" : npc->query("startroom"),
                                "where": maze_target,
                                "dgmsg" : msg,
                                "object" : base_name(npc),
                        ]);
                        tell_object(ob, questtemp["dgmsg"] + "\n");
                        set("quest_dg", questtemp, ob);

                        return 1;
                }
                else
                {
                        switch(questtemp["type"])
                        {
                        case "杀":
                                if( query("race", get_object(questtemp["object"])) != "人类" )
                                {
                                        questtemp["type"] = "擒";
                                        msg = dg_msg[random(sizeof(dg_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",questtemp["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                                        break;
                                }
                                if(undefinedp(msg = questtemp["msg1"])||msg==""||random(2))
                                {
                                        if(questtemp["race"])
                                                msg=DGMSG_D->query_dgmsg("宰",questtemp["name"]);
                                        else
                                                msg=DGMSG_D->query_dgmsg("杀",questtemp["name"]);
                                }
                                break;
                        case "寻":
                                if(undefinedp(msg = questtemp["msg"])||msg==""||random(2))
                                        msg=DGMSG_D->query_dgmsg("寻",questtemp["name"]);
                                break;
                        case "擒":
                                if( query("race", get_object(questtemp["object"])) != "人类" )
                                {
                                        msg = dg_msg[random(sizeof(dg_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",questtemp["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                                        break;
                                }
                                if(undefinedp(msg = questtemp["msg2"])||msg==""||random(2))
                                {
                                        if(questtemp["race"])
                                                msg=DGMSG_D->query_dgmsg("捉",questtemp["name"]);
                                        else
                                                msg=DGMSG_D->query_dgmsg("擒",questtemp["name"]);
                                }
                                break;
                        case "送":
                                npc = new(CLASS_D("generate") + "/dg_receiver.c");
                                FUBEN_D->clear_fuben("ultra",query("id", ob));
                                maze_object=get_object("/f/ultra/"+query("id", ob)+"/maze");
                                maze_object->set_maze_boss(npc);
                                maze_target=get_object("/f/ultra/"+query("id", ob)+"/maze/exit");
                                //maze_target = MAZE_D->create_maze(npc);
                                npc->move(maze_target);
                                /*
                                NPC_D->place_npc(npc,query("combat_exp", ob)<500000?({"大理一带","终南山","关外","西域"}):
                                                      query("combat_exp", ob)<800000?({"大理一带","终南山","西域"}):({"大理一带","西域"}));
                                */
                                NPC_D->set_from_me(npc, ob, 100);
                                set_temp("quester",query("id",  ob), npc);
                                /*
                                NPC_D->random_move(npc);
                                NPC_D->random_move(npc);
                                NPC_D->random_move(npc);
                                */
                                //place = npc->query("place");
                                thing = new(questtemp["object"]);
                                if (! objectp(thing))
                                        log_file("static/Non_things", sprintf("无法找到物品 %s\n", questtemp["object"]));
                                set("send_to",query("id",  npc), thing);
                                set("send_from", query("id"), thing);
                                set("send_from_name", query("name"), thing);
                                msg = dg_msg[random(5)]+"麻烦你帮我将"+thing->name(1)+"送至"+npc->name(1)+"处，"
                                                "他现在正在迷宫中，误了时间他可能就离开了。";
                                /*
                                msg = dg_msg[random(5)]+"麻烦你帮我将"+thing->name(1)+"送至"+npc->name(1)+"处，"
                                                "他现在正在"+place+"，误了时间他可能就离开了。";
                                */
                                if (!thing->move(ob))
                                {
                                        thing->move(environment(this_object()));
                                        message_vision("独孤求败将$N轻轻放在地上。\n",thing);
                                } else message_vision("独孤求败将$N交给$n。\n",thing,ob);
                                break;
                        }
                        questdg=([
                                "name":questtemp["name"],
                                "type":questtemp["type"],
                                "bonus":questtemp["bonus"],
                                "object":questtemp["object"],
                                "dgmsg":msg,
                        ]);
                }
        }
/*
        if (questdg["type"] == "杀" && (random(6) == 2 || wizardp(ob)))
        {
                robot_quest = ANTI_ROBOT->get_question();
                msg = "独孤求败郑重说道：“我刚将我们组织的口令更改了一下，你去通知一下" + questdg["name"] + NOR"，新口令是：\n";
                msg += robot_quest["question"];
                msg += "你只需要将口令用"HIR"普通的数字形式"NOR"传送过去就行了，传送的指令是：whisper。\n";
                questdg["type"]   = "传";
                questdg["dgmsg"]  = msg;
                questdg["answer"] = robot_quest["answer"];
        }
*/

        tell_object(ob, questdg["dgmsg"]+"\n");
        questdg["level"]=level;
        if (questdg["type"] == "送")
        {
                questdg["obj"] = thing;
                questdg["send_to"]=query("send_to", thing);
                if (maze_object)
                        questdg["maze"] = maze_object;
        }
        set("quest_dg", questdg, ob);
        return 1;
}


int accept_object(object who, object ob)
{
        int exp, pot,level,bonus,time,times;
        int i,quest_count,mar,score,weiwang,all_quest_dg;
        int total_count;
        mapping questdg;
        string dest,msg;
        object gold,obj;
        mixed special = 0;
        mixed money = 0;
        mapping my;

        if (base_name(ob) == "/clone/lonely/book/dugubook")
        {
                if (who->query_skill("lonely-sword", 1) < 340)
                {
                        command("shake");
                        command("say 可惜，可惜！你独孤九剑还不够熟练，还无法领悟独孤九剑的精妙之处！");
                        destruct(ob);
                        return 1;
                }

                if( query("lonely-sword/nothing", who) )
                {
                        command("nod");
                        command("say 你已经领悟了独孤九剑之精髓，下去好好练习吧！");
                        destruct(ob);
                        return 1;
                }

                // 开始传授独孤九剑之无招
                command("nod");
                command("say 不错，不错！既然如此，我就将独孤九剑之精髓传授于你。");
                command("say 独孤九剑最精妙之处已经不是招式，而是一种" HIY "境界" NOR + CYN "！");
                command("say 独孤九剑讲究后发制人，不拘泥于任何招式，随心而发，随心而收，达到一\n"
                        "种" HIY "无招胜有招" NOR + CYN "的境界！");
                command("say 明白了？");

                set("lonely-sword/nothing", 1, who);

                if (who->can_improve_skill("sword"))
                        who->improve_skill("sword", 1500000);
                if (who->can_improve_skill("sword"))
                        who->improve_skill("sword", 1500000);
                if (who->can_improve_skill("sword"))
                        who->improve_skill("sword", 1500000);
                if (who->can_improve_skill("lonely-sword"))
                        who->improve_skill("lonely-sword", 1500000);
                if (who->can_improve_skill("lonely-sword"))
                        who->improve_skill("lonely-sword", 1500000);
                if (who->can_improve_skill("lonely-sword"))
                        who->improve_skill("lonely-sword", 1500000);
                who->improve_skill("martial-cognize", 1500000);
                who->improve_skill("martial-cognize", 1500000);
                who->improve_skill("martial-cognize", 1500000);

                tell_object(who, HIG "你学会了独孤九剑之「无招」。\n" NOR);

                destruct(ob);
                return 1;
        }

        if( !(questdg=query("quest_dg", who)) )
        {
                tell_object(who,"独孤求败看了看你，似乎不知道你是什么意思。\n");
                return notify_fail("独孤求败淡淡一笑，道：“我可不缺什么东西。”\n");
        }

        if( query("money_id", ob) )
        {
                if (ob->value() < 1000000)
                {
                        tell_object(who,"独孤求败对你语重心长的说：你拿这么点钱来干什么呢？我又不是缺钱花。\n");
                        return notify_fail("独孤求败摇摇头：如果给个100两黄金，或许我就消除了你的任务。\n");
                }
                delete("quest_dg", who);
                tell_object(who,"独孤求败盯着" + ob->name(1) + "注视良久，叹气道：那你这个任务不做就算了吧。\n");
                destruct(ob);
                return 1;
        }

        if(questdg["type"] != "寻" && questdg["type"] != "擒" && questdg["type"] != "送")
        {
                tell_object(who,"独孤求败看了看你，似乎不知道你是什么意思。\n");
                return notify_fail("独孤求败淡淡一笑，道：“我可不缺什么东西。”\n");
        }

        if( ob->name(1) != questdg["name"] || userp(ob))
        {
                tell_object(who,"独孤求败叹了口气，道：这并不是我想要的。\n");
                return notify_fail("独孤求败看着你，道：“你是不是再去找找看啊？”\n");
        }

        if(questdg["type"]=="送")
        {
                if( !ob->is_receipt() || query("reply_to", ob) != query("id", this_object()) )
                {
                        write("独孤求败接过来一看，惊讶的说：“我不是叫你帮我送东西了么，你是不是记错了？”\n");
                        return 0;
                }
                if( query("reply_by", ob) != questdg["send_to"] )
                {
                        write("独孤求败接过来一看，生气的说：“这张回执是谁给你的？别想来糊弄我！”\n");
                        return 0;
                }
                if( query("receive_from", ob) != query("id", who) )
                {
                        write("独孤求败接过来一看，生气的说：“这张回执是你自己得到的么？别想来糊弄我！”\n");
                        return 0;
                }
        }

        if( userp(ob) || query("user", ob) ||
            ob->is_item_make() ||
            ob->query_save_file())
        {
                write("独孤求败大怒道：“好你个小子，竟然想蒙骗本宗师！来人！把他给我抓起来！”\n");
                who->get_into_prison(this_object(), 0, 30);
                log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(独孤任务)制造%s(%s)(%s)作弊\n",query("name", who),
                query("id", who),ob->name(),query("id", ob),ctime(time())));
                return 1;
        }

        // message_vision("$N将$n交给独孤求败。\n",who,ob); 与give信息重复
        tell_object(who,"独孤求败点头微笑，其意颇为嘉许，道：“不错！不错！”\n");
        delete("quest_dg", who);
        if( ob->is_character() && query("startroom", ob) )
        {
                my = ob->query_entire_dbase();
                my["jing"]   = my["eff_jing"]   = my["max_jing"];
                my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                my["qi"]     = my["eff_qi"]     = my["max_qi"];
                my["neili"]  = my["max_neili"];
                if(! living(ob))
                        ob->revive();
                ob->clear_condition();
                ob->remove_all_killer();
                if (! ob->return_home(query("startroom", ob)) )
                        ob->move(query("startroom", ob));
        } else destruct(ob);

        level = questdg["level"]+1;
        if( (i=query("questdg_times", who))<8 )
                i = 15-i;
        else i = 1;

        exp = level*105 + questdg["bonus"]*3;
        exp+=query("questdg_times", who);
        exp += random(exp/2);
        exp /= i;

        if (questdg["type"] == "擒")
        exp += exp/5;
        pot = exp/(2+random(2));
        score = random(exp/20);
        weiwang = random(exp/15);

        if( query("questdg_times", who)+1>200 )
               mar=exp/5+random(query("questdg_times", who));
        else mar = 20 + random(20);
        
        exp = exp*3;
        pot = pot*3;
        mar = mar*3;
        
        if (mar > 1000) mar = 1000;

        if(wizardp(who)||!random(10))
        {
                i=(exp/60+1);
                if(i>30) i=30;
                gold=new("/clone/money/gold");
                gold->set_amount(i);
                tell_object(who,"接着说道：“整日行走江湖，手头有点紧吧？！喏，拿点黄金做盘缠吧！”\n"
                        HIW"\n你被奖励了 "+i+" 两黄金。\n");
                if(!gold->move(who))
                {
                        message_vision("但是$N身上东西太重，黄金一下子掉到了地上。\n",who);
                        gold->move(environment());
                }
                GIFT_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                      "weiwang" : weiwang, "score" : score, "percent" : 100 ]), 1);
        }
        else
                GIFT_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar, "percent" : 100,
                                      "weiwang" : weiwang, "score" : score ]), 1);

        // who->add("questdg_times",1);
        addn("total_hatred", -5, who);
        if( query("total_hatred", who)<0)set("total_hatred", 0, who);


        quest_count=query("questdg_times", who)+1;
        total_count = quest_count % 500;
        if (total_count == 50)
        {
                msg = "$N呵呵笑了两声道：“你还可以，连着"+chinese_number(quest_count)+
                      "次任务都完成的漂漂亮亮，继续努力！”\n";
                special = 1;
        } else
        if (total_count == 100)
        {
                msg = "$N笑的合不拢嘴，看了你一眼道：“有志气！"+chinese_number(quest_count)+
                      "次任务干得干净利索！”\n";
                special = "/clone/gift/puti-zi";
        } else
        if (total_count == 150)
        {
                msg = "$N叹道：“真是长江后浪推前浪，想不到你接连"+chinese_number(quest_count)+
                      "次任务都无一疏漏，不易，不易！”\n";
                money = 1;
        } else
        if (total_count == 200)
        {
                msg = "$N叹道：“真是长江后浪推前浪，想不到你接连"+chinese_number(quest_count)+
                      "次任务都无一疏漏，不易，不易！”\n";
                money = 1;
        } else
        if (total_count == 250)
        {
                msg = "$N叹道：“真是长江后浪推前浪，想不到你接连"+chinese_number(quest_count)+
                      "次任务都无一疏漏，不易，不易！”\n";
                money = 1;
        } else

        if (total_count == 300)
        {
                msg = "$N叹道：“真是长江后浪推前浪，想不到你接连"+chinese_number(quest_count)+
                      "次任务都无一疏漏，不易，不易！”\n";
                special = "/clone/gift/tianxiang";
        } else
        if (total_count == 350)
        {
                msg = "$N吓了一跳：“看来你真的很适合学武，竟接连"+chinese_number(quest_count)+
                      "次任务都无一疏漏，不易，不易！”\n";
                special = "/clone/gift/tianxiang";
        } else
        if (total_count == 400)
        {
                msg = "$N叹道：“真是一个武学天才啊，想不到你接连"+chinese_number(quest_count)+
                      "次任务都无一疏漏，不易，不易！”\n";
                special = "/clone/gift/jiuzhuan";
        } else
        if (total_count == 450)
        {
                msg = "$N大声叫起来：“天才！真是天才，真有人连续"+chinese_number(quest_count)+
                      "次任务都无一疏漏，不易，不易！”\n";
                special = "/clone/gift/jiuzhuan";
        } else
        if (total_count == 0)
        {
                msg = "$N深深叹了口气，道：“没想到你连着"+chinese_number(quest_count)+
                      "次任务无一失手，看来以后就是你们这些人挑大梁啦！”\n";
                special = "/clone/gift/jiuzhuan";
#ifdef DB_SAVE
                if( MEMBER_D->is_valid_member(query("id", who)) )
                {

                        if( query("special_skill/sophistry", who) )
                        {
                        if (quest_count >= 5000)
                                        quest_count = 0;
                        } else {
                        if (quest_count >= 2000)
                                        quest_count = 0;
                        }
                } else {
#endif
                        if (quest_count >= 1000)
                                quest_count = 0;
#ifdef DB_SAVE
                }
#endif
        } else
        if ((total_count % 10) == 0)
        {
                msg = "$N呵呵笑着：“你表现很不错啊，居然连着" +
                      chinese_number(quest_count) +
                      "次都没有失手，别忙着练，慢慢来。”\n";
        }

        set("questdg_times", quest_count, who);

        if (special)
        {
                // message_vision(msg, this_object(), who);
                GIFT_D->special_bonus(this_object(), who, special);
        }
        if (money)
        {
                // message_vision(msg, this_object(), who);
                QUEST_D->money_bonus(this_object(), who, money);
        }

        // 记录完成任务的次数（不要求连续），如果满1000次则奖励玛瑙残片
        all_quest_dg=query("all_quest_dg", who);
        if (!all_quest_dg) all_quest_dg = 0;
        all_quest_dg += 1;
        if (all_quest_dg == 1000)
        {
                obj = new("/clone/tessera/mdiamond.c");
                tell_object(who,this_object()->name() + "又对你点了点头：你已经从我这里接了一千个任务，我这里正好\n" +
                        "有个"+query("name", obj)+"，就奖给你了！\n");
                if (!obj->move(who))
                        obj->move(environment());
                set("all_quest_dg", 0, who);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D->add_bunch_fame(who, 20 + random(5));
        }else set("all_quest_dg", all_quest_dg, who);
        return -1;
}

int give_up()
{
        object ob,obj,room;
        mapping questdg;

        ob = this_player();

        if( mapp(questdg=query("quest_dg", ob)) )
        {
                write("你满脸羞惭，请求独孤求败取消自己的任务。\n");
                /*
                if (questdg["type"] == "传")
                {
                        message_vision("$N惊讶地对$n笑笑：『传口令，这个是很简单的任务啊！不要着急，回头再好好想想，努力把它完成！\n",this_object(),ob);
                        return 1;
                }
                */
                write("独孤求败和颜悦色地拍拍你的脑袋，道：“没关系，要继续努力啊！”\n");
                if(questdg["type"] == "送")
                {
                        if( query("questdg_times", ob)>0 )
                                addn("questdg_times", -1, ob);
                }
                else if(questdg["type"] == "杀"&&questdg["level"] == 8)    //by llm
                {
                        set("questdg_times", 0, ob);
                }
                else
                        set("questdg_times", 0, ob);

                if ( stringp(questdg["maze"]) )
                {
                        //MAZE_D->remove_maze(questdg["maze"]);
                        FUBEN_D->clear_fuben("ultra",query("id", ob));
                }

        }
                /*
                if(questdg["type"] == "送")
                {
                        if(objectp(obj = questdg["obj"]))
                        {
                                if(obj->is_character())
                                        message_vision("$N一跃而起，跑得无影无踪了。\n",obj);
                                obj->move(environment(ob));
                                destruct(obj);
                                if( query("questdg_times", ob)>0 )
                                        addn("questdg_times", -1, ob);
                        }
                }
                else
                if(questdg["type"] == "杀"&&questdg["level"] == 8)    //by llm
                {
                        if(!(room = find_object(questdg["where"])) )
                                room = load_object(questdg["where"]);

                        if(objectp(obj = present(questdg["id"],room))
                                &&obj->is_character()
                                &&!userp(obj))
                        {
                                message_vision("$N哼了一声，转身走开了。\n",obj);
                                obj->move("/d/wizard/wizard_room");
                                destruct(obj);
                        }
                        set("questdg_times", 0, ob);
                }
                else
                        set("questdg_times", 0, ob);
        }
        */
        else
                write("独孤求败和颜悦色地看着你，道：“没关系，你现在根本就没有任务啊！”\n");
        delete("quest_dg", ob);
        set("questdg_giveup_time", time(), ob);
        return 1;
}

string time_period(int timep)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";
        return time;
}

void destory(object ob)
{
        if(!ob)
                return;
        if(ob->is_character())
                message_vision("$N一跃而起，跑得无影无踪了。\n",ob);
        ob->move("/d/wizard/wizard_room");
        destruct(ob);
        return ;
}

void npc_dest(object npc)
{
        if(!npc) return;
        if( npc->is_fighting() && query_temp("wait_times", npc)<4 )
        {
                addn_temp("wait_times", 1, npc);//4次机会
                call_out("npc_dest",60,npc);     //再等一分钟
                return;
        }
        if(npc->is_character())
                message_vision("$N重重地哼了一声：“看来都是胆小鬼”，转身一晃，已不见了身影。\n",npc);
        npc->move("/d/wizard/wizard_room");
        destruct(npc);
        return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "天地绝灭" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/juemie",
                           "name"    : "天地绝灭",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "天打雷劈" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/lei",
                           "name"    : "天打雷劈",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "破字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/po",
                           "name"    : "破字诀",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "天花乱坠" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/tianhua",
                           "name"    : "天花乱坠",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "晴空万里" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/wanli",
                           "name"    : "晴空万里",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "御策诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/yuce",
                           "name"    : "御策诀",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "throwing"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
