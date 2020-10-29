// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽兽[2;37;0m[2;37;0m", ({"qiling"}));        
        set("gender", "男性");                
        set("long", "兽兽[2;37;0m
它是测试甲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "abctest");
        set("owner_name", "测试甲");
        set_temp("owner", "abctest");
        set_temp("owner_name", "测试甲");
        ::setup();
}
