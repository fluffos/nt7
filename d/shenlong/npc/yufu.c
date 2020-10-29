// dizi.c

#include <ansi.h>

#define YOU RANK_D->query_respect(this_object())
#define ME  RANK_D->query_respect(me)
#define DIALOG_D "/adm/daemons/dialogd"

inherit NPC;

mixed ask_shejing();

void create()
{
	set_name("神秘渔夫", ({"shenmi yufu"}));
	set("long",
	        "这是一个附近岛屿上的渔夫，看样子是遇到风浪到此暂时躲避的。\n"
	);

	set("gender", "男性");
	set("attitude", "peaceful");

	set("age", 50 + random(30));
	
	set("str", 25 + random(10));
	set("dex", 25 + random(10));
	set("max_qi", 20000);
	set("max_jing", 15000);
	set("neili", 20000);
	set("max_neili", 20000);
	set("jiaji", 50 + random(5));
	set("combat_exp", 10000000 + random(100000));

	set("inquiry", ([
                //"蛇精" : (: ask_shejing :),
		"阿鼻道第三刀" : "如果你能证明你参与过对抗蛇精之战，这第三刀的秘密我便告诉你。\n",
	]));

	set_skill("force", 40);
	set_skill("dodge", 40);
	set_skill("unarmed", 40);
	set_skill("parry", 40);
	set_skill("sword", 50);
	set_skill("blade", 50);
        set("chat_chance", 5);
        set("chat_msg", ({
"渔夫叹道：听说这神龙岛上的蛇精又要出来害人了，孽障啊，孽障~~\n",
        }) );

	setup();

	carry_object("/clone/misc/cloth")->wear();
}

mixed ask_shejing()
{
	string *msg;

	object me;

	me = this_player();

	msg = ({
		"渔夫打量了一下你说道：这位" + ME + "恐怕是刚来这神龙岛的吧，呵呵~~",
		"你说道：正是！",
		"渔夫点了点头又道：老朽是这岛附近的一个渔夫，在这附近打渔已经40多年了，还从未见过这蛇精呢。",
		"你疑惑到：哦？那" + YOU + "刚才口中所说的蛇精是怎么回事？难道这岛上真有蛇精不成？",
		"渔夫道：听祖辈们说过，这岛原不叫神龙岛，而叫蛇岛，这岛上有着成千上万种怪蛇，这些蛇凶猛无比，任何踏足\n"
		"岛上的人它们都会主动攻击，据说，进入蛇岛深处的人至今还无一人生还　……",
		"你说道：既然如此，那为什么那些人又要上蛇岛呢，难道这岛上有宝贝不成？",
		"渔夫摇了摇头道：" + ME + "有所不知：这蛇岛地处交通要地，凡是出去捕渔的渔夫都会经过此地，每逢遇到风浪，附近\n"
		"捕渔的渔夫都会上岛躲避风浪，但是，一旦踏足这蛇岛就再无人生还，哎～",
		"你说道：那为什么附近的渔民不自己组织一批身强力壮之士来将这些蛇全部杀掉，这不就可以永绝后患了吗？",
		"渔夫叹了口气道：听我的祖辈们说，他们先后组织了四批勇士前来岛上，这四批勇士每个都是身怀绝迹，并且都带着\n"
		"火把、硫磺，装备着各种兵器、铠甲，起初进入蛇岛，一切都还顺利，将蛇杀得几乎一条不留，但是到后来……",
		"你急切道：后来，后来怎么了？难道是？",
		"渔夫点了点头继续道：但是后来，他们却发现这岛上的射就犹如江河水一般，源源不断，始终杀不完，而且越杀越多，\n"
		"到最后这些勇士一个个都是耗尽精力被群射缠食而死。",
		"你迫不及待地追问道：这难道是蛇精在作祟？",
		"渔夫稍有惧色道：蛇精，蛇精！谁有没见过，当时这四批公认最厉害的勇士全军覆没后，也再没人敢提这件事了，从此附近\n"
		"渔民外出捕渔都是绕过此岛，即使是遇到风浪也不再踏足此岛。后来，这事就渐渐被人遗忘。",
		"你说道：那后来呢？没人见过蛇精怎么会有人知道是蛇精在作祟呢？",
		"后来有一位游方道人到此小住，见渔民出外捕渔都是避蛇岛而远之，便觉奇怪，后来多放打探才知道原委。这位道人为报答\n"
		"渔民盛情，事后，开坛做法，欲除去这岛上之害，但是，这位道人道行有限，一系列法事后，他告诉附近村民说，经他开坛\n"
		"做法虽不能解除蛇岛之患，但他算出这蛇岛上的毒蛇并非原本就有，而是来自与这蛇岛上的千年蛇精，只要这只蛇精不\n"
		"除，蛇岛之患便永久无法解除。",
		"你连忙问道：那这位道人有没有说怎么才能杀掉这两只蛇精呢？",
		"渔夫摇头道：这我就不是很清楚了，刚才我所说的也是听我父辈口述，只知道后来蛇精被压在这蛇岛底，这岛也改名叫神龙岛，\n"
		"至于其中来龙去脉我就不得而知了，但是，据说，最后有一位叫赛神龙的勇士降伏了蛇精",
		"你说道：哦？赛神龙，何许人也？",
		"渔夫道：我听我祖辈说，赛神龙乃人中龙凤，武艺超群，当年，由他带头降伏了蛇精，并终身驻守神龙岛，以防蛇精重出人间。",
		"你说道：那怎么才能找到赛神龙？",
		"渔夫道：听说他就驻守在此岛的蛇精洞内，但是，千百年来也无人再敢进入 ……",
		"你说道：多谢！",

	});

	DIALOG_D->start_dialog(this_object(), me, msg);

	return 1;

}

int accept_object(object me, object ob)
{
	if (! objectp(me) || ! objectp(ob))return 0;
	
	if( query("id", ob) != "shejing linpian" )
	{
		return 0;
	}
	
	command("yi");
	
	if( !query("can_perform/badao/san-2", me) )
	{
		command("say 这不是从九头蛇精身上掉下鳞片吗！阁下勇气超群，老夫佩服，佩服！");
		command("tan");
		command("say 可惜你还未掌握阿鼻道第二刀的精髓，等你学会阿鼻道第二刀再来吧！");
		return 0;
	}

	if( query("can_perform/badao/san", me) )
	{
		command("bow"+query("id", me));
		command("say 阁下定会扬名江湖！！");
		return 0;
	}

	if (me->query_skill("badao", 1) < 1000)
	{
		command("say 这不是从九头蛇精身上掉下鳞片吗！阁下勇气超群，老夫佩服，佩服！");
		command("tan");
		command("say 可惜你霸刀火候还不够，这第三刀恐怕不能传你！");
		return 0;
	}
/*
	if( query("scborn/cur_lunhui_point", me)<8 && !query("thborn/ok", me) )
	{
		command("say 这不是从九头蛇精身上掉下鳞片吗！阁下勇气超群，老夫佩服，佩服！");
		command("tan");
		command("say 可惜你轮回点不足，这第三刀恐怕不能传你！");
		return 0;		
	}
*/
		
	command("say 这不是从九头蛇精身上掉下鳞片吗！阁下勇气超群，老夫佩服，佩服！");
	command("nod");
	command("say 阁下如此勇气，日后定当扬名江湖，老夫便将这失传已久的阿鼻道第三刀传你，你可听好了 ...");

	tell_object(me, HIG "恭喜你，领悟了阿鼻道第三刀！\n" NOR);
	tell_object(me, HIR "恭喜你，已经领悟了阿鼻道三刀的所有招式，阿鼻道三刀已经练成！\n" NOR);
set("can_perform/badao/san", 1, 	me);

/*
	// 扣除轮回点
	if( !query("thborn/ok", me) )
addn("scborn/cur_lunhui_point", -8, 		me);

	// 设置扣除轮回点的出处
	if( !query("thborn/ok", me) )
set("scborn/perform_san_yufu", 1, 		me);
*/
	
	me->save();
	
	destruct(ob);
	
	return 1;
}
