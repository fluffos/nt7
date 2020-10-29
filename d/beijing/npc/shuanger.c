#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
int ask_go();
int ask_kiss();
int do_chase();
void create()
{
        set_name("双儿", ({ "shuang er", "shuang","er"}));
        set("title", HIW "天下无双" NOR);
        set("nickname", HIM "大功告成" NOR);
        set("gender", "女性");
        set("age", 15);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 15);
        set("int", 25);
        set("con", 25);
        set("dex", 30);
        set("per", 27);
        
        set("max_qi", 500);
        set("max_jing", 200);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 50);
        set("combat_exp", 50000+random(10000));
        set("score", 20000);
        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("unarmed", 80);
        set_skill("sword", 80);
        set_skill("taiji-jian", 70);
        set_skill("taiji-quan", 70);
        set_skill("tiyunzong",50);
        map_skill("dodge", "tiyunzong");
          map_skill("parry", "taiji-jian");
          map_skill("sword", "taiji-jian");
          map_skill("unarmed", "taiji-quan");
        set_temp("apply/attack", 15);
        set_temp("apply/attack", 15);
        set_temp("apply/damage", 15);
       set("inquiry", ([
            "你愿不愿意跟我走" : (: ask_go :),
            "大功告成" :  (: ask_kiss :),
        ]));
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth")->wear();
}
int init()
{
       add_action("do_attack","attack");
       add_action("do_stop","stop");
       add_action("do_send","sendto");
       add_action("do_sha","sha");
}
int ask_kiss()
{
  object me;
  string host_id;
  me=this_player();
  if(query("id")!="shuang er")
        {
         sscanf(query("id"),"%s's shuang er",host_id);
         if( query("id", me) == host_id )
           {
           if(random(10)<1)               
           {
           say(query("name")+"满脸羞得通红,垂下头来,缓缓的点了点头.\n");
           addn("combat_exp",2000);
           }            
           else 
           say(query("name")+"啊的一声,一下子跳将开去,说:不嘛,不要.\n");
           return 1;
           }
        }
    say(query("name")+"说道:呸,我不干!\n");
return 1;
}
int ask_go()
{
  object me;
  string new_name,new_id,host_id;
   me=this_player();
           if(query("id")!="shuang er")
        {
                 sscanf(query("id"),"%s's shuang er",host_id);
                 if(query("id")==host_id)
           {say(query("name")+"睁大眼睛看了看"+
                                query("name", me)+"，说:当然愿意啦,我都听你的。\n");
            return 1;
           }
         if( query("id", me) != host_id )
           {say(query("name")+"睁大眼睛看了看"+
                                query("name", me)+"，说:不行的,我得听我主人的。\n");
                        return 1;
           }
         }
         if( query("weiwang", this_player()) >= 70 && query_temp("zhuang_liwu", this_player()) )
           {
           write( HIY "双儿道:夫人待我恩重如山,主人对我庄家又有大恩。\n" NOR);
           write( HIY "夫人要我服侍主人,我一定尽心。\n" NOR);
           command("nod");      
           set_leader(me);
       new_name=query("name", me)+"的丫环双儿";
       new_id=query("id", me)+"'sshuanger";
       set("name",new_name);
       set("id",new_id);
           tell_object(me, "可用指令:\nattack sb 攻击某人.\nsha sb 杀死某人.\nstop 停止战斗.\nsendto sb.--把双儿送给sb.\n");
           set("long","这是"+new_name+"。\n"
                "她是一个十分清秀的少女,大约十四五岁年纪;\n"
                "一张雪白的脸庞,眉弯嘴小,笑靥如花,正笑嘻嘻地看着你。\n");
        call_out("do_chase",5);
       }
           else say(query("name")+"睁大眼睛看着"+query("name", me)+"，说:不行的,夫人没有同意。\n");
        return 1;
}
int do_chase()
{
        object dest=this_object();
        object me=query_leader();
        if( !objectp(me) || me->is_ghost() ){
           set_leader(0);
                return 1;
        }
        if( !living(me) || !living(dest) || query("no_fight", environment()) || query("fight_room", environment())){
                call_out("do_chase", 5);
                return 1;
        }
        if ( environment(me)==environment(dest) )      
        {
                call_out("do_chase", 5);
                return 1;
        }
        message_vision("$N急急忙忙地跑开了！\n",this_object());
        dest->move(environment(me));
        message_vision("$n急急忙忙的追上来，撅起小嘴：“$N别跑这么快，我有点累呢！\n" NOR, me,this_object());
        call_out("do_chase", 5);
         return 1;
}
int do_attack(string arg)
{
  object ob; 
  string host_id;
  object me=this_player();
  if(query("id")=="shuang er")
   {say("你无权使用此命令。\n");
    return 0;}
  sscanf(query("id"),"%s's shuang er",host_id);
  if( query("id", me) != host_id )
  return notify_fail("双儿连理都不理你！\n");
  if(!arg||!objectp(ob=present(arg,environment(me))))
        return notify_fail("双儿傻傻地望着你，不明白你的意思。\n");
  if (userp(ob)) return notify_fail("双儿脸庞憋的通红的说：对不起，我不能杀玩家的！\n");
  if( environment() && query("no_fight", environment()))return notify_fail("双儿小心翼翼的看了你一眼说：这里是安全区啊！\n");
  if(!living(ob)) 
         return notify_fail("双儿说:"
              +query("name", ob)+"已经这样啦你还要...??!!\n");
  message_vision("双儿对主人$N点头道: 嗯,好的.\n",me);
  fight_ob(ob);
  return 1;
}
int do_stop()
{
   string host_id;
  object me=this_player();
  if(query("id")=="shuang er")
   return notify_fail("你无权使用此命令。\n");
  sscanf(query("id"),"%s's shuang er",host_id);
  if( query("id", me) != host_id )
   return notify_fail("双儿连理都不理你！\n");
 if(!is_fighting())
         return notify_fail("双儿现在没和人打斗.\n");
 command("halt");
 message_vision("双儿对主人$N微微一笑。\n",me);
 return 1;
}
int do_send(string arg)
{
  object ob; string host_id,new_name,new_id;
  object me=this_player();
  if(query("id")=="shuang er")
   return notify_fail("你无权使用此命令。\n");
  sscanf(query("id"),"%s's shuang er",host_id);
  if( query("id", me) != host_id )
   return notify_fail("双儿连理都不理你！\n");
  if(!arg||!objectp(ob=present(arg,environment(me))))
        return notify_fail("你要把双儿送给谁？\n");
  if(!living(ob) || !userp(ob)) 
         return notify_fail("你只能把双儿给活人!\n");
 message_vision("双儿眼泪汪汪地望着主人$N，说:\n主人待我好,是我命好;主人待我不好,是我命苦罢了.\n",me);
 set_leader(ob);
 new_name=query("name", ob)+"的丫环双儿";
           set("long","这是"+new_name+"。\n"
                "她是一个十分清秀的少女,大约十四五岁年纪;\n"
                "一张雪白的脸庞,眉弯嘴小,却象是刚受人欺负,眼泪汪汪地看着你。\n");
 new_id=query("id", ob)+"'sshuanger";
 set("name",new_name);
 set("id",new_id);
 write(HIY"双儿对新主人"+query("name", ob)+"楚楚可怜地盈盈一拜。\n"NOR);
 tell_object(ob,"可用指令:\nattack sb 攻击某人.\nsha sb 杀死某人.\nstop 停止战斗.\nsendto sb.--把双儿送给sb.\n");
 return 1;
}
int do_sha(string arg)
{
        object me,ob;
        me = this_object();
        if(!arg||!objectp(ob=present(arg,environment(me))))
        return notify_fail("你要双儿杀谁？\n");
        if( !query("no_fight", environment(ob)) )
        {
        message_vision("双儿对$N点头说道: 嗯,好的.\n",this_player());
        command("say 哼,主人要我杀了你!");
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob); 
        }
        return 1;
}       
int return_home(object room)
{
        if (query_leader())
                return 1;
        ::return_home(room);
}
