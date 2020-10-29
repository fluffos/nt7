// This program is a part of NITAN MudLIB 
// redl 2013/3
#include <ansi.h>
inherit BAOXIANG_ITEM;

void create()
{
        set_name(HIC"活跃度"HIY"宝箱"NOR,({"xiang"}));
        //这个一定要设置：
        set("BAOXIANG_LIST",([
                                "/clone/money/gold"                                     :341,
                                "/clone/money/cash"                                     :50,
                "/clone/medicine/yuqing"                        :148,
                "/clone/fam/etc/prize5"                         :105,
                "/clone/gift/puti-zi"                           :58,
                                "/clone/tessera/cdiamond"                         :10,
                                "/clone/tessera/cemerald"                         :10,
                                "/clone/tessera/cruby"                         :10,
                                "/clone/tessera/csapphire"                         :10,
                                "/clone/tessera/ctopaz"                         :10,
                                "/clone/tessera/rune11"                         :6,
                                "/clone/tessera/rune12"                         :6,
                                "/clone/tessera/rune13"                         :6,
                                "/clone/tessera/rune14"                         :6,
                                "/clone/tessera/rune15"                         :6,
                "/clone/gift/jiuzhuan"                          :80,
                                "/clone/tessera/rune20"                         :3,
                                "/clone/tessera/rune21"                         :3,
                                "/clone/tessera/rune22"                         :3,
                                "/clone/tessera/rune23"                         :3,
                                "/clone/tessera/rune24"                         :3,
                                "/clone/tessera/rune25"                         :2,
                                "/clone/tessera/rune26"                         :2,
                                "/clone/tessera/rune27"                         :2,
                                "/clone/tessera/rune28"                         :1,
                                "/clone/tessera/rune29"                         :1,
                                "/clone/tessera/rune30"                         :1,
                "/clone/gift/tianxiang"                         :9,
                                "/clone/goods/tianshi-charm"            :4,
                "/clone/gift/xuanhuang"                         :1,

                
        ])); //概率是以1000作为总数，且几项的概率总和为1000，概率大的出现几率高。。。
        
        set("long", HIY "这是一只华丽的箱子，装饰的珠光宝气，你或许可以打开（open）它。\n" NOR); 
        set("unit", "些");
        set("base_unit", "个");
                set("dynamic_quest", 1);
                        set("no_give","这样东西不能离开你。\n");
                        set("no_drop","这样东西不能离开你。\n");
                set("no_sell", "这样东西不能离开你。\n");
                set("no_put", "这样东西不能放在那儿。\n");
                set("no_store", "这样东西不能放在那儿。\n");
                set("no_get", "这样东西不能离开那儿。\n");
                set("no_steal", "这样东西不能离开那儿。\n");
                set("no_beg", "这样东西不能离开那儿。\n");
                set("base_value", 0);
                        set("base_weight",1);
        set_amount(1); //因为是个combined物品 所以这个一定要设置，不然报错的

}
void init()
{
        add_action("do_open","open"); //玩家使用的接口 具体内容在std里
        //add_action("do_test","test"); //用于巫师测试用 测试ok请注释此行
}
