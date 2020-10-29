// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("淫荡情人[2;37;0m[2;37;0m", ({"aimin"}));        
        set("gender", "女性");                
        set("long", "一头很淫荡的.....[2;37;0m
它是幽林清风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "coolmoon");
        set("owner_name", "幽林清风");
        set_temp("owner", "coolmoon");
        set_temp("owner_name", "幽林清风");
        ::setup();
}
