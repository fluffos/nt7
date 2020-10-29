// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"weiwang"}));        
        set("gender", "男性");                
        set("long", "麒麟就是麒麟 有啥好描述的 自己看[2;37;0m
它是王小的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wangwei");
        set("owner_name", "王小");
        set_temp("owner", "wangwei");
        set_temp("owner_name", "王小");
        ::setup();
}
