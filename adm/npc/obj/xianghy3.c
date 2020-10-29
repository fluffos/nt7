// This program is a part of NITAN MudLIB 
// redl 2013/3
#include <ansi.h>
inherit BAOXIANG_ITEM;

void create()
{
        set_name(HIW"江湖"HIY"宝箱"NOR,({"xiang"}));
        //这个一定要设置：
        set("BAOXIANG_LIST",([
                                "/clone/money/gold"                                     :200,
                                "/clone/money/cash"                                     :50,
                "/clone/medicine/yuqing"                        :250,
                "/clone/fam/etc/prize5"                         :105,
                "/clone/gift/puti-zi"                           :58,
                                "/clone/tessera/rune11"                         :9,
                                "/clone/tessera/rune12"                         :9,
                                "/clone/tessera/rune13"                         :9,
                                "/clone/tessera/rune14"                         :9,
                                "/clone/tessera/rune15"                         :9,
                "/clone/gift/jiuzhuan"                          :80,
                                "/clone/tessera/rune20"                         :3,
                                "/clone/tessera/rune21"                         :3,
                                "/clone/tessera/rune22"                         :3,
                                "/clone/tessera/rune23"                         :3,
                                "/clone/tessera/rune24"                         :3,
                "/clone/gift/tianxiang"                         :9,
                                "/clone/goods/tianshi-charm"            :2,
                "/clone/gift/xuanhuang"                         :5,
                "/clone/tessera/diamond"                :4,
                "/clone/tessera/emerald"                :4,
                "/clone/tessera/sapphire"               :4,
                "/clone/tessera/ruby"                   :4,
                "/clone/tessera/topaz"                  :4,

                
        ])); //概率是以1000作为总数，且几项的概率总和为1000，概率大的出现几率高。。。
        
        set("long", HIY "这是宝宝在江湖游历时获取到的箱子，装饰的珠光宝气，你或许可以打开（open）它。\n" NOR); 
        set("unit", "些");
        set("base_unit", "个");
                set("dynamic_quest", 1);
                set("no_sell", "这样东西不能离开你。\n");
                set("no_store", "这样东西不能放在那儿。\n");
                set("no_steal", "这样东西不能离开那儿。\n");
                set("no_beg", "这样东西不能离开那儿。\n");
                set("base_value", 100);
                        set("base_weight",1);
        set_amount(1); //因为是个combined物品 所以这个一定要设置，不然报错的

}
void init()
{
        add_action("do_open","open"); //玩家使用的接口 具体内容在std里
        //add_action("do_test","test"); //用于巫师测试用 测试ok请注释此行
}

