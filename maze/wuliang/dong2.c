// dong2.c
// bbb 1997/07/16
//COOL@SJ,9808
//tangfeng@SJ,2004

#include <ansi.h>
inherit ROOM;

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"
#define QUESTDIR6 "quest/天龙八部/武功/"

string look_yuxiang();
string look_zi();
string look_shoe();
string look_left();
string look_right();
string look_picture();
void dy(object me);

void create()
{
    set("short", "内室");
	set("long", @LONG
眼前突然一亮，一个宫装美女，手持长剑，剑尖对准了你的胸膛。细看之
下，原来是一座玉像(yuxiang)。东壁写了许多字(zi)，笔法飘逸，似以极强
腕力以利器写成，西壁镶了六块大水晶，水晶外绿水隐隐，映得石室中比第一
间石室亮了数倍。
LONG
	);

	set("exits", ([
		"out" : __DIR__"dong1",
	]));

	set("valid_startroom",1);
	
	set("item_desc",([
		"left"		:	(: look_left :),
		"right"	:		(: look_right :),
		"zi"		:	(: look_zi :),
		"yuxiang"	:	(: look_yuxiang :),
		"picture"	:	(: look_picture :),

	]));

	setup();
}


void init()
{
	object me;
    me = this_player();
    
    //通缉犯不可逗留；不过通缉犯能来这里，肯定是巫师帮忙
    if(me->query_condition("killer"))
    {
       message_vision(HIC"\n突然，不知道从哪里传来一个声音道：这里不欢迎$N。\n"NOR,me); 
       tell_object(me,HIR"跟着，不知道哪里来的一只神脚飞起一脚，将你一脚踢飞出去！\n"NOR);
       tell_room(environment(me),HIR"\n不知道哪里来的一只神脚飞起一脚，将"+ me->name()+ "踢飞出去！\n"NOR, ({ me }));
       if(random(2)) me->move("/maze/wuliang/xiaoxi");
       else me->move("/d/xiangyang/conglin3");
       tell_room(environment(me), HIR"\n只见"+ me->name()+ "大叫一声飞过来，摔了个狗吃屎！好帅哦~~~~~~~~\n"NOR, ({ me }));
       me->start_busy(1);
       return;
    }
	if( query(QUESTDIR1+"start", me )
	 && !query(QUESTDIR1+"wuliangover", me )
	 && query_temp(QUESTDIR1+"jianying", me )
	 && !query_temp(QUESTDIR1+"see_duanyu1", me) )
    {      
  	  me->start_busy(2);
  	  remove_call_out("dy");
  	  call_out("dy",1,me);
  	}
  	add_action("do_ketou", "ketou");
  	add_action("do_ketou", "kneel");
  	add_action("do_yanjiu", "yanjiu");
}
void dy(object me)
{
	object obj;
  if(!me) return;
  if(!present(me,this_object())) return;
  if(present("duan yu",this_object()))
  {
  	obj=present("duan yu",this_object());
  	destruct(obj); 
  }
  if( query(QUESTDIR1+"start", me) && !query(QUESTDIR1+"wuliangover", me) && query_temp(QUESTDIR1+"jianying", me) && !query_temp(QUESTDIR1+"see_duanyu1", me) )
  {
      tell_object(me,HIG"\n你伸手推门，眼前陡然一亮，失声惊呼：“啊哟！”眼前一个宫装美女，手持长剑，剑尖对准了他胸膛。你定睛看时，见这女子虽\n"
                          "是仪态万方，却似并非活人，大着胆子再行细看，才瞧出乃是一座白玉雕成的玉像。这玉像与生人一般大小，身上一件淡黄色绸衫\n"
                          "微微颤动；更奇的是一对眸子莹然有光，神彩飞扬。更奇怪的是一对眼珠乃以黑宝石雕成，只觉越看越深，眼里隐隐有光彩流转。\n"
                          "这玉像所以似极了活人，主因当在眼光灵动之故。 \n"NOR);
     obj=new(__DIR__"npc/dy");
     if(!present("qingnian nanzi",this_object()) && !present("duan yu",this_object()))
            obj->move(environment(me)); 
  }  
}
int do_ketou(string arg)
{      
       int time;
	object me,obj;
	me=this_player();
  if(present("duan yu",this_object())) return 0;

	if( !arg || arg != "yuxiang" ) return 0;
	
	if( arg=="yuxiang" ) {
		message_vision("$N口中数着，恭恭敬敬的向玉像磕起头来。\n", this_player());
		if( !query_temp(QUESTDIR1+"lbwb/left", me) || !query_temp(QUESTDIR1+"lbwb/right", me) )
		{
			tell_object(me,"你对着玉像一个头磕下去，似乎发现玉像的左脚(left)、右脚(right)绣得有字。 \n");
			return 1; 
		}
addn_temp(QUESTDIR1+"ketou_trigger", 1, 		me);
	}
	if( query_temp(QUESTDIR1+"ketou_trigger", me) == 16){
delete_temp(QUESTDIR1+"lbwb1", 		me);
delete_temp(QUESTDIR1+"ketou_trigger", 		me);
		if( query(QUESTDIR1+"wuliangover", me) && !query(QUESTDIR6+"yuxiang", me)){
set(QUESTDIR6+"yuxiang", 1, 			me);
		log_file("quest/TLBB",sprintf("%s(%s)玉像处磕头获得武功标志1。经验：%d。\n",me->name(1),query("id", me),query("combat_exp", me)));
		return 1;
		}
		
		if( query(QUESTDIR1+"start", me )
		 && query_temp(QUESTDIR1+"see_duanyu1", me )
		 && !query(QUESTDIR1+"wuliangover", me) )
		{
		   message_vision("$N看见蒲团上的薄草早已破裂，不由伸手进去，里面什么也没有，好象已经被取走了。\n", me);
                  if( !query(QUESTDIR6+"yuxiang", me))log_file("quest/TLBB",sprintf("%s(%s)玉像处磕头获得武功标志1。经验：%d。\n",me->name(1),query("id", me),query("combat_exp", me)));
           set(QUESTDIR6+"yuxiang", 1, me);
           return 1;	
	     }
		if( query(QUESTDIR1+"start", me )
		 && query(QUESTDIR1+"wuliangover", me )
		 && !query(QUESTDIR1+"over", me) )
		{
		   message_vision("$N看见蒲团上的薄草早已破裂，不由伸手进去，里面什么也没有，好象已经被取走了。\n", me);
		   tell_object(me,HIG"虽然什么都没有，你忍不住不住地磕头，看来你已经形似痴狂。\n"NOR);
		   
		   return 1;
		}
		if( query(QUESTDIR1+"start", me )
		 && query(QUESTDIR6+"yuxiang", me )
		 && query(QUESTDIR1+"over", me) )
		{
			if( query(QUESTDIR6+"pass", me) )
			{
				message_vision("$N看见蒲团上的薄草早已破裂，不由伸手进去，里面什么也没有，好象已经被取走了。\n", me);
				tell_object(me,HIG"你虽然已经领悟到了凌波微步，还是忍不住回到这里，看来你已经形似痴狂。\n"NOR);
				return 1;
			}

       //增加时间间隔一天
	if( query(QUESTDIR6+"time", me) && time()-query(QUESTDIR6+"time", me)<86400 )
	     {
		       message_vision("$N看见蒲团上的薄草早已破裂，不由伸手进去，里面什么也没有，好象已经被取走了。\n", me);
	         return 1;
		 }
       //by Spiderii@ty 加入新标记,只为防止以前开lbwb的玩家可以连续fan bojuan
       time=time()-query("quest/天龙八部/武功/time", me);
       if( query("quest/天龙八部/武功/time", me) && time<86400 )
          {
		       message_vision("$N看见蒲团上的薄草早已破裂，不由伸手进去，里面什么也没有，好象已经被取走了。\n", me);
	         return 1;
		 }


       if(present("bo juan",me))
	     {
		       message_vision("$N看见蒲团上的薄草早已破裂，不由伸手进去，里面什么也没有，好象已经被取走了。\n", me);
	         return 1;	
		 }
       //任何人都可以拿到凌波微步秘籍，但是能不能领悟却只有三次机会（非VIP）
       
       obj=new("/d/dali/obj/dodge_book");
         if(!clonep(obj)){
		       message_vision("$N看见蒲团上的薄草早已破裂，不由伸手进去，里面什么也没有，好象已经被取走了。\n", me);
              return 1;
         }
         if(clonep(obj) && obj->violate_unique()){
            destruct(obj);
		       message_vision("$N看见蒲团上的薄草早已破裂，不由伸手进去，里面什么也没有，好象已经被取走了。\n", me);
            return 1;
         } 

	   message_vision(HIR"$N看见蒲团上的薄草早已破裂，不由伸手进去，里面好像什么也没有，$N不甘心又摸索一会，果然找出一个帛卷。\n"NOR, me);
	log_file("quest/TLBB",sprintf("%s(%s)玉像处磕头获得帛卷。\n",me->name(1),query("id", me)));
          set("owner",query("id",  me), obj);//BySpiderii@ty加个标记,防止BUG
	   obj->move(me);	
          set("quest/天龙八部/武功/time", time(), me);//加个限制。禁止连续翻,只为防备以前开lbwb的玩家BySpiderii@ty
	   return 1;
	  }	  
	}
	return 1;
}


string look_left()
{ 
     object me;  
     me=this_player();
     set_temp(QUESTDIR1+"lbwb/left", 1, me);
	return
	 HIC"磕首百遍，供我驱策。\n"NOR;
}

string look_right()
{ 
     object me;  
     me=this_player();
    set_temp(QUESTDIR1+"lbwb/right", 1, me);
	return
	HIY"遵行我命，百死无悔。 \n"NOR;
}

string look_zi()
{
	return
	HIW"洞中无日月，人间至乐也 -- 逍遥子为秋水妹书。\n"NOR;
}

string look_yuxiang()
{    
     object me;  
     me=this_player();
     set_temp(QUESTDIR1+"lbwb/yuxiang", 1, me);
  	return
	HIR"那是一座白玉雕成的玉像，与真人一般大小，身上淡黄绸衫微微颤动，更奇的是一对眸子莹然有光，神采飞扬。\n"NOR;
}

string look_picture()
{    
     object me;  
     me=this_player();
  	return
	HIR"画卷上赫然出现一个横卧的裸女画像，全身一丝不挂，面貌竟与那玉像一般无异。\n"NOR;
}

int do_yanjiu(string arg)
{
	object me = this_player();  
	int time;
	      		       
	if (!(arg=="picture")) return 0;
		
	if ( me->is_busy()) 
		return notify_fail("你现在正忙着呢。\n");
		
	if( me->is_fighting() ) 
		return notify_fail("你无法在战斗中做这个事情。\n");
		

	if( query("quest/天龙八部/北冥神功/pass", me) )
		return notify_fail("你已经完全参透了北冥神功绝学。\n");
		
	if( query("quest/天龙八部/北冥神功/fail", me) >= 3 && query("registered", me)<3 )
		return notify_fail("就你现在的情况，恐怕没有机会领悟无量山中的武功了。\n");
		
		time=time()-query("quest/天龙八部/北冥神功/time", me);
       if( query("quest/天龙八部/北冥神功/time", me) && time<86400 )
		       return notify_fail("你来的也太勤快了些吧。\n");
/*
if( query("quest/天龙八部/北冥神功/combat_exp", me) && query("combat_exp", me)-query("quest/天龙八部/北冥神功/combat_exp", me)<100000 )
	return notify_fail("以你当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。\n");
*/
 if( query("combat_exp", me)<2000000 )
    return notify_fail("你的实战经验不够，无法钻研这么高深的武功。\n"); 
              
  if( random(query("kar", me))>26
        && query("kar", me)<31
        && random(query("pur", me))>25
        && query("pur", me)<31
        && ((!query("buyvip", me) && random(15) == 1) || (query("buyvip", me) && random(12) == 1) )
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
     remove_call_out("beiming1");
     call_out("beiming1", 5, me); 
     me->start_busy(10);
   
}
else
{
		  tell_object(me,HIR"但见帛卷上赫然出现一个横卧的裸女画像，全身一丝不挂，面貌竟与那玉像一般无异。\n"+
		                    "你只觉多瞧一眼也是亵渎了神仙姊姊，急忙掩卷不看。然而你却发现画卷已不知所踵。\n"NOR);
addn("quest/天龙八部/北冥神功/fail", 1, 	me);
	log_file("quest/bmsg",sprintf("%s(%s)试图解开北冥神功失败。经验：%d。富源：%d。\n",me->name(1),query("id", me),query("combat_exp", me),query("kar", me)));
	  me->start_busy(2);
set("quest/天龙八部/北冥神功/time", time(), 	me);
set("quest/天龙八部/北冥神功/combat_exp",query("combat_exp",  me), 	me);
}
	return 1;	
}
void beiming1(object me)
{
  if(!me) return;
     tell_object(me,HIY"你赞道：“神仙姊姊这段话说得再也明白不过了。”再想：“\n"+
                       "这北冥神功是修积内力的功夫，学了自然丝毫无碍。”左手慢\n"+
                       "慢展开帛卷，突然间“啊”的一声，心中怦怦乱跳，霎时间面\n"+
                       "红耳赤，全身发烧。但见帛卷上赫然出现一个横卧的裸女画像\n"+
                       "，全身一丝不挂，面貌竟与那玉像一般无异。你只觉多瞧一眼\n"+
                       "也是亵渎了神仙姊姊，急忙掩卷不看。过了良久，心想：“神\n"+
                       "仙姊姊吩咐：‘以下诸图，务须用心修习。’我不过遵命而行\n"+
                       "，不算不敬。”\n\n"NOR);
     remove_call_out("beiming2");
     call_out("beiming2", 1, me);  
}

void beiming2(object me)
{
  if(!me) return;
     tell_object(me,HIM"于是颤抖着手翻过帛卷，但见画中裸女嫣然微笑，眉梢眼角，\n"+
                       "唇边颊上，尽是妖媚，比之那玉像的庄严宝相，容貌虽似，神\n"+
                       "情却是大异。你似乎听到自己一颗心扑通、扑通的跳动之声，\n"+
                       "斜眼偷看那裸女身子时，只见有一条绿色细线起自左肩，横至\n"+
                       "颈下，斜行而至右乳。你看到画中裸女椒乳坟起，心中大动，\n"+
                       "急忙闭眼，过了良久才睁眼再看，见绿线通至腋下，延至右臂\n"+
                       "，经手腕至右手大拇指而止。你越看越宽心，心想看看神仙姊\n"+
                       "姊的手臂，手指是不打紧的，但藕臂葱指，毕竟也不能不为之\n"+
                       "心动。\n\n"NOR);
     remove_call_out("beiming3");
     call_out("beiming3", 1, me);  
}

void beiming3(object me)
{
  if(!me) return;
     tell_object(me,HIC"另一条绿线却是至颈口向下延伸，经肚腹不住向下，至离肚脐\n"+
                       "数分处而止。你对这条绿线不敢多看，凝目看手臂上那条绿线\n"+
                       "时，见线旁以细字注满了“云门”、“中府”、“天府”、“\n"+
                       "侠白”、“尺泽”、“孔最”、“列缺”、“经渠”、“大渊\n"+
                       "”、“鱼际”等字样，至拇指的“少商”而止。你平时常听师\n"+
                       "父谈论武功，虽不留意，但听得多了，知道“云门”、“中府\n"+
                       "”等等都是人身的穴道名称。\n\n"NOR);
     remove_call_out("beiming4");
     call_out("beiming4", 1, me);  
}

void beiming4(object me)
{
  if(!me) return;
     tell_object(me,HIB"当下将帛卷又展开少些，见下面的字是：“北冥神功系引世人\n"+
                       "之内力而为我有。北冥大水，非由自生。语云：百川汇海，大\n"+
                       "海之水以容百川而得。汪洋巨浸，端在积聚。此‘手太阴肺经\n"+
                       "’为北冥神功之第一课。”\n\n"NOR);
     remove_call_out("beiming5");
     call_out("beiming5", 1, me);  
}

void beiming5(object me)
{
  if(!me) return;
     tell_object(me,HIR"          下面写的是这门功夫的详细练法。\n\n"+
                       HIG"最后写道：“世人练功，皆自云门而至少商，我逍遥派则反其\n"+
                       "道而行之，自少商而至云门，拇指与人相接，彼之内力即入我\n"+
                       "身，贮于云门等诸穴。然敌之内力若胜于我，则海水倒灌而入\n"+
                       "江河，凶险莫甚，慎之，慎之。本派旁支，未窥要道，惟能消\n"+
                       "敌内力，不能引而为我用，犹日取千金而复弃之于地，暴殄珍\n"+
                       "物，殊可哂也。”\n\n"NOR);
         set("quest/天龙八部/北冥神功/pass", 1, me);
         
     if(!me->query_skill("beiming-shengong")) 
{
me->set_skill("beiming-shengong",251);
         
tell_object(me,HIC"你的「北冥神功」进步了！”\n"NOR);
tell_object(me,HIC"你俨然已学会画卷中的武功绝学，以后就要靠你自己练习了！”\n"NOR);
	  me->start_busy(2);
set("quest/天龙八部/北冥神功/time", time(), 	me);
set("quest/天龙八部/北冥神功/combat_exp",query("combat_exp",  me), 	me);
	log_file("quest/bmsg",sprintf(HIR"%s(%s)学会北冥神功。富源：%d；经验：%d。\n"NOR,me->name(1),query("id", me),query("kar", me),query("combat_exp", me)));
}
else
{
tell_object(me,HIR"你俨然已学会画卷中的武功绝学，以后就要靠你自己练习了！”\n"NOR);
 me->start_busy(2);
set("quest/天龙八部/北冥神功/time", time(), me);
set("quest/天龙八部/北冥神功/combat_exp",query("combat_exp",  me), me);
log_file("quest/bmsg",sprintf(HIR"%s(%s)学会北冥神功。富源：%d；经验：%d。\n"NOR,me->name(1),query("id", me),query("kar", me),query("combat_exp", me)));
}
}