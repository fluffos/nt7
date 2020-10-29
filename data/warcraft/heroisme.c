// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("赤眉碧睛麒麟[2;37;0m[2;37;0m", ({"heroismine"}));        
        set("gender", "男性");                
        set("long", "红眉绿眼健硕无比[2;37;0m
它是大风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "heroisme");
        set("owner_name", "大风");
        set_temp("owner", "heroisme");
        set_temp("owner_name", "大风");
        ::setup();
}
