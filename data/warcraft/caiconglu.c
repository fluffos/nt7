// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[35m童年[2;37;0m[2;37;0m", ({"childhood"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$MAG$童年[2;37;0m
它是蔡丛露的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "caiconglu");
        set("owner_name", "蔡丛露");
        set_temp("owner", "caiconglu");
        set_temp("owner_name", "蔡丛露");
        ::setup();
}
