#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"帛卷"NOR, ({ "bo juan", "bojuan", "book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "一本帛制长卷，质地柔软坚韧，不知道什么材质织成，正是逍遥派无崖子所藏秘籍。\n"); 
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

	if (me->query("quest/天龙八部/武功/pass") && me->query("quest/天龙八部/北冥神功/pass") )
		return notify_fail("帛卷中所记载的内容对你来说已经了然于胸了。\n");

       if (me->query_temp("find") < 8 ){
              write("你缓缓展开帛卷，只见里面密密麻麻的都是一些图形和文字，正是逍遥无崖子所藏的武功秘籍。\n");
              me->add_temp("find", 1);         
              return 1;
         }
  
write("你仔细翻看着帛卷里所记的逍遥派武学，武学修为大有进展。\n");

   if(   (random(me->query("kar"))+random(me->query("int"))) > 30
           && (random(me->query("dex"))+random(me->query("int"))) > 30
           && random(me->query("kar")) <31
           && random(me->query("kar"))> 20 )
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
         me->set_skill("lingbo-weibu",1);
	  log_file("quest/lbwb", sprintf(HIR"%s(%s) 通过无崖子秘籍学会凌波微步。富源：%d；经验：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
  }

 if(   random(me->query("kar"))>20
        && me->query("kar") <31 
        && random(me->query("pur") )>20
        && me->query("pur") <31
      && ( random(5) ==1 ||( me->query("buyvip")&& random(3)==1 ) )
 ) { 
       tell_object(me,HIC"你战战兢兢的打开绸包，里面是个卷成一卷的帛卷展将开来，\n"+
                        "第一行写着“北冥神功”。字迹娟秀而有力，便与绸包外所书\n"+
                        "的笔致相同。其后写道：“庄子‘逍遥游’有云：‘穷发之北\n"+
                        "有冥海者，天池也。有鱼焉，其广数千里，未有知其修也。’\n"+
                        "又云：‘且夫水之积也不厚，则其负大舟也无力。覆杯水于坳\n"+
                        "堂之上，则芥为之舟；置杯焉则胶，水浅而舟大也。’是故本\n"+
                        "派武功，以积蓄内力为第一要义。内力既厚，天下武功无不为\n"+
                        "我所用，犹之北冥，大舟小舟无不载，大鱼小鱼无不容。是故\n"+
                        "内力为本，招数为末。以下诸图，务须用心修习。”\n\n"NOR);

       me->set("quest/天龙八部/北冥神功/pass",1);
      if(!me->query_skill("beiming-shengong")) 
                 me->set_skill("beiming-shengong",1);
          
          message_vision(HIC"\n你的「北冥神功」进步了！”\n"NOR,me); 
          message_vision(HIC"\n你俨然已参透了帛卷中的武功绝学，以后就要靠你自己练习了！”\n"NOR,me); 
      me->start_busy(2);
      me->set("quest/天龙八部/北冥神功/time", time());
      me->set("quest/天龙八部/北冥神功/combat_exp",me->query("combat_exp"));
     if(!me->query_skill("beiming-shengong"))  me->set_skill("beiming-shengong",1);
     log_file("quest/bmsg", sprintf(HIR"%s(%s) 通过无崖子秘籍学会北冥神功。富源：%d；经验：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
    }

  else
  {
	  tell_object(me,HIY"\n你翻到最后发现帛卷已经过于陈旧，什么都看不清了，只得作罢。无法从里面学到东西。\n"NOR);
	  log_file("quest/lbwb", sprintf("%s(%s) 试图阅读无崖子秘籍失败。经验：%d。富源：%d。\n", me->name(1),me->query("id"), me->query("combat_exp"),me->query("kar")) );
	  tell_room(environment(me),HIY""+me->name()+"懊恼之下,顺手将帛卷扔到了地下。\n"NOR, ({}));
	  me->start_busy(2);

  }
message_vision(HIC"\n你还待翻阅，却发现帛卷因为过于陈旧，已经化为飞灰，不复辨识了。！”\n"NOR,me); 
       destruct(this_object()); 
	return 1;	    

}


