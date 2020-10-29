// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("多林麒麟[2;37;0m[2;37;0m", ({"miduolins"}));        
        set("gender", "男性");                
        set("long", "多林麒麟[2;37;0m
它是米多三的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduolinc");
        set("owner_name", "米多三");
        set_temp("owner", "miduolinc");
        set_temp("owner_name", "米多三");
        ::setup();
}
