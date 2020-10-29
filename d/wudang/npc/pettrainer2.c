// #pragma save_binary


// Tie@fy
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("高人", ({ "gaoren" }) );
        set("gender", "男性" );
        set("title","半仙兽");
        set("age", 32);
        set("long","一个得半道的老道士，对改善动物的体质别有妙技。\n");
        set("combat_exp", 5000);
        set("attitude", "friendly");
        set("chat_chance", 15);
        set("title",HIW"三界散人"NOR);
        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_train", "xunlian");

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "高人说道：这位" + RANK_D->query_respect(ob)
                                + "，来陪我聊一聊？\n");
                        break;
                case 1:
                        say( "高人笑道：这不，生意来了！\n");
                        break;
        }
}

int do_train(string arg)
{
        object me,pet,gold;
        int cost;
        string which;
        me = this_player();
        if(me->is_busy())
        return notify_fail("你上一个动作还没有完成。\n");
        if(!arg) return notify_fail("高人道：＂你要什么呀？＂\n");
        pet = present(arg,environment());
        if(!objectp(pet)) return notify_fail("高人道：＂你要什么呀？＂\n");
        if( query("possessed", pet) != me )
        return notify_fail("高人道：＂那好象不是你的吧？＂\n");
        switch (random(2)){
        case 0: which = "max_jing"; break;
        case 1: which = "max_qi"; break;
                        }
//okey we identified the target, now the cost:
        cost=query(which, pet)/10;
        cost *= cost;
        if (cost > 200) cost = 200;
        gold = present("gold_money", me);
        if(!gold) return notify_fail("你身上没有金子。\n");
        if((int) gold->query_amount() < cost)
        return notify_fail("你身上没有"+chinese_number(cost)+"两金子。\n");
        if( query("score", me)<cost )
        return notify_fail("你的评价不够"+chinese_number(cost)+"点。\n");
        addn(which, 20, pet);
        pet->save();
        gold->add_amount(-cost);
        addn("score", -cost, me);
        command("say 这就得了！\n");
        return 1;
}
