// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m球钱[2;37;0m[2;37;0m", ({"zxclpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱球的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxcl");
        set("owner_name", "钱球");
        set_temp("owner", "zxcl");
        set_temp("owner_name", "钱球");
        ::setup();
}
