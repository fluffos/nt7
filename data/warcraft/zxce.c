// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m伍钱[2;37;0m[2;37;0m", ({"zxcepet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是钱伍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxce");
        set("owner_name", "钱伍");
        set_temp("owner", "zxce");
        set_temp("owner_name", "钱伍");
        ::setup();
}
