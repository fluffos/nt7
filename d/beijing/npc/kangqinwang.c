#include <ansi.h>

inherit NPC;

void create()
{
        set_name("康亲王", ({ "kang qinwang", "kang"}));
        set("title", HIY "当朝亲王" NOR);
        set("gender", "男性" );
        set("age", 42);
        set("long", "\n只见他一身锦衣，笑容满面，任谁见了他都生不起气来。\n"+
                      "此人深谙为官之道，极善察言观色、溜须拍马，颇得皇帝\n欢心。\n");
        set("shen_type", 1);
        set("combat_exp", 50000);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "peaceful");
        set_skill("dodge", 50);
        set_skill("unarmed", 50);

        setup();
        carry_object("/d/beijing/npc/obj/goldcloth2")->wear();
}

void init()
{
        object ob = this_player();

        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
}

void greeting(object ob)
{
        object man;

        if (! ob || environment(ob) != environment())
                return;

        if( query("meili", ob)<20 )
        {
                if (userp(ob))
                        message_vision("\n康亲王一见$N, 顿时勃然大怒，叫道：“来人啊！将这厮给我拿下！”\n", ob);

                if(! present("shi", environment(ob)))
                {
                        message_vision("登时门外冲进几个侍卫，挥刀向$N直扑过来。\n",ob);
                        man = new("/d/beijing/npc/shiwei2.c");
                        man->move(environment(ob));
                        man = new("/d/beijing/npc/shiwei2.c");
                        man->move(environment(ob));
                        man = new("/d/beijing/npc/shiwei2.c");
                        man->move(environment(ob));
                }
                return ;
        }

        switch (random(5))
        {
                case 0:
                        message_vision("\n$N刚一进门, 康亲王便抢着迎了出来，笑道：“这位" +
                                       RANK_D->query_respect(ob) + "，请进请进。\n", ob);
                        if( query("meili", ob)<100 )
                        {
                                addn("meili", 10, ob);
                                message_vision(HIC "$N的魅力值提高了！\n" NOR, ob);
                                command("tell"+query("id", ob)+"你现在的魅力值是"+
                                        chinese_number(query("meili", ob))+"点");
                        }
                        break;
                default:
                        say("康亲王笑道：不知这位" + RANK_D->query_respect(ob) +
                            "，光临寒舍有何贵干？\n");
                        break;
        }
}

