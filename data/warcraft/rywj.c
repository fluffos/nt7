// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("其实也想留[2;37;0m[2;37;0m", ({"qsbxz"}));        
        set("gender", "男性");                
        set("long", "不知道说啥[2;37;0m
它是日月无极的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "rywj");
        set("owner_name", "日月无极");
        set_temp("owner", "rywj");
        set_temp("owner_name", "日月无极");
        ::setup();
}
