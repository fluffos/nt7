#include "herb.h"

void create()
{
         set_name(NOR + BLU "七叶一枝花" NOR, ({ "qiye yizhihua","hua","herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIY "七叶一枝花(Paris polyphylla)的干燥根茎。因其叶多为7—10片轮生于茎项，而花单生于轮生叶片之上，故得此名。又因花的外轮花被片形大.似叶状；内轮花被片退化呈长线状 ......\n" NOR);
                set("base_unit", "颗");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

