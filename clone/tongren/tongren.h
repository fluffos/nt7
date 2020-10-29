
#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "铜人NAME" NOR, ({ "铜人ID", "tongren" }));
        set_weight(50);
        
        set("unit", "个");
        set("long", NOR + YEL "这是一个冲穴铜人，上面绘制了一些经络穴位图案，以及冲穴使用方法。\n" NOR);
        set("value", 10000);
        set("material", "steal");

        set("jingmai_name", "JINGMAI_NAME");
        set("xuewei_name", "XUEWEI_NAME");
        set("chongxue_xiaoguo", "CHONGXUE_XIAOGUO");
        set("neili_cost", "NEILI_COST");
        setup();
}


