#include <ansi.h>

inherit NPC;

void create()
{
        set_name("捡破烂的", ({ "jian polan" }));

        set("long", @LONG
这个人不但自己捡破烂，身上也穿得破烂不堪。
LONG
        );

        set("gender", "男性" );
        set("age", 30);

        set("combat_exp", 1000);
        set_skill("unarmed", 20); 
        set_skill("parry", 20); 
        set_skill("dodge", 20); 
               
        set_temp("apply/attack", 5); 
        set_temp("apply/defense", 5); 
        set_temp("apply/damage", 5); 
      
        set("attitude", "friendly"); 


        set("chat_chance", 10);
        set("chat_msg", ({
                (: command, "get all" :),
                "捡破烂的喃喃道：怎么这些人那么没公德心，随便乱扔东西。\n",
                "捡破烂的嘴里嘟哝著，不知道说些什麽。\n",
                "捡破烂的伸手捉住了身上的虱子，一脚踩得扁扁的。 \n",
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: random_move :)
        }) );

        setup();

        add_money("coin", 50);

}

int accept_object(object me, object obj)
{
        command("smile");
        command("say 多谢这位" + RANK_D->query_respect(me) + "！");
        return 1;
}

int accept_fight(object me)
{
        command("say " + RANK_D->query_respect(me) + "饶命！小的这就离开！\n");
        return 0;
}
