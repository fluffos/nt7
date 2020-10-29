inherit NPC;
#include <ansi.h>
int big_blowing();
int hurting();
void create()
{
        set_name(HIR"烈火孽龙"NOR, ({ "dragon lord", "dragon" }) );
        set("vendetta_mark","dragon");
        set("race", "野兽");
        set("gender", "雄性");
        set("age", 200);

        set("long",
"这是一条全身赤红，吸天地之间的火气而长大的孽龙！
它全身散发着赤红色的火焰\n");

        set("str", 100+random(20));
        set("con", 52);
        set("dex", 20);
        set("resistance/gin",40);
        set("resistance/sen",40);
        set("resistance/qi",40);
        set("no_curse",1);
        set("max_qi", 8000);
        set("max_jing", 4000);
        set("neili", 100000);
        set("max_neili", 100000);
        set("attitude", "aggressive");
        set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("chat_chance_combat",80);
        set("chat_msg_combat", ({
                (: big_blowing :)
        }) );
        set("combat_exp", 600000);
        set("bellicosity", 3000 );

        set_temp("apply/attack", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 150);
        setup();
}

int big_blowing()
{
        remove_call_out("hurting");
        message_vision( HIR "\n\n$N"HIR"深深地吸入一口火气，全身转为鲜红的火色，整个龙腹胀大了几倍！！\n\n"NOR,
        this_object());
        hurting();
        start_busy(3+random(2));
}
int hurting()
{
        int i;
        int dam;
        object *inv;

        message_vision( HIR "\n\n$N"+HIR"吐出一股炽可焚金的火焰．．整个天地似乎都被燃烧着！！！\n\n",this_object());
        inv = all_inventory(environment(this_object()));
        for(i=sizeof(inv)-1; i>=0; i--)
        if( living(inv[i]))
        if( inv[i] != this_object())
        {
                dam=(random(100)+100)*(100-query_temp("apply/reduce_wood", inv[i]))/100;
                if(dam <0) dam = 0;
                inv[i]->receive_wound("qi",dam);
                COMBAT_D->report_status(inv[i],1);
        }
        return 1;
}