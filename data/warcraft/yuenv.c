// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "这就是朱雀。[2;37;0m
它是越女的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yuenv");
        set("owner_name", "越女");
        set_temp("owner", "yuenv");
        set_temp("owner_name", "越女");
        ::setup();
}
