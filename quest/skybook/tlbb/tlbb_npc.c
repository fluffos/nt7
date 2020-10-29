// tangfeng@SJ 2004
// /d/shaolin/npc/tlbb_npc.c
//inherit NPC;

inherit FIGHTER;
#include <ansi.h>

#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"

//string *str_menpai = ({ "wd","hs","ss","gm","tz","dls","sld","xx","mj","thd","kl"});	
//#include "/d/city/npc/skills_pfm.h";

void create()
{
	set_name("弟子", ({ "di zi", "dizi"}));
	set("long", "一位某门派弟子。\n");
	set("gender", "男性");
	set("age", 33);
	set("attitude", "peaceful");
	set("shen", -100);
  set("str", 20);
	set("int", 20);
  set("con", 20);
	set("dex", 20);
  set("double_attack",1);
	set("max_qi", 30000);
	set("max_jing", 6000);
	set("eff_jingli",6000);
	set("neili", 40000);
	set("max_neili", 30000);
	set("jiali", 200);
	set("combat_exp", 5000000+random(8000000));
	set_skill("force", 70);
	set_skill("dodge", 80);
	set_skill("unarmed", 70);
	set_skill("parry", 80);
	set_skill("sword", 80);
	set_skill("cuff", 80);
	setup();
	carry_object(ARMOR_D("shoes"))->wear();
	carry_object(ARMOR_D("changshan"))->wear();
}
void init()
{
    object me,ob;  
    string good_skills;
    int i;     
    ::init();
    ob = this_object();
    if(ob->query("setok")) return;
	  if(!ob->query("party"))	ob->set("party",str_menpai[random(sizeof(str_menpai))]);  	 
    ob->copy_menpai(({ob->query("party")}),1,random(2),100);  //复制npc的门派武功                                              
	  ob->copy_state();				//根据门派更新npc 的一些状态
		if (ob->query("f_skill2")) 
				good_skills=to_chinese(ob->query("f_skill"))+"和"+to_chinese(ob->query("f_skill2"));
		else	
				good_skills=to_chinese(ob->query("f_skill"));
   	ob->set("long",HIW+ob->query("family/family_name")+"高手，成名绝技："+good_skills+"。"NOR);
    if(!ob->query("fight_id"))
    {
		  ob->set_skills_level(350+random(200));
    	return;
    }
    me = present(ob->query("fight_id"),environment(ob));
	  if(!me) 
	  {
		  ob->set_skills_level(350+random(200));
    	return;
    }
    ob->set("setok",1);    
	  i=me->query("max_pot");
	  if(i<350) i=350;
	  i=i-100;	
	  
    //无名僧
	  if(ob->query("party")=="sl")
	  {
	  	set_name("无名老僧", ({"wuming laoseng","wuming","laoseng",}));
      set("long",
                "他是一位身穿青袍的枯瘦僧人，身材不高。\n"
                "年纪已在七旬开外，稀稀疏疏的几根长须已然全白。\n"
      );
      set("nickname", "无名神僧");
      set("gender", "男性");
      set("attitude", "friendly");
      set("class", "bonze");
      set("no_bark",1);
      set("age", 70);
      set("shen", 32000);
      set("str", 25);
      set("int", 30);
      set("con", 30);
      set("dex", 30);
    }
	  else if(ob->query("party")=="gb")
	  {
	    set_name("萧峰", ({"xiao feng", "xiao", "feng"}));
	    set("gender", "男性");
	    set("nickname",HIB"奇侠"NOR);
	    set("title",HIY"前丐帮帮主"NOR);
	    set("age", 58);
	    set("long", 
	    	"他就是丐帮前任帮主萧峰。\n"
	    	"他身高六尺有余，体格十分魁梧，长有一张线条粗旷、十\n"
		    "分男性化的脸庞，双目如电，炯炯有神。\n");
    	set("attitude", "peaceful");
	    set("str", 30);
    	set("int", 30);
	    set("con", 30);
	    set("dex", 30);
    }
    ob->set_skills_level(i-random(50)+random(50));
	  ob->set("max_neili",me->query("max_neili"));
  	ob->set("max_jingli",me->query("max_jingli"));
    ob->set("max_qi",me->query("max_qi"));
  	ob->set("max_jing",me->query("max_jing"));
		ob->set("neili",query("max_neili")*3/2);
		ob->set("jingli",query("max_jingli")*3/2);
		ob->set("eff_jingli",query("max_jingli")*3/2);
		ob->set("qi",query("max_qi"));
		ob->set("eff_qi",query("max_qi"));
		ob->set("jing",query("max_jing")*3/2);
		ob->set("eff_jing",query("max_jing")*3/2);
    ob->set("jiali",150+random(50));
    ob->set("combat_exp",me->query("combat_exp")*5/4);
 		ob->set_skill("literate",ob->query("int")*10); 	 											//full literate

       set_temp("double_attack",1);//嘿嘿
       set("double_attack",1);//嘿嘿
 		if(ob->query("party")=="gb") message_vision(HIC"$N对$n哈哈笑道：“$n上次趁我伤势未好偷袭，这次就再决一胜负。”\n" NOR, ob,me);
 		if(ob->query("party")=="sl") message_vision(HIC"$N对$n合手施礼道：“$n放下屠刀，立地成佛。我弥陀佛。”\n" NOR, ob,me);
    ob->set_skill("wuxing-zhen",200);
    ob->remove_all_killer();
}

void die()
{
	object ob=this_object();
  if(random(2))command("why");
  else command("disapp "+ob->query("id"));
  if(random(2)) message_vision(HIG"$N点了点头，缓缓消失在角落里。\n\n" NOR, ob);
  else message_vision(HIG"$N慢慢地退了出去。\n\n" NOR, ob);
	destruct(ob);
}
void unconcious()
{
  die();
}
