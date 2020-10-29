// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拖拉机[2;37;0m[2;37;0m", ({"daibu"}));        
        set("gender", "男性");                
        set("long", "行路难[2;37;0m
它是天山姥姥的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kokoyb");
        set("owner_name", "天山姥姥");
        set_temp("owner", "kokoyb");
        set_temp("owner_name", "天山姥姥");
        ::setup();
}
