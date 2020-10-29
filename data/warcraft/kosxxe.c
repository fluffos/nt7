// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m伍学[2;37;0m[2;37;0m", ({"kosxxepet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是学伍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosxxe");
        set("owner_name", "学伍");
        set_temp("owner", "kosxxe");
        set_temp("owner_name", "学伍");
        ::setup();
}
