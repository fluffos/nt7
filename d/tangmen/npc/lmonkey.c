// lmonkey.c

inherit NPC;

void create()
{
        set_name("小猴子",({"monkey", "hou", "houzi"}) );
        set("race", "野兽");
        set("gender", "雄性" );
        set("age", 7);
        set("long", "这是一只调皮的小猴子。\n");
        set("combat_exp", 100);
        set("str", 15);
        set("dex", 15);
        set("con", 15);
        set("int", 15);
        set("attitude", "peaceful");

        set("max_qi",100);
        set("qi",100);
        set("max_jingli",100);
        set("jingli",100);
        
        set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
        set("verbs", ({ "knock", "hoof" }) );

        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);

        setup();
}