// This program is a part of NITAN MudLIB 
// redl 2014/3
#include <ansi.h>
inherit BAOXIANG_ITEM;

void create()
{
        set_name(NOR BLU"护舒宝"NOR,({"hushu bao", "bao"}));
        set("BAOXIANG_LIST",([
                                "/clone/money/thousand-gold"            :800,
                                "/clone/goods/tianshi-charm"            :130,
                                "/d/dongtian/obj/wanxiangbook"          :67,
                                "/u/redl/npc/obj/ntb"                   :3

        ])); //概率是以1000作为总数，且几项的概率总和为1000，概率大的出现几率高。。。
        
        set("long", NOR BLU "这是女性夜里专用（open）物品，男童鞋拿去客店送给戚长发处理吧。\n" NOR); 
        set("unit", "些");
        set("base_unit", "包");
                set("dynamic_quest", 1);
                set("no_sell", "这样东西不能离开你。\n");
                set("no_store", "这样东西不能放在那儿。\n");
                set("no_steal", "这样东西不能离开那儿。\n");
                set("no_beg", "这样东西不能离开那儿。\n");
                set("base_value", 100);
                set("base_weight",1);
        set("bindable", 2); 
        set_amount(1); //因为是个combined物品 所以这个一定要设置，不然报错的

}

int cantuse()
{
        tell_object(this_player(), "你冥思苦想怎么也得不出恰当的使用方法。\n");
        return 1;
}

void init()
{
        if (query("gender",this_player())=="女性") {
                add_action("do_open","open"); //玩家使用的接口 具体内容在std里
        } else {
                add_action("cantuse","open"); //玩家使用的接口 具体内容在std里
        }
        //add_action("do_test","test"); //用于巫师测试用 测试ok请注释此行
}

