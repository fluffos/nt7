// by tangfeng 8/2004

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"提示卡"NOR, ({ "tishi ka", "ka", "paper"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long", "这是来自巫师的东西，似乎和冷泉神功有关。\n\n"
                            +"提示一：有其他内功为情况下，学习冷泉神功速度减半。\n"
                            +"提示二：学会冷泉神功后，胡家刀法和苗家剑法才能发挥真正的威力。\n"
							+"提示三：寻找纸团，VIP两次机会，普通玩家一次机会。\n"); 
                set("unique", 1);
                set("treasure", 1);
                set("material", "silk");
                set("no_give", "这样东西不能离开你。\n");
                set("no_get", "这样东西不能离开那儿。\n");
        }
}
