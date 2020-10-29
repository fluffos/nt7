// lengyue_dao.c 冷月宝刀
#include <ansi.h>
#include <weapon.h>
inherit BLADE;
inherit F_UNIQUE;
#define QUESTDIR5 "quest/雪山飞狐/宝藏/"
#define QUESTDIR4 "quest/雪山飞狐/武功/"

void create()
{
        set_name( HIB"冷月宝刀"NOR , ({ "lengyue dao","lengyue baodao","baodao","lengyue","blade","dao"}));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIB"刀光如水，在冷月下流转不定。刀柄上用金丝银丝镶着一钩眉毛弯月。\n"NOR);
                set("value", 1);
                set("unique", 1);
                set("rigidity", 4);
                set("sharpness", 4);
                set("weapon_prop/parry", 4);
                set("wield_maxneili", 1400);
                set("treasure",1);
                set("wield_str", 24);
                set("material", "steel");
                set("wield_msg", HIB"$N缓缓抽刀出鞘，冷森森的一道青光激射而出，眨眼之间，手中已多了一柄寒气逼人的长刀。\n"NOR);
                set("unwield_msg",HIB"$N将冷月宝刀小心的收起，耀人的寒光没入刀鞘。\n"NOR);
        }
        init_blade(120);
        setup();
}
void init()
{
	if (environment()==this_player()&&!this_player()->query_condition("killer"))
	{

		add_action("do_yanjiu",({"yanjiu", "研究"}));
		add_action("do_guanzhu",({"guanzhu", "灌注"}));
		add_action("do_search",({"search", "寻找"}));
	}
}
int wield()
{
	  object me = environment();
      object ob = this_object();
	  int i=::wield();
          if(clonep() && i &&  objectp(me) && userp(me) && me->query(QUESTDIR4+"hujiadaofa")&&!me->query_temp(QUESTDIR4+"lengquan"))
	  {
     	   message_vision(HIW"\n$N将"+ob->query("name")+HIW"拿起，突然"+ob->query("name")+HIW"闪出耀眼的白光！\n"NOR,me);
     	   tell_object(me,HIB"突然从刀身传来一股真力，瞬间你感觉七筋八脉全然贯通一气。\n"NOR);
           me->set_temp(QUESTDIR4+"lengquan",1);
	   }
	   if(i) return i;
	   else return 0;
}

int unequip()
{
	  object me = environment();
  	  int i=::unequip();
          if(clonep() && objectp(me) && userp(me)  && me->query_temp(QUESTDIR4+"lengquan") && i )
           me->delte_temp(QUESTDIR4+"lengquan");
	   if(i) return i;
	   else return 0;
}
int do_yanjiu(string arg)
{
     	object me, obj;
     	me = this_player();
            obj = this_object();
     	if(me->is_busy()) return 0;
     	if(!me->query(QUESTDIR5+"start")) return 0;
     	if(me->query("neili") < 200)  return notify_fail("你内力不够。\n");
     	if(!present("baozang tu",me)) return notify_fail("一把破刀你研究什么？\n");
        if( ! arg || (arg != "lengyue baodao"&& arg != "baodao"&& arg != "lengyue"))
                return notify_fail("你要研究什麽？\n");
        if(me->query_temp(QUESTDIR5+"yanjiu_ok"))
     			return notify_fail("你已经发现刀身上的脉路，你可以尝试对照藏宝图！\n");
     	if(me->query(QUESTDIR5+"time")&&time()-me->query(QUESTDIR5+"time")<84600)
     			return notify_fail("你感觉全身气血翻腾，看来刚才的研究已经大伤你的精神！\n");
     	if(me->query(QUESTDIR5+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR5+"combat_exp")<500000)
     			return notify_fail("你感觉全身气血翻腾，看来以你当前的功力无法继续研究！\n");

	   me->start_busy(1);
       message_vision(HIC"$N将"+this_object()->name()+HIC"翻来覆去地研究着！\n"NOR, me);
       me->add("neili", -150);
       me->add_temp(QUESTDIR5+"yanjiu",1);
      if(me->query_temp(QUESTDIR5+"yanjiu")>6)
      {
      	me->set(QUESTDIR5+"time",time());
      	me->set(QUESTDIR5+"combat_exp",me->query("combat_exp"));
      	tell_object(me,YEL"你发现"+obj->name()+YEL"刀身上刻有着数条脉路，似乎和藏宝图可以对照。\n"NOR);
		tell_object(me,YEL"你感觉全身气血翻腾，看来刚才的研究只怕已经大伤你的精神！\n"NOR);
      	me->set_temp(QUESTDIR5+"yanjiu_ok",1);
      	me->delete_temp(QUESTDIR5+"yanjiu");
      }
     	return 1;
}
int do_guanzhu(string arg)
{
     	object me, obj;
     	string force;

     	me = this_player();
     	obj = this_object();
     	if(me->is_busy()) return 0;
     	if(!me->query(QUESTDIR5+"start")) return 0;
        if( ! arg || (arg != "lengyue baodao"&& arg != "baodao"&& arg != "lengyue"))
                return notify_fail("你要干什麽？\n");
        if(me->query_temp(QUESTDIR5+"guanzhu_ok"))
     			return notify_fail("你已经灌注了内力，刀身上的脉路更加清晰！\n");
        if(!stringp(force = to_chinese(me->query_skill_mapped("force"))))
      		return notify_fail("你没有激发内功如何灌注内力！\n");
     	if(me->query("neili") < 200)  return notify_fail("你内力不够。\n");

		message_vision(HIC"$N默运"+force+HIC"，慢慢地将内力灌注到"+obj->name()+HIC"中，突然"+obj->name()+HIC"闪出耀眼的白光！\n"NOR, me);
        tell_object(me,HIY"你仔细观察"+obj->name()+HIY"，发现脉路更加清晰。\n"NOR);
     	me->add("max_neili", -10);
     	tell_object(me,HIB"只是，你感到有些内力不适，怕是这次灌注已经大伤你的内功修为。\n"NOR);
     	me->set_temp(QUESTDIR5+"guanzhu_ok",1);
	    me->start_busy(2);
     	return 1;
}
int do_search()
{
     object me, obj;
     me = this_player();
     if(!me->query(QUESTDIR5+"start")) return 0;
     if(!present("baozang tu",me)) return 0;
     if(!me->query_temp(QUESTDIR5+"map_where")) return 0;
     if(me->is_busy()) return 0;
     if(me->is_fighting()) return 0;
     if(me->query_temp(QUESTDIR5+"search_ok"))
     	return notify_fail("你已经发现找到藏宝地址了！\n");
     if((string)file_name(environment(me))!=me->query_temp(QUESTDIR5+"map_where"))
	    return notify_fail(HIW"你绕着"+environment(me)->query("short")+HIW"走了一圈，这里没有宝藏！\n"NOR);
     me->start_busy(2);
     if(random(2)) message_vision(HIW"$N绕着"+environment(me)->query("short")+HIW"走来走去，仔细观察着什么！\n"NOR, me);
	 else message_vision(HIW"$N似乎发现"+environment(me)->query("short")+HIW"一些什么特别的地方，绕着"+environment(me)->query("short")+HIW"走来走去！\n"NOR, me);
     me->add_temp(QUESTDIR5+"search",1);

      if(me->query_temp(QUESTDIR5+"search")==4||me->query_temp(QUESTDIR5+"search")==8)
      {
      	me->set(QUESTDIR5+"time",time());
      	me->set(QUESTDIR5+"combat_exp",me->query("combat_exp"));
      	obj=new("/d/xingxiu/baozang/npc/gaoshou");
      	obj->set("kill_id",me->query("id"));
        obj->set("fight_id",me->query("id"));
      	if(me->query_temp(QUESTDIR5+"search")==4) obj->set("title",HIB"黑风寨三当家"NOR);
      	else obj->set("title",HIB"黑风寨寨主"NOR);
      	obj->move(environment(me));
        message_vision(HIC"突然从角落里跳出一个人，$n对着$N嚷道：“我就是"+obj->query("title")+HIC"，赶快离开"+environment(me)->query("short")+HIC"。”\n"NOR, me,obj);
      	if(me->query_temp(QUESTDIR5+"search")==8)
      	{
      	    obj=new("/d/xingxiu/baozang/npc/gaoshou");
      	    obj->set("kill_id",me->query("id"));
            obj->set("fight_id",me->query("id"));
      	    obj->set("title",HIB"黑风寨二当家"NOR);
      	    obj->move(environment(me));
            message_vision(HIC"跟着又出来一个人，竟然是"+obj->query("title")+HIC"$N，嚷道：“我们老大的话，没听清楚？小子找死。”\n"NOR, obj);
            log_file("quest/FEIHU", sprintf("%s(%s)寻找宝藏的过程中遇到黑风寨寨主。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
      	}
      }
      if(me->query_temp(QUESTDIR5+"search")==12)
      {
      	me->set(QUESTDIR5+"time",time());
      	me->set(QUESTDIR5+"combat_exp",me->query("combat_exp"));
        tell_object(me,YEL"你发现"+environment(me)->query("short")+YEL"似乎正合乎刀身上刻的脉路，你心念一动走到"+environment(me)->query("short")+YEL"的一个角落。\n"NOR);
      	message_vision(HIY"$N意外地发现一个可以通向地下的通道。\n"NOR, me);
        message("channel:rumor", HIW"【谣言】"HIG + "传说在"+environment(me)->query("short")+HIG"，有人找到闯王宝藏的进口！\n"NOR,users() );
        log_file("quest/FEIHU", sprintf("%s(%s)寻找宝藏成功。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
        if( !environment(me)->query("exits/down") ) {
           environment(me)->set("exits/down","/d/xingxiu/baozang/tiantan");
           call_out("close_path", 30,environment(me));
        }
      	me->set_temp(QUESTDIR5+"search_ok",1);
      	me->delete_temp(QUESTDIR5+"search");
      }
     	return 1;
}
void close_path(object ob)
{
        if( !ob->query("exits/down") ) return;
        message("vision",HIR"一阵风吹过，一切都有如往昔，刚才的一切如梦如幻！\n"NOR,ob);
        ob->delete("exits/down");
}
