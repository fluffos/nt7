// examined.c

// #pragma optimize
// #pragma save_binary

#include <localtime.h>

inherit F_DBASE;
inherit F_SAVE;

nosave int auto_examine = 0;

void create()
{
        seteuid(getuid());
        ::restore();
        set("channel_id", "检查精灵");
        auto_examine = CONFIG_D->query_int("enable auto examine");
}

string query_save_file()
{
        return DATA_DIR "examined";
}

void remove()
{
        save();
}

void examine_player(object ob)
{
        int exp;
        object sandgold, cash, gold, silver, coin;
        string log_msg;
        int tval;

        if (! auto_examine || wizardp(ob))
                return;

        sandgold = present("thousand-gold_money", ob);
        cash = present("cash_money", ob);
        gold = present("gold_money", ob);
        silver = present("silver_money", ob);
        coin = present("coin_money", ob);
        exp=query("combat_exp", ob);

        tval = 0;
        if( sandgold ) tval += sandgold->query_amount() * 1000;
        if (cash) tval += cash->query_amount() * 10;
        if (gold) tval += gold->query_amount();
        if (tval < 100) return;
        if (silver) tval += silver->query_amount() / 100;
        if (coin) tval += coin->query_amount() / 10000;

        if (tval > 30000)
        {
                if( !query_temp("reported/too_much_money", ob) )
                {
                        set_temp("reported/too_much_money", 1, ob);
                        log_msg = sprintf("%s(%s) has (%d gold) at %s on %s",
                                          ob->name(1),query("id", ob),tval,
                                          (environment(ob) ? base_name(environment(ob)) : "Unknow"),
                                          ctime(time()));
                        log_file("user/money_report", log_msg + "\n");
                        CHANNEL_D->do_channel(this_object(), "sys", log_msg);
                }

                if (! ob->is_loging_now() &&
                    find_object(CONFIG_D) &&
                    CONFIG_D->query_int("enable auto log"))
                        // I will call the user to start log
                        // directly, because I don't want log
                        // the user after he quit & relogin
                        ob->start_log();
        }
}

string create_log_file(object ob)
{
        string fn;
        mixed lt;

        if (! userp(ob))
                return 0;

        lt = localtime(time());

        fn = "user/" + sprintf("%d-%d-%d/", lt[LT_YEAR],
                               lt[LT_MON] + 1, lt[LT_MDAY]) +
             query("id", ob);
        assure_file(LOG_DIR + fn);

        return fn;
}

int start_log_player(string id, string me)
{
        mixed by;
        object ob;

        if (! is_root(previous_object()))
                return 0;

        by = query("log_by/" + id);
        if (stringp(by) && (wiz_level(by) > wiz_level(me)))
                return notify_fail("已经有权限比你高的人记录该玩家的日志了。\n");

        if (stringp(by) && by == me)
                return notify_fail("你已经开始记录这个玩家的日志了。\n");

        ob = find_player(id);
        if (! by && ob && ob->is_loging_now() && wizhood(me) != "(admin)")
                return notify_fail("EXAMINE DAEMON 正在记录这个玩家的日志，你无权干涉。\n");

/*
        if (wizhood(id) == "(admin)" &&
            (!this_player() || !query("env/admin", this_player())) )
                return notify_fail("不能记录 admin 的日志。\n");

*/
        set("log_by/" + id, me);

        log_file("static/log_user", sprintf("%s start log %s on %s\n",
                                            me, id, ctime(time())));
        if (objectp(ob)) ob->start_log();
        save();

        return 1;
}

int end_log_player(string id, string euid)
{
        object ob;
        mixed by;

        if (! is_root(previous_object()))
                return 0;

        ob = find_player(id);
        by = query("log_by/" + id);

        if (! by && (! ob || ! ob->is_loging_now()))
                return notify_fail("系统现在并没有记录这个玩家的日志。\n");

        if (euid == ROOT_UID || wizhood(euid) == "(admin)" ||
            stringp(by) && (by == euid || wiz_level(by) <= wiz_level(euid)))
        {
                delete("log_by/" + id);
                log_file("static/log_user", sprintf("%s stop log %s on %s\n",
                                                    euid, id, ctime(time())));
                save();
                if (objectp(ob)) ob->end_log();
                return 1;
        }

        return notify_fail("你不是 ROOT 或是开始记录日志的巫师，不能中止记录。\n");
}

varargs mixed query(string idx, object ob)
{
        if( !ob ) ob = this_object();
        if (previous_object() && ! is_root(previous_object()))
                return 0;

        return ob->query_db(idx);
}

varargs mixed set(string idx, mixed data, object ob)
{
        if( !ob ) ob = this_object();
        if (previous_object() && ! is_root(previous_object()))
                return 0;

        return ob->set_db(idx, data);
}
