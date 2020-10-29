//meipo.c

#include <ansi.h>
inherit NPC;

string ask_hunyin();

void create()
{
      set_name("媒婆",({"meipo", "mei po", "po", "mei"}));
      set("age", 65);
      set("gender", "女性");
      set("nickname", "姻缘天定");
      set_skill("unarmed", 40);

      set("inquiry",([
            "介绍对象" :  (: ask_hunyin :),
      ]));

        set("chat_chance", 15); 
        set("chat_msg", ({ 
                "花媒婆神秘兮兮的说道：据说灵山上有传说中的雪莲花，那可是送给心上人最好的礼物哦。\n",
                "花媒婆讪讪的说：这个～～他是个瘸子，老婆子我可没说他不是啊，这嫁都嫁了，还能怪我？\n",
                "花媒婆偷偷一笑：这雪莲花戴上了真是花容月貌啊，我老婆子可要想个法子留下，不能就这么给了那小娘子。\n"
        }) ); 

      setup();
      carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
      object ob;

      ::init();

      if (interactive(ob=this_player())&&!is_fighting())
      {
           remove_call_out("greeting");
           call_out("greeting", 1, ob);
      }
      add_action("do_agree", "agree");
}

void greeting(object ob)
{
      if (!ob||environment(ob)!=environment())   return;
      if( query("age", ob) >= 18 && !query("couple", ob) )
      {
           if( query("gender", ob) == "无性" )
           {
                 message_vision("$N对$n摇头叹道：可惜是个太监，不然也到" +
                                "娶媳妇的时候了。\n", this_object(), ob);
                 return;
           }

           if( query("gender", ob) == "男性" )
           {
                 if( query("per", ob)<20 )

                 message_vision("$N看见$n，吓了一跳：这位公子可是要老婆子" +
                                "给你介绍对象？难哪！\n", this_object(), ob);
                 else

                 message_vision("$N凑上前对$n道：公子一表人材，可要老婆子" +
                                "给你介绍对象？\n", this_object(), ob);
                 return;
           }

           if( query("gender", ob) == "女性" )
           {
                 if( query("per", ob)<20 )

                 message_vision("$N看见$n，叹了口气：这位姑娘虽不愁嫁，可要找" +
                                "个好人家却非易事！\n", this_object(), ob);
                 else

                 message_vision("$N凑上前对$n道：好俊俏的人儿，可要老婆子" +
                                "给你介绍对象？\n", this_object(), ob);
                 return;
           }
      }
      return;
}

string ask_hunyin()
{
      object *list = users();
      object ob = this_player();
      string who,gender=query("gender", ob);
      int i, p;

      if (gender == "无性")
           return "你个死太监，还想找对象结婚害人？";

      if( query("couple", ob) )
           return "你都是结了婚的人了, 还找什么对象？";

      if( query("age", ob)<18 )
           return "这么小就想找对象啦，嘻嘻。\n";

      if( query_temp("mameipo/agree", ob) )
           return "怎么？"+query_temp("mameipo/agree", ob)+
                  "还没有答应你这门亲事吗？\n";

      i = 0;
      while ( i <sizeof(list))
      {
           if( query("gender", list[i]) == gender || 
               query("gender", list[i]) == "无性" || 
               query("age", list[i])<18 || 
               query("age", list[i])>query("age", ob)+5 || 
               query("age", list[i])<query("age", ob)-5 || 
               query("class", list[i]) == "bonze" || 
               query("couple", list[i]) )
           list[i] = 0;
           i++;
      }

      list -= ({ 0 });
      if ( sizeof(list) > 0 )
      {
           p = random(sizeof(list));
           who=query("id", list[p]);
           set_temp("mameipo/who", who, ob);
           return "看来"+query("name", list[p])+"("+query("id", list[p])+")"+
                  "和你很相配，你意下如何？(agree)\n";
      }
      else   return "暂时还找不到与你相配的人。";
}

int do_agree()
{
      object who, ob = this_player();

      if( !query_temp("mameipo/who", ob) )
      {
           tell_object(ob, "花媒婆对你道：你是想老婆子给你介绍对象么？\n");
           return 1;
      }

      tell_object(ob, HIC"花媒婆对你道：既如此，老婆子就给你把这好事儿跟对方说说。\n"NOR);
      who=find_player(query_temp("mameipo/who", ob));
      if (!who)
      {
           tell_object(ob,HIC"花媒婆对你道：可惜，现在老婆子找不到你的意中人。\n"NOR);
           return 1;
      }

      tell_object(who,query("name", ob)+"托花媒婆给你送来朵"+HIR+"红玫瑰"NOR+"。\n");
      command("tell"+query_temp("mameipo/who", ob)+""+query("name", ob)+"("+
              query("id", ob)+")对你很有意思，托老婆子给你说说。\n");
      new("/d/city/obj/rrose")->move(who);
      tell_object(ob, HIC"花媒婆对你道：老婆子已经把你的意思转告了，你这就去提亲吧。\n"NOR);
      delete_temp("mameipo/who", ob);
      set_temp("mameipo/agree",query("name",  who)+"("+query("id", who)+")", ob);
      return 1;
}
