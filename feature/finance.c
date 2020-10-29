// finance.c
// can_afford() checks if this_object() can afford a price, it returns:
//
//      0:      cannot afford.
//      1:      can afford with proper money(coins).
//
int can_afford(int amount)
{
        int total;
        object gold, silver, coin, thousandcash, thousandgold;
        gold = present("gold_money",this_player());
        silver = present("silver_money",this_player());
        coin = present("coin_money",this_player());
        thousandcash = present("thousand-cash_money",this_player());
        thousandgold = present("thousand-gold_money",this_player());
        total = 0;
        if( thousandgold ) total += thousandgold->value();
        if( thousandcash ) total += thousandcash->value();
        if( gold ) total += gold->value();
        if( silver ) total += silver->value();
        if( coin ) total += coin->value();
        if( total < amount ) return 0;

        if( coin ) amount -= (int)coin->value();
        if( amount <= 0 ) return 1;
        else if( amount % 100 ) return 2;

        if( silver ) amount -= (int)silver->value();
        if( amount <= 0 ) return 1;
        else if( amount % 10000 ) return 2;

        if( gold ) amount -= (int)gold->value();
        if( amount <= 0 ) return 1;
        else if( amount % 10000000 ) return 2;
        return 1;
}
int pay_money(int amount)
{
        int total;
        object gold, silver, coin, thousandcash, thousandgold;
        int zc, tc;
    
        gold = present("gold_money",this_player());
        silver = present("silver_money",this_player());
        coin = present("coin_money",this_player());
        thousandcash = present("thousand-cash_money",this_player());
        thousandgold = present("thousand-gold_money",this_player());
        total = 0;
        if( thousandgold ) {
                zc = thousandgold->query_amount();
                total += thousandgold->value();
                destruct(thousandgold);
        }
        if( thousandcash ) {
                tc = thousandcash->query_amount();
                total += thousandcash->value();
                destruct(thousandcash);
        }
        if( gold ) {
                total += gold->value();
                destruct(gold);
        }
        if( silver ) {
                total += silver->value();
                destruct(silver);
        }
        if( coin ) {
                total += coin->value();
                destruct(coin);
        }
        if( total < amount ) return 0;
        
        total-=amount;
        if( total > 10000000 && zc ) {
                thousandgold=new(THGOLD_OB);
                if( !thousandgold->move(this_player()) ) thousandgold->move(environment(this_player()));
                thousandgold->set_amount(total/10000000);
                total %= 10000000;
        }        
        if( total > 100000 && tc ) {
                thousandcash=new(THCASH_OB);
                if( !thousandcash->move(this_player()) ) thousandcash->move(environment(this_player()));
                thousandcash->set_amount(total/100000);
                total %= 100000;
        }  
        if( total > 10000 ) {
                gold=new(GOLD_OB);
                if( !gold->move(this_player()) ) gold->move(environment(this_player()));
                gold->set_amount(total/10000);
                total %= 10000;
        }
        if( total > 100 ) {
                silver=new(SILVER_OB);
                if( !silver->move(this_player()) ) silver->move(environment(this_player()));
                silver->set_amount(total/100);
                total %= 100;
        }
        if( total > 0 ){
                coin=new(COIN_OB);
                if( !coin->move(this_player()) ) coin->move(environment(this_player()));
                coin->set_amount(total);
        }
        return 1;
}

