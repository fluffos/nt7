#include <ansi.h>

inherit ITEM;

#define MEMBER_D        "/adm/daemons/memberd"

void create()
{
        set_name(HIY "炎黄金条" NOR, ({ "yhhero goldbar", "yhhero", "goldbar" }) );
        set_weight(300);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "一根金灿灿的金条，拿在手里颇为舒适。\n"
                            "使用 changing 指令将炎黄金条兑换为十万YSG，会员可兑换十一万YSG。\n" 
                            "如果暂时不使用，最好将金条存入仓库，以免丢失。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "根");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_changing", "changing");
        }
}

int do_changing(string arg)
{
        object me;
        object ob;
        string enid, obid;
        int point, cur_firm;

        me = this_player();
                
        if (! MEMBER_D->is_valib_member(me->query("id")))
        {
                me->add("stocks/balance", 100000);
                write(HIG "成功将一跟炎黄金条兑换为十万YSG并存入了您的银库。\n" NOR);
                write(HIY "您目前在炎黄银库存有 " + HIC + me->query("stocks/balance") + HIY "YSG。\n" NOR);

        }
        else
        {
                me->add("stocks/balance", 110000);
                write(HIG "成功将一跟炎黄金条兑换为十一万YSG并存入了您的银库。\n" NOR);
                write(HIY "您目前在炎黄银库存有 " + HIC + me->query("stocks/balance") + HIY "YSG。\n" NOR);
        }

        destruct(this_object());
        me->save();

        return 1;
}

int query_autoload()
{
         return 1;
}