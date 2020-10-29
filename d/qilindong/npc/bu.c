#include <ansi.h>
inherit NPC;
int ask_jian();
int ask_baojian();
void consider();
void create()
{
    set_name("步惊云", ({"bu jingyun", "bu", "jingyun"}));
    set("nickname", HIY "不哭死神" NOR );
    set("gender", "男性");
    set("age", 25);
    set("long",
        "他就是天下会云堂堂主步惊云，江湖上人称「不哭死神」。\n");
    set("attitude", "peaceful");

    set("str", 100);
    set("int", 80);
    set("con", 86);
    set("dex", 240);
    set("chat_chance", 1);
    set("chat_msg", ({
        "步惊云叹了口气道：“唉 …… 我的令牌哪里去了 ……”\n",
        "步惊云低头沉思，悠然不语。\n",
    }));
    set("inquiry", ([
        "令牌"     : "谁能帮我找到令牌，我什么事都答应他! \n",
        "宝剑" : (: ask_baojian:),
        "绝世好剑" : (: ask_baojian:),
    ]));
    set("qi", 20000);
   set("max_qi", 20000);
    set("jing", 5000);
    set("max_jing", 5000);
    set("max_jingli", 3000);

    set("jingli", 3000);
    set("neili", 6000);
    set("max_neili", 20000);
    set("jiali", 300);

     set("combat_exp", 60000000);

  set_skill("force", 600);
    set_skill("huntian-baojian", 600);
     set_skill("paiyun-zhang", 300);
   set_skill("strike", 500);
     set_skill("dodge", 500);
    set_skill("zhuangzi-wu", 500);
    set_skill("parry", 500);
   set_skill("sword", 500);
    set_skill("zhuihun-jian", 500);
    set_skill("qimen-wuxing",800);
    set_skill("literate",550);           // 读书识字
    map_skill("force"  , "huntian-baojian");
    map_skill("strike", "paiyun-zhang");
    map_skill("dodge"  , "zhuangzi-wu");
    map_skill("parry"  , "paiyun-zhang");
             prepare_skill("strike" , "paiyun-zhang"); 
    create_family("天下会", 2, "堂主");
         set("chat_chance_combat", 150);
            set("chat_msg_combat", ({ 
                    (: perform_action, "strike.paishan" :), 
            })); 


	setup();

    carry_object("/d/taohua/obj/bupao")->wear();


}

int accept_object(object who, object ob)
{

    if ( (string) ob->query("id") =="ling pai" ) {
        // 是否那剑的本人
        if(ob->query("owner") == who->query("id") )
        {
            if (!(int)who->query_temp("tmark/ling")) who->set_temp("tmark/ling", 0);
            message_vision("步惊云看了看$N送来的令牌，点了点头，说道：\n"
                                   "难得你将令牌送回。你送我的东西我就收下了。\n"
                                   "作为补偿,我可以告诉你点秘密。\n", who);
           who->set_temp("tmark/ling", 1);
            return 1;
        }
    }
}

int ask_baojian()
{
  int p1, p2;
  if ((int)this_player()->query("_passwd")) {
 say("步惊云不悦地说道：我不是都告诉你了吗？我不知道。\n");
  }
if ((int)this_player()->query_temp("tmark/ling")) {
 say("步惊云一惊，说道：你怎么知道的？\n");
 write("步惊云顿一顿，接着对你低声说：那我就告诉你算了");
// p1=random(4)+1;
// p2=random(4)+1;

    p1 = random(100)+1;
    this_player()->set("_passwd", p1);
    write(CHINESE_D->chinese_number(p1));
    write("把\n宝剑，就是绝世宝剑。\n");
  }
  else {
   message("vision",
   HIY "步惊云勃然大怒，喝道：你也窥视我的绝世宝剑？！我跟你拼了！\n"
   NOR, environment(), this_object() );
   kill_ob(this_player());
  }
  this_player()->delete_temp("tmark/ling");
  return 1;
}

int ask_jian()
{
  int p1, p2;
            object me,obj;
            me = this_player();
                if (me->query("tmark/ling")) {
 say("步惊云一脸讥笑的样子，说：我凭什么告诉你？\n");
  }

    if ((int)this_player()->query("_passwd")) {
        say("步惊云一惊，说道：你怎么知道的？宝剑的秘密就我知道。\n");
        write("步惊云想了下低声说：好吧，看在你帮我过，我就告诉你：");

        //p2=(int)p1/10;
        // 这句的p1没有初始化。这样导致p2和p1总是为0

        write(CHINESE_D->chinese_number(p1)+"十"+CHINESE_D->chinese_number(p2));
        write("把\n宝剑，就是绝世好剑。你只要输入“press ***”就行！\n");
                 me->delete("tmark/ling");
                 me->set("tmark/ling",1);
                me->start_busy(2);
                return 1;
    }
}
