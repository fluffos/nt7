// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("花爵[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "花爵[2;37;0m
它是百炼生的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "liansheng");
        set("owner_name", "百炼生");
        set_temp("owner", "liansheng");
        set_temp("owner_name", "百炼生");
        ::setup();
}
