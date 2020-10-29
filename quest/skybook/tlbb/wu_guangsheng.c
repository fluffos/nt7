// NPC :wu_guangsheng.c 吴光胜
// By River 98/12
inherit NPC;
#include <ansi.h>

#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
void create()
{
        set_name("吴光胜", ({ "wu guangsheng", "wu", "guangsheng"}));
        set("title","无量剑东宗弟子");              
        set("gender", "男性" );
        set("age", 36);
        set("str", 27);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 15);
   	    set("attitude", "friendly");

        set("max_qi", 1000);
        set("max_jing", 800);
        set("eff_jingli", 800);
        set("neili", 1000);
	      set("qi", 1000);	
        set("max_neili", 1000);      
        set("unique", 1);
        
        set("long","他是无量剑东宗的弟子。\n");
        set("combat_exp", 200000);
        set("shen", 800); 

        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("cuff", 80);
        set_skill("sword", 80);
        set_skill("qiantian-yiyang", 80);   
        set_skill("xiaoyaoyou", 80);
        set_skill("wuliang-jianfa", 80);
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "wuliang-jianfa");
        map_skill("sword", "wuliang-jianfa");
        map_skill("force", "qiantian-yiyang");         

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/dali/wuliang/npc/obj/changpao")->wear();
}
void die()
{
	object me,ob=this_object();
       me=ob->query_temp("last_damage_from");

 if(objectp(me)&& !present("yu guangbiao", environment(me))&& me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query_temp(QUESTDIR1+"jianying") || me->query_temp("marks/xiaoyao/gotowyz")  )
 {
    tell_object(me,HIY"\n这"+ob->name()+"眼见就要丧命，突然开口向你求饶，告诉你关于后山剑影的秘密。\n"NOR);
	  tell_room(environment(me),HIC"\n只见，郁光标似乎重伤在身，向"+me->query("name")+"似乎讨教着什么。\n"NOR, ({ me }));
	  me->set_temp(QUESTDIR1+"jianying",1);
    tell_object(me,HIY"\n按"+ob->name()+"所说，这后山一个峭崖边，一块常见到壁上常出现舞剑的人影，有时是男子，有时是女子，\n"
                       "有时更是男女对使，互相击刺。玉壁上所显现的剑法之精，据说极其高明，相传是仙人使剑。\n"NOR);

    tell_object(me,HIC"\n你听完"+ob->name()+"之后，还是手下不留情面，双手一紧，一股内力蓬勃而发。\n"NOR);
	  tell_room(environment(me),HIC"\n吴光胜说完很多之后，然而不知为何，似乎气血一震，好像失去了什么似的，慢慢萎靡倒地。\n"NOR, ({ me }));
    message_vision(HIG"$n仰天长叹，为什么啊，为什么，$N竟然如此狠心。\n"NOR, me, this_object());
    if(me->query_temp("marks/xiaoyao/gotowyz")) {
    	me->delete_temp("marks/xiaoyao/gotowyz");
       me->delete_temp(QUESTDIR1+"jianying",1);
       me->set("marks/xiaoyao","gotofind");	
    	}
    
  }
	::die();
}
