// huang 黄裳

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

#define ULTRA_OPINION   "宗师"
#define OPINION_TYPE    HIY "拳脚功夫" NOR
#define MY_OPINION      "unarmed"

#define QUEST_HS_D(x)   ("/quest/quesths/quest/quesths" + x)
#define QUEST_WUGOOD_D  ("/quest/questsj/quest_sj")
#define HSMSG_D         ("/quest/quesths/quest/huangshang-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
mixed ask_skill();
int give_quest();
int give_up();
void destory(object ob);
string time_period(int timep);
mixed ask_maze();

string  *my_opinions = ({ "unarmed", "finger",
                          "strike", "cuff", "hand", "claw" });

string* hs_msg = ({
        "黄裳头也不抬地说：“",
        "黄裳翻出一叠档案道：“",
        "黄裳低头想了想，说道：“",
        "黄裳拿着一份公文，说道：“",
        "黄裳微微笑了笑道：“",
});

// 该头文件必须在这里嵌入
#include <ultra.h>

void create()
{
        set_name("黄裳", ({ "huang shang", "huang" }) );
        set("title", HIY "大宗师" NOR);
        set("gender", "男性");
        set("age", 92);
        set("long", "此人气度闲雅，看不出武功高低。\n");
        set("attitude", "peaceful");
        set("no_get", 1);
        set("str", 32);
        set("int", 39);
        set("con", 37);
        set("dex", 32);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "九阴真经" : "想不到当年我随手写的一本武学心得竟成为危害江湖的不祥之物。",
                "评价"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武学修养" : "武学修养(martial-cognize)不到家，还谈什么武功呢？",
                "摄心大法" : (: ask_skill :),
                "任务"     : "天性好，又是负神的话，可以在我这里领任务(quest)。\n",
                "迷宫"      : (: ask_maze :),
                "maze"      : (: ask_maze :),
        ]));

        set_skill("unarmed", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("strike", 500);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("jiuyin-shengong", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 200);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "某家");

        setup();
        carry_object("/clone/cloth/cloth")->wear();

        set("startroom", "/d/dali/lushui");
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
        if( !is_fighting() &&random(5)==0)
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
        add_action("give_quest", "quest");
        add_action("give_up","giveup");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("quest_hs", ob) && query("shen", ob)<0 )
                write("黄裳说道："+query("name", ob)+",你的任务完成得怎么样了？\n");
}

mixed ask_maze()
{
        object me;
        object ob;
        mapping quest;
        mapping maze;

        me = this_player();
        ob = this_object();
        quest=query("quest_hs", me);

        if (!quest)
                return "你并没有接我的任务，瞎嚷嚷什么？";

        if ( undefinedp(quest["maze"]) )
                return "你接的任务跟迷宫无关，好好把你手头的事情做了！";

        /* 取消老的迷宫
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "真是没用！那个迷宫据说都已经消失了！";

        message_vision("$N对$n点头道：“既然你已经准备好要去那里，那切记一定要成功！”\n", ob, me);
        FUBEN_D->enter_fuben(me, "ultra");

        return 1;
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if( query("combat_exp", me)<200000 )
                return "呵呵，你这点武功还谈什么评价？";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "哈哈，你拳脚方面的修为已经称得上是宗师了！咱们要不要过过招？";

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

        switch(query_temp("want_opinion/huang", me) )
        {
        case 0:
                command("look"+query("id", me));
                command("say 好吧，你空手攻我一招，我看看你的水平如何。");
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

        addn_temp("want_opinion/huang", 1, me);
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
        action = SKILL_D(sp)->query_action(me, 0);
        if (mapp(action))
                lvl += (action["force"] + action["attack"] +
                        action["parry"] + action["dodge"] - 150) / 15;
        return lvl;
}

void do_congration(object me)
{
        command("chat 恭喜这位" + RANK_D->query_respect(me) + "，不过武"
                "道永无止境，还望继续努力啊！");
}

int accept_hit(object me)
{
        if( query_temp("want_hit/huang", me) >= 2 )
        {
                command("heng");
                command("say 事不过三，你要找死那就去死吧！");
                kill_ob(me);
                return 1;
        }

        command("shake");
        command("say 这位" + RANK_D->query_respect(me) + "，"
                "练武之人切忌贸然挑衅。");
        addn_temp("want_hit/huang", 1, me);
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

        if( !query_temp("want_opinion/huang", me) )
        {
                command("say 平白无故动什么手？");
                return 0;
        }

        if( objectp(weapon=query_temp("weapon", me)) )
        {
                command("say 把你手中的" + weapon->name() + NOR +
                        CYN "给我放下！" NOR);
                return 0;
        }

        if( query("qi", me)*100/query("max_qi", me)<80 || 
            query("jing", me)*100/query("max_jing", me)<80 )
        {
                command("say 你现在状态不佳，等休息好了再说吧！");
                return 0;
        }

        command("nod");
        COMBAT_D->do_attack(me, this_object(), 0);
        COMBAT_D->do_attack(this_object(), me, 0);

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
        if( query("character", me) != "光明磊落" && 
            query("character", me) != "国士无双" )
        {
                command("say 大丈夫处世，不论善恶行事一定要光"
                        "明磊落，你生性不是这种人。");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say 想学我的九阴神功？你还不够资格，"
                        "等你成了大宗师再说吧！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say 够了！我就教你到这里吧，武功还是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if (skill != "jiuyin-shengong")
                return 1;

        if( query_temp("can_learn/huang/jiuyin-shengong", me) )
                return 1;

/*
        set_temp("can_learn/huang/jiuyin-shengong", 1, me);
        command("nod");
        command("say 很好，我就传你九阴神功吧，可不要忘记做人"
                "的根本！");
        return 1;
*/
        return -1;
}

void unconcious()
{
        /*
        message("vision", "\n"HIR + name() + "脸色一变，吐了一口鲜"
                "血，身形一闪，消逝不见。\n\n" NOR, environment());
        command("chat 罢！罢！罢！老夫去也！");
        destruct(this_object());
        */
        full_self();
        return;
}

mixed ask_skill()
{
        object me;

        me = this_player();

        if( query("can_perform/jiuyin-shengong/xin", me) )
        {
             command("say 你不是已经会了吗？");
             return 1;
        }

        if( !query("can_learn/jiuyin-shengong/xin", me) )
        {
               message_sort(HIM "\n黄裳叹道：“当年我随手写了一本武学心得，名曰「九阴真经」，本欲"
                            "留与后人研究武学之用，不料竟成为危害江湖的不祥之物。如果阁下能将其上、"
                            "下两册收集齐交还与我，我便传你绝招「摄心大法」。\n", me);
               command("tan");

               return "阁下意下如何？";
        }


        if (me->query_skill("jiuyin-shengong", 1) < 240)
        {
               command("say 你九阴神功火候还不够，我还不能传你这招！");
               return 1;
        }
        if (me->query_skill("martial-cognize", 1) < 240)
        {
               command("say 你武学修养不足，还是下去多磨练一下吧！");
               return 1;
        }
        if( !query("can_perform/jiuyin-shengong/shou", me )
            || !query("can_perform/jiuyin-shengong/zhi", me )
            || !query("can_perform/jiuyin-shengong/zhua", me )
            || !query("can_perform/jiuyin-shengong/zhang", me) )
        {
               command("shake");
               command("say 等你将九阴神功其他绝招领悟后再来找我吧！");
               return 1;
        }

        command("nod");
        command("say 很好，很好！");
        command("say 既然这样我就传你摄心大法！");
        message_sort(HIC "\n黄裳将$N" HIC "呼自身旁，对着$N" HIC "耳边小声嘀咕了几句。"
                       "黄裳不时地做出各种奇怪的表情，$N" HIC "边听边看，良久，$N" HIC
                       "一声长啸，胸中疑虑顿然消失，再无困扰 ……\n", me);
        command("haha");

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jiuyin-shengong"))
                me->improve_skill("jiuyin-shengong", 1500000);
        if (me->can_improve_skill("martial-cognize"))
                me->improve_skill("martial-cognize", 1500000);

        tell_object(me, HIG "你学会了「摄心大法」！\n" NOR);
        set("can_perform/jiuyin-shengong/xin", 1, me);
        return 1;
}
void die()
{
        /*
        message("vision", "\n"HIR + name() + "大叫一声，狂吐了一口鲜"
                "血，身形一闪，就此不见。\n\n" NOR, environment());
        command("chat 老夫去也！");
        destruct(this_object());
        */
        full_self();
        return;
}
/*
int accept_object(object me, object ob)
{
        if (base_name(ob) != "/clone/lonely/book/zhenjing1"
          && base_name(ob) != "/clone/lonely/book/zhenjing2")
        {
               command("say 你给我这种东西干什么？");
               return 0;
        }

        if (base_name(ob) == "/clone/lonely/book/zhenjing1")
        {
               command("nod");
               command("say 很好，很好！");
               if( query("give_zhenjing2", me) )
               {
                     command("haha");
                     command("say 既然这样我就传你绝招，你可以随时来问我！");
                     tell_object(me, HIG "黄裳决定传你「摄心大法」。\n" NOR);
                     set("can_learn/jiuyin-shengong/xin", 1, me);
                     delete("give_zhenjing1", me);
                     delete("give_zhenjing2", me);
                     destruct(ob);
                     return 1;
               }
               set("give_zhenjing1", 1, me);
               command("say 还有一本「九阴真经下册」，你尽快找到交还与我！");
               destruct(ob);
               return 1;
        }

        if (base_name(ob) == "/clone/lonely/book/zhenjing2")
        {
               command("nod");
               command("say 很好，很好！");
               if( query("give_zhenjing1", me) )
               {
                     command("haha");
                     command("say 既然这样我就传你绝招，你可以随时来问我！");
                     tell_object(me, HIG "黄裳决定传你「摄心大法」。\n" NOR);
                     set("can_learn/jiuyin-shengong/xin", 1, me);
                     delete("give_zhenjing1", me);
                     delete("give_zhenjing2", me);
                     destruct(ob);
                     return 1;
               }
               set("give_zhenjing2", 1, me);
               command("say 还有一本「九阴真经上册」，你尽快找到交还与我！");
               destruct(ob);
               return 1;
        }

}
*/

int give_quest()
{
    mapping quest,qgood,skills,robot_quest;
    object me,target,thing,npc;
    int i, giveup,tag,want,lev,lev1;
    int exp;
    int all_lvl,lvl;
    string msg,*sname,place;
    object maze_target;
    object maze_object;

    me = this_player();
    exp=query("combat_exp", me);

    if( (query("character", me) != "光明磊落") && 
            (query("character", me) != "国士无双") && 
           (query("character", me) != "狡黠多变") )
    {
        write("黄裳问你：你这种性格的人，来这里干什么？\n");
        return 1;
    }
    /*
    if( !(query("shen", me)<0) )
    {
        write("黄裳看着你只是摇头：“行走江湖，不是光想着做大侠，我讲求的是以杀止杀，你杀性不够，还是算了吧！”\n");
        return 1;
    }
    */
    if (exp < 500000)
    {
        write("黄裳对你说道：以你现在的经验，还需要多多磨练啊。\n");
        return 1;
    }

    if( quest=query("quest_hs", me) )
    {
        write("黄裳对你说：先把你手上的任务完成再说。\n");
        return 1;
    }
    if( mapp(query("quest_dg", me)) )
    {
        write("黄裳对你说：独孤求败的任务你还没完成，莫非想找老夫讨打？\n");
        return 1;
    }

    giveup=query_temp("hs_giveup", me);
    if( (time()-query("quesths_giveup_time", me))<20+giveup*2 )
    {
        write("黄裳对你哼了一声道：“老完不成任务，我对你的表现很不满意，先反省一会儿。\n");
        return 1;
    }

/*
        if( query("quesths_times", me)<3
         || (query("quesths_times", me)>5 && random(20) == 5) )
        {
                X_QuestD->query_quest(me, this_object());
                return 1;
        }
*/
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

    i=query("quesths_times", me);
    if((i > 20 && random(20)==18) || wizardp(me))
    {
        qgood = QUEST_WUGOOD_D->query_good();
        msg = qgood["msg"+random(4)];
        want = random(qgood["max_num"] - qgood["min_num"] + 1) + qgood["min_num"];
        msg = YEL"黄裳微微笑着，赞许地说道：“办事能力不错！\n"+
              msg+"\n"+
              "你想法弄一批"+qgood["name"]+"来，大约要 "+want+" "+qgood["unit"]+"，有多少可以先交多少。去罢！”\n"NOR;
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
        set("quest_hs", quest, me);
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
            /*
            NPC_D->place_npc(npc,query("combat_exp", me)<500000?({"大理一带","终南山","关外","西域"}):
                                  query("combat_exp", me)<800000?({"大理一带","终南山","西域"}):({"大理一带","西域"}));
            */
            npc->set_from_me(me,1);
            addn_temp("apply/attack", npc->query_skill("force")/3, npc);
            addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
            addn_temp("apply/parry", npc->query_skill("force")/3, npc);
            addn_temp("apply/damage", 200+random(100), npc);
            addn_temp("apply/unarmed_damage", 200+random(100), npc);
            addn_temp("apply/armor", 200+random(300), npc);
            set_temp("quester",query("id",  me), npc);
            set("auto_perform", 1, npc);
            /*
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            */
            place=query("place", npc);

            set("shen",query("combat_exp",  npc)/2000, npc);
            msg="黄裳忧心忡忡的说：“"+npc->name(1)+
                "这个假仁假义的无耻之徒多次危害武林，听说他最近躲在迷宫中，你去除掉他吧！”\n";

            quest = ([
                //"maze" : maze_target->query("maze/mazename"),
                "maze" : maze_object,
                "name" : npc->name(1),
                "id":query("id", npc),
                "bonus": (200+random(51)),
                "type" :"杀",
                "level":8,
                //"chinese_w":place,
                //"where":npc->query("startroom"),
                "where": maze_target,
                "msg":msg,
                "object":base_name(npc),
            ]);
            tell_object(me,quest["msg"]+"\n");
            set("quest_hs", quest, me);

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
                quest = QUEST_HS_D(lvl)->query_quesths();
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
        case "杀":
                msg=HSMSG_D->query_hsmsg("杀",quest["name"]);
                break;
        case "寻":
                msg=HSMSG_D->query_hsmsg("寻",quest["name"]);
                break;
        case "征":
                npc = new(CLASS_D("generate") + "/hs_target.c");
                FUBEN_D->clear_fuben("ultra",query("id", me));
                maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
                maze_object->set_maze_boss(npc);
                maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
                //maze_target = MAZE_D->create_maze(npc);
                npc->move(maze_target);
                /*
                NPC_D->place_npc(npc,query("combat_exp", me)<500000?({"大理一带","终南山","关外","西域"}):
                                      query("combat_exp", me)<800000?({"大理一带","终南山","西域"}):({"大理一带","西域"}));
                */
                NPC_D->set_from_me(npc, me, 100);
                set_temp("quester",query("id",  me), npc);
                /*
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                */
                place=query("place", npc);
                msg = hs_msg[random(5)]+npc->name(1)+"去年从武林同盟这里借走不少钱，地方分舵催讨多次不得，"
                        "听说他现在正在迷宫中，你去试试！\n如果也收不到钱，就收了他的"+quest["name"]+"。拿武林令要出示(chushi)一下。";
                thing = new("/quest/quesths/wulin-ling");
                thing->move(me);
                message_vision("黄裳将武林令交给$N。\n",me);
                quest["target"]=query("id", npc);
                break;
        case "送":
                npc = new(CLASS_D("generate") + "/hs_receiver.c");
                FUBEN_D->clear_fuben("ultra",query("id", me));
                maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
                maze_object->set_maze_boss(npc);
                maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
                //maze_target = MAZE_D->create_maze(npc);
                npc->move(maze_target);
                /*
                NPC_D->place_npc(npc,query("combat_exp", me)<500000?({"大理一带","终南山","关外","西域"}):
                                      query("combat_exp", me)<800000?({"大理一带","终南山","西域"}):({"大理一带","西域"}));
                */
                NPC_D->set_from_me(npc, me, 100);
                set_temp("quester",query("id",  me), npc);
                /*
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                */
                place=query("place", npc);
                thing = new(quest["object"]);
                set("send_to",query("id",  npc), thing);
                set("send_from", query("id"), thing);
                set("send_from_name", query("name"), thing);
                msg = hs_msg[random(5)]+"你帮我将"+thing->name(1)+"送至"+npc->name(1)+"处，"
                                        "他现在正在迷宫中，误了时间他可能就离开了。";
                if (!thing->move(me))
                {
                    thing->move(environment());
                    message_vision("黄裳将$N扔在地上。\n",thing);
                } else message_vision("黄裳将$N交给$n。\n",thing,me);
                quest["thing"] = thing;
                quest["send_to"]=query("send_to", thing);
                break;
    }
    }
    quest["msg"] = msg;
    quest["level"] = tag;
/*
    if (quest["type"] == "杀" && random(6) == 3)
    {
        robot_quest = ([]);
        robot_quest = ANTI_ROBOT->get_question();
        msg = "";
        msg += "黄裳郑重说道：“我刚将武林同盟的口令更改了一下，你去通知一下" + quest["name"] + NOR"，新口令是：\n";
        set_temp("test", robot_quest, me);
        msg += robot_quest["question"];
        msg += "你只需要将口令用"HIR"普通的数字形式"NOR"传送过去就行了，传送的指令是：whisper。\n";
        quest["type"]   = "传";
        quest["msg"]  = msg;
        quest["answer"] = robot_quest["answer"];
    }
*/

    if (maze_object)
        quest["maze"] = maze_object;

    set("quest_hs", quest, me);
    write(msg + "\n");
    return 1;
}

int accept_object(object me, object ob)
{
    int rank,exp,pot,score,times,i,tag,all_quest_hs,bonus;
    mapping quest;
    object gold,who,obj;
    string msg;
    int mar,weiwang,shen,quest_count;
    int total_count;
    mixed special = 0;
    mixed money = 0;

    who = this_object();

    if( (query("character", me) != "光明磊落") && (query("character", me) != "狡黠多变") && query("character", me) != "国士无双" && !(query("shen", me)<0) )
    {
        write("黄裳奇道：“你是何人？”\n");
        return 0;
    }
    else if( !(quest=query("quest_hs", me)) )
    {
        write("黄裳说道：“无功不受禄，东西你收回。”\n");
        return 0;
    }

    if( query("money_id", ob) )
    {
                if (ob->value() < 1000000)
           {
                   tell_object(me,"黄裳满脸不悦的对你说：这么一点点钱，能用来干什么？你自己留着买鸡腿用吧！\n");
                   return notify_fail("黄裳抬头望天，缓缓说道：如果给个100两黄金，或许我就消除了你的任务。\n");
           }
           delete("quest_hs", me);
           tell_object(me,"黄裳接过你的" + ob->name(1) + "，微微笑了笑，点头道：那你这个任务不做就算了吧。\n");
           destruct(ob);
           return 1;
    }

    if (quest["type"]!="寻"&&quest["type"]!="征"&&quest["type"]!="收"&&quest["type"]!="送")
    {
        write("黄裳说道：“我没有叫你去找东西，东西你收回。”\n");
        return 0;
    }

    if (userp(ob) ||
        ob->is_item_make() ||
        ob->query_save_file())
    {
        write("黄裳大怒道：“好你个小子，竟然想蒙骗本盟主！来人！把他给我抓起来！”\n");
        me->get_into_prison(this_object(), 0, 30);
        log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(黄裳任务)制造%s(%s)(%s)作弊\n",query("name", me),
             query("id", me),ob->name(),query("id", ob),ctime(time())));
        return 1;
    }

    if ( quest["type"] == "征" )
    {
        if( query_temp("zheng", ob) != query("id", me) )
        {
            write("黄裳接过来，一看怒道：“这哪是你拣来的，还想蒙骗本盟主！走，你的江湖威望降低了！”\n");
            addn("weiwang", -weiwang*(random(5)+4)/4, me);
            if( query("weiwang", me)<0)set("weiwang", 0, me);
            return 0;
        }
    } else if ( quest["type"] == "送" )
    {
        if( !ob->is_receipt() || query("reply_to", ob) != query("id", who) )
        {
            write("黄裳接过来一看，皱眉道：“给我这玩艺干什么？”\n");
            return 0;
        }
        if( query("reply_by", ob) != quest["send_to"] )
        {
            write("黄裳接过来一看，勃然大怒道：“这张回执是谁给你的？别想来糊弄我！”\n");
            return 0;
        }
        if( query("receive_from", ob) != query("id", me) )
        {
            write("黄裳接过来一看，勃然大怒道：“这张回执是你自己得到的么？别想来糊弄我！”\n");
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
                    write("黄裳接过来一看，皱眉道：“给我这玩艺干什么？”\n");
                    return 0;
                }

                if( !mapp(query("armor_prop", ob)) || 
                     !stringp(query("armor_type", ob)) )
                {
                    write("黄裳接过来一看，皱眉道：“给我这玩艺干什么？”\n");
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
                    write("黄裳接过来一看，皱眉道：“给我这玩艺干什么？”\n");
                    return 0;
                }

                if( !mapp(query("weapon_prop", ob)) )
                {
                    write("黄裳接过来一看，皱眉道：“给我这玩艺干什么？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
            default :
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("黄裳接过来一看，皱眉道：“给我这玩艺干什么？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
        }
    } else if ( ob->name(1) != quest["name"] )
    {
        write("黄裳说道：“这不是我想要的。”\n");
        return 0;
    }

//    message_vision("$N将$n交给黄裳。\n",me,ob);与give信息重复haiyan
    times=query("quesths_times", me);//连续次数
    tag=query("quest_hs/level", me)+1;//任务等级
    if( (i=query("quesths_times", me))<15)i=15-i;
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

    if (mar > 1000) mar = 1000;

    if(quest["type"]=="收")
    {
        if((int)quest["want"]>(quest["ok"]+1))
        {
            addn("quest_hs/ok", 1, me);
            write("黄裳接过来点点头说：“第 "+quest["ok"]+" 了，很好，还有 "+(quest["want"]-quest["ok"])+" 个，继续努力！”\n");
            exp /= 2;
            pot /= 2;
            mar /= 2;
            weiwang /= 2;
            score /= 3;
            GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                  "weiwang" : weiwang, "score" : score]), 1);
            addn("quest_hs/all_bonus", exp, me);
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
    write("黄裳接过来说道：“很好！你这次任务完成得不错！”\n");
    destruct(ob);

    if (quest["type"]=="征" && objectp(obj = present("wulin ling", me)))
        destruct(obj);
        
    exp = exp*3;
    pot = pot*3;
    mar = mar*3;
        
    if(!random(10))
    {
        i=(exp/60+1);
        if(i>30) i=30;
        gold=new("/clone/money/gold");
        gold->set_amount(i);
        tell_object(me,"然后取出一锭黄金给你：“这次奖你些金子，下次继续努力！”\n"
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
        set("quesths_times", 1, me);
    else
        addn("quesths_times", 1, me);
    */
        set_temp("hs_giveup", 0, me);

   addn("total_hatred", -5, me);
   if( query("total_hatred", me)<0)set("total_hatred", 0, me);

   quest_count=query("quesths_times", me)+1;
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
        }
        else
        {
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
       msg = "$N微微点头：“干的不错，居然连着" +
       chinese_number(quest_count) +
       "次都没有失手，接着来，别放松！”\n";
   }

   set("quesths_times", quest_count, me);

   if (special) {
       // message_vision(msg, who, me);
       GIFT_D->special_bonus(who, me, special);
   }
    if (money) {
        // message_vision(msg, who, me);
        QUEST_D->money_bonus(who, me, money);
    }

    delete("quest_hs", me);

   //记录完成任务的次数（不要求连续），如果满1000次则奖励水晶残片
   all_quest_hs=query("all_quest_hs", me);
   if (!all_quest_hs) all_quest_hs = 0;
   all_quest_hs += 1;
   if (all_quest_hs == 1000)
   {
       obj = new("/clone/tessera/mtopaz.c");
       tell_object(me,this_object()->name() + "又对你点了点头：你已经从我这里接了一千个任务，我这里正好\n" +
                   "有个"+query("name", obj)+"，就奖给你了！\n");
       if (!obj->move(me))
               obj->move(environment());
       set("all_quest_hs", 0, me);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D ->add_bunch_fame(who, 20 + random(5));
   }else set("all_quest_hs", all_quest_hs, me);
   return 1;
}

int give_up()
{
    object me,ob,obj;
    int giveup,rank;
    mapping quest;

    me = this_player();
    /*
    if( query("quest_hs", me) )
    {
    if( (query("character", me) != "光明磊落") && (query("character", me) != "狡黠多变") && !(query("shen", me)<0) )
        return 1;
    }
    */
    if( (quest=query("quest_hs", me)) )
    {
        message_vision("$N战战兢兢地走到黄裳面前请罪：“小的该死，辜负了盟主的期望......”\n",me);
        /*
        if (quest["type"] == "传")
        {
                message_vision("$N皱着眉头对$n说：『不就是传一个口令么？有那么难？回去仔细想想，这个任务一定要完成！\n",this_object(),me);
                return 1;
        }
        */
        if ( stringp(quest["maze"]) )
        {
                //MAZE_D->remove_maze(quest["maze"]);
                FUBEN_D->clear_fuben("ultra",query("id", me));
        }

        if (quest["type"] == "征")
        {
               if (ob = present("wulin ling",me))
               {
                        ob->move("/d/register/prison");
                        destruct(ob);
               }
        }
        if (quest["type"] == "送")
        {
                if (objectp(ob = quest["thing"]))
                {
                        ob->move("/d/register/prison");
                        destruct(ob);
                }
        }
        message_vision("黄裳对$N叹了一声道: 怎么不动动脑筋？这么简单的事情都做不了。\n", me);

        if (quest["type"] == "收")
        {
                delete("quest_hs", me);
                return 1;
        }
        rank=query("quest_hs/level", me);
        addn("weiwang", -(rank*6+random(rank+4)), me);
        if( query("weiwang", me)<0 )
               set("weiwang", 0, me);
        write("黄裳告诉你：“你的江湖威望降低了！”\n");

        set("quesths_times", 0, me);

        giveup=query_temp("hs_giveup", me);
        if ( giveup < 1 )
            set_temp("hs_giveup", 1, me);
        else if ( giveup < 5 )
            set_temp("hs_giveup", giveup+1, me);
        else set_temp("hs_giveup", 5, me);

        set("quesths_giveup_time", time(), me);

        delete("quest_hs", me);
    }
    else
        write("黄裳告诉你：你目前没有任何任务。\n");
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
    ob->move("/d/wizard/wizard_room");
    destruct(ob);
    return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "九阴神拳" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/quan",
                           "name"    : "九阴神拳",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "cuff"    : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "九阴神手" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/shou",
                           "name"    : "九阴神手",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "hand"    : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "摄心大法" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/xin",
                           "name"    : "摄心大法",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "九阴神掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/zhang",
                           "name"    : "九阴神掌",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "strike"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "九阴神指" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/zhi",
                           "name"    : "九阴神指",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "finger"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "九阴神爪" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/zhua",
                           "name"    : "九阴神爪",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "claw"    : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
