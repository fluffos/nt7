// 通宝物品答疑 mm2.c
// by fengyue 0808
#include <ansi.h>

inherit NPC;

int do_look(string);
int ask_me();
int ask_wuliao();

int ask_cantu();
int ask_daopu();
int ask_ebook();
int ask_tianlong();
int ask_jingpa();
int ask_kongxin();
int ask_pearl();
int ask_putao();
int ask_shuzhi();
int ask_suizhi();
int ask_taijitu();
int ask_wcard();
int ask_yuji();
int ask_zhanshu();
int ask_shenshu();
int ask_fail();


void create()
{
     set_name("奥黛雷赫", ({ "audrey hepburn","girl", "meimei" }) );
      set("title",HIC"假日公主"NOR);
     //set("nickname",HIR"专 用"NOR);
     set("gender", "女性" );
     set("age", 18);
     set("long","奥黛丽·凯瑟琳·赫本-鲁斯顿（Audrey Kathleen Hepburn-Ruston）;\n"+
                "假日里的小公主。\n");
     set("combat_exp", 10000);
     set("attitude", "friendly");
     set("no_get", 1);
     set("per", 30);
     set("inquiry", ([
//                   "sex" :         (: ask_me :),
//                  "make love" :   (: ask_me :),
//                   "QQ" :          (: ask_wuliao :),
//                   "电话号码" :    (: ask_wuliao :),
//                   "qq" :          (: ask_wuliao :),
//                   "msn" :         (: ask_wuliao :),
//                   "手机号码" :    (: ask_wuliao :),
//                   "name" :        (: ask_wuliao :),

                   "苗家剑法残图" : (: ask_cantu :),
                   "cantu" :        (: ask_cantu :),

                   "破旧刀谱" :     (: ask_daopu :),
                   "daopu" :        (: ask_daopu :),

                   "精英之书" :     (: ask_ebook :),
                   "ebook" :        (: ask_ebook :),

                   "天龙八部" :     (: ask_tianlong :),
                   "tianlong" :     (: ask_tianlong :),

                   "鸳鸯锦帕" :     (: ask_jingpa :),
                   "jingpa" :       (: ask_jingpa :),

                   "空心散" :       (: ask_kongxin :),
                   "kongxinsan" :   (: ask_kongxin :),

                   "幸运珍珠" :     (: ask_pearl :),
                   "pearl" :        (: ask_pearl :),

                   "神奇葡萄" :     (: ask_putao :),
                   "putao" :        (: ask_putao :),

                   "小树枝"  :      (: ask_shuzhi :),
                   "xiaoshuzhi"  :  (: ask_shuzhi :),

                   "碎纸片" :       (: ask_suizhi :),
                   "suizhi pian" :  (: ask_suizhi :),

                   "太极图" :       (: ask_taijitu :),
                   "taijitu" :      (: ask_taijitu :),

                   "清池贵宾卡" :   (: ask_wcard :),
                   "guibinka" :     (: ask_wcard :),


                   "玉肌丸" :       (: ask_yuji :),
                   "yujiwan" :      (: ask_yuji :),

                   "独孤战书" :     (: ask_zhanshu :),
                   "zhanshu" :      (: ask_zhanshu :),

                   "金庸全集" :     (: ask_shenshu :),
                   "shenshu" :      (: ask_shenshu :),

                   "失败" :     (: ask_fail :),

                     ]) );

      setup();
         carry_object(ARMOR_D("changqun"))->wear();
         carry_object(ARMOR_D("flower_shoe"))->wear();
}


void init()
{
	object ob;

	::init();
	add_action("do_look","kiss1");
	add_action("do_look","kick");
	add_action("do_look","flirt");
	add_action("do_look","loveshoe");

	if( interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

int ask_me()
{
	object me;

	me = this_player();
	switch( random(5) ) {
		case 0:
			message("vision", "美眉向" + me->name() +"怒道：你无聊不无聊呀。流氓！你出去！\n", me );
			command("slap " + me->query("id"));
			remove_call_out("kicking");
			call_out("kicking", 1, me);
			break;
		case 1:
			message("vision", "美眉向" + me->name() +"怒道：你无聊不无聊呀。流氓！你出去！\n", me );
			command("kick " + me->query("id"));
			remove_call_out("kicking");
			call_out("kicking", 1, me);
			break;
		case 2:
			command("faint " + me->query("id"));
			break;
		case 3:
			command("rascal " + me->query("id"));
			command("kick2 " + me->query("id"));
			break;
		case 4:
			command("xixi " + me->query("id"));
			command("benger " + me->query("id"));
	}
	return 1;
}

int do_look(string target)
{
	object me;

	me = this_player();
	if (target=="shuang" || target=="shuang er")
	if ((string)me->query("gender") != "女性") {
		message("vision", "美眉向" + me->name() +"道：你无聊不无聊呀。\n", me );
		switch( random(5) ) {
			case 0:
				command("club " + me->query("id"));
				remove_call_out("kicking");
				call_out("kicking", 1, me);
				break;
			case 1:
				command("kick " + me->query("id"));
				remove_call_out("kicking");
				call_out("kicking", 1, me);
				break;
			case 2:
				command("faint " + me->query("id"));
				break;
			case 3:
				command("stare " + me->query("id"));
				break;
			case 4:
				command("rascal " + me->query("id"));
				command("kick2 " + me->query("id"));
		}
	}
	return 0;

}

void kicking(object me)
{
	if (!me || environment(me) != environment()
	|| environment(this_object())->query("short") != "当铺")
		return;

	me->move("/d/city/guangchangnan");
	message("vision","只听“嘭”地一声，紧接着" +  me->query("name") +
		"从当铺里飞了出来，脸上一个红手印，屁股上有一个小鞋印。\n", environment(me), me);
}

int ask_wuliao()
{
     object me;

	me = this_player();
            command("mimi "+me->query("id") );
            command("? ");
            command("hmm ");
         return 1;
}

int ask_cantu()
{
     object me;
     me = this_player();
     command("say 本周你好象已经翻阅过"+ chinese_number(me->query("spec/cantu")) +NOR"次苗家剑法残图了。");
     command("say 这些残图我已经翻(fanyue mjjf cantu)过好多遍了，可是上面的剑招太难了，没人指点，我总是学不会。");
     command("sigh ");
     command("say 你知道谁能指点我一下嘛？要不等你学会了回来教我好不好？ ");
     command("addoil girl ");
         return 1;
}
int ask_daopu()
{
     object me;
     me = this_player();
     command("say 本周你已经弄坏了"+ HIR+chinese_number(me->query("spec/daopu")) +NOR"本破旧刀谱了。");
     command("say 据说这上面纪录的是传说中享誉江湖的胡家刀法呢！");
     command("say 看不清楚的话,我可以借个放大镜给你仔细辨认一下(bianren pojiu daopu)，不过你要请我吃哈根达斯哦！");
     command("smile ");
         return 1;
}
int ask_ebook()
{
     object me;
     me = this_player();
     command("say 本周你已经用掉了"+ HIR+chinese_number(me->query("spec/ebook")) +NOR"本精英之书。");
     command("say 怎么才涨了这么点经验啊？");
     command("push ");
         return 1;
}
int ask_tianlong()
{
     object me;
     me = this_player();
     command("say 本周你已经读(read)过"+ HIR+chinese_number(me->query("spec/tianlong")) +NOR"遍天龙八部了。");
     command("say 我最崇拜里面的萧峰萧大哥了！");
     command("say 最可怜的人还是阿紫啊！");
     command("sigh ");
         return 1;
}
int ask_jingpa()
{
     object me;
     me = this_player();
     command("say 本周你已经归还给瑛姑阿姨"+ HIR+chinese_number(me->query("spec/jingpa")) +NOR"方鸳鸯锦帕。");
     command("say 她有没有教你点鬼谷神机术啊？");
     command("say 不过这死老太婆老不肯教我，说我笨。");
     command("shout ");
         return 1;
}
int ask_kongxin()
{
     object me;
     me = this_player();
     command("say 本周你已经服用过"+ HIR+chinese_number(me->query("spec/kongxin")) +NOR"次空心散。");
     command("say 服用一点逍遥自在，就会把江湖琐事忘的干干净净。");
     command("say 这东西不会就是传说中的K粉吧");
     command("fear ");
         return 1;
}
int ask_pearl()
{
     object me;
     me = this_player();
     command("say 本周你已经对着它祈祷(pary)过"+ HIR+chinese_number(me->query("spec/pearl")) +NOR"次了。");
     command("say 我有这样一串珍珠手链呢。");
     command("say 不过我还是觉得自己挺倒霉的，老是碰见些色狼来骚扰我。");
     command("club ");
         return 1;
}
int ask_putao()
{
     object me;
     me = this_player();
     command("say 本周你已经吃过"+ HIR+chinese_number(me->query("spec/putao")) +NOR"串神奇葡萄。");
     command("say 酸酸甜甜就是我。");
     command("sing ");
         return 1;
}

int ask_shuzhi()
{
     object me;
     me = this_player();
     command("say 本周你已经随手乱丢过"+ HIR+chinese_number(me->query("spec/shuzhi")) +NOR"根小树枝了。");
     command("say 乱丢垃圾是要罚款的哦！");
     command("say 左圆右方，这么简单的事情嘛，我也能画(hua fangyuan)出来哦！");
     command("draw lao ban ");
         return 1;
}

int ask_suizhi()
{
     object me;
     me = this_player();
     command("say 本周你已经随手乱丢过"+ HIR+chinese_number(me->query("spec/suizhi")) +NOR"团碎纸片了。");
     command("say 你老是翻来覆去的拿着它看什么啊(chakan suizhi pian)？");
     command("say 不可能是张教主藏经图的啦！");
     command("giggle ");
     command("say 张教主早回家种田去了，传闻多少年都没出了。");
     command("laugh ");
         return 1;
}
int ask_taijitu()
{
     object me;
     me = this_player();
     command("say 本周你已经盯着这张太极图研究(yanjiu taiji tu)"+ HIR+chinese_number(me->query("spec/taijitu")) +NOR"次啦。");
     command("say 邋遢道士天天嘟囔着太极深意，可意会不可言传。");
     command("say 要不你去问问他吧。");
         return 1;
}
int ask_wcard()
{
     object me;
     me = this_player();
     command("say 本周你已经用掉了"+ HIR+chinese_number(me->query("spec/wcard")) +NOR"张贵宾卡。");
     command("say 我爱洗澡，皮肤好好！");
     command("sing ");
     command("say 没事你秀(show card)啥呢？你以为就你自己办过了啊？");
     command("wah "+ me->query("id") +" ");

         return 1;
}


int ask_zhanshu()
{
     object me;
     me = this_player();
     command("say 本周你已经拆阅(yuedu)过"+ HIR+chinese_number(me->query("spec/zhanshu")) +NOR"封独孤战书。");
     command("say 独孤九剑，难道天下真的有这么高明的剑法么？ ");
     command("think ");
     return 1;
}

int ask_yuji()
{
     object me;
     me = this_player();
     command("say 本周你已经服用过"+ HIR+chinese_number(me->query("spec/yuji")) +NOR"粒玉肌丸。");
     command("say 本周你已经服用过"+ HIR+chinese_number(me->query("spec/yuji1")) +NOR"粒极品玉肌丸。");
     command("say 朵尔胶囊，以内养外，补肾养颜....");
     command("blush ");
         return 1;
}

int ask_shenshu()
{
     object me;
     me = this_player();
     command("say 本周你已经阅读过"+ HIR+chinese_number(me->query("spec/shenshu")) +NOR"次金庸全集。");
         return 1;
}

int ask_fail()
{
     object me;
     me = this_player();
     command("say " + HIW + "九阴神功上卷" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/jiuyin1/fail"))+NOR"次。\n");
     command("say " + HIG + "九阴神功下卷" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/jiuyin2/fail"))+NOR"次。\n");
     command("say " + HIB + "冷泉神功" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/雪山飞狐/武功/lengquanfail"))+NOR"次。\n");
     command("say " + HIW + "蛤蟆功" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/hama/fail"))+NOR"次。\n");
     command("say " + HIC + "凌波微步" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("天龙八部/武功/fail"))+NOR"次。\n");
     command("say " + HIR + "葵花宝典" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/pixie/fail"))+NOR"次。\n");
     command("say " + HIW + "左右互搏" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/hubo/fail"))+NOR"次。\n");
     command("say " + HIR + "凝血神爪" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/ningxue/fail"))+NOR"次。\n");
     command("say " + HIG + "金刀黑剑" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/jindaoheijian/fail"))+NOR"次。\n");
     command("say " + HIC + "太玄功" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/taixuan/fail"))+NOR"次。\n");
     command("say " + HIR + "千蜘万毒手" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/qianzhu/fail"))+NOR"次。\n");
     command("say " + HIM + "杨家枪" + NOR + "，已经失败了"+ HIR+chinese_number(me->query("quest/yangjiaqiang/fail"))+NOR"次。\n");
         return 1;
}
