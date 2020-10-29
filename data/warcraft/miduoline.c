// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("多才麒麟[2;37;0m[2;37;0m", ({"miduolinqilin"}));        
        set("gender", "男性");                
        set("long", "多才麒麟[2;37;0m
它是米多吴的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduoline");
        set("owner_name", "米多吴");
        set_temp("owner", "miduoline");
        set_temp("owner_name", "米多吴");
        ::setup();
}
