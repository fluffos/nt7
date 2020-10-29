// liuhongying.c

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("刘虹瑛", ({ "liu hongying", "liu" }));
        set("title","金牛武馆教习");
        set("long", "刘教头是武馆的新来教习，你可别小看她哦。\n");
        set("gender", "女性");
        set("age", 32);

        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("strike", 80);
        set_skill("sword", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);
        setup();

}

int recognize_apprentice(object ob)
{
        if( !query_temp("marks/jinniu_paied", ob) == 1)return 0;
        return 1;
}