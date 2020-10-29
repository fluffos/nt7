// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("金乌杖[2;37;0m[2;37;0m", ({"jinwu_staff"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是呼延庆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesj");
        set("owner_name", "呼延庆");
        set_temp("owner", "zuesj");
        set_temp("owner_name", "呼延庆");
        ::setup();
}
