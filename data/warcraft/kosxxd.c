// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m肆学[2;37;0m[2;37;0m", ({"kosxxdpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是学肆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosxxd");
        set("owner_name", "学肆");
        set_temp("owner", "kosxxd");
        set_temp("owner_name", "学肆");
        ::setup();
}
