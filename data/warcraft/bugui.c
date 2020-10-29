// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("太白虎[2;37;0m[2;37;0m", ({"feifei"}));        
        set("gender", "女性");                
        set("long", "好大只白虎[2;37;0m
它是何处归的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "bugui");
        set("owner_name", "何处归");
        set_temp("owner", "bugui");
        set_temp("owner_name", "何处归");
        ::setup();
}
