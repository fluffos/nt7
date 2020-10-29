#include <ansi.h>

inherit NPC;

void smart_fight();

void create()
{
        string *names = ({RED"僵尸"NOR});
        set_name( names[random(sizeof(names))], ({ "zombie"}));
        set("vendetta_mark","skeleton");
        set("long", "这是一只"+query("name")+"。\n");
        set("zone","blood");
        set("attitude", "aggressive");
        set("chat_chance_combat", 0);
        set("chat_msg_combat", ({
                (: smart_fight() :),
        }) );

        set("death_msg",BLU"\n$N散成了一堆肉渣。\n\n"NOR);

        setup();
}

int is_undead() { return 1; }
void unconcious()
{
    die();
}

void init()
{
        object *obs;
	int just,n;
	object env = environment();

	if( !is_fighting() )
	{
		n=query("user_num",env);
		just=query("tuan_num",env);
		if( !n ) n=1;
	        set("max_qi",100+query("base_qi")*n*(1+3*just));
	        set("max_jing",100+query("base_jing")*n*(1+3*just));
                full_self();
        }

        ::init();
}

void heart_beat()
{
	object *enemy,me;
	me=this_object();
	enemy=query_enemy();
        for( int i=0; i<sizeof(enemy); i++ )
	        if( environment() == environment(enemy[i]) )
		        if( query("combat_exp",me)<query("combat_exp",enemy[i]) )
			        set("combat_exp",query("combat_exp",enemy[i]),me);

	::heart_beat();
}
