//bao.c

inherit NPC;
#include <ansi.h>

void create()
{
	set_name("包惜弱", ({ "bao xiruo", "bao", "xiruo" }) );
	set("gender", "女性" );
	set("age", 25);
	set("long",
                "她身材极好，虽然脸有点黑，但是还是看出无限的妩媚动人。\n");
	set("str", 10);
	set("dex", 10);
	set("con", 5);
	set("int", 5);
	set("per", 30);
	set("shen_type", 1);
	set_skill("unarmed", 5);
    
	set("combat_exp", 15000);
	set("max_qi", 100);
	set("max_jing", 100);
	set("max_neili", 0);
	set("eff_jingli",200);
	set("qi",100);
	set("jing",100);
	set("jingli",200);
	set("neili", 0);

        set("inquiry", ([
                "郭啸天" : "他是我夫君义兄。",
                "杨康" : "这是一个道人给我未出世的儿女取的名字。",
                "郭靖" : "这是我夫君义兄郭啸天的骨肉。",
                "李萍" : "她是我嫂子",
	]));

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        carry_object("/clone/cloth/shoes.c")->wear();
} 



