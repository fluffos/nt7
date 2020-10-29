// linzhennan.c 林震南
// modified by XiaoYao 98/12/16
// Modify by Lklv 2001.10.12

#include <ansi.h>

inherit NPC;
#include "hubiao.h";

int ask_fuwei();
int ask_yuantu();
int ask_pixie();
int ask_tong();

void create()
{
	set_name("林震南", ({ "lin zhennan", "lin", "zhennan" }));
	set("gender", "男性");
	set("age", 45);
	set("long", "他就是「福威镖局」的总镖头－－林震南。\n");

	set("combat_exp", 30000);
	set("shen_type", 1);

	set("max_neili", 500);
	set("jiali", 10);
	set("no_get","林震南对你来说太重了。\n");

	set_skill("force", 40);
	set_skill("sword", 50);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);

	set("inquiry", ([
		"向阳老宅" : "那是我家从前的宅院，已经没有人住了。",
		"福威镖局" : (: ask_fuwei :),
		"远图公" : (: ask_yuantu :),
		"林远图" : "哼！小孩子这么没礼貌，直呼先人名讳！",
		"辟邪剑法" : (: ask_pixie:),
		"铜钱" : (: ask_tong:),
		"铜板" : (: ask_tong:),
		"押镖" : (: test_dart :),
		"护镖" : (: test_dart :),
		"job" : (: test_dart :),
	]) );

	set("chat_chance", 2);
	set("chat_msg", ({
		CYN"林震南说道：「这个月镖局生意不错！」\n"NOR,
	}) );
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/damage", 15);

	setup();
	carry_object(BINGQI_D("changjian"))->wield();
        carry_object(ARMOR_D("cloth"))->wear();
        carry_object(ARMOR_D("shoes"))->wear();
}

int ask_fuwei()
{
	say(CYN"林震南炫耀地说：「我们林家三代走镖，一来仗着先祖远图公当年闯下的威名，\n"
	"二来靠著我们林家家传的玩艺儿不算含糊，这才有今日的局面，成为大江以南\n"
	"首屈一指的大镖局。江湖上提到『福威镖局』四字，谁都要翘起大拇指，说一\n"
	"声：『好福气！好威风！』哈哈，哈哈！」\n"NOR);
	this_player()->set_temp("marks/林1", 1);
	return 1;
}

int ask_yuantu()
{
	if (this_player()->query_temp("marks/林1")) {
		say(CYN"林震南磕一磕烟斗，说道：「远图公是我的祖父，福威镖局是他一手创办的。\n"
		"当年祖父以七十二路辟邪剑法开创镖局，当真是打遍黑道无敌手。其时白道上\n"
		"英雄见他太过威风，也有去找他比试武艺的，青城派掌门余观主的师父长青子\n"
		"少年之时便在他辟邪剑法下输了几招。」\n"NOR);
		this_player()->set_temp("marks/林2", 1);
		return 1;
	}
	say(CYN"林震南说道：「远图公是我的祖父。」\n"NOR);
	return 1;
}

int ask_pixie()
{
	int p1, p2, p3, p4;

	if (this_player()->query("combat_exp") < 100000) {
		message_vision(CYN"$N勃然大怒，喝道：「你也窥视我们林家的辟邪剑谱？！我跟你拼了！」\n" NOR, this_object());
		kill_ob(this_player());
	} 
	else {
		if (this_player()->query("quest/pixie/pxj_passwd"))
			say(CYN"林震南不悦地说道：「我不是都告诉你了吗？我的剑法不及先祖。」\n"NOR);
		else if (this_player()->query_temp("marks/林2")) {
			say(CYN"林震南一惊，说道：「你怎么知道的？噢，我刚才说露嘴了。嗨，在下的功夫\n"
			"外人不知底细，其实及不上先祖。」\n"NOR);
			write(CYN"林震南顿一顿，接着低声说道：「先祖去世前，曾给家父留下");
			p1=random(4)+1;
			p2=random(4)+1;
			p3=random(4)+1;
			p4=random(4)+1;
			this_player()->set("quest/pixie/pxj_passwd", p1*1000+p2*100+p3*10+p4);
			write(chinese_number(this_player()->query("quest/pixie/pxj_passwd")));
			write("\n个铜钱，我一直未解其中奥秘。」\n"NOR);
		}
		else {
			message_vision(CYN"$N勃然大怒，喝道：「你也窥视我们林家的辟邪剑谱？！我跟你拼了！」\n" NOR,this_object());
			kill_ob(this_player());
		}
		this_player()->delete_temp("marks/林1");
		this_player()->delete_temp("marks/林2");
	}
	return 1;
}

int ask_tong()
{
	int p;

	if (!(p=this_player()->query("quest/pixie/pxj_passwd")))
		say(CYN"林震南一脸讥笑的样子，说：「怎么混到这一步了到处要钱？」\n"NOR);
	else {
		write(CYN"林震南低声说：「先祖去世前，曾给家父留下");
 		write(chinese_number(p));
 		write("个铜钱，我一直\n未解其中奥秘。」\n"NOR);
	}
	return 1;
}
