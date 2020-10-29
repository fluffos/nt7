// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m肆黄[2;37;0m[2;37;0m", ({"matxpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是黄肆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matx");
        set("owner_name", "黄肆");
        set_temp("owner", "matx");
        set_temp("owner_name", "黄肆");
        ::setup();
}
