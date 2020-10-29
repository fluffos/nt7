
#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "冲穴铜人·冲脉·大赫穴" NOR, ({ "tongren f5", "tongren" }));
        set_weight(50);
        
        set("unit", "个");
        set("long", NOR + YEL "这是一个冲穴铜人，上面绘制了一些经络穴位图案，以及冲穴使用方法。\n" NOR);
        set("value", 10000);
        set("material", "steal");

        set("jingmai_name", "冲脉");
        set("xuewei_name", "大赫穴");
        set("chongxue_xiaoguo", "JIALI:50");
        set("neili_cost", "1000");
        setup();
}


