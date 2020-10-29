// cateran.c
// Modify By River@SJ
// Validate By YUJ@SJ 2002-01-17

#include <ansi.h>
inherit NPC;
int do_copy(object ob);

string *title = ({
	"天河帮", "长鲸岛", "神农帮", "巨鲸帮", "海沙派", "青竹帮",
	"龙游帮", "金龙帮", "鄱阳帮", "恶虎沟", "千柳庄"
});

void create()
{
string weapon = "null" , menpai;
	mapping name;
	int i;

	i = random(4);

name = RNAME_D->get_random_name(i);
set_name(name["name"], name["id"] + ({ "jie fei" }));
set("title", HIW+title[random(sizeof(title))]+NOR+(i?"":"女")+"帮众");
set("gender", i?"男性":"女性");
set("age", 27+random(30));

set("long","这个拦路的劫匪是"+query("title")+"，满脸伤疤，一脸凶狠而霸道的样子。\n");
set("attitude", "peaceful");
set("combat_exp", 5000000);

set("str",35+random(5));
set("int",35+random(5));
set("con",35+random(5));
set("dex",35+random(5));

	set("hubiao_jiefei", 1);
	set("max_qi", 20000);
	set("max_jing", 20000);
	set("max_neili", 5000);
	set("max_neili", 20000);
	set("neili", 5000);
	set("neili", 20000);
	set_temp("apply/armor", 200);
  set_temp("apply/defense", 100);
	set("eff_jing", 20000);
	set("eff_jingli", 20000);
	set("jingli", 20000);
	set("max_jingli", 20000);

	set("no_ansuan",1);
	set("no_bark", 1);
	set("no_quest", 1);
	set("location", 1);

	set_skill("strike", 500);
	set_skill("cuff", 500);
	set_skill("hand", 500);
	set_skill("dodge", 500);
	set_skill("sword", 500);
	set_skill("force", 500);
	set_skill("parry", 500);
	set_skill("blade", 500);
	set_skill("hammer", 500);
	set_skill("stick", 500);
	set_skill("club", 500);
	set_skill("staff", 500);
	set_skill("literate", query("int") * 10);
	set_skill("whip", 500);
	set_skill("dagger", 500);
	set("location",1);
	set("no_get", 1);

	switch( random(32) ) {
		case 0:  // wd1
		set_skill("yinyun-ziqi", 500);
		set_skill("tiyunzong", 500);
		set_skill("taiji-jian", 500);
		set_skill("taiji-quan", 500);
		map_skill("force", "yinyun-ziqi");
		map_skill("dodge", "tiyunzong");
		map_skill("sword", "taiji-jian");
		map_skill("parry", "taiji-quan");
		map_skill("cuff", "taiji-quan");
		prepare_skill("cuff", "taiji-quan");
	  set("chat_chance_combat", 50);
		set("chat_msg_combat", ({
			(: exert_function, "cuff.gangrou" :),
			(: perform_action, "cuff.taiji" :),
			(: perform_action, "cuff.ji" :),
			(: perform_action, "cuff.zhen" :),
			(: perform_action, "cuff.luanhuan" :),
		}));
		menpai = "武当";
		break;
		case 1:  // wd2
		set_skill("yinyun-ziqi", 500);
		set_skill("tiyunzong", 500);
		set_skill("taiji-jian", 500);
		set_skill("taiji-quan", 500);
		map_skill("force", "yinyun-ziqi");
		map_skill("dodge", "tiyunzong");
		map_skill("sword", "taiji-jian");
		map_skill("parry", "taiji-jian");
		map_skill("cuff", "taiji-quan");
		prepare_skill("cuff", "taiji-quan");
	  set("chat_chance_combat", 50);
		set("chat_msg_combat", ({
			(: perform_action, "dodge.zong" :),
			(: perform_action, "sword.chan" :),
			(: perform_action, "sword.sanhuan" :),
		  (: perform_action, "sword.lian" :),
		}));
		weapon = "sword";
		menpai = "武当";
		break;
		case 2:  // sl1
		set_skill("yijin-jing", 500);
		set_skill("shaolin-shenfa", 500);
		set_skill("riyue-bian", 500);
		set_skill("yizhi-chan", 500);
		map_skill("force", "yijin-jing");
		map_skill("dodge", "shaolin-shenfa");
		map_skill("whip", "riyue-bian");
		map_skill("parry", "riyue-bian");
		map_skill("finger", "yizhi-chan");
		prepare_skill("finger", "yizhi-chan");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "jingang" :),
			(: perform_action, "whip.chanrao" :),
			(: perform_action, "whip.fumoquan" :),
		}));
		weapon = "whip";
		menpai = "少林";
		break;
		case 3:  // huashan1
		set_skill("huashan-qigong", 500);
		set_skill("huashan-shenfa", 500);
		set_skill("huashan-jianfa", 500);
		set_skill("hunyuan-zhang", 500);
		map_skill("force", "huashan-qigong");
		map_skill("dodge", "huashan-shenfa");
		map_skill("sword", "huashan-jianfa");
		map_skill("parry", "huashan-jianfa");
		map_skill("strike", "hunyuan-zhang");
		prepare_skill("strike", "hunyuan-zhang");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "yujianshi" :),
			(: perform_action, "sword.shijiushi" :),
			(: perform_action, "sword.lianhuan" :),
		}));
		weapon = "sword";
		menpai = "华山";
		break;
		case 4:  // sl3
		set_skill("yijin-jing", 500);
		set_skill("shaolin-shenfa", 500);
		set_skill("yizhi-chan", 500);
		map_skill("force", "yijin-jing");
		map_skill("dodge", "shaolin-shenfa");
		map_skill("parry", "yizhi-chan");
		map_skill("finger", "yizhi-chan");
		prepare_skill("finger", "yizhi-chan");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "jingang" :),
			(: perform_action, "finger.wofo" :),
			(: perform_action, "finger.qiankun" :),
		}));
		menpai = "少林";
		break;
		case 5:  // hs1
		set_skill("huashan-qigong", 500);
		set_skill("dugu-jiujian", 500);
		set_skill("hunyuan-zhang", 500);
		map_skill("force", "huashan-qigong");
		map_skill("dodge", "dugu-jiujian");
		map_skill("sword", "dugu-jiujian");
		map_skill("parry", "dugu-jiujian");
		map_skill("strike", "hunyuan-zhang");
		prepare_skill("strike", "hunyuan-zhang");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "yujianshi" :),
			(: perform_action, "sword.poqi" :),
			(: perform_action, "sword.zongjue" :),
		}));
		weapon = "sword";
		menpai = "华山";
		break;
		case 6:  // hs2
		set_skill("zixia-gong", 500);
		set_skill("huashan-shenfa", 500);
		set_skill("fanliangyi-dao", 500);
		set_skill("poyu-quan", 500);
		map_skill("force", "zixia-gong");
		map_skill("dodge", "huashan-shenfa");
		map_skill("blade", "fanliangyi-dao");
		map_skill("parry", "fanliangyi-dao");
		map_skill("cuff", "poyu-quan");
		prepare_skill("cuff", "poyu-quan");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "zixia" :),
			(: perform_action, "blade.sanshenfeng" :),
		}));
		weapon = "blade";
		menpai = "华山";
		break;
		case 7:  // gb1
		set_skill("huntian-qigong", 500);
		set_skill("bangjue", 500);
		set_skill("xiaoyaoyou", 500);
		set_skill("dagou-bang", 500);
		set_skill("xianglong-zhang", 500);
		map_skill("force", "huntian-qigong");
		map_skill("dodge", "xiaoyaoyou");
		map_skill("stick", "dagou-bang");
		map_skill("parry", "dagou-bang");
		map_skill("strike", "xianglong-zhang");
		prepare_skill("strike", "xianglong-zhang");
	  set("chat_chance_combat", 40);
		set("chat_msg_combat", ({
			(: exert_function, "huntian" :),
			(: perform_action, "stick.chuo" :),
			(: perform_action, "stick.chan" :),
			(: perform_action, "stick.pi" :),				
		}));
		weapon = "stick";
		menpai = "丐帮";
		break;
		case 8:  // gb2
		set_skill("huntian-qigong", 500);
		set_skill("bangjue", 500);
		set_skill("xiaoyaoyou", 500);
		set_skill("dagou-bang", 500);
		set_skill("xianglong-zhang", 500);
		map_skill("force", "huntian-qigong");
		map_skill("dodge", "xiaoyaoyou");
		map_skill("stick", "dagou-bang");
		map_skill("parry", "xianglong-zhang");
		map_skill("strike", "xianglong-zhang");
		prepare_skill("strike", "xianglong-zhang");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "strike.xiao" :),
			(: perform_action, "strike.paiyun" :),
		}));
		menpai = "丐帮";
		break;
		case 9:  // thd1
		set_skill("bihai-chaosheng", 500);
		set_skill("qimen-bagua", 500);
		set_skill("suibo-zhuliu", 500);
		set_skill("yuxiao-jian", 500);
		set_skill("tanzhi-shentong", 500);
		set_skill("lanhua-shou", 500);
		set_skill("luoying-zhang", 500);
		set_skill("xuanfeng-tui", 500);
		map_skill("force", "bihai-chaosheng");
		map_skill("dodge", "suibo-zhuliu");
		map_skill("sword", "yuxiao-jian");
		map_skill("parry", "yuxiao-jian");
		map_skill("finger", "tanzhi-shentong");
		prepare_skill("finger", "tanzhi-shentong");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "maze" :),
			(: perform_action, "sword.yuxiao" :),
			(: perform_action, "sword.feiying" :),
			(: perform_action, "sword.qimen" :),
		}));
		set("thd/perform",999);
		weapon = "xiao";
		menpai = "桃花岛";
		break;
		case 10: // thd2
		set_skill("bihai-chaosheng", 500);
		set_skill("qimen-bagua", 500);
		set_skill("suibo-zhuliu", 500);
		set_skill("yuxiao-jian", 500);
		set_skill("tanzhi-shentong", 500);
		map_skill("force", "bihai-chaosheng");
		map_skill("dodge", "suibo-zhuliu");
		map_skill("sword", "yuxiao-jian");
		map_skill("parry", "tanzhi-shentong");
		map_skill("finger", "tanzhi-shentong");
		prepare_skill("finger", "tanzhi-shentong");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "maze" :),
			(: perform_action, "finger.huayu" :),
			(: perform_action, "finger.shentong" :),
		}));
		set("thd/perform",999);
		menpai = "桃花岛";
		break;
		case 11: // mr1
		set_skill("shenyuan-gong", 500);
		set_skill("douzhuan-xingyi", 500);
		set_skill("yanling-shenfa", 500);
		set_skill("murong-jianfa", 500);
		set_skill("tanzhi-shentong", 500);
		map_skill("force", "shenyuan-gong");
		map_skill("dodge", "yanling-shenfa");
		map_skill("sword", "murong-jianfa");
		map_skill("parry", "douzhuan-xingyi");
		map_skill("finger", "canhe-zhi");
		prepare_skill("finger", "canhe-zhi");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "shenyuan" :),
			(: perform_action, "parry.xingyi" :),
      (: perform_action, "parry.lianhuan" :),
		}));
		weapon = "sword";
		menpai = "姑苏慕容";
		break;
		case 12: // gumu1
		set_skill("yunu-xinjing", 500);
		set_skill("yunu-shenfa", 500);
		set_skill("xuantie-jianfa", 500);
		set_skill("anran-zhang", 500);
		map_skill("force", "yunu-xinjing");
		map_skill("dodge", "yunu-shenfa");
		map_skill("sword", "xuantie-jianfa");
		map_skill("parry", "xuantie-jianfa");
		map_skill("strike", "anran-zhang");
		prepare_skill("strike", "anran-zhang");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.wujian" :),
			(: perform_action, "sword.haichao" :),
		}));
		weapon = "sword";
		menpai = "古墓";
		if (random(2)) set("env/玄铁剑法","海潮");
		else set("env/玄铁剑法","汹涌");
		break;
		case 13: // emei1
		set_skill("linji-zhuang", 500);
		set_skill("anying-fuxiang", 500);
		set_skill("huifeng-jian", 500);
		set_skill("jieshou-jiushi", 500);
		map_skill("force", "linji-zhuang");
		map_skill("dodge", "anying-fuxiang");
		map_skill("sword", "huifeng-jian");
		map_skill("parry", "huifeng-jian");
		map_skill("hand", "jieshou-jiushi");
		prepare_skill("hand", "jieshou-jiushi");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "wuwo" :),
			(: perform_action, "sword.mie" :),
			(: perform_action, "sword.jue" :),
			(: perform_action, "sword.liaoyuan" :),
		}));
		weapon = "sword";
		menpai = "峨嵋";
		break;
		case 14: // emei2
		set_skill("linji-zhuang", 500);
		set_skill("anying-fuxiang", 500);
		set_skill("yanxing-daofa", 500);
		set_skill("sixiang-zhang", 500);
		map_skill("force", "linji-zhuang");
		map_skill("dodge", "anying-fuxiang");
		map_skill("blade", "yanxing-daofa");
		map_skill("parry", "yanxing-daofa");
		map_skill("strike", "sixiang-zhang");
		prepare_skill("strike", "sixiang-zhang");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "wuwo" :),
			(: perform_action, "blade.huanying" :),
		}));
		weapon = "blade";
		menpai = "峨嵋";
		break;
		case 15: // mj1
		set_skill("shenghuo-shengong", 500);
		set_skill("qiankun-danuoyi", 500);
		set_skill("piaoyi-shenfa", 500);
		set_skill("shenghuo-lingfa", 500);
		set_skill("hanbing-mianzhang", 500);
		map_skill("force", "shenghuo-shengong");
		map_skill("dodge", "piaoyi-shenfa");
		map_skill("dagger", "shenghuo-lingfa");
		map_skill("parry", "qiankun-danuoyi");
		map_skill("cuff", "shenghuo-lingfa");
		prepare_skill("cuff", "shenghuo-lingfa");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "yinfeng" :),
			(: perform_action, "dagger.ji" :),
			(: perform_action, "dagger.xinmo" :),
			(: perform_action, "dagger.tisha" :),
		}));
		weapon = "tieling";
		menpai = "明教";
		break;
		case 16: // mj2
		set_skill("jiuyang-shengong", 500);
		set_skill("qiankun-danuoyi", 500);
		set_skill("piaoyi-shenfa", 500);
		set_skill("shenghuo-lingfa", 500);
		set_skill("qishang-quan", 500);
		map_skill("force", "jiuyang-shengong");
		map_skill("dodge", "piaoyi-shenfa");
		map_skill("dagger", "shenghuo-lingfa");
		map_skill("parry", "shenghuo-lingfa");
		map_skill("cuff", "qishang-quan");
		prepare_skill("cuff", "qishang-quan");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "jiuyang" :),
			(: perform_action, "dagger.ji" :),
			(: perform_action, "dagger.xinmo" :),
			(: perform_action, "dagger.tisha" :),
		}));
		weapon = "tieling";
		menpai = "明教";
		case 17: // dali1
		set_skill("qiantian-yiyang", 500);
		set_skill("tianlong-xiang", 500);
		set_skill("duanjia-jianfa", 500);
		set_skill("qingyan-zhang", 500);
		map_skill("force", "qiantian-yiyang");
		map_skill("dodge", "tianlong-xiang");
		map_skill("sword", "duanjia-jianfa");
		map_skill("parry", "duanjia-jianfa");
		map_skill("strike", "qingyan-zhang");
		prepare_skill("strike", "qingyan-zhang");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "xinjing" :),
			(: perform_action, "sword.fenglei" :),
		}));
		weapon = "sword";
		menpai = "西南大理";
		break;
		case 18: // tls
		set_skill("kurong-changong", 500);
		set_skill("tianlong-xiang", 500);
		set_skill("cihang-bian", 500);
		map_skill("force", "kurong-changong");
		map_skill("dodge", "tianlong-xiang");
		map_skill("parry", "kurong-changong");
		map_skill("strike", "kurong-changong");
		prepare_skill("strike","kurong-changong");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "ku" :),
			(: exert_function, "jiuchong" :),
		}));
		menpai = "大理天龙寺";
		break;
		case 19: // gumu2
		set_skill("yinsuo-jinling", 500);
		set_skill("yunu-jianfa", 500);
		set_skill("yunu-shenfa", 500);
		set_skill("meinu-quanfa", 500);
		set_skill("yunu-xinjing", 500);
		map_skill("force", "yunu-xinjing");
		map_skill("dodge", "yunu-shenfa");
		map_skill("sword", "yunu-jianfa");
		map_skill("whip", "yinsuo-jinling");
		map_skill("parry", "yinsuo-jinling");
		map_skill("cuff", "meinu-quanfa");
		prepare_skill("cuff", "meinu-quanfa");
		set("yueyin", 1);
		set("gmsanwu", 1);
	  set("chat_chance_combat", 20);
		set("chat_msg_combat", ({
			(: perform_action, "whip.yueyin" :),
			(: perform_action, "whip.sanwu" :),
		}));
		weapon = "whip";
		menpai = "古墓派";
		break;
		case 20: //gumu3
		set_skill("anran-zhang", 500);
		set_skill("yunu-xinjing", 500);
		set_skill("yunu-shenfa", 500);
		map_skill("force", "yunu-xinjing");
		map_skill("dodge", "yunu-shenfa");
		map_skill("parry", "anran-zhang");
		map_skill("strike", "anran-zhang");
		prepare_skill("strike", "anran-zhang");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "strike.xiaohun" :),
  //  		(: perform_action, "strike.anran" :),
			(: perform_action, "strike.jishi" :),
		}));
		menpai = "古墓派";
		break;
		case 21: // kl1
		set_skill("xuantian-wuji", 500);
		set_skill("taxue-wuhen", 500);
		set_skill("kunlun-zhang", 500);
		map_skill("force", "xuantian-wuji");
		map_skill("dodge", "taxue-wuhen");
		map_skill("parry", "kunlun-zhang");
		map_skill("strike", "kunlun-zhang");
		prepare_skill("strike", "kunlun-zhang");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
      (: perform_action, "strike.diezhang" :),
		}));
		menpai = "昆仑派";
		break;
		case 22: // kl2
		set_skill("xuantian-wuji", 500);
		set_skill("taxue-wuhen", 500);
		set_skill("zhentian-quan", 500);
		map_skill("force", "xuantian-wuji");
		map_skill("dodge", "taxue-wuhen");
		map_skill("parry", "zhentian-quan");
		map_skill("cuff", "zhentian-quan");
		prepare_skill("cuff", "zhentian-quan");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "taxue" :),
			(: perform_action, "cuff.kaishan" :),
		}));
		menpai = "昆仑派";
		break;
		case 23: // kl3
		set_skill("xuantian-wuji", 500);
		set_skill("taxue-wuhen", 500);
		set_skill("chuanyun-tui", 500);
		map_skill("force", "xuantian-wuji");
		map_skill("dodge", "taxue-wuhen");
		map_skill("parry", "chuanyun-tui");
		map_skill("leg", "chuanyun-tui");
		prepare_skill("leg", "chuanyun-tui");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: exert_function, "taxue" :),
			(: perform_action, "leg.chuanyun" :),
		}));
		menpai = "昆仑派";
		break;
		case 24: // kl4
		set_skill("xuantian-wuji", 500);
		set_skill("taxue-wuhen", 500);
		set_skill("liangyi-jian", 500);
		map_skill("force", "xuantian-wuji");
		map_skill("dodge", "taxue-wuhen");
		map_skill("parry", "liangyi-jian");
		map_skill("sword", "liangyi-jian");
	  set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.xunlei" :),
			(: perform_action, "sword.podi" :),
		}));
		menpai = "昆仑派";
		weapon = "sword";
		break;
		case 25: // tls3
		set_skill("kurong-changong", 500);
		set_skill("tianlong-xiang", 500);
		set_skill("yiyang-zhi", 500);
		set_skill("jingmai-xue", 500);
		map_skill("force", "kurong-changong");
		map_skill("dodge", "tianlong-xiang");
		map_skill("parry", "kurong-changong");
		map_skill("finger", "yiyang-zhi");
		prepare_skill("finger", "yiyang-zhi");
	  set("chat_chance_combat", 20);
		set("chat_msg_combat", ({
			(: perform_action, "finger.sanmai" :),
			(: perform_action, "finger.sandie" :),
		}));
		menpai = "大理天龙寺";
		break;
		case 26: // tz1
		set_skill("guiyuan-tunafa", 500);
		set_skill("shuishangpiao", 500);
		set_skill("tiezhang-zhangfa", 500);
		map_skill("force", "guiyuan-tuanfa");
		map_skill("dodge", "shuishangpiao");
		map_skill("parry", "tiezhang-zhangfa");
		map_skill("strike", "tiezhang-zhangfa");
		prepare_skill("strike", "tiezhang-zhangfa");
	  set("chat_chance_combat", 20);
	  set("quest/tzauto/over",1);
		set("chat_msg_combat", ({
			(: exert_function, "juli" :),
			(: perform_action, "dodge.piao" :),
			(: perform_action, "strike.heyi" :),
			(: perform_action, "strike.qinna" :),
			(: perform_action, "strike.lianhuan" :),
		}));
		menpai = "铁掌派";
		break;
		case 27: // tz2
		set_skill("guiyuan-tunafa", 500);
		set_skill("shuishangpiao", 500);
		set_skill("tiezhang-zhangfa", 500);
		map_skill("force", "guiyuan-tunafa");
		map_skill("dodge", "shuishangpiao");
		map_skill("parry", "tiezhang-zhangfa");
		map_skill("strike", "tiezhang-zhangfa");
		prepare_skill("strike", "tiezhang-zhangfa");
	  set("chat_chance_combat", 20);
		set("chat_msg_combat", ({
			(: exert_function, "juli" :),
			(: perform_action, "dodge.piao" :),
			(: perform_action, "strike.tianlei" :),
			(: perform_action, "strike.lianhuan" :),
			(: perform_action, "strike.heyi" :),
		}));
		menpai = "铁掌派";
		break;
		case 28: // sld1
		set_skill("dulong-dafa", 500);
		set_skill("youlong-shenfa", 500);
		set_skill("huagu-mianzhang", 500);
		map_skill("force", "dulong-dafa");
		map_skill("dodge", "youlong-shenfa");
		map_skill("parry", "huagu-mianzhang");
		map_skill("strike", "huagu-mianzhang");
		prepare_skill("strike", "huagu-mianzhang");
	  set("chat_chance_combat", 20);
		set("chat_msg_combat", ({
			(: exert_function, "wudi" :),
			(: perform_action, "strike.bujue" :),
		}));
		menpai = "神龙教";
		break;
		case 29: // sld2
		set_skill("dulong-dafa", 500);
		set_skill("youlong-shenfa", 500);
		set_skill("huagu-mianzhang", 500);
		set_skill("tenglong-bifa", 500);
		map_skill("dagger", "tenglong-bifa");
		map_skill("force", "dulong-dafa");
		map_skill("dodge", "youlong-shenfa");
		map_skill("parry", "tenglong-bifa");
		map_skill("strike", "huagu-mianzhang");
		prepare_skill("strike", "huagu-mianzhang");
	  set("chat_chance_combat", 20);
		set("chat_msg_combat", ({
			(: exert_function, "wudi" :),
			(: perform_action, "dagger.xiaolian" :),
			(: perform_action, "dagger.beauty" :),
			(: perform_action, "dagger.diqing" :),
		}));
		menpai = "神龙教";
		weapon = "dagger";
		break;
		
		
		
		case 30: // super
		set_skill("jiuyin-zhengong", 500);
		set_skill("jiuyin-shenfa", 500);
		set_skill("jiuyin-shenzhua", 500);
		set_skill("youlong-bian", 500);
		map_skill("whip", "youlong-bian");
		map_skill("force", "jiuyin-zhengong");
		map_skill("dodge", "jiuyin-shenfa");
		map_skill("parry", "yinlong-bian");
		map_skill("claw", "jiuyin-shenzhua");
		prepare_skill("claw", "jiuyin-shenzhua");
	  set("chat_chance_combat", 30);
		set("chat_msg_combat", ({
			(: exert_function, "zongjue" :),
			(: perform_action, "whip.chanrao" :),
			(: perform_action, "whip.feilong" :),
			(: perform_action, "whip.feilong" :),
		}));
		menpai = "神龙教";
		weapon = "whip";
		break;
		
		
		
		
				case 31: // super
		set_skill("hamagong", 500);
		set_skill("hamabu", 500);
		set_skill("lingshe-quanfa", 500);
		set_skill("lingshe-zhangfa", 500);
		map_skill("cuff", "lingshe-quanfa");
		map_skill("force", "hamagong");
		map_skill("dodge", "hamabu");
		map_skill("parry", "lingshe-quanfa");
		map_skill("staff", "lingshe-zhangfa");
		prepare_skill("cuff", "lingshe-quanfa");
	  set("chat_chance_combat", 30);
	  set("ofy/hamagong",3);
		set("chat_msg_combat", ({
			(: exert_function, "nizhuan" :),
			(: perform_action, "cuff.lingshe" :),
			(: perform_action, "cuff.lingshe" :),
		}));
		menpai = "神龙教";
		break;
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		default: // others      BUG!!!
		set("long","武功设置错误，BUG！！！");
	}
	set("weapon" , weapon);

	setup();
	if( weapon != "null" ) carry_object(BINGQI_D(weapon))->wield();
	carry_object(ARMOR_D("yexing-yi"))->wear();
	call_out("dest", 300);
}

int do_copy(object ob)
{
	mapping skills;
	string *sk;
	object me;
	int lv,exp,i;

	me = this_object();

	lv = ob->query("max_pot") -100;

	exp = ob->query("combat_exp");
	exp = exp / 100 * (100+random(20));

	me->set("max_qi", ob->query("max_qi")*3/2);
	me->set("eff_qi", me->query("max_qi"));
	me->set("qi", me->query("max_qi"));
	me->set("max_jing", ob->query("max_jing"));
	me->set("eff_jing", ob->query("max_jing"));
	me->set("jing", ob->query("max_jing"));
	me->set("max_neili", ob->query("max_neili"));
	me->set("neili", ob->query("neili"));
	if( me->query("neili") < me->query("max_neili"))
	me->set("neili", me->query("max_neili"));
	me->set("eff_jingli", ob->query("eff_jingli"));
	me->set("jingli", ob->query("jingli"));
	if( me->query("jingli") < me->query("eff_jingli"))
	me->set("jingli", me->query("eff_jingli"));
	me->set("combat_exp", exp);

	skills = me->query_skills();
	if (mapp(skills)) {
		sk = keys(skills);
		for (i=0;i<sizeof(sk);i++)
		if ( sk[i] != "literate")
		skills[sk[i]] = lv;
	}
	me->set("jiali", me->query_skill("force")/4);
}

void init()
{
	object cart,me=this_player();

	::init();
	cart = query_temp("target");
	if (cart && me->query_temp("protecting") == cart) {
		kill_ob(me);
		me->fight_ob(this_object());
	}
}

void kill_ob(object ob)
{
	object me = this_object();

	if(!objectp(me->query_temp("target"))
	|| (me->query_temp("target") != ob->query_temp("protecting"))){
		me->remove_enemy(ob);
		ob->remove_killer(me);
		return;
	}
	::kill_ob(ob);
}

void fight_ob(object ob)
{
	if (!objectp(query_temp("target"))
	|| ob->query_temp("protecting") != query_temp("target")) {
		command("say 走远点，老子正忙着呢。");
		ob->remove_killer(this_object());
	}
	else ::fight_ob(ob);
}

void dest()
{
	object ob = this_object();

	if (environment(ob)) message_vision("$N匆匆忙忙地离开了。\n",ob);
	destruct(ob);
}
