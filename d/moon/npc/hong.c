#include <ansi.h>
inherit NPC;
int askward();
string *level = ({
  YEL "已有小成" NOR,YEL "融会贯通" NOR,HIY "心领神会" NOR,
	HIY "了然於胸" NOR,HIG "已有大成" NOR,HIG "非同凡响" NOR,HIC "举世无双" NOR,
	HIC "震古铄今" NOR,HIW "无与伦比" NOR,HIW "超凡入圣" NOR
});
void create()
{
    set_name("傅红雪", ({ "hongxue", "fu hongxue", "fu hong xue"}) );
    set("gender", "男性");
    set("age", 24);
    set("long","傅红雪的手里握着刀，一柄形状很奇特的刀，刀鞘漆黑，刀柄漆黑。
无论他在作什么的时候都没有放过这柄刀。\n"); 
	set("attitude", "friendly");
    set("combat_exp", 200000000);

	set("str", 600);
	set("cor", 130);
	set("agi", 600);
	set("int", 30);
	set("cps", 30);
	set("max_force" , 1500000);
	set("force" , 1500000);
	set("force_factor" , 3000);
	set("score" , 200000);
	set("class","bandit");
    set("chat_chance", 3);
    set("chat_msg", ({
            "傅红雪正在吃饭，吃一口饭，配一口菜，吃得很慢。\n",
    "傅红雪漆黑的刀，漆黑的衣服，漆黑的眸子，黑得发亮！\n"
    }) );
     set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
               
                (: perform_action, "blade.kuaidao" :),
        }) );
            set("inquiry",      ([
  
"快刀" : (: askward :),
"kuaidao" : (: askward :),
        ]) );
    set_skill("blade", 3000);
    set_skill("dodge", 2000);
    set_skill("parry", 2000);
	set_skill("move",  2000);
	set_skill("force", 10000);
    set_skill("tianya-blade",3000);
    set_skill("moon-steps",3000);
    set_skill("yueying",3000);

    map_skill("blade","moon-blade");
    map_skill("parry","moon-blade");
    map_skill("dodge","moon-steps");
    map_skill("move","moon-steps");
    map_skill("force","yueying");
    setup();
   carry_object(__DIR__"obj/blade")->wield();
	 carry_object("/obj/money/tenthousand-cash");
}
int askward()
{
    object me,item;
        int lvl;
    me=this_player();
   lvl = me->query("for_modao_num")/10000;
   if (lvl>10) lvl =10;
                 if (me->query("for_practice_modao")<lvl) {
                                 
                            me->set("for_practice_modao", lvl);
                            
                         tell_object(me,WHT"傅红雪对你说道：不错，你的刀法又精进不少。\n"NOR);
                         CHANNEL_D->do_sys_channel(
					"info",sprintf(HIY"%s(%s)通过傅红雪的教导快刀已经达到了"+level[lvl-1]+HIY"的境界。", 
					me->query("name"),me->query("id")));
                            return 1;

                                } else 
                      tell_object(me,HIW"\n傅红雪冷冷的道：你的刀法怎么丝毫没有长进。\n\n"NOR);

    return 1;
}
void die()
{
        object me, owner;
        if(objectp(me=query_temp("last_damage_from") ))     
        if(owner=me->query("possessed")) {
                me = owner;
        } 
        me->set_temp("wanma/傅红雪_ma",1);
        ::die();
}  