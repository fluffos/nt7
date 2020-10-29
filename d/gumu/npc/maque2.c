// maque.c 麻雀
// /d/gumu/npc/maque.c
// Date: 08/05/2001
// update april 01.08.26

inherit NPC;

void create()
{
        set_name("麻雀", ({ "ma que", "que", "bird", "maque" }) );
        set("race", "飞禽");
        set("age", 1+random(3));
        set("long", "一只叽叽喳喳，飞来飞去的小麻雀。\n");
        set("attitude", "peaceful");
        
        set("combat_exp", 100);

        set("chat_chance", 10);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
                "小麻雀叽叽喳喳的叫着，在你头顶上东飞西扑，灵便异常。\n",
                                "小麻雀贪婪地看着玉蜂，随时准备扑上去一饱口福。 \n",
        }) );
        
        set("chat_msg_combat", ({
                (: this_object(), "random_move" :),
                "小麻雀叽叽叽地怒叫着，全身的羽毛都抖竖起来！\n",
        }) );
                
        setup();
}