#include <ansi.h>
#include <room.h>
inherit ROOM;
string look_left(object me);
string look_right(object me);

void create()
{
   set("short",MAG"关冲"NOR);
	set("long",@LONG
这个山洞内一尘不染，非常干净，光线来自洞顶，似乎有块非常大的宝石，
迎面墙壁上挂着两张图谱(tupu)，地上放着几个蒲团，你随便找了个地方坐了
下来。
LONG
	);

	set("item_desc", ([
		"tupu" : "墙上挂着两张图谱(left)(right)，似乎就是六脉神剑的武功要诣。\n",
		"left": (: look_left :),
		"right": (: look_right :),
	]));

	set("exits", ([
		"southeast" : __DIR__"pyd",
	]));
       
	setup();
}

string look_left(object me)
{
	return YEL"这张图谱是一个卷轴舒开，帛面年深日久，已成焦黄之色，图上开头写着： \n"+
		  "“六脉神剑”以一阳指指力为根基，将一阳指的指力化作剑气，有质无形，可\n"+
		  "称无形气剑。所谓六脉，即手之六脉太阴肺经、厥阴心包经、少阴心经、太阳\n"+
		  "小肠经、阳明胃经、少阳三焦经，六脉神剑，即是由六脉劲气化出的六种无形\n"+
		  "剑气。。。紧跟着帛上绘着个裸体男子的图形，身上注明穴位，以红线黑线绘\n"+
		  "着内力的运走径道，旁边注着一行小字“关冲剑运气法门”。\n" NOR;
}

string look_right(object me)
{
	return YEL"这张图谱是一个卷轴舒开，帛面年深日久，已成焦黄之色，图上都是纵横交叉\n"+
		  "的直线、圆圈和弧形，但见红线黑线，纵横交错，头绪纷繁之极，这图便是关\n"+
		  "冲剑的剑法，这路剑法以拙滞古朴取胜，一招一式看似笨拙无比，其实包含极\n"+
		  "大的后着。\n" NOR;
}

void init()
{
	add_action("do_study", "yanxi");
	add_action("do_study", "xuexi");
	add_action("do_study", "xiulian");    
}

int do_study(string arg)
{
	object me,weapon;
	string *skill;
	int j,lvl,neili;
	mapping skill_name;
	me=this_player();
       
	neili=me->query("max_neili");
	skill_name = me->query("liumai-shenjian");
	lvl=me->query_skill("liumai-shenjian",1);
	if (skill_name)
		skill=keys(skill_name);

	j=sizeof(skill);

	weapon = me->query_temp("weapon");

	if(me->is_busy()|| me->is_fighting()) 
		return notify_fail("你正忙着呢！\n");

	if (!arg) return 0;   

	if (weapon )
		return notify_fail("你手中拿着东西，怎么练？\n");   

	if(arg=="left" ) {
		if (lvl > 30*(j+1))
			me->set_skill("liumai-shenjian",30*(j+1));
           if ((j+1) > 6 && me->query_skill("liumai-shenjian", 1) >= 180)
                   return notify_fail("你已经领会了所有六脉神剑了！\n"); 
		if (neili < (j+1)*3000+1500 && !me->query("liumai-shenjian/guanchong"))
			return notify_fail("你竭尽全力的驱动体内的一阳指真气，试图由关冲穴射出无形剑气，却无半点劲气发出。\n");
		if (me->query("neili",1)<50)
			return notify_fail("你的内力快不够了！\n");   
		if (me->query("jing",1)<50)
			return notify_fail("你的精神快不够了！\n"); 
		me->receive_damage("jing",40+random(10));
		me->receive_damage("neili",40+random(10));
		if ( lvl >= 30*(j+1) || me->query("liumai-shenjian/guanchong",1)){
			write("你内力运转自如，凝聚真气，无名指一出，嗤嗤声响，一条无形剑气自“关冲”穴中激射而出。\n");
			if (!me->query("liumai-shenjian/guanchong"))
				me->add("liumai-shenjian/guanchong", 1);
			if ( lvl < 30*j)
				me->improve_skill("liumai-shenjian", me->query("int"));
		}
		else {
			write("你照着图谱研习关冲剑法的运气法门，渐渐的悟出其中的精要所在。\n");
			if (!me->query("liumai-shenjian/guanchong"))
				me->improve_skill("liumai-shenjian", me->query("int"));
		}
		return 1;
	}
	else if (arg=="right") {
		if (!me->query("liumai-shenjian/guanchong"))
			return notify_fail("你已经竭尽全力去体会图谱上的剑法，可惜这一路剑法的剑气你还没有练成！\n");
		if (me->query("neili",1) < 60)
			return notify_fail("你的内力快不够了！\n");   
		if (me->query("jing",1) < 60)
			return notify_fail("你的精神快不够了！\n");
		me->receive_damage("jing",50+random(10));
		me->receive_damage("neili",50+random(10));
		write("你照着剑谱研习关冲剑法，渐渐的悟出其中的精要所在。\n");
		me->add_temp("guanchong", 1);
		if (me->query_temp("guanchong")>=10) {
			me->add("liumai-shenjian/guanchong", 1);
			me->set_temp("guanchong",0);
			write("你凝聚真气，拇指点处，将图上的关冲剑法演练了一遍。\n");
		}
		return 1;
	}
}

int valid_leave(object me, string dir)
{
	me->set_temp("guanchong", 0);
	return 1;        
}
