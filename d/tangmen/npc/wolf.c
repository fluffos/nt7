// wolf.c

inherit NPC;

void create()
{
        set_name("野狼", ({ "wolf","lang" }) );
        set("race", "野兽");
        set("age", 3);
        set("long", "一只瘦骨如柴的灰色饿狼。\n");
        set("attitude", "heroism");

        set("str",35);
        set("dex", 35);
        set("max_qi",600);
        set("qi",600);
        set("max_jingli",900);
        set("jingli",900);
        
        set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("chat_chance", 6);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
                "野狼张着血盆大嘴象你冲来。\n",
                "野狼对着你龇了龇牙。\n",
        }) );                

        set("combat_exp", 50000);

        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 50);
        set_temp("apply/armor", 10);

        setup();
}

void init()
{
        object ob;
        ::init();

        if (living(this_object()) && interactive(ob = this_player()) && random(ob->query_kar() + ob->query_per()) < 30)
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 2, ob); 
        }
}