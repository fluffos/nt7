// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[45m[1;32m魔法飞毯[2;37;0m[2;37;0m", ({"fei_tan"}));        
        set("gender", "女性");                
        set("long", "魔法飞毯[2;37;0m
它是舞沉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wuc");
        set("owner_name", "舞沉");
        set_temp("owner", "wuc");
        set_temp("owner_name", "舞沉");
        ::setup();
}
