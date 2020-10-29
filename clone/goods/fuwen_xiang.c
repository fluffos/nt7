#include <ansi.h>
inherit BAOXIANG_ITEM;

void create()
{
        set_name(HIM"符文箱子"NOR,({"xiang"}));
        //这个一定要设置：
        set("BAOXIANG_LIST",([
                "/clone/tessera/rune01":100,   //物品文件名:概率
                "/clone/tessera/rune02":95,   //物品文件名:概率
                "/clone/tessera/rune03":90,   //物品文件名:概率
                "/clone/tessera/rune04":85,   //物品文件名:概率
                "/clone/tessera/rune05":80,   //物品文件名:概率
                "/clone/tessera/rune06":75,
                "/clone/tessera/rune07":70,
                "/clone/tessera/rune08":65,
                "/clone/tessera/rune09":60,
                "/clone/tessera/rune10":55,
                "/clone/tessera/rune11":43,
                "/clone/tessera/rune12":40,
                "/clone/tessera/rune13":37,
                "/clone/tessera/rune14":35,
                "/clone/tessera/rune15":30,
                "/clone/tessera/rune16":15,
                "/clone/tessera/rune17":10,
                "/clone/tessera/rune18":8,
                "/clone/tessera/rune19":5,
                "/clone/tessera/rune20":2,
        ])); //概率是以1000作为总数，且几项的概率总和为1000，概率大的出现几率高。。。
        
        set("long", HIY "这是一只金色的宝箱，装饰的珠光宝气，你或许可以打开（open）它。\n" NOR); 
        set("unit", "些");
        set("base_unit", "个");
        set("no_give",1);
        set("no_drop",1);
        set("base_weight",1);
        set("base_value",1);
        set_amount(1); //因为是个combined物品 所以这个一定要设置，不然报错的

}
void init()
{
        add_action("do_open","open"); //玩家使用的接口 具体内容在std里
        add_action("do_test","test"); //用于巫师测试用 测试ok请注释此行
}

