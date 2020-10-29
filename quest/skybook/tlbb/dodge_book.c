//By Spiderii@ty 从新编写,彻底完善
// By Spiderii@ty 加入天赋系统

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"帛卷"NOR, ({ "bo juan", "bojuan", "book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "一本烂的不成样子的帛制长卷。\n"); 
                set("unique", 1);
                set("treasure", 1);
                set("material", "silk");
                set("no_give", "这样东西不能离开你。\n");
                set("no_get", "这样东西不能离开那儿。\n");
        }
}
void init()
{
             add_action("do_du", "read");
     	      add_action("do_fan", "fan");	
      	      add_action("do_fan", "find");
}

int do_fan(string arg)
{
	object obj,me = this_player();        		       
	if (!(arg=="bo juan" || arg == "bojuan" || arg == "book")) return 0;
	if ( me->is_busy()) 
		return notify_fail("你现在正忙着呢。\n");
	if( me->is_fighting() ) 
		return notify_fail("你无法在战斗中做这个事情。\n");
	if (!id(arg))
		return notify_fail("你要翻什么？\n");
	if(this_object()->query("owner")!=me->query("id"))
		return notify_fail("你哪里来的这个东西啊。\n");
	if (me->query("quest/天龙八部/武功/pass"))
		return notify_fail("帛卷中所记载的内容对你来说已经了然于胸了。\n");
              
       if (me->query_temp("find") < 8 ){
              write("你仔细翻看着被撕的破烂的帛卷，希望能从中找出点什么。\n");
              me->add_temp("find", 1);         
              return 1;
         }
  //难度系数加大,毕竟是sj第一dodge
  if((random(me->query("kar"))+random(me->query("int"))) > 38
           && (random(me->query_dex(1))+random(me->query_int(1))) > 60
         && random(me->query("kar")) <31
           && random(me->query("kar"))>25
           && ((!me->query("buyvip")&&random(5)==1)||(me->query("buyvip")&&random(4)==1)))
  {
	  tell_object(me,HIG"你翻到最后，不由得大为狂喜，这部分并没有被撕烂，题着“凌波微步”四字。\n"NOR);
	  tell_object(me,HIG"其后绘的是无数足印，注明“妇妹”、“无妄”等等字样，尽是易经中的方位。\n"NOR);
         tell_object(me,HIG"只见足印密密麻麻，不知有几千百个，自一个足印至另一个足印均有绿线贯串。\n"NOR);
	  tell_object(me,HIG"线上绘有箭头，料是一套繁复的步法。最后写着一行字道：“猝遇强敌，以此。\n"NOR);
	  tell_object(me,HIG"保身，更积内力，再取敌命。\n"NOR);
	  me->set("quest/天龙八部/武功/pass",1);
         me->set("quest/天龙八部/武功/read", 1);
         me->delete_temp("find");
	  me->start_busy(2);
	  log_file("quest/lbwb", sprintf(HIR"%s(%s) 学会凌波微步。富源：%d；经验：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
  }
  else
  {
	  tell_object(me,HIY"\n你翻到最后发现帛卷撕的乱七八糟，什么都看不清，根本无法从里面学到东西。\n"NOR);
	  log_file("quest/lbwb", sprintf("%s(%s) 试图解开凌波微步失败。经验：%d。富源：%d。\n", me->name(1),me->query("id"), me->query("combat_exp"),me->query("kar")) );
	  tell_room(environment(me),HIY""+me->name()+"懊恼之下,顺手将帛卷扔到了地下。\n"NOR, ({}));
	  me->start_busy(2);
	  destruct(this_object()); 
  }
	return 1;	    
}
int do_du(string arg)
{
        object me = this_player();
        if (!(arg=="bo juan" || arg == "bojuan" || arg == "book"))
        return 0;
        if( me->is_busy()) 
            return notify_fail("你现在正忙着呢。\n");
        if( me->is_fighting() ) 
            return notify_fail("你无法在战斗中专心下来研读新知！\n");
        if(!id(arg))
             return notify_fail("你要读什么？\n");
	 if (!me->query("quest/天龙八部/武功/pass"))
             return notify_fail("帛卷撕的乱七八糟，什么都看不清，你无法从里面学到东西。\n");
        if (!me->query("quest/天龙八部/武功/read"))
             return notify_fail("帛卷撕的乱七八糟，什么都看不清，你无法从里面学到东西。\n");
	 if((int)me->query("jing") < 25 )
             return notify_fail("你现在过于疲倦，无法专心下来研读新知。\n");        
	 if((int)me->query("neili") < 35 )
             return notify_fail("你内力不够，无法专心下来研读新知。\n");        
        if((int)me->query_int() < 34)
             return notify_fail("你的悟性不足钻研这么高深的武功。\n");
        if((int)me->query_skill("literate", 1) < 100)
             return notify_fail("你看不懂这上面所写的文字。\n"); 
        if((int)me->query("max_neili") < 1200 )
             return notify_fail("你内力修为不够，无法钻研这么高深的武功。\n");
        if((int)me->query("combat_exp")< 200000)
             return notify_fail("你的实战经验不够，无法钻研这么高深的武功。\n"); 
        if( me->query_skill("lingbo-weibu", 1) > 180)
	     return notify_fail("你研读了一会儿，觉得书上讲的步法，如果不身体力行的练习是无法领会的。\n");
        //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了凌波微步的精华所在。\n"NOR);
            me->set_skill("lingbo-weibu",180);
            }

          me->receive_damage("jing", 15);
          me->add("neili",-(int)me->query_skill("lingbo-weibu", 1)/2);  
          me->improve_skill("lingbo-weibu", (int)me->query_skill("literate", 1)/3+1);
          write("你仔细研读着帛卷上的步法。\n");
        
         return 1;
}

