// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m坤月[2;37;0m[2;37;0m", ({"kunyue"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIM$坤月[2;37;0m
它是望坤月的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "smd");
        set("owner_name", "望坤月");
        set_temp("owner", "smd");
        set_temp("owner_name", "望坤月");
        ::setup();
}
