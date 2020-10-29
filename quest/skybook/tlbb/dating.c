// Room: /d/nanyang/dating.c
// Lklv Modify 2001.10.11
// Tangfeng@SJ 2004

#include <ansi.h>
inherit ROOM;

#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"

void xiaofeng1(object me);
void xiaofeng2(object me);
void xiaofeng3(object me);
int do_action(string arg);
int do_jiejiu(string arg);
void copy_person(object ob,int i);
void destruct_person(object ob);
void set_person(object obj1,object obj2,int i);

void create()
{
        set("short", "聚贤庄大厅");
        set("long", @LONG
这是聚贤庄的大厅，大厅内很宽敞，放着几十张桌子。东首主位的桌子旁
放有三把黑色的太师椅，其中一个椅子上坐着一个中年男子。他身后的墙上挂
有两副圆盾、一柄单刀，一杆短枪。
LONG
        );
		set("quest",1);
		set("exits", ([
		"south" : __DIR__"jxzhuang",
		"east" : __DIR__"houyuan",
	]));
	
	set("objects",([
		__DIR__"npc/youju" : 1,
		__DIR__"npc/youji" : 1,
        ]));
	
	setup();
}
void init()
{
  object me,obj;
  me = this_player();
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"jxzhuang")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if (this_object()->query("busy")) 
  {
	  me->move("/d/nanyang/jxzhuang");
	  message_vision(HIR "\n$N发现聚贤庄内打斗越来越激烈，刀剑无眼，还是走为上策！\n" NOR, me);
	  return;
  }
  if (me->query_condition("killer")) 
  {
	  me->move("/d/nanyang/jxzhuang");
  	  message_vision(HIR "\n$N发现聚贤庄内打斗越来越激烈，刀剑无眼，还是走为上策！\n" NOR, me);
	  return;
  }
  me->start_busy(2);
  me->set_temp(QUESTDIR3+"jxzhuang",1);
  copy_person(this_object(),3);//复制情节人物，3是用来控制萧峰有普通招数，其他npc只有绝招  
  obj=present("xiao feng", this_object());
  tell_object(me,HIG"\n你走进大厅内，果然一片混乱。大厅上聚集着三百余人，大家挤在一团，真能挨到萧峰身边的，不过五六人而已，\n"
                      "刀枪剑戟四下舞动，一大半人倒要防备为自己人所伤。\n"NOR); 
  message_vision(HIR "\n$N微一凝神，运起混天气功，全身骨节发出一阵爆豆般的声响。\n" NOR, obj);
  remove_call_out("xiaofeng1");
  remove_call_out("busy");
  //避免玩家quest混乱
  this_object()->set("busy",1);
  call_out("busy", 1200);   
  call_out("xiaofeng1",10, me);  
  log_file("quest/TLBB", sprintf("%s(%s)聚贤庄大混乱开始。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  add_action("do_action", ({"dazuo", "tuna", "lian", "learn", "du", "guard","steal","kill", "hit", "fight", "throw", "ansuan"}));  
  add_action("do_jiejiu", ({"help","bangzhu","jiejiu", "save"}));
}
void xiaofeng1(object me)
{
	object obj;
	if(!me) return;
	if (!me->query(QUESTDIR3+"start")) return;
	if (!me->query_temp(QUESTDIR3+"kill")) return;
	if (me->query(QUESTDIR3+"over")) return;
	if (me->query_temp(QUESTDIR3+"help")) return;
	if(!present(me,this_object())) 
	{
		tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
		me->delete_temp("quest/busy");//任务系统冲突标志
		me->delete_temp("quest/天龙八部");   
		me->delete(QUESTDIR3+"start");
		me->add("mana",-200);
		if(me->query("mana")<0) me->set("mana",0);
		destruct_person(this_object());//消除所有人物
		return;
	}
	copy_person(this_object(),1);//复制情节人物  ,1是最激烈的战斗
	obj=present("xiao feng", this_object());
    message_vision(HIG"\n\n$N果然了得，手掌扬处，砰砰两声，又有两人中了劈空拳倒地，随势冲入人群，肘撞拳击，掌劈脚踢，霎时间又打倒数人。\n\n"NOR, obj);
    message_vision(HIG"$N对着$n冷笑一声。\n\n"NOR, obj,me);
	remove_call_out("xiaofeng2");
	call_out("xiaofeng2",20, me);   
	return;
}
void xiaofeng2(object me)
{
  object obj1,obj2;
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任务系统冲突标志
	  me->delete_temp("quest/天龙八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  copy_person(this_object(),0);//复制情节人物 ,0让所有的人物战斗停止
  obj1=present("xiao feng", this_object());
  obj2=present("xuan nan", this_object());
  tell_object(me,HIY"\n一会工夫，大厅情况发生变化。却见中央让出一块空地，只见少林高僧玄难缓步而前，本来是数十人围攻乔\n"
                      "峰的局面，玄难这一出手，余人自觉在旁夹攻反而碍手碍脚，自然而然的逐一退下，各人团团围住，以防乔\n"
                      "峰逃脱，凝神观看玄难和他决战。\n"NOR);                    
  message_vision(HIY"\n$N突然深吸一口气，目露慈光，面带微笑，内力运转，竟使全身上下宝光流动，是「金刚不坏体神功」！\n" NOR, obj2); 
  obj2->kill_ob(obj1);
  obj1->start_busy(3);
  obj2->start_busy(3);
  message_vision(HIR"\n$n向$N喝道：“看我袖里乾坤。”只见$N内力充盈，衣袖拂起，拳劲却暗藏在袖底发出，正是少林绝技。\n" NOR, obj1,obj2); 
  message_vision(HIW"\n$N料想这招衣袖便是拳劲的掩饰，使其无法看到拳势来路，攻他个措手不及。当即全神贯注的拆解他袖底所\n"
                      "藏拳招，$N使出「蜻蜓点水」，恰好躲过了$n的攻势。\n" NOR, obj1,obj2); 
  message_vision(HIY"\n岂料，衣袖之上却也蓄有极凌厉的招数和劲力，$N当即大喝一声，孤注一掷，将全身功力汇于一袖之内挥出！\n" NOR,obj2);
  message_vision(HIW"\n$N见他攻到，两只宽大的衣袖鼓风而前，便如是两道顺风的船帆，威势非同小可，大声喝道：“袖里乾坤，\n"
                      "果然了得！”呼的一掌，拍向他衣袖。$n的袖力广被宽博，$N这一掌却是力聚而凝，只听得嗤嗤声响，两股\n"
                      "力道相互激荡，突然间大厅上似有数十只灰蝶上下翻飞。\n" NOR, obj1,obj2); 
  tell_object(me,HIB"\n你暗叫一声“好武功”，萧峰只如此一掌，便破了渡难的成名绝技。\n"NOR);  
  log_file("quest/TLBB", sprintf("%s(%s)聚贤庄大混乱玄难与萧峰单干。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  remove_call_out("xiaofeng3");
  call_out("xiaofeng3",15, me);   
  return;
}
void xiaofeng3(object me)
{
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任务系统冲突标志
	  me->delete_temp("quest/天龙八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  copy_person(this_object(),3);//复制情节人物 
  message_vision(HIY"\n玄难突然深吸一口气，目露慈光，面带微笑，内力运转，竟使全身上下宝光流动，是「金刚不坏体神功」！\n" NOR,me); 
  message_vision(HIR"\n玄难似乎渐渐不是对手，群雄又是全部一拥而上，场面更加混乱，战斗越来越是激烈！\n" NOR,me); 
  remove_call_out("xiaofeng4");
  call_out("xiaofeng4",30, me);   
  return;
}
void xiaofeng4(object me)
{
  object obj;
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任务系统冲突标志
	  me->delete_temp("quest/天龙八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  copy_person(this_object(),3);//复制情节人物 
  obj=present("xiao feng", this_object());
  message_vision(HIW"\n瞬间之内，$N发现萧峰似乎背心、右胸、右肩同时中刀，更不可思议的是萧峰竟然当即昂立不动，陡然仰天\n"
                      "大叫，声音直似猛兽狂吼。却见单正正大呼而前，举刀往萧峰胸口刺去。\n"NOR,me);
  tell_object(me,HIR"\n你暗道一声“不妙”，需要你赶快去解救萧峰（jiejiu xiao feng）。\n"NOR);
  log_file("quest/TLBB", sprintf("%s(%s)聚贤庄大混乱需要解救萧峰。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  me->set_temp(QUESTDIR3+"can_be_help",1);
  remove_call_out("xiaofeng5");
  call_out("xiaofeng5",10, me); 
  remove_call_out("xiaofeng_over");
  call_out("xiaofeng_over",120, me);  
  return;
}
void xiaofeng5(object me)
{
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if (!me->query_temp(QUESTDIR3+"can_be_help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任务系统冲突标志
	  me->delete_temp("quest/天龙八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  copy_person(this_object(),3);//复制情节人物 
  tell_object(me,HIR"\n你赶快去解救萧峰（jiejiu xiao feng）啊。别发呆了！\n"NOR);
  remove_call_out("xiaofeng5");
  call_out("xiaofeng5",10, me); 
  return;
}
void xiaofeng_over(object me)
{
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if (!me->query_temp(QUESTDIR3+"can_be_help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任务系统冲突标志
	  me->delete_temp("quest/天龙八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  tell_object(me,HIC"\n突然一个黑衣人丛房顶跳下来，一个窜身向单正拿去，势道奇急，正好碰在单正的钢刀之上。钢刀顺势落地。厅中登时大\n"
                      "乱，群雄惊呼叫嚷。黑衣人顺手检起角落一团长绳，用力一甩，趁群雄纷举兵刃挡格之际，绳头陡转，往萧峰腰间一缠，\n"
                      "随即提起。黑衣人随手倒转长绳，绕向八九丈外的一株大树，一拉长绳，顷刻间越过那株大树，已在落在后院。\n"NOR);
  tell_room(environment(me),HIC"\n突然一个人影化过，却见单正已经昏倒在地，而萧峰腾空而起。再仔细看时，人已经落在后院之中。\n"NOR, ({}));                       

  tell_object(me,HIG"\n你这种情况竟然不敢救援，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
  me->delete_temp("quest/busy");//任务系统冲突标志
  me->delete_temp("quest/天龙八部");   
  me->delete(QUESTDIR3+"start");
  me->add("mana",-200);
  if(me->query("mana")<0) me->set("mana",0);
  log_file("quest/TLBB", sprintf("%s(%s)聚贤庄大混乱没有解救萧峰，任务失败。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  destruct_person(this_object());//消除所有人物
  return;
}

int do_jiejiu(string arg)
{
  object obj,room,me;
  me = this_player();
  if (!me->query(QUESTDIR3+"start")) return 0;
  if (!me->query_temp(QUESTDIR3+"kill")) return 0;
  if (me->query(QUESTDIR3+"over")) return 0;
  if (me->query_temp(QUESTDIR3+"help")) return 0;
  if(!arg) return 0;
  if(arg!="xiao feng" && arg!="xiao")
  {
      tell_object(me,HIR"\n没人用你来解救。\n"NOR);
	  return 1; 
  }
  if (!me->query_temp(QUESTDIR3+"can_be_help"))
  {
      tell_object(me,HIR"\n还不到时候，不需要你解救，萧峰自能自己应付。\n"NOR);
	  return 1; 
  }
  if(!(obj=present("xiao feng", environment(me))))
  {
      copy_person(this_object(),3);
  }
  obj=present("xiao feng", environment(me));
  obj->set("qi", obj->query("max_qi")/3);
  obj->set("eff_qi", obj->query("max_qi")/3);
  obj->set("jing", obj->query("max_jing"));
  obj->set("eff_jing", obj->query("max_jing"));
  obj->add("neili", obj->query("max_neili")*2);
  obj->set("jingli", obj->query("max_jingli"));
  if(obj->is_busy()) obj->start_busy(-1);	  
 
  tell_object(me,HIC"\n你暗道一声“不妙”，马上一个窜身，你势道奇急，正好碰在单正的钢刀之上。钢刀顺势落地。厅中登时大乱，\n"
                      "群雄惊呼叫嚷。你顺手检起角落一团长绳，用力一甩，趁群雄纷举兵刃挡格之际，绳头陡转，往萧峰腰间一缠，\n"
                      "随即提起。你随手倒转长绳，绕向八九丈外的一株大树，一拉长绳，顷刻间越过那株大树，已在落在后院。\n"NOR);
  tell_room(environment(me),HIC"\n突然一个人影化过，却见单正已经昏倒在地，而萧峰腾空而起。再仔细看时，人已经落在后院之中。\n"NOR, ({}));                       
  if (!(room = find_object("/d/nanyang/houyuan")))
      room = load_object("/d/nanyang/houyuan");
  if(room)
  {
  	me->move(room);  
  	obj->move(room);
    tell_object(me,HIR"\n你跟着又甩长绳，再绕远处大树，如此几个起落，已然走得无影无踪。\n"NOR);
  }
  else 
  {
	  destruct_person(this_object());//消除所有人物
	  tell_object(me,HIR"\n你跟着又甩长绳，再绕远处大树，如此几个起落，靠，还在原地？？\n"NOR);
	  me->delete_temp("quest/busy");//任务系统冲突标志
	  me->delete_temp("quest/天龙八部");   
	  log_file("quest/TLBB", sprintf("%s(%s)聚贤庄缺少houyuan.c文件。\n", me->name(1),me->query("id")) );
	  return 1;
  }
  if (!(room = find_object("/d/nanyang/duanya2")))
      room = load_object("/d/nanyang/duanya2");
  if(room)
  {
    tell_room(environment(me),HIC"\n"+me->name()+"又一甩长绳，再绕远处大树，如此几个起落，已然走得无影无踪。\n"NOR, ({}));                       
  	me->move(room);  
  	obj->move(room);
    tell_object(me,HIG"\n你怕有追兵追赶，连续走过几个地方，才来到一个断崖边停住。\n"NOR);
  }
  else 
  {
    destruct_person(this_object());//消除所有人物
	me->delete_temp("quest/busy");//任务系统冲突标志
	me->delete_temp("quest/天龙八部");   
    tell_object(me,HIR"\n你跟着又甩长绳，再绕远处大树，如此几个起落，靠，还在原地？？\n"NOR);
	log_file("quest/TLBB", sprintf("%s(%s)聚贤庄缺少duanya2.c文件。\n", me->name(1),me->query("id")) );
    return 1;
  }
  log_file("quest/TLBB", sprintf("%s(%s)聚贤庄大混乱成功解救萧峰。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  me->set_temp(QUESTDIR3+"help",1);
  destruct_person(this_object());//消除所有人物
  return 1;
}
void busy()
{
	this_object()->delete("busy");
	return;
}
int do_action(string arg)
{
	this_player()->start_busy(1);
   	tell_object(this_player(),HIR"\n你正要有所动作，突然感觉这里太过混乱，还是安静得好！\n");
   	return 1;
}
int valid_leave(object me, string dir)
{
     if (present("xiao feng", environment(me)))
           return notify_fail(HIR"别忘记了此行的目的，怎能不管萧峰了，还是静观其变！\n"NOR);
     return ::valid_leave(me, dir);
}
void copy_person(object ob,int i)
{
	object obj1,obj2;
	//添加萧峰
  if(!(obj1=present("xiao feng", ob))) 
  {
 	   obj1=new(__DIR__"npc/xiaofeng");
    obj1->set("no_death",1);
     obj1->move(ob); 
  }
    obj1->set("no_death",1);
  obj1->remove_all_killer(); 
  //添加丐帮宋奚陈吴白
  if(!(obj2=present("wu zhanglao", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("吴长老", ({ "wu zhanglao", "wu","zhanglao"}) );
		 obj2->set("title",HIB"丐帮长老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); //设置战斗还是停止战斗,0 停止战斗，1战斗，2战斗但只发绝技，3战斗只有xiao feng 出普通招
  if(!(obj2=present("song zhanglao", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("宋长老", ({ "song zhanglao", "song","zhanglao"}) );
		 obj2->set("title",HIM"丐帮长老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("xi zhanglao", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("奚长老", ({ "xi zhanglao", "xi","zhanglao"}) );
		 obj2->set("title",HIC"丐帮长老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("chen zhanglao", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("陈长老", ({ "chen zhanglao", "chen","zhanglao"}) );
		 obj2->set("title",HIY"丐帮长老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("bai shijing", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("白世镜", ({ "bai shijing", "bai"}) );
		 obj2->set("title",HIC"执法堂主"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  //添加少林玄慈、玄济
  if(!(obj2=present("xuan nan", ob))) 
  {
 	   obj2=new(__DIR__"npc/sldizi");
		 obj2->set_name("玄难", ({ "xuan nan", "xuan","nan"}) );
		 obj2->set("title",HIY"少林长老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("xuan ji", ob))) 
  {
 	   obj2=new(__DIR__"npc/sldizi");
		 obj2->set_name("玄寂", ({ "xuan ji", "xuan","ji"}) );
		 obj2->set("title",HIY"少林长老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 

  //添加单正谭公谭婆赵钱李
  if(!(obj2=present("shan zheng", ob))) 
  {
 	   obj2=new(__DIR__"npc/otherdizi");
		 obj2->set_name("单正", ({ "shan zheng", "shan","zheng"}) );
		 obj2->set("title",HIB"铁面判官"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("tan po", ob))) 
  {
 	   obj2=new(__DIR__"npc/otherdizi");
		 obj2->set_name("谭婆", ({ "tan po", "tan","po"}) );
		 obj2->set("title",HIY"太行山冲霄洞"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("tan gong", ob))) 
  {
 	   obj2=new(__DIR__"npc/otherdizi");
		 obj2->set_name("谭公", ({ "tan gong", "tan","gong"}) );
		 obj2->set("title",HIY"太行山冲霄洞"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("zhao qianli", ob))) 
  {
 	   obj2=new(__DIR__"npc/otherdizi");
		 obj2->set_name("赵钱李", ({ "zhao qianli", "zhao"}) );
		 obj2->set("title",HIG"骑驴客"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  //人物添加结束  
  return;	
}
void set_person(object obj1,object obj2,int i)
{
  if(!obj1) return;
  if(!obj2) return;
  //obj1是萧峰
  if(i>0) obj2->kill_ob(obj1);
  else obj2->remove_all_killer(); 
  if(i==2) 
  {
	  obj1->set_temp("no_fight",1);
	  obj2->set_temp("no_fight",1);
  }
 if(i==3) 
  {
	  obj1->delete_temp("no_fight");
	  obj2->set_temp("no_fight",1);
  }
  if(i==4) 
  {
	  obj2->delete_temp("no_fight");
	  obj1->set_temp("no_fight",1);
  }
  return;
}
void destruct_person(object ob)
{
	object obj;
	if((obj=present("xuan nan", ob))) 
	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("xiao feng", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("xuan ji", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("wu zhanglao", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("xi zhanglao", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("song zhanglao", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("chen zhanglao", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("bai shijing", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("shan zheng", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("tan gong", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("tan po", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("zhao qianli", ob))) 	{
    message_vision(HIR"$N打了个哈哈，竟然走开了。\n" NOR, obj);
		destruct(obj);
  }
  return;
}
