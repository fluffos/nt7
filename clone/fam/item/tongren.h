// 铜人

#include <ansi.h>

inherit ITEM;

#define MEMBER_D        "/adm/daemons/memberd"

int is_tongren() { return 1; };

void create()
{
        set_name(NOR + YEL "铜人中文名" NOR, ({ "铜人ID" }) );
        set_weight(50);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + YEL "这是一个冲穴铜人，上面绘制了打通经脉的关键穴位。\n" HIG
                                      "*有关经脉冲穴的详细介绍请参见 help jingmai \n" NOR);
                set("value", 1);
                set("unit", "个");
                set("neili", NEILICOST); // 消耗内力
                set("jingmai_name", "JINGMAI_NAME"); // 经脉名
                set("xuewei_name", "XUEWEI_NAME"); // 穴位名
                set("point", "CHONGXUE_XIAOGUO"); // 冲穴效果
        }

        setup();
}

int query_autoload()
{
         return 1;
}