// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("叫花子[2;37;0m[2;37;0m", ({"qigai"}));        
        set("gender", "女性");                
        set("long", "叫花子[2;37;0m
它是第五季节的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gbdm");
        set("owner_name", "第五季节");
        set_temp("owner", "gbdm");
        set_temp("owner_name", "第五季节");
        ::setup();
}
