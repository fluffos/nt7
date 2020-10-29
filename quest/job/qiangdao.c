// qiangdao.c 强盗
inherit NPC;
#include <ansi.h>
void move();

void create()
{
        set_name(HIW "强盗" NOR, ({ "qiang dao", "dao",}));
        set("gender", "男性");
        set("age", 28);
        set("long", "他是一个专靠打劫营生的强盗。\n");
        
        set("combat_exp",1000);
        set("attitude", "peaceful");
        
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        
         set("str",30);
         set("per",18);
         set("food",400);
         set("water",400);

        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        add_money("silver",10);
}

void init()
{
        remove_call_out("leave");
        call_out("leave",300);
}

void leave()
{
        object ob = this_object();
        if (!ob->is_fighting()) {
                message_vision(HIC "强盗钻进路边的杂草，不见了。\n" NOR,this_object());
                }
        else call_out("leave",10);
}

void die()
{
        object me = this_object()->query_temp("last_damage_from");
        object corpse, money;      
        int kar, exp, pot;
        kar = random(30);
        exp = kar + random(200);
        pot = 200 + random(50);

        message_vision(HIR "\n强盗倒在地上，挣扎了几下就死了。\n" NOR,me);
        if (me->query("kill_qiangdao") == 1 && this_object()->query_temp("owner/id") == me->query("id")) {
                message_vision(HIW "$N被奖励了：\n"
                + chinese_number(exp) + "点实战经验，\n"
                + chinese_number(pot) + "点潜能，\n"
                + chinese_number(10) + "点威望。\n" NOR, me);
                me->add("combat_exp", exp);
                me->add("potential", pot);
                me->add("weiwang", 10);
                me->delete("quest3");
                me->delete("kill_qiangdao");
                }
        else {
                message_vision(HIC "\n由于$N"HIC"杀错了目标，防碍了别人做任务。现在倒扣经验：\n"
                + chinese_number(200) + "点实战经验，\n"
                + chinese_number(100) + "点潜能，\n"
                + chinese_number(1000) + "点威望作为答谢。\n" NOR, me);
                me->add("combat_exp", -200);
                me->add("potential", -100);
                me->add("weiwang",-1000);
                }

        corpse = new("/clone/misc/corpse");
        corpse->set("name",HIW "强盗的尸体" NOR);
        corpse->set("long","他是一个曾经无恶不做的强盗，\n然而，他已经死了，剩下一具丑陋的尸体。\n");
        corpse->move(environment(this_object()));
        corpse->set_max_encumbrance(1000);        
        money = new("/clone/money/gold");
        money->move(corpse);
        me->add("MKS", 1);

        destruct(this_object());
}

