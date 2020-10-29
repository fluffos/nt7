// chenglingsu
//modified by tangfeng@SJ 2004

inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR3 "quest/雪山飞狐/解药篇/"

string ask_jindi();
int ask_jieyao();
int ask_yaofang();
int ask_qixinghaitang();
int ask_hufei();
void destroying(object obj);
void giveyaofang(object me);

void create()
{
       set_name("程灵素", ({ "cheng lingsu", "cheng" }));
       set("nickname", "药师");
       set("long",
               "她就是药师程灵素。\n"
               "年纪已仅有二十来岁，但是各种药理极为精通。\n");
        set("gender", "女性");
       set("age", 21);
       set("attitude", "friendly");
       set("shen", -3000);
       set("str", 29);
       set("int", 27);
       set("con", 26);
       set("dex", 26);

       set("max_qi", 200);
       set("max_jing", 100);
       set("neili", 1000);
       set("max_neili", 1000);
       set("jiali", 10);
       set("combat_exp", 80000);
       set("no_get",1);
       set("no_bark",1);
       set_skill("force", 60);
        set_skill("yinyun-ziqi", 60);
       set_skill("dodge", 60);
       set_skill("jinshe-zhangfa", 60);
       set_skill("tiyunzong", 60);
       set_skill("strike", 60);
       set_skill("jinshe-jianfa", 60);
       set_skill("parry", 60);
       set_skill("sword", 60);
       set_skill("poison", 160);
       set_skill("medicine", 160);
       set_skill("literate", 120);
        map_skill("force", "yinyun-ziqi");
       map_skill("dodge", "tiyunzong");
       map_skill("strike", "jinshe-zhangfa");
       map_skill("parry", "jinshe-jianfa");
       map_skill("sword", "jinshe-jianfa");
       prepare_skill("strike", "jinshe-zhangfa");

       set("inquiry", ([
                "五毒教" : (: ask_jindi :),
                "解药" : (: ask_jieyao :),
                "药方" : (: ask_yaofang :),
                "治疗" : (: ask_jieyao :),
                "七星海棠" : (: ask_qixinghaitang :),
                "胡斐" : (: ask_hufei :),
                "禁地" : (: ask_jindi :),
                "苗人凤" : "苗大侠武功高强，倒是其次，多年来兴侠仗义尤其佩服！\n",
                "胡一道" : "辽东大侠胡一刀！\n",
       ]));
       setup();
       carry_object("/clone/armor/cloth")->wear();
}
void init()
{
     add_action("do_yes","yes");
     add_action("do_no","no");
}
string ask_jindi()
{
       object applicant;
       object ob;
       int exp;
       applicant=this_player();

        exp=(int)applicant->query("combat_exp",1);
        if(exp<90000)
        return "你就这点功夫，恐怕连五毒教的山也上不去，等几年在说吧！\n";

        if (  present("jiuxuebiyun dan", this_player()) )
        return "我已经给过你了，为何还要向我要？此药很难炼制，不要太贪心！\n";

        if( applicant->query("wudu_jiedu") ){
        ob = new(__DIR__"obj/jxdan1");
        ob->move(applicant);
        message_vision("$N获得一颗九雪碧云丹。\n",this_player());

        return "你上次答应我的事情还没做，怎麽又来要？ 程灵素皱了皱眉，
冷冷的说到：“丹到还有一颗，你要就拿去吧。\n";
        }

         applicant->set_temp("marks/程",1);
         return "五毒教的禁地种满了各种奇花异草，其中大部分具有巨毒，如果一旦随着
空气吸入体中，必将中毒而死。如果你想去五毒教，我这里有颗丹药可抵制其毒。你如能
进去帮我寻得雪蛛，我愿将此药赠于你，你考虑一下，是否答应(yes)或者不答应(no)我。\n";


}
int do_yes()
{

   object jxdan, me, ob;
   me = this_object();
   ob = this_player();

   if(!ob->query_temp("marks/程")) return 0;
        jxdan = new(__DIR__"obj/jxdan");
   ob->set("wudu_jiedu", 1);
   ob->delete_temp("marks/程");
   jxdan->move(this_player());
   message_vision("$N获得一颗九雪碧云丹。\n",this_player());
   message_vision("$N对你微微一笑，说道：祝你此行顺利。另外希望你能言而有信。\n",me, this_object());
   return 1;
}
int do_no()
{
   object me = this_player();
   if(!me->query_temp("marks/程")) return 0;
   message_vision("程灵素无奈的一笑，说到，既然你不能答应我的要求，丹药自然不能给你。\n",me);
   me->delete_temp("marks/程");

   return 1;
}
int accept_object(object who, object ob,object me)
{
	 if(who->query_condition("killer"))
	 {
	   command("shake "+who->query("id"));
     command("say 你目前被官府通缉，我如何敢受"+ob->name()+"！");
	   return 0;
	 }
	 if(ob->query("id")=="qixing haitang" )
   {
   	 command("ah "+(string)who->query("id"));
     if(who->query_temp(QUESTDIR3+"qixinghaitang") && who->query(QUESTDIR3+"start")&& ob->query("owner")==who->query("id"))
     {
     	command("nod "+(string)who->query("id"));
     	command("say 就是它！但是要想制造解药，还需要一种东西，它就生长在五毒教，一种蓝色的药花。");
     	who->set_temp(QUESTDIR3+"jieyao2",1);
     	who->delete_temp(QUESTDIR3+"qixinghaitang");
     }
     else  command("thank "+(string)who->query("id"));
   }
   else if(ob->query("id")=="lanse yaohua")
   {
   	 command("ah "+(string)who->query("id"));
     if(who->query_temp(QUESTDIR3+"jieyao2") && who->query(QUESTDIR3+"start")&& ob->query("owner")==who->query("id"))
     {
     	command("nod "+(string)who->query("id"));
     	command("say 就是它！稍微等我一下，我马上就好。\n");
     	tell_object(who,HIC"程灵素开始制起解药，从程序上看，只要药物齐全，似乎不是很复杂。\n\n"NOR);
	    tell_room(environment(who),HIC"\n程灵素转过身，似乎开始制造解药。\n"NOR, ({ who }));
     	who->set_temp(QUESTDIR3+"getjieyao",1);
     	who->delete_temp(QUESTDIR3+"jieyao2");
     	who->start_busy(4);
      remove_call_out("giveyaofang");
      call_out("giveyaofang",10, who);
     }
     else  command("thank "+(string)who->query("id"));
   }
   else if (ob->query("id") == "xue zhu" )
   {
   	 command("thank " + who->query("id"));
     command("say 你果然言而有信，下次你要再去五毒教来找我吧。\n");
     who->delete("wudu_jiedu");
   }
   else
   {
     command("? "+(string)who->query("id"));
   }
   call_out("destroying", 1, ob);
   return 1;
}
void destroying(object obj)
{
        if(!userp(obj)) destruct(obj);
        return;
}
void giveyaofang(object me)
{
      object obj;
      if(!me) return;

      obj=new("/d/miaojiang/npc/obj/yaofang");
      if(!obj) return;
      if(!me->query_temp(QUESTDIR3+"getjieyao")) return;
	    if(environment(me)!=environment(this_object()))
 	    {
 	    	command("say 人呢？难道不要解药了？");
       	me->delete_temp(QUESTDIR3+"getjieyao");
 	    	return;
 	    }
     	command("nod "+(string)me->query("id"));
     	command("say 等着急了吧。这是药方，你可以使用内屋那个药炉制作。");
      obj->move(me);
      tell_object(me,HIC"程灵素给你一份"+HBCYN"药方"NOR+HIC"。\n"NOR);
            tell_room(environment(me),HIC"\n程灵素交给"+me->query("name")+"一张纸。\n"NOR, ({ me }));
  	  if(!present("qixing haitang",me))
  	  {
  		  obj=new("/d/miaojiang/npc/obj/qixinghaitang");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一份"+HBCYN"七星海棠"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("lanse yaohua",me))
  	  {
  		  obj=new("/d/miaojiang/npc/obj/lanseyaohua");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一朵"+HBCYN"蓝色药花"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("ren shen",me))
  	  {
  		  obj=new("/clone/medicine/drug/renshen.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一棵"+HBCYN"人参"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("jinyin hua",me))
  	  {
  		  obj=new("/clone/medicine/drug/hua.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一棵"+HBCYN"金银花"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("zang honghua",me))
  	  {
  		  obj=new("/clone/medicine/drug/zanghonghua.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一朵"+HBCYN"藏红花"NOR+HIC"。\n"NOR);
  	  }
      return;
}
int ask_yaofang()
{
	object obj,me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("nod "+me->query("id"));
	  command("say 七星海棠，可称谓天下第一奇草，本身剧毒无比。用这种办法治疗苗大侠也是无奈之举。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")
      && me->query_temp(QUESTDIR3+"getjieyao"))
  {
  	  if(!present("qixing haitang",me))
  	  {
  		  obj=new("/d/miaojiang/npc/obj/qixinghaitang");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一份"+HBCYN"七星海棠"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("lanse yaohua",me))
  	  {
  		  obj=new("/d/miaojiang/npc/obj/lanseyaohua");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一朵"+HBCYN"蓝色药花"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("ren shen",me))
  	  {
  		  obj=new("/clone/medicine/drug/renshen.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一棵"+HBCYN"人参"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("jinyin hua",me))
  	  {
  		  obj=new("/clone/medicine/drug/hua.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一棵"+HBCYN"金银花"NOR+HIC"。\n"NOR);
  	  }
  	  if(!present("zang honghua",me))
  	  {
  		  obj=new("/clone/medicine/drug/zanghonghua.c");
  		  obj->set("no_give",1);
  		  obj->set("no_sell",1);
  		  obj->set("no_drop",1);
  		  obj->move(me);
        tell_object(me,HIC"程灵素给你一朵"+HBCYN"藏红花"NOR+HIC"。\n"NOR);
  	  }

  	if(!present("yao fang",me))
  	{
  		obj=new("/d/miaojiang/npc/obj/yaofang");
  		obj->move(me);
      tell_object(me,HIC"程灵素给你一份"+HBCYN"药方"NOR+HIC"。\n"NOR);
     	command("say 不要再丢了。");
  	}
  	else
  	{
      command("sigh "+me->query("id"));
	    command("say 七星海棠，可称谓天下第一奇草，本身剧毒无比。用这种办法治疗苗大侠也是无奈之举。");
	  }
	  return 1;
  }
  command("say 七星海棠，可称谓天下第一奇草，本身剧毒无比。");
	return 1;
}
int ask_jieyao()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("nod "+me->query("id"));
	  command("say 我想也应该有效地治好苗大侠的病。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"getjieyao"))
  {
	  command("nod "+me->query("id"));
	  command("say 赶快给苗大侠治疗去吧。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao2"))
  {
	  command("nod "+me->query("id"));
	  command("say 除了七星海棠，还需要五毒教一种蓝色药花，我们一起找找看。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"qixinghaitang"))
  {
	  command("nod "+me->query("id"));
	  command("say 快把七星海棠给我。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao1"))
  {
	  command("nod "+me->query("id"));
	  command("say 七星海棠正是这主药之一，可惜被阎基和石万嗔抢走了。你赶快去找回来吧。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
    tell_object(me,HIC"你着急地将苗大侠病情和症状转告给程灵素，应该是断肠草之毒。\n"NOR);
    tell_room(environment(me),HIC"\n"+me->query("name")+"很着急地和程灵素说了些什么。\n"NOR, ({ me }));
	  command("nod "+me->query("id"));
	  command("say 苗大侠也是我敬佩的人，我自当尽力。你说这种毒药的确很凶猛，虽然不是立刻毙命，但是必须使用一种奇草。");
	  command("say 就是剧毒的七星海棠，当年我师傅种植了三棵，只有一颗成熟，可惜被阎基和石万嗔抢走了。你赶快去找回来吧。\n");
	  me->set_temp(QUESTDIR3+"jieyao1",1);
	  return 1;
  }
	command("?");
	command("sorry");
	return 1;
}
int ask_qixinghaitang()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("nod "+me->query("id"));
	  command("say 七星海棠，可称谓天下第一奇草，本身剧毒无比。用这种办法治疗苗大侠也是无奈之举。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")
      && (me->query_temp(QUESTDIR3+"getjieyao")
      ||me->query_temp(QUESTDIR3+"jieyao1")
      ||me->query_temp(QUESTDIR3+"jieyao2")
      ||me->query_temp(QUESTDIR3+"askqixinghaitang"))
      )
  {
	  command("sigh "+me->query("id"));
	  command("say 七星海棠，可称谓天下第一奇草，本身剧毒无比。用这种办法治疗苗大侠也是无奈之举。");
	  return 1;
  }
  command("say 七星海棠，可称谓天下第一奇草，本身剧毒无比。");
	return 1;
}
int ask_hufei()
{
  message_vision(HIC"$N沉默很久道：我不认识这个人......\n"NOR,this_object());
	return 1;
}
