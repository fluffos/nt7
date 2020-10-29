// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啸易今夕[2;37;0m[2;37;0m", ({"chen_chong"}));        
        set("gender", "男性");                
        set("long", "通体碧绿，其身鳞片闪闪发亮，一吼[2;37;0m
它是遥剑沂笑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chenbikuan");
        set("owner_name", "遥剑沂笑");
        set_temp("owner", "chenbikuan");
        set_temp("owner_name", "遥剑沂笑");
        ::setup();
}
