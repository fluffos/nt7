#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "莹血蛛丝" NOR, ({"yingxue zhusi", "yingxue", "zhusi"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "据说楚国有一剧毒蜘蛛，名为：莹血，不但其血液晶莹剔透，且于夜晚处荧光闪\n"
                                                "闪，婉如明珠，剧毒无比，触之及死。所吐之丝细柔若无，却丝毫无毒，常年生\n"
                                                                "活在深山秘穴之中，常人即使发现其行踪，但要捕捉取丝多半也是被其剧毒所伤，\n"
                                                                "无一幸免。\n" HIG 
                                                                "千百年来莹血蛛丝为制作披风的最佳材料。所铸造出披风永不磨损。\n" NOR);
                set("unit", "卷");
                set("value", 20000);
                set("item_origin", 1);
                set("material_attrib", "tian jing");
                set("material_name", HIR "莹血蛛丝" NOR);
                set("can_make", ({ "披风" }));
                set("power_point", 150 + random(10));
        }
}

int query_autoload()
{
        return 1;
}
