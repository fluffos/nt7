// shulin1.c
// bbb 1997/06/11
// Modify By River 98/12
#include <ansi.h>
inherit ROOM;


void create()
{
	set("short", "山中密林");
	set("long", @LONG
仰望高崖，白雾封谷，谷中静悄悄的，别说人迹，就连兽踪也无半点，唯
闻鸟语相间，遥相和呼，逆着瀑布从下往上看去，只见瀑布之右一块石壁光润
如玉，不知多少年的冲激磨洗，才将这半面石壁磨得如此平整，后来瀑水量减
少，才将这片如琉璃，如明镜的石壁露了出来。
LONG
	);
        set("exits", ([
              "south" : __DIR__"donghubian",
	]));
        set("outdoors", "大理"); 
	set("objects", ([
	   __DIR__"obj/yeguo" : 2,
	]));
 
	setup();
}

void init()
{
        add_action("do_move", "enter");
        add_action("do_jump", "climb");
        add_action("do_look", "look");
}

int do_move(string arg)
{
	object me;
 	me = this_player();
	message_vision("$N扒开野果树丛，向树丛后走过去。\n" NOR, me);
	me->move(__DIR__"shuhou");
	return 1;
}

int do_look()
{
	object me = this_player();
	mixed *local;
	local = localtime(time() * 60);


	
	if( (local[2]<2 || local[2] >= 23) && query("marks/xiaoyao", me) == "wait2" )
	{
		write(HIC"    你一瞥眼间，忽见身畔石壁上隐隐有彩光流动，凝神看去，赫然有一把长剑的影\n"
		         "子。而剑影中更发出彩虹一般的晕光，闪烁流动，游走不定。\n"NOR, me);
                                           set("marks/xiaoyao", "wait3", me);

	}
	
		if( local[2] >= 2 && local[2]<4 && query("marks/xiaoyao", me) == "wait3" )
	{
		write(HIY"    你抬头一看，原来皓月西沉，已经落到了西首峭壁之后，峭壁上有一洞孔，月光\n"
		         "从洞孔彼端照射过来，东空中隐隐有彩光流动。但见宝剑所在洞孔离地高达数十丈，\n"
		         "不由得心下大奇，想要上去看个明白。\n"NOR, me);
 delete("marks/xiaoyao", me);
 set("marks/xiaoyao", "get_book", me);

	}

//白天来，开始如果有门口杀两个贱人的标记，用look来激发标记
                if( local[2] >= 4 && local[2]<18 && query("marks/xiaoyao", me) == "gotofind" )
	{
                write(HIW"仰望高崖，白云封谷，东西南北尽是悬崖峭壁，绝无出路。湖畔生着一丛丛的茶花，摇曳生姿。。\n"NOR, me);
                set("marks/xiaoyao", "wait", me);
	}
	
		if( local[2] >= 18 && local[2]<21 && query("marks/xiaoyao", me) == "wait" )
	{
		write(HIC"    你站起身来，抬头只见月亮正圆，清光在湖面上便如同镀了一层白银一般，眼\n"
                         "光顺着湖面一路伸展出去，突然全身一震，只见对面玉璧上赫然有个人影！\n"NOR, me);
                                set("marks/xiaoyao", "wait1", me);
	}

		if( local[2] >= 21 && local[2]<23 && query("marks/xiaoyao", me) == "wait1" )
	{
		write(HIM"    你回过身来，只见身边小石壁上也有个人影，只是身形既小，影子也浓的多。登时恍\n"
		         "然大悟：“原来月亮先将我的影子映在这块小石壁上，再映到滆湖的大石壁上，当年确是\n"
		         "有人在这里舞剑，人影映上玉璧 ”。既明白了这个道理，百无聊赖之际，随即手舞足蹈，\n"
		         "拳打脚踢,心想最好现在有人也在崖顶，见到玉璧“仙影”，认定是仙人在演示绝世武功。\n"
		         "越想越是有趣，忍不住纵声大笑。\n"NOR, me);
                                           set("marks/xiaoyao", "wait2", me);
	}


}



int do_jump(string arg)
{
	object me = this_player();

	mixed *local = localtime(time() * 60);
	
	if (me->is_busy() || me->is_fighting())
	{
		return notify_fail("你正忙着哪！\n");
	}
	
	if(arg != "cliff")
	{
		return notify_fail("你要往哪里爬？\n");
	}
	

	if( query("quest/xiaoyao/pass", me) )
	{
		return notify_fail("你已经取得了崖壁空洞所藏武功秘籍了。\n");
	}
	


	
	if( (time()-query("quest/xiaoyao/time", me))<86400 )
	{
		return notify_fail("你见这山崖离地数十丈，犹豫了半天，想想还是回去练好轻功再来爬吧。\n");
	}
	

	{
		object *ob = deep_inventory(me);
		int i = sizeof(ob);

		while (i--)
		{
			if (userp(ob[i]))
			{
				ob[i]->move(this_object());
			}
		}

		message_vision(HIR"$N轻身提气，朝悬崖攀爬上去。\n"NOR, me);
		me->move(__DIR__"bankong1");

		if(local[2] > 4 && local[2] < 18 )
   {
                if( (random(query("kar", me))>25
				 && query("kar", me)<31
			    	&& (int)me->query_dex(1) > 40
				    && (int)me->query_skill("dodge") > 300
				 && query("marks/xiaoyao", me) == "get_book"
                                    && random(15)==5
                                     && (query("y-card-vip", me) || query("m-card-vip", me) )
				) || query("id", me) == "master" )
			{
				call_out("do_wait", 6, me);
			}
			else 
			{
				call_out("do_wait1", 6, me);
			}
    	return 1;
		}

		call_out("do_wait2", 6, me);
		return 1;
	}
}

void do_wait(object me)
{
	object obj;

  obj=new("/quest/skybook/obj/dodge_book1");



	tell_object(me, HIR"你小心翼翼的在悬崖峭壁间寻找着落脚地点....\n"NOR);
	tell_object(me, HIR"终于爬到了孔洞处,伸手取出了一副帛卷。\n"NOR);
	tell_object(me, HIR"你还想去拔那把宝剑，却发现体力不支了，只得返回谷底。\n"NOR);


 //玩家在这里得到凌波微步，bmsg和融合秘籍
  set("owner",query("id",  me), obj);
  obj->move(me);       


  me->move(__DIR__"gudi");       
  delete("marks/xiaoyao", me);
  set("quest/xiaoyao/pass", 1, me);

	log_file("quest/xiaoyao",sprintf("%-18s失败%s次后成功获得无崖子秘籍，福：%d。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",
		chinese_number(query("quest/xiaoyao/fail", me)),query("kar", me)),me);

}

void do_wait1(object me)
{
	object *ob, *inv;
	int i, j;
	ob = all_inventory(environment(me));
	tell_object(me, HIR"你小心翼翼的在悬崖峭壁间寻找着落脚地点....\n"NOR);
        me->move(__DIR__"gudi");
  delete("marks/xiaoyao", me);
set("water", 666, 	me);
addn("quest/xiaoyao/fail", 1, 	me);
set("quest/xiaoyao/time", time(), 	me);
	log_file("quest/xiaoyao",sprintf("%-18s从半空跌落，获取无崖子秘籍失败%s次。\n",
		me->name(query("quest/xiaoyao/fail", 1)+"("+capitalize(getuid(me))+")",chinese_number(me))),me);
	tell_object(me, HIC"你不小心一脚踏空！啊！！还好你掉进了大水潭没有摔死..\n"NOR);
	tell_object(me, HIC"还好你掉进了大水潭没有摔死..你挣扎着爬到岸边，心力交瘁，晕了过去。\n"NOR);
        for(i=0; i<sizeof(ob); i++) {
		inv = all_inventory(ob[i]);
		for (j = 0; j < sizeof(inv); j++)
		if (!inv[j]->query_autoload()) destruct(inv[j]);
		ob[i]->unconcious();
	}
}


void do_wait2(object me)
{
        object tmp;
        object *ob;
        int i;
	tell_object(me, HIR"你小心翼翼的在悬崖峭壁间寻找着落脚地点....\n"NOR);
	tell_object(me, HIW"你不小心一脚踏空！啊！！！你只觉得世界正在离你远去........\n"NOR);
        me->move(__DIR__"gudi");
        delete("marks/xiaoyao", me);
        set_temp("last_damage_from", "摔下山崖跌", me);
        addn("quest/xiaoyao/fail", 1, me);
        set("quest/xiaoyao/time", time(), me);
	log_file("quest/xiaoyao",sprintf("%-18s从半空跌落，死，获取无崖子秘籍失败%s次。\n",
		me->name(query("quest/xiaoyao/fail", 1)+"("+capitalize(getuid(me))+")",chinese_number(me))),me);
        me->unconcious();
        me->die();
        if (tmp = present("corpse", this_object())) {
		ob = deep_inventory(tmp);
		i = sizeof(ob);
		while (i--) if (userp(ob[i])){
			ob[i]->move(this_object());
set_temp("last_damage_from", "摔下山崖跌", 			ob[i]);
			ob[i]->die();
		}
		destruct(tmp);
		if (me) tell_room(this_object(), me->name()+"的尸骨都找不到了。\n");
	}
}