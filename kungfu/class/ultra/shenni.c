// shenni 南海神尼

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;


#define ULTRA_OPINION   "宗师"
#define OPINION_TYPE    HIY "内家功夫" NOR
#define MY_OPINION      "force"

#define QUEST_SN_D(x)   ("/quest/questsn/quest/questsn" + x)
#define QUEST_WUGOOD_D  ("/quest/questsj/quest_sj")
#define SNMSG_D         ("/quest/questsn/quest/shenni-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
int give_quest();
int give_up();
void destory(object ob);
string time_period(int timep);
mixed ask_maze();

string* sn_msg = ({
        "南海神尼微笑着说：“",
        "南海神尼闭着眼睛冥思片刻道：“",
        "南海神尼低头想了想，说道：“",
        "南海神尼拍了拍手，说道：“",
        "南海神尼微微笑了笑道：“",
});

string* qin_msg1 = ({
        "动物是人们的朋友，就算name严重影响了生态环境，关起来也就可以了，",
        "我听说name过多的繁殖，影响了当地的生态，不过还是不应该随便杀动物，",
        "难道name也会给人类带来麻烦？真是稀奇，我到是想看看它，",
        "我这里的花园养着很多的动物，就是没有name，",
        "在空闲的时候，看看动物的生活能够放松情绪，name其实挺可爱的，",
        "独孤求败是一个很喜欢动物的人，尤其是name，用来送给他做礼物最好不过，",
        "江湖上打打杀杀的，少不了让name也遭受无辜连累，我有心保护它，",
});

string* qin_msg2 = ({
        "你去把它带到这里来吧。”",
        "去找到它，把它带来。”",
        "你能把它带我这里来么？”",
        "你就辛苦一趟去帮我把它找来吧。”",
        "把它弄来给我。”",
});

string  *my_opinions = ({ "force" });

// 该头文件必须在这里嵌入
#include <ultra.h>

void create()
{
        set_name("南海神尼", ({ "nanhai shenni", "shenni", "nanhai" }) );
        set("title", HIG "大宗师" NOR);
        set("gender", "女性");
        set("age", 91);
        set("long", "这是一位青衫老尼，看不出有什么不同。\n");
        set("attitude", "peaceful");
        set("class", "bonze");
        set("no_get", 1);
        set("str", 30);
        set("int", 37);
        set("con", 39);
        set("dex", 33);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 70);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "弹指神通" : "那是我碧海神功关于指法方面的变化，当年我到东海，曾经传授给一人。",
                "评价"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武学修养" : "好好提高自己的武学修养(martial-cognize)，到时候什么武功都如小儿科！",
                "任务" : "本性凶狠但是立身正派的人，可以在我这里领任务(quest)。\n",
                "迷宫"      : (: ask_maze :),
                "maze"      : (: ask_maze :),
        ]));

        set_skill("strike", 500);
        set_skill("finger", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("staff", 500);
        set_skill("bluesea-force", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 220);

        map_skill("parry", "bluesea-force");
        map_skill("force", "bluesea-force");
        map_skill("dodge", "bluesea-force");
        map_skill("finger", "bluesea-force");
        map_skill("strike", "bluesea-force");
        map_skill("staff", "bluesea-force");

        prepare_skill("finger", "bluesea-force");
        prepare_skill("strike", "bluesea-force");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "本座");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhubang")->wield();

        set("startroom", "/d/xiakedao/zhuwu2");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        delete_temp("want_opinion", me);
        if (ultrap(me))
                message_vision("$N眉角微微一动。\n", this_object(), me);
        add_action("give_quest", "quest");
        add_action("give_up","giveup");
}

mixed ask_maze()
{
        object me;
        object ob;
        mapping quest;
        mapping maze;

        me = this_player();
        ob = this_object();
        quest=query("quest_sn", me);

        if (!quest)
                return "你并没有接我的任务，找我问迷宫的事情干什么？";

        if ( undefinedp(quest["maze"]) )
                return "你接的任务跟迷宫无关啊，凑什么热闹呢？";
        /*
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "你的任务看来是无法完成啦，那个迷宫据说已经消失了。";

        message_vision("$N对$n点头道：“既然你已经准备好要去那里，那就祝你一切顺利！”\n", ob, me);
        //me->move(maze["entry"]);
        FUBEN_D->enter_fuben(me, "ultra");

        return 1;
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if( query("combat_exp", me)<200000 )
                return "哼！你这点武功也出来丢人现眼？";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "不必了，你内功方面的修为已经称得上是宗师了！要是和贫尼过上几招也不错。";

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

                message_vision("$N颇为恼怒的对$n道：“没看我正忙着吗？”\n",
                               this_object(), me);
                return 1;
        }

        switch(query_temp("want_opinion/shenni", me) )
        {
        case 0:
                command("say 好吧，咱们过一招，比拚一下内力。");
                break;
        case 1:
                command("say 你准备好没有？好了就来吧。");
                break;
        case 2:
                message_vision(CYN "$N" CYN "皱眉对$n" CYN
                               "道：“我看你这人是够罗嗦的。”\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say 快给我闭上你的鸟嘴！");
                return 1;
        }

        addn_temp("want_opinion/shenni", 1, me);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

        lvl += me->query_skill(sp, 1);
        if( query("max_neili", me)>4000)lvl+=20;
        return lvl;
}

void do_congration(object me)
{
        command("chat 不错，不错，真是不错。");
}

int accept_hit(object me)
{
        command("heng");
        command("say 好你个" + RANK_D->query_rude(me) + "，你找死找到这来了！");
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        object weapon;

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
        {
                message_vision("$N对$n道：“很好，你也算是宗师高手了，"
                               "来吧！咱们比划一下！”\n",
                               this_object(), me);
                return 1;
        }

        if( !query_temp("want_opinion/shenni", me) )
        {
                command("say 你干什么要和我动手？");
                return 0;
        }

        command("look "+query("id", me));

        COMBAT_D->do_attack(this_object(), me, 0);

        if( query("qi", me) <= 0 )
        {
                message_vision("\n$N摇摇头对$n道：“你现在的武功"
                               "还差得远，连我一招都接不住！”\n",
                               this_object(), me);
                return notify_fail("看来要好好的修炼功夫了。\n");
        }

        message_combatd("$N右掌伸出，正和$n手掌相对，两人同时运起内力，"
                       "不一会儿只见二人头上生起腾腾雾气。\n忽然$N手掌"
                       "一撤、收回功力，没有一点阻滞，不禁让$n大为愕然。\n",
                       this_object(), me);
        if( query("neili", me)<3000 )
        {
                message_vision("$N摇摇头对$n道：“适才你内力不足，我难"
                               "以衡量，待你将内力修炼好了再来吧！”\n",
                               this_object(), me);
                return notify_fail("看来还是回去锻炼一下内力吧！\n");
        }
        set("neili", 0, me);


        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        delete_temp("want_opinion", me);
        message_vision("\n$N一摆手道：“好了，待我想想。”\n",
                       this_object(), me);
        return notify_fail("看来不能心急，还得等一会儿。\n");
}

int accept_kill(object me)
{
        if( query("combat_exp", me)<500000000 )
        {
                message_vision("$N大怒道：“无名小辈捣什么"
                               "乱？给我滚！”说罢一掌把$n劈倒在地。\n",
                               this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say 很好！近年还真没有遇到什么敢和我较量的高手！");
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if( query("character", me) != "心狠手辣" && query("character", me) != "国士无双" )
        {
                command("say 你这人生性不够毒辣，下不了狠心，"
                        "我没有兴趣教你！");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say 想学我的碧海神功？你还不够资格，"
                        "等你成了大宗师再说吧！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say 够了！我就教你到这里吧，武功还是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if (skill != "bluesea-force")
                return 1;

        if( query_temp("can_learn/shenni/bluesea-force", me) )
                return 1;

/*
        set_temp("can_learn/dugu/bluesea-force", 1, me);
        command("nod");
        command("say 不错，我教你我的绝学碧海神功，能不能学，"
                "就看你的造化了！");
        return 1;
*/
        return -1;
}

void unconcious()
{
        /*
        message("vision", "\n"HIR + name() + "脸色一变，吐了一口鲜"
                "血，身形一闪，消逝不见。\n\n" NOR, environment());
        command("chat 罢！罢！罢！贫尼去也！");
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
        command("chat 贫尼去也！");
        destruct(this_object());
        */
        full_self();
        return;
}

int give_quest()
{
    mapping quest,qgood,skills,robot_quest;
    object me,target,thing,npc,the_ob;
    int i, giveup,tag,want,lev,lev1,time;
    int exp;
    int lvl,all_lvl;
    string msg,*sname,place,the_race;
    object maze_target;
    object maze_object;

    me = this_player();
    exp=query("combat_exp", me);

    if( (query("character", me) != "阴险奸诈") && 
            (query("character", me) != "国士无双") && 
            (query("character", me) != "心狠手辣") )
    {
        write("南海神尼摇头道：你天性忠实厚道，恐怕接我任务会太过于心慈手软，还是另找别人要任务吧。\n");
        return 1;
    }
    /*
    if( !(query("shen", me)>0) )
    {
        write("南海神尼看着你只是摇头：“行走江湖，立身要正！虽然我讲究以杀止杀，但是你邪气太重，还是算了吧！”\n");
        return 1;
    }
    */
    if(exp < 500000)
    {
        write("南海神尼微笑着拍了拍你的脑袋：以你现在的经验，接我任务实在太过危险，好好去历练历练，回头再来找我。\n");
        return 1;
    }


    if( quest=query("quest_sn", me) )
    {
        write("南海神尼呵呵笑着说：心急可是喝不了热粥啊，不要着急，慢慢来。\n");
        return 1;
    }

    if( mapp(query("quest_kh", me)) )
    {
        write("南海神尼微微一怔说：葵花太监不是给了你任务了么？要不你还是先完成手头的任务吧。\n");
        return 1;
    }


    giveup=query_temp("sn_giveup", me);
    if( (time()-query("questsn_giveup_time", me))<20+giveup*2 && !wizardp(me) )
    {
        write("南海神尼笑着对你说道：“怎么完不成任务这么不顺利？不要着急，先好好想想原因在哪里。\n");
        return 1;
    }

/*
    if( query("questsn_times", me)<3
         || (query("questsn_times", me)>5 && random(20) == 5) )
    {
        X_QuestD->query_quest(me, this_object());
        return 1;
    }
*/

    quest = ([]);
    // 以下给任务
    if(exp <= 600000)        tag = 0;
    else if(exp <= 900000)   tag = 1;
    else if(exp <= 1200000)  tag = 2;
    else if(exp <= 1800000)  tag = 3;
    else if(exp <= 2500000)  tag = 4-random(3);
    else if(exp <= 3200000)  tag = 5-random(3);
    else if(exp <= 4000000)  tag = 6-random(3);
    else
    {
        if(random(15)==0||(exp>10000000&&random(10)==0))
            tag=8;
        else tag=7-random(3);
    }

    i=query("questsn_times", me);
    if((i > 20 && random(20)==18) || wizardp(me))
    {
        qgood = QUEST_WUGOOD_D->query_good();
        msg = qgood["msg"+random(4)];
        want = random(qgood["max_num"] - qgood["min_num"] + 1) + qgood["min_num"];
        msg = YEL"南海神尼呵呵大笑，高兴的说道：“你的办事能力真不赖！\n"+msg
            +"\n你想法弄一批"+qgood["name"]+"来，大约要 "+want+" "+qgood["unit"]+"，有多少可以先交多少。去罢！”\n"NOR;
        write(msg);
        quest = ([
                   "id"         : qgood["id"],
                   "name"       : qgood["name"],
                   "msg"        : msg,
                   "want"       : want,
                   "type"       : "收",
                   "check_file" : qgood["check_file"],
                   "level"      : tag,
                   "bonus"      : 0,
                   "all_bonus"  : 0,
                ]),
        set("quest_sn", quest, me);
        return 1;
    }

    if(tag==8)
    {
        npc = new(CLASS_D("generate") + "/player_npc.c");
        FUBEN_D->clear_fuben("ultra",query("id", me));
        maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
        maze_object->set_maze_boss(npc);
        //maze_target = MAZE_D->create_maze(npc);
        maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
        npc->move(maze_target);
        npc->set_from_me(me,1);
        addn_temp("apply/attack", npc->query_skill("force")/3, npc);
        addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
        addn_temp("apply/parry", npc->query_skill("force")/3, npc);
        addn_temp("apply/damage", 200+random(100), npc);
        addn_temp("apply/unarmed_damage", 200+random(100), npc);
        addn_temp("apply/armor", 200+random(300), npc);
        set_temp("quester",query("id",  me), npc);
        set("auto_perform", 5, npc);

        set("shen", -query("combat_exp", npc)/2000, npc);
        msg="南海神尼正容对你说：“"+npc->name(1)+
            "这个恶棍多次危害武林，听说他最近躲在一个迷宫中，你去除掉他吧！”\n";

        quest = ([
            "maze" : maze_object,
            "name" : npc->name(1),
            "id":query("id", npc),
            "bonus": (200+random(51)),
            "type" : "杀",
            "level": 8,
            "where": maze_target,
            "msg":   msg,
            "object": base_name(npc),
        ]);
        tell_object(me, quest["msg"]+"\n");
        set("quest_sn", quest, me);

        return 1;
    }
    else
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
            } else lvl = tag;
            while(1)
            {
                quest = QUEST_SN_D(lvl)->query_quest();
                if (quest["type"] == "杀" || quest["type"] == "擒")
                {
                    if (! get_object(quest["object"])->is_master())
                    break;
                } else
                    break;
            }

/*
    if(undefinedp(quest["msg"]) || quest["msg"] == "")
*/
    switch(quest["type"])
    {
        case "擒":
                msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                break;
        case "杀":
                if( query("race", get_object(quest["object"])) != "人类" )
                {
                        quest["type"] = "擒";
                        msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                        break;
                } else msg=SNMSG_D->query_snmsg("杀",quest["name"]);
                break;
        case "寻":
                msg=SNMSG_D->query_snmsg("寻",quest["name"]);
                break;
        case "送":
                npc = new(CLASS_D("generate") + "/sn_receiver.c");
                FUBEN_D->clear_fuben("ultra",query("id", me));
                maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
                maze_object->set_maze_boss(npc);
                maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
                //maze_target = MAZE_D->create_maze(npc);
                npc->move(maze_target);
                NPC_D->set_from_me(npc, me, 100);
                set_temp("quester",query("id",  me), npc);
                thing = new(quest["object"]);
                set("send_to",query("id",  npc), thing);
                set("send_from", query("id"), thing);
                set("send_from_name", query("name"), thing);
                msg = sn_msg[random(5)]+"你看能否帮我将"+thing->name(1)+"送至"+npc->name(1)+"处，"
                                        "他现在正在一个迷宫中，赶紧去，不然误了时间他可能就不在了。";
                if (!thing->move(me))
                {
                    thing->move(environment());
                    message_vision("南海神尼将$N轻轻放在地上。\n",thing);
                } else message_vision("南海神尼将$N交给$n。\n",thing,me);
                quest["thing"] = thing;
                quest["send_to"]=query("send_to", thing);
                quest["maze"] = maze_object;
                break;
        }
    }
    quest["msg"] = msg;
    quest["level"] = tag;

/*
    if (quest["type"] == "杀" && (random(6) == 3 || wizardp(me)))
    {
        robot_quest = ANTI_ROBOT->get_question();
        msg = "南海神尼微笑着说道：“我刚将武林同盟的口令更改了一下，你去通知一下" + quest["name"] + NOR"，新口令是：\n";
        msg += robot_quest["question"];
        msg += "你只需要将口令用"HIR"普通的数字形式"NOR"传送过去就行了，传送的指令是：whisper。\n";
        quest["type"]   = "传";
        quest["msg"]  = msg;
        quest["answer"] = robot_quest["answer"];
    }
*/

    set("quest_sn", quest, me);
    if(stringp(quest["msg"])&&quest["msg"]!="")
                write(YEL""+quest["msg"]+"\n"NOR);
    else
    {
                write(YEL""+msg+"\n"NOR);
                set("quest_sn/msg", msg, me);
    }
    return 1;
}

int accept_object(object me, object ob)
{
    int rank,exp,pot,score,times, i,tag,all_quest_sn, bonus;
    mapping quest;
    object gold,who,obj;
    string msg;
    int mar,weiwang,shen,quest_count;
    int total_count;
    mixed special = 0;
    mixed money = 0;

    who = this_object();

    if( (query("character", me) != "阴险奸诈") && (query("character", me) != "心狠手辣") && query("character", me) != "国士无双" && !(query("shen", me)>0) )
    {
        write("南海神尼惊讶的道：“你是谁？给我这个东西干什么？”\n");
        return 0;
    }
    else if( !(quest=query("quest_sn", me)) )
    {
        write("南海神尼呵呵笑道：“我知道你想孝敬我，但是可以靠实际行动嘛，东西你还是自己留着吧。”\n");
        return 0;
    }

    if( query("money_id", ob) )
    {
           if (ob->value() < 1000000)
           {
                   tell_object(me,"南海神尼呵呵一笑：我不缺钱花啊，这点钱，你自己留着买东西吃吧。\n");
                   return notify_fail("南海神尼轻轻说道：如果给我100两黄金，我就取消了你的任务。\n");
           }
           delete("quest_sn", me);
           tell_object(me,"南海神尼随手发下" + ob->name(1) + "，轻轻对你说：那你这个任务不做就算了吧。\n");
           destruct(ob);
           return 1;
    }

    if(quest["type"]!="寻"&&quest["type"]!="收"&&quest["type"]!="送"&&quest["type"]!="擒")
    {
        write("南海神尼微笑道：“我没有叫你去找东西呀，东西你收回。”\n");
        return 0;
    }

    if (userp(ob) ||
        ob->is_item_make() ||
        ob->query_save_file())
    {
        write("南海神尼大怒道：“好你个小子，竟然想蒙骗本副盟主！来人！把他给我抓起来！”\n");
        me->get_into_prison(this_object(), 0, 30);
        log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(神尼任务)制造%s(%s)(%s)作弊\n",query("name", me),
             query("id", me),ob->name(),query("id", ob),ctime(time())));
        return 1;
    }

    if ( quest["type"] == "送" )
    {
        if( !ob->is_receipt() || query("reply_to", ob) != query("id", who) )
        {
            write("南海神尼接过来一看，皱眉道：“给我这玩艺干什么？”\n");
            return 0;
        }
        if( query("reply_by", ob) != quest["send_to"] )
        {
            write("南海神尼接过来一看，皱眉道：“这张回执是谁给你的？别想来糊弄我！”\n");
            return 0;
        }
        if( query("receive_from", ob) != query("id", me) )
        {
            write("南海神尼接过来一看，皱眉道：“这张回执是你自己得到的么？别想来糊弄我！”\n");
            return 0;
        }
    } else if ( quest["type"] == "收" )
    {
        switch( quest["id"] )
        {
            case "HEAD_OBJ":
            case "ARMOR_OBJ":
            case "CLOTH_OBJ":
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("南海神尼接过来一看，皱眉道：“给我这玩艺干什么？”\n");
                    return 0;
                }

                if( !mapp(query("armor_prop", ob)) || 
                     !stringp(query("armor_type", ob)) )
                {
                    write("南海神尼接过来一看，皱眉道：“给我这玩艺干什么？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
            case "SWORD_OBJ":
            case "BLADE_OBJ":
            case "HAMMER_OBJ":
            case "STAFF_OBJ":
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("南海神尼接过来一看，皱眉道：“给我这玩艺干什么？”\n");
                    return 0;
                }

                if( !mapp(query("weapon_prop", ob)) )
                {
                    write("南海神尼接过来一看，皱眉道：“给我这玩艺干什么？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
            default :
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("南海神尼接过来一看，皱眉道：“给我这玩艺干什么？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
        }
    } else if ( ob->name(1) != quest["name"] )
    {
        write("南海神尼说道：“这不是我想要的。”\n");
        return 0;
    }

//    message_vision("$N将$n交给南海神尼。\n",me,ob);与give信息重复haiyan
    times=query("questsn_times", me);//连续次数
    tag=query("quest_sn/level", me)+1;//任务等级
    if( (i=query("questsn_times", me))<15)i=15-i;
    else i = 1;

    exp = tag*80 + quest["bonus"]*3;
        exp += times;
    exp += random(exp/2);
    exp = exp/i;

    if (tag > 4 && i > 5)
        exp /= 2;

    if (quest["type"]=="收")
    {
        exp = quest["bonus"]*(tag + 1);
        exp += random(exp/2);
    }

    pot = exp/(2+random(2));

    score = random(exp/20);
    weiwang = random(exp/15);

    if (times + 1 > 200)
         mar = exp/5 + random(times);
    else mar = 20 + random(20);

    exp = exp*3;
    pot = pot*3;
    mar = mar*3;
        
    if (mar > 1000) mar = 1000;

    if(quest["type"]=="收")
    {
        if((int)quest["want"]>(quest["ok"]+1))
        {
            addn("quest_sn/ok", 1, me);
            write("南海神尼接过来高兴的说：“我要的就是这个，第 "+quest["ok"]+" 了，太好了，还有 "+(quest["want"]-quest["ok"])+" 个，继续努力！”\n");
            score /= 3;
            exp /= 2;
            pot /= 2;
            mar /= 2;
            weiwang /= 2;
            QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                  "weiwang" : weiwang, "score" : score]), 1);
            addn("quest_sn/all_bonus", exp, me);
            destruct(ob);
            return 1;
        }
        exp += quest["all_bonus"]/2;
        pot = exp/(2+random(2));
        weiwang = random(exp/15);
        mar = mar*2;
        mar += mar/4 * quest["want"];
        score = score;
    }
    write("南海神尼接过来开心的笑着说：“不错呀！你这次任务完成得很好！”\n");
    destruct(ob);
    if(!random(10))
    {
        i=(exp/60+1);
        if(i>30) i=30;
        gold=new("/clone/money/gold");
        gold->set_amount(i);
        tell_object(me,"然后取出一锭黄金给你：“行走江湖，身上总要带点钱，我这里有些金子，给你去用吧！”\n"
                       HIW"\n你被奖励了 "+i+" 两黄金。\n");
        if(!gold->move(me))
        {
            message_vision("但是$N身上东西太重，黄金一下子从手中滑到了地上。\n",me);
            gold->move(environment());
        }
        GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                             "weiwang" : weiwang, "score" : score, "percent" : 100 ]), 1);
    }
    else GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar, "percent" : 100,
                              "weiwang" : weiwang, "score" : score ]), 1);

    /*
    if ( times < 1 )
        set("questsn_times", 1, me);
    else
        addn("questsn_times", 1, me);
    */
   set_temp("sn_giveup", 0, me);

   addn("total_hatred", -5, me);
   if( query("total_hatred", me)<0)set("total_hatred", 0, me);

   quest_count=query("questsn_times", me)+1;
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
       if( MEMBER_D->is_valid_member(query("id", me)) )
        {
                if( query("special_skill/sophistry", me) )
                {
                       if (quest_count >= 5000)
                               quest_count = 0;
                } else {
                       if (quest_count >= 2000)
                               quest_count = 0;
                }
        }
       else
        {
#endif
       if (quest_count >= 1000)
           quest_count = 0;
#ifdef DB_SAVE
        }
#endif
   } else
       if ((total_count % 10) == 0)
   {
       msg = "$N微微点头：“干的不错，居然连着"+chinese_number(quest_count)+
       "次都没有失手，接着来，别放松！”\n";
   }

   set("questsn_times", quest_count, me);

   if (special) {
       // message_vision(msg, who, me);
       GIFT_D->special_bonus(who, me, special);
   }
    if (money) {
        // message_vision(msg, who, me);
        QUEST_D->money_bonus(who, me, money);
    }

    delete("quest_sn", me);

   //记录完成任务的次数（不要求连续），如果满1000次则奖励翡翠残片
   all_quest_sn=query("all_quest_sn", me);
   if (!all_quest_sn) all_quest_sn = 0;
   all_quest_sn += 1;
   if (all_quest_sn == 1000)
   {
       obj = new("/clone/tessera/msapphire.c");
       tell_object(me,this_object()->name() + "又对你点了点头：你已经从我这里接了一千个任务，我这里正好\n" +
                   "有个"+query("name", obj)+"，就奖给你了！\n");
       if (!obj->move(me))
               obj->move(environment());
       set("all_quest_sn", 0, me);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D->add_bunch_fame(who, 20 + random(5));
   }else set("all_quest_sn", all_quest_sn, me);

   return 1;
}

int give_up()
{
    object me,ob,obj;
    int giveup,rank;
    mapping quest;

    me = this_player();
    /*
    if( query("quest_sn", me) )
    {
    if( (query("character", me) != "阴险奸诈") && (query("character", me) != "心狠手辣") && !(query("shen", me)>0) )
        return 1;
    }
    */
    if( (quest=query("quest_sn", me)) )
    {
        message_vision("$N委屈的到南海神尼面前哭诉：“我这次任务没有完成，辜负了您老人家的期望......”\n",me);
        /*
        if (quest["type"] == "传")
        {
                message_vision("$N皱着眉头对$n说：『不就是传一个口令么？有那么难？回去仔细想想，这个任务一定要完成！\n",this_object(),me);
                return 1;
        }
        */
        if (quest["type"] == "送")
        {
                if (objectp(ob = quest["thing"]))
                {
                        ob->move("/d/register/prison");
                        destruct(ob);
                }
        }
        if ( stringp(quest["maze"]) )
        {
            //MAZE_D->remove_maze(quest["maze"]);
            FUBEN_D->clear_fuben("ultra",query("id", me));
        }

        message_vision("南海神尼对$N微笑着说:“没关系，下次好好努力就行啦。”\n", me);

        if (quest["type"] == "收")
        {
                delete("quest_sn", me);
                return 1;
        }
        set("questsn_times", 0, me);

        giveup=query_temp("sn_giveup", me);
        if ( giveup < 1 )
            set_temp("sn_giveup", 1, me);
        else if ( giveup < 5 )
            set_temp("sn_giveup", giveup+1, me);
        else set_temp("sn_giveup", 5, me);

        set("questsn_giveup_time", time(), me);

        delete("quest_sn", me);
    }
    else
        write("南海神尼微笑着告诉你：“你目前没有任何任务。”\n");
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
    if(!ob) return;
    if(ob->is_character())
        message_vision("$N突然一溜烟地跑得没影了。\n",ob);
    ob->move("/d/wizard/prison");
    destruct(ob);
    return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "碧海清波" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/bo",
                           "name"    : "碧海清波",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "苦海无边" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/hai",
                           "name"    : "苦海无边",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "finger"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "绝仙决" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/jue",
                           "name"    : "绝仙决",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "戮仙决" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/lu",
                           "name"    : "戮仙决",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "五阴焚灭" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/mie",
                           "name"    : "五阴焚灭",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "strike"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "南海无影杖" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/nan",
                           "name"    : "南海无影杖",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "staff"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "玄黄连环掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/xuan",
                           "name"    : "玄黄连环掌",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "strike"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "斩仙决" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/zhan",
                           "name"    : "斩仙决",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "诛仙决" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/zhu",
                           "name"    : "诛仙决",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
