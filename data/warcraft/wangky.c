// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m坤月[2;37;0m[2;37;0m", ({"kunyue"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIM$坤月[2;37;0m
它是忘困月的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wangky");
        set("owner_name", "忘困月");
        set_temp("owner", "wangky");
        set_temp("owner_name", "忘困月");
        ::setup();
}
