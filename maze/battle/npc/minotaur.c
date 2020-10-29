// niutou.c

#include <ansi.h>
#define BATTLEFIELD2_D     "/adm/daemons/battlefieldd2.c"

inherit NPC;

void create()
{
        set_name("牛头怪", ({ "niutou guai", "niutou" }) );
        set("title", HIY "魔族" NOR);
        set("gender", "男性");
        set("age", 58);
        set("long", @LONG
这是一个满脸杀气的恶汉，两眼直露凶光。
LONG );
        set("combat_exp", 100000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 200000);
        set("neili", 200000);
        set("max_jing", 200000);
        set("jing", 200000);
        set("max_qi", 2500000);
        set("qi", 2500000);
        set("jingli", 2000000);
        set("max_jingli", 2000000);
        set("jiali", 2000);

        set("str", 100);
        set("int", 30);
        set("con", 100);
        set("dex", 100);

        set_skill("unarmed", 1200);
        set_skill("sword", 1200);
        set_skill("parry", 1200);
        set_skill("dodge", 1200);
        set_skill("force", 1200);
        
        set_temp("apply/attack", 1300);
        set_temp("apply/unarmed_damage", 1500);
        set_temp("apply/armor", 2000);

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIR "$N" HIR "口中呵呵作响，两眼中"
                       "凶光毕露。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N一阵狂叫，猛然扑了上来。\n",
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 2000 + random(2000), me);
        set("neili",query("max_neili",  me), me);
        return HIR "$N" HIR "身上腾起一股火焰，登时逼得$n"
               HIR "退后几步，闷哼一声。\n" NOR;
}

varargs void die(object killer)
{
        object me;
        int i;

        me = this_object();

        if( !killer ) killer = me->query_last_damage_from();
        if( objectp(killer) )
        {
                BATTLEFIELD2_D->add_killnpc_score(killer, 1);
        }

        ::die(killer);
}

