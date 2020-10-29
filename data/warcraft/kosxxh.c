// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m捌学[2;37;0m[2;37;0m", ({"kosxxhpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是学捌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosxxh");
        set("owner_name", "学捌");
        set_temp("owner", "kosxxh");
        set_temp("owner_name", "学捌");
        ::setup();
}
