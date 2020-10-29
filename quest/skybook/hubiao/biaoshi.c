inherit NPC;

void create()
{
        set_name("镖师", ({ "biao shi", "bian"}) );
        set("gender", "男性" );
        set("age", 32);
        set("long", "这是一位高达六尺的镖师。\n");
        set("combat_exp", 200000);
        set("attitude", "friendly");
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("strike",100);
        set_skill("blade",100);
        set_skill("murong-daofa",100);
        set_skill("xingyi-zhang",100);

        map_skill("strike", "xingyi-zhang");
        map_skill("parry","xingyi-zhang");
        map_skill("blade","murong-daofa");

        prepare_skill("blade","murong-daofa");
        prepare_skill("strike", "xingyi-zhang");

        set("max_qi",1000);
        set("max_jing",1000);
        set("neili",1000);
        set("max_neili",1000);
        set("jingli",1000);
        set("eff_jingli",1000);
        set("jiali",20);
        set_temp("apply/damage", 60);
        set_temp("apply/armor", 100);
        set_temp("no_return",1);
        setup();
        add_money("silver", 50);
        carry_object("/clone/armor/bcloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
        carry_object(ARMOR_D("shoes"))->wear();
}

void heart_beat()
{
	object me = this_object();
	object where;

	::heart_beat();
	
	if ( ! me) return;
	if ( !environment(me)) return;
	if ( me->query_temp("protecting")) {
		where = environment(me->query_temp("protecting"));
		if ( where && environment(me) != where)
			me->move(where);
	}
}
