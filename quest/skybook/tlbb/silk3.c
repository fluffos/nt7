// /d/xingxiu/silk3.c
//tangfeng@SJ 2004

#include <ansi.h>
inherit ROOM;
#include <wanted.h>

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"

void create()
{
        set("short", HIM"颂摩崖"NOR);
        set("long", @LONG
颂摩崖又名黄龙碑。周围山势陡峭，两山对峙，一泓中流，两峡旁有潭，
渊深莫测。俗传有黄龙自潭飞出，因名黄龙潭。潭左侧摩崖成碑。汉隶真迹，
笔触遒劲，刀刻有力，记叙了开天井道的过程。往东南是仇池山，往西则是
石门。
LONG);
        set("outdoors", "yili");
           set("quest",1);

        set("exits", ([
                "eastdown" : __DIR__"silk2",
                "westdown" : __DIR__"silk4",
                "north" : __DIR__"silk3a",
        ]));

        set("coor/x",-250);
  set("coor/y",90);
   set("coor/z",0);
   set("coor/x",-250);
  set("coor/y",90);
   set("coor/z",0);
   set("coor/x",-250);
 set("coor/y",90);
   set("coor/z",0);
   setup();
}

void init()
{
	object me = this_player();
	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
		add_action("do_jump", ({"jump", "tiao"}));
		add_action("do_look", ({"look"}));
	}
        if ((me->query(QUESTDIR3+"good")&&me->query_temp(QUESTDIR4+"dagouzhen") &&me->query_temp(QUESTDIR4+"shaolinzhen")&&!me->query(QUESTDIR4+"over"))||(me->query(QUESTDIR4+"start")&&!me->query(QUESTDIR4+"over"))) {
		add_action("do_da", ({"da", "answer"}));
    if (localtime(TIME_TICK)[2] <= 2) tell_object(me,HIB"天黑了，这里黑黝黝一片，伸手不见五指，正是夜袭大营的好时候，怎么接应的人还没来呢？\n"NOR); 
		add_action("do_han", ({"han", "yell"}));
	}
}
int do_look(string arg)
{
	object me = this_player();

	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
	 if (!arg) {
		set("long", @LONG
颂摩崖又名黄龙碑。周围山势陡峭，两山对峙，一泓中流，两峡旁有潭，
渊深莫测。俗传有黄龙自潭飞出，因名黄龙潭。潭左侧摩崖成碑。汉隶真迹，
笔触遒劲，刀刻有力，记叙了开天井道的过程。往东南是仇池山，往西则是
石门。山壁（cliff）上远远看去一块地方光亮无比，似乎可以跳跃上去。
LONG
);
		me->look(arg);
	 }
	 else if (arg == "cliff") {
		tell_object(me,HIR"你仔细地观察着峭壁，发现可以跳跃（jump）上去。\n"NOR);
		return 1;
	 }
	}
	else
	{
		set("long", @LONG
颂摩崖又名黄龙碑。周围山势陡峭，两山对峙，一泓中流，两峡旁有潭，
渊深莫测。俗传有黄龙自潭飞出，因名黄龙潭。潭左侧摩崖成碑。汉隶真迹，
笔触遒劲，刀刻有力，记叙了开天井道的过程。往东南是仇池山，往西则是
石门。
LONG
);
		me->look(arg);
	}		
}

int do_jump(string arg)
{
	object room,me = this_player();
	object *player;
	int i;

	if(me->query_condition("killer")) return 0;//tjf不可以
   
	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
		if( arg == "cliff" || arg == "峭壁" || arg == "峭崖")
		{
			if(me->query_skill("dodge")<200) 
			{
				message_vision(HIC"\n$N吸了一口气，尝试一跃峭壁，却突然发现风大山高，却有点力不从心。\n"NOR,me);
				return 1;
			}
			message_vision(HIC"\n$N吸了一口气，一个纵身已经跳上峭壁。\n"NOR, this_player());
			if (!(room = find_object(__DIR__"cliff")))
				room = load_object(__DIR__"cliff");
			if(!room)
			{ 
				tell_object(me,HIR"\n你无论怎么跳，发现都还在原地!\n");
				log_file("quest/TLBB", sprintf("%s(%s)缺少cliff.c文件。\n", me->name(1),me->query("id")) );	
			}
			else
			{
				player = all_inventory(room);
				for (i = 0; i < sizeof(player); i++) {
					if (player[i]->is_character()) return notify_fail(YEL"你突然发现这个落脚之处过于狭小，已经有"+player[i]->query("name")+"在上面，你更本无法站稳。\n你叹了口气，只能左脚一点崖壁，又跳了下来。"NOR);
				}         	 
				tell_object(me,HIY"你没有想到，这块峭壁上竟然还有如此大的空间可以落脚，估计是当年中原高手埋伏的地点之一。\n"NOR);
				me->move(room);
			}
			return 1;
		}
	}
	return 0;
}
int do_han(string arg)
{
	object me, env;
	int count;

  me = this_player();
  
  //如果玩家进过大营，可以随时返会大营
  
	if (localtime(TIME_TICK)[2] > 2 && !me->query(QUESTDIR4+"start"))  return 0;

	env = this_object();
	count = me->query_temp(QUESTDIR4+"count");
	if(!me->query(QUESTDIR3+"good") )return 0;
	if(!me->query(QUESTDIR4+"start")&&!me->query_temp(QUESTDIR4+"dagouzhen")) return 0;
	if(!me->query(QUESTDIR4+"start")&&!me->query_temp(QUESTDIR4+"shaolinzhen")) return 0;
	if(me->query_condition("killer")) return 0;//tjf不可以
	if (present("wu shi", env))
		return notify_fail(HIR"一品堂喝道：“深更半夜，鬼苦一样大呼小叫什么？”\n"NOR);
	if (me->is_busy())
		return notify_fail("你要喊什么？先喘口气吧。\n");

	if ( count > 3 ){
    message_vision(HIC"$N吸了口气，道：“在下"+me->name()+HIC"，还请阁下现身！”声音传出去很远。\n"NOR, me);
		me->start_busy(1);
		remove_call_out("happen");
		call_out("happen", 10, me);
		return 1;
	}
	else
	{
		if(random(2)) me->start_busy(1);
    me->add_temp(QUESTDIR4+"count",1);
    tell_object(me,HIY"你尝试喊了一声，可是似乎毫无反应。\n"NOR);
	}
	return 1;
}

void happen(object me)
{
	object ob, env;

	env = this_object();
	if (!me) return;
	if(!me->query(QUESTDIR3+"good") )return 0;
	if (me->query_temp(QUESTDIR4+"count")<3) return;
	
	if (!(ob = present("dizi", env))) {
                ob = new("/d/gb/npc/dizi");
                ob->set("party","gb");
		ob->move(env);
		tell_room(env, HIY"夜色中有人咳嗽了一声，只见一个丐帮弟子疾步走了过来。\n"NOR, ({}));
	}
	if (!present(me, env)||(!me->query_temp(QUESTDIR4+"anhao")&&!me->query(QUESTDIR4+"start"))) {
		tell_room(env, CYN"丐帮四处看了看，皱了皱眉转身走了。\n"NOR, ({}));
		destruct(ob);
		return;
	}
  message_vision(HIW"丐帮弟子向$N一拱手，道：“天王盖地虎！”\n"NOR, me);
  me->start_busy(2);
}

int do_da(string arg)
{
	object me, ob,room,*obj;
	int i;
	me = this_player();
	if (!me) return 0;
  if (me->query_temp(QUESTDIR4+"count")<3) return 0;

	if (me->is_busy() || !arg )
		return notify_fail("你要说什么？先喘口气吧。\n");

  if (!present("gaibang dizi", this_object())){
		message_vision(CYN"丐帮弟子在远处喊道：“"+me->name()+""CYN"，我先走了！”\n"NOR, me);
		me->delete_temp("quest/天龙八部");
		me->delete_temp("quest/busy");//任务冲突标志取消 
		me->start_busy(1);
		return 1;
	}
  ob = present("gaibang dizi", this_object());
  obj = deep_inventory(me);
  i = sizeof(obj);
  while (i--)
    if (obj[i]->is_character())
       me->set_temp("out",1);
  if (me->query_temp("out")){
		message_vision(HIY"$N皱了皱眉头道："+me->name()+HIY"，你身上这位是......！我先走了！”\n"NOR,ob,me);
		me->delete_temp("quest/天龙八部");
		me->delete_temp("quest/busy");//任务冲突标志取消 
		me->delete_temp("out");
		me->start_busy(1);
		destruct(ob);
		return 1;
	}
	
    if (arg==me->query_temp(QUESTDIR4+"anhao")||me->query(QUESTDIR4+"start")) {
	  me->start_busy(1);
	  message_vision(HIC"$N对$n点了点头。\n"NOR, ob,me);
	  //只能一个人做
	  obj = users();
	  i = sizeof(obj);
	  while(i--) {
		  if ( obj[i]->query_temp(QUESTDIR4+"godaliao") && obj[i]!=me) 
		  {
			  message_vision(HIY"$N微笑着道：不用担心了，已经有"+obj[i]->query("name")+RANK_D->query_respect(obj[i]) +"前往大辽营救去了！\n"NOR,ob,me);
			  message_vision(HIY"$N晃了晃头道："+obj[i]->query("name")+RANK_D->query_respect(obj[i]) +"武功高墙，料想没什么问题！这样的话，我先走了！\n"NOR,ob,me);
			  message_vision(HIY"$N耸了耸肩，做了个揖，转身离开了。\n"NOR,ob,me);
			  me->delete_temp("quest/天龙八部");
			  me->delete_temp("quest/busy");//任务冲突标志取消 
			  log_file("quest/TLBB", sprintf("%s(%s)开始解救萧峰，但和%s(%s)冲突失败。经验：%d。\n", me->name(1),me->query("id"), obj[i]->name(1),obj[i]->query("id"), me->query("combat_exp")) ); 
			  destruct(ob);
			  return 1;
		  }
	  }
      
	  message_vision(HIC"$N说道：「"+me->name()+"，我们这就出发，且随我来。」\n"NOR, ob,me);
	  if (!(room = find_object(__DIR__"daliao/shulin")))
		  room = load_object(__DIR__"daliao/shulin");
	  if(!room)
	  { 
		  tell_object(me,HIR"\n你发现你们竟然还在原地!\n");
		  log_file("quest/TLBB", sprintf("%s(%s)缺少文件..daliao/shulin.c。\n", me->name(1),me->query("id")) ); 
	  	  return 1;
	  }

	  tell_object(me,HIY"你跟着丐帮弟子疾步向北走去，你突然发现这丐帮弟子轻功确实不错，丐帮不愧为天下第一帮。\n"NOR);
	  message_vision(YEL"$N急急忙忙离开颂摩崖。\n"NOR,me);
	  message_vision(YEL"$N急急忙忙离开颂摩崖。\n"NOR,ob);
	  me->move(room);
	  ob->move(room);
	  message_vision(YEL"$N急急忙忙来到"+room->query("short")+YEL"。\n"NOR,me);
	  message_vision(YEL"$N急急忙忙来到"+room->query("short")+YEL"。\n"NOR,ob);
	  message_vision(HIC"\n$N对$n点了点头。\n"NOR, ob,me);
	  message_vision(CYN"$N说道：「一直北行就是辽兵大营。我先行告退，还有几批武林人士需要接应。"+me->name()+CYN"还请小心，这一路恐怕不免一路厮杀。」\n"NOR, ob,me);
	  message_vision(CYN"$N说道：「"+RANK_D->query_respect(me) +"最好先去粮仓所在，可以点火（dianhuo），引起混乱，之后伺机营救萧大侠。萧大侠据说在辽营左堂附近。」\n"NOR, ob,me);
	  message_vision(HIC"$N对着$n挥了挥手。\n"NOR, ob,me);
	  message_vision(YEL"$N急急忙忙离开"+room->query("short")+YEL"。\n"NOR,ob);
	  log_file("quest/TLBB", sprintf("%s(%s)已经深入大辽，开始解救萧峰。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) ); 
	  me->set_temp(QUESTDIR4+"godaliao",1);
	  me->set(QUESTDIR4+"start",1);
	  destruct(ob);
	  return 1;
	}
	message_vision(HIY"$N抓耳挠腮，想了半天说道：“"+arg+"”。\n"NOR, me);
	message_vision(HIY"$N皱了皱眉头道："+me->query("name")+HIY"，你的意思是......"+arg+"”\n"NOR,ob,me);
	message_vision(HIY"$N皱了皱眉头。\n"NOR,ob);
	me->start_busy(1);
	return 1;
} 
 int valid_leave(object me, string dir)
 {
        object ob;
        if (base_name(this_object())==__DIR__"silk8" && dir == "south" && (is_wanted(me) || !userp(me)))
                return 0;
 
        if(me->query_temp("wait_target") && objectp(present("anran zi", environment(me))))
                return notify_fail("黯然子闪身拦在你面前，喝道：临阵想溜？给我滚回来！\n");
 
        if(me->query_temp("xx_rob") 
        && objectp(ob = present("hubiao biaoshi", environment(me)))
        && ob->query("target") == me)
                return notify_fail("护镖镖师闪身拦住你的去路，看来是想把你给废了！\n");  
 
        if(me->query_temp("xx_rob") && objectp(present("shangdui", environment(me))))
                return notify_fail("商队在这里呢，快抢(qiang)啊！\n");  
 
        return ::valid_leave(me, dir);
 }
