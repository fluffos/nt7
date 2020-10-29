// liumang.c 流氓
#include <ansi.h>

inherit NPC;

#define PLACE "yz"     //扬州
#define TYPE  "bad"    //黑道
#define WAIT_TIME 60    //完成不了任务的反省时间

string *fail_xc_msg1=({
        "place你查看了没有？",
        "你有没有看一下place？",
        "难道place就不用巡查了？",
        "去place再看看！",
        "你别把place给拉下啊，",
        "place是一个很重要的地方，不能不查看一下，",
        "你没有去巡查place吧？",
});

string *fail_xc_msg2=({
        "你这算什么巡城！",
        "你这就回来了？",
        "巡城怎么可以这么草率啊！",
        "不要总想着偷懒！",
        "你办事情也太不认真了吧。",
        "这也能算巡城啊，当我老的管不了你了？",
        "别偷懒！",
        "做事情要踏踏实实！",
});

mapping bang_bad = ([
        "name" : "小刀会",
        "id"   : "xdh",
        "place": "yz",
        "boss" : "鞠老大",
]);

void create()
{
	set_name("鞠老大", ({ "ju laoda", "laoda" }));
	set("gender", "男性");
	set("age", 23);
	set("long", "他是一个长得很英俊的男子，看上去风流倜傥，让人无法相信他就本城地头蛇" + bang_bad["name"] + "的首领。\n");
	set("title",HIW"扬州小刀会总首领"NOR);
       set("nickname",HIY"天下第一大色狼"NOR);
       set("per",29);
	set("combat_exp", 1000000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver",2);
}

void init()
{
       add_action("do_join","join");
       add_action("do_disengage","disengage");
       add_action("do_choose","choose");
       add_action("do_giveup","giveup");
}

int do_join()
{
       string msg;
       object me,obj;
       me = this_player();
       obj = this_object();

       if( query("bang_bad", me) )
       {
               if( query("bang_bad/name", me) == bang_bad["name"] )
               {
                       if( query("shen", me)>0 )
                       {
                               message_vision("$N对着$n勃然大怒：好你个兔崽子，没事偏偏要去冒充什么正人君子！\n",obj,me);
                               delete("bang_bad", me);
                               msg = "听说" + me->name(1) + "被" + obj->name(1) + "逐出了" + bang_bad["name"];
                               CHANNEL_D->do_channel(this_object(), "rumor", msg);
                               return notify_fail("你被" + obj->name() + "开除出了" + bang_bad["name"] + "。\n");
                       }
                       return notify_fail("你已经是我"+query("bang_bad/name", me)+"的成员了，昏头了？\n");
               }
               return notify_fail("你现在是"+query("bang_bad/name", me)+"的成员，要加入我"+bang_bad["name"]+"，得先脱离(disengage)原来的帮会。\n");
       }
       
       if( query("bang_good", me) || query("shen", me)>0 )
       {
               message_vision("$N上上下下的仔细打量着$n，脸色越来越难看。\n",obj,me);
               command("say " + "你这种自命正派人士的到我这里来干什么？想找茬子？");
               return notify_fail("看来" + obj->name() + "并不欢迎你！\n");
       }

       if( query("combat_exp", me)<10000 )
       {
               command("joke"+query("id", me));
               command("say 这位" + RANK_D->query_respect(me) + "，你还太嫩了点，先锻炼锻炼然后再出来跟我混。");
               return notify_fail("看来" + obj->name() + "觉得你实在太嫩了点。\n");
       }

       if( query("combat_exp", me) >= 600000 )
       {
               command("joke"+query("id", me));
               command("say 这位" + RANK_D->query_respect(me) + "，您身手这么高了，我这种小帮会怎能留住你。");
               return notify_fail("看来" + obj->name() + "觉得你等级太高了。\n");
       }

       set("bang_bad", bang_bad, me);
       message_vision("$N单膝跪下，对着$n恭恭敬敬的喊了声：老大！\n",me,obj);
       message_vision("$N微微一笑，对着$n点了点头，摆手让$n站起身来。\n",obj,me);
       tell_object(me,"恭喜你成为" + bang_bad["name"] + "的成员！\n");
       msg = "听说" + me->name(1) + "拜" + obj->name(1) + "为老大，加入了" + bang_bad["name"];
       CHANNEL_D->do_channel(this_object(), "rumor", msg);
       return 1;
}

int do_disengage()
{
       string msg;
       object me,obj;
       me = this_player();
       obj = this_object();

       if( query("bang_good", me) )
       {
               message_vision("$N上上下下的仔细打量着$n，脸色越来越难看。\n",obj,me);
               command("say " + "你这种自命正派人士的到我这里来干什么？想找茬子？");
               return notify_fail("看来" + obj->name() + "并不欢迎你！\n");
       }

       if( !query("bang_bad", me) || query("bang_bad/name", me) != bang_bad["name"] )
       {
               command("yi"+query("id", me));
               command("say 这位" + RANK_D->query_respect(me) + "，你并非我" + bang_bad["name"] + "的成员啊！");
               return notify_fail("看来" + obj->name() + "给你搞的满头雾水。\n");
       }

       if( query("bang_bad/boss", me) != bang_bad["boss"] )
               return notify_fail("想脱离我小刀会？找你的介绍人"+query("bang_bad/boss", me)+"去吧。\n");

       delete("bang_bad", me);

       if( query("shen", me)>0 )
       {
               message_vision("$N对着$n勃然大怒：好你个兔崽子，没事偏偏要去冒充什么正人君子！\n",obj,me);
               delete("bang_bad", me);
               tell_object(me,"你被" + obj->name() + "开除出了" + bang_bad["name"] + "。\n");
               msg = "听说" + me->name(1) + "被" + obj->name(1) + "逐出了" + bang_bad["name"];
               CHANNEL_D->do_channel(this_object(), "rumor", msg);
       } else
       {
               message_vision("$N对着$n叹气道：早就知道你不会在这种小地方混一辈子的，也罢，你自己保重！\n",obj,me);
               delete("bang_bad", me);
               tell_object(me,"你决定脱离" + bang_bad["name"] + "。\n");
       }
       return 1;
}

int do_choose(string bh)
{
       string msg;
       mapping bang_quest;
       object me,obj;

       me = this_player();
       obj = this_object();

       //如果是白道的，就赶走
       if( query("bang_good", me) )
       {
               message_vision("$N上上下下的仔细打量着$n，脸色越来越难看。\n",obj,me);
               command("say " + "你这种自命正派人士的到我这里来干什么？想找茬子？");
               return notify_fail("看来" + obj->name() + "并不欢迎你！\n");
       }

       //如果不是本帮会的，不给领取任务
       if( !query("bang_bad", me) || query("bang_bad/name", me) != bang_bad["name"] )
       {
               command("yi"+query("id", me));
               command("say 这位" + RANK_D->query_respect(me) + "，你并非我" + bang_bad["name"] + "的成员啊！");
               return notify_fail("看来" + obj->name() + "给你搞的满头雾水。\n");
       }

       //如果是本帮会，但是变成了正神，那么如果是本人收录的成员，将其开除；否则，将其赶走
       if( query("shen", me)>0 )
       {
               message_vision("$N对着$n勃然大怒：好你个兔崽子，没事偏偏要去冒充什么正人君子！\n",obj,me);
               if( query("bang_bad/boss", me) == bang_bad["boss"] )
               {
                       message_vision("$N对着$n怒喝道：留你在我" + bang_bad["name"] + "岂非叫人笑话！\n",obj,me);
                       delete("bang_quest", me);
                       delete("bang_bad", me);
                       msg = "听说" + me->name(1) + "被" + obj->name(1) + "逐出了" + bang_bad["name"];
                       CHANNEL_D->do_channel(this_object(), "rumor", msg);
                       return notify_fail("你被" + obj->name() + "开除出了" + bang_bad["name"] + "。\n");
               } else
               {
                       message_vision("$N对着$n怒喝：还不给我快滚！\n",obj,me);
                       return notify_fail("你没有从" + obj->name() + "那里领取到任何任务，反而挨了一顿臭骂。\n");
               }
       }

       //如果已经有任务在身，就痛骂一顿
       if( query("bang_quest", me) )
               return notify_fail(obj->name() + "生气的看着你说：你刚才领的任务还没有完成，急什么？\n");

       //如果没有输入编号，则提示指令
       if (!bh)
               return notify_fail(obj->name() + "奇怪的看着你，你想领取什么任务？指令是：choose <编号>。\n");
 
       //如果是追杀任务，则不需要领取任务
       if (bh[0..1] == "zs")
               return notify_fail(obj->name() + "微微一笑，既然是追杀令，还用领取任务？赶紧去完成吧！\n");

       //如果是巡城，则看玩家是否加入的本地帮会
       if( bh == "xc" && query("bang_bad/place", me) != bang_bad["place"] )
               return notify_fail(obj->name() + "对你摆了摆手说：巡城这种事情，我本城的兄弟就可以胜任，不劳你大驾了！\n");

       //如果这个NPC正BUSY，则不给任务
       if (obj->is_busy())
               return notify_fail(obj->name() + "正忙着呢，你稍微等一下。\n");

       //如果这个玩家刚放弃过任务，需要等待
       if( time()-query("last_bang_quest", me)<query("need_wait_time", me) )
               return notify_fail("完成不了任务，先好好反省一下，然后再来领取任务！\n");

       //检查该编号的任务是否存在
       bang_quest = PARTY_QUEST_D->query_city_quest(PLACE,TYPE,bh);

       if (!bang_quest)
               return notify_fail(obj->name() + "翻开簿子看了看，对你说：目前没有" + bh + "这个任务。\n");

       //如果是巡城任务，则检查当天是否已经有人在巡城
       if (bang_quest["id"] == "xc" && !bang_quest["enable"])
               return notify_fail(obj->name() + "微微笑着说：今天已经有兄弟去巡城了，你就等改天吧！\n");

       //给任务，并且将该任务从列表中删除 
       obj->start_busy(1);
       PARTY_QUEST_D->delete_city_quest(PLACE,TYPE,bh);
       set("bang_quest", bang_quest, me);
       message_vision("$N对着$n点了点头：那么这个任务就交给你了，好好去干！\n",obj,me);
       tell_object(me,"你接的任务是：\n" + bang_quest["msg"] + "\n");
       return 1;
}

int do_giveup()
{
       string msg;
       object me,obj;

       me = this_player();
       obj = this_object();

       //如果是白道的，就赶走
       if( query("bang_good", me) )
       {
               message_vision("$N上上下下的仔细打量着$n，脸色越来越难看。\n",obj,me);
               command("say " + "你这种自命正派人士的到我这里来干什么？想找茬子？");
               return notify_fail("看来" + obj->name() + "并不欢迎你！\n");
       }

       //如果不是本帮会的，不理会
       if( !query("bang_bad", me) || query("bang_bad/name", me) != bang_bad["name"] )
       {
               command("yi"+query("id", me));
               command("say 这位" + RANK_D->query_respect(me) + "，你并非我" + bang_bad["name"] + "的成员啊！");
               return notify_fail("看来" + obj->name() + "给你搞的满头雾水。\n");
       }

       //如果是本帮会，但是变成了正神，那么如果是本人收录的成员，将其开除；否则，将其赶走
       if( query("shen", me)>0 )
       {
               message_vision("$N对着$n勃然大怒：好你个兔崽子，没事偏偏要去冒充什么正人君子！\n",obj,me);
               if( query("bang_bad/boss", me) == bang_bad["boss"] )
               {
                       message_vision("$N对着$n怒喝道：留你在我" + bang_bad["name"] + "岂非叫人笑话！\n",obj,me);
                       delete("bang_quest", me);
                       delete("bang_bad", me);
                       msg = "听说" + me->name(1) + "被" + obj->name(1) + "逐出了" + bang_bad["name"];
                       CHANNEL_D->do_channel(this_object(), "rumor", msg);
                       return notify_fail("你被" + obj->name() + "开除出了" + bang_bad["name"] + "。\n");
               } else
               {
                       message_vision("$N对着$n怒喝：还不给我快滚！\n",obj,me);
                       return notify_fail("你被" + obj->name() + "狠狠的痛骂了一番。\n");
               }
       }

       if( !query("bang_quest", me) )
               return notify_fail(obj->name() + "奇怪的看着你说：你现在并没有任务在身啊，是不是闲的发慌了？\n");

       delete("bang_quest", me);
       message_vision("$N对着$n一个劲的叹气，似乎不明白为什么$n为何如此的不成材。\n",obj,me);
       tell_object(me,obj->name() + "冲你瞪了一眼：这点小事情都完成不了，一边去好好反省反省！\n");

       //记录放弃时间
       set("last_bang_quest", time(), me);

       //如果玩家没有连续完成任务的次数记录，则累加该玩家需要等待的时间，最多WAIT_TIME秒，否则，等待3秒
       if( !query_temp("finish_bang_times", me) )
              set("need_wait_time",query("need_wait_time",  me)+3, me);
       else set("need_wait_time", 3, me);

       if( query("need_wait_time", me)>WAIT_TIME)set("need_wait_time", WAIT_TIME, me);

       //清除连续完成任务的次数
       delete_temp("finish_bang_times", me);
       return 1;
}

int accept_object(object who,object me,object ob)
{
       int exp,pot,score,weiwang;
       mapping bang_quest,bonus;
       object env;
       string *place,the_place,msg;

       if (base_name(ob) != "/d/city/npc/obj/yaopai")
               return notify_fail(who->name() + "不屑的把" + ob->name() + "抛还给你：什么烂东西也给我？\n");

       if( !query("bang_quest", me) )
               return notify_fail(who->name() + "朝你点了点头，没有说什么话。\n");

       bang_quest=query("bang_quest", me);

       if (bang_quest["id"] != "xc" || bang_quest["name"] != "巡扬州城")      
               return notify_fail(who->name() + "朝你点了点头，没有说什么话。\n");

       place = bang_quest["place"];

       if (sizeof(place))
       {
               the_place = place[random(sizeof(place))];
               env = get_object(the_place);
               msg = fail_xc_msg1[random(sizeof(fail_xc_msg1))];
               msg = replace_string(msg,"place",env->short());
               msg += fail_xc_msg2[random(sizeof(fail_xc_msg2))];
               return notify_fail(who->name() + "生气的对你说：" + msg + "\n");
       }

       message_vision("$N高兴的拍了拍$n的肩膀：干的好！\n",who,me);
       exp = bang_quest["bonus"]; 
       pot = exp/(2+random(2)); 
       weiwang = 5 + random(10); 
       score = 5 + random(10); 
       delete("bang_quest", me);
       addn_temp("finish_bang_times", 1, me);
       bonus = ([ "exp" : exp, 
                  "pot" : pot, 
                  "score" : score, 
                  "weiwang" : weiwang, 
                  "prompt": "在巡扬州城的过程中，经过锻炼" 
               ]);
       QUEST_D->delay_bonus(me, bonus);
       destruct(ob);
       return 1;
}