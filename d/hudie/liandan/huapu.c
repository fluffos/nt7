#include <ansi.h>
inherit ROOM;
void faya(object me);
void jiaoshui(object me);
void chucao(object me);
void zhuochong(object me);
void shouhuo(object me);


void create()
{
	set("short", "花圃");
	set("long", @LONG
这里是『蝶谷医仙』胡青牛的药圃，零零落落种了几株植物。胡大
夫为人脾气古怪，请不到什么人为他打理，因此这块药圃显得相当破败
衰落。
LONG
	);
       set("outdoors", "mingjiao");

	set("exits", 
	([
          	"north" : __DIR__"hudiegu",
	]));
        set("objects", 
	([
	]));
    
	setup();
}

void init ()
{
  	add_action("do_mai","mai");
  	add_action("do_jiaoshui","jiaoshui");
  	add_action("do_chucao","chucao");
  	add_action("do_zhuochong","zhuochong");
    	add_action("discmds",({"sleep","respitate","exert","array","duanlian",
	"ansuan","touxi","persuade","teach","exert","exercise","study","learn",
	"kill","steal","conjure","fight","hit","perform","prcatice","scribe","surrender"}));

}

int do_mai(string arg)
{
    	object ob;
    	object me = this_player();

	if (me->is_busy())
  		return notify_fail("你现在正忙,等一下再种吧!\n");

	if (!arg)
		return notify_fail("你要种什么？\n");

    	if (arg != "hua zhong")
       	return notify_fail("这样东西并不适合在这里种植。\n");
       
	if( query_temp("zhonghua", me) )
       	return notify_fail("你上次种的花花草草都长好了吗？\n");

	ob = present("hua zhong", me);
	if (!ob)
		return notify_fail("你要种什么？\n");

	destruct(ob);

	message_vision (MAG"$N在地上挖了一个小坑，小心地把鲜花种籽埋在里面。\n"NOR,me);

	me->start_busy(5);
set_temp("zhonghua", 1, 	me);

       call_out("faya",8, me);
	return 1;

}


void faya(object me)
{
	message_vision (HIG"$N耐心地等了一段时间，只见一根绿油油的嫩苗破土而出！\n"NOR,me);

	me->start_busy(5);

    	switch (random(4)) 
    	{
    		case 0: 
     			call_out("jiaoshui",8, me);
		break;

    		case 1:
     			call_out("chucao",8, me);
		break;

    		case 2:
     			call_out("zhuochong",8, me);
		break;

    		case 3:
     			call_out("shouhuo",8, me);
		break;

    	}
}

void jiaoshui(object me)
{
	message_vision (HIR"只见天空骄阳似火，$N种下的植物眼看着就一点点干枯了。\n"NOR,me);

set_temp("need_jiaoshui", 1, 	me);
}

int do_jiaoshui()
{
    	object me = this_player();
	object ob;

	if( !query_temp("need_jiaoshui", me) )
		return notify_fail("你要做什么？\n");
	
	if (!ob = present("shui hu", me))
		return notify_fail("你身上没有水壶，拿什么浇花？\n");

	message_vision (HIB"$N拿出一把水壶，仔细地浇在自己种的植物上。\n"NOR,me);
	me->start_busy(5);
delete_temp("need_jiaoshui", 	me);

    	switch ( random(3) ) 
    	{

    		case 0:
     			call_out("chucao",8, me);
		break;

    		case 1:
     			call_out("zhuochong",8, me);
		break;

    		case 2:
     			call_out("shouhuo",8, me);
		break;

    	}
	return 1;
}

void chucao(object me)
{
	message_vision (GRN"随着时间的推移，$N种下的植物旁边渐渐长出了一些杂草。\n"NOR,me);

set_temp("need_chucao", 1, 	me);
}

int do_chucao()
{
    	object me = this_player();
	object ob;

	if( !query_temp("need_chucao", me) )
		return notify_fail("你要做什么？\n");
	
	if (!ob = present("yao chu", me))
		return notify_fail("你身上没有药锄，拿什么除草？\n");

	message_vision (HIB"$N拿出药锄，仔细地把周围的杂草清除干净。\n"NOR,me);
	me->start_busy(5);
delete_temp("need_chucao", 	me);

    	switch ( random(3) ) 
    	{

    		case 0:
     			call_out("jiaoshui",8, me);
		break;

    		case 1:
     			call_out("zhuochong",8, me);
		break;

    		case 2:
     			call_out("shouhuo",8, me);
		break;

    	}
	return 1;
}

void zhuochong(object me)
{
	message_vision (HIY"又过了一会，$N突然发现有几只害虫正在疯狂地啃噬植物的根茎！\n"NOR,me);

set_temp("need_zhuochong", 1, 	me);
}

int do_zhuochong()
{
    	object me = this_player();

	if( !query_temp("need_zhuochong", me) )
		return notify_fail("你要做什么？\n");
	
	message_vision (HIB"$N不顾地面肮脏，趴在地上把害虫一条一条找出来杀死。\n"NOR,me);
	me->start_busy(5);
delete_temp("need_zhuochong", 	me);

    	switch ( random(3) ) 
    	{

    		case 0:
     			call_out("jiaoshui",8, me);
		break;

    		case 1:
     			call_out("chucao",8, me);
		break;

    		case 2:
     			call_out("shouhuo",8, me);
		break;

    	}
	return 1;
}
void shouhuo(object me)
{
	int i;
	object hua1, hua2, hua3, hua4; 

	i = 1 + random(4);

	if (i == 1)
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N收获了一朵"+hua1->name()+HIM"！\n"NOR, this_player());
	}
	else if (i == 2)
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N收获了一朵"+hua1->name()+HIM"！\n"NOR, this_player());

		hua2 = new(__DIR__"/yao/hualei");
   		hua2->move(me);
   		message_vision(HIM"$N收获了一朵"+hua2->name()+HIM"！\n"NOR, this_player());

	}
	else if (i == 3)
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N收获了一朵"+hua1->name()+HIM"！\n"NOR, this_player());

		hua2 = new(__DIR__"/yao/hualei");
   		hua2->move(me);
   		message_vision(HIM"$N收获了一朵"+hua2->name()+HIM"！\n"NOR, this_player());

		hua3 = new(__DIR__"/yao/hualei");
   		hua3->move(me);
   		message_vision(HIM"$N收获了一朵"+hua3->name()+HIM"！\n"NOR, this_player());

	}
	else
	{
		hua1 = new(__DIR__"/yao/hualei");
   		hua1->move(me);
   		message_vision(HIM"$N收获了一朵"+hua1->name()+HIM"！\n"NOR, this_player());

		hua2 = new(__DIR__"/yao/hualei");
   		hua2->move(me);
   		message_vision(HIM"$N收获了一朵"+hua2->name()+HIM"！\n"NOR, this_player());

		hua3 = new(__DIR__"/yao/hualei");
   		hua3->move(me);
   		message_vision(HIM"$N收获了一朵"+hua3->name()+HIM"！\n"NOR, this_player());

		hua4 = new(__DIR__"/yao/hualei");
   		hua4->move(me);
   		message_vision(HIM"$N收获了一朵"+hua4->name()+HIM"！\n"NOR, this_player());

	}

	me->start_busy(2);

	message_vision (HIR"终于到了收获的季节！$N这次收获了"+chinese_number(i)+"朵花！\n"NOR,me);

addn("combat_exp", 1000+random(i*1000), 	me);
addn("potential", 300+random(i*300), 	me);

        delete_temp("zhonghua", me);


	tell_object(this_player(),MAG"由于你的辛勤劳动，经验和潜能都有所增长。\n"NOR);


}

int valid_leave(object me, string dir)
{
	if( query_temp("zhonghua", me) )
		 return notify_fail("等花种出来再走也不迟。\n");
	else return ::valid_leave(me, dir);
}

int discmds()
{
        tell_object(this_player(),"既然到了这里，还是专心种花吧！\n");
        return 1;
}
