
#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "冲穴铜人·阳跷脉·络却穴" NOR, ({ "tongren b18", "tongren" }));
        set_weight(50);
        
        set("unit", "个");
        set("long", NOR + YEL "这是一个冲穴铜人，上面绘制了一些经络穴位图案，以及冲穴使用方法。\n" NOR);
        set("value", 10000);
        set("material", "steal");

        set("jingmai_name", "阳跷脉");
        set("xuewei_name", "络却穴");
        set("chongxue_xiaoguo", "QI:500:MAR:100");
        set("neili_cost", "1100");
        setup();
}


