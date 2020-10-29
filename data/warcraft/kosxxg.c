// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m柒学[2;37;0m[2;37;0m", ({"kosxxgpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是学柒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosxxg");
        set("owner_name", "学柒");
        set_temp("owner", "kosxxg");
        set_temp("owner_name", "学柒");
        ::setup();
}
