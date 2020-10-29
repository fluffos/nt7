// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[35m童年[2;37;0m[2;37;0m", ({"childhood"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$MAG$童年[2;37;0m
它是柴玉红的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "chaiyuhong");
        set("owner_name", "柴玉红");
        set_temp("owner", "chaiyuhong");
        set_temp("owner_name", "柴玉红");
        ::setup();
}
