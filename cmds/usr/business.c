// business.c

inherit F_CLEAN_UP;

nomask int main(object me, string arg)
{
        object ob;

        if( arg && wizardp(me) )
                ob = find_player(arg);

        if( !ob )
                ob = me;

        write(ob->query_business_status());
        return 1;
}

int help()
{
        write("\n此命令可以列出你的贸易情况。\n\n");
        return 1;
}
