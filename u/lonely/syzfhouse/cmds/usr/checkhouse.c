// /cmds/usr/checkhouse.c 查看自建屋宅情况指令
// By Alf, Last Update 2003.0720

#include <ansi.h>
#include <getconfig.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    int i, value;
    object ob;
    string type, msg, pass, *key;
    mapping house, build;

    seteuid(getuid());

    if(!arg)
        ob = me;
    else
        ob = LOGIN_D->find_body(arg);

    if(ob && ob != me && !wizardp(me))
        return notify_fail("只有巫师可以查看他人的屋宅情况。\n");
    if(!ob)
        return notify_fail("你想查看的人目前不在线。\n");

    build = ob->query("house/build");
    if(sizeof(build) == 0)
        return notify_fail((ob == me ? "你" : ob->name()) + "目前尚未在「"
                            HIY + LOCAL_MUD_NAME() + NOR"」拥有任何屋宅。\n");
    msg  = HIC "\n" + (ob == me ? "你" : ob->name()) + "目前在「"
           HIY + LOCAL_MUD_NAME() + HIC"」拥有的屋宅有：\n";
    msg += HIG "-----------------------------------------------------------------\n" NOR;
    key = sort_array(keys(build), 1);
    for(i = 0; i < sizeof(key); i++)
    {
        house = ob->query("house/" + key[i]);
        if(key[i] == "user")    type = "玩家住宅";
        if(key[i] == "bang")    type = "帮会驻地";
        if(key[i] == "xian")    type = "散仙居所";
        msg += sprintf(HIW "一处位于" HIC "%s%s" HIW "的%s「"
                       HIG "%s" HIW "」，价值" NOR, house["base"]["place"],
                                                    house["base"]["name"],
                                                    type,
                                                    house["name"]);
        if(key[i] == "xian")
            msg += HIW "已非凡物可以计算。\n" NOR;
        else
            msg += sprintf(HIY " %-6d两黄金" HIW "。\n", house["value"]);

        if(wizardp(me) && wiz_level(me) > 3)
            msg += sprintf(HIW "%s在" HIC "%s%s" HIW "的这套"
                           HIG "%s" HIW "的屋宅编码为：『"
                           HIY "%s" HIW "』。\n" NOR, (ob == me ? "你" : ob->name()),
                                                      house["base"]["place"],
                                                      house["base"]["name"],
                                                      house["name"],
                                                      house["pass"]);
    }
    msg += HIG "-----------------------------------------------------------------\n" NOR;
    tell_object(me, msg);
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式：checkhouse [ID]

这个指令可用来查看自己拥有的屋宅情况。
巫师可用该指令查看某一玩家的屋宅情况。

HELP);
    return 1;
}