// banker.c
// Rewritten by Lonely@XYZX (16/05/2009)

#include <ansi.h>

#ifndef STORAGE_D
#define STORAGE_D "/adm/daemons/storaged"
#endif


#define REBOOT_CMD      "/cmds/arch/reboot"

int do_check()
{
        // here we use 3 units to display bank infos
        int total = (int)query("balance", this_player());
        if( !total || total < 0) {
                set("balance", 0, this_player());
                write("您在敝商号没有存钱。\n");
                return 1;
        }
        write(query("name")+"悄悄告诉你：您在弊商号共存有" +
              MONEY_D->money_str(total) + "。\n");
        return 1;
}

int do_convert(string arg)
{
        string from, to;
        int amount, bv1, bv2;
        object from_ob, to_ob;
        object me;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("你还是等有空了再说吧！\n");

        if( this_object()->is_fighting() )
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if( !arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3 )
                return notify_fail("命令格式：convert|duihuan <数量> <货币单位> to <新货币单位>\n");

        from_ob = present(from + "_money", me);
        to_ob = present(to + "_money", me);

        if( !to_ob && file_size("/clone/money/" + to + ".c") < 0 )
                return notify_fail("你想兑换成什么？\n");

        if( !from_ob )
                return notify_fail("你身上没有带这种钱。\n");

        if( from_ob == to_ob )
                return notify_fail("你有毛病啊？\n");

        if( amount < 1 )
                return notify_fail("你想白赚啊？\n");

        if( (int)from_ob->query_amount() < amount )
                return notify_fail("你带的" + query("name", from_ob) + "不够。\n");

        bv1 = query("base_value", from_ob);
        if( !bv1 )
                return notify_fail("这样东西不值钱。\n");

        bv2 = to_ob ? query("base_value", to_ob)
                    : query("base_value", get_object("/clone/money/" + to));

        if( !bv2 )
                return notify_fail("这样东西不值钱。\n");

        if( bv1 < bv2 )  amount -= amount % (bv2 / bv1);
        if( amount == 0 )
                return notify_fail("这些" + query("name", from_ob) +
                                   "不够换。\n ");

        if( bv1 > bv2 && bv1 / bv2 * amount > 20000 )
                return notify_fail("哦呦...我这一下子还拿不出这么多散钱...\n");

        // allowed to convert now
        me->start_busy(1);

        from_ob->add_amount(-amount);

        if( !to_ob ) {
                to_ob = new("/clone/money/" + to);
                to_ob->set_amount(amount * bv1 / bv2);
                to_ob->move(me, 1);
        } else  to_ob->add_amount(amount * bv1 / bv2);

        message_vision(sprintf("$N从身上取出%s%s%s，换成了%s%s%s。\n",
                chinese_number(amount),
                query("base_unit", from_ob),
                query("name", from_ob),
                chinese_number(amount * bv1 / bv2),
                query("base_unit", to_ob),
                query("name", to_ob)), me);

        return 1;
}

int do_deposit(string arg)
{
        string what;
        int amount;
        object what_ob, me;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("你还是等有空了再说吧！\n");

        if( this_object()->is_fighting() )
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if( !arg || (sscanf(arg, "%d %s", amount, what) != 2 &&
            sscanf(arg, "all %s", what) != 1) )
                return notify_fail("命令格式：deposit:cun <数量>|all <货币单位>\n");

        what_ob = present(what + "_money", me);
        if( !what_ob )
                return notify_fail("你身上没有带这种钱。\n");

        if( !amount ) amount = what_ob->query_amount();
        if( amount < 1 )
                return notify_fail("你想存多少" + query("name", what_ob) + "？\n");

        if( (int)what_ob->query_amount() < amount )
                return notify_fail("你带的" + query("name", what_ob) + "不够。\n");

        // deposit it
        me->start_busy(1);

        addn("balance", query("base_value", what_ob) * amount, me);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N拿出%s%s%s，存进了银号。\n",
                chinese_number(amount), query("base_unit", what_ob),
                query("name", what_ob)), me);

        MYGIFT_D->check_mygift(me, "newbie_mygift/cunqian"); 
        return 1;
}

int do_withdraw(string arg)
{
        string what, t;
        int amount;
        object what_ob, me;
        int v;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("你还是等有空了再说吧！\n");

        if( this_object()->is_fighting() )
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if( !arg || sscanf(arg, "%d %s", amount, what) != 2 )
                return notify_fail("命令格式：withdraw|qu <数量> <货币单位>\n");

        if( amount < 1 )
                return notify_fail("你想取出多少钱？\n");

        if( amount >= 10000 )
                return notify_fail("这么大的数目。本店没这么多零散现金。\n");

        if( file_size("/clone/money/" + what + ".c") < 0 )
                return notify_fail("你想取出什么钱？\n");

        t = "/clone/money/" + what;
        if( (v = amount * query("base_value", get_object(t))) > query("balance", me) || v <= 0 )
               return notify_fail("你存的钱不够取。\n");

        me->start_busy(1);

        what_ob = new(t);
        what_ob->set_amount(amount);
        if( me->query_encumbrance() + what_ob->query_weight() > me->query_max_encumbrance() )
        {
                tell_object(me, "你的负重不够，无法拿动这么多钱。\n");
                destruct(what_ob);
                return 1;
        }
        what_ob->move(me, 1);
        addn("balance",  -v, me);
        //MONEY_D->pay_player(me, v, what);

        //message_vision(sprintf("$N从银号里取出%s。\n", MONEY_D->money_str(v)), me);
        message_vision(sprintf("$N从银号里取出%s%s%s。\n",
                chinese_number(amount), query("base_unit", what_ob),
                query("name", what_ob)), me);

        me->save();
        return 1;
}

int do_transfer(string arg)
{
        string who, what;
        int value;
        object me, ob;
        int amount;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("你还是等有空了再说吧！\n");

        if( this_object()->is_fighting() )
                return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

        if( REBOOT_CMD->is_rebooting() )
                return notify_fail("现在本站正在准备重新启动，本钱庄暂停转帐功能。\n");

        if( !arg || sscanf(arg, "%d %s to %s", amount, what, who) != 3 )
                return notify_fail("命令格式：transfer|zhuan <数量> <货币单位> to <某人>\n");

        if( amount < 1 )
                return notify_fail("你想转帐多少钱？\n");

        if( amount > 10000000 )
                return notify_fail("这么大的数目，有洗钱的嫌疑，本店可不敢犯法。\n");

        if( file_size("/clone/money/" + what + ".c") < 0 )
                return notify_fail("你想转帐钱的单位是？\n");

        what = "/clone/money/" + what;
        value = amount*query("base_value", get_object(what));

        if( value > query("balance", me) || value <= 0 )
               return notify_fail("你存的钱不够转帐。\n");

        if( !objectp(ob = UPDATE_D->global_find_player(who)) )
                return notify_fail("没有这个人！\n");

        me->start_busy(1);

        addn("balance", -value, me);
        addn("balance",  value, ob);
        me->save();
        ob->save();
        tell_object(ob, "\a", 0);
        tell_object(ob, HIR + me->query_idname(1) + HIR "从银号里划转"+ MONEY_D->money_str(value) + "到你的帐户上。\n" NOR);
        tell_object(me, HIR "你从银号里划转"+ MONEY_D->money_str(value) + "到" + ob->query_idname(1) + HIR "的帐户上。\n" NOR);
        UPDATE_D->global_destruct_player(ob, 1);
        return 1;
}

//储物柜业务
int do_cw(string arg)
{
        string cmd;
        object me = this_player();
        if( !arg || arg=="" ) {
                write("请使用cw help来查询使用帮助。\n");
                return 1;
        }
        arg = lower_case(arg);
        if( arg == "help" || arg == "cancel" || arg == "list" )
                cmd = arg;
        else if( sscanf(arg,"%s %s",cmd,arg) != 2 ) {
                //dohelp2
                write("请使用cw help来查询使用帮助。\n");
                return 1;
        }
        switch( cmd ) {
        case "open":    //开帐户
                STORAGE_D->OpenAccount(me,arg);
                break;
        case "put":
                STORAGE_D->PutObject(me,arg);
                break;
        case "get":
                STORAGE_D->GetObject(me,arg);
                break;
        case "fee":
                STORAGE_D->DoFee(me,arg);
                break;
        case "list":
                STORAGE_D->ListObject(me);
                break;
        case "cancel":
                STORAGE_D->CancelAccount(me);
                break;
        case "help":
                STORAGE_D->ShowHelp(me);
                break;
        default:
                write("你想要做什么啊？还是使用cw help来查看一下帮助吧！\n");
        }
        return 1;
}
