// person used in quest
#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

object jiufen_object = 0;
string jiufen_name = "";
string quest_ob = "";

string *say_msg = ({
"$N冲着$n愤怒的说：赶紧把我的obj_name还给我，否则对你不客气！",
"$N指着$n的鼻子对大家说：你们来评评道理，这个臭贼去年拿走了我的obj_name，到现在还不还给我！",
"“碰”的一声，却是一张板凳给$N踹了老高，又落在$n的身边，空气中浓浓的火药味。",
"$N死命的盯着$n，脚开始微微颤抖，似乎随时都会踹出去。",
"$N咬咬牙，把手插进裤兜，似乎要掏出把什么东西来，看到$n冷冷的目光，却又空手抽了出来。",
"$N越说越激动：obj_name是我当初最好朋友留下的唯一遗物，给$n骗走后至今未归还给我。",
"$N咬牙切齿的看着$n，当初说好是借一个星期，现在过了一年了怎不见你还给我？",
"$N满脸不屑的看着$n，你真是一个大骗子！",
"$N怒火冲天的吼：就算是弄丢了你也得给我找回来！吐沫星子喷了$n满脸。",
"$N一屁股坐地上，撒赖似的对着$n哼哼：不把东西还给我，以后我就吃你的喝你的用你的。",
"$N眼睛瞪得和香炉一样大：$n你这个骗子，我不把你扁得满脸冒血，你就不知道花儿~为什么,那!样!红!!!~~",
"只见$N一个箭步，“啪....啪....啪”转眼间已经在$n的屁股上留下十几个脚印。",
"$N冲$n的鼻梁狠狠的打了一拳，然后$n眼泪哗啦哗啦流了一脸盆。",
"$N看着$n的满脸的奸笑愤声暗骂道：“他奶奶的！！！”",
"$N打了$n一记响亮的耳光。",
"$N真想$n去死。",
"$N对$n正色道：“直娘贼，你可不要自寻死路！”",
"$N对着$n阴阴的笑：你不把obj_name还给我，你就别想有好日子过！",
});

string *reply_msg = ({
"$N冲着$n故作茫然地说：你说什么obj_name啊？我怎么听不懂哦？",
"$N指着$n的鼻子对大家说：你看看他这种穷酸样，会是一个有obj_name的人么？",
"“碰”的一声，却是一张板凳给$N踹了老高，又落在$n的身边，空气中浓浓的火药味。",
"$N冷冷的盯着$n的脚，生怕它突然踹过来。",
"$N的火气也越来越大：$n你口口声声说是我好朋友，不就是一个破烂obj_name，也值得你这样？",
"$N越说越激动：obj_name本来就是我父亲给$n的，现在回到我手里也是很正常的嘛。",
"$N咬牙切齿的看着$n，就你这态度，还想我把obj_name还给你？做梦去吧！",
"$N满脸不屑的看着$n，对付你这种猪头猪脑的土包子，还用讲什么道理？",
"$N怒火冲天的吼：$n你给我听着，别说我现在没有obj_name，就算有也不会给了你！",
"$N看着$n突然嘻嘻的笑：你急啊，你叫啊，我就是不给你，你能怎的？吃了我？",
"$N眼睛瞪得和香炉一样大：$n你这个臭小子，我不把你扁得满脸冒血，你就不知道花儿~为什么,那!样!红!!!~~",
"只见$N一个箭步，“啪....啪....啪”转眼间已经在$n的屁股上留下十几个脚印。",
"$N冲$n的鼻梁狠狠的打了一拳，然后$n眼泪哗啦哗啦流了一脸盆。",
"$N看着$n的怒气冲天的样子，突然哈哈一笑，翘起二郎腿慢慢的喝香茶。",
"$N打了$n一记响亮的耳光。",
"$N真想$n去死。",
"$N对$n正色道：“直娘贼，你可不要自寻死路！”",
"$N对着$n阴阴的笑：想我把obj_name还给你，除非跪下来给我磕三个响头！",
});

void set_quest_ob(string arg);
void set_jiufen_object(object ob);
int  accept_object(object who, object ob);
int  leave();
int  is_stay_in_room()        { return 1; }
void heart_beat();
void destruct_me();
string ask_me();

void create()
{
        ::create();
        set("gender",query("gender"));
        set("age", 30 + random(30));
        if (arrayp(query("from")) && sizeof(query("from")))
                set("long",query("from")[random(sizeof(query("form")))] + "\n据说这次重入江湖乃是因为跟人有了纠纷。\n");
        else
                set("long","据说这次重入江湖乃是因为跟人有了纠纷\n");


        set("attitude", "friendly");
        set("chat_chance", 30);
        set("scale", 150);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 50);
        set_temp("born_time", time());
        set("inquiry", ([
                 "调解" : (: ask_me :),
         ]) );
        set_heart_beat(10);
}

void set_quest_ob(string arg)
{
       quest_ob = arg;
       return;
}

void set_jiufen_object(object ob)
{
       jiufen_object = ob;
       jiufen_name = ob->name();
       return;
}

int accept_fight(object ob)
{
        command("say 你我之间又没什么纠纷，凑啥热闹！");
        return notify_fail("你满脸羞愧，取消了跟" + this_object()->name() + "比试的念头！\n");
}

int accept_kill(object ob)
{
        command("say 怎么说？你也来欺负我？");
        command("cry");
        return notify_fail("刹那间你只觉得下不了手。\n"); 
}

int accept_hit(object ob)
{
        command("say 怎么说？你也来欺负我？");
        command("cry");
        return 0;
}

int accept_touxi(object ob)
{
        tell_object(ob,"你刚想偷袭，突然发现" + this_object()->name() + "防备很严谨。\n"); 
        return 1;
}

int accept_ansuan(object who) 
{
        return notify_fail("你刚想暗算，可是发现" + this_object()->name() + "非常小心谨慎，让你无从下手。\n"); 
} 

void heart_beat()
{
       mapping msg;
       string msg1,msg2;

        if (time() - query_temp("born_time") > 900)
        {
                message_vision("$N哭闹了半天，感觉没什么意思，讪讪的走了。\n", this_object());
                destruct_me();
                return;
        }

       if (!objectp(jiufen_object) || 
           !living(jiufen_object) ||
           !environment(this_object()) || 
           !environment(jiufen_object) ||
           environment(this_object()) != environment(jiufen_object))
        {
                message_vision("$N哼了一声，恨恨的骂道：这个缩头乌龟，今天我暂且先走了，下次再来！\n", this_object());
                destruct_me();
                return;
        }

       //如果已经开始调节纠纷，则停止吵架
       if (query_temp("on_tiaojie")) 
       {
              message_vision("$N对着$n哼了一声。\n",this_object(),jiufen_object);
              message_vision("$n恼怒的瞪着$N，看上去正在强忍着心头的怒气。\n",this_object(),jiufen_object);
              return;
       }

       msg1 = say_msg[random(sizeof(say_msg))];
       msg2 = reply_msg[random(sizeof(reply_msg))];
       msg1 = replace_string(msg1,"obj_name",quest_ob);
       msg2 = replace_string(msg2,"obj_name",quest_ob);
       message_vision(msg1 + "\n",this_object(),jiufen_object);
       message_vision(msg2 + "\n",jiufen_object,this_object());
       return;
}

void destruct_me()
{
       message_vision("$N转身离开了。\n",this_object());
       destruct(this_object());
       return;
}

int accept_object(object who,object ob)
{
       int exp,pot,weiwang,score;
       mapping b;

        if (ob->is_character() || ob->is_item_make())
                // 不接受人物和自造的兵器
                return 0;

       if( !query("bunch_quest", who) || 
           query("bunch_quest/type", who) != "调解纠纷" || 
           query("bunch_quest/ob", who) != this_object() )
               return notify_fail("你小子送我这个东西干什么？蒙我？\n");

       if( query("name", ob) != quest_ob )
       {
               command("angry");
               command("say TNND,拿这个破玩意来糊弄我？我要的是" + quest_ob + "，找不到就别来充老大！");
               return 0;
       }

       exp=query("bunch_quest/bonus", who);
       exp += random(exp);
       pot = exp/(2+random(1));
       weiwang = 5 + random(10);
       score = 5 + random(10);

       delete("bunch_quest", who);
       addn_temp("finish_bunch_times", 1, who);
       command("wa"+query("id", who));
       command("leyun"+query("id", who));
       command("spank"+query("id", who));
       command("say 既然这位" + RANK_D->query_respect(who) + "如此仗义，那我也没话好说了，兄弟这次先告辞了，后会有期！");

       b = ([ "exp" : exp,
               "pot" : pot,
               "score" : score,
               "weiwang" : weiwang,
               "prompt": "在帮助" + jiufen_name + HIG "调解纠纷的过程中，经过锻炼"
           ]);

       QUEST_D->delay_bonus(who, b);

       remove_call_out("destruct_me");
       call_out("destruct_me",0);

       return 1;
}

string ask_me()
{
       object who;
       who = this_player();
       if( !query("bunch_quest", who) || 
           query("bunch_quest/type", who) != "调解纠纷" || 
           query("bunch_quest/ob", who) != this_object() )
               return "你是谁？在一边JJYY的烦不烦，给我滚远点，这里没你的事！";
       
       set_temp("on_tiaojie", 1, this_object());
       return "调解？用什么来调解？莫非你还能帮我把" + quest_ob + "找回来啊！";
}