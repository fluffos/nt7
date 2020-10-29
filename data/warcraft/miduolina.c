// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("多林麒麟一[2;37;0m[2;37;0m", ({"duolina"}));        
        set("gender", "男性");                
        set("long", "多林麒麟一[2;37;0m
它是米多一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduolina");
        set("owner_name", "米多一");
        set_temp("owner", "miduolina");
        set_temp("owner_name", "米多一");
        ::setup();
}
