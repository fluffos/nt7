// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m壹武[2;37;0m[2;37;0m", ({"mathpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是武壹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "math");
        set("owner_name", "武壹");
        set_temp("owner", "math");
        set_temp("owner_name", "武壹");
        ::setup();
}
