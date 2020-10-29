#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("伙计", ({ "huo ji", "huo", "ji" }) );
        set("title", HIB"药王谷"NOR+YEL"跑堂"NOR);
        set("gender", "男性" );
        set("age", 22);
        set("combat_exp", 100);
        set("attitude", "friendly");

        set("no_clean_up", 1);
        setup();
        add_money("silver", 5);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob = this_player();

//      add_action("do_sell", "寄售");
//      add_action("do_sell", "jishou");
        add_action("do_buy", "buy");
        add_action("do_list", "list");

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int greeting(object ob)
{
        if( query("family/family_name", ob) == HIB"药王谷"NOR){
        command("say 这位兄弟请了，你有药品拿给我寄售吗？(指令格式：寄售 xxx)\n");
                return 1;}
        else {
        switch( random(4) ) {
                case 0:
                        command("bow"+query("id", ob));
                        command("say "+RANK_D->query_respect(ob)
                +"，这里出售药王谷弟子精心炮制的成药，药效不凡！\n");
                        break;
                case 1:
                        command("nod"+query("id", ob));
                        command("say "+RANK_D->query_respect(ob)
                +"，这里出售药王谷弟子精心炮制的成药，药效不凡！\n");
                        break;
                case 2:
                        command("hi"+query("id", ob));
                        command("say "+RANK_D->query_respect(ob)
                +"，这里出售药王谷弟子精心炮制的成药，药效不凡！\n");
                        break;
                case 3:
                        command("welcome"+query("id", ob));
                        command("say "+RANK_D->query_respect(ob)
                +"，这里出售药王谷弟子精心炮制的成药，药效不凡！\n");
                        break;
                }
        }
}
/*
int do_sell(string arg)
{
        object ob;
        int i;
        int count;
        int value;
        object *inv;
        
        if (!arg || !(ob = present(arg, this_player())))
                return notify_fail("你要寄售什么东西？\n");

        if( !query("yaowang", ob) )
                return notify_fail("这个东西不能在这里寄售！\n");

        value=query("value", ob);
        if (value < 30)
                write(query("name", ob)+"一文不值！\n");
        else {
                message_vision("$N拿出一"+query("unit", ob)+
                query("name", ob)+"给$n寄售。\n",this_player(),this_object());
                MONEY_D->pay_player(this_player(), value * 90 / 100);
                if ( userp(ob))
                {
                        ob->move("/d/city/cangku");
                        set("startroom", "/d/city/cangku", ob);
                        ob->set_temp("selled");
                        ob->save();
                }
                else if (value < 50)
                        destruct(ob);
                else
                {
                        inv = all_inventory(this_object());
                        count=0;
                        for (i = 0; i < sizeof(inv); i++)
                        {
                                if (inv[i]->short()==ob->short())
                                        count++;
                        }
                        if (count<500)
                                ob->move(this_object());
                        else
                                destruct(ob);
                }
        }
        return 1;
}
*/
int do_list()
{
        string *goods;
        object *inv;
        object *inv1;
        int *count;
        int i;
        int j;

        inv = all_inventory(this_object());

        if (!sizeof(inv) && !arrayp(goods = query("vendor_goods")))
                return notify_fail("目前这里没有东西寄售。\n");
        for (i = 0; i < sizeof(inv); i++) 
        {
                if( !query("equipped", inv[i]) && !query("money_id", inv[i]) )
                {
                        if (!arrayp(inv1))
                        {
                                inv1=({inv[i]});
                                count=({1});
                        }
                        else
                        {
                                for (j = 0; j < sizeof(inv1); j++)
                                        if (inv[i]->short()==inv1[j]->short())
                                                break;
                                if (j == sizeof(inv1))
                                {
                                        inv1+=({inv[i]});
                                        count+=({1});
                                }
                                else
                                        count[j]+=1;
                        }
                }
        }
        
        printf("%s现在寄售出列物品：\n", query("name"));

        for (i = 0; i < sizeof(inv1); i++) 
                printf("%30-s：数量：%3-i %s\n", inv1[i]->short(),
                count[i],
                MONEY_D->price_str(query("value", inv1[i])));
        if (arrayp(goods = query("vendor_goods")))
                for (i = 0; i < sizeof(goods); i++)
                        printf("%30-s：%s\n", goods[i]->short(),
                        MONEY_D->price_str(query("value", get_object(goods[i])))); 
        return 1;
}       

int do_buy(string arg)
{
        string ob_file;
        object ob;

        if (!arg)
                return notify_fail("你想买什么？ \n");

        if (!(ob = present(arg, this_object())))
                        return notify_fail("你想买什么？ \n");

        if (!ob) {
                ob = new(ob_file);
        }
        else {
                if( query("equipped", ob) )
                        return notify_fail("你想买什么？ \n");
        }

        if (query_temp("busy"))
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        
        switch(MONEY_D->player_pay(this_player(),query("value", ob))){
        case 0:
                return notify_fail("穷光蛋，一边呆着去！\n");
        case 2:
                return notify_fail("您的零钱不够了，银票又没人找得开。\n");
        default:
                set_temp("busy", 1);
                message_vision("$N从$n那里买下了一"+query("unit", ob)+
                query("name", ob)+"。\n",this_player(),this_object());
                ob->move(this_player());

        }
        remove_call_out("enough_rest");
        call_out("enough_rest", 1);

        return 1;
}

void enough_rest()
{
        delete_temp("busy");
}
