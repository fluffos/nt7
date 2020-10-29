// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大雅[2;37;0m[2;37;0m", ({"pifengblong"}));        
        set("gender", "男性");                
        set("long", "大欲[2;37;0m
它是麒麟衣的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pifengb");
        set("owner_name", "麒麟衣");
        set_temp("owner", "pifengb");
        set_temp("owner_name", "麒麟衣");
        ::setup();
}
