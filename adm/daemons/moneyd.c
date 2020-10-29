// moneyd.c  钱的功能
// by Xiang@XKX (95/12/22)
// Rewritten by Lonely@chinamud.cn

// #pragma optimize
// #pragma save_binary

string money_str(int amount)
{
        // returns a chinese string of `amount` of money
        string output;

        if( amount / 10000 ) {
                output = chinese_number(amount / 10000) + "两黄金";
                amount %= 10000;
        }
        else
                output = "";
        if( amount / 100 ) {
                output = output + chinese_number(amount / 100) + "两白银";
                amount %= 100;
        }
        if( amount )
                return output + chinese_number(amount) + "文铜钱";
        return output;
}

string price_str(int amount)
{
        // returns a chinese string of `amount` of money
        string output;

        if( amount < 1 )
                amount = 1;

        if( amount / 10000 ) {
                output = chinese_number(amount / 10000) + "两黄金";
                amount %= 10000;
        }
        else
                output = "";
        if( amount / 100 ) {
                if( output != "" )
                        output += "又" + chinese_number(amount / 100) + "两白银";
                else
                        output = chinese_number(amount / 100) + "两白银";
                amount %= 100;
        }
        if( amount )
                if( output != "" )
                        return output + "又" + chinese_number(amount) + "文铜板";
                else
                        return chinese_number(amount) + "文铜板";
        return output;
}

void pay_player(object who, int amount)
{
        int v;
        object ob;

        seteuid(getuid());
        if( amount < 1 )
                amount = 1;
        /*
        if( v = amount / 10000000 ) {
                ob = new(THGOLD_OB);
                ob->set_amount(v);
                ob->move(who, 1);
                amount %= 10000000;
        }
        if( v = amount / 100000 ) {
                ob = new(THCASH_OB);
                ob->set_amount(v);
                ob->move(who, 1);
                amount %= 100000;
        }
        */
        if( v = amount / 10000 ) {
                ob = new(GOLD_OB);
                ob->set_amount(v);
                ob->move(who, 1);
                amount %= 10000;
        }
        if( v = amount / 100 ) {
                ob = new(SILVER_OB);
                ob->set_amount(v);
                ob->move(who, 1);
                amount %= 100;
        }
        if( amount ) {
                ob = new(COIN_OB);
                ob->set_amount(amount);
                ob->move(who, 1);
        }
}

int player_pay(object who, int amount)
{
        object z_ob, t_ob, g_ob, s_ob, c_ob;
        int zc, tc, gc, sc, cc, left;
        int v;

        seteuid(getuid());

        if( z_ob = present("thousand-gold_money", who) )
                zc = z_ob->query_amount();
        else
                zc = 0;
        if (t_ob = present("thousand-cash_money", who))
                tc = t_ob->query_amount();
        else
                tc = 0;
        if( g_ob = present("gold_money", who) )
                gc = g_ob->query_amount();
        else
                gc = 0;
        if( s_ob = present("silver_money", who) )
                sc = s_ob->query_amount();
        else
                sc = 0;
        if( c_ob = present("coin_money", who) )
                cc = c_ob->query_amount();
        else
                cc = 0;

        v  = cc + sc * 100 + gc * 10000;
        v += tc * 100000;
        v += zc * 10000000;

        if( v < amount ) {
                if( query("balance", who)<amount )
                        return 0;

                addn("balance", -amount, who);
                return 1;
        } else {
                left = v - amount;
                if( zc ) {
                        zc = left / 10000000;
                        left %= 10000000;
                }

                if( tc ) {
                        tc = left / 100000;
                        left %= 100000;
                }
                gc = left / 10000;
                left = left % 10000;
                sc = left / 100;
                cc = left % 100;

                if( z_ob )
                        z_ob->set_amount(zc);

                if( t_ob )
                        t_ob->set_amount(tc);

                if( g_ob )
                        g_ob->set_amount(gc);
                else if( gc ) {
                        g_ob = new(GOLD_OB);
                        g_ob->set_amount(gc);
                        g_ob->move(who, 1);
                }
                if( s_ob )
                        s_ob->set_amount(sc);
                else if( sc ) {
                        s_ob = new(SILVER_OB);
                        s_ob->set_amount(sc);
                        s_ob->move(who, 1);
                }
                if( c_ob )
                        c_ob->set_amount(cc);
                else if( cc ) {
                        c_ob = new(COIN_OB);
                        c_ob->set_amount(cc);
                        c_ob->move(who, 1);
                }

                return 1;
        }
}

int player_carry(object ob)
{
        object sand_ob;
        object cash_ob;
        object gold_ob;
        object silver_ob;
        object coin_ob;
        int gold;

        gold=query("balance", ob)/10000;

        sand_ob = present("thousand-gold_money", ob);
        cash_ob = present("cash_money", ob);
        gold_ob = present("gold_money", ob);
        silver_ob = present("silver_money", ob);
        coin_ob = present("coin_money", ob);
        if( sand_ob ) gold += sand_ob->query_amount() * 1000;
        if( cash_ob ) gold += cash_ob->query_amount() * 10;
        if( gold_ob ) gold += gold_ob->query_amount();
        if( silver_ob ) gold += silver_ob->query_amount() / 100;
        if( coin_ob )   gold += coin_ob->query_amount() / 10000;
        return gold;
}
