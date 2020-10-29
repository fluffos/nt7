// kuihua 葵花太监

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

#define ULTRA_OPINION   "宗师"
#define OPINION_TYPE    HIY "轻身功夫" NOR
#define MY_OPINION      "dodge"

#define QUESTKILL_D     "/quest/questkh/quest/questkill"
#define QUESTKH_D(x)    ("/quest/questkh/quest/questkh" + x)
#define KHMSG_D         ("/quest/questkh/kuihua-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
int give_quest();
int give_up();
void destory(object ob);
void npc_dest(object npc);
string time_period(int timep);
mixed ask_maze();
string  *my_opinions = ({ "dodge" });

// 该头文件必须在这里嵌入
#include <ultra.h>

void create()
{
        set_name("葵花太监", ({ "kuihua taijian", "kuihua", "taijian" }) );
        set("title", HIR "大宗师" NOR);
        set("gender", "男性");
        set("age", 99);
        set("long", "此人脸型瘦削，满是阴骛，不知是喜是怒。\n");
        set("attitude", "peaceful");
        set("no_get", 1);
        set("str", 31);
        set("int", 39);
        set("con", 34);
        set("dex", 36);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "葵花宝典" : "那是我写的一本关于轻功方面的心得，怎么，你有兴趣？",
                "评价"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武学修养" : "学习深奥武功，没有深厚的武学修养(martial-cognize)，提也休提！",
                "任务"     : "葵花太监低了头，抚摩着手中的玉如意，全神贯注，理都不理。”\n",
                "maze"     : (: ask_maze :),
                "迷宫"     : (: ask_maze :),
        ]));

        set_skill("unarmed", 500);
        set_skill("finger", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("sword", 500);
        set_skill("kuihua-mogong", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 220);

        map_skill("parry", "kuihua-mogong");
        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("finger", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");

        prepare_skill("finger", "kuihua-mogong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "本宫");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/misc/spin")->wield();

        set("startroom", "/d/beijing/shanlu3");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        delete_temp("want_opinion", me);
        if (ultrap(me))
                message_vision(CYN "$N" CYN "扫了$n" CYN
                               "一眼，冷笑一声。\n" NOR,
                               this_object(), me);
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
        quest=query("quest_kh", me);

        if (!quest)
                return "你是不是吃饱了没事干，莫非想去鬼门关逛逛？";

        if ( undefinedp(quest["maze"]) )
                return "你接的任务跟迷宫无关，不该知道的事情不要多问！";

        /*
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "真是该死，那个迷宫据说已经消失，你还有脸来见我？";

        message_vision("$N对$n点头道：“既然你已经准备好要去那里，那就千万别失手！”\n", ob, me);
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
                return "嘿，你这点武功只好抓抓老鼠。";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "嗯，你轻功方面的修为已经称得上是宗师了！要是有兴趣咱们过两招？";

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

                message_vision(CYN "$N" CYN "颇为恼怒的对$n"
                               CYN "道：“没看我正忙着吗？”\n" NOR,
                               this_object(), me);
                return 1;
        }

        switch(query_temp("want_opinion/kuihua", me) )
        {
        case 0:
                command("say 好吧，你准备好了就接我一招，我看看你的水平如何。");
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

        addn_temp("want_opinion/kuihua", 1, me);
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
        lvl += 20;
        return lvl;
}

void do_congration(object me)
{
        command("chat*heihei"+query("id", me));
}

int accept_hit(object me)
{
        command("heng");
        command("say 你活得不耐烦了！");
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        object weapon;

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
        {
                message_vision(CYN "$N" CYN "对$n" CYN "道：“很"
                               "好，你也算是顶尖高手了，来吧！咱"
                               "们比划一下！”\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( !query_temp("want_opinion/kuihua", me) )
        {
                command("say 你干什么要和我动手？");
                return 0;
        }

        command("look"+query("id", me));
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
        if( query("character", me) != "阴险奸诈" && 
            query("character", me) != "国士无双" )
        {
                command("say 你这人没有领会立世的精妙之理，还"
                        "是回去吧！");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say 想学我的葵花神功？你还不够资格，"
                        "等你成了大宗师再说吧！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say 够了！我就教你到这里吧，武功还是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if (skill != "kuihua-mogong")
                return 1;

        if( query_temp("can_learn/kuihua/kuihua-mogong", me) )
                return 1;

/*
        set_temp("can_learn/kuihua/kuihua-mogong", 1, me);
        command("nod");
        command("say 不错，我就传你葵花神功吧，不要读什么葵花"
                "宝典，那是我拿去害人的！");
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

int give_quest()
{
    mapping questtemp,questkh,questkill,skills,robot_quest;
    object ob,npc;
    int time,level,i,lev,lev1;
    int exp;
    int lvl,all_lvl;
    string msg,*sname,place;
    object maze_target;
    object maze_object;

    ob = this_player();
    exp=query("combat_exp", ob);

    if( (query("character", ob) != "阴险奸诈") && 
            (query("character", ob) != "国士无双") && 
            (query("character", ob) != "心狠手辣") )
    {
        message_vision("葵花太监抬头看了$N一眼，尖着嗓子道：“你这号假仁假义的货色，再不马上给我滚开，我让你血溅五步！”\n", ob);
        return 1;
    }
    /*
    if( query("shen", ob) >= 0 )
    {
        write("葵花太监头也不抬，轻轻叹了口气，道：“好好一个人，偏要弃暗投明，竟还敢到这里来，真是不想活啦？”\n");
        return 1;
    }
    */
        if (exp < 500000)
    {
        write("葵花太监头也不抬，轻轻道：“你先去练练功夫吧，想为我做事，你还不够呢。”\n");
        return 1;
    }
    if( mapp(query("quest_kh", ob)) )
    {
       write("葵花太监把玩着手中古玩，微微点头来，道：“你手头的任务可是完成了？”\n");
        return 1;
    }
    if( mapp(query("quest_sn", ob)) )
    {
        write("葵花太监把玩着手中古玩，冷笑摇头，道：“南海神尼那个老不死的总和我作对，你敢带着她的任务来找我？”\n");
        return 1;
    }


    if( (time()-query("questkh_giveup_time", ob))<(20+random(10)) )
    {
        write("不要急，慢一点嘛。\n");
        return 1;
    }

/*
        if( query("questkh_times", ob)<3
         || (query("questkh_times", ob)>5 && random(20) == 5) )
        {
                X_QuestD->query_quest(ob, this_object());
                return 1;
        }
*/

    // 以下给任务
    if(exp <= 600000)        level = 0;
    else if(exp <= 900000)   level = 1;
    else if(exp <= 1200000)  level = 2;
    else if(exp <= 1800000)  level = 3;
    else if(exp <= 2500000)  level = 4-random(3);
    else if(exp <= 3200000)  level = 5-random(3);
    else if(exp <= 4000000)  level = 6-random(3);
    else
    {
        if(random(15)==0||(exp>10000000&&random(10)==0)||wizardp(ob))
            level=8;
        else level=7-random(3);
    }

    i=query("questkh_times", ob);

    if(i > 20 && random(20) == 15)
    {
        questkill = QUESTKILL_D->query_questkill();
        msg = questkill["msg"];
        write("葵花太监用眼角瞟了你一眼，微露讶色，道：“你倒是好象挺能干的嘛，嗯？”\n");
        write(msg+"\n");
        time = questkill["time"]/2+random(questkill["time"]/2);
        write("葵花太监回头看了看你，又道：“我给你"+time_period(time)+"时间，你快去罢。”\n");
        time += time();
      //不要直接修改questkill
        questkh = ([
            "name" :  questkill["name"],
            "khmsg":  msg,
            "dir"  :  questkill["dir"],
            "dir1" :  questkill["dir1"],
            "type" :  questkill["type"],
            "time" :  time,
            "level":  level,
            "desc" :  "灭",
            ]),
        set("quest_kh", questkh, ob);
        return 1;
    }
    else
    {
        if(level==8)
        {
            npc = new(CLASS_D("generate") + "/player_npc.c");
            FUBEN_D->clear_fuben("ultra",query("id", ob));
            maze_object=get_object("/f/ultra/"+query("id", ob)+"/maze");
            maze_object->set_maze_boss(npc);
            //maze_target = MAZE_D->create_maze(npc);
            maze_target=get_object("/f/ultra/"+query("id", ob)+"/maze/exit");
            npc->move(maze_target);
            npc->set_from_me(ob,1);
            addn_temp("apply/attack", npc->query_skill("force")/3, npc);
            addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
            addn_temp("apply/parry", npc->query_skill("force")/3, npc);
            addn_temp("apply/damage", 200+random(100), npc);
            addn_temp("apply/unarmed_damage", 200+random(100), npc);
            addn_temp("apply/armor", 200+random(300), npc);
            set_temp("quester",query("id",  ob), npc);
            set("auto_perform", 5, npc);

            set("shen",query("combat_exp",  npc)/2000, npc);
            msg="葵花太监恨恨地说：“"+npc->name(1)+
                "这个所谓的大侠屡次和我作对，听说他最近躲在迷宫中，你去宰了他，提头来见！”\n";

            questkh = ([
                "maze" : maze_object,
                "name" : npc->name(1),
                "id":query("id", npc),
                "bonus": (200+random(51)),
                "type" : "杀",
                "level": 8,
                "where": maze_target,
                "khmsg": msg,
                        "object":base_name(npc),
            ]);
            tell_object(ob,questkh["khmsg"]+"\n");
            set("quest_kh", questkh, ob);

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
            } else lvl = level;
            while(1)
            {
                questtemp = QUESTKH_D(lvl)->query_questkh(ob);
                if (questtemp["type"] == "杀" || questtemp["type"] == "擒")
                {
                    if (! get_object(questtemp["object"])->is_master())
                        break;
                } else
                    break;
            }

                if(undefinedp(msg = questtemp["msg"]) || msg == "" || random(2))
                {
                                if(questtemp["race"])
                                        msg=KHMSG_D->query_khmsg("宰",questtemp["name"]);
                                else
                                        msg=KHMSG_D->query_khmsg(questtemp["type"],questtemp["name"]);
                        }
                questkh=([
                        "id":questtemp["id"],
                        "name":questtemp["name"],
                        "bonus":questtemp["bonus"],
                        "type":questtemp["type"],
                        "khmsg":msg,
                        "level":level,
                        "object":questtemp["object"],
                        ]);

/*
    if (questkh["type"] == "杀" && (random(6) == 3 || wizardp(ob)))
    {
        robot_quest = ANTI_ROBOT->get_question();
        msg = "葵花太监阴笑着说道：“我刚将出入宫门的口令更改了一下，你去通知一下" + questkh["name"] + NOR"，新口令是：\n";
        msg += robot_quest["question"];
        msg += "你只需要将口令用"HIR"普通的数字形式"NOR"传送过去就行了，传送的指令是：whisper。\n";
        questkh["type"]   = "传";
        questkh["khmsg"]  = msg;
        questkh["answer"] = robot_quest["answer"];
    }
*/

                write(questkh["khmsg"]+"\n");
                set("quest_kh", questkh, ob);
            }
    }
    return 1;
}

int accept_object(object who, object ob)
{
   int exp, pot,level,bonus,i,all_quest_kh;
   mapping questkh;
   object me,gold,obj;
   int shen,mar,weiwang,score,quest_count;
   int total_count;
   string msg;
   mixed special = 0;
   mixed money = 0;

   me = this_object();
   if( !(questkh=query("quest_kh", who)) )
   {
      return notify_fail("葵花太监满脸不耐烦的冲你说：“走开，不要来烦我。”\n");
   }

   if( query("money_id", ob) )
   {
           if (ob->value() < 1000000)
           {
                   tell_object(who,"葵花太监勃然大怒道：你拿这么点钱来哄我啊？再不给我滚远点，我扒了你的皮！\n");
                   return notify_fail("葵花太监轻蔑的说：如果能给个100两黄金，或许我就消除了你的任务。\n");
           }
           delete("quest_kh", who);
           tell_object(who,"葵花太监抛了抛手中的" + ob->name(1) + "，冷冷道：那你这个任务不做就算了吧。\n");
           destruct(ob);
           return 1;
   }

   switch(questkh["type"])
   {
      case "寻"  :
         if(ob->name(1) != questkh["name"] || userp(ob))
         {
            tell_object(who,"葵花太监大怒，斥道：“这是什么东西？你想来糊弄我么！”\n");
            return notify_fail("葵花太监吁了口气，向你甩甩手，道：“你去吧，不要烦我。”\n");
         }
         break ;
      case "杀"  :
         if(!ob->is_head() && !ob->is_corpse())
         {
            tell_object(who,"葵花太监斜着眼睛描了一下，斥道：“这是个什么东西？你想来糊弄我么！”\n");
            return notify_fail("葵花太监白了你一眼，甩甩手，道：“你还站在这里干什么？还不快去！”\n");
         }
         else if( !stringp(query("victim_name", ob)) || query("victim_name", ob) != questkh["name"] )
            {
                tell_object(who,"葵花太监捂着鼻子挥手说道：“什么臭烘烘的？快给我拿走！”\n");
                return notify_fail("葵花太监白了你一眼，甩甩手，道：“我给你的任务你是否不想做了？”\n");
            }
            else if( query("killed_by", ob) != query("id", who) )
            {
                tell_object(who,"葵花太监哼了一声道：“你是从哪里捡来的？你自己做不了么？”\n");
                return notify_fail("葵花太监白了你一眼，甩甩手，道：“你还站在这里干什么？还不快出去！”\n");
             }
         break ;
      default    :
         return 0;
   }

        if( userp(ob) || query("user", ob) || 
            ob->is_item_make() ||
            ob->query_save_file())
    {
        write("葵花太监大怒道：“好你个小杂种，竟然想蒙骗本宫！来人！把他给我抓起来！”\n");
        who->get_into_prison(this_object(), 0, 30);
        log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(葵花任务)制造%s(%s)(%s)作弊\n",query("name", who),
             query("id", who),ob->name(),query("id", ob),ctime(time())));
        return 1;
    }

//   message_vision("$N将$n交给葵花太监。\n",who,ob);与give信息重复haiyan
   tell_object(who,"葵花太监冷笑了一声，抬头看了看你，点头道：“嗯，你可以去了。”\n");
    destruct(ob);
   if( (i=query("questkh_times", who))<15)i=15-i;
   else i = 1;
   level = questkh["level"]+1;
   exp = level*80 + questkh["bonus"]*3;
        exp+=query("questkh_times", who);
   exp += random(exp/2);
   exp = exp/i;

   if (level > 4 && i > 5)
        exp /= 2;

    /*
   if (level == 9)
       pot = exp*(2 + random(2));
   else
    */
       pot = exp/(2+random(2));
   score = random(exp/20);
   weiwang = random(exp/15);

   if( query("questkh_times", who)+1>200 )
         mar=exp/5+random(query("questkh_times", who));
   else mar = 20 + random(20);

   exp = exp*3;
   pot = pot*3;
   mar = mar*3;
    
   if (mar > 1000) mar = 1000;

   if(!random(18))
   {
      i=(exp/60+1);
      if(i>30) i=30;
      gold=new("/clone/money/gold");
      gold->set_amount(i);
      tell_object(who,"突然一锭黄金飞入你的手中，背后葵花太监冷冷说道：“这些金子拿去，日后办事卖力点！”\n"
          HIW"\n你被奖励了 "+i+" 两黄金。\n"NOR);
       if(!gold->move(who))
       {
          message_vision("但是$N身上东西太重，黄金一下子从手中滑到了地上。\n",who);
          gold->move(environment());
      }
      GIFT_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                            "weiwang" : weiwang, "score" : score, "percent" : 100 ]), 1);
   }
   else GIFT_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar, "percent" : 100,
                              "weiwang" : weiwang, "score" : score ]), 1);

   // who->add("questkh_times",1);
   quest_count=query("questkh_times", who)+1;
   total_count = quest_count % 500;
   if (total_count == 50)
   {
       msg = "$N嘿嘿冷笑两声道：“你小子还可以，连着"+chinese_number(quest_count)+
       "次任务都完成的干净利索，还算有点前途。”\n";
        special = 1;
           } else
       if (total_count == 100)
   {
       msg = "$N抬头使劲看了你一眼道：“真是不错，"+chinese_number(quest_count)+
       "次任务干得还算妥当。”\n";
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
       msg = "$N深深叹了口气，道：“想不到你连着"+chinese_number(quest_count)+
       "次任务无一失手，看来以后的江湖就是你的天下啦！”\n";
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
       msg = "$N微微点头：“干的不错，居然连着" +chinese_number(quest_count)+
       "次都没有失手，继续给我好好表现！”\n";
   }

   set("questkh_times", quest_count, who);

   if (special) {
       // message_vision(msg, me, who);
       GIFT_D->special_bonus(me, who, special);
   }
    if (money) {
        // message_vision(msg, me, who);
        QUEST_D->money_bonus(me, who, money);
    }
   delete("quest_kh", who);
   addn("total_hatred", -5, who);
   if( query("total_hatred", who)<0)set("total_hatred", 0, who);

   //记录完成任务的次数（不要求连续），如果满1000次则奖励钻石残片
   all_quest_kh=query("all_quest_kh", who);
   if (!all_quest_kh) all_quest_kh = 0;
   all_quest_kh += 1;
   if (all_quest_kh == 1000)
   {
       obj = new("/clone/tessera/memerald.c");
       tell_object(who,this_object()->name() + "又对你点了点头：你已经从我这里接了一千个任务，我这里正好\n" +
                   "有个"+query("name", obj)+"，就奖给你了！\n");
       if (!obj->move(who))
               obj->move(environment());
       set("all_quest_kh", 0, who);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D->add_bunch_fame(who, 20 + random(5));
   }else set("all_quest_kh", all_quest_kh, who);

   return 1;
}

int give_up()
{
   object ob,obj,room;
   mapping questkh;

   ob = this_player();

   if(query("kill_all"))   return 0;

   message_vision("$N心惊胆战，双腿乱颤，请求葵花太监取消自己的任务。\n",ob);
   if( mapp(questkh=query("quest_kh", ob)) )
   {
      /*
      if (questkh["type"] == "传")
      {
         message_vision("$N勃然大怒，指着$n鼻子骂道：『不就是传一个口令么？这么点小事都完成不了？还不快滚！\n",this_object(),ob);
         return 1;
      }
      */
      if(questkh["desc"] == "灭")
      {
         message_vision("葵花太监看了$N一眼，“嗯”了一声，不置可否。\n", ob);
      }
      else if(questkh["type"] == "杀"&&questkh["level"] == 8)    //by llm
      {
          message_vision("葵花太监头也不抬，哼了一声道：“没用的东西！蠢材！”\n", ob);
          set("questkh_times", 0, ob);
      }
      else
      {
         message_vision("葵花太监头也不抬，哼了一声道：“没用的东西！蠢材！”\n", ob);
         set("questkh_times", 0, ob);
      }

      if ( stringp(questkh["maze"]) )
      {
         //MAZE_D->remove_maze(questkh["maze"]);
         FUBEN_D->clear_fuben("ultra",query("id", ob));
      }

   }
   else
   {
      message_vision("葵花太监专心把玩手中的古董，好象根本没看见$N\n", ob);
   }
   delete("quest_kh", ob);
   set("questkh_giveup_time", time(), ob);
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
        message_vision("$N哈哈一笑：“葵花太监的手下尽是一些窝囊废！”转身一晃，已不见了身影。\n",npc);
    npc->move("/d/register/prison");
    destruct(npc);
    return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "无边无际" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/bian",
                           "name"    : "无边无际",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "分身化影" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/fenshen",
                           "name"    : "分身化影",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "鬼魅身法" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/gui",
                           "name"    : "鬼魅身法",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "dodge"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "毁天灭地" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/hui",
                           "name"    : "毁天灭地",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "无穷无尽" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/qiong",
                           "name"    : "无穷无尽",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "无声无息" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/sheng",
                           "name"    : "无声无息",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "dodge"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "无法无天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/tian",
                           "name"    : "无法无天",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "无双无对" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/wswd",
                           "name"    : "无双无对",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "群魔乱舞" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/wu",
                           "name"    : "群魔乱舞",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "幽灵一击" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/you",
                           "name"    : "幽灵一击",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "幽冥神指" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/zhi",
                           "name"    : "幽冥神指",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "finger"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
