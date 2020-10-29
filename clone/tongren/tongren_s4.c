
#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "冲穴铜人·足阳明脉·地仓穴" NOR, ({ "tongren s4", "tongren" }));
        set_weight(50);
        
        set("unit", "个");
        set("long", NOR + YEL "这是一个冲穴铜人，上面绘制了一些经络穴位图案，以及冲穴使用方法。\n" NOR);
        set("value", 10000);
        set("material", "steal");

        set("jingmai_name", "足阳明脉");
        set("xuewei_name", "地仓穴");
        set("chongxue_xiaoguo", "MAR:20:FOOD:100");
        set("neili_cost", "30000");
        setup();
}


