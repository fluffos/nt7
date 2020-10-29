inherit ITEM;

int is_task() { return 1; }
varargs int move(mixed dest, int raw)
{
        object ob;

        if( ::move(dest, raw) ) {
                ob = environment();
                if (objectp(ob) && !query("geter") && userp(ob))
                        set("geter", ob->name(1));
                return 1;
        }
}

string extra_long()
{
        string str;

        str  = sprintf( "\n物品属性 : 任务物品，重量%d克，下线%s丢失\n",
                        this_object()->query_weight(),
                        (this_object()->query_autoload() || query("auto_load")) ? "不" : "" );

        return str;
}

