//ytx.c

inherit NPC;
#include <ansi.h>
int ask_jiuyuan();
#define QUESTDIR "skybook/shediao/"

void greeting(object me);

void create()
{
	set_name("郭啸天", ({ "guo xiaotian", "guo", "xiaotian" }) );
	set("gender", "男性" );
	set("title", HIC"大侠"NOR);
	set("nickname", HIC"北俠郭靖之父"NOR);
	set("age", 28);
	set("long",
                "他身材魁梧，浓眉大眼。\n"
                "他是梁山泊好汉地佑星赛仁贵郭盛的后代。\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
        set("no_get", 1);
	set_skill("force", 200);
	set_skill("dodge", 200);
	set_skill("parry", 200);
	set_skill("cuff",200); 
	set_skill("jinyan-gong",200);
	set_skill("changquan",200);
	set_skill("xiantian-gong",200);
	map_skill("force","xiantian-gong");
	map_skill("cuff","changquan");
	map_skill("dodge","jinyan-gong");
        prepare_skill("cuff", "changquan");
    
	set("combat_exp", 1000000);
	set("max_qi", 30000);
	set("max_jing", 30000);
	set("max_neili", 50000);
	set("eff_jingli",30000);
	set("qi",30000);
	set("jing",30000);
	set("jingli",30000);
	set("neili", 50000);

        set("inquiry", ([
                "救援": (: ask_jiuyuan :),
		"杨铁心": "他是我义弟。",
                "李萍" : "她是我浑家。",
                "郭靖" : "这是一个道人给我未出世的儿女取的名字。",
                "杨康" : "这是我义弟杨铁心的骨肉。",
                "包惜弱" : "她是我弟媳。",

	]));
	set("chat_chance", 10);
        set("chat_msg", ({
		"村里不怎么的出现大批金兵，这到底是发生了什么事情、、、\n",
		"内子和弟媳快要生了，这节骨眼上怎么会发生这种事情呢、、、\n",
        }) );
        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        carry_object("/clone/cloth/shoes.c")->wear();
} 

int ask_jiuyuan()
{
	object me = this_player();

	if( query(QUESTDIR+"start",me) )
        {
                command("beg1 "+query("id",me));
		command("say 这位"+RANK_D->query_respect(this_player())+"，快去救我义弟啊，要不他顶不住了？");
	        return 1;
        } 
	if( query(QUESTDIR+"over",me) )
        {
	        command("beg1 "+me->query("id"));
		command("say 多谢这位"+RANK_D->query_respect(this_player())+"出手救我义弟呀？");		
	        return 1;
        } 
        if(  query("combat_exp",me) < 2000000 )
        {
	        command("hmm "+ query("id",me));
		command("say 以你当前的经验恐怕还不能帮忙救援我义弟，还是抓紧去练功去吧。\n");
       	        return 1;
        }  	
        if( query(QUESTDIR+"time",me) && time()- query(QUESTDIR+"time",me)<86400)
	{
	        command("shake "+ query("id",me));
	        command("say 今天先帮到这里吧，明天吧。");
	        return 1;
        }
        if( query(QUESTDIR+"combat_exp",me) && query("combat_exp",me)-query(QUESTDIR+"combat_exp",me)<100000)
	{
	        command("look "+query("id",me));
	        command("say 以你当前的经验恐怕还是无法帮忙，还是抓紧去练功去吧。");
	        return 1;
        }
        if( !query(QUESTDIR+"over",me) )
        {
	        set(QUESTDIR+"风雪惊变/start", 1, me);
	        set(QUESTDIR+"time",time(),me);
                set(QUESTDIR+"combat_exp",query("combat_exp",me),me);
	        command("cry "+query("id",me));
	        command("say 昨日我和义弟救援一位被金兵追杀的道士，没想到今日却来有金兵来抓我们，\n"+
		       "这位大侠请赶快去我义弟家解救我义弟杨铁心吧，我准备下武器随后就到。");
	        return 1;
        }
}

