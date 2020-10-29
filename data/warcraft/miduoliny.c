// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("多歪麒麟[2;37;0m[2;37;0m", ({"miduoyqilin"}));        
        set("gender", "男性");                
        set("long", "多歪麒麟[2;37;0m
它是米多福的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduoliny");
        set("owner_name", "米多福");
        set_temp("owner", "miduoliny");
        set_temp("owner_name", "米多福");
        ::setup();
}
