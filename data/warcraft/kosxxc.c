// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m叁学[2;37;0m[2;37;0m", ({"kosxxcpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是学叁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosxxc");
        set("owner_name", "学叁");
        set_temp("owner", "kosxxc");
        set_temp("owner_name", "学叁");
        ::setup();
}
